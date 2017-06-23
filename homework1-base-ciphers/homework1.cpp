#include <iostream>
#include <string>
#include <cstdint>
#include <cstring>
using namespace std;

char plaintext[18] = "sentfrommyiphone";
static char ciphertext[18];


void CaesarCipher();
void MonoalphabeticCipher();
void PlayfairCipher();

int convertToDecimal(string decimalNumber);
int convertToDecimal(string binarylNumber);
void VernamCipher();

void RowTransposition();
void ProductCipher();


int main(int argc, char const *argv[])
{
	cout << "The plaintext is " << plaintext << ". \n " << endl;
	cout << "The ciphertext is " << endl;
	
	CaesarCipher();
	MonoalphabeticCipher();
	PlayfairCipher();
	VernamCipher();
	RowTransposition();
	ProductCipher();

	return 0;
}

void CaesarCipher()
{
	char alphabet[28] = "abcdefghijklmnopqrstuvwxyz";
	int key = 3;

	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 26; ++j)
		{
			if (plaintext[i] == alphabet[j])
			{
				ciphertext[i] = alphabet[(j + key) % 26];
			}
		}
	}

	cout<< ciphertext << "	after Caesar Cipher." << endl;
}

void MonoalphabeticCipher()
{
	char alphabet[28] = "abcdefghijklmnopqrstuvwxyz";
	char keyAlphabet[28] = "QWERTYUIOPASDFGHJKLZXCVBNM";

	/* 
		Find the alperbet index in plaintext by compare plaintext with alphabet array.
		And use this index to find its ciphertext.
	*/
	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 26; ++j)
		{
			if (plaintext[i] == alphabet[j])
			{
				ciphertext[i] = keyAlphabet[j];
			}
		}
	}

	cout << ciphertext << "	after Monoalphabetic Cipher."  << endl;
}
void PlayfairCipher()
{
	/***
		The key is 'DPP'.
		The table is :
		D P A B C
		E F G H I/J 
		K L M N O 
		Q R S T U 
		V W X Y Z
	***/
	char playfairCipherTable[5][7] = {"DPABC","EFGHI","KLMNO","QRSTU","VWXYZ"};

	int i1,j1,i2,j2;
	for (int m = 0; m < 15; ++m)
	{
		if (plaintext[m] == 'J')
		{
			plaintext[m] = 'I';
		}
		
		// compare two alperbets and record their index in array 'playfairCipherTable'
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if ((playfairCipherTable[i][j] + 32) == plaintext[m])
				{
					i1 = i;
					j1 = j;
				}
			}
		}
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if ((playfairCipherTable[i][j] + 32) == plaintext[m+1])
				{
					i2 = i;
					j2 = j;
				}
			}
		}

		/* 
		encrypte the plaintext by find the moved alperbet in 
		array 'playfairCipherTable', and give this result to ciphertext

		So the code below is to get the ciphertext[m] in different situations
		*/
		if (i1 == i2)
		{
					
			if (j1 == 4)
			{
				ciphertext[m] = playfairCipherTable[i1][0];
				ciphertext[m+1] = playfairCipherTable[i2][j2+1];
			}
			else if (j2 == 4)
			{
				ciphertext[m] = playfairCipherTable[i1][j1+1];
				ciphertext[m+1] = playfairCipherTable[i2][0];
			}
			else 
			{
				ciphertext[m] = playfairCipherTable[i1][j1+1];
				ciphertext[m+1] = playfairCipherTable[i2][j2+1];
			}
		}
		else if (j1 == j2)
		{
			if (i1 == 4)
			{
				ciphertext[m] = playfairCipherTable[0][j1];
				ciphertext[m+1] = playfairCipherTable[i2+1][j2];
			}
			else if (i2 == 4)
			{
				ciphertext[m] = playfairCipherTable[i1+1][j1];
				ciphertext[m+1] = playfairCipherTable[0][j2];
			}
			else 
			{
				ciphertext[m] = playfairCipherTable[i1+1][j1];
				ciphertext[m+1] = playfairCipherTable[i2+1][j2];
			}
		}
		else{
			ciphertext[m] = playfairCipherTable[i1][j2];
			ciphertext[m+1] = playfairCipherTable[i2][j1];
		}
		// move to next group alperbets(one group has two alperbets)
		++m;
	}
	
	cout << ciphertext << "	after Playfair Cipher." << endl;
}

