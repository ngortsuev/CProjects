#pragma once
#include <string>
#include <vector>
using namespace std;

class Mono1
{
private:
	int key;
	int random_key;
	vector<char> plainText;
	vector<char> cipherText;
public:
	Mono1();
	string encrypt(string text);
	string decrypt(string text);
};

