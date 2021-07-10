#include "model.hxx"
#include "controller.hxx"
#include <thread>
#include <chrono>

Model::Model()
{}


std::vector<int>
Model::new_tile()
{
    //generate a random integer between 1-4
    ge211::Random_source<int> random_int(1, 4);
    int new_tile = random_int.next();

    while (new_tile == current_sequence[current_sequence.size() - 1]) {
        new_tile = random_int.next();
    }

    //add new tile to the end of the vector
    current_sequence.push_back(new_tile);

    return current_sequence;
}



void
Model::level_up( int x) {
    level += 1;
    current_sequence.clear();
    user_sequence.clear();
    tile = 0;
    health = 3;
    frame = 0;
    sequence_position = 0;
    sequence_frame = 0;

    if(x == 2){
        level = 1;
    }

    start_game();

    if(level == 3){
        won = true;
    }
}

void
Model::reset_sequence()
{
    current_sequence.clear();

}

void
Model::end_game()
{
    if(current_sequence.size() != 10 || health == 0){
        loss = true;
    }
    won = true;
    reset_sequence();
}

void
Model::make_selection()
{
    user_sequence.push_back(tile);
}

bool
Model::check_correct()
{
    return (current_sequence == user_sequence);
}

void
Model::clear_user_sequence()
{
    user_sequence.clear();
    light_on = true;
}

void
Model::start_game()
{
    //populates the sequence vector with 3 random tiles
    new_tile();
}
//
// void
// Model::rand_int()
// {
//     ge211::Random_source<int> random_int(1, 4);
//     int v1 = random_int.next();
//     int v2 = random_int.next();
//
//     while (v1 == v2) {
//         v2 = random_int.next();
//     }
//
//     int v3 = random_int.next();
//     while (v2 == v3) {
//         v3 = random_int.next();
//     }
//
// }