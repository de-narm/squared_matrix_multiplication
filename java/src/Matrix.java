import java.io.File;
import java.io.PrintWriter;
import java.util.Random;
import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

/**
 * @author Matthias Nickel
 * 
 * Represents a n x n Matrix.
 *
 */
public class Matrix {

	/**
	 * Array of cells
	 */
	private double cell[][];
	
	public static void main(String[] args) {
		Matrix matrixA, matrixB;
		Scanner scanner = new Scanner(System.in);
		final int MIN_THREADS = 2;
		final int THREAD_INC = 1;
		//gets number of CPU cores
		final int NUMBER_OF_CORES = Runtime.getRuntime().availableProcessors();
		
		int max_threads = NUMBER_OF_CORES;
		int min_rc = 100;
		int max_rc = 2000;
		int max_print_size = 4;
		
		ExecutorService es;
		
		System.out.println("Quadratic Matrix Multiplication\nNumber of Available Cores: " + NUMBER_OF_CORES);
		
		int choice;
		do{
			//ask user if he wants a benchmark, to calculate a 
			System.out.print(
					  "\n----------------------------------------------------"
					+ "\n1 - Benchmark\n2 - Calculate\n3 - Options\n4 - Exit"
					+ "\n----------------------------------------------------"
					+ "\nOption: ");
			try{
				choice = scanner.nextInt();
			} catch(Exception e){
				choice = 0;
				scanner.nextLine();
			}
			switch(choice){
				//benchmark branch
				case 1:
					PrintWriter writer = null;

					try{
						writer = new PrintWriter(new File("Benchmark.csv"));
					}catch(Exception e){
						System.out.println("Could not create file for result!");
						break;
					}
					//write results to console and file
					writer.write("Size (Row/Column);Duration sequential (in ms)");
					for(int tc = MIN_THREADS; tc <= max_threads; tc += THREAD_INC){
						writer.write(";Duration " + tc + " Threads (in ms)");
					}
					writer.write("\n");
					for(int size = min_rc; size <= max_rc; size += 100){
						matrixA = Matrix.createRandomMatrix(size);
						matrixB = Matrix.createRandomMatrix(size);
						long timeStart = System.currentTimeMillis();
						Matrix.multiply(matrixA, matrixB);
						long timeEnd = System.currentTimeMillis();
						long duration = timeEnd - timeStart;
						
						System.out.print("Size: " + size + "\tDuration (sequential): " + duration);
						writer.write(size + ";" + duration);
						
						for(int tc = MIN_THREADS; tc <= max_threads; tc += THREAD_INC){
							timeStart = System.currentTimeMillis();
							//TODO: es = Executors.newCachedThreadPool();
							es = Executors.newFixedThreadPool(tc);
							Matrix.multiplyParallel(matrixA, matrixB, es);
							try {
								es.awaitTermination(7, TimeUnit.DAYS);
							} catch (InterruptedException e) {
								e.printStackTrace();
							}
							timeEnd = System.currentTimeMillis();
							duration = timeEnd - timeStart;
							System.out.print("\tDuration ("+ tc + " Threads): " + duration + " ms");
							writer.write(";" + duration);
						}
						writer.write("\n");
						System.out.println();
					}
					writer.flush();
					writer.close();
					break;
				//calculation branch
				case 2:
					//ask user for size of matrices and if he wants to create values randomly or not
					System.out.print("Size of Matrix: ");
					int size;
					try{
						size = scanner.nextInt();
					} catch(Exception e){
						size = 1;
						scanner.nextLine();
					}
					System.out.print("Create random values (j/n)? Answer: ");
					//create 2 random matrices
					String random;
					try{
						random = scanner.next();
					} catch(Exception e){
						random ="";
					}
					if(random.compareTo("j") == 0){
						matrixA = Matrix.createRandomMatrix(size);
						matrixB = Matrix.createRandomMatrix(size);
						
						
						if(matrixA.getSize() <= max_print_size){
							System.out.println("\nFirst Matrix:");
							matrixA.print();
						}
						
						
						if(matrixB.getSize() <= max_print_size){
							System.out.println("\nSecond Matrix:");
							matrixB.print();
						}
						
					//create to 2 matrices and ask user for values
					} else{
						matrixA = new Matrix(size);
						matrixB = new Matrix(size);
						System.out.println("Please insert values for the first matrix.");
						matrixA.setValues(scanner);
						System.out.println("Please insert values for the second matrix.");
						matrixB.setValues(scanner);
					}
					//print result of sequential calculation to console and the required time 
					System.out.println("\nResult (sequential):");
					long timeStart = System.nanoTime();
					Matrix matrixC = Matrix.multiply(matrixA, matrixB);
					long timeEnd = System.nanoTime();
					
					if(matrixC.getSize() <= max_print_size){
						matrixC.print();
					}
		
					System.out.println("Duration: " + (timeEnd - timeStart) + " ns.");
					
					//print result of sequential calculation to console and the required time 
					System.out.println("\nResult (" + max_threads + " Threads): ");
					timeStart = System.nanoTime();
					//TODO: es = Executors.newCachedThreadPool();
					es = Executors.newFixedThreadPool(max_threads);
					matrixC = Matrix.multiplyParallel(matrixA, matrixB, es);
					//wait until all threads are finished
					try {
						es.awaitTermination(7, TimeUnit.DAYS);
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
					timeEnd = System.nanoTime();
					
					if(matrixC.getSize() <= max_print_size)
						matrixC.print();
					
					System.out.println("Duration: " + (timeEnd - timeStart) + " ns.");
					break;
				case 3:
					do{
						System.out.print(
								  "\n----------------------------------------------------"
								+ "\n1 - Maximum number of Threads (" + max_threads + " Threads)"
								+ "\n2 - Calculation: Maximum size of printable matrix (" + max_print_size + ")" 
								+ "\n3 - Benchmark: Minimum number of columns/rows (" + min_rc + ")"
								+ "\n4 - Benchmark: Maximum number of columns/rows (" + max_rc + ")"
								+ "\n5 - Back"
								+ "\n----------------------------------------------------"
								+ "\nOption: ");
						try{
							choice = scanner.nextInt();
						}catch(Exception e){
							choice = 0;
						}
						switch(choice){
							case 1:
								System.out.print("Number of maximum Threads: ");
								try{
									size = scanner.nextInt();
									if(size >= MIN_THREADS){
										max_threads = size;
									}else{
										System.out.println("Invalid value!");
									}
								}catch(Exception e){
									scanner.nextLine();
								}
								break;
							case 2:
								System.out.print("Maximum size of printable Matrix: ");
								try{
									size = scanner.nextInt();
									if(size >= 1){
										max_print_size = size;
									}else{
										System.out.println("Invalid value!");
									}
								}catch(Exception e){
									scanner.nextLine();
								}
								break;
							case 3:
								System.out.print("Minimum number of colums/rows (has to be a multiple of 100): ");
								try{
									size = scanner.nextInt();
									if(size > 0){
										size /= 100;
										size = (size == 0) ? 100 : size * 100;
										min_rc = (size > max_rc) ? max_rc : size;
									}else{
										System.out.println("Invalid value!");
									}
								}catch(Exception e){
									scanner.nextLine();
								}
								break;
							case 4:
								System.out.print("Maximum number of colums/rows (has to be a multiple of 100): ");
								try{
									size = scanner.nextInt();
									if(size > 0){
										size /= 100;
										size = (size == 0) ? 100 : size * 100;
										max_rc = (size < min_rc) ? min_rc : size;
									}else{
										System.out.println("Invalid value!");
									}
								}catch(Exception e){
									scanner.nextLine();
								}
								break;
						}
					
					}while(choice != 5);
					choice = 0;
					break;
			}
			//exit if user chooses option 3
		}while(choice != 4);
		System.out.println("\nGoodbye!");
	}
	
	/**
	 * Creates a new Matrix instance.
	 * 
	 * @param size number of columns and rows
	 */
	public Matrix(int size){
		cell = new double[size][size];
	}
	
	/**
	 * Returns number of columns/rows.
	 * 
	 * @return
	 */
	public int getSize(){
		return cell.length;
	}
	
	/**
	 * Multiplies both matrices and returns result.
	 * 
	 * @param matrixA first matrix
	 * @param matrixB second matrix
	 * @return result of multiplication
	 */
	public static Matrix multiply(Matrix matrixA, Matrix matrixB){
		Matrix matrixC = new Matrix(matrixA.getSize());
		for(int r = 0; r < matrixC.getSize(); r++){
			for(int c = 0; c < matrixC.getSize(); c++){
				matrixC.cell[r][c] = 0;
				for(int add = 0; add < matrixC.getSize(); add++){
					matrixC.cell[r][c] += matrixA.cell[r][add] * matrixB.cell[add][c];	
				}
			}
		}
		return matrixC;
	}
	
	public static Matrix multiplyParallel(Matrix matrixA, Matrix matrixB, ExecutorService es){
		Matrix matrixC = new Matrix(matrixA.getSize());
		for(int c = 0; c < matrixC.getSize(); c++){
			es.execute(new Thread(new MatrixColumnMultiply(matrixA, matrixB, matrixC, c)));
		}
		es.shutdown();
		return matrixC;
	}
	
	/**
	 * Prints matrix to console.
	 */
	public void print(){
		for(int r = 0; r < getSize(); r++){
			for(int c = 0; c < getSize(); c++){
				System.out.print(cell[r][c] + "\t");
			}
			System.out.println();
		}
	}
	
	/**
	 * Creates a new scanner instance and
	 * asks user for values for the matrix.
	 */
	public void setValues(){
		setValues(new Scanner(System.in));
	}
	
	/**
	 * Asks user for values for the matrix.
	 * 
	 * @param scanner Scanner instance which shall be used for user input 
	 */
	public void setValues(Scanner scanner){
		for(int r = 0; r < getSize(); r++){
			for(int c = 0; c < getSize(); c++){
				System.out.print("("+ r + ", " + c + "): ");
				try{
					setCell(r, c, scanner.nextDouble());
				}catch(Exception e){
					scanner.nextLine();
					c--;
				}
				
			}
		}
	}
	
	/**
	 * Creates a new Matrix instance with random values.
	 * 
	 * @param size size of matrix
	 * @return create Matrix instance
	 */
	public static Matrix createRandomMatrix(int size){
		Matrix matrix = new Matrix(size);
		Random random = new Random();
		for(int r = 0; r < size; r++){
			for(int c = 0; c < size; c++){
				matrix.cell[r][c] = random.nextDouble();
			}
		}
		return matrix;
	}
	
	/**
	 * Inserts value into cell.
	 * 
	 * @param r number of row
	 * @param c number of column
	 * @param value value which shall be inserted
	 */
	public void setCell(int r, int c, double value){
		cell[r][c] = value;
	}
	
	/**
	 * Returns value of cell.
	 * 
	 * @param r number of row
	 * @param c number of column
	 * @return value of cell
	 */
	public double getCell(int r, int c){
		return cell[r][c];
	}
}
