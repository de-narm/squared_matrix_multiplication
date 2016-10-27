
public class MatrixColumnMultiply implements Runnable{
	
	private int column;
	private Matrix matrixA, matrixB, matrixC;
	
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
