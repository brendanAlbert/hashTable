/*
	Albert, Brendan
	Fazeli, Bijan

	CS A200
	March 4, 2017

	Lab 06: Hash Tables - Deleting & Rehashing
 */

#include "HashTable.h"

#include <iostream>
using namespace std;

int main()
{
	/*
	int a2[] = {70, 81, 60, 51, 89, 38, 97, 68, 24};
	//int a3[] = { 1, 2 };
	int numOfElem1 = 9;

	HashTable ht1;

	for (int i = 0; i < numOfElem1; ++i)
		ht1.insert(a2[i]);

	cout << ht1 << endl;

	cout << (ht1.deleteElement(89) ? "Element removed!\n" : "Element not found.\n\n");
	cout << (ht1.deleteElement(60) ? "Element removed!\n":"Element not found.\n\n");
	cout << (ht1.deleteElement(6) ? "Element removed!\n" : "Element not found.\n\n");
	cout << ht1 << endl;
	*/
	
	int a1[] = {45,32,65,24,91,67,82,46,73,12,58};
	int numOfElem1 = 11;
	HashTable ht1;
	cout << "Insert half of the array into the hash table...\n";
	for (int i = 0; i < (numOfElem1 / 2); ++i)
		ht1.insert(a1[i]);

	cout << ht1;
	cout << endl;
	
	cout << "\nInsert the rest of the array into the hash table...\n";
	for (int i = (numOfElem1 / 2); i < numOfElem1; ++i)
		ht1.insert(a1[i]);

	cout << ht1;
	cout << endl;
	
	cout << "\nStart searching...\n";
	for (int i = numOfElem1 - 1; i >= 0; --i)
	{
		if (ht1.search(a1[i]))
			cout << a1[i] << " found." << endl;
		else
			cout << a1[i] << " not found." << endl;
	}

	(ht1.search(999))? cout << "999 found.\n" : cout << "999 not found.\n";
	cout << endl;

	cout << ((ht1.deleteElement(32))? "Element deleted.\n\n":"Element not found.\n\n");
	cout << ((ht1.deleteElement(45)) ? "Element deleted.\n\n" : "Element not found.\n\n");
	cout << ((ht1.deleteElement(1)) ? "Element deleted.\n\n" : "Element not found.\n\n");


	/*
	This code was only relevant when the hash table contained as many elements as the capacity allowed.
	This will not happen now with the ability to rehash.
	The code will be kept for posterity though.

	cout << "\nTry inserting another item => Expected: Error message\n";
	ht1.insert(35);
	cout << endl;
	*/

	cout << "\nTest copy constructor...\n";
	HashTable ht2 (ht1);
	cout << ht2;
	cout << endl;

	cout << "\nCheck if different addresses (should be different)...\n";
	cout << "Address ht1: " << &ht1 << endl;
	cout << "Address ht2: " << &ht2 << endl;
	cout << endl;

	cout << "\nTest overloaded assignment operator...\n";
	HashTable ht3;
	ht3 = ht1;
	cout << ht3;
	cout << endl;
	
	cout << "\nCheck if different addresses (should be different)...\n";
	cout << "Address ht1: " << &ht1 << endl;
	cout << "Address ht3: " << &ht3 << endl;
	cout << endl;

	

	cout << endl;
	system("Pause");
	return 0;
}