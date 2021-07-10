#include "model.hxx"
#include <catch.hxx>

//Once a game runs, a square will immediately flash and
//become the first element in the sequence. Thus,
//the sequence must grow to a vector of 1 element.
TEST_CASE("CHECK SPECIFICATION 2: One random square flashes upon start")
{
    Model model_;

    CHECK(model_.current_sequence.size() == 1);
}

//Checks that incorrect user inputs (a sequence of tiles different
//than the given flashing sequence) results in the loss of a life
TEST_CASE("CHECK SPECIFICATION 4: Incorrect guesses remove lives")
{
    Model model_;

    model_.new_tile();
    model_.new_tile();
    model_.new_tile();

    for(int tile: model_.current_sequence){
        model_.user_sequence.push_back(tile);
    }

    if(model_.current_sequence[model_.current_sequence.size() - 1] == 1){
        model_.user_sequence[model_.user_sequence.size() - 1] = model_
                                                                        .current_sequence[model_.current_sequence.size() - 1] + 1;
    } else {
        model_.user_sequence[model_.user_sequence.size() - 1] = model_
                                                                        .current_sequence[model_.current_sequence.size() - 1] - 1;
    }


    if(!model_.check_correct()){
        model_.health -= 1;
    }

    CHECK(model_.health == 2);



    Model m;
    CHECK(m.health == 3);
    m.current_sequence = {1,4,1,2,3};
    CHECK(m.health == 3);


    m.user_sequence = {1,4,1,2,3};
    CHECK(m.check_correct());
    CHECK(m.health == 3);

    m.current_sequence = {1,4,1,2,3, 2};
    m.user_sequence = {1,4,1,2,3, 1};

    CHECK(!m.check_correct());

    if(!m.check_correct()){
        m.health -= 1;
    }

    CHECK(m.health == 2);


}

//Leveling up begins a new sequence, resets lives,
TEST_CASE("CHECK SPECIFICATION 7: Level Up")
{
    Model model_;

    //user had one life
    model_.health = 1;

    //random sequences of 10 elements
    model_.current_sequence = {1,2,2,1,4,2,3,1,2,4};
    model_.user_sequence = {1,2,2,1,4,2,3,1,2,4};


    CHECK(model_.health == 1);

    model_.level_up(1);

    //new level
    CHECK(model_.level == 2);

    //health reset to 3
    CHECK(model_.health == 3);

    //user sequence cleared
    CHECK(model_.user_sequence.size() == 0);

    //new sequence with 1 tile
    CHECK(model_.current_sequence.size() == 1);
}

//Checks that correct user input results in a new tile being
//added to the end of the sequence
TEST_CASE("CHECK SPECIFICATION 5: Sequence Grows")
{
    Model model_;

    model_.new_tile();
    model_.new_tile();
    model_.new_tile();

    for(int tile: model_.current_sequence){
        model_.user_sequence.push_back(tile);
    }

    //copies the elements of the current sequence
    std::vector<int> copy = model_.current_sequence;

    CHECK(model_.current_sequence.size() == 4);

    if(model_.check_correct())
    {
        //new tile added to the end of the current sequence
        model_.new_tile();
    }

    CHECK(model_.current_sequence.size() == 5);

    //checks that the new_tile adds a tile to the end of the vector
    //the original vector is equal to the new vector minus the last element
    model_.current_sequence.pop_back();
    CHECK(copy == model_.current_sequence);
}

//Checks that the loss of 3 lives results in
//a loss game state
TEST_CASE("CHECK SPECIFICATION 6: Loss Game")
{
    Model model_;

    model_.new_tile();
    model_.new_tile();
    model_.new_tile();

    //user sequence matches current flashed sequence
    for(int tile: model_.current_sequence){
        model_.user_sequence.push_back(tile);
    }

    if(model_.current_sequence[model_.current_sequence.size() - 1] == 1){
        model_.user_sequence[model_.user_sequence.size() - 1] = model_
                                                                        .current_sequence[model_.current_sequence.size() - 1] + 1;
    } else {
        model_.user_sequence[model_.user_sequence.size() - 1] = model_
                                                                        .current_sequence[model_.current_sequence.size() - 1] - 1;
    }

    //decrements health if the sequence don't match
    if(!model_.check_correct()){
        model_.health -= 1;
    }

    if(!model_.check_correct()){
        model_.health -= 1;
    }

    if(!model_.check_correct()){
        model_.health -= 1;
    }

    //end game at 3 lives lost
    model_.end_game();

    //check that boolean loss is set to true once a user has lost 3 lives
    CHECK(model_.loss);
}

