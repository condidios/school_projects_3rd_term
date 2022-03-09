#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <stack>
using namespace std;

class cases{                        //I have a class that has the different transitions rules as objects with their attributes.
public:
    string initialState,newState;
    char input,toPop,toPush;
};

bool checkIfIn(vector<string> v,string s){
    for(string k : v){
        if (s == k){
            return true;
        }
    }
    return false;
}                                                       //I wrote 2 functions to check if something is in a given vector. One for chars and one for strings.
bool checkIfIn(vector<char> v,char s){
    for(char k : v){
        if (s == k){
            return true;
        }
    }
    return false;
}
void reverseStack(stack<char> s,stack<char> &k){
    if (s.empty()){
        return;
    }
    stack<char> temp = s;
    char n = temp.top();
    temp.pop();
    k.push(n);
    reverseStack(temp,k);
}                                                       // I wrote a function to write the stack in the output file, and it uses another
string printStack(stack<char> s){                       // function which I wrote to reverse the stack in order to give right output.
    stack<char> tempStack;
    string toReturn;
    reverseStack(s,tempStack);
    int temp = tempStack.size();
    for (int i = 0; i < temp; ++i) {
        if (i > 0){
            toReturn+= ",";
        }
        toReturn+= tempStack.top();
        tempStack.pop();
    }
    return toReturn;
}
int main(int argc, char *argv[]) {
    fstream myOutputFile;
    myOutputFile.open(argv[3],ios::out);
    fstream myFile;
    myFile.open(argv[1],ios::in);
    string s;
    int counter = 0;
    vector<cases> caseArray;
    vector<string> stateCheck;
    string startState;
    vector<char> inputLib;
    vector<string> availableStates;
    vector<char> stackLib;
    vector<string> endState;
    while (getline(myFile,s)){                          //I used counters to understand which line I'm reading in order to get all given
        if (counter == 0){                                    // alphabets and hold them in vectors. Counter 0 is for all states, final states and start state
            int i = 2;
            string tempString;
            while (s[i] != '='){
                if (s[i] == ',' || s[i] == ' '){
                    stateCheck.push_back(tempString);
                    tempString = "";

                }
                if (s[i] != ','){
                    tempString.push_back(s[i]);
                }
                i++;
            }
            i += 4;
            while (s[i] != ')'){
                startState += s[i];
                i++;
            }
            i+=1;
            tempString = "";
            while (s.length() > i){
                if (s[i] != ',' && s[i] != ']' && s[i] != '[' ){
                    tempString += s[i];
                    i++;
                }
                else if (tempString.empty()){
                    i++;
                    continue;
                }
                else{
                    endState.push_back(tempString);
                    tempString = "";
                }
            }
            counter++;
        }
        else if (counter == 1){                     //Counter 1 is for input alphabet
            int i = 2;
            while (i < s.length()){
                if  (s[i] != ','){
                    inputLib.push_back(s[i]);
                    i++;
                    continue;
                }
                i++;
            }
            counter++;
        }
        else if (counter == 2){                     // Counter 2 is for stack alphabet
            int i = 2;
            while(i < s.length()){
                if (s[i] != ','){
                    stackLib.push_back(s[i]);
                    i++;
                }
                i++;
            }
            counter++;
        }
        else{                                      // After all the alphabets are created, in this part I create all the transition rules as objects and
            s.erase(0,2);                  // hold them in an array
            int n = s.size();
            char str[n];
            strcpy(str,s.c_str());
            char *ptr;
            ptr = strtok(str,",");
            cases tempCase;
            int counterTemp = 0;
            while (ptr!= NULL){
                if (counterTemp == 0){
                    tempCase.initialState = ptr;
                    availableStates.push_back(ptr);
                    counterTemp++;
                    ptr = strtok(NULL,",");
                    continue;
                }
                else if (counterTemp == 1 ){
                    tempCase.input = *ptr;
                    counterTemp++;
                    ptr = strtok(NULL,",");
                    continue;
                }
                else if (counterTemp == 2 ){
                    tempCase.toPop = *ptr;
                    counterTemp++;
                    ptr = strtok(NULL,",");
                    continue;
                }
                else if (counterTemp == 3){
                    tempCase.newState = ptr;
                    counterTemp++;
                    ptr = strtok(NULL,",");
                    continue;
                }
                else if (counterTemp == 4){
                    tempCase.toPush = *ptr;
                    counterTemp++;
                    ptr = strtok(NULL,",");
                    continue;
                }
            }
            caseArray.push_back(tempCase);
        }
    }
    for (cases k: caseArray){
        if (!checkIfIn(stateCheck,k.initialState) || !checkIfIn(stateCheck,k.newState)){
            myOutputFile << "Error [1]:DPDA description is invalid!" << endl;
            return 1;
        }                                                                               // This part terminates the code with respect to the given error handling rules.
        if (!checkIfIn(inputLib,k.input) && k.input != 'e'){
            myOutputFile << "Error [1]:DPDA description is invalid!" << endl;
            return 1;
        }
        if (!checkIfIn(stackLib,k.toPush) && k.toPush != 'e'){
            myOutputFile << "Error [1]:DPDA description is invalid!" << endl;
            return 1;
        }
    }
    myFile.close();
    myFile.open(argv[2],ios::in);
    while (getline(myFile,s)) {                         //In this part I start reading the input file in order to do the operations.
        stack<char> newStack;
        vector<char> inputList;
        vector<cases> usedCases;
        string currentCase = startState;
        int i = 0;
        while (i < s.size()) {
            for (char c: inputLib) {
                if (c == s[i]) {
                    inputList.push_back(s[i]);
                    i++;
                    continue;
                }
            }
            i++;
        }
        if (!inputList.empty()){                            //There are a lot of conditions in order to do right operations according to the inputs and the
            for (char c: inputList) {                      // state of the dpda.
                char caseInput;
                while (true) {
                    if (checkIfIn(availableStates,currentCase)){
                        for (cases k: caseArray) {
                            if (k.initialState == currentCase) {
                                if (k.input == c) {
                                    if (!newStack.empty()){
                                        if (k.toPop == newStack.top()) {
                                            newStack.pop();
                                            if (k.toPush != 'e') {
                                                currentCase = k.newState;
                                                newStack.push(k.toPush);
                                                caseInput = k.input;
                                                myOutputFile << k.initialState << "," << k.input << "," << k.toPop << " => "
                                                     << k.newState << "," << k.toPush << " [STACK]:" << printStack(newStack)
                                                     << endl;
                                                usedCases.push_back(k);
                                                break;
                                            } else if (k.toPush == 'e') {
                                                currentCase = k.newState;
                                                caseInput = k.input;
                                                myOutputFile << k.initialState << "," << k.input << "," << k.toPop << " => "
                                                     << k.newState << "," << k.toPush << " [STACK]:" << printStack(newStack)
                                                     << endl;
                                                usedCases.push_back(k);
                                                break;
                                            }
                                        } else if (k.toPop == 'e') {
                                            if (k.toPush != 'e') {
                                                currentCase = k.newState;
                                                newStack.push(k.toPush);
                                                caseInput = k.input;
                                                myOutputFile << k.initialState << "," << k.input << "," << k.toPop << " => "
                                                     << k.newState << "," << k.toPush << " [STACK]:" << printStack(newStack)
                                                     << endl;
                                                usedCases.push_back(k);
                                                break;
                                            } else {
                                                currentCase = k.newState;
                                                caseInput = k.input;
                                                myOutputFile << k.initialState << "," << k.input << "," << k.toPop << " => "
                                                     << k.newState << "," << k.toPush << " [STACK]:" << printStack(newStack)
                                                     << endl;
                                                usedCases.push_back(k);
                                                break;
                                            }
                                        }
                                    }
                                    else{
                                        if (k.toPop == 'e') {
                                            if (k.toPush != 'e') {
                                                currentCase = k.newState;
                                                newStack.push(k.toPush);
                                                caseInput = k.input;
                                                myOutputFile << k.initialState << "," << k.input << "," << k.toPop << " => "
                                                     << k.newState << "," << k.toPush << " [STACK]:" << printStack(newStack)
                                                     << endl;
                                                usedCases.push_back(k);
                                                break;
                                            } else {
                                                currentCase = k.newState;
                                                caseInput = k.input;
                                                myOutputFile << k.initialState << "," << k.input << "," << k.toPop << " => "
                                                     << k.newState << "," << k.toPush << " [STACK]:" << printStack(newStack)
                                                     << endl;
                                                usedCases.push_back(k);
                                                break;
                                            }
                                        }
                                    }
                                } else if (k.input == 'e') {
                                    if (!newStack.empty()) {
                                        if (k.toPop == newStack.top()) {
                                            newStack.pop();
                                            if (k.toPush != 'e') {
                                                currentCase = k.newState;
                                                newStack.push(k.toPush);
                                                caseInput = k.input;
                                                myOutputFile << k.initialState << "," << k.input << "," << k.toPop << " => "
                                                     << k.newState << "," << k.toPush << " [STACK]:" << printStack(newStack)
                                                     << endl;
                                                usedCases.push_back(k);
                                                break;
                                            } else if (k.toPush == 'e') {
                                                currentCase = k.newState;
                                                caseInput = k.input;
                                                myOutputFile << k.initialState << "," << k.input << "," << k.toPop << " => "
                                                     << k.newState << "," << k.toPush << " [STACK]:" << printStack(newStack)
                                                     << endl;
                                                usedCases.push_back(k);
                                                break;
                                            }
                                        } else if (k.toPop == 'e') {
                                            if (k.toPush != 'e') {
                                                currentCase = k.newState;
                                                newStack.push(k.toPush);
                                                caseInput = k.input;
                                                myOutputFile << k.initialState << "," << k.input << "," << k.toPop << " => "
                                                     << k.newState << "," << k.toPush << " [STACK]:" << printStack(newStack)
                                                     << endl;
                                                usedCases.push_back(k);
                                                break;
                                            } else {
                                                currentCase = k.newState;
                                                caseInput = k.input;
                                                myOutputFile << k.initialState << "," << k.input << "," << k.toPop << " => "
                                                     << k.newState << "," << k.toPush << " [STACK]:" << printStack(newStack)
                                                     << endl;
                                                usedCases.push_back(k);
                                                break;
                                            }
                                        }
                                    } else {
                                        if (k.toPop == 'e') {
                                            if (k.toPush != 'e') {
                                                currentCase = k.newState;
                                                newStack.push(k.toPush);
                                                caseInput = k.input;
                                                myOutputFile << k.initialState << "," << k.input << "," << k.toPop << " => "
                                                     << k.newState << "," << k.toPush << " [STACK]:" << printStack(newStack)
                                                     << endl;
                                                usedCases.push_back(k);
                                                break;
                                            } else {
                                                currentCase = k.newState;
                                                caseInput = k.input;
                                                myOutputFile << k.initialState << "," << k.input << "," << k.toPop << " => "
                                                     << k.newState << "," << k.toPush << " [STACK]:" << printStack(newStack)
                                                     << endl;
                                                usedCases.push_back(k);
                                                break;
                                            }
                                        }

                                    }
                                }
                            }
                        }
                        if  (c == caseInput){
                            break;
                        }
                    }
                    else{
                        break;
                    }

                }
            }
            for(cases k: caseArray){
                if (k.input == 'e' && k.initialState == usedCases.at(usedCases.size()-1).newState){
                    if (!newStack.empty()){
                        if (newStack.top() == k.toPop){
                            if (k.toPop != '$'){
                                newStack.pop();
                            }
                            if (k.toPush == 'e'){
                                currentCase = k.newState;
                                myOutputFile << k.initialState << "," << k.input << "," << k.toPop << " => "
                                     << k.newState << "," << k.toPush << " [STACK]:" << printStack(newStack)
                                     << endl;
                            }
                            else if (k.toPush == '$'){
                                currentCase = k.newState;
                                myOutputFile << k.initialState << "," << k.input << "," << k.toPop << " => "
                                     << k.newState << "," << k.toPush << " [STACK]:" << printStack(newStack)
                                     << endl;
                            }
                            else{
                                newStack.push(k.toPush);
                                currentCase = k.newState;
                                myOutputFile << k.initialState << "," << k.input << "," << k.toPop << " => "
                                     << k.newState << "," << k.toPush << " [STACK]:" << printStack(newStack)
                                     << endl;
                            }
                        }
                        else if (k.toPop == 'e'){
                            if (k.toPush == 'e'){
                                currentCase = k.newState;
                                myOutputFile << k.initialState << "," << k.input << "," << k.toPop << " => "
                                     << k.newState << "," << k.toPush << " [STACK]:" << printStack(newStack)
                                     << endl;
                            }
                            else if (k.toPush == '$'){
                                currentCase = k.newState;
                                myOutputFile << k.initialState << "," << k.input << "," << k.toPop << " => "
                                     << k.newState << "," << k.toPush << " [STACK]:" << printStack(newStack)
                                     << endl;
                            }
                            else{
                                newStack.push(k.toPush);
                                currentCase = k.newState;
                                myOutputFile << k.initialState << "," << k.input << "," << k.toPop << " => "
                                     << k.newState << "," << k.toPush << " [STACK]:" << printStack(newStack)
                                     << endl;
                            }
                        }
                    }
                    else{
                        if (k.toPop == 'e') {
                            if (k.toPush != 'e') {
                                currentCase = k.newState;
                                newStack.push(k.toPush);
                                myOutputFile << k.initialState << "," << k.input << "," << k.toPop << " => "
                                     << k.newState << "," << k.toPush << " [STACK]:" << printStack(newStack)
                                     << endl;
                            }
                            else {
                                currentCase = k.newState;
                                myOutputFile << k.initialState << "," << k.input << "," << k.toPop << " => "
                                     << k.newState << "," << k.toPush << " [STACK]:" << printStack(newStack)
                                     << endl;
                            }
                        }
                    }
                }
            }

        }
        if (checkIfIn(endState,currentCase)){                   //This part decides whether the last output wil be accept or reject.
            if (newStack.size() == 1 && newStack.top() == '$'){      // It checks the condition of the current state and the contents of the stack.
                myOutputFile << "ACCEPT" << endl;
            }
            else if (newStack.empty()){
                myOutputFile << "ACCEPT" << endl;
            }
            else {
                myOutputFile << "REJECT" << endl;
            }
        }
        else{
            myOutputFile << "REJECT" << endl;
        }
        myOutputFile << endl;
    }
    myFile.close();
    return 0;
}