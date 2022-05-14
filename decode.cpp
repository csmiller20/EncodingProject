#include<iostream>
#include<fstream>
#include<string>
#include<string.h>
#include"defns.h"
using namespace std;

void merge(tree*,int,int,int);
void mergeSort(tree*, int, int);
void insertionSort(tree*, int);
void buildTree(tree*,tree,tree,int);
void writeEncoding(symbol*, symbol, string);
symbol advanceBit(symbol, int);

/*
-------------FILE FOLLOWS VERY SIMILAR STEPS TO encoding.cpp
-------------BUT FOLLOWS THE ENCODING DETAILS TO DECODE THE BINARY
 */

symbol* advanceBit(symbol* root, int bit){
  if(bit == 0){
    return root->left;
  }
  else{
    return root->right;
  }
}

void writeEncoding(symbol* symbols, symbol A, string bin){
  if(A.left == NULL || A.right == NULL){
    for(int i = 0; i < (signed)bin.length(); i++){
      symbols[(int)A.symbol].encoding[i] = bin.at(i);
    }
  }
  else{
    writeEncoding(symbols, *(A.left), bin+"0");
    writeEncoding(symbols, *(A.right), bin+"1");
  }
}

void buildTree(tree* treeArray, tree leftTree, tree rightTree, int k){
  symbol* newParent = new symbol;
  symbol* leftChild = new symbol;
  symbol* rightChild = new symbol;
  *leftChild = *leftTree.root;
  *rightChild = *rightTree.root;
  newParent->parent = NULL;
  newParent->left = leftChild;
  newParent->right = rightChild;
  newParent->freq = leftChild->freq + rightChild->freq;
  leftChild->parent = newParent;
  rightChild->parent = newParent;
  treeArray[k-1].freq = 0;
  treeArray[k].root = newParent;
  treeArray[k].freq = newParent->freq;
  
  
}

void insertionSort(tree* A, int n){
  for(int i = 1; i < n; i++){
    tree key = A[i];
    int j = i - 1;
    while(j >= 0 && A[j].freq >= key.freq){
      if(A[j].freq == key.freq){
	if(A[j].symbol > key.symbol){
	  A[j+1] = A[j];
	  j--;
	}else{
	  break;
	}
      }
      else{
	A[j+1] = A[j];
	j--;
      }
    }
    A[j+1] = key;
  }
}

void mergeSort(tree* A, int l, int r){
  if(l < r){
    int mid = (l+r)/2;
    mergeSort(A, l, mid);
    mergeSort(A, mid+1, r);
    merge(A, l, mid, r);
  }
}

void merge(tree* A, int l, int mid, int r){
  int n1 = mid-l+1;
  int n2 = r-mid;
  tree* leftA = new tree[n1+1];
  tree* rightA = new tree[n2+1];
  for(int i = 0; i <= n1; i++){
    leftA[i] = A[l+i];
  }
  for(int i = 0; i < n2; i++){
    rightA[i] = A[mid+i+1];
  }
  leftA[n1].freq = 10000;
  rightA[n2].freq = 10000;
  int i = 0;
  int j = 0;
  for(int k = l; k < r+1; k++){
    if(leftA[i].freq < rightA[j].freq){
      A[k] = leftA[i];
      i++;
    }
    else if(leftA[i].freq == rightA[j].freq){
      if(leftA[i].symbol <= rightA[j].symbol){
	A[k] = leftA[i];
	i++;
      }
      else{
	A[k] = rightA[j];
	j++;
      }
    }
    else{
      A[k] = rightA[j];
      j++;
    }
  }
}

