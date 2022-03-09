#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

string* split(string& uzun){                // The method to split commands
    string* toReturn = new string[100];
    stringstream ss(uzun);
    string word;
    int i = 0;
    while (ss >> word) {
        toReturn[i] = word;
        ++i;
    }
    return toReturn;
}
bool checkIfIn(vector<vector<int>> &grid, vector<int> vectorTemp){      //The method where I check if an element is in a 2d array
    for(vector<int> vector : grid){
        if (vector[0] == vectorTemp[0] && vector[1] == vectorTemp[1]){
            return false;
        }
    }
    return true;
}
void checkBalloon(vector<vector<int>> &coords,vector<vector<int>> &grid, int gridSize, int x_coord, int y_coord){       //Recursive function for finding the linking
    vector<int> temp1 = {x_coord,y_coord};                                                                              //balloons with the same value
    if (checkIfIn(coords,temp1)){
        coords.push_back(temp1);
    }
    if (x_coord-1 >= 0){
        if(x_coord-1 >= 0 && grid[x_coord][y_coord] == grid[x_coord-1][y_coord]){
            vector<int> temp = {x_coord-1,y_coord};
            if (checkIfIn(coords, temp)){
                coords.push_back(temp);
                checkBalloon(coords,grid, gridSize, x_coord-1, y_coord);
            }
        }
    }
    if (x_coord +1 < gridSize)   {
        if(x_coord +1 < gridSize && grid[x_coord][y_coord] == grid[x_coord + 1][y_coord]) {
            vector<int> temp = {x_coord + 1, y_coord};
            if (checkIfIn(coords, temp)){
                coords.push_back(temp);
                checkBalloon(coords,grid, gridSize, x_coord+1, y_coord);
            }
        }
    }
    if (y_coord-1 >= 0){
        if(y_coord-1 >= 0 && grid[x_coord][y_coord] == grid[x_coord][y_coord-1]) {
            vector<int> temp = {x_coord , y_coord-1};
            if (checkIfIn(coords, temp)){
                coords.push_back(temp);
                checkBalloon(coords,grid, gridSize, x_coord, y_coord-1);
            }
        }
    }
    if (y_coord+1 < gridSize){
        if(y_coord+1 < gridSize && grid[x_coord][y_coord] == grid[x_coord][y_coord+1]) {
            vector<int> temp = {x_coord, y_coord+1};
            if (checkIfIn(coords, temp)){
                coords.push_back(temp);
                checkBalloon(coords,grid, gridSize, x_coord, y_coord+1);
            }
        }
    }
}
void addBalloon(vector<vector<int>> &grid, int grid_size, int x_coord, int y_coord, int value){     //Recursive method for adding balloons to the grid. It is recursive
    grid[x_coord][y_coord] = value;                                                                 //because when I combine balloons I use this function again in order
    vector<vector<int>> coords;                                                                     //to combine new set of balloons if there is one.
    checkBalloon(coords,grid,grid_size,x_coord,y_coord);
    if (coords.size() > 2){
        for(std::vector<int> vector2 : coords){
            grid[vector2[0]][vector2[1]] = 0;
        }
        addBalloon(grid,grid_size,x_coord,y_coord,value + 1);
    }
}
int main(int argc, char *argv[]) {
    int grid_size;
    int grid_size2;
    vector<vector<int>> grid;
    vector<vector<int>> grid2;
    fstream file;
    string inputLine;
    int counter = 0;
    int counter2 = 0;
    file.open(argv[1]);
    while (getline(file, inputLine)) {      //While loop I used to read the first input file line by line. I do all of my operations in
        if (counter == 0) {                       // this while loop while reading the input. My operations work for every line individually.
            grid_size = stoi(inputLine);
            for (int i = 0; i < stoi(inputLine); ++i) {
                vector<int> temp;
                for (int j = 0; j < stoi(inputLine); ++j) {
                    temp.push_back(0);
                }
                grid.push_back(temp);
            }
            counter++;
            continue;
        }
        addBalloon(grid, grid_size, stoi(split(inputLine)[1]), stoi(split(inputLine)[2]), stoi(split(inputLine)[0]));
    }
    file.close();

    //The part where I read the second input file for part 2

    file.open(argv[2]);
    int point = 0;
    getline(file, inputLine);
    if (counter2 == 0) {
        grid_size2 = stoi(inputLine);
        counter2++;
    }
    for (int i = 0; i < grid_size2 && getline(file, inputLine); i++) {
        vector<int> temp;
        for (int j = 0; j < grid_size2; ++j) {
            temp.push_back(stoi(split(inputLine)[j]));
        }
        grid2.push_back(temp);
    }
    while (getline(file, inputLine)) {            //While loop I use to pop balloons in the same row, column and diagonals of the given squares value
        int x_coord = stoi(split(inputLine)[0]);
        int y_coord = stoi(split(inputLine)[1]);
        int k = grid2[x_coord][y_coord];
        if (k == 6) {
        }
        for (int x = 0; x < grid_size2; x++) {
            if (grid2[x][y_coord] == k) {
                grid2[x][y_coord] = 0;
                point += k;
            }
            if (grid2[x_coord][x] == k) {
                grid2[x_coord][x] = 0;
                point += k;
            }
        }
        for (int x = x_coord, y = y_coord; x > -1 && y < grid_size2; ++y, --x) {
            if (grid2[x][y] == k) {
                grid2[x][y] = 0;
                point += k;
            }
        }
        for (int x = x_coord, y = y_coord; x < grid_size2 && y < grid_size2; ++y, ++x) {
            if (grid2[x][y] == k) {
                grid2[x][y] = 0;
                point += k;
            }
        }
        for (int x = x_coord, y = y_coord; x < grid_size2 && y > -1; --y, ++x) {
            if (grid2[x][y] == k) {
                grid2[x][y] = 0;
                point += k;
            }
        }
        for (int x = x_coord, y = y_coord; x > -1 && y > -1; --y, --x) {
            if (grid2[x][y] == k) {
                grid2[x][y] = 0;
                point += k;
            }
        }
    }
    file.close();

    //The part where I start writing my output to a .txt file

    file.open(argv[3]);
    file << "PART 1:" << endl;
    for (vector<int> vector: grid) {
        for (int i = 0; i < grid_size; ++i) {
            file << vector[i] << " ";
        }
        file << endl;
    }
    file << endl;
    file << "PART 2:" << endl;
    for (vector<int> vector: grid2) {
        for (int i = 0; i < grid_size2; ++i) {
            file << vector[i] << " ";
        }
        file << endl;
    }
    file << endl;
    file << "Final Point: " << point << "p";
    file.close();
    return 0;
}