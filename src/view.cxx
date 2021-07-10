#include "view.hxx"
#include <string>


static ge211::Color const black_color {0, 0, 0};
static ge211::Color const red_color {255, 0, 0};
static ge211::Color const blue_color {0, 0, 255};
static ge211::Color const green_color {0, 255, 0};
static ge211::Color const yellow_color{255, 255, 0};

static ge211::Color const light_red{255, 204, 204};
static ge211::Color const light_blue{204, 255, 255};
static ge211::Color const light_green{205, 255, 204};
static ge211::Color const light_yellow{255, 255, 204};

View::View(Model const& model)
        : model_(const_cast<Model&>(model)),
          black_background(ge211::Dims<int>(model_.width,model_.width),
                           black_color),
          red_tile(model_.tile_dims, red_color),
          blue_tile(model_.tile_dims, blue_color),
          yellow_tile(model_.tile_dims, yellow_color),
          green_tile(model_.tile_dims, green_color),
          health1_sprite(make_ui_text("Lives: 1")),
          health2_sprite(make_ui_text("Lives: 2")),
          health3_sprite(make_ui_text("Lives: 3")),
          level1_sprite(make_ui_text("Level: 1")),
          level2_sprite(make_ui_text("Level: 2")),
          won_sprite(make_end_text("YOU WON")),
          loss_sprite(make_end_text("YOU LOST")),
          goodbye_screen(make_end_text("GOODBYE")),
          restart_screen(make_end_text("RESTARTING"))
{ }




void
View::draw(ge211::Sprite_set& set)
{
    set.add_sprite(red_tile, {0, model_.mouse_position_y2});
    set.add_sprite(blue_tile, {model_.mouse_position_x,
                               model_.mouse_position_y2});
    set.add_sprite(yellow_tile, {0, model_.mouse_position_y});
    set.add_sprite(green_tile, {model_.mouse_position_x,
                                model_.mouse_position_y});

    if(model_.quit && model_.health != 0){
        set.add_sprite(black_background, {model_.origin_x,model_.origin_y});
        set.add_sprite(goodbye_screen, model_.after_game_dims);
    }

    if(model_.reset && model_.health != 0){
        set.add_sprite(black_background, {model_.origin_x,model_.origin_y});
        set.add_sprite(restart_screen, {model_.offset, model_
        .after_game_dims.y });
    }

    if(!model_.reset){
        red_tile.recolor(red_color);
        blue_tile.recolor(blue_color);
        yellow_tile.recolor(yellow_color);
        green_tile.recolor(green_color);
    }


    if(model_.health == 1 && !model_.loss){
        set.add_sprite(health1_sprite, model_.health_dims);
    }

    if(model_.health == 2 && !model_.loss){
        set.add_sprite(health2_sprite, model_.health_dims);
    }

    if(model_.health == 3 && !model_.loss){
        set.add_sprite(health3_sprite, model_.health_dims);
    }

    if(model_.level == 1 && !model_.loss) {
        set.add_sprite(level1_sprite, model_.level_dims);
    }

    if(model_.level == 2 && !model_.loss) {
        set.add_sprite(level2_sprite, model_.level_dims);
    }

    if(model_.health == 0){
        red_tile.recolor(black_color);
        blue_tile.recolor(black_color);
        yellow_tile.recolor(black_color);
        green_tile.recolor(black_color);
        model_.loss = true;
        model_.light_on = false;

        set.add_sprite(loss_sprite, model_.after_game_dims);
    }

    if(model_.tile == 1){
        flash_tile(1);
    }

    if(model_.tile == 2){
        flash_tile(2);
    }

    if(model_.tile == 3){
        flash_tile(3);
    }

    if(model_.tile == 4){
        flash_tile(4);
    }

    if(model_.light_on && !model_.reset) {
        flash_sequence();

        if(model_.sequence_position == model_.current_sequence.size()){
            model_.light_on = false;
            model_.sequence_position = 0;
            reset_colors();
        }
    }

    if(model_.level == 3){
        red_tile.recolor(black_color);
        blue_tile.recolor(black_color);
        yellow_tile.recolor(black_color);
        green_tile.recolor(black_color);
        model_.health = 4;
        set.add_sprite(won_sprite, model_.after_game_dims);
    }
}



void
View::flash_tile(int t){
    if (t == 1) {

        red_tile.recolor(light_red);

        if (model_.frame == (model_.max_frames / model_.level)) {
            red_tile.recolor(red_color);
            //model_.frame = 0;

        }
    }

    if (t == 2) {
        blue_tile.recolor(light_blue);

        if (model_.frame == (model_.max_frames / model_.level)) {
            blue_tile.recolor(blue_color);
            //model_.frame = 0;
        }
    }

    if (t == 3) {
        yellow_tile.recolor(light_yellow);

        if (model_.frame == (model_.max_frames / model_.level)) {
            yellow_tile.recolor(yellow_color);
            //model_.frame = 0;
        }
    }

    if (t == 4) {
        green_tile.recolor(light_green);

        if (model_.frame == (model_.max_frames / model_.level)) {
            green_tile.recolor(green_color);
            // model_.frame = 0;
        }
    }
}


ge211::Text_sprite
View::make_ui_text(std::string src)
{
    ge211::Text_sprite sprite;
    ge211::Font font("sans.ttf", 25);

    ge211::Text_sprite::Builder string_build(font);
    string_build.color(ge211::Color::white()) << src;
    sprite.reconfigure(string_build);
    return sprite;
}





ge211::Text_sprite
View::make_end_text(std::string src)
{
    ge211::Text_sprite sprite;
    ge211::Font font("sans.ttf", 100);


    ge211::Text_sprite::Builder string_build(font);
    string_build.color(ge211::Color::white()) << src;
    sprite.reconfigure(string_build);
    return sprite;}

void
View::reset_colors()
{
    red_tile.recolor(red_color);
    blue_tile.recolor(blue_color);
    yellow_tile.recolor(yellow_color);
    green_tile.recolor(green_color);
}

void
View::flash_sequence()
{
    for(int x = 0; x < model_.current_sequence.size(); x++) {
        //model_.sequence_frame = 0;
        int t = model_.current_sequence[model_.sequence_position];
        flash_tile(t);

        if(model_.frame == (model_.max_frames / model_.level)) {
            model_.sequence_position += 1;
            model_.frame = 0;
        }
    }
}