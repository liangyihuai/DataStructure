#include <iostream>

using namespace std;

class String {

public:
	String(char * init, int m);

	~String() {
		cout << "delete = " << this->str << endl;
		if (this->f) {
			delete[] this->f;
		}
		else {
			cout << "-----------ll-------------" << endl;
		}
	}

	//the number of characters in this string
	int Length()const;

	int Find(const String &pat);

	int FastFind(const String &pat);

	bool isEmpty() const {
		return (!this->str) || (str == "");
	}

private:
	char *str = nullptr;
	int len;
	int *f = nullptr;

	void FailureFunction();
};

String::String(char * init, int m) {
	if (init == nullptr || m < 0) throw std::invalid_argument("Invalid args.");

	this->str = init;
	this->len = m;
	this->f = new int[m + 1];
	FailureFunction();
}

int String::Length() const {
	return this->len;
}

/*
Return -1 if pat does not occur in *this
otherwise return the first position in *this, where pat begins.
*/
int String::Find(const String &pat) {
	int len = pat.Length();
	//check for match beginning at str[start]
	for (int start = 0; start <= Length() - pat.Length(); start++) {
		for (int j = 0; j < pat.Length() && str[start + j] == pat.str[j]; j++) {
			if (j == pat.Length() - 1)return start;//match found
		}
	}
	//pat is empty or does not occur in s
	return -1;
}

/*
determine if pat is a substring of s
*/
int String::FastFind(const String &pat) {
	if (pat.isEmpty()) return -1;

	int PosP = 0, PosS = 0;
	int LengthP = pat.Length(), LengthS = Length();
	while ((PosP < LengthP) && (PosS < LengthS)) {
		if (pat.str[PosP] == str[PosS]) {
			PosP++; PosS++;
		}
		else {
			if (PosP == 0) PosS++;
			else PosP = pat.f[PosP - 1] + 1;
		}
	}
	if (PosP < LengthP)return -1;
	else return PosS - LengthP;

}

/*
compute the failure function for the pattern *this
*/
void String::FailureFunction() {
	int lenghtP = Length();
	f[0] = -1;
	for (int j = 1; j < lenghtP; j++) {
		int i = f[j - 1];
		while ((*(str + j) != *(str + i + 1)) && (i >= 0)) i = f[i];
		if (*(str + j) == *(str + i + 1)) {
			f[j] = i + 1;
		}
		else {
			f[j] = -1;
		}
	}
}


int main() {
	cout << "---- Find function test ---" << endl;
	String s("Hello, today is a sunny day!", 28);
	String s2("", 0);
	String pat("sun", 3);
	String pat2("", 0);
	String pat3("days", 4);
	String pat4("day", 3);

	cout << "start index1 = " << s.Find(pat) << endl;
	cout << "start index2 = " << s.Find(pat2) << endl;
	cout << "start index3 = " << s.Find(pat3) << endl;
	cout << "start index4 = " << s.Find(pat4) << endl;
	cout << "start index4 = " << s2.Find(pat) << endl;

	cout << "---- FastFind function test ---" << endl;
	cout << s.FastFind(pat) << endl;
	cout << s.FastFind(pat2) << endl;
	cout << s.FastFind(pat3) << endl;
	cout << s.FastFind(pat4) << endl;
	cout << s2.FastFind(pat) << endl;


	system("pause");
	return 0;
}