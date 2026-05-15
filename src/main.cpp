#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <cstdlib>
#include <ctime>

#include "app_state.hpp"
#include "game_loop.hpp"
#include "game_logic.hpp"
#include "runtime_ui.hpp"
#include "scene_context.hpp"
#include "scene_setup.hpp"
#include "util.hpp"

using namespace std;

int main()
{
	srand((unsigned int)time(NULL));

	SceneContext scene;
	if (!initialize_scene(scene))
		return EXIT_FAILURE;

	AppState state = {
		{0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
		{0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
		0,
		false,
		false,
		false,
		0.0,
		{false, ""}};

	RuntimeUi runtime_ui;
	if (!initialize_runtime_ui(runtime_ui, scene))
		return EXIT_FAILURE;

	initialize_position(state.position);
	copy_array_10(state.saved_position, state.position);

	if (!run_game_loop(scene, state, runtime_ui))
		return EXIT_FAILURE;

	return 0;
}
