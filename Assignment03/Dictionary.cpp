#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <set>
using namespace std;

string searchForWord(string word, string search, bool& found);
vector<string> parse(const string& wordAndDefinition, char delimiter);
string toString(string word, string definition);
string parts(string definition);
void help();
void print(int counter, multiset<string> multi, string word, vector<string> modSearch);
void printDistinct(int size, vector<string> modSearch, set<string> newSet, string word );
void printReverse(int size, vector<string> modSearch, multiset<string>multi, string word);
vector<string> printError(vector<string> modSearch, const bool& partOfSpeech);

int main() {
	fstream ioFile;
	string line, next;
	vector<string> dictionary;
	string searchWord;
	vector<string> modSearch;
	vector<string> definitions;
	string search;

	bool partOfSpeech = false;;
	bool found = false;
	int count = 1;

	ioFile.open("./Data.CS.SFSU.txt", ios::in);
	cout << "<!>Enter the CORRECT data file path : ./Data.CS.SFSU.txt" << endl;
	cout << "! Loading data..." << endl;
	while (getline(ioFile, line)) {
		dictionary.push_back(line);
	}
	cout << "! Loading complete..." << endl;
	cout << "! Closing data file... ./Data.CS.SFSU.txt" << endl;
	ioFile.close();


	cout << "===== Dictionary 340 C++ ======" << endl;
	cout << "----- Keywords: " << dictionary.size() << endl;
	cout << "----- Defintions: " << " 61" << endl;							// Add parsed number of definitions
	while (true) {

		cout << "Search " << "[" << to_string(count) << "] : ";

		getline(cin, search);

		if (search == "!q") {

			break;
		}
		else if (search == "!help" || search == "") {

			help();
			count++;
			continue;
		}

		// to lower case of search to match the data from the .txt file 
		for (int i = 0; i < search.length(); i++) {
			search[i] = tolower(search[i]);

		}
		modSearch = parse(search, ' ');



		for (vector<string>::iterator itr = dictionary.begin(); itr != dictionary.end(); itr++) {
			found = false;
			//cout << *itr << endl;
			searchWord = searchForWord(*itr, modSearch[0], found);
			//cout << modSearch[0] << endl << endl;
			if (found) {
				break;
			}
		}
		if (!found) {

			cout << "\t|" << endl << "\t<NOT FOUND> To be considered for the next release. Thank you." << endl << "\t|" << endl;
			help();
			count++;
			continue;
		}
		if (modSearch.size() >= 2) {
			partOfSpeech = modSearch[1] == "noun" || modSearch[1] == "adverb" || modSearch[1] == "verb" ||
				modSearch[1] == "pronoun" || modSearch[1] == "adjective" ||
				modSearch[1] == "conjunction" || modSearch[1] == "interjection";
		}


		definitions = parse(searchWord, '|');
		(definitions[0])[0] = toupper((definitions[0])[0]);
		int counter = 0;
		string word;
		string part;
		multiset<string> multi;
		int firstLetterOfWord = 0;
		for (vector<string>::iterator itr = definitions.begin(); itr != definitions.end(); itr++) {
			// cout << *itr << endl;
			if (counter == 0) {
				word = *itr;
				counter++;
			}
			firstLetterOfWord = (*itr).find(' ', 2);
			if (firstLetterOfWord != string::npos) {
				(*itr)[firstLetterOfWord+6] = toupper(( * itr)[firstLetterOfWord+6]);
			}
			multi.insert(*itr);
		}
		counter = 0;
		while (true) {
			if (modSearch.size() == 1) {
				print(counter, multi, word, modSearch);
				break;
			}
			else if (modSearch.size() == 2) {
				if (partOfSpeech || modSearch[1] == "distinct" || modSearch[1] == "reverse") {
					print(counter, multi, word, modSearch);
					break;
				}

				else {
					modSearch = printError(modSearch, partOfSpeech);
					//modSearch.erase(find(modSearch.begin(), modSearch.end(), modSearch[1]));
					continue;
				}

			}
			else if (modSearch.size() == 3) {
				if ((partOfSpeech && modSearch[2] == "distinct") || (partOfSpeech && modSearch[2] == "reverse") || (modSearch[1] == "distinct" && modSearch[2] == "reverse")) {
					print(counter, multi, word, modSearch);
					break;
				}

				else {
					modSearch = printError(modSearch, partOfSpeech);
					//modSearch.erase(find(modSearch.begin(), modSearch.end(), modSearch[2]));
					continue;
				}


			}
			else if (modSearch.size() == 4) {
				if ((partOfSpeech && modSearch[2] == "distinct" && modSearch[3] == "reverse")) {
					print(counter, multi, word, modSearch);
					break;
				}

				else {
					modSearch = printError(modSearch, partOfSpeech);
					//modSearch.erase(find(modSearch.begin(), modSearch.end(), modSearch[3]));
					continue;
				}

			}
			else {
				help();
				break;
			}
		}
	
		count++;
	}


	cout << "-----THANK YOU-----";
	return 0;
}

