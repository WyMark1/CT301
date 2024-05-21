#include <iostream>
#include <fstream>
#include <string>
#include "game_of_life.h"

using namespace std;
//Wyatt Markham
//wymark

/*customMod*/
//Input: two constant ints a and b
//Output: a int that is a%b but if a is negitive it is b-a
//A custom modulo function that when given a negitive number outputs such that customMod(-1,5) = 4 used to help with wraping calculations
int customMod(const int &a, const int &b) {
    return (a % b + b) % b;
}

/*GetGenerations*/
//Input: none
//Output: a int that is num_gens
//A getter method to get num_gens
int game_of_life::GetGenerations() {
    return num_gens;
}

/*NextGen*/
//Input: none
//Output: none
//This function computes the next generation of john conways game of life
//If a cell has less than two neighbors it dies, If it has two neighbors it stays alive and 
//if a cell has exactly 3 neighbors then a dead cell becomes a live cell and a live cell stays alive, and anything else it dies
//This implemenation uses wrap around meaning if you have a cell on the right side it is neighbors with the left size or if at the top neighbors with the bottom
//This is implemented by finding the neighbors around the current cell then it counts how many live cells are around it and then aplies the rules above.  
void game_of_life::NextGen() {
    string next_gen(width*height, dead_cell);
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            int num_nieghbors = 0; 
            int curr_index = col+(row*width);
            int curr_row = curr_index; // Current middle point of row
            for (int i=0; i < 3; ++i) {
                if (curr_row != curr_index) { // If it is the current cell don't add it to num_neighbors
                    if (curr_gen[curr_row]==live_cell) ++num_nieghbors; // Middle cell
                }
                if (curr_gen[customMod(curr_row+1,width)+(width*(curr_row/width))]==live_cell) // Right cell
                    ++num_nieghbors;
                if (curr_gen[customMod(curr_row-1,width)+(width*(curr_row/width))]==live_cell) // Left cell
                    ++num_nieghbors;
                if (i==0) curr_row = customMod(curr_index+width,(width*height)); // Bottom row
                if (i==1) curr_row = customMod(curr_index-width,(width*height)); // Top Row
            }
           
            if (num_nieghbors<2) { // Are there less then 2 neighbors then underpopulation
                next_gen[curr_index] = dead_cell;
            } else if (num_nieghbors == 2 && curr_gen[curr_index] == live_cell) { // Have two neighbors then sustain
                next_gen[curr_index] = live_cell;
            } else if(num_nieghbors == 3) { // Have three neighbors or dead cell then sustain or rebirth
                next_gen[curr_index] = live_cell;
            } else { // More than three neighbors over population
                next_gen[curr_index] = dead_cell;
            }
        }
    }
    curr_gen = next_gen;
    ++num_gens;
}

/*NextNGen*/
//Input: n
//Output: none
//Calls NextGen n times
void game_of_life::NextNGen(int n) {
    for(int i = 0; i < n; ++i) {
        NextGen();
    }
}

/*SetLiveCell*/
//Input: a char that is the new live cell
//Output: none
//Checks if the new live cell is the same as the dead cell and if so throw an error
//Then it replaces all instances of the old live cell with the new one in curr_gen then set the live_cell = to the new cell
void game_of_life::SetLiveCell(char cell) {
    if (dead_cell == cell)
        throw runtime_error(cell_dupe_error);
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            if (curr_gen[col+(row*width)] == live_cell)
                curr_gen[col+(row*width)] = cell;
        }
    }
    live_cell = cell;
}

/*SetDeadCell*/
//Input: a char that is the new dead cell
//Output: none
//Checks if the new dead cell is the same as the live cell and if so throw an error
//Then it replaces all instances of the old dead cell with the new one in curr_gen then set the dead_cell = to the new cell
void game_of_life::SetDeadCell(char cell) {
    if (live_cell == cell)
        throw runtime_error(cell_dupe_error);
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            if (curr_gen[col+(row*width)] == dead_cell)
                curr_gen[col+(row*width)] = cell;
        }
    }
    dead_cell = cell;
}

/*operator+*/
//Input: a int gens which is the numebr of generations to calculate
//Output: the current object
//Calls NextNGen gens times
game_of_life& game_of_life::operator+(int gens) {
    NextNGen(gens);
    return *this;
}

/*operator++*/
//Input: none
//Output: the current object
//Calls NextGen once to iterate it then returns 
game_of_life& game_of_life::operator++() {
    NextGen();
    return *this;
}

/*operator++*/
//Input: int
//Output: a copy of the object before iterating
//Calls NextGen once to iterate it then returns the object before iterating it
game_of_life game_of_life::operator++(int) {
    const auto copy = *this;
    NextGen();
    return copy;
}

/*ToString*/
//Input: none
//Output: a string which has the game table and the number of generations computed
//Formats a string based on the current game table and the numebr of generations
string game_of_life::ToString() const {
    string out = "Generation: ";
    out += to_string(this->num_gens);
    out += '\n';
    for (int row = 0; row < this->height; ++row) {
        for (int col = 0; col < this->width; ++col) {
            out += this->curr_gen[col+(row*this->width)];
        }
        out += '\n';
    }
    return out;
}

/*operator<<*/
//Input: ostream and game_of_life object
//Output: a ostream that has the game of life in it
//Calls ToString and sends it to an ostream
std::ostream & operator<<(std::ostream &os, const game_of_life &game) {
    return os << game.ToString();
}

/*game_of_life*/
//Input: filename, chars for the live and dead cells and the number of generations to compute before running
//Output: none
//Checks if the filename leads to an actual file then checks if the file is formated correctly then checks if the live and dead cell charaters are the same
//Then it sets the width and height, live_cell, and dead_cell variables. Then it instantiates the curr_gen variable as an array of width*height size filled with dead cells
//It then loops through every line in the file and fills in the curr_gen array after that it runs the number of pregens specified
game_of_life::game_of_life(string filename, char live, char dead, int pregens) {
    string line;
    ifstream file_in(filename);
    if (!file_in)
        throw runtime_error(file_not_found_error + filename + error_end);
    file_in >> width >> height; 
    if (!file_in)
        throw runtime_error(invalid_read_error + filename + error_end);
    if (dead == live)
        throw runtime_error(cell_dupe_error);
    live_cell = live;
    dead_cell = dead;
    string defualt_gen(width*height, dead_cell);
    curr_gen = defualt_gen;
    getline(file_in, line);
    for (int row = 0; file_in && row < height; ++row) { 
        getline(file_in, line);
        for (int col = 0; col < width; ++col) {
            if (line[col] == '*') {
                curr_gen[col+(row*width)] = live_cell;
            }
        }
    }
    NextNGen(pregens);
}

/*game_of_life*/
//Input: filename, chars for the live and dead cells
//Output: none
//Calls the first constructor but pregens = 0
game_of_life::game_of_life(string filename, char live, char dead) : game_of_life(filename, live, dead, 0) {}

/*game_of_life*/
//Input: filename and the number of generations to compute before running
//Output: none
//Calls the first constructor but live cell = * and dead cell = -
game_of_life::game_of_life(string filename, int pregens) : game_of_life(filename, '*', '-', pregens) {}

/*game_of_life*/
//Input: filename
//Output: none
//Calls the first constructor but live cell = * and dead cell = - and pregens = 0
game_of_life::game_of_life(string filename) : game_of_life(filename, '*', '-', 0) {}