int main(int argc, char** argv){
  
  string allInput;

  bool merge = false;
  
  symbol* symbols = new symbol[128];
  for(int i = 0; i < 128; i++){
    symbols[i].freq = 0;
    symbols[i].parent = NULL;
    symbols[i].left = NULL;
    symbols[i].right = NULL;
    symbols[i].symbol = (char) i;
  }
  ifstream preInput;
  preInput.open(argv[1], ifstream::in);
  int preChar;
  int inputFreq;
  while(preInput >> preChar){
    preInput >> inputFreq;
    symbols[preChar].symbol = (char) preChar;
    symbols[preChar].freq = inputFreq;
  }
  for(int i = 0; i < 128; i++){
    if(symbols[i].freq > 0){
      //cout << symbols[i].symbol << "\t" << symbols[i].freq << endl;
    }
  }
  
  tree* alpha = new tree[52];
  tree* nonAlpha = new tree[76];
  for(int i = 0; i < 52; i++){
    if(i > 25){
      alpha[i].index = i+71;
      alpha[i].freq = symbols[i+71].freq;
      alpha[i].symbol = symbols[i+71].symbol;
      alpha[i].root = &symbols[i+71];
    }
    else{
      alpha[i].index = i+65;
      alpha[i].freq = symbols[i+65].freq;
      alpha[i].symbol = symbols[i+65].symbol;
      alpha[i].root = &symbols[i+65];
    }
    
  }
  for(int i = 0; i < 76; i++){
    if(i < 65){
      nonAlpha[i].index = i;
      nonAlpha[i].freq = symbols[i].freq;
      nonAlpha[i].symbol = symbols[i].symbol;
      nonAlpha[i].root = &symbols[i];
    }
    else if(i < 71){
      nonAlpha[i].index = i+26;
      nonAlpha[i].freq = symbols[i+26].freq;
      nonAlpha[i].symbol = symbols[i+26].symbol;
      nonAlpha[i].root = &symbols[i+26];
    }
    else{
      nonAlpha[i].index = i+52;
      nonAlpha[i].freq = symbols[i+52].freq;
      nonAlpha[i].symbol = symbols[i+52].symbol;
      nonAlpha[i].root = &symbols[i+52];
    }
  }
  if(strcmp(argv[2], "insertion")==0){
    //cout << "insertion sorted\n";
    insertionSort(alpha, 52);
    insertionSort(nonAlpha, 76);
  }
  else if(strcmp(argv[2], "merge")==0){
    merge = true;
    //cout << "merge sorted\n";
    mergeSort(alpha, 0, 51);
    mergeSort(nonAlpha, 0, 75);
  }
  else{
    //cout << "not sorted\n";
  }
  //cout << "\n------------\n";
  /*for(int i = 0; i < 76; i++){
    cout << nonAlpha[i].symbol << "\t" << nonAlpha[i].freq << endl;
  }
  for(int i = 0; i < 52; i++){
    cout << alpha[i].symbol << "\t" << alpha[i].freq << endl;
  }*/

  //-------------------ENCODING---------------------------------------

  for(int i = 0; i < 51; i++){
    if(alpha[i].freq > 0){
      buildTree(alpha, alpha[i], alpha[i+1], i+1);
      if(merge){mergeSort(alpha, 0, 51);}
      else{insertionSort(alpha, 52);}
    }
  }


  for(int i = 0; i < 75; i++){
    if(nonAlpha[i].freq > 0){
      buildTree(nonAlpha, nonAlpha[i], nonAlpha[i+1], i+1);
      if(merge){mergeSort(nonAlpha, 0, 75);}
      else{insertionSort(nonAlpha, 76);}
    }
  }
 
  //cout << "\n\n" << alpha[51].freq << "\t" << nonAlpha[75].freq << endl;
  tree* bothTrees = new tree[2];
  bothTrees[0] = alpha[51];
  bothTrees[1] = nonAlpha[75];
  
  /*if(merge){mergeSort(bothTrees, 0, 1);}
    else{insertionSort(bothTrees, 2);}*/

  buildTree(bothTrees, bothTrees[0], bothTrees[1], 1);
  /*tree singleA = alpha[51];
  tree singleNA = nonAlpha[75];
  tree singleBinary;
  symbol treeRoot;
  treeRoot.freq = 0;
  treeRoot.left = NULL;
  treeRoot.right = NULL;
  treeRoot.parent = NULL;
  singleBinary.root = &treeRoot;
  singleBinary.freq = treeRoot.freq;
  treeRoot.left = singleA.root;
  treeRoot.right = singleNA.root;
  singleA.root->parent = &treeRoot;
  singleNA.root->parent = &treeRoot;
  */
  tree encodingTree = bothTrees[1];
  writeEncoding(symbols, *(encodingTree.root), "");

  
  for(int i  = 0; i < 128; i++){
    if(symbols[i].freq > 0){
      //cout << symbols[i].symbol << "\t" << symbols[i].encoding << endl;
    }
  }
  int numSyms = 0;
  string str;
  cin >> numSyms;
  for(int i = 0; i < numSyms+1; i++){
    getline(cin, str);
  }
  symbol* curSym = new symbol;
  curSym = encodingTree.root;
  if(symbols[10].freq > 0){
    getline(cin, str);
  }
  getline(cin, str);
  while(getline(cin, str)){
    for(int i = 0; i < (signed)str.length()+1; i++){
      if(i == (signed)str.length()){
	cout << curSym->symbol;
      }
      else{
      if(curSym->left == NULL && curSym->right == NULL){
	cout << curSym->symbol;
	curSym = encodingTree.root;
	curSym = advanceBit(curSym, str.at(i)-48);
      }
      else{
	curSym = advanceBit(curSym, str.at(i)-48);
      }
      }
    }
  }
  
  return 0;
}
