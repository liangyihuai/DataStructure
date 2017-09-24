#include <iostream>
using namespace std;

class Matrix {
public:
	Matrix(int row, int col);
	int GetData();
	Matrix Transpose();
	void Display();
	//Matrix Add(Matrix b);
	Matrix Multiply(Matrix b);
	int CompareRowCol(Matrix b);
private:
	int rows, cols;
	//int Term[rows][cols];
	int *Term;//the add 2.6ress of a[i][j] = 0 + i * cols + j => Fig2.6
};

Matrix::Matrix(int row, int col) : rows(row), cols(col)
{
	Term = new int[rows * cols];
}

int Matrix::GetData() {
	int input_value;

	for (int j = 0; j < rows * cols; j++)
	{
		cout << "term value = ";
		cin >> input_value;
		cout << " " << endl;
		Term[j] = input_value;
	}
	return 0;
}

Matrix Matrix::Transpose() {
	Matrix b(cols, rows);
	//...
	// 학생들이 code 작성
	for (int i = 0; i < cols; ++i) {
		for (int j = 0; j < rows; ++j) {
			int value = Term[cols * j + i];
			b.Term[rows * i + j] = value;
		}
	}
	return b;
}

Matrix Matrix::Multiply(Matrix b) {
	if (this->cols != b.rows) {
		throw "Incompatible matrices";
	}
	Matrix result(this->rows, b.cols);
	Matrix bXpose = b.Transpose();

	int index = 0;
	
	for (int i = 0; i < this->rows; ++i) {//the rows of first matrix
		for (int k = 0; k < bXpose.rows; ++k) {//the rows of second matrix
			int dotMult = 0;
			for (int j = 0; j < this->cols; ++j) {//the cols of first and second matrix
				int value_matrix1 = this->Term[this->cols * i + j];//the item of first matrix
				int value_matrix2 = bXpose.Term[bXpose.cols * k + j];//the item of second matrix
				dotMult += value_matrix1 * value_matrix2; //dot multiple value
			}
			result.Term[index++] = dotMult;
		}
	}
	return result;
}

int Matrix::CompareRowCol(Matrix b) {
	if (cols != b.rows) return 1;
	else return 0;
}

void  Matrix::Display() {
	for (int j = 0; j < rows; ++j) {
		for (int i = 0; i < cols; ++i) {
			cout << Term[cols * j + i] << " ";
		}
		cout << endl;
	}
}

int main_Matrix()
{
	Matrix a(2, 3);
	Matrix b(3, 2);
	Matrix c(2, 2);

	cout << "Enter first matrix: " << endl;
	a.GetData();
	a.Display();

	cout << "Transpose Matrix: " << endl;
	Matrix transposeResult = a.Transpose();
	transposeResult.Display();

	cout << "Enter second matrix: " << endl;
	b.GetData();

	cout << "Display first matrix: " << endl;
	a.Display();
	cout << "Display second matrix: " << endl;
	b.Display();

	Matrix d(4, 5);
	d = b.Transpose();
	cout << "Transpose() of Matrix b" << endl;
	d.Display();

	/* If colum of first matrix in not equal to row of second matrix, asking user to enter the size of matrix again. */
	if (a.CompareRowCol(b))
	{
		cout << "Error! column of first matrix not equal to row of second.";
		cout << "Enter rows and columns for first matrix: ";
	}


	c = a.Multiply(b);
	cout << "Multiply of Matrix a,b" << endl;
	c.Display();


	system("pause");
	return 0;
}
