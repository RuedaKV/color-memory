#pragma once

#include "model.hxx"

class View
{
public:
    explicit View(Model const& model);

    void draw(ge211::Sprite_set& set);

    //given an integer representing one of the four colored tiles, flashes
    //the tile for 120 frames or 60 frames depending on the level
    void flash_tile(int t);

    //flashes the current sequence
    void flash_sequence();

    //resets the colored tiles to their default colors.
    void reset_colors();

private:
    Model& model_;
    //initialize sprites
    ge211::Rectangle_sprite const black_background;
    ge211::Rectangle_sprite red_tile;

    ge211::Rectangle_sprite  blue_tile;

    ge211::Rectangle_sprite  yellow_tile;

    ge211::Rectangle_sprite  green_tile;

    ge211::Text_sprite  const health1_sprite;
    ge211::Text_sprite  const health2_sprite;
    ge211::Text_sprite  const health3_sprite;

    ge211::Text_sprite  const level1_sprite;
    ge211::Text_sprite  const level2_sprite;


    //makes level and health text sprites
    ge211::Text_sprite make_ui_text(std::string src);

    ge211::Text_sprite const won_sprite;
    ge211::Text_sprite const loss_sprite;

    //makes "loss", "won", and "goodbye" text screens
    ge211::Text_sprite make_end_text(std::string src);

    ge211::Text_sprite const goodbye_screen;
    ge211::Text_sprite const restart_screen;

};