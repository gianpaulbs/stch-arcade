#pragma once
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>

using namespace System;
using namespace std;
class File {
private:
	ofstream fileWrite;
	ifstream fileRead;
	string text;
	int n, x, y;
public:
	File() {}
	~File() {}
	void readData() {
		fileRead.open("resources/files/coordenadas.txt", ios::in);
		if (fileRead.fail()) {
			fileRead.close();
			fileWrite.open("resources/files/coordenadas.txt", ios::out);
			fileWrite << "65" << endl;
			fileWrite << "65" << endl;
			fileWrite.close();
			fileRead.open("configuration.txt", ios::in);
		}
		
		getline(fileRead, text);
		x = atoi(text.c_str());
		getline(fileRead, text);
		y = atoi(text.c_str());
		fileRead.close();
	}
	int getX() { return x; }
	int getY() { return y; }
};