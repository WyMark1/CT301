#include "game_of_life.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    try{
        game_of_life game("gamestarter.txt",'%','/',45);
        cout << game;
        game.NextGen();
        
    return 0;
    }
    catch(const runtime_error& e){
        cerr << "Runtime Error: " << e.what();
        return 0;
    }
}