 #include "bits/stdc++.h" 
 #include <iostream>
 #include <fstream>
using namespace std; 

// structure for trie node which contains 2 maps and 1 boolean
struct TrieNode {  
	map<char, TrieNode*> children; 
	bool isEndOfWord; 
	map<char, int> num; 
}; 
// global variable root which contains the head of the trie
struct TrieNode* root; 

//Method to create a new trie node
struct TrieNode* getNewTrieNode() 
{ 
	struct TrieNode* pNode = new TrieNode; 
	pNode->isEndOfWord = false; 
	return pNode; 
} 

// method for inserting the word into the trie
void insertWord(std::vector<string>& words) 
{ 
	
	struct TrieNode* current = root; 
    int size = stoi(words[1]);
    string word = words[0];
	char s; 

	for (int i = 0; i < word.length(); i++) { 
		s = word[i]; 

		if (current->children.find(s) 
			== current->children.end()) { 
 
			struct TrieNode* p = getNewTrieNode(); 

			(current->children)[s] = p; 

			(current->num)[s] = size; 
		} 
		else {  
			current->num[s] = (current->num)[s] + size; 
		}  
		current = (current->children)[s]; 
	} 
	current->isEndOfWord = true; 
} 

 
// method for checking the if the trie contains that word if yes then 
// return the frequency of that letter otherwise 0
int countWords(std::vector<std::vector<string>>& words, 
			string prefix) 
{ 
	root = getNewTrieNode(); 

	int n = words.size(); 

	for (int i = 0; i < n; i++) { 
		insertWord(words[i]); 
	} 

	struct TrieNode* current = root; 
	char s; 
 
	int wordCount = 0; 

	for (int i = 0; prefix[i]; i++) { 
		s = prefix[i]; 

		if (current->children.find(s) 
			== current->children.end()) { 
			wordCount = 0; 
			break; 
		} 

		wordCount = (current->num)[s]; 

		current = (current->children)[s]; 
	} 
    for (auto i : current->num) 
        wordCount-=i.second;
	return wordCount; 
} 


// main driver function to run the code 
int main() 
{ 
    // making the object to read the data form csv file

	ifstream myFile;
	myFile.open("EnglishDictionary.csv");
	std::vector<std::vector<string>> vec; // vector of vector for all the string in the csv file

	// taking input and entering into vector
	while(myFile.good())
	{
		string line;
		getline(myFile, line, '\n');
		char char_array[line.size() + 1]; 
		strcpy(char_array, line.c_str()); 
		char *token = strtok(char_array, ","); 
    
    std::vector<string> v;
    while (token != NULL) 
    { 
        v.push_back(token); 
        token = strtok(NULL, ","); 
    }
    vec.push_back(v);
	}

	string prefix;
	cin>>prefix; 
    // getting ans if ans less than equal to 0 then string does not exist 
    // and if greater than zero than string exists and ans contains its frequency
	int ans = countWords(vec, prefix); 
	if(ans<=0)
		cout<<"NO";
	else
		cout<<"YES, "<<ans;
	return 0; 
} 
