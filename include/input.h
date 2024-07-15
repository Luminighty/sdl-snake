#ifndef _INPUT_H_
#define _INPUT_H_

#include <stdbool.h>
#include <SDL.h>
#include "SDL_scancode.h"


typedef enum {
	INPUT_UP,
	INPUT_DOWN,
	INPUT_LEFT,
	INPUT_RIGHT,

	INPUT_SIZE,
} InputKey;


typedef enum {
	INPUTSTATE_RELEASED,
	INPUTSTATE_IDLE,
	INPUTSTATE_PRESSED,
	INPUTSTATE_HELD,
} InputState;


typedef struct {
	InputState state[INPUT_SIZE];
	InputKey keymap[SDL_NUM_SCANCODES];
} Input;


Input input_create();
void input_update(Input* input);
void input_key_down(Input* input, SDL_Scancode keycode);
void input_key_up(Input* input, SDL_Scancode keycode);
void input_set_key(Input* input, SDL_Scancode sdl_key, InputKey key);

bool input_is_pressed(const Input* input, InputKey key);
bool input_is_just_pressed(const Input* input, InputKey key);
bool input_is_released(const Input* input, InputKey key);
bool input_is_just_released(const Input* input, InputKey key);


#endif // _INPUT_H_