string convertToFiveBinary(int number)
{
	int binaryTemp[5];
	int temp = 0;

	for (int i = 0; i < 5; ++i)
	{

		if (number != 0)
		{
			// cout << number << " ";
			binaryTemp[i] = number%2;
			number = number/2;
			temp ++;
		}
		else
		{
			break;
		}
	}

	string v = "";
	for (int i = temp - 1; i >= 0; --i)
	{
		v += to_string(binaryTemp[i]);
	}
	while( v.size() < 5)
	{
		v = "0" + v;
	}
	 
	return v;
}

int convertToDecimal(string binarylNumber)
{
	int length = binarylNumber.size();
	char binaryNumberBinary[length];
	strcpy(binaryNumberBinary , binarylNumber.c_str());
	int tempDecimalNumber = 1;
	int decimalNumber = 0;

	for (int i = length; i > 0; --i)
	{
		tempDecimalNumber = 1;
		if(binaryNumberBinary[i - 1] == '1')
		{
			for (int j = 0; j < (length - i); ++j)
			{
				tempDecimalNumber = tempDecimalNumber * 2 ;
			}
			decimalNumber = decimalNumber + tempDecimalNumber * 1;
		}
	}
	return decimalNumber;
}

void VernamCipher()
{
	char alphabet[28] = "abcdefghijklmnopqrstuvwxyz";
	int plaintextDecimalIndex[16];
	string plaintextBinaryIndex[16];

	char keyAlphabet[5] = "KMT";
	int keyDecimalIndex[3];
	string keyBinaryIndex[3];
	string keyBinary = "";

	string ciphertextBinaryArr[16];
	string ciphertextBinaryTemp = "";
	char plaintextBinaryTemp[5];
	char keyBinaryTemp[5];
	int cipertextDecimalIndex[16];

	/* 1 get the plaintextBinary */
	// find the plaintext decimal index of alperbet
	for (int i = 0; i < sizeof(plaintext) - 2; ++i)
	{
		for (int j = 0; j < 26; ++j)
		{
			if (plaintext[i] == alphabet[j])
			{
				plaintextDecimalIndex[i] = j;
			}
		}
	}
	// convert plaintext decimal index to binary by one and one alperbet
	for (int i = 0; i < sizeof(plaintextBinaryIndex)/sizeof(plaintextBinaryIndex[0]); ++i)
	{
		plaintextBinaryIndex[i] = convertToFiveBinary(plaintextDecimalIndex[i]);
	}

	/* 2 get the keyBinary */
	// find the key decimal index of alperbet
	for (int i = 0; i < (sizeof(keyAlphabet)/sizeof(keyAlphabet[0])) - 2; ++i)
	{
		for (int j = 0; j < 26; ++j)
		{
			if ((keyAlphabet[i] +32) == alphabet[j])
			{
				keyDecimalIndex[i] = j;
			}
		}
	}
	// convert key decimal index to binary by one and one alperbet
	for (int i = 0; i < (sizeof(keyAlphabet)/sizeof(keyAlphabet[0])) - 2; ++i)
	{
		keyBinaryIndex[i] = convertToFiveBinary(keyDecimalIndex[i]);
	}

	/* 3 xor operation for plaintextBinary and keyBinary */
	for (int i = 0; i < sizeof(plaintextBinaryIndex)/sizeof(plaintextBinaryIndex[0]); ++i)
	{
		ciphertextBinaryTemp = "";
		strcpy(plaintextBinaryTemp , plaintextBinaryIndex[i].c_str());
		strcpy(keyBinaryTemp , keyBinaryIndex[i%3].c_str());

		for (int j = 0; j < sizeof(plaintextBinaryTemp)/sizeof(plaintextBinaryTemp[0]); ++j)
		{
				/* compare every char */
				if (plaintextBinaryTemp[j] == keyBinaryTemp[j])
				{
					ciphertextBinaryTemp = ciphertextBinaryTemp + "1";
				}
				else
				{
					ciphertextBinaryTemp = ciphertextBinaryTemp + "0";
				}
		}
		ciphertextBinaryArr[i] = ciphertextBinaryTemp;
	}

	/* 4 convert cipertext binary to  decimal by for loop */
	for (int i = 0; i < sizeof(ciphertextBinaryArr)/sizeof(ciphertextBinaryArr[0]); ++i)
	{
		cipertextDecimalIndex[i] = convertToDecimal(ciphertextBinaryArr[i]);
	}

	/* 5 print the cipher alperbet by decimal index by for loop */
	for (int i = 0; i < sizeof(cipertextDecimalIndex)/sizeof(cipertextDecimalIndex[0]); ++i)
	{
		// if cipertextDecimalIndex[i] > 26 , it will use the value of mod 26.
		cout << alphabet[cipertextDecimalIndex[i]%26];
	}

	cout << "	after Vernam Cipher." << endl;
}

