#pragma once

#include "model.hxx"
#include "view.hxx"

#include <ge211.hxx>

class Controller : public ge211::Abstract_game
{

public:
    Controller();



protected:
    void draw(ge211::Sprite_set& set) override;

    //tracks mouse position on the screen
    void on_mouse_down(ge211::Mouse_button, ge211::Posn<int>) override;

    //responds to user clicks on the screen,
    void on_mouse_move(ge211::Posn<int>) override;

    //responds to user clicks. 'q' quits the game. 'r' restarts the game.
    void on_key(ge211::Key) override;

    //counter of frames
    void on_frame(double dt) override;


private:
    Model model_;
    View view_;

    //tracks mouse position on the screen
    ge211::Posn<int> mouse_position = {0,0};

};