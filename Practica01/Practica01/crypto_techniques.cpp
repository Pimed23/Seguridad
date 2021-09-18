#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

string read_file(string filename);

void preprocessing_text(string& text);
void replacing_letters(string& text);
void remove_accents(string& text);
void convert_lowercase(string& text);
void convert_uppercase(string& text);
void remove_special_characters(string& text);
void frequencies(string text);
void kasiski(string text);
void unicode8(string text);
void insert_word(string text, string word);

bool sorting_frequencies(const pair<char, int>& l, const pair<char, int>& r);

int main() {
	string file = "HERALDOSNEGROS.txt";
	string text = read_file(file);
	preprocessing_text(text);

	string file_preprocessed = "HERALDOSNEGROS_pre.txt";
	string text_preprocessed = read_file(file_preprocessed);

	frequencies(text_preprocessed);
	kasiski(text_preprocessed);
	unicode8(text_preprocessed);

	string inserted_word = "AQUI";
	insert_word(text_preprocessed, inserted_word);

	return 0;
}


string read_file(string filename) {

	ifstream file;
	file.open(filename, ios::in);

	if (file.fail()) {
		cout << "No se pudo abrir el archivo...";
		exit(1);
	}

	string temp, text = "";
	while (!file.eof()) {
		getline(file, temp);
		text += temp;
	}

	file.close();
	return text;
}


void preprocessing_text(string& text) {

	convert_lowercase(text);
	replacing_letters(text);
	remove_accents(text);
	convert_uppercase(text);
	remove_special_characters(text);
}


void replacing_letters(string& text) {

	ofstream file;
	cout << "Reemplazando las letras..." << endl;
	file.open("Ejercicio #01 - Sustituciones.txt", ios::out);

	for (auto i = text.begin(); i < text.end(); ++i) {
		switch (*i) {
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
	
	file << text;
	file.close();
}

void remove_accents(string &text) {

	ofstream file;
	cout << "Quitando las tildes..." << endl;
	file.open("Ejercicio #02 - Tildes.txt", ios::out);
	for (auto i = text.begin(); i < text.end(); ++i) {
		switch (*i) {
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
			default:
				break;
		}
	}

	file << text;
	file.close();
}

void convert_lowercase(string& text) {

	for (auto i = text.begin(); i < text.end(); ++i) {
		if (*i >= 'A' && *i <= 'Z')
			*i += 32;
		else if (*i == 'Ñ')
			*i = 'ñ';
	}
}

void convert_uppercase(string& text) {

	ofstream file;
	cout << "Convirtiendo a mayusculas..." << endl;
	file.open("Ejercicio #03 - Mayusculas.txt", ios::out);

	for (auto i = text.begin(); i < text.end(); ++i) {
		if (*i >= 'a' && *i <= 'z')
			*i -= 32;
	}

	file << text;
	file.close();
}

void remove_special_characters(string& text) {

	ofstream file, out;
	cout << "Quitando las espacios y caracteres especiales..." << endl;
	file.open("Ejercicio #04 - Espacios y signos.txt", ios::out);
	out.open("HERALDOSNEGROS_pre.txt", ios::out);

	for (auto i = text.begin(); i < text.end(); ++i) {
		if (*i < 'A' || *i > 'Z')
			*i = '\0';
	}

	text.erase(std::remove(text.begin(), text.end(), '\0'), text.end());

	file << text;
	out << text;

	file.close();
	out.close();
}

void frequencies(string text) {

	ofstream file;
	cout << "Realizando la tabla de frecuencias..." << endl;
	file.open("Ejercicio #05 - Frecuencias.txt", ios::out);
	
	map<char, int> frecuency_table;
	for (auto i = text.begin(); i < text.end(); ++i) {
		if (frecuency_table.find(*i) != frecuency_table.end())
			frecuency_table.at(*i)++;
		else
			frecuency_table.insert_or_assign(*i, 1);
	}

	std::vector<pair<char, int>> frecuency_table_sorted;
	std::copy(frecuency_table.begin(), frecuency_table.end(), std::back_inserter<std::vector<pair<char, int >>>(frecuency_table_sorted));
	std::sort(frecuency_table_sorted.begin(), frecuency_table_sorted.end(), sorting_frequencies);

	file << "Tabla de frecuencias" << endl;
	for (auto& elem : frecuency_table)
		file << elem.first << " " << elem.second << endl;

	file << "\nValores más altos:" << endl;
	for (auto i = frecuency_table_sorted.begin(); i < frecuency_table_sorted.begin() + 5; ++i) {
		file << (*i).first << " " << (*i).second << endl;
	}

	file.close();
}

bool sorting_frequencies(const pair<char, int>& l, const pair<char, int>& r) {
	if (l.second != r.second)
		return l.second > r.second;
	return l.first > r.first;
}

void kasiski(string text) {

	ofstream file;
	cout << "Utilizando metodo de Kasiski..." << endl;
	file.open("Ejercicio #06 - Kasiski.txt", ios::out);

	int distance = 0;
	string trigram1, trigram2;
	for (size_t i = 0; i < text.size() - 2; ++i) {
		trigram1 = text.substr(i, 3);
		
		for (size_t j = i + 1; j < text.size() - 2; ++j) {
			trigram2 = text.substr(j, 3);
			
			if (trigram1 == trigram2) {
				distance = j - i;
				file << trigram1 << " " << trigram2 << " Distance: " << distance << endl;
			}
		}
	}

	file.close();
}

void unicode8(string text) {

	ofstream file;
	cout << "Convirtiendo a UNICODE-8..." << endl;
	file.open("Ejercicio #07 - Unicode8.txt", ios::out);

	file << "0x";
	for (size_t i = 0; i < text.size(); ++i)
		file << std::hex << int(text[i]);

	file.close();
}

void insert_word(string text, string word) {

	ofstream file;
	cout << "Agregando la palabra AQUI cada 20 caracteres..." << endl;
	file.open("Ejercicio #09 - Aqui.txt", ios::out);

	string result = "";
	int count = 0;
	for (size_t i = 0; i < text.size(); ++i) {
		
		if (count == 20) {
			result += word;
			count = -1;
		} else 
			result += text[i];
		++count;
	}

	while (result.size() % 4) result += "X";

	file << result;
	file.close();
}


