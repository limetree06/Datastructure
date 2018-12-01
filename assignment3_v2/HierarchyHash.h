#ifndef HIERARCHYHASH_H
#define HIERARCHYHASH_H

#include <iostream>
#include "FlatHash.h"
using namespace std;


class HierarchyHash
{
private:
	unsigned int** hashtable;
	enum overflow_handle flag;
	unsigned int table_size;
	unsigned int sub_table_size;
	unsigned int num_of_keys;
    int keycount=0;
    int resizes=0;

public:
	HierarchyHash(enum overflow_handle _flag);

	~HierarchyHash();

	unsigned int HashFunction(const int key) { return key % table_size; }

	unsigned int GetTableSize() { return table_size; }

	unsigned int GetNumofKeys() { return num_of_keys; }

	// Return the size of allocated sub hash table
	unsigned int GetAllocatedSize();

	// Return time cost
	int Insert(const unsigned int key);

	// Return time cost
	int Remove(const unsigned int key);

	// Return time cost
	int Search(const unsigned int key);

	// Delete tombstomes
	void ClearTombstones();

	void Print();
};

HierarchyHash::HierarchyHash(enum overflow_handle _flag)
{
	// Initial map size is 1000
	table_size = 1000;
	// Table size is fixed to 100
	sub_table_size = 100;
	flag = _flag;

	// Write your code


}

HierarchyHash::~HierarchyHash()
{
	// Write your code

}

unsigned int HierarchyHash::GetAllocatedSize()
{
	return keycount;

}

int HierarchyHash::Insert(const unsigned int key)
{
	return 1;

}

int HierarchyHash::Remove(const unsigned int key)
{
	return 1;

}

int HierarchyHash::Search(const unsigned int key)
{
	return 1;

}

void HierarchyHash::ClearTombstones()
{
	// Write your code

}

void HierarchyHash::Print()
{
	cout << "[]" <<endl;


}

#endif
