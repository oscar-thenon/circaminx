#include "ui_render.hpp"

namespace
{
void update_texture(int symbol_id,
                    sf::Sprite &sprite,
                    sf::Texture &texture_1,
                    sf::Texture &texture_1_rev,
                    sf::Texture &texture_2,
                    sf::Texture &texture_2_rev,
                    sf::Texture &texture_3,
                    sf::Texture &texture_3_rev,
                    sf::Texture &texture_4,
                    sf::Texture &texture_4_rev,
                    sf::Texture &texture_bottom,
                    sf::Texture &texture_top)
{
    switch (symbol_id)
    {
        case 0:
            sprite.setTexture(texture_1);
            break;
        case 1:
            sprite.setTexture(texture_2);
            break;
        case 2:
            sprite.setTexture(texture_3);
            break;
        case 3:
            sprite.setTexture(texture_4);
            break;
        case 4:
            sprite.setTexture(texture_bottom);
            break;
        case 5:
            sprite.setTexture(texture_top);
            break;
        case 6:
            sprite.setTexture(texture_1_rev);
            break;
        case 7:
            sprite.setTexture(texture_2_rev);
            break;
        case 8:
            sprite.setTexture(texture_3_rev);
            break;
        case 9:
            sprite.setTexture(texture_4_rev);
            break;
        default:
            sprite.setTexture(texture_1);
            break;
    }
}
} // namespace

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
                    sf::Texture &texture_top)
{
    for (int k = 0; k < 10; k++)
    {
        update_texture(position[k], *symbol_sprites[k], texture_1, texture_1_rev, texture_2, texture_2_rev, texture_3, texture_3_rev, texture_4, texture_4_rev, texture_bottom, texture_top);
    }
}

void update_move_counter(sf::Text &move_counter_text,
                         float screen_w_scale,
                         float screen_h_scale,
                         const sf::Color &success_color,
                         bool solved,
                         const std::string &move_count_string)
{
    move_counter_text.setString(move_count_string);
    sf::FloatRect bounds = move_counter_text.getLocalBounds();
    move_counter_text.setPosition(screen_w_scale * 1884 - bounds.width, screen_h_scale * 958);
    move_counter_text.setFillColor(solved ? success_color : sf::Color::Black);
}
