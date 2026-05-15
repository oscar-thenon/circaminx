#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>

#include "position.hpp"

void update_display(const Position &position,
                    sf::Sprite *symbol_sprites[10],
                    sf::Texture &texture_1,
                    sf::Texture &texture_1_rev,
                    sf::Texture &texture_2,
                    sf::Texture &texture_2_rev,
                    sf::Texture &texture_3,
                    sf::Texture &texture_3_rev,
                    sf::Texture &texture_4,
                    sf::Texture &texture_4_rev,
                    sf::Texture &texture_bottom,
                    sf::Texture &texture_top);

void update_move_counter(sf::Text &move_counter_text,
                         float screen_w_scale,
                         float screen_h_scale,
                         const sf::Color &success_color,
                         bool solved,
                         const std::string &move_count_string);
