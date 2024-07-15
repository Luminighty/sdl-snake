#include "app.h"
#include "config.h"

App app_create() {
	App app;

	SDL_Init(SDL_INIT_VIDEO);

	app.window = SDL_CreateWindow(
		"Snake", 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH, WINDOW_HEIGHT, 
		0
	);

	app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);
	app.quit = 0;

	return app;
}


void app_destroy(App *app) {
	SDL_DestroyRenderer(app->renderer);
	SDL_DestroyWindow(app->window);
}

