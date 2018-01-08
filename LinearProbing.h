#ifndef _LINEARPROBINGH_
#define _LINEARPROBINGH_

#include <vector>
#include <string>
using namespace std;

// QuadraticProbing Hash table class
//
// CONSTRUCTION: an initialization for ITEM_NOT_FOUND
//               and an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// Hashable find( x )     --> Return item that matches x
// void makeEmpty( )      --> Remove all items
// int hash( String str, int tableSize )
//                        --> Static method to hash strings


/**
* Internal method to test if a positive number is prime.
* Not an efficient algorithm.
*/
bool isprime(int n)
{
	if (n == 2 || n == 3)
		return true;

	if (n == 1 || n % 2 == 0)
		return false;

	for (int i = 3; i * i <= n; i += 2)
		if (n % i == 0)
			return false;

	return true;
}

/**
* Internal method to return a prime number at least as large as n.
* assumes n > 0.
*/
int nextPrime(int n)
{
	if (n % 2 == 0)
		n++;

	for (; !isprime(n); n += 2)
		;

	return n;
}


/**
* A hash routine for string objects.
*/
int hashFunction(const std::string &key, int tableSize)
{
	int hashVal = 0;

	for (int i = 0; i < key.length(); i++)
		hashVal = 37 * hashVal + key[i];
	hashVal %= tableSize;
	if (hashVal < 0)
		hashVal += tableSize;
	return hashVal;
}

/**
* A hash routine for integers
*/
int hashFunction(int key, int tableSize)
{
	if (key < 0) key = -key;
	return key % tableSize;
}

template <class HashedObj>
class HashTable
{
public:
	explicit HashTable(const HashedObj & notFound, int size = 2049);
	HashTable(const HashTable & rhs)
		: ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND),
		array(rhs.array), currentSize(rhs.currentSize) { }

	const HashedObj & find(const HashedObj & x, string str) const;
	const HashedObj & findIt(int kkk) const;

	void makeEmpty();
	void insert(const HashedObj & x, string str);
	void remove(const HashedObj & x, string str);

	const HashTable & operator=(const HashTable & rhs);

	enum EntryType { ACTIVE, EMPTY, DELETED };
	//private:
	struct HashEntry
	{
		HashedObj element;
		EntryType info;
		string element2 = "";
		HashEntry(const HashedObj & e = HashedObj(), EntryType i = EMPTY)
			: element(e), info(i) { }
	};

	std::vector<HashEntry> array;
	int currentSize;
	const HashedObj ITEM_NOT_FOUND;

	bool isActive(int currentPos) const;
	int findPos(const HashedObj & x, string str) const;
	int findPos2(const HashedObj & x) const;
	void rehash();
};

/**
* Construct the hash table.
*/
template <class HashedObj>
HashTable<HashedObj>::HashTable(const HashedObj & notFound, int size) :ITEM_NOT_FOUND(notFound), array(nextPrime(size))
{
	makeEmpty();
}

/**
* Insert item x into the hash table. If the item is
* already present, then do nothing.
*/
template <class HashedObj>
void HashTable<HashedObj>::insert(const HashedObj & x, string str)
{
	// Insert x as active
	int currentPos = findPos(x, str);
	if (isActive(currentPos))
		return;
	array[currentPos] = HashEntry(x, ACTIVE);
	array[currentPos].element2 = str;
	//cout << currentPos << " "<<isActive(currentPos) << " ";
	// Rehash; see Section 5.5
	if (++currentSize > array.size() / 2)
		rehash();
}

/**
* Expand the hash table.
*/
template <class HashedObj>
void HashTable<HashedObj>::rehash()
{
	std::vector<HashEntry> oldArray = array;

	// Create new double-sized, empty table
	array.resize(nextPrime(2 * oldArray.size()));
	for (int j = 0; j < array.size(); j++)
		array[j].info = EMPTY;

	// Copy table over
	currentSize = 0;
	for (int i = 0; i < oldArray.size(); i++)
		if (oldArray[i].info == ACTIVE)
			insert(oldArray[i].element, oldArray[i].element2);
}

/**
* Method that performs quadratic probing resolution.
* Return the position where the search for x terminates.
*/
template <class HashedObj>
int HashTable<HashedObj>::findPos(const HashedObj & x, string str) const
{
	int collisionNum = 0;
	int currentPos = hashFunction(str, array.size());

	while (array[currentPos].info != EMPTY &&
		array[currentPos].element2 != str)
	{
		currentPos += 1;  // Compute ith probe
		if (currentPos >= array.size())
			currentPos -= array.size();
	}

	return currentPos;
}


template <class HashedObj>
int HashTable<HashedObj>::findPos2(const HashedObj & x) const
{
	
	int currentPos = 0;

	while (	array[currentPos].element != x && currentPos <array.size()-1)
	{
		currentPos += 1;  // Compute ith probe

	}

	return currentPos;
}




/**
* Remove item x from the hash table.
*/
template <class HashedObj>
void HashTable<HashedObj>::remove(const HashedObj & x, string str)
{
	int currentPos = findPos(x, str);
	if (isActive(currentPos))
		array[currentPos].info = DELETED;
}

/**
* Find item x in the hash table.
* Return the matching item, or ITEM_NOT_FOUND, if not found.
*/
template <class HashedObj>
const HashedObj & HashTable<HashedObj>::find(const HashedObj & x, string str) const
{
	int currentPos = findPos(x, str);
	return isActive(currentPos) ? array[currentPos].element : ITEM_NOT_FOUND;
}

template <class HashedObj>
const HashedObj & HashTable<HashedObj>::findIt(int currentPos) const
{

	return isActive(currentPos) ? array[currentPos].element : ITEM_NOT_FOUND;
}


/**
* Make the hash table logically empty.
*/
template <class HashedObj>
void HashTable<HashedObj>::makeEmpty()
{
	currentSize = 0;
	for (int i = 0; i < array.size(); i++)
		array[i].info = EMPTY;
}

/**
* Deep copy.
*/
template <class HashedObj>
const HashTable<HashedObj> & HashTable<HashedObj>::
operator=(const HashTable<HashedObj> & rhs)
{
	if (this != &rhs)
	{
		array = rhs.array;
		currentSize = rhs.currentSize;
	}
	return *this;
}


/**
* Return true if currentPos exists and is active.
*/
template <class HashedObj>
bool HashTable<HashedObj>::isActive(int currentPos) const
{
	return array[currentPos].info == ACTIVE;
}

#endif

