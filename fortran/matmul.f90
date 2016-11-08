module matrix
    contains
    function matmul_(matrix_a, matrix_b) result(matrix_r)
        implicit none
        double precision, intent(in), dimension(:, :) :: matrix_a, matrix_b
        double precision, dimension(:, :), allocatable :: matrix_r
        integer :: n, i, j, k
        double precision :: s

        n = size(matrix_a, 1)
        allocate(matrix_r(n, n))

        !$OMP parallel shared(matrix_a, matrix_b, matrix_r, n) private(i, j, s, k)

        !$OMP parallel do
        do i = 1, n
            do j = 1, n
                s = 0.0
                do k = 1, n
                    s = s + matrix_a(i, k) * matrix_b(k, j)
                end do
                matrix_r(i, j) = s
            end do
        end do
        !$OMP end parallel do

        !$OMP end parallel
    end function matmul_
end module matrix

program main
    use matrix
    implicit none
    integer :: i, j, n
    real :: cl1, cl2
    double precision, dimension(:,:), allocatable :: matrix_a, matrix_b, matrix_r
    character(len=32) :: arg

    call get_command_argument(1, arg)

    if(len_trim(arg) == 0) then
        write(0, *) "use: matmul <n>"
        stop 9
    end if

    read(arg, '(i32)') n

    allocate(matrix_a(n, n))
    allocate(matrix_b(n, n))

    call random_number(matrix_a)
    call random_number(matrix_b)

    call cpu_time(cl1)
    !matrix_r = matmul_(matrix_a, matrix_b)
    matrix_r = matmul(matrix_a, matrix_b)
    call cpu_time(cl2)

    do i = 1, size(matrix_a, 1)
        write(*, "(10g10.5)") (matrix_r(j, i), j = 1, size(matrix_a, 1))
    end do

    write(0, "(g16.10' seconds')") (cl2 - cl1)
end program main
