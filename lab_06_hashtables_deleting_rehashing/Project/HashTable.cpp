#include "HashTable.h"

ostream& operator<<(ostream& out, const HashTable& hash)
{
	for (int i = 0; i < hash.capacity; i++)
	{
		out << "Index " << i << ": ";
		if (hash.table[i] != -1)
			out << hash.table[i] << endl;
		else
			out << "E" << endl;
	}
	return out;
}

HashTable::HashTable()
{
	capacity = CAPACITY;
	numOfElements = 0;
	table = new int[capacity];

	while (numOfElements < capacity) { table[numOfElements++] = -1; }

	numOfElements = 0;
}

HashTable::HashTable(int newCapacity)
{
	capacity = newCapacity;
	numOfElements = 0;
	table = new int[capacity];

	while (numOfElements < capacity) { table[numOfElements++] = -1; }

	numOfElements = 0;
}

HashTable::HashTable(const HashTable & otherHash)
{
	capacity = otherHash.capacity;
	numOfElements = otherHash.numOfElements;

	table = new int[capacity];

	for (int i = 0; i < capacity; i++)
		table[i] = otherHash.table[i];
}

bool HashTable::deleteElement(int key)
{
	if (numOfElements > 0)
	{
		int iterations = 0;
		int index = hashValue(key);
		while (iterations < capacity)
		{
			if (table[index + iterations] == key)
			{
				table[index + iterations] = -2;
				numOfElements--;
				return true;
			}
			else if (table[index + iterations] == -1 || iterations == capacity - 1)
			{
				cerr << key << " not found.\n\n";
				return false;
			}
			else if (index + iterations == capacity - 1)
			{
				index = 0;
				iterations = 0;
			}
			else iterations++;
		}
	}
	else
	{
		cerr << "Hash Table is empty.  No elements to delete.\n\n";
		return false;
	}
	
}

void HashTable::insert(int key)
{
	int iterations = 0;
	int index = hashValue(key);
	while (iterations < capacity)
	{
		// this if statement assumes that none of the elements meant to be persisted, are negative.
		// otherwise we would say this || table[index + iterations] == -2
		if (table[index + iterations] <= -1)
		{
			table[index + iterations] = key;
			numOfElements++;
			iterations = capacity; // to exit loop
		}
		// wraps around to beginning of hash table
		else if (index + iterations == capacity - 1)
		{
			index = 0;
			iterations = 0;
		}
		else iterations++;
	}
	
	// rehash automatically if the hash table is equal to or over half capacity
	if (numOfElements / (capacity*1.0) >= HALF_FULL_THRESHOLD) rehash();
}

void HashTable::rehash()
{
	HashTable newTable(updateCapacity());
	int newKey = 0;
	for(int i = 0; i < capacity; i++)
	{
		if (table[i] != -1)
		{
			newKey = newTable.hashValue(table[i]);
			if (newTable.table[newKey] == -1)
			{
				newTable.table[newKey] = table[i];
				newTable.numOfElements++;
			}
			else collision(i, newKey,newTable);
		}
		// else, dont do anything because that index is already -1/E
	}
	*this = newTable;
}

int HashTable::updateCapacity() const
{
	// Note: If the hash table is large enough, doubling its capacity and adding one exceeds any of the listed prime numbers here.
	// But we are only working with small hash tables hopefully.
	// If the hash table were bigger we would have to provide a different implementation that has 3 digit prime numbers.
	int primeNumberArray[25] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97 };
	int newCapacity = capacity * 2 + 1;
	// find the prime number that is equal to or just above 'newCapacity'
	int i = 0;
	while (i < 25)
	{
		if (primeNumberArray[i] == newCapacity || 
			primeNumberArray[i] > newCapacity) { return primeNumberArray[i]; }
		else i++;
	}
}

void HashTable::collision(int i, int newKey, HashTable& newTable)
{
	int iterations = 1;
	while (iterations < newTable.capacity)
	{
		// if we went off the end of the array, circle back to the front
		if ((newKey + iterations) >= newTable.capacity)
		{
			iterations = 0;
			newKey = 0;
		}
		else if (newTable.table[newKey + iterations] == -1)
		{
			newTable.table[newKey + iterations] = table[i];
			newTable.numOfElements++;
			iterations = newTable.capacity;
		}
		else iterations++;
	}
}

bool HashTable::search(int key)
{
	int iterations = 0;
	int index = hashValue(key);
	while (iterations < capacity)
	{
		if (table[index + iterations] == key) return true;
		// an empty index just after where the key is expected
		// means the hash table does not contain the key
		else if (table[index + iterations] == -1 || iterations == capacity - 1) return false;
		// if the hashValue is located towards the end of the
		// hash table, it might have been bumped to the beginning.
		else if (index + iterations == capacity - 1)
		{
			index = 0;
			iterations = 0;
		}
		else iterations++;
	}
}

HashTable& HashTable::operator=(const HashTable& rightSide)
{
	if (&rightSide != this)
	{
		if (capacity != rightSide.capacity)
		{
			delete[] table;
			table = new int[rightSide.capacity];

			capacity = rightSide.capacity;
		}

		numOfElements = rightSide.numOfElements;

		for (int i = 0; i < capacity; i++)
			table[i] = rightSide.table[i];
	}
	else
		cerr << "Attempted assignment to itself.";

	return *this;
}

int HashTable::operator[](int index) const
{
	return table[index];
}

HashTable::~HashTable()
{
	delete[] table;
	table = nullptr;
}