void RowTransposition()
{
	/*
		5 2 8 3 4 6 7 1
		S E N T F R O M 
		M Y I P H O N E
	*/
	int key[8] = {5,2,8,3,4,6,7,1};
	int keyLength = sizeof(key) / sizeof(key[0]);
	int plaintextLength = sizeof(plaintext) / sizeof(plaintext[0]);
	int rowsOfPlaintext = plaintextLength / keyLength;
	char rowTable[rowsOfPlaintext][keyLength];
	int counter = 0;

	int keyIndex[keyLength];
	int keyIndexLength = sizeof(keyIndex) / sizeof(keyIndex[0]);

	// create the rowTable
	for (int i = 0; i < plaintextLength; ++i)
	{
		int cols = i % 8;
		int rows = i / 8;

		rowTable[rows][cols] = plaintext[i];
	}

	/* create a new order table for cipher, this order must */
	for (int i = 0; i < keyLength; ++i)
	{
		for (int j = 0; j < keyLength; ++j)
		{
			if (key[j] < key[i])
			{
				counter++;
			}
		}
		keyIndex[counter] = i;
		counter = 0;
	}

	/* 
	add to ciphertext ordering by RowTransposition
	and the key is 5 2 8 3 4 6 7 1
	*/
	int rowsNumber = sizeof(rowTable)/sizeof(rowTable[0]);
	int cipertextIndexTemp = 0;

	for (int i = 0; i < keyIndexLength; ++i)
	{
		for (int j = 0; j < rowsNumber; ++j)
		{
			ciphertext[cipertextIndexTemp] = rowTable[j][keyIndex[i]];
			cipertextIndexTemp++;
		}

	}
	cout << ciphertext << "	after Row Transposition." << endl;
}

void ProductCipher()
{
	/*
	key :
	01 02 03 04 05 06 07 08 
	09 10 11 12 13 14 15 16
	Transport :
	15 11 02 10 16 03 07 14 
	04 12 09 06 01 05 08 13

	plaintext table :
	s e n d f r o m
	m y i p h o n e
	transport plaintext result :
	n i e y e n o o
	d p m r s f m h
	*/
	int plaintextLength = sizeof(plaintext)/sizeof(plaintext[0]) -2;

	// create transportIndex
	int transportIndex[plaintextLength] = {15,11,2,10,16,3,7,14,4,12,9,6,1,5,8,13};

	// give the ciphertext by transpoertIndex value and its index
	for (int i = 0; i < plaintextLength; ++i)
	{
		ciphertext[i] = plaintext[transportIndex[i] - 1];
	}
	cout << ciphertext << "	after Product Cipher." << endl;
}
