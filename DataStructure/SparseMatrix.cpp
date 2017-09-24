#include <iostream>
#include <memory>
#include <stdlib.h>

using namespace std;

class SparseMatrix;//forward declaration

class MatrixTerm
{
	friend class SparseMatrix;
private:
	int row, col, value;
};


class SparseMatrix
{
public:
	SparseMatrix();
	SparseMatrix(int r, int c, int t);
	SparseMatrix Transpose();
	int GetData(int numTerms);
	SparseMatrix FastTranspose();
	SparseMatrix Add(SparseMatrix b);
	SparseMatrix Sub(SparseMatrix b);
	void StoreSum(const int sum, const int r, const int c);
	void ChangeSize1D(const int newSize);
	SparseMatrix Multiply(SparseMatrix b);
	int MergeSum(SparseMatrix b);//merge sum of a.row with b.col
	void Display();

private:
	int rows, cols, terms, capacity;
	MatrixTerm *smArray;
};

SparseMatrix::SparseMatrix()
{
	cols = 3;
	rows = 3;
	terms = 5;
	smArray = new MatrixTerm[terms];
}

//rows num, cols num, element num
SparseMatrix::SparseMatrix(int r, int c, int t)
{
	cols = c;
	rows = r;
	terms = t;
	smArray = new MatrixTerm[t];
}

int SparseMatrix::GetData(int numTerms) {
	int input_row;
	int input_col;
	int input_value;
	cout << "rows = " << rows << "  cols = " << cols << " terms = " << terms << endl;

	for (int j = 0; j < numTerms; j++)
	{
		cout << endl << "row = ";
		cin >> input_row;
		cout << "  col = ";
		cin >> input_col;
		cout << "  value = ";
		cin >> input_value;
		smArray[j].row = input_row;
		smArray[j].col = input_col;
		smArray[j].value = input_value;
	}
	return 0;
}
SparseMatrix SparseMatrix::Transpose()
{
	SparseMatrix b(cols, rows, terms);
	if (terms > 0){
		int currentB = 0;
		for (int c = 0; c<cols; c++)
			for (int i = 0; i<terms; i++)
				if (smArray[i].col == c){
					b.smArray[currentB].row = c;
					b.smArray[currentB].col = smArray[i].row;
					b.smArray[currentB++].value = smArray[i].value;
				}
	}
	return b;
}

SparseMatrix SparseMatrix::FastTranspose()
{
	SparseMatrix b(cols, rows, terms);
	if (terms > 0)
	{
		//page 102 coding
	}
	return b;
}
void SparseMatrix::ChangeSize1D(const int newSize)
{
	if (newSize < terms) throw "New size must be >= number of terms";
	MatrixTerm *temp = new MatrixTerm[newSize];
	
	//copy(smArray, smArray + terms, temp);

	memcpy(temp, smArray,terms);
	delete[] smArray;
	smArray = temp;
	capacity = newSize;
}

void SparseMatrix::StoreSum(const int sum, const int r, const int c)
{
	if (sum != 0)
	{
		if (terms = capacity)
			ChangeSize1D(2 * capacity);
		smArray[terms].row = r;
		smArray[terms].col = c;
		smArray[terms++].value = sum;
	}
}

int SparseMatrix::MergeSum(SparseMatrix b)//merge sum of a.row with b.col
{
	int sumTerms = 0;
	if (cols != b.rows) throw "Incompatible matrices";
	SparseMatrix bXpose = b.Transpose();
	// coding for merging of terms for (i, j)
	return sumTerms;
}

void SparseMatrix::Display()
{
	cout << "row  col  value" << endl;
	cout << "---------------" << endl;
	for (int i = 0; i < terms; i++)
		cout << smArray[i].row << "   " << smArray[i].col << "   " << smArray[i].value << endl;

}
SparseMatrix SparseMatrix::Add(SparseMatrix b)
{
	SparseMatrix result;
	result.rows = rows;
	result.cols = cols;
	result.terms = terms;
	if (terms>0)
	{

	}
	return result;
}



