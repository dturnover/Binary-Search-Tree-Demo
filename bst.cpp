// Author : Desmond Turner
// Assignment : Lab 08
// Date : Spring 2019

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "BinarySearchTree.h"

using namespace std;

int buildTree (string filename, BinarySearchTree <string> * & BST);

int main(int argc, char * argv[])
{
  // Error Message
  if (argc < 3)
    {
      cout << "Usage: " << argv[0] << " <input-file> <output-file>\n";
      exit(1);
    }
  // Initiate output
  ofstream output (argv[2]);
  // Start time?
  double finish_time;
  double start_time = clock();
  // Initialize BST and build the tree
  BinarySearchTree <string> * words = new BinarySearchTree <string> ();
  int count = buildTree(argv[1], words);
  // Record time
  finish_time = clock();
  double time = (double) (finish_time - start_time) / CLOCKS_PER_SEC;
  // Initial message
  cout << "Total number of words:                  " << count << endl;
  cout << "Total number of disctinct words:        " << words->getSize() << endl;
  cout << "Time taken to build index using BST is: " << time << endl;
  cout << "Height of BST tree is:                  " << words->getHeight() << endl;
  // Repeatedly obtain user input
  char answer;
  string s;
  while (answer != '4')
    {
      cout << "Options: (1) display index, (2) search, (3) save index, (4) quit " << endl;
      cin >> answer;
      // Potential options
      switch (answer)
	{
	case '1':
	  words->printTree();
	  break;
	case '2':
	  cout << "Search word? ";
	  cin >> s;
	  cout << "Line numbers<BST>: ";
	  words->search(s);
	  cout << endl;
	  break;
	case '3':
	  words->printTree(output);
	  break;
	case '4':
	  break;
	default:
	  cout << "Not a valid option\n";
	}
    }
  // End everythin
  output.close();
  return 0;
}


int buildTree (string filename, BinarySearchTree <string> * & BST)
{
  // Initialize input and different variables
  ifstream input(filename.c_str());
  string word_string;
  int line = 1;
  char c;
  string single_word;
  int count = 0;
  // Grab each line from the input stream
  while (getline(input, word_string))
    {
      // Go through the currently selected line
      for (int i = 0; i < word_string.length(); i++)
	{
	  single_word = "";
	  c = word_string[i];
	  // Go through the current word
	  if (!isspace(c) and (isalpha(c) or isdigit(c)))
	    {
	      while (i < word_string.length() and !isspace(c) and (isalpha(c) or isdigit(c) or c == '-' or c == '\''))
		{
		  single_word += c;
		  i++;
		  c = word_string[i];
		}
	      // Increment the word count and insert the word into BST
	      count++;
	      BST->insert (single_word, line);
	    }
	}
      // Increment the line count
      line++;
    }
  // Close and end input and function
  input.close();
  return count;
}


