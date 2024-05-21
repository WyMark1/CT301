#include <iostream>
#include <fstream>
#include <string>

using namespace std;
//Wyatt Markham
//wymark

// A custom modulo function that when given a negitive number outputs such that customMod(-1,5) = 4 used to help with wraping calculations
int customMod(const int &a, const int &b) {
    return (a % b + b) % b;
}

// Given a string gen and the current generation number out put the board of the current generation which has a width of width
void OutputGeneration(string &gen, int curr_gen, int width){
    cout << "Generation: " << curr_gen << "\n";
    for (int row = 0; row < width; row++){
        for (int col = 0; col < width; col++){
            cout << gen[col+(row*width)];
        }
        cout << "\n";
    }
}

// Given a string curr_gen manipulate the given string next_gen based on John Conway's game of life. 
// For a board size of width*width and the board has both top bottom and left right wraping
void CalculateGeneration(string &curr_gen, string &next_gen, int width){
    for (int row = 0; row < width; row++){
        for (int col = 0; col < width; col++){
            int num_nieghbors = 0; // Total number of neighbors around current cell
            int curr_index = col+(row*width); 
            int curr_row = curr_index; // Current middle point of row
            for (int i=0; i < 3; i++){
                if (curr_row != curr_index){ // If it is the current cell don't add it to num_neighbors
                    if (curr_gen[curr_row]=='*') num_nieghbors++; // Middle cell
                }
                if (curr_gen[customMod(curr_row+1,width)+(width*(curr_row/width))]=='*') // Right cell
                    num_nieghbors++; 
                if (curr_gen[customMod(curr_row-1,width)+(width*(curr_row/width))]=='*') // Left cell 
                    num_nieghbors++; 
            
                if (i==0) curr_row = customMod(curr_index+width,(width*width)); // Bottom row
                if (i==1) curr_row = customMod(curr_index-width,(width*width)); // Top Row
            }
            
            if (num_nieghbors<2){ // Are there less then 2 neighbors then underpopulation
                next_gen[curr_index] = '-';
            } else if (num_nieghbors == 2 && curr_gen[curr_index] == '*') { // Have two neighbors then sustain
                next_gen[curr_index] = '*';
            } else if(num_nieghbors == 3){ // Have three neighbors or dead cell the sustain or rebirth
                next_gen[curr_index] = '*';
            } else{ // More than three neighbors over population
                next_gen[curr_index] = '-';
            }
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2){
        cerr << argv[0] << " Usage:\n" << argv[0] << " filename\n\n" << "The filename passed should contain the following, the integer width of the table, the number of generations then a Width by Width table of characters for setting up the game\n" << endl;
        return -1;
    }
    string filename = argv[1];
    ifstream file_in(filename);
    string line;
    int width;
    int generations;
    file_in >> width >> generations;
    string game_table_alpha(width*width, '-');
    string game_table_beta(width*width, '-');
    getline(file_in, line);
    for (int row = 0; file_in && row < width; ++row){
        getline(file_in, line);
        for (int col = 0; col < width; ++col)
        {
            game_table_alpha[col+(row*width)] = line[col];
        }
    }

    int curr_gen = 0; 
    for (int i=0; i<generations; i++){ 
        OutputGeneration(game_table_alpha, curr_gen, width); // Print the generation 
        CalculateGeneration(game_table_alpha, game_table_beta, width); // Calculate the next generation 
        game_table_alpha = game_table_beta; // Overwrite the pervious generation with the current generation 
        curr_gen++;  
    }
    OutputGeneration(game_table_alpha, curr_gen, width);
    ofstream out_file;
    size_t end_file_path = filename.find_last_of('/');
    string out_filename;
    if (end_file_path != string::npos) {
        out_filename = filename.substr(end_file_path+1);
    }
    else {
        out_filename = filename;
    }
    out_file.open("final_output_"+out_filename);
    out_file << "Final Generation: " << generations << "\n";
    for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < width; j++)
            {
                out_file << game_table_alpha[j + (i*width)];
            }
            out_file << "\n";
        }
    out_file.close();
}