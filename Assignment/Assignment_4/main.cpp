#include <iostream>
#include <fstream>
#include "trie.h"
using namespace std;

int main(int argc, char *argv[]) {
    fstream myFile;
    fstream myFileOut;
    myFile.open(argv[1],ios::in);
    myFileOut.open(argv[2],ios::out);
    string s;
    trie wordTrie;
    while (getline(myFile,s)){              //The part where I read the input line by line
        if (s[0] == 'i'){
            s.erase(0,7);
            int i = 0;
            string dothraki;
            string english;
            while (s[i] != ','){
                dothraki += s[i];
                i++;
            }
            i++;
            while (s[i] != ')'){
                english += s[i];
                i++;
            }
            if (wordTrie.search(dothraki) != 1){
                wordTrie.insert(dothraki,english);
                myFileOut << "\"" << dothraki << "\"" << " was added" << endl;
            }
            else if (wordTrie.search(dothraki) == 1 && wordTrie.searchWord(dothraki).value == english){
                myFileOut << "\"" << dothraki << "\"" << " already exists" << endl;
            }
            else if (wordTrie.search(dothraki) == 1 && wordTrie.searchWord(dothraki).value != english) {
                wordTrie.searchWord(dothraki).value = english;
                myFileOut << "\"" << dothraki << "\"" << " was updated" << endl;
            }
        }
        else if (s[0] == 's'){
            s.erase(0,7);
            int i = 0;
            string word;
            while (s[i] !=')'){
                word += s[i];
                i++;
            }
            if (wordTrie.search(word[0])){
                if (wordTrie.search(word) != -1){
                    string temp = wordTrie.searchWord(word).value;
                    if(wordTrie.search(word) == 1){
                        myFileOut << "\"The English equivalent is " << wordTrie.searchWord(word).value << "\"" << endl;
                    }
                    else{
                        myFileOut << "\"not enough Dothraki word\"" << endl;
                    }
                }
                else{
                    myFileOut << "\"incorrect Dothraki word\"" << endl;
                }
            }
            else{
                myFileOut << "\"no record\"" << endl;
            }
        }
        else if (s[0] == 'd'){
            s.erase(0,7);
            int i = 0;
            string word;
            while (s[i] !=')'){
                word += s[i];
                i++;
            }
            if (wordTrie.search(word[0])){
                if (wordTrie.search(word) != -1){
                    string temp = wordTrie.searchWord(word).value;
                    if(wordTrie.search(word) == 1){
                        wordTrie.deleteWord(word);
                        myFileOut << "\"" << word << "\" deletion is successful" << endl;
                    }
                    else{
                        myFileOut << "\"not enough Dothraki word\"" << endl;
                    }
                }
                else{
                    myFileOut << "\"incorrect Dothraki word\"" << endl;
                }
            }
            else{
                myFileOut << "\"no record\"" << endl;
            }
        }
        else if (s[0] == 'l'){
            myFileOut << "I couldn't write the list function so it doesn't give any output. " << endl;
        }
    }
    myFile.close();
    myFileOut.close();
    return 0;
}