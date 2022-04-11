
#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;
bool isvalidcc(const string& pid);
int sumEven(int integerValue);
bool reversedVector(vector<char> vec);


int main()
{
	//
	// PLEASE DO NOT CHANGE function main
	//
	vector<string> cardnumbers = {
		 "371449635398431", "4444444444444448", "4444424444444440", "4110144110144115",
		"4114360123456785", "4061724061724061", "5500005555555559", "5115915115915118",
		"5555555555555557", "6011016011016011", "372449635398431", "4444544444444448",
		"4444434444444440", "4110145110144115", "4124360123456785", "4062724061724061",
		"5501005555555559", "5125915115915118", "5556555555555557", "6011116011016011",
		 "372449635397431", "4444544444444448", "4444434444544440", "4110145110184115",
		"4124360123457785", "4062724061724061", "5541005555555559", "5125115115915118",
		"5556551555555557", "6011316011016011"
	};

	int i;
	vector<string>::iterator itr;

	for (i = 1, itr = cardnumbers.begin(); itr != cardnumbers.end(); ++itr, i++) {
		cout << setw(2) << i << " "
			<< setw(17) << *itr
			<< ((isvalidcc(*itr))? " is valid" : " is not valid") << endl;
	}

	return 0;
}


bool isvalidcc(const string& pid)
{
	vector<char> vec;
	for (unsigned i = 0; i < pid.length(); i++) {
		vec.push_back(pid.at(i));
	}
	bool trueOrFalse =  reversedVector(vec);

	return trueOrFalse;
}

bool reversedVector(vector<char> vec){
	int sum = 0;
	int even = 0;
	int odd = 0;
	int counter = 1;
	int number1, integerValue;
	stringstream stream;
	string str;
	for (vector<char>::reverse_iterator itr = vec.rbegin(); itr != vec.rend(); itr++) {
		
		integerValue = *itr - '0';
		//cout << integerValue << " ";
		if ((counter % 2) == 0) {
			even = even + sumEven(integerValue);
		}else {
			odd = odd + integerValue;
		}
		counter++;
	
	}
	sum = even + odd;
	// cout << sum << " " << even << " " << odd << "   " <<endl;

	if (sum % 10 == 0) {
		return true;
	}
	else {
		return false;
	}
}
int sumEven(int integerValue) {
	int evenSum = 0;
	int number1 = 0;
	stringstream stream;
	string str;
	
	number1 = integerValue * 2;

	if (number1 > 9) {
		stream << number1;
		stream >> str;
		number1 = (str.at(0)-'0') + (str.at(1) - '0');
	}

	evenSum = evenSum + number1;

	return evenSum;
}

