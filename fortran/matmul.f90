module matrix
    contains
    function matmul(matrix_a, matrix_b) result(matrix_r)
        implicit none
        double precision, intent(in), dimension(:, :) :: matrix_a, matrix_b
        double precision, dimension(:, :), allocatable :: matrix_r
        integer :: n, i, j, k
        double precision :: s

        n = size(matrix_a, 1)
        allocate(matrix_r(n, n))

        do i = 1, n
            do j = 1, n
                s = 0.0
                do k = 1, n
                    s = s + matrix_a(i, k) * matrix_b(k, j)
                end do
                matrix_r(i, j) = s
            end do
        end do
    end function matmul

    subroutine load_matrix(infile, matrix_a, matrix_b)
        implicit none
        character*(*) :: infile
        double precision, intent(out), dimension(:, :), allocatable :: matrix_a, matrix_b
        integer :: n, res

        open(10, file=infile, access="sequential", form="formatted", iostat=res)

        read(10, *) n

        allocate(matrix_a(n, n))
        allocate(matrix_b(n, n))

        read(10, *) matrix_a
        read(10, *) matrix_b

        close(10)
    end subroutine load_matrix
end module

program main
    use matrix
    implicit none
    integer :: i, j
    real :: cl1, cl2
    double precision, dimension(:,:), allocatable :: matrix_a, matrix_b, matrix_r
    character*(*), parameter :: infile = "matrix.csv"

    ! matrix_a = reshape((/ 0.2, 0.4, 0.6, 0.8, 0.1, 0.3, 0.5, 0.7, 0.9 /), shape(matrix_a))
    ! matrix_b = reshape((/ 0.2, 0.4, 0.6, 0.8, 0.1, 0.3, 0.5, 0.7, 0.9 /), shape(matrix_b))

    call load_matrix(infile, matrix_a, matrix_b)

    call cpu_time(cl1)
    matrix_r = matmul(matrix_a, matrix_b)
    call cpu_time(cl2)

    do i = 1, size(matrix_a, 1)
        write(*, "(10g10.5)") (matrix_r(j, i), j = 1, size(matrix_a, 1))
    end do

    write(0, "(g16.10' seconds')") (cl2 - cl1)
end program main