string searchForWord(string line, string search, bool &found) {
	string word = "";
	string delimiter = "|";
	string temp = " ";
	auto start = 0;
	auto end = line.find(delimiter, start);
	unsigned pos = 0;
	while (end != std::string::npos)
	{
		if (line.substr(start, end - start) == search) {
			word = line;
			found = true;
			break;
		}
		else {
			//cout << "word not found";
			break;
		}
	}
	return word;
}
vector<string> parse(const string& wordAndDefinition, char delimiter) {
	vector<string> parsed;
	stringstream ss(wordAndDefinition);
	string temp = "";
	while (getline(ss, temp, delimiter)) {
		parsed.push_back(temp);
	}
	
	return parsed;
}

string toString(string word, string definition) {
	size_t pos = definition.find("-=>> ");
	if (pos > 10000) {
		return definition;
	}
	if (pos != string::npos) {
		definition.erase(pos, 5);
	}
	definition.insert(0, 1, '[');

	pos = definition.find(' ');
	if (pos != string::npos) {
		definition.insert(pos, 1, ']');
		definition.insert(pos+1, 1, ' ');
		definition.insert(pos+2, 1, ':');
	}
	
	else {
		definition.erase(0);
	}
	if (word.length() > 3 ) {
		if (word.substr(0, 3) == "Csc") {
			for (int i = 0; i < word.substr(0, 3).length(); i++) {
				word[i] = toupper(word[i]);
			}
		}
	}
	cout << "\t" << word << " " << definition << endl;

	return definition;
}

string parts(string definition) {
	string subString;
	size_t pos = definition.find(' ');
	if (pos != string::npos) {
		subString = definition.substr(0,pos);
	}
	//cout << subString << " this is the substring of parts";
	return subString;
}

void help() {
	cout << "\t|" << endl;
	cout << "\tPARAMETER HOW-TO, please enter:" << endl << "\t1. A search key -then 2. An optional part of speech -then"
		<< endl << "\t3. an optional 'distinct' -then 4. An optional 'reverse'" << endl;
	cout << "\t|" << endl;
}

void print(int counter, multiset<string> multi, string word, vector<string> modSearch) {
	int size = modSearch.size();
	string part = "";
	bool partOfSpeech = false;
	bool foundPartOfSpeech = false;
	size_t found = 0;
	set<string> newSet(multi.begin(), multi.end());
	if (size >= 2) {
		partOfSpeech = modSearch[1] == "noun" || modSearch[1] == "adverb" || modSearch[1] == "verb" ||
			modSearch[1] == "pronoun" || modSearch[1] == "adjective" ||
			modSearch[1] == "conjunction" || modSearch[1] == "interjection";
	}
	cout << "\t|" << endl;
	for (multiset<string>::iterator itr = multi.begin(); itr != multi.end(); itr++) {
		if (size >= 2 && partOfSpeech) {
			found = (*itr).find(modSearch[1]);
			if (found < 10000 && partOfSpeech) {
				foundPartOfSpeech = true;
			
			}
		}
		
		part = parts(*itr);
		

		if (counter == 0) {
			counter++;
			continue;
		}
		if (size == 1) {
			toString(word, *itr);
				continue;
		
			
		}
		if (size == 2 && partOfSpeech) {

			if (part == modSearch[1]) {
				toString(word, *itr);
				continue;
				
			}
		}
		
		if (size == 2 && modSearch[1] == "distinct") {
			printDistinct(size, modSearch, newSet, word);
			break;
		}
		else if (modSearch[1] == "reverse") {
			printReverse(size, modSearch, multi, word);
			break;
		}
		if (size == 3) {
			set<string> mySet(multi.begin(), multi.end());;
			multiset<string> myMultiSet(mySet.begin(), mySet.end());
			if (modSearch[1] == "distinct" && modSearch[2] == "reverse") {
				printReverse(size, modSearch, myMultiSet, word);
				break;
			}
			else if (part == modSearch[1] && modSearch[2] == "distinct") {
				printDistinct(size, modSearch, newSet, word);
				break;
			}
			else if (part == modSearch[1] && modSearch[2] == "reverse") {
				printReverse(size, modSearch, multi, word);
				break;
			}
		}
		if (size == 4) {
		
			set<string> mySet(multi.begin(), multi.end());;
			multiset<string> myMultiSet(mySet.begin(), mySet.end());
			if (partOfSpeech && part == modSearch[1] && modSearch[2] == "distinct" && modSearch[3] == "reverse"){
				printReverse(size, modSearch, myMultiSet, word);
				break;
			}
			else if (modSearch[2] != "distinct" || modSearch[3] != "reverse") {
				printError(modSearch, &partOfSpeech);
			}
		}
	
		
	}
	if (size >= 2 && !foundPartOfSpeech && partOfSpeech) {
		cout << "\t<NOT FOUND> To be considered for the next release. Thank you." << endl ;
		cout << "\t|" << endl;
		help();
		return;
	}
	cout << "\t|" << endl;

}

