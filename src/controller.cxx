#include "controller.hxx"
#include "model.hxx"
#include "view.hxx"
#include <ge211.hxx>
#include <iostream>
#include <cmath>

using Sprite_set = ge211::Sprite_set;

Controller::Controller()
        : model_(),
          view_(model_)
{ }


void
Controller::on_key(ge211::Key key)
{
    if (key == ge211::Key::code('q')) {
        model_.quit = true;
        model_.frame = 0;

    }

    if (key == ge211::Key::code('r')) {
        model_.reset = true;
        model_.frame = 0;
        model_.level_up(2);
    }
}


void
Controller::on_mouse_down(ge211::Mouse_button mouse, ge211::Posn<int>)
{
    //the mouse position on the screen may refer to one of the four colored
    // tiles
    if(mouse_position.x < model_.mouse_position_x && mouse_position.y <
                                                     model_.mouse_position_y && mouse_position.y > model_
            .mouse_position_y2){
        model_.tile = 1;
    }

    if(mouse_position.x > model_.mouse_position_x && mouse_position.y <
                                                     model_.mouse_position_y && mouse_position.y >
                                                                                model_.mouse_position_y2){
        model_.tile = 2;
    }

    if(mouse_position.x < model_.mouse_position_x && mouse_position.y >
                                                     model_.mouse_position_y){
        model_.tile = 3;
    }

    if(mouse_position.x > model_.mouse_position_x && mouse_position.y >
                                                     model_.mouse_position_y){
        model_.tile = 4;
    }

    //initializes the frames to 0
    model_.frame = 0;

    //adds user selected tile to the user vector
    model_.make_selection();

    //once the user selects a number of tiles equal to the number of tiles
    //in the sequence, initialize the comparison stage
    if(model_.current_sequence.size() == model_.user_sequence.size()){
        model_.tile = 0;

        //compares the user input with the sequence
        //if the user is correct and hasn't reached the end of the level,
        //add a tile to the sequence and continue. If the user is correct and
        //has reached the end of the level, level up (new sequence, fresh lives)
        //if the user is incorrect and still has lives remaining, remove a life.
        //if the user is incorrect and has no remaining lives, end the game
        if(model_.check_correct()){
            if(model_.current_sequence.size() < 10){
                model_.new_tile();
            } else {
                model_.level_up(1);
            }
        } else {
            model_.health -= 1;
            if(model_.health == 0){
                model_.frame = 0;
                model_.level_up(2);
            }
        }

        //clear the user sequence to allow for a fresh set of input
        model_.clear_user_sequence();
    }
}

void
Controller::on_mouse_move(ge211::Posn<int> position)
{
    mouse_position = position;
}

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}

void
Controller::on_frame(double dt)
{
    //controls how fast to flash a tile
    if(model_.frame < (model_.max_frames / model_.level)) {
        model_.frame += 1;
    }

    //controls when to flash a tile
    if(model_.sequence_frame == (model_.max_frames / model_.level)){
        model_.sequence_position += 1;
        //model_.frame = 0;
    }

    if(model_.frame == model_.max_frames && model_.reset){
        model_.reset = false;
        model_.frame = 1;
        model_.light_on = true;
    }

    if(model_.frame == model_.max_frames && model_.quit){
        quit();
    }

}