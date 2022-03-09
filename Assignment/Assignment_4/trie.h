#include <iostream>
using namespace std;
class trie{
    const static int size = 26;
public:
    struct TrieNode{                            //This is the main structure I use for the trie construction
        struct TrieNode *children[size];
        char c;
        int endWord;
        string value;
    };
    static struct TrieNode *getNode(char k){    //The funciton to create a node
        TrieNode *toReturn =  new TrieNode;
        toReturn->c = k;
        toReturn->endWord = 0;

        for (int i = 0; i < size; i++)
            toReturn->children[i] = NULL;

        return toReturn;
    }
    TrieNode *root = getNode('\0');
    void insert(string key, string value){              //The function to insert a word to the trie with it's english meaning
        TrieNode *node = root;
        for (int i = 0; i < key.length(); i++){
            int index = key[i] - 'a';
            if (!node->children[index])
                node->children[index] = getNode(key[i]);

            node = node->children[index];
        }
        node->endWord = 1;
        node->value = value;
    }
    int search(string key){                         //I have made a different algorithm for storing the info which says if a node is the end of the word or not.
        TrieNode *toReturn = root;                    //This function searches and returns 0,1 or -1. This helps me to give different errors "Incorrect" and "Not enough"
        for (int i = 0; i < key.length(); i++){
            int index = key[i] - 'a';
            if (!toReturn->children[index])
                return -1;
            toReturn = toReturn->children[index];
        }
        return (toReturn->endWord);
    }
    struct TrieNode searchWord(string word){            //This is the function that finds wether a word is present in the trie or not and returns the last letter node of the word if it is.
        TrieNode *toReturn = root;
        for (int i = 0; i < word.length(); i++){
            int index = word[i] - 'a';
            if (!toReturn->children[index]){
                return *toReturn;
            }
            toReturn = toReturn->children[index];
        }
        return (*toReturn);
    }
    bool search(char key){                            //This function searches the trie for a specific letter and returns a boolean value in respect to whether that letter is present or not
        TrieNode *toReturn = root;
        int index = key - 'a';
        if (!toReturn->children[index])
            return false;
        else{
            return true;
        }
    }
    bool isEmpty(TrieNode* root){               //The function that checks if the root has any children
        for (int i = 0; i < size; i++)
            if (root->children[i])
                return false;
        return true;
    }
    TrieNode* remove(TrieNode* &root, string key, int depth = 0){       //The function that removes a word from the trie
        if (!root)
            return NULL;
        if (depth == key.size()) {
            if (root->endWord == 1){
                root->endWord = 0;
            }
            if (isEmpty(root)) {
                delete (root);
                root = NULL;
            }
            return root;
        }
        int index = key[depth] - 'a';
        root->children[index] = remove(root->children[index], key, depth + 1);
        if (isEmpty(root) && root->endWord == 0) {
            delete (root);
            root = NULL;
        }
        return root;
    }
    void deleteWord(string key){            //I couldn't access the root from the main function so I wrote a simple function to access is out of the class file
        remove(root,key);
    }
};