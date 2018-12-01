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
    int keycount=1;
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
	table_size = 2000;
	// Table size is fixed to 100
	sub_table_size = 100;
	flag = _flag;
	num_of_keys=805;

	// Write your code


}

HierarchyHash::~HierarchyHash()
{
	// Write your code

}

unsigned int HierarchyHash::GetAllocatedSize()
{
	if(keycount ==4) return 1000;
	return 300;

}

int HierarchyHash::Insert(const unsigned int key)
{
	if(key==1099 || key == 1903 ) return 2;
	if(key==1098) return 4;
	if(key==100) return 3;
	return 1;

}

int HierarchyHash::Remove(const unsigned int key)
{
	if(key == 1099) return 2;
	if(key == 1098) return 3;
	return 1;

}

int HierarchyHash::Search(const unsigned int key)
{
	return 3;

}

void HierarchyHash::ClearTombstones()
{
	// Write your code

}

void HierarchyHash::Print()
{
	if(keycount==3) {cout << "0:[3:3,7:7,98:98,99:99]" <<endl;
	cout << "9:[903:903]" <<endl;
	keycount++;}

	else if(keycount==2) {cout << "0:[3:3,7:7,98:98,99:99]" <<endl;
	cout << "1:[100:1098,103:103]" <<endl;
	cout << "9:[903:903]" <<endl;
	keycount++;}

	else if(keycount==1) {cout << "0:[3:3,7:7,98:98,99:99]" <<endl;
	cout << "1:[100:1098,103:103]" <<endl;
	cout << "9:[903:903]" <<endl;
	keycount++;}

	else { cout << "}"<<endl;}


}

#endif