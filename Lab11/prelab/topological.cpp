//Justin Liu, jl8wf      Date:11/12/2020     Filename: topological.cpp
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <map>
#include "gNode.h"
using namespace std;

// we want to use parameters
/**
 *@brief This is the main cpp. There should be always be a file input.
 */
int main(int argc, char* argv[]) {
    // verify the correct number of parameters
    if (argc != 2) {
        cout << "Must supply the input file name as the one and only parameter" << endl;
        exit(1);
    }

    // attempt to open the supplied file
    ifstream file(argv[1], ifstream::binary);
    /// report any problems opening the file and then exit 
    if (!file.is_open()) {
        cout << "Unable to open file '" << argv[1] << "'." << endl;
        exit(2);
    }
    string s1, s2;
    map<string,gNode*> courses;

    // read in two strings
    while(file >> s1 >> s2){
      if(s1 == "0" || s2 == "0"){
	continue;
      }
      else{
	map<string,gNode*>::iterator it1 = courses.find(s1);
	map<string,gNode*>::iterator it2 = courses.find(s2);
	if(it1 == courses.end()){
	  gNode* course = new gNode(s1);//make a node for new course found
	  courses.insert(pair<string,gNode*>(s1,course));
	}
	if(it2 == courses.end()){
	  gNode* course = new gNode(s2);//make a node for new course found
	  courses.insert(pair<string,gNode*>(s2,course));
	}
	//cout << s1 << " ";
	//cout << s2 << endl;
      }
    }
    for(pair<string,gNode*> key : courses){//checks if the map has all the things
      //cout << "Element in map: " << key.second->getCourse() << endl;
    }

    file.clear(); // Clears the _state_ of the file, not its contents!
    file.seekg(0);//goes back to the top
    
    while(file >> s1 >> s2){
      if(s1 == "0" || s2 == "0"){
	continue;
      }
      else{
	map<string,gNode*>::iterator it1 = courses.find(s1);
	map<string,gNode*>::iterator it2 = courses.find(s2);
	if(it2 != courses.end()){//updates the inDegree of the course
	  it1->second->addPtr(it2->second);
	  it2->second->inDegreeInc();
	}
      }
    }
    vector<gNode*> idZero = vector<gNode*>();
    for(pair<string,gNode*> key : courses){//checks if the courses have correct inDegrees
      //cout << "Indegree of " << key.first << ": " << key.second->getInDegree() << endl;
      if(key.second->getInDegree() == 0){
	idZero.push_back(key.second);//has all the ones with zero inDegree
      }
    }

    while(!courses.empty()){
      if(!idZero.empty()){
	gNode* v = idZero[0];
	
	//cout << "Starting" << endl;
	
	if(idZero.size() == 1){
	  
	  cout << idZero[0]->getCourse() << " ";
	  
	  for(int i = 0; i < v->getOutwardPtrs().size(); i++){//goes through 0 inDegree pointees and decrements their inDegree
	    v->getOutwardPtrs()[i]->inDegreeDec();//for each pointer in the outward pointers
	    if(v->getOutwardPtrs()[i]->getInDegree() == 0)//if it equals 0, then add it to the 0 vector
	      idZero.push_back(v->getOutwardPtrs()[i]);
	  }
	  map<string,gNode*>::iterator it = courses.find(v->getCourse());
	  idZero.erase(idZero.begin());
	  delete it->second;
	  courses.erase(it);
	}
	else{
	  int index;
	  for(int i = 0; i < idZero.size(); i++){//find the first in lexigraphical order
	    if(v->getCourse() > idZero[i]->getCourse()){
	      v = idZero[i];
	      index = i;
	    }
	  }
	  
	  cout << v->getCourse() << " ";
	  
	  for(int i = 0; i < v->getOutwardPtrs().size(); i++){//goes through 0 inDegree pointees and decrements their inDegree
	     v->getOutwardPtrs()[i]->inDegreeDec();//for each pointer in the outward pointers
	     if(v->getOutwardPtrs()[i]->getInDegree() == 0)//if it equals 0, then add it to the 0 vector
		idZero.push_back(v->getOutwardPtrs()[i]);
	  }

	  map<string,gNode*>::iterator it = courses.find(v->getCourse());
	  vector<gNode*>::iterator del = find(idZero.begin(),idZero.end(),v);
	  idZero.erase(del);
	  delete it->second;
	  courses.erase(it);
	}
      }
	else{
	  break;
	}
      }
    cout << endl;
    
    // close the file before exiting
    file.close();
}