SparseMatrix SparseMatrix::Multiply(SparseMatrix b)
{
	if (cols != b.rows) throw "Incompatible matrices";
	SparseMatrix bXpose = b.Transpose();
	SparseMatrix d(rows, b.cols, 0);
	int currRowIndex = 0, currRowBegin = 0, currRowA = smArray[0].row;
	if (terms == capacity) ChangeSize1D(terms + 1);
	bXpose.ChangeSize1D(bXpose.terms + 1);
	smArray[terms].row = rows;
	bXpose.smArray[b.terms].row = b.cols;
	bXpose.smArray[b.terms].col = -1;

	int sum = 0;

	while (currRowIndex < terms)
	{
		int currColB = bXpose.smArray[0].row;
		int currColIndex = 0;
		while (currColIndex <= b.terms)
		{
			if (smArray[currRowIndex].row != currRowA)
			{
				d.StoreSum(sum, currRowA, currColB);
				sum = 0;
				currRowIndex = currRowBegin;
				while (bXpose.smArray[currColIndex].row == currColB)
					currColIndex++;
				currColB = bXpose.smArray[currColIndex].row;;
			}
			else if (bXpose.smArray[currColIndex].row != currColB)
			{
				d.StoreSum(sum, currRowA, currColB);
				sum = 0;
				currRowIndex = currRowBegin;
				currColB = bXpose.smArray[currColIndex].row;
			}
			else
				if (smArray[currRowIndex].col < bXpose.smArray[currColIndex].col)
					currRowIndex++;
				else if (smArray[currRowIndex].col == bXpose.smArray[currColIndex].col)
				{
					sum += smArray[currRowIndex].value * bXpose.smArray[currColIndex].value;
					currRowIndex++; currColIndex++;
				}
				else currColIndex++;
		}
		while (smArray[currRowIndex].row == currRowA)
			currRowIndex++;
		currRowBegin = currRowIndex;
		currRowA = smArray[currRowIndex].row;
	}
	return d;
}


int main_SparseMatrix()
{

	SparseMatrix a(5, 7, 5);
	SparseMatrix b(7, 9, 5);
	SparseMatrix c(5, 9, 5);
	SparseMatrix a2(5, 7, 5);
	SparseMatrix a3(5, 7, 5);
	SparseMatrix d(9, 7, 5);

	cout << "Enter first matrix: " << endl;
	a.GetData(5);
	cout << "Enter second matrix: " << endl;
	b.GetData(5);
	cout << "Display first matrix: " << endl;
	a.Display();
	cout << "Display second matrix: " << endl;
	b.Display();


	d = b.Transpose();
	cout << "Transpose() of Matrix b" << endl;
	d.Display();


	/* If colum of first matrix in not equal to row of second matrix, asking user to enter the size of matrix again. */
	/*if (a.CompareRowCol(b))
	{
	cout << "Error! column of first matrix not equal to row of second.";
	cout << "Enter rows and columns for first matrix: ";
	}
	*/


	char select;
	cout << endl << "Select command:";
	cin >> select;
	while (select != 'Q')
	{
		cout << " 연산의 종류를 선택하세요. >> ";
		cin >> select;
		switch (select)
		{
		case 'P':
			a.Display();
			b.Display();
			break;
		case 'T':
			d = b.Transpose();
			d.Display();
			break;
		case 'M':
			c = a.Multiply(b);
			c.Display();
			break;
		case 'A':

			a3 = a.Add(a2);
			a3.Display();
			break;
		case 'Q' | 'q':
			cout << "Program TERMINATED" << endl;
			break;
		default:
			cout << "WRONG INPUT  " << endl;
			cout << "Re-Enter" << endl;
		}
	}
	system("pause");
	return 0;
}
