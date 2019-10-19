#pragma once
#include <string>
using namespace std;

class Caesar
{
private:
	int key;
	char encrypt_sym(char c, int k);
	char decrypt_sym(char c, int k);

public:
	Caesar(int key);
	string encrypt(string text);
	string decrypt(string text);
};

