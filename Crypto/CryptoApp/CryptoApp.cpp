#include <iostream>
#include <string>
#include "Caesar.h"
using namespace std;

int main()
{
    std::cout << "Caesar algoritm\n";

	string text = "simpletext";

	Caesar* caesar = new Caesar(25);
	
	string en_text = caesar->encrypt(text);
	string de_text = caesar->decrypt(en_text);

	cout << "Text: " << text << endl;

	cout << "Encrypt: " << en_text << endl;

	cout << "Decrypt: " << de_text << endl;
}
