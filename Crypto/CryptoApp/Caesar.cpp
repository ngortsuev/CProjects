#include "Caesar.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

Caesar::Caesar(int key) 
{
	this->key = key;
}

char Caesar::encrypt_sym(char c, int k)
{
	c = toupper(c);
	
	c = (((c - 65) + k) % 26) + 65;
	
	return c;
}

char Caesar::decrypt_sym(char c, int k)
{
	c = ((((c - 65) - k) + 26) % 26) + 65;

	c = tolower(c);

	return c;
}

string Caesar::encrypt(string text)
{
	string output;
	
	for (unsigned int x = 0; x < text.length(); x++) 
	{
		output += encrypt_sym(text[x], key);
	}
	return output;
}

string Caesar::decrypt(string text) 
{
	string output;
	
	for (unsigned int x = 0; x < text.length(); x++)
	{
		output += decrypt_sym(text[x], key);
	}
	return output;
}
