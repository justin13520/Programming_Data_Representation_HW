/*Justin Liu, jl8wf   Date:10/7/2020    Filename: wordPuzzle.cpp */
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "hashTable.h"
#include "timer.h"
#include <cmath>
using namespace std;

#define MAXROWS 500
#define MAXCOLS 500
char grid[MAXROWS][MAXCOLS];


bool readInGrid(string filename, int& rows, int& cols) {
    // try to open the file
    ifstream file(filename);
    // upon an error, return false
    if (!file.is_open()) {
        return false;
    }

    // first comes the number of rows
    file >> rows;
    //cout << "There are " << rows << " rows." << endl;

    // then the columns
    file >> cols;
    //cout << "There are " << cols << " cols." << endl;

    // and finally the grid itself
    string data;
    file >> data;

    // close the file
    file.close();

    // convert the string read in to the 2-D grid format into the
    // grid[][] array.
    // In the process, we'll print the grid to the screen as well.
    int pos = 0; // the current position in the input data
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            grid[r][c] = data[pos++];
            //cout << grid[r][c];
        }
        //cout << endl;
    }
    return true;
}

/** This function will retrieve a word in a grid of letters in a given
 * direction.  If the end of the grid is encountered before the length
 * of the desired string is reached, then a shorter string will be
 * returned.  The data is retrieved from a global char grid[][]
 * array, which is assumed to be defined (and in scope).  NOTE: The
 * return value is a static string variable (for efficiency
 * reasons), so a successive return value will overwrite a previous
 * return value.
 *
 * @return A STATIC string containing the letters in the provided direction.
 * @param startRow The starting (row,col) position to find the word.
 * @param startCol The starting (row,col) position to find the word.
 * @param dir The direction to move: 0 is north (upwards), 1 is
 *            northeast, and it rotates around clockwise until it
 *            reaches 7 for northwest.
 * @param len The desired length of the string to return (assuming
 *            the edge of the grid is not reached--if the edge of the
 *            grid is reached, it will return as many characters as
 *            possible up to the edge of the grid, so the returned
 *            string may not have the same length as this parameter
 *            indicates).
 * @param numRows The number of rows in the global char grid[][]
 *                array.
 * @param numCols The number of columns in the global char grid[][]
 *                array.
 */

string getWordInGrid (int startRow, int startCol, int dir, int len,
                      int numRows, int numCols) {
    // the static-ness of this variable prevents it from being
    // re-declared upon each function invocation.  It also prevents it
    // from being deallocated between invocations.  It's probably not
    // good programming practice, but it's an efficient means to return
    // a value.
    static string output;
    output.clear(); // Since it's static we need to clear it
    output.reserve(256); // Can't set capacity in the constructor so do it the first time here

    // the position in the output array, the current row, and the
    // current column
    int r = startRow, c = startCol;
    // iterate once for each character in the output
    for (int i = 0; i < len; i++) {
        // if the current row or column is out of bounds, then break
        if (c >= numCols || r >= numRows || r < 0 || c < 0) {
            break;
        }

        // set the next character in the output array to the next letter
        // in the grid
        output += grid[r][c];

        // move in the direction specified by the parameter
        switch (dir) { // assumes grid[0][0] is in the upper-left
            case 0:
                r--;
                break; // north
            case 1:
                r--;
                c++;
                break; // north-east
            case 2:
                c++;
                break; // east
            case 3:
                r++;
                c++;
                break; // south-east
            case 4:
                r++;
                break; // south
            case 5:
                r++;
                c--;
                break; // south-west
            case 6:
                c--;
                break; // west
            case 7:
                r--;
                c--;
                break; // north-west
        }
    }

    return output;
}

