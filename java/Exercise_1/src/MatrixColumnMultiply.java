
/**
 * Class to parallelize the Matrix multiplication.
 * 
 * @author Matthias Nickel
 */
public class MatrixColumnMultiply implements Runnable{
	
	/**
	 * index of column
	 */
	private int column;
	/**
	 * Matrices which shall be multiplied C = A * B
	 */
	private Matrix matrixA, matrixB, matrixC;
	
	/**
	 * Standard constructor.
	 * 
	 * @param matrixA First matrix which shall be multiplied.
	 * @param matrixB Second matrix which shall be multiplied.
	 * @param matrixC Result matrix of multiplication of matrix A and B.
	 * @param column Index of column.
	 */
	public MatrixColumnMultiply(Matrix matrixA, Matrix matrixB, Matrix matrixC, int column){
		this.column = column;
		this.matrixA = matrixA;
		this.matrixB = matrixB;
		this.matrixC = matrixC;
	}

	@Override
	public void run() {
		for(int r = 0; r < matrixC.getSize(); r++){
			matrixC.setCell(r, column, 0);
			for(int add = 0; add < matrixC.getSize(); add++){
				matrixC.setCell(r, column, 
						matrixC.getCell(r, column) + matrixA.getCell(r, add) * matrixB.getCell(add, column));
			}
		}
	}
}
