#include <iostream>
#include <memory>

#define RESET_COLOR "\033[0m"
#define GREEN  "\033[32m"

using namespace std;

class Polynomial;

class Term{
	friend Polynomial;
private:
	float coef = 0.0f;
	int exp = 0;
};


class Polynomial {
public:
	Polynomial();
	Polynomial(int degree);
	Polynomial Add(Polynomial b);
	Polynomial Substract(Polynomial b);
	Polynomial Multiply(Polynomial b);
	void NewTerm(const float theCoeff, const int theExp);
	int Display();
	int GetData();
private:
	Term *termArray; // array of nonzero terms
	int capacity = 0; //size of termArray
	int terms = 0; //number of nonzero terms
};

Polynomial::Polynomial() {}

Polynomial::Polynomial(int degree) {
	this->termArray = new Term[degree+1];
	this->capacity = degree + 1;
}

int Polynomial::Display() {
	int i = 0;
	for (i = 0; i < terms; ++i) {
		cout << termArray[i].coef << " x^" << termArray[i].exp ;
		if (i < terms-1) cout << " + ";
	}

	cout << "\n";

	return 0;
}


int Polynomial::GetData() {
	cout << "Enter Degree of Polynomial: ";
	int degree;
	cin >> degree;

	int coeff, expo;
	this->termArray = new Term[degree+1];
	for (int i = degree; i >= 0; i--) {
		cout << "Enter coefficient of " << " x^" << i <<":";
		cin >> coeff;
		expo = i;
		NewTerm(coeff, expo);
	}

	return 0;
}

void Polynomial::NewTerm(const float theCoeff, const int theExp){
	if (terms == capacity){
		if (capacity == 0) capacity = 1;
		else capacity *= 2;
		Term *temp = new Term[capacity];

		for (int i = 0; i < terms; ++i) {
			temp[i].coef = termArray[i].coef;
			temp[i].exp = termArray[i].exp;
		}

		delete[] termArray;
		termArray = temp;
	}
	termArray[terms].coef = theCoeff;
	termArray[terms++].exp = theExp;
}


Polynomial Polynomial::Add(Polynomial b){
	Polynomial result;
	int aPos = 0, bPos = 0;
	while ((aPos < terms) && (bPos < b.terms))
		if ((termArray[aPos].exp == b.termArray[bPos].exp)){
			float t = termArray[aPos].coef + b.termArray[bPos].coef;
			if (t) result.NewTerm(t, termArray[aPos].exp);
			aPos++; bPos++;
		}
		else if ((termArray[aPos].exp < b.termArray[bPos].exp)){
			result.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
			bPos++;
		}
		else{
			result.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
			aPos++;
		}

	for (; aPos < terms; aPos++)
		result.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
	for (; bPos < b.terms; bPos++)
		result.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);

	return result;
}


Polynomial Polynomial::Substract(Polynomial b) {
	Polynomial result;
	int aPos = 0, bPos = 0;
	while ((aPos < terms) && (bPos < b.terms))
		if ((termArray[aPos].exp == b.termArray[bPos].exp)) {
			float t = termArray[aPos].coef - b.termArray[bPos].coef;
			if (t) result.NewTerm(t, termArray[aPos].exp);
			aPos++; bPos++;
		}
		else if ((termArray[aPos].exp < b.termArray[bPos].exp)) {
			result.NewTerm(-b.termArray[bPos].coef, b.termArray[bPos].exp);
			bPos++;
		}
		else {
			result.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
			aPos++;
		}

		for (; aPos < terms; aPos++)
			result.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
		for (; bPos < b.terms; bPos++)
			result.NewTerm(-b.termArray[bPos].coef, b.termArray[bPos].exp);

		return result;
}

Polynomial Polynomial::Multiply(Polynomial b) {
	Polynomial result;
	int len = b.termArray[0].exp + this->termArray[0].exp + 1;
	// restore coeff, and the index of the array stands for exp value.
	//eg:coeffArr[2] = 1.9, it means coeff = 1.9, exp = 2;
	float *coeffArr = new float[len];
	//init the coeffArr array
	for (int i = 0; i < len; ++i) {
		coeffArr[i] = 0.0f;
	}
	for (int i = 0; i < terms; ++i) {
		for (int j = 0; j < b.terms; ++j) {
			float newCoeff = this->termArray[i].coef * b.termArray[j].coef;
			int newExp = this->termArray[i].exp + b.termArray[j].exp;
			coeffArr[newExp] += newCoeff;
		}
	}
	//build array terms 
	for (int i = len - 1; i >= 0; --i) {
		if (coeffArr[i] != 0.0f) {
			result.NewTerm(coeffArr[i], i);
		}
	}
	return result;
}

int main_polynomial0() {

	/*Polynomial p(2);
	p.NewTerm(5, 2);
	p.NewTerm(5, 1);
	p.NewTerm(5, 0);
	p.Display();

	Polynomial p2(2);
	p2.NewTerm(3, 2);
	p2.NewTerm(3, 1);
	p2.NewTerm(3, 0);
	p2.Display();

	Polynomial result = p.Add(p2);
	result.Display();*/

	int choice;
	
	Polynomial P1, P2, P3;
	cout << GREEN << "Instruction:- \nExample:-\nP(x)=5x^3+3x^1\nEnter the Polynomial like\nP(x)=5x^3+0x^2+3x^1+0x^0\n" << RESET_COLOR;
	cout << "Enter Polynomial1:-" << endl;
	P1.GetData();
	cout << "Enter Polynomial2:-" << endl;
	P2.GetData();

	while (1) {
		cout << "\n****** Menu Selection ******" << endl;
		cout << "1: Addition\n2: Substraction\n3: Multiplication\n0: Exit" << endl;
		cout << "Enter ypur choice:";
		cin >> choice;
		switch (choice) {
		case 1:
			cout << GREEN << "\n--------------- Addition ---------------\n";
			cout << "Polynomial1:";
			P1.Display();
			cout << "Polynomial2:";
			P2.Display();
			cout << "\n ---------------result---------------\n";
			P3 = P1.Add(P2);
			P3.Display();
			cout << "----------------------------------------\n" << RESET_COLOR;
			break;
		case 2:
			cout << GREEN << "\n------------- Substraction -------------\n";
			cout << "Polynomial1:";
			P1.Display();
			cout << "Polynomial2:";
			P2.Display();
			cout << "\n ---------------result---------------\n";
			P3 = P1.Substract(P2);
			
			P3.Display();
			cout << "----------------------------------------\n" << RESET_COLOR;
			break;
		case 3:
			cout << GREEN << "\n----------- Multiplication -------------\n";
			cout << "Polynomial1:";
			P1.Display();
			cout << "Polynomial2:";
			P2.Display();
			cout << "\n ---------------result---------------\n";
			P3 = P1.Multiply(P2);
			P3.Display();
			cout << "----------------------------------------\n" << RESET_COLOR;
			break;
		case 0:
			cout << "Good Bye...!!!" << endl;
			exit(0);
		}
	}
	return 0;
}
