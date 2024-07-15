#include <SDL2/SDL.h>
#include <stdint.h>
#include "SDL_timer.h"
#include "app.h"
#include "gamestate.h"
#include "input.h"

void render(App* app, GameState* game) {
	SDL_SetRenderDrawColor(app->renderer, 0, 0, 255, 255);
	SDL_RenderClear(app->renderer);

	SDL_FRect rect = { game->x, game->y, 200.0, 200.0 };
	SDL_SetRenderDrawColor(app->renderer, 0, 255, 255, 255);
	SDL_RenderFillRectF(app->renderer, &rect);
	SDL_RenderPresent(app->renderer);
}


void poll_events(App* app, GameState* game, Input* input) {
	input_update(input);
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			app->quit = 1;
			return;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
				app->quit = 1;
			input_key_down(input, event.key.keysym.scancode);
			break;
		case SDL_KEYUP:
			input_key_up(input, event.key.keysym.scancode);
			break;
		}
	}
}


void input_set_keys(Input* input) {
	input_set_key(input, SDL_SCANCODE_UP, INPUT_UP);
	input_set_key(input, SDL_SCANCODE_DOWN, INPUT_DOWN);
	input_set_key(input, SDL_SCANCODE_LEFT, INPUT_LEFT);
	input_set_key(input, SDL_SCANCODE_RIGHT, INPUT_RIGHT);
}


const float PLAYER_SPEED = 2.0f;
void update(GameState* game, Input* input) {
	int dy = (input_is_pressed(input, INPUT_UP) ? -1 : 0) +
		(input_is_pressed(input, INPUT_DOWN) ? 1 : 0);
	int dx = (input_is_pressed(input, INPUT_LEFT) ? -1 : 0) +
		(input_is_pressed(input, INPUT_RIGHT) ? 1 : 0);

	game->x += dx * PLAYER_SPEED;
	game->y += dy * PLAYER_SPEED;
}


int main() {
	GameState game = { 220, 100 };
	App app = app_create();
	Input input = input_create();
	input_set_keys(&input);

	uint64_t last_time, current_time = SDL_GetTicks64();
	uint64_t delta_time = 0;
	const uint64_t FPS_TICKS = 1000 / 60;
	while (!app.quit) {
		current_time = SDL_GetTicks64();
		delta_time = current_time - last_time;

		poll_events(&app, &game, &input);
		update(&game, &input);
		render(&app, &game);

		if (delta_time < FPS_TICKS)
			SDL_Delay(FPS_TICKS - delta_time);
		last_time = current_time;
	}
	
	app_destroy(&app);
	return 0;
}

