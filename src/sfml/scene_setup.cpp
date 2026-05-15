#include "scene_setup.hpp"
#include "scene_context.hpp"


namespace {
bool load_texture(sf::Texture &texture, const char *path) {
    return texture.loadFromFile(path);
}

bool load_textures(SceneContext &scene) {
    return load_texture(scene.texture_1, "./assets/img/1.png") &&
           load_texture(scene.texture_1_rev, "./assets/img/1r.png") &&
           load_texture(scene.texture_2, "./assets/img/2.png") &&
           load_texture(scene.texture_2_rev, "./assets/img/2r.png") &&
           load_texture(scene.texture_3, "./assets/img/3.png") &&
           load_texture(scene.texture_3_rev, "./assets/img/3r.png") &&
           load_texture(scene.texture_4, "./assets/img/4.png") &&
           load_texture(scene.texture_4_rev, "./assets/img/4r.png") &&
           load_texture(scene.texture_bottom, "./assets/img/b.png") &&
           load_texture(scene.texture_top, "./assets/img/h.png");
}

bool load_sprites(SceneContext &scene) {
    scene.sprite_1.setPosition(scene.screen_w_scale * 548, scene.screen_h_scale * 141);
    scene.sprite_1_rev.setPosition(scene.screen_w_scale * 1196, scene.screen_h_scale * 97);
    scene.sprite_2.setPosition(scene.screen_w_scale * 256, scene.screen_h_scale * 334);
    scene.sprite_2_rev.setPosition(scene.screen_w_scale * 1498, scene.screen_h_scale * 266);
    scene.sprite_3.setPosition(scene.screen_w_scale * 285, scene.screen_h_scale * 679);
    scene.sprite_3_rev.setPosition(scene.screen_w_scale * 1529, scene.screen_h_scale * 600);
    scene.sprite_4.setPosition(scene.screen_w_scale * 599, scene.screen_h_scale * 840);
    scene.sprite_4_rev.setPosition(scene.screen_w_scale * 1237, scene.screen_h_scale * 791);
    scene.sprite_bottom.setPosition(scene.screen_w_scale * 904, scene.screen_h_scale * 626);
    scene.sprite_top.setPosition(scene.screen_w_scale * 883, scene.screen_h_scale * 302);

    scene.sprite_1.scale(scene.screen_w_scale, scene.screen_h_scale);
    scene.sprite_1_rev.scale(scene.screen_w_scale, scene.screen_h_scale);
    scene.sprite_2.scale(scene.screen_w_scale, scene.screen_h_scale);
    scene.sprite_2_rev.scale(scene.screen_w_scale, scene.screen_h_scale);
    scene.sprite_3.scale(scene.screen_w_scale, scene.screen_h_scale);
    scene.sprite_3_rev.scale(scene.screen_w_scale, scene.screen_h_scale);
    scene.sprite_4.scale(scene.screen_w_scale, scene.screen_h_scale);
    scene.sprite_4_rev.scale(scene.screen_w_scale, scene.screen_h_scale);
    scene.sprite_bottom.scale(scene.screen_w_scale, scene.screen_h_scale);
    scene.sprite_top.scale(scene.screen_w_scale, scene.screen_h_scale);

    scene.sprite_1.setTexture(scene.texture_1);
    scene.sprite_1_rev.setTexture(scene.texture_1_rev);
    scene.sprite_2.setTexture(scene.texture_2);
    scene.sprite_2_rev.setTexture(scene.texture_2_rev);
    scene.sprite_3.setTexture(scene.texture_3);
    scene.sprite_3_rev.setTexture(scene.texture_3_rev);
    scene.sprite_4.setTexture(scene.texture_4);
    scene.sprite_4_rev.setTexture(scene.texture_4_rev);
    scene.sprite_bottom.setTexture(scene.texture_bottom);
    scene.sprite_top.setTexture(scene.texture_top);

    return true;
}

bool setup_background(SceneContext &scene, const sf::VideoMode &desktop_mode) {
    scene.screen_w_scale = (desktop_mode.width + 0.0f) / 1920;
    scene.screen_h_scale = (desktop_mode.height + 0.0f) / 1080;

    scene.window.create(sf::VideoMode(desktop_mode.width, 
                                      desktop_mode.height,
                                      desktop_mode.bitsPerPixel),
                        "Circaminx",
                        sf::Style::Fullscreen);

    if (!load_texture(scene.background_texture, "./assets/img/fond.png"))
        return false;

    scene.background_sprite.setTexture(scene.background_texture);
    scene.background_sprite.scale(scene.screen_w_scale, scene.screen_h_scale);

    return true;
}

bool setup_sprites(SceneContext &scene) {
    return load_textures(scene) && load_sprites(scene);
}

bool setup_texts(SceneContext &scene) {
    if (!scene.main_font.loadFromFile("./assets/fonts/utopia.ttf"))
        return false;

    scene.move_counter_text.setFont(scene.main_font);
    scene.move_counter_text.setFillColor(scene.success_color);
    scene.move_counter_text.setCharacterSize(90 * scene.screen_h_scale);
    scene.move_counter_text.setString("0");

    sf::FloatRect bounds = scene.move_counter_text.getLocalBounds();
    scene.move_counter_text.setPosition(scene.screen_w_scale * 1884 - bounds.width, scene.screen_h_scale * 958);

    return true;
}

bool setup_symbol_sprites(SceneContext &scene) {
    scene.symbol_sprites[0] = &scene.sprite_1;
    scene.symbol_sprites[1] = &scene.sprite_2;
    scene.symbol_sprites[2] = &scene.sprite_3;
    scene.symbol_sprites[3] = &scene.sprite_4;
    scene.symbol_sprites[4] = &scene.sprite_bottom;
    scene.symbol_sprites[5] = &scene.sprite_top;
    scene.symbol_sprites[6] = &scene.sprite_1_rev;
    scene.symbol_sprites[7] = &scene.sprite_2_rev;
    scene.symbol_sprites[8] = &scene.sprite_3_rev;
    scene.symbol_sprites[9] = &scene.sprite_4_rev;
    return true;
}
}

SceneContext::SceneContext() = default;

bool initialize_scene(SceneContext &scene)
{
    sf::VideoMode desktop_mode = sf::VideoMode::getDesktopMode();
    return setup_background(scene, desktop_mode)
        && setup_sprites(scene)
        && setup_texts(scene)
        && setup_symbol_sprites(scene);
}



