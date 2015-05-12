
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

/* ~~~ Question (a) ~~~ */
string make_numeronym(const string &str) {
	if (str.size() < 2) {
		return str;
	}

	ostringstream res;
	res << str[0] << str.size()-2 << str[str.size()-1];

	return res.str();	
}

/* ~~~ Question (b) ~~~ */

void from_numeronym_aux(char first, char last, string::size_type letters_left,
			string &buff, vector<string> &results) {
	if (letters_left == 0) {
		results.push_back(first + buff + last);
		return;
	}

	for (int i = 0; i < 26; i++) {
		buff.push_back('a'+i);
		from_numeronym_aux(first, last, letters_left-1, buff, results);
		buff.pop_back();
	}
}

vector<string> from_numeronym(const string &numeronym) {
	vector<string> result;
	if (numeronym.size() < 2) {
		result.push_back(numeronym);
		return result;
	}

	char first = numeronym[0];
	char last = numeronym[numeronym.size()-1];
	istringstream iss(numeronym.substr(1, numeronym.size()-2));
	string::size_type letters;
	iss >> letters;

	string buff;
	from_numeronym_aux(first, last, letters, buff, result);

	return result;
}

int main(void) {
	cout << "Enter a string to convert to numeronym and then from numeronym to every possible combination" << endl;
	cout << "> ";

	string str;
	while (cin >> str) {
		string numeronym = make_numeronym(str);
		cout << "Numeronym: " << numeronym << endl;

		cout << "Show possible strings (output may be very large)? [Y/N] ";
		char answer;
		cin >> answer;

		if (answer == 'Y' || answer == 'y') {

			cout << "Possible strings:" << endl;
			vector<string> possibilities = from_numeronym(numeronym);

			for (vector<string>::const_iterator it = possibilities.begin();
			     it != possibilities.end();
			     it++) {
				cout << *it << endl;
			}
		}

		cout << "> ";
	}

	return 0;
}
