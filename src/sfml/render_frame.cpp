#include "render_frame.hpp"
#include "runtime_ui.hpp"
#include "scene_context.hpp"

void render_frame(SceneContext &scene, RuntimeUi &runtime_ui)
{
    scene.window.clear();

    scene.window.draw(scene.background_sprite);

    for (int k = 0; k < 10; k++)
        scene.window.draw(*scene.symbol_sprites[k]);

    scene.window.draw(scene.move_counter_text);
    scene.window.draw(runtime_ui.timer_text);
    scene.window.draw(runtime_ui.score_text);

    scene.window.display();
}
