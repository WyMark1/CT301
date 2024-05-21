#include <iostream>
#include <fstream>
#include <string>
#include "game_of_life.h"

using namespace std;
//Wyatt Markham
//wymark

/** customMod
 * A custom modulo function that when given a negitive number outputs such that customMod(-1,5) = 4 used to help with wraping calculations 
*/
int customMod(const int &a, const int &b) {
    return (a % b + b) % b;
}

/** GetStruct
 * creats a game_save_struct out of the current game
*/
game_of_life::game_save_state game_of_life::GetStruct() {
    game_save_state curr;
    curr.game_board = curr_gen;
    curr.width = width;
    curr.height = height;
    curr.generation = num_gens;
    curr.live = live_cell;
    curr.dead = dead_cell;
    return curr;
}

/** ChangeState
 * changes the game to save
*/
void game_of_life::ChangeState(game_save_state save) {
    curr_gen = save.game_board;
    width = save.width;
    height = save.height;
    num_gens = save.generation; 
    live_cell = save.live;
    dead_cell = save.dead;
    for (int i = num_gens; i < 100; ++i) {
        saved_games[i] = game_save_state();
    }
}

/** NumLive
 * counts the number of live cells in the current game
*/
int game_of_life::NumLive() const {
    int num_live = 0; 
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            if (curr_gen[col+(row*width)] == live_cell) num_live++;
        }
    }
    return num_live;
}

/** New
 * changes the game to become a new one 
*/
void game_of_life::New(string game, int height_, int width_) {
    for (int i = 0; i < num_gens_saved; ++i) {
        saved_games[i] = game_save_state();
    }
    num_gens_saved = 0;
    num_gens = 0;
    curr_gen = game;
    width = width_;
    height = height_;
}