void printDistinct(int size, vector<string> modSearch, set<string> newSet, string word ) {
	string part = "";

	for (set<string>::iterator itr = newSet.begin(); itr != newSet.end(); itr++) {
		part = parts(*itr);
		if (size > 2) {
			if (part == modSearch[1] && modSearch[2] == "distinct") {
				toString(word, *itr);
			}
		}
		else {
			toString(word, *itr);
		}
		
	}
}

void printReverse(int size, vector<string> modSearch, multiset<string>multi, string word){
	string part = "";

	for (multiset<string>::reverse_iterator rit = multi.rbegin(); rit != multi.rend(); rit++) {
		part = parts(*rit);

		if (size == 3) {
			if (part == modSearch[1] && modSearch[2] == "reverse") {
				toString(word, *rit);
			}
			else if (modSearch[1] == "distinct" && modSearch[2] == "reverse") {
				toString(word, *rit);
			}

		}
		else if (size > 3) {
			if (part == modSearch[1] && modSearch[2] == "distinct" && modSearch[3] == "reverse") {
				toString(word, *rit);
			}

		}
		else {
			toString(word, *rit);
		}
	}
}

vector<string> printError(vector<string> modSearch, const bool &partOfSpeech) {
	int size = modSearch.size();
	bool remove1 = false;
	bool remove2 = false;
	bool remove3 = false;
	if (size >= 2) {
		if (!partOfSpeech ^ modSearch[1] != "distinct" ^ modSearch[1] != "reverse") {
			cout << "\t|" << endl;

			cout << "\t<The entered 2nd parameter '" << modSearch[1] << "' is NOT a part of speech.>" << endl;
			cout << "\t<The entered 2nd parameter '" << modSearch[1] << "' is NOT 'distinct'.>" << endl;

			cout << "\t<The entered 2nd parameter '" << modSearch[1] << "' is NOT 'reverse'.>" << endl;

			cout << "\t<The entered 2nd parameter '" << modSearch[1] << "' was disregarded.>" << endl;
			cout << "\t<The 2nd parameter should be a part of speech or 'distinct' or 'reverse'.>" << endl;
			cout << "\t|" << endl;
			remove1 = true;
		}

	}
	if (size >= 3) {
		

		if (modSearch[2] != "distinct" && modSearch[2] != "reverse") {
			cout << "\t|" << endl;

			cout << "\t<The entered 3rd parameter '" << modSearch[2] << "' is NOT 'distinct'.>" << endl;
			cout << "\t<The entered 3rd parameter '" << modSearch[2] << "' is NOT 'reverse'.>" << endl;
			cout << "\t<The entered 3rd parameter '" << modSearch[2] << "' was disregarded.>" << endl;

			cout << "\t<The 3rd parameter should be 'distinct' or 'reverse'.>" << endl;
			cout << "\t|" << endl;

			remove2 = true;
		}
		
	}
	if (size == 4) {
		cout << "\t|" << endl;
		if (modSearch[3] != "reverse") {
			cout << "\t<The entered 4th parameter '" << modSearch[3] << "' is NOT 'reverse'.>" << endl;

			cout << "\t<The 4th parameter should be 'reverse'.>" << endl;
			cout << "\t|" << endl;
			remove3 = true;
		}

	}
	if (remove3) {
		modSearch.erase(find(modSearch.begin(), modSearch.end(), modSearch[3]));
	}
	if (remove2) {
		modSearch.erase(find(modSearch.begin(), modSearch.end(), modSearch[2]));
	}
	if (remove1) {
		modSearch.erase(find(modSearch.begin(), modSearch.end(), modSearch[1]));
	}
	
	return modSearch;
}
