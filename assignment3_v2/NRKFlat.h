#ifndef NRKFLAT_H
#define NRKFLAT_H

#include "FlatHash.h"
#include <iostream>
#include <stdint.h>

using namespace std;


#define INT2VOIDP(i) (void*)(uintptr_t)(i)

class NRKFlat : public FlatHash
{
private:
	unsigned int* hashtable;
	enum overflow_handle flag;
	unsigned int table_size;
	unsigned int num_of_keys;
    int *bucket = new int[1000];
    int keycount=0;
    int resizes=0;

	unsigned int* counters;

public:
	NRKFlat(enum overflow_handle _flag);

	~NRKFlat();

	unsigned int MurmurHash2(const void* key);

	void GetMMHashValue(const unsigned int key, int& h1, int& h2, int& h3);

	bool Filter(const unsigned int key);
	int Insert(const unsigned int key);
	int Remove(const unsigned int key);
	int Search(const unsigned int key);
	void ClearTombstones();
	void Print();
};

NRKFlat::NRKFlat(enum overflow_handle _flag) : FlatHash(_flag)
{
	table_size = 1000;
	num_of_keys = 0;
	flag = _flag;
	for (int i=0; i<table_size; i++){bucket[i] = 0;}

}

NRKFlat::~NRKFlat()
{
	ClearTombstones();
	delete [] bucket;

}

unsigned int NRKFlat::MurmurHash2(const void* key){
	int len = 4;
	unsigned int seed = 2018;

	const unsigned int m = 0x5bd1e995;
	const int r = 24;

	unsigned int h = seed ^ len;

	const unsigned char * data = (const unsigned char *)key;

	while(len >= 4)
	{
		unsigned int k = *(unsigned int *)data;

		k *= m;
		k ^= k >> r;
		k *= m;

		h *= m;
		h ^= k;

		data += 4;
		len -= 4;
	}

	switch(len)
	{
	case 3: h ^= data[2] << 16;
	case 2: h ^= data[1] << 8;
	case 1: h ^= data[0];
	        h *= m;
	};

	h ^= h >> 13;
	h *= m;
	h ^= h >> 15;

	return h;
}

void NRKFlat::GetMMHashValue(const unsigned int key, int& h1, int& h2, int& h3)
{
	// You can use h1, h2 and h3 as hashing results which you have to use to decide counter locations
	h1 = MurmurHash2(INT2VOIDP(&key));
	h2 = MurmurHash2(INT2VOIDP(&h1));
	h3 = MurmurHash2(INT2VOIDP(&h2));
}

bool NRKFlat::Filter(const unsigned int key)
{
	// You can use h1, h2 and h3 as hashing results which you have to use to decide counter locations
	int h1, h2, h3;
	GetMMHashValue(key, h1, h2, h3);

	// Write your code


}

int NRKFlat::Insert(const unsigned int key)
{
	if ( key <= 0 || key >1000000){return 0;}
    int j = 1, fflag=0, timecost=1;
	int realkey = key % table_size;
	keycount ++;
	if (flag == 0){
        while (1){
        if( bucket[realkey] == 0){bucket[realkey] = key; break;}
            realkey = (key+j) % table_size;
            timecost++; j++;
            }}

	else {
        while (1){
        if( bucket[realkey] == 0){ bucket[realkey] = key; break;}
            realkey = (key+j*j) % table_size;
            timecost++; j++;
            if( j > (table_size-1)) {fflag=1; realkey = key % table_size; break;}}

            j=0;

            while(fflag == 1){
                if( bucket[realkey] == 0){ bucket[realkey] = key; break;}
                    realkey = (key+j) %table_size;
                    timecost++; j++; }}

	if (keycount > ((table_size)*0.8) ){
            int* newArr = new int[table_size + 1000];
            int arr[1000];
            for (int i=0; i < table_size; i++){arr[i] = bucket [i];}
            table_size+=1000;
            delete [] bucket;
            bucket = newArr;

            for(int i=0; i< table_size; i++){bucket[i]= 0;}
            keycount = 0;
            for (int i=0; i < table_size-1000; i++){if(arr[i]!=0){Insert(arr[i]);} }
	}
return timecost;

}

int NRKFlat::Remove(const unsigned int key)
{
	int j = 1, fflag=0, timecost=1;
	keycount--;
	int realkey = key % table_size;
	if (flag == 0){
        while (1){
        if( bucket[realkey] == key ){bucket[realkey] = 0; break;}
            realkey = (key+j) % table_size;
            timecost++; j++; }

        int arr[table_size];
        for (int i=realkey; i < table_size; i++){arr[i] = bucket [i];}
        for(int i=realkey; i< table_size; i++){if(bucket[i]!=0){keycount--; bucket[i]=0;}}
        for (int i=realkey; i < table_size; i++){ if(arr[i]!=0) Insert(arr[i]);}
    }

	else{
	    while (1){
        if( bucket[realkey] == key){ bucket[realkey] += 1000000; break;}
            realkey = (key+j*j) % table_size;
            timecost++; j++;
            if( j > (table_size-1)) {fflag=1; realkey = key%table_size; break;}}
            j=0;
            while(fflag == 1){
                if( bucket[realkey] == key){ bucket[realkey] += 1000000; break;}
                    realkey = (key+j) % table_size;
                    timecost++; j++; }}

    return timecost;
}



int NRKFlat::Search(const unsigned int key)
{
	int check = 1;
	int j=1;
	int timecost=1;
	int fflag=0;
	int realkey = key % table_size;
	if (flag == 0){
        while (1){
        if( bucket[realkey] == key ) break;
            realkey = (key+j) % table_size;
            timecost++; j++;check ++;
            if(check == table_size) return 0;
            }}

	else{
	    while (1){
        if( bucket[realkey] == key) break;
            realkey = (key+j*j) % table_size;
            timecost++; j++;
            if( j > (table_size-1)) {fflag=1; realkey = key%table_size; break;}}
            j=0;
            while(fflag == 1){
                if( bucket[realkey] == key) break;
                    realkey = (key+j) % table_size;
                    timecost++; j++; check ++;
                if(check == table_size) return 0; }}

    return timecost;

}

void NRKFlat::Print(){
	std::cout << "[";
    int check=0;
    for(int i=0; i<= table_size; i++){
        if (bucket[i] > 0 && bucket[i] < 1000000 ){
            check++;
            if (check != keycount) cout << i <<":" << bucket[i]<<",";
            else cout << i <<":" << bucket[i];
        }
    }
	std::cout << "]" << std::endl;
}

void NRKFlat::ClearTombstones(){
	for (int i=0; i < table_size; i++){
        if(bucket[i] > 1000000) bucket[i] = 0;}

	int arr[table_size];
        for (int i=0; i < table_size; i++){arr[i] = bucket [i];}
        for(int i=0; i< table_size; i++){bucket[i]= 0;}
        keycount = 0;
        for (int i=0; i < table_size; i++){ if(arr[i]!=0) Insert(arr[i]); }

}


#endif