/** SimulateNext
 * it is nextGen() but it dosen't change the state of the game
*/
string game_of_life::SimulateNext() const {
    string next_gen(width*height, dead_cell);
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            int num_nieghbors = 0; 
            int curr_index = col+(row*width);
            int curr_row = curr_index; // Current middle point of row
            for (int i = 0; i < 3; ++i) {
                if (curr_row != curr_index) { // If it is the current cell don't add it to num_neighbors
                    if (curr_gen[curr_row] == live_cell) ++num_nieghbors; // Middle cell
                }
                if (curr_gen[customMod(curr_row+1, width) + (width*(curr_row/width))] == live_cell) // Right cell
                    ++num_nieghbors;
                if (curr_gen[customMod(curr_row-1, width) + (width*(curr_row/width))] == live_cell) // Left cell
                    ++num_nieghbors;
                if (i == 0) curr_row = customMod(curr_index+width, (width*height)); // Bottom row
                if (i == 1) curr_row = customMod(curr_index-width, (width*height)); // Top Row
            }
           
            if (num_nieghbors < 2) { // Are there less then 2 neighbors then underpopulation
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
    return next_gen;
}

/** GetGenerations
 * A getter method to get num_gens
*/
int game_of_life::GetGenerations() const {
    return num_gens;
}

/** NextGen
 * This function computes the next generation of john conways game of life
 * If a cell has less than two neighbors it dies, If it has two neighbors it stays alive and 
 * if a cell has exactly 3 neighbors then a dead cell becomes a live cell and a live cell stays alive, and anything else it dies
 * This implemenation uses wrap around meaning if you have a cell on the right side it is neighbors with the left size or if at the top neighbors with the bottom
 * This is implemented by finding the neighbors around the current cell then it counts how many live cells are around it and then aplies the rules above.  
*/
void game_of_life::NextGen() {
    game_save_state curr = GetStruct();
    if (num_gens_saved == 100) {
        for (int i = 0; i < 99; ++i) {
            saved_games[i] = saved_games[i+1];
        }
        saved_games[99] = curr;
    } else {
        num_gens_saved++;
        saved_games[num_gens_saved-1] = curr;
    }

    string next_gen(width*height, dead_cell);
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            int num_nieghbors = 0; 
            int curr_index = col+(row*width);
            int curr_row = curr_index; // Current middle point of row
            for (int i = 0; i < 3; ++i) {
                if (curr_row != curr_index) { // If it is the current cell don't add it to num_neighbors
                    if (curr_gen[curr_row] == live_cell) ++num_nieghbors; // Middle cell
                }
                if (curr_gen[customMod(curr_row+1, width) + (width*(curr_row/width))] == live_cell) // Right cell
                    ++num_nieghbors;
                if (curr_gen[customMod(curr_row-1, width) + (width*(curr_row/width))] == live_cell) // Left cell
                    ++num_nieghbors;
                if (i == 0) curr_row = customMod(curr_index+width, (width*height)); // Bottom row
                if (i == 1) curr_row = customMod(curr_index-width, (width*height)); // Top Row
            }
           
            if (num_nieghbors < 2) { // Are there less then 2 neighbors then underpopulation
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

/** NextNGen
 * Calls NextGen n times
*/
void game_of_life::NextNGen(int n) {
    for(int i = 0; i < n; ++i) {
        NextGen();
    }
}

/** SetLiveCell
 * Checks if the new live cell is the same as the dead cell and if so throw an error
 * Then it replaces all instances of the old live cell with the new one in curr_gen then set the live_cell = to the new cell
*/
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

/** SetDeadCell
 * Checks if the new dead cell is the same as the live cell and if so throw an error
 * Then it replaces all instances of the old dead cell with the new one in curr_gen then set the dead_cell = to the new cell
*/
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

/** operator-
 * rolls back the game gens number of generations
*/
game_of_life game_of_life::operator-(int gens) {
    if (gens < 0) {
        throw runtime_error("game_of_life - operator-(int) - Negative gens not allowed\n");
    } else if (num_gens_saved == 0) {
        throw domain_error("game_of_life - operator-(int) - No avaliable gens to roll back to.\n");
    } else if (num_gens_saved < gens) {
        throw range_error("game_of_life - operator-(int) - Not enough gens to roll back "+to_string(gens)+" gens.\n");
    }
    game_of_life game = *this;
    
    game.ChangeState(saved_games[(num_gens - (num_gens % num_gens_saved)) - gens]);
    game.num_gens_saved -= gens;
    return game;
}

/** operator+
 * Calls NextNGen gens times on a copy of the current game
*/
game_of_life game_of_life::operator+(int gens) {
    if (gens < 0) {
        return *this - abs(gens);
    }
    game_of_life game = *this;
    game.NextNGen(gens);
    return game;
}

/** operator++
 * Calls NextGen once to iterate it then returns 
*/
game_of_life& game_of_life::operator++() {
    NextGen();
    return *this;
}

/** operator++
 * Calls NextGen once to iterate it then returns the object before iterating it
*/
game_of_life game_of_life::operator++(int) {
    const auto copy = *this;
    NextGen();
    return copy;
}

/** operator-=
 * subtract operator but it dose it to the current game
*/
game_of_life& game_of_life::operator-=(int gens) {
    if (gens < 0) {
        throw runtime_error("game_of_life - operator-=(int) - Negative gens not allowed\n");
    } else if (num_gens_saved == 0) {
        throw domain_error("game_of_life - operator-=(int) - No avaliable gens to roll back to.\n");
    } else if (num_gens_saved < gens) {
        throw range_error("game_of_life - operator-=(int) - Not enough gens to roll back "+to_string(gens)+" gens.\n");
    }
    ChangeState(saved_games[num_gens - gens]);
    num_gens_saved -= gens;
    return *this;
}

/** operator+=
 * addition operator but it dose it to the current game
*/
game_of_life& game_of_life::operator+=(int gens) {
    if (gens < 0) {
        return *this -= abs(gens);
    }
    NextNGen(gens);
    return *this;
}

/** operator--
 * -= operator but with a value of 1
*/
game_of_life& game_of_life::operator--() {
    if (num_gens_saved < 1)
        throw domain_error("game_of_life - operator--() - No avaliable gens to roll back to.\n");
    return *this -= 1;
}

/** operator--
 * -= operator but with a value of 1 and returns a copy of the game before
*/
game_of_life game_of_life::operator--(int fake) {
    if (num_gens_saved < 1)
        throw domain_error("game_of_life - operator--(int) - No avaliable gens to roll back to.\n");
    const auto copy = *this;
    *this -= 1;
    return copy;
}

/** operator==
 * compares a ratio of live cells in the current game to another game and sees if they are equal to each other within .05
*/
bool game_of_life::operator==(game_of_life& rhs) {
    double lhs_cells = width * height;
    double rhs_cells = rhs.width * rhs.height;
    double lhs_ratio = NumLive() / lhs_cells;
    double rhs_ratio = rhs.NumLive() / rhs_cells;
    if (abs(lhs_ratio - rhs_ratio) <= .05) return true;
    return false;
}

/** operator<
 * compares a ratio of live cells in the current game to another game and detrimines if the current game is less than the other game
*/
bool game_of_life::operator<(game_of_life& rhs) {
    double lhs_cells = width * height;
    double rhs_cells = rhs.width * rhs.height;
    double lhs_ratio = NumLive() / lhs_cells;
    double rhs_ratio = rhs.NumLive() / rhs_cells;
    if (lhs_ratio < rhs_ratio) return true;
    return false;
}

/** operator<=
 * calls the < operator and == operator if both false return false
*/
bool game_of_life::operator<=(game_of_life& rhs) {
    if (*this < rhs ) return true;
    else if (*this == rhs) return true;
    return false;
}

/** operator>
 * calls the <= operator and if false return true
*/
bool game_of_life::operator>(game_of_life& rhs) {
    return !(*this <= rhs);
}

/** operator>=
 * calls the > operator and == operator if both false return false
*/
bool game_of_life::operator>=(game_of_life& rhs) {
    if (*this > rhs ) return true;
    else if (*this == rhs) return true;
    return false;
}

/** GenWindow
 * creates a window into the current game starting at row,col and going down height_ and right width_
*/
string game_of_life::GenWindow(int row, int col, int height_, int width_) {
    if (height_ > height || width_ > width) {
        throw domain_error("game_of_life - GenWindow(int,int,int,int) - Width or Height Out of Bounds for height: "+to_string(height_)+", width: "+to_string(width_)+", Max values are height: "+to_string(height)+", width: "+to_string(width)+".\n");
    } else if (row > height-1 || col > width-1) {
        throw range_error("game_of_life - GenWindow(int,int,int,int) - Index Out of Bounds for row: "+to_string(row)+", coloumn: "+to_string(col)+", Max values are row: "+to_string(height)+", col: "+to_string(width)+".\n");
    } 
    string window(width_ * height_, dead_cell);
    for (int i = 0; i < height_; ++i) {
        int curr_row = (row + i) % height;
        for (int j = 0; j < width_; ++j) {
            int curr_col = col + j;
            window[j + (i * width_)] = curr_gen[(curr_col % width) + (width * curr_row)];
        }
    }
    return window;
}

/** GenSubGame
 * gets a string for the sub game from GenWindow then creates a copy of the current game then replaces all data in the copy with the sub game data
*/
game_of_life game_of_life::GenSubGame(int row, int col, int height_, int width_) {
    string game = GenWindow(row, col, height_, width_);
    game_of_life copy = *this;
    copy.New(game, height_, width_);
    return copy;
}

/** ToggleCell
 * checks index of the game board and inverts it
*/
void game_of_life::ToggleCell(int index) {
    size_t temp = index;
    if (temp >= curr_gen.length()) {
        throw range_error("game_of_life - ToggleCell(int) - Index Out of Bounds for index "+to_string(index)+", Max value is index "+to_string(curr_gen.length())+".\n");
    }
    if (curr_gen[index] == dead_cell) curr_gen[index] = live_cell;
    else curr_gen[index] = dead_cell;
}

/** ToggleCell
 * calls ToggleCell(index) where index is computed from row and col
*/
void game_of_life::ToggleCell(int row, int col) {
    if (row >= height || col >= width) {
        throw range_error("game_of_life - ToggleCell(int,int) - Index Out of Bounds for row: "+to_string(row)+", coloumn: "+to_string(col)+", Max values are row: "+to_string(height)+", col: "+to_string(width)+".\n");
    }
    ToggleCell((row*width)+col);
}

/** IsStillLife
 * checks if the next generation will be the same as the current one
*/
bool game_of_life::IsStillLife() const {
    string next_gen = SimulateNext();
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            if (curr_gen[col+(row*width)] != next_gen[col+(row*width)]) return false;
        }
    }
    return true;
}

/** GetAvailableGens
 * returns the number of generations that have been saved
*/
int game_of_life::GetAvailableGens() const {
    return num_gens_saved;
}

/** operator<<
 * prints the current generation number then prints the game board
*/
ostream & operator<<(ostream &os, const game_of_life &game) {
    os << "Generation: " << game.GetGenerations() << '\n' ;
    string curr_gen = game.curr_gen;
    for (int row = 0; row < game.height; ++row) {
        for (int col = 0; col < game.width; ++col) {
            os << curr_gen[col + (row * game.width)];
        }
        os << '\n';
    }
    return os;
}

/** Constructor
 * Checks if the filename leads to an actual file then checks if the file is formated correctly then checks if the live and dead cell charaters are the same
 * Then it sets the width and height, live_cell, and dead_cell variables. Then it instantiates the curr_gen variable as an array of width*height size filled with dead cells
 * It then loops through every line in the file and fills in the curr_gen array after that it runs the number of pregens specified
*/
game_of_life::game_of_life(string filename, char live, char dead, int pregens) {
    string line;
    num_gens_saved = 0;
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

/** Constructor
 * Calls the first constructor but pregens = 0
*/
game_of_life::game_of_life(string filename, char live, char dead) : game_of_life(filename, live, dead, 0) {}

/** Constructor
 * Calls the first constructor but live cell = * and dead cell = -
*/
game_of_life::game_of_life(string filename, int pregens) : game_of_life(filename, '*', '-', pregens) {}

/** Constructor
 * Calls the first constructor but live cell = * and dead cell = - and pregens = 0
*/
game_of_life::game_of_life(string filename) : game_of_life(filename, '*', '-', 0) {}  