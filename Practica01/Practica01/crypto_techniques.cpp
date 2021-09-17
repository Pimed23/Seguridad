#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

void replace_letter(string &text) {
	for (auto i = text.begin(); i < text.end(); ++i) {
		switch (*i) {
			// Removing the accents
			case 'á':
				*i = 'a';
				break;
			case 'é':
				*i = 'e';
				break;
			case 'í':
				*i = 'i';
				break;
			case 'ó':
				*i = 'o';
				break;
			case 'ú':
				*i = 'v';
				break;

			// Substituting special letters
			case 'j':
				*i = 'i';
				break;
			case 'h':
				*i = 'i';
				break;
			case 'ñ':
				*i = 'n';
				break;
			case 'k':
				*i = 'l';
				break;
			case 'u':
				*i = 'v';
				break;
			case 'w':
				*i = 'v';
				break;
			case 'y':
				*i = 'z';
				break;
			default:
				break;
		}
	}
}

void remove_special_characters(string &text) {
	for (auto i = text.begin(); i < text.end(); ++i) {
		if (*i < 'A' || * i > 'Z')
			*i = '\0';
	}
}

void convert_uppercase(string& text) {
	for (auto i = text.begin(); i < text.end(); ++i) {
		if (*i >= 'a' && *i <= 'z')
			*i -= 32;
	}
}

void convert_lowercase(string& text) {
	for (auto i = text.begin(); i < text.end(); ++i) {
		if (*i >= 'A' && *i <= 'Z')
			*i += 32;
		else if (*i == 'Ñ')
			*i = 'ñ';
	}
}

void substitute_letters(string filename) {
	ofstream out;
	ifstream file;
	file.open(filename, ios::in);
	out.open("HERALDOSNEGROS_pre.txt", ios::out);

	if (file.fail()) {
		cout << "No se pudo abrir!" << endl;
		return;
	}

	string text;
	while (!file.eof()) {
		std::getline(file, text);
		convert_lowercase(text);
		replace_letter(text);
		convert_uppercase(text);
		remove_special_characters(text);
		for (auto i = text.begin(); i < text.end(); ++i) {
			if (*i == '\0')
				continue;
			out << *i;
		}
	}

	file.close();
	out.close();
}

void frequencies(string filename) {
	map<char, int> frecuency_table;
	ifstream file;
	file.open(filename, ios::in);

	if (file.fail()) {
		cout << "No se pudo abrir!" << endl;
		return;
	}
	
	// Filling the table
	string text;
	while (!file.eof()) {
		std::getline(file, text);
		for (auto i = text.begin(); i < text.end(); ++i) {
			if (frecuency_table.find(*i) != frecuency_table.end()) {
				frecuency_table.at(*i)++;
			} else {
				frecuency_table.insert_or_assign(*i, 1);
			}
		}
	}

	file.close();
	
	// Sorting
	std::vector<pair<char, int>> temp;
	std::copy(frecuency_table.begin(), frecuency_table.end(),std::back_inserter<std::vector<pair<char, int >>>(temp));
	
	std::sort(temp.begin(), temp.end(),[](const pair<char, int> &l, const pair<char, int> &r) {
		if (l.second != r.second) 
			return l.second > r.second;
		return l.first > r.first;
	});

	/*
	for (auto& t : frecuency_table) {
		cout << t.first << " " << t.second << endl;
	}*/

	/* ORDERED */
	cout << "TABLA DE FRECUENCIAS" << endl;
	for (int i = 0; i < temp.size(); ++i)
		cout << temp[i].first << " " << temp[i].second << endl;
}

void kasiski(string filename) {
	ifstream file;
	file.open(filename, ios::in);

	if (file.fail()) {
		cout << "No se pudo abrir!" << endl;
		return;
	}
	
	string text;
	while (!file.eof()) {
		std::getline(file, text);
		auto last = text.begin();
		int distance;

		for (auto i = text.begin(), j = text.begin() + 1, k = text.begin() + 2; k < text.end(); ++i, ++j, ++k) {
			if (*i == *j && *i == *k) {
				if (last != i) {
					cout << i - last << endl;
					last = i;
				}
			}
		}
	}

	file.close();
}

void convert_utf8(string filename) {
	ifstream file;
	map <char, string> utf8;
	utf8.insert(make_pair('A', "41"));
	utf8.insert(make_pair('B', "42"));
	utf8.insert(make_pair('C', "43"));
	utf8.insert(make_pair('D', "44"));
	utf8.insert(make_pair('E', "45"));
	utf8.insert(make_pair('F', "46"));
	utf8.insert(make_pair('G', "47"));
	utf8.insert(make_pair('H', "48"));
	utf8.insert(make_pair('I', "49"));
	utf8.insert(make_pair('J', "4A"));
	utf8.insert(make_pair('K', "4B"));
	utf8.insert(make_pair('L', "4C"));
	utf8.insert(make_pair('M', "4D"));
	utf8.insert(make_pair('N', "4E"));
	utf8.insert(make_pair('O', "4F"));
	utf8.insert(make_pair('P', "50"));
	utf8.insert(make_pair('Q', "51"));
	utf8.insert(make_pair('R', "52"));
	utf8.insert(make_pair('S', "53"));
	utf8.insert(make_pair('T', "54"));
	utf8.insert(make_pair('U', "55"));
	utf8.insert(make_pair('V', "56"));
	utf8.insert(make_pair('W', "57"));
	utf8.insert(make_pair('X', "58"));
	utf8.insert(make_pair('Y', "59"));
	utf8.insert(make_pair('Z', "5A"));

	
	file.open(filename, ios::in);
	if (file.fail()) {
		cout << "No se pudo abrir!" << endl;
		return;
	}
	
	cout << "CONVERT TO UTF-8" << endl;
	string text;
	while (!file.eof()) {
		std::getline(file, text);
		cout << "0x";
		for (auto i = text.begin(); i < text.end(); ++i) {
			cout << utf8.at(*i);
		}
		cout << endl;
	}
	
}

int main() {
	string filename = "HERALDOSNEGROS.txt";
	substitute_letters(filename);
	frequencies("HERALDOSNEGROS_pre.txt");
	kasiski("HERALDOSNEGROS_pre.txt");
	convert_utf8("HERALDOSNEGROS_pre.txt");


	return 0;
}