#include<fstream>
#include<string>
#include<iostream>
#include"defns.h"
using namespace std;
int main(int argc, char** argv){
  //AN ARRAY OF ALL OF THE ASCII SYMBOLS ARE INITIALIZED
  symbol* symbols = new symbol[128];
  for(int i = 0; i < 128; i++){
    symbols[i].freq = 0;
    symbols[i].parent = NULL;
    symbols[i].left = NULL;
    symbols[i].right = NULL;
    symbols[i].symbol = (char) i;
  }

  //FILE AND ITS CHARACTERS ARE READ FROM STDIN
  //AND EACH SYMBOL'S FREQUENCY IS COUNTED 
  char fileLine;
  while(cin.get(fileLine)){
    int fileSym = (int) fileLine;
    symbols[fileSym].freq++;
  }
  //PRINTS ALL THE SYMBOLS PRESENT IN THE FILE
  for(int i = 0; i < 128; i++){
    if(symbols[i].freq > 0){
      cout << (int) symbols[i].symbol << "\t" << symbols[i].freq << "\n";
    }
  }
  return 0;
}
