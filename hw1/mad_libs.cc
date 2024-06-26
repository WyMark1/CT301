#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;
// Wyatt Markham
// wymark

string program_name;
// No Changes needed, this method queries a user for input
bool GetMadLibFile(ifstream& input_file){
    if (input_file.is_open())
        input_file.close();
    cout << "Please enter a valid Mad Libs File or 'exit' to close: ";
    string filename;
    getline(cin, filename);
    string temp = filename;
    transform(filename.begin(), filename.end(), filename.begin(), [](unsigned char c){return tolower(c);});
    if (filename == "exit"){
        cout << "Exiting program, Thanks for playing!\n";
        return false;
    }
    input_file.open(temp, ifstream::in);
    if (!input_file){
        cerr << program_name << ", Function: GetMadLibFile. Error File cannot be found/opened: " << filename << ".\n";
        return false;
    }
    return true;
}

bool IsFillInBlank(const string &word){
    //TODO: Check if string begins and ends with '_'
    if (word[0]=='_' && word[word.length()-1]=='_') 
        return true;
    return false;
}

string GetUserResponse(string &fill_in){
    string out;
    //TODO: Trim the '_' off of the fill in word and query the user for a replacement.
    //See https://www.techiedelight.com/replace-occurrences-character-string-cpp/
    size_t pos;
    while ((pos = fill_in.find('_')) != string::npos)
        fill_in.replace(pos, 1, " ");
    fill_in.replace(0,1,"");
    fill_in.replace(fill_in.length()-1,1,"");
    //TODO: Query the user for the Fill in the blank word generated by your trimming of the '_' character
    cout << "Please enter a \"" << fill_in << "\": ";
    getline(cin, out);
    return out;
}

int main(int argc, char* argv[]){
    program_name = argv[0];
    // Create the File reading ifstream.
    ifstream input_file;
    while (GetMadLibFile(input_file)){
        // NOTE: Your code goes here
        // NOTE: Get a line, check to see if any of the words in the line are a fill in word.
        //TODO: Output the finished madlib like so "Your MadLib!\n\n" followed by their madlib and a new line at the end
        string out;
        string curr_line;
        while (getline(input_file, curr_line)){
            stringstream ss(curr_line);
            string curr_word;
            while (ss >> curr_word){
                if (IsFillInBlank(curr_word))
                    out.append(GetUserResponse(curr_word) + " ");
                else 
                    out.append(curr_word + " ");
            }
            out.append("\n");
        }
        cout << "Your MadLib!\n\n" << out << "\n";
    }
}