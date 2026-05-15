#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>

struct SceneContext
{
    sf::RenderWindow window;

    float screen_w_scale;
    float screen_h_scale;

    sf::Texture background_texture;
    sf::Sprite background_sprite;

    sf::Texture texture_1;
    sf::Texture texture_1_rev;
    sf::Texture texture_2;
    sf::Texture texture_2_rev;
    sf::Texture texture_3;
    sf::Texture texture_3_rev;
    sf::Texture texture_4;
    sf::Texture texture_4_rev;
    sf::Texture texture_top;
    sf::Texture texture_bottom;

    sf::Sprite sprite_1;
    sf::Sprite sprite_1_rev;
    sf::Sprite sprite_2;
    sf::Sprite sprite_2_rev;
    sf::Sprite sprite_3;
    sf::Sprite sprite_3_rev;
    sf::Sprite sprite_4;
    sf::Sprite sprite_4_rev;
    sf::Sprite sprite_top;
    sf::Sprite sprite_bottom;

    sf::Font main_font;
    sf::Text move_counter_text;
    sf::Color success_color{sf::Color::Green};

    sf::Sprite *symbol_sprites[10];

    SceneContext();
};
