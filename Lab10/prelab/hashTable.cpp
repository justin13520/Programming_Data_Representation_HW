/* Justin Liu, jl8wf    Date:11/5/2020    Filename: hashTable.cpp  */
#include "hashTable.h"
#include <iostream>
#include <vector>

using namespace std;

hashTable::hashTable(){
  table = vector<unsigned int>(96, 0);//96 possible characters
  
}

hashTable::~hashTable(){

}

unsigned int hashTable :: hash(char k){
  return k-31;//space has value of 32, so -31 gets it in index 1, 126-31 = 95
}

void hashTable::insert(char key){
  unsigned int hashKey = hash(key);
  table[hashKey]++;//increase frequency by 1
}

unsigned int hashTable::getFrequency(char key){
  unsigned int hashKey = hash(key);
  return table[hashKey];
}
