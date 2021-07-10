#pragma once

#include <ge211.hxx>
#include <vector>

class Model
{
public:
    Model();

    bool reset = false;
    bool quit = false;

    //variables to prevent 'magic numbers'
    int max_frames = 120;
    int mouse_position_y = 325;
    int mouse_position_x = 400;
    ge211::Posn<int> after_game_dims = {150, 100};
    ge211::Dims<int> tile_dims = {mouse_position_x,275};
    ge211::Posn<int> level_dims = {300,0};
    ge211::Posn<int> health_dims = {mouse_position_x, 0};
    int mouse_position_y2 = 50;
    int width  = 800;

    int origin_x = 0;
    int origin_y = 0;

    int offset = 100;

    //tile holds the last selected user tile. If a user selects red,
    //tile = 1.
    int tile = 0;

    //represents the current user level
    int level = 1;

    //current user health
    int health = 3;

    //indicates whether draw should flash the sequence or not
    bool light_on = true;

    //represents the potential end states of the game
    bool loss = false;
    bool won = false;

    //holds a counter of game frames
    double frame = 0;

    //additional counter of game frames
    double sequence_frame = 0;

    //holds the position in the sequence vector that should flash
    double sequence_position = 0;


    int v1 = rand() % 4 + 1;
    // void rand_int();


    //vector of integers refers to integers between 1-4. Each integer refers to
    //one of the four colored tiles. The order of the integers in the vector
    //corresponds to the order in which tiles light up.
    std::vector<int> current_sequence{v1};
    std::vector<int> user_sequence;


    //compares the current sequence to the user input sequence
    bool check_correct();

    //initializes default game state
    void start_game();

    //user tile selection is added to the user sequence vector
    void make_selection();

    //increases game difficulty. resets the game.
    void level_up(int x);

    //populates the sequence vector with a new random integer between 1-4,
    //representing a new random tile
    std::vector<int> new_tile();

    //clear user sequence
    void clear_user_sequence();

    //sets the game state to either loss or true
    void end_game();

    //clear the random sequence
    void reset_sequence();

private:

};