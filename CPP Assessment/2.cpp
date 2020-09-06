// CPP program to display content of Trie 
#include <iostream> 
#include <string.h> 
#include "bits/stdc++.h" 
 #include <iostream>
 #include <fstream>
using namespace std; 
#define alpha_size 256 
#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0]) 

using namespace std; 

// structure for creation of trie node
struct TrieNode 
{ 
    struct TrieNode* children[alpha_size]; 

    bool isLeaf; 
}; 

 // method to create a trie node 
struct TrieNode* createNode() 
{ 
    struct TrieNode* pNode = new TrieNode; 

    for (int i = 0; i < alpha_size; i++) 
        pNode->children[i] = NULL; 

    pNode->isLeaf = false; 

    return pNode; 
}; 

// inssert function to insert word into the trie
void insert_node(struct TrieNode* root, char* key) 
{ 
    int level; 
    int length = strlen(key); 
    struct TrieNode* pCrawl = root; 
    
    for (level = 0; level < length; level++) 
    { 
        int index = key[level]; 
        if (pCrawl->children[index] == NULL) 
            pCrawl->children[index] = createNode(); 
        pCrawl->isLeaf = false;
        pCrawl = pCrawl->children[index]; 
    } 


    pCrawl->isLeaf = true;
    
} 

// checking if the the node is the leaf node or not
bool isLeafNode(struct TrieNode* root) 
{ 
    return root->isLeaf != false; 
} 

// traversing the trie and print the user input leaf node string
void display(struct TrieNode* root, char str[], int level,int n,int *count) 
{ 
    // checking if the node is the leaf node
    if (isLeafNode(root)) 
    { 
        ++*count;
        str[level] = '\0';
        if(*count==n)
        { 
        cout << str << endl;
         exit(0);  
  
        } 

    } 
    //traversing all the string in the trie
    int i; 
    for (i = 65; i < 123 ; i++) 
    { 
        if (root->children[i]) 
        { 
            str[level] = i; 
            // recursive call to print the strings
            display(root->children[i], str, level + 1,n,count); 
        } 
    } 
} 

// main function to run the code
int main() 
{ 
    // making the object to read the data form csv file
    ifstream myFile;
    
    myFile.open("EnglishDictionary.csv");
    
    std::vector<string> vec;     // vector for all the string in the csv file
    
    // taking input and entering into vector
    while(myFile.good())
    {
        string line;
        getline(myFile, line, '\n');
        char char_array[line.size() + 1]; 
        strcpy(char_array, line.c_str()); 
        char *token = strtok(char_array, ","); 
    
    while (token != NULL) 
    { 
        vec.push_back(token); 
        token = strtok(NULL, ","); 
    }
    }


    // making the root Node
    struct TrieNode* root = createNode(); 

    // adding all the string to the vector using insert method
    for (int j = 0; j < vec.size(); j++)
    { 
        int n = vec[j].size();
        char char_array[n + 1];
        insert_node(root, strcpy(char_array, vec[j].c_str())); 
    }

    int level = 0; 
    char str[256]; 
    int n;
    cin>>n;
    int count = -1;
    // printing the i leaf node string
    display(root, str, level,n,&count); 
} 
