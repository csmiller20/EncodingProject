#include<fstream>
#include<string.h>
#include<iostream>
#include"defns.h"
#include<string>

using namespace std;

void merge(tree*,int,int,int);
void mergeSort(tree*, int, int);
void insertionSort(tree*, int);
void buildTree(tree*,tree,tree,int);
void writeEncoding(symbol*, symbol, string);

//WRITES THE ENCODING FOR THE GIVEN SYMBOLS TREE NODE BY
//RECURSIVELY ADDING ON 0's WHEN MOVING LEFT AND 1's
//WHEN MOVING RIGHT TO THE BINARY STRING
void writeEncoding(symbol* symbols, symbol A, string bin){
  //CHECKS FOR LEAF NODE
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

//TRAVERSES DOWN THE SORTED ARRAY AND CREATES NEW PARENT NODES
void buildTree(tree* treeArray, tree leftTree, tree rightTree, int k){
  symbol* newParent = new symbol;
  symbol* leftChild = new symbol;
  symbol* rightChild = new symbol;
  *leftChild = *leftTree.root;
  *rightChild = *rightTree.root;
  newParent->parent = NULL;
  newParent->left = leftChild;
  newParent->right = rightChild;
  //THE NEW NODE'S FREQUENCY IS THE SUM OF THE OF THE
  //TWO SUBTREES ROOT'S FREQUENCY
  newParent->freq = leftChild->freq + rightChild->freq;
  newParent->symbol = -1;
  leftChild->parent = newParent;
  rightChild->parent = newParent;
  //THE LAST ELEMENT IN THE SORTED ARRAY IS SET TO 0, SO IT IS IGNORED
  treeArray[k-1].freq = 0;
  //THE CURRENT ELEMENT IS SET TO BE THE NEWLY CREATED PARENT NODE 
  treeArray[k].root = newParent;
  treeArray[k].freq = newParent->freq;
  
  
}

//IMPLEMENTATION OF INSERTION SORT FOR AN ARRAY OF TREES/SUBTREES
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

//IMPLEMENTATION OF MERGE SORT FOR AN ARRAY OF TREES/SUBTREES
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
      if(leftA[i].symbol >= rightA[j].symbol || leftA[i].symbol == -1){
	A[k] = rightA[j];
	j++;
      }
      
      else{
	A[k] = leftA[i];
	i++;
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

  //SYMBOLS ARRAY IS INITIALIZED
  symbol* symbols = new symbol[128];
  for(int i = 0; i < 128; i++){
    symbols[i].freq = 0;
    symbols[i].parent = NULL;
    symbols[i].left = NULL;
    symbols[i].right = NULL;
    symbols[i].symbol = (char) i;
  }

  //CHARACTERS IN THE GIVEN FILE ARE READ AND PUT IN AN ALPHABETICAL
  //TREE ARRAY AND A NON-ALPHABETICAL TREE ARRAY
  char fileChar;
  allInput += (char) cin.peek();
  while(cin.get(fileChar)){
    int fileSym = (int) fileChar;
    symbols[fileSym].freq++;
    allInput += (char) cin.peek();
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

  //CHECKS IF COMMAND LINE ARGUEMENT ASKS FOR THE CHARACTERS
  //TO BE INSERTION OR MERGE SORTED (MERGE SORTED BY DEFAULT)
  if(strcmp(argv[2], "insertion")==0){
    insertionSort(alpha, 52);
    insertionSort(nonAlpha, 76);
  }
  else{
    merge = true;
    mergeSort(alpha, 0, 51);
    mergeSort(nonAlpha, 0, 75);
  }

  //-------------------ENCODING---------------------------------------

  //CALLS THE SORT FUNCTIONS EACH TIME A NEW NODE IS CREATED BY buildTree()
  for(int i = 0; i < 51; i++){
    if(alpha[i].freq > 0){
      
      if(merge){mergeSort(alpha, 0, 51);}
      else{insertionSort(alpha, 52);}
      buildTree(alpha, alpha[i], alpha[i+1], i+1);
      if(merge){mergeSort(alpha, 0, 51);}
      else{insertionSort(alpha, 52);}
    }
  }


  for(int i = 0; i < 75; i++){
    if(nonAlpha[i].freq > 0){
      
      if(merge){mergeSort(nonAlpha, 0, 75);}
      else{insertionSort(nonAlpha, 76);}
      buildTree(nonAlpha, nonAlpha[i], nonAlpha[i+1], i+1);
      if(merge){mergeSort(nonAlpha, 0, 75);}
      else{insertionSort(nonAlpha, 76);}
    }
  }
 
  //COMBINES THE TWO TREES WITH THE ALPHABETICAL CHARACTERS IN THE RIGHT SUBTREE
  tree* bothTrees = new tree[2];
  bothTrees[0] = alpha[51];
  bothTrees[1] = nonAlpha[75];
  
  if(merge){mergeSort(nonAlpha, 0, 75);}
      else{insertionSort(nonAlpha, 76);}
  buildTree(bothTrees, bothTrees[0], bothTrees[1], 1);

  //WRITES THE BINARY ENCODING OF THE FINAL TREE IN FULL
  tree encodingTree = bothTrees[1];
  writeEncoding(symbols, *(encodingTree.root), "");

  int sum = 0;
  for(int i = 0; i < 128; i++){
    if(symbols[i].freq > 0){
      sum++;
    }
  }
  cout << sum << endl;
  for(int i  = 0; i < 128; i++){
    if(symbols[i].freq > 0){
      cout << (int)symbols[i].symbol << "\t" << symbols[i].symbol << "\t" << symbols[i].encoding << endl;
    }
  }
  cout << endl;
  
  //PRINTS THE ENCODING OF THE FILE
  for(int i = 0; i < (signed)allInput.length(); i++){
    cout << symbols[(int)allInput.at(i)].encoding;
   
  }
  return 0;
}
