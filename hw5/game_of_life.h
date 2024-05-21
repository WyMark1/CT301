#ifndef GAME_OF_LIFE_H_DEFINED
#define GAME_OF_LIFE_H_DEFINED
#include <string>
#include <iostream>
class game_of_life {
    struct game_save_state {
        std::string game_board;
        int width;
        int height;
        int generation;
        char live;
        char dead;
    };

    /** GetStruct
     * @Param None
     * @Return a game_save_state of the current position
    */
    game_save_state GetStruct();

    /** ChangeState
     * @Param save a game_save_state of some game
     * @Return None
    */
    void ChangeState(game_save_state save);

    /** New
     * @Param game a string that is the game board
     * @Param height_ the height of the new game
     * @Param width_ the width of the new game
     * @Return None
    */
    void New(std::string game, int height_, int width_);

    /** NumLive
     * @Param None
     * @Return a int that is the number of live cells in the current game
    */
    int NumLive() const;

    /** SimulateNext
     * @Param None
     * @Return a string that represents the game board of the next generation
    */
    std::string SimulateNext() const;

    std::string curr_gen;
    int num_gens = 0;
    int width;
    int height;
    int num_gens_saved;
    game_save_state saved_games[100];
    char live_cell;
    char dead_cell;
    constexpr static const char * cell_dupe_error = "game_of_life - Live Cell and Dead Cell cannot be the same character\n";
    constexpr static const char * file_not_found_error = "game_of_life - File Not Found \"";
    constexpr static const char * invalid_read_error = "game_of_life - Width and Height incorrectly formatted for file \"";
    constexpr static const char * error_end = "\"\n";
    
public:
    game_of_life() = delete;

    /** Constructor
     * @Param filename a string for the file name
     * @Return None
    */
    game_of_life(std::string filename);

    /** Constructor
     * @Param filename a string for the file name
     * @Param pregens a int representing the number of generations to start at
     * @Return None
    */
    game_of_life(std::string filename, int pregens);

    /** Constructor
     * @Param filename a string for the file name
     * @Param live_cell a char for what the live cell will be represented as
     * @Param dead_cell a char for what the dead cell will be represented as
     * @Return None
    */
    game_of_life(std::string filename, char live_cell, char dead_cell);

    /** Constructor
     * @Param filename a string for the file name
     * @Param live_cell a char for what the live cell will be represented as
     * @Param dead_cell a char for what the dead cell will be represented as
     * @Param pregens a int representing the number of generations to start at
     * @Return None
    */
    game_of_life(std::string filename, char live_cell, char dead_cell, int pregens);

    //Big 5
    game_of_life(const game_of_life &) = default;
    game_of_life(game_of_life &&rhs) = default;
    game_of_life &operator=(const game_of_life &) = default;
    game_of_life &operator=(game_of_life &&rhs) = default;
    virtual ~game_of_life() = default;

    /** GetGenerations
     * @Param None
     * @Return a int that is the number of generations calculated in the current game
    */
    int GetGenerations() const;

    /** NextGen
     * @Param None
     * @Return None
    */
    void NextGen();

    /** NextNGen
     * @Param n a int for the number of generations to calculate
     * @Return None
    */
    void NextNGen(int n);

    /** SetLiveCell
     * @Param live_cell a char for what the live cell will be represented as
     * @Return None
    */
    void SetLiveCell(char live_cell);

    /** SetDeadCell
     * @Param dead_cell a char for what the dead cell will be represented as
     * @Return None
    */
    void SetDeadCell(char dead_cell);

    /** operator+
     * @Param gens the number of generations to be added to the current game
     * @Return a copy of the current game that is gen number of generations ahead
    */
    game_of_life operator+(int gens); 

    /** operator++
     * @Param None
     * @Return a reference to the curent game but is one generation higher
    */
    game_of_life& operator++();

    /** operator++
     * @Param fake a int that is just used to differentiate it from pre-increment
     * @Return a copy of the current game
    */
    game_of_life operator++(int fake); 

    /** operator+=
     * @Param gens the number of generations to be added to the current game
     * @Return a reference to the curent game but is gens generations higher
    */
    game_of_life& operator+=(int gens);

    /** operator-=
     * @Param gens the number of generations to be subtracted to the current game
     * @Return a reference to the curent game but is gens generations lower
    */
    game_of_life& operator-=(int gens);

    /** operator-
     * @Param gens the number of generations to be subtracted to the current game
     * @Return a copy of the current game that is gen number of generations behind
    */
    game_of_life operator-(int gens);

    /** operator--
     * @Param None
     * @Return a reference to the curent game but is one generation lower
    */
    game_of_life& operator--();

    /** operator--
     * @Param fake a int that is just used to differentiate it from pre-decrement
     * @Return a copy of the current game
    */
    game_of_life operator--(int fake);

    /** operator<
     * @Param rhs a game_of_life reference to compare the current game to
     * @Return a bool representing whether or not the current game is less than rhs
    */
    bool operator<(game_of_life& rhs);

    /** operator<=
     * @Param rhs a game_of_life reference to compare the current game to
     * @Return a bool representing whether or not the current game is less than or equal to rhs
    */
    bool operator<=(game_of_life& rhs);

    /** operator>
     * @Param rhs a game_of_life reference to compare the current game to
     * @Return a bool representing whether or not the current game is greater than rhs
    */
    bool operator>(game_of_life& rhs);

    /** operator>=
     * @Param rhs a game_of_life reference to compare the current game to
     * @Return a bool representing whether or not the current game is greater than or equal to rhs
    */
    bool operator>=(game_of_life& rhs);

    /** operator==
     * @Param rhs a game_of_life reference to compare the current game to
     * @Return a bool representing whether or not the current game is equal to rhs
    */
    bool operator==(game_of_life& rhs);

    /** GenWindow
     * @Param row the row to start the window on
     * @Param col the column to start the window on
     * @Param height_ the total height of the window
     * @Param width_ the total width of the window
     * @Return a string representing a window into the current game
    */
    std::string GenWindow(int row, int col, int height_, int width_);

    /** GenSubGame
     * @Param row the row to start the subgame on
     * @Param col the column to start the subgame on
     * @Param height_ the total height of the subgame
     * @Param width_ the total width of the subgame
     * @Return a new game_of_life object that is a sub game of the current one
    */
    game_of_life GenSubGame(int row, int col, int height_, int width_);

    /** ToggleCell
     * @Param index a int which is a index in the current game
     * @Return None
    */
    void ToggleCell(int index);

    /** ToggleCell
     * @Param row what row you want to toggle a cell on
     * @Param col what column you want to toggle a cell on
     * @Return None
    */
    void ToggleCell(int row, int col);

    /** IsStillLife
     * @Param None
     * @Return a bool representing whether or not the current game is unchanging 
    */
    bool IsStillLife() const;

    /** GetAvailableGens
     * @Param None
     * @Return a int representing the number of generations you can roll back to
    */
    int GetAvailableGens() const;

    /** operator<<
     * @Param os a reference to a ostream object
     * @Param game a reference to a game_of_life object
     * @Return a ostream which is just os but modified with the contents of game
    */
    friend std::ostream & operator<<(std::ostream &os, const game_of_life &game);
};

#endif