//Checks that leveling up twice (completing level 2) results in a win state
TEST_CASE("CHECK SPECIFICATION 8: Win Game")
{
    Model model_;

    //level up twice
    model_.level_up(1);
    model_.level_up(1);
    model_.end_game();

    //check that boolean won is set to true upon leveling up twice (beating
    // level 2)
    CHECK(model_.won);
}

TEST_CASE("Add 3 flashes and check user input matches")
{
    Model model_;

    model_.new_tile();
    model_.new_tile();
    model_.new_tile();

    //match user sequence to current sequence
    for(int tile: model_.current_sequence)
    {
        model_.user_sequence.push_back(tile);
    }

    //check_correct() returns true if the user sequence matches the game
    // sequence
    CHECK(model_.check_correct());
}

TEST_CASE("Lose 2 hearts then level up")
{
    Model model_;

    //make a game sequence with 9 tiles
    model_.new_tile();
    model_.new_tile();
    model_.new_tile();
    model_.new_tile();
    model_.new_tile();
    model_.new_tile();
    model_.new_tile();
    model_.new_tile();


    //user sequence is incorrect
    for(int tile: model_.current_sequence)
    {
        if(tile == 1)
        {
            model_.user_sequence.push_back(tile + 1);
        } else {
            model_.user_sequence.push_back(tile - 1);
        }
    }

    //user loses health due to incorrect sequence
    if(!model_.check_correct())
    {
        model_.health -= 1;
    }

    model_.user_sequence[model_.user_sequence.size() - 1] = 5;

    //user loses health due to incorrect sequence
    if(!model_.check_correct())
    {
        model_.health -= 1;
    }

    CHECK(model_.health == 1);

    model_.clear_user_sequence();
    model_.new_tile();

    //user sequence now matches game sequence
    for(int tile: model_.current_sequence)
    {
        model_.user_sequence.push_back(tile);
    }

    //game sequence reaches 10 and levels up user
    if(model_.current_sequence.size() == 10 && model_.check_correct())
    {
        model_.level_up(1);
    }


    //checks that reaching level two resets the game sequence to 1 tiles and
    // resets player health
    CHECK(model_.level == 2);
    CHECK(model_.current_sequence.size() == 1);
    CHECK(model_.health == 3);
}

TEST_CASE("Game resets upon loss")
{
    Model model_;

    model_.new_tile();
    model_.new_tile();
    model_.new_tile();

    //user sequence does not match current sequence
    for(int tile: model_.current_sequence)
    {
        if(tile == 1)
        {
            model_.user_sequence.push_back(tile + 1);
        } else {
            model_.user_sequence.push_back(tile - 1);
        }
    }

    //user loses health
    if(!model_.check_correct())
    {
        model_.health -= 1;
    }

    model_.user_sequence[model_.user_sequence.size() - 1] = 5;

    if(!model_.check_correct())
    {
        model_.health -= 1;
    }

    model_.user_sequence[model_.user_sequence.size() - 1] = 6;

    if(!model_.check_correct())
    {
        model_.health -= 1;
    }

    //game resets upon reaching a health of 0
    if(model_.health == 0) {
        model_.level_up(2);
    }

    //checks that having 0 health resets the game with a game sequence of 1
    // (1 tile flashed) and 3 lives
    CHECK(model_.current_sequence.size() == 1);
    CHECK(model_.user_sequence.size() == 0);
    CHECK(model_.health == 3);
}


TEST_CASE("Complete Level 1")
{
    Model model_;

    for(int x = 0; x < 9; x++)
    {
        for(int tile: model_.current_sequence)
        {
            model_.user_sequence.push_back(tile);
        }

        if(model_.check_correct())
        {
            model_.new_tile();
        }

        model_.clear_user_sequence();
    }

    if(model_.current_sequence.size() == 10)
    {
        model_.level_up(1);
    }

    //check that level up makes the level 2
    CHECK(model_.level == 2);
}

TEST_CASE("Complete entire game")
{
    Model model_;

    for(int x = 0; x < 9; x++)
    {
        for(int tile: model_.current_sequence)
        {
            model_.user_sequence.push_back(tile);
        }

        if(model_.check_correct())
        {
            model_.new_tile();
        }

        model_.clear_user_sequence();
    }

    if(model_.current_sequence.size() == 10)
    {
        model_.level_up(1);
    }

    CHECK(model_.level == 2);

    for(int x = 0; x < 9; x++)
    {
        for(int tile: model_.current_sequence)
        {
            model_.user_sequence.push_back(tile);
        }

        if(model_.check_correct())
        {
            model_.new_tile();
        }

        model_.clear_user_sequence();
    }

    if(model_.current_sequence.size() == 10)
    {
        model_.level_up(1);
    }

    //check that leveling up makes boolean won equal to true
    CHECK(model_.level == 3);
    CHECK(model_.won == true);
}