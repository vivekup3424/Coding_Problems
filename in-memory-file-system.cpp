/**
 * The given problem asks for the design of a data structure that acts 
 * like an in-memory file system. This file system should be able to 
 * handle various commands similar to those found in a Unix-style 
 * file system. Specifically, the file system should:

    Initialize with no files or directories upon instantiation.
    List all the files and directories at a given directory path, 
    returned in lexicographic order.
    Create new directories given a path, and if necessary, create 
    any intermediate directories along that path.
    Add content to a file at a given path, creating the file if it 
    does not exist, or appending to it if it does.
    Read and return the content from a file at a given path.

The system must be able to distinguish between file and directory paths and perform actions accordingly.
*/

#include <bits/stdc++.h>
using namespace std;

//I am going to implement a trie data structure for this problem

class Trie{
public:
  string name; //name of the file or directory
  bool isFile;
  string content; //flag for the content if the thing is a file
  map<string, Trie*> children; //sorted map to store the child in lexographical orer
  Trie(): isFile(false), name(""){}
  ~Trie(){
    //memory clean up
    for(auto child : children){
      delete child.second;
    }
  }
  //method to search for a node using path
  Trie *search(string path){
    auto temp = this;

  }
};
//uses a tree(trie) data structure to manage file and directories;
class FileSystem{
private:
  Trie *root;
public:
  FileSystem(){
    root = new Trie();
  }
  ~FileSystem(){
    delete root;
  }
  vector<string> ls(string path){
    for(auto it : root.chilren)
  }
}
