#ifndef FLATHASH_H
#define FLATHASH_H
#include <iostream>
using namespace std;

enum overflow_handle {
	LINEAR_PROBING = 0,
	QUDRATIC_PROBING = 1
};

class FlatHash
{private:
	unsigned int* hashtable;
	enum overflow_handle flag;
	unsigned int table_size;
	unsigned int num_of_keys;
    int *bucket = new int[1000];
    int keycount=0;
    int resizes=0;

public:
	FlatHash(enum overflow_handle _flag);
	~FlatHash();
	unsigned int HashFunction(const unsigned int key) { return key % table_size; }
	unsigned int GetTableSize() { return table_size; }
	unsigned int GetNumofKeys() { return num_of_keys; }
	int Insert(const unsigned int key);
	int Remove(const unsigned int key);
	int Search(const unsigned int key);
	void ClearTombstones();
	void Print();
};

FlatHash::FlatHash(enum overflow_handle _flag)
{   table_size = 1000;
	num_of_keys = 0;
	flag = _flag;
	for (int i=0; i<table_size; i++){bucket[i] = 0;}}

FlatHash::~FlatHash(){
	ClearTombstones();
	delete [] bucket;}

int FlatHash::Insert(const unsigned int key){
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


int FlatHash::Remove(const unsigned int key){
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

int FlatHash::Search(const unsigned int key){
	int check = 1;
	int j=1;
	int timecost=1;
	int fflag=0;
	int realkey = key % table_size;
	if (flag == 0){
        while (1){
        if( bucket[realkey] == key ) break;
            realkey = (key+j) % table_size;
            timecost++; j++; check ++;
        if(check == table_size) return 0; }}

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
                if(check == table_size) return 0;}}

    return timecost;
    }

void FlatHash::ClearTombstones(){
	for (int i=0; i < table_size; i++){
        if(bucket[i] > 1000000) bucket[i] = 0;}

	int arr[table_size];
        for (int i=0; i < table_size; i++){arr[i] = bucket [i];}
        for(int i=0; i< table_size; i++){bucket[i]= 0;}
        keycount = 0;
        for (int i=0; i < table_size; i++){ if(arr[i]!=0) Insert(arr[i]); }

}

void FlatHash::Print(){
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

#endif