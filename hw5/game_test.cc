#include "game_of_life.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    try{
        game_of_life game("gamestarter.txt",'*',' ',45);
        game_of_life game3("gamestarter2.txt",'*',' ',199);
        cout << game;
        game_of_life game2 = game.GenSubGame(19, 19, 3, 4);
        cout << "\n\n\n\n" << game2;
        game_of_life game4 = game3 - 100;
        cout << game4 - 1;
        cout << game3;
        cout << (game < game2);
        cout << '\n' << game2.IsStillLife() << "\n";
        cout << (game == game3) << " ==\n";
        cout << (game < game3) << " game < game2\n";
        cout << (game > game3) << " game > game2\n";
        cout << (game >= game3) << " game >= game2\n";
        cout << (game <= game3) << " game <= game2\n";
    return 0;
    }
    catch(const exception& e){
        cerr << "Runtime Error: " << e.what();
        return 0;
    }
}