int main(int argc, char* argv[]){
  timer t;
  int rows, cols;
  string grid(argv[2]);//gets grid filename
  //cout << grid << endl;//gets grid file
  bool result = readInGrid(grid,rows,cols);//prints grid if it exists
  int wordsInDict = 0;
  if (!result) {
        cout << "Error reading in file!" << endl;
        return 1;
   }
  
  
  string wordsFile(argv[1]);
  //cout << wordsFile << endl;
  ifstream words(wordsFile);

  // if(words.good()){
  //   cout << "good" << endl;
  // }
  
  for(string line; getline(words,line);){
    wordsInDict++;
  }
  //cout << wordsInDict << endl;
  //cout << "before" <<endl;
  hashTable h = hashTable(wordsInDict);

  words.clear();
  words.seekg(0, ios::beg);

  for(string line; getline(words,line);){
    h.insert(line,line);
  }
  
  //cout << "found status: " << h.found("sod") << endl;
  words.close();
  //cout << rows << "&" << cols << endl;
  //cout << getWordInGrid(0,3,2,3,500,500) << "'s length is: " << getWordInGrid(0,3,2,3,500,500).length()<< endl;
  vector<string> found = vector<string>();
  /*for(vector<string>::iterator itr = found.begin(); itr != found.end(); itr++){
    *itr = "";
    }*/

  int wordsFound = 0;

  t.start();
  
  for(int r = 0; r < rows; r++){
    for(int c = 0; c < cols; c++){
	for(int i = 0; i < 8;i++) {
	  int tempR = r;
	  int tempC = c;
	  for(int l = 1; l < 23; l++){
	     if(h.found(getWordInGrid(r, c, i, l, rows, cols)) && getWordInGrid(r,c,i,l,rows,cols).length() >= 3 ){
	       if(i == 0){
		 string w = "N (" + to_string(r) + ", " + to_string(c) + "):     " + getWordInGrid(r, c, i, l, rows, cols);
		 found.push_back(w);
	       }
	       if(i == 1){
		 string w = "NE (" + to_string(r) + ", " + to_string(c) + "):    " + getWordInGrid(r, c, i, l, rows, cols);
		 found.push_back(w);
	       }
	       if(i == 2){
		 string w = "E (" + to_string(r) + ", " + to_string(c) + "):     " + getWordInGrid(r, c, i, l, rows, cols);
		 found.push_back(w);
	       }
	       if(i == 3){
		 string w = "SE (" + to_string(r) + ", " + to_string(c) + "):    " + getWordInGrid(r, c, i, l, rows, cols);
		 found.push_back(w);
	       }
	       if(i == 4){
		 string w = "S (" + to_string(r) + ", " + to_string(c) + "):     " + getWordInGrid(r, c, i, l, rows, cols);
		 found.push_back(w);
	       }
	       if(i == 5){
		 string w = "SW (" + to_string(r) + ", " + to_string(c) + "):    " + getWordInGrid(r, c, i, l, rows, cols);
		 found.push_back(w);
	       }
	       if(i == 6){
		 string w = "W (" + to_string(r) + ", " + to_string(c) + "):     " + getWordInGrid(r, c, i, l, rows, cols);
		 found.push_back(w);
	       }
	       if(i == 7){
		 string w = "NW (" + to_string(r) + ", " + to_string(c) + "):    " + getWordInGrid(r, c, i, l, rows, cols);
		 found.push_back(w);
	       }
	      wordsFound++;
	  }
	     
	    switch (i) { // assumes grid[0][0] is in the upper-left
            case 0:
                tempR--;
                break; // north
            case 1:
                tempR--;
                tempC++;
                break; // north-east
            case 2:
	      
                tempC++;
                break; // east
            case 3:
                tempR++;
                tempC++;
                break; // south-east
            case 4:
                tempR++;
                break; // south
            case 5:
                tempR++;
                tempC--;
                break; // south-west
            case 6:
                tempC--;
                break; // west
            case 7:
                tempR--;
                tempC--;
                break; // north-west
	    }
	    //cout << "tempR is: "<<  tempR << " & tempC is: " << tempC << endl;
	    if(tempR >= rows || tempC >= cols || tempR < 0 || tempC < 0){
	      break;
	    }
       }
     }
   }
 }
  t.stop();
  for(int i = 0; i < found.size(); i++){
    if(found[i] == ""){
      break;
    }
    cout << found[i] << endl;
  }
  
  cout << wordsFound << " words found" << endl;
 return 0;
} 
