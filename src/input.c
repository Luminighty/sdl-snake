#include "input.h"
#include <stdbool.h>



Input input_create() {
	Input input;
	for (int i = 0; i < INPUT_SIZE; i++)
		input.state[i] = INPUTSTATE_IDLE;
	for (int i = 0; i < SDL_NUM_SCANCODES; i++)
		input.keymap[i] = INPUT_SIZE;
	return input;
}


void input_set_key(Input* input, SDL_Scancode sdl_key, InputKey key) {
	input->keymap[sdl_key] = key;
}


bool input_is_pressed(const Input *input, InputKey key) {
	switch (input->state[key]) {
	case INPUTSTATE_PRESSED:
	case INPUTSTATE_HELD:
		return true;
	default:
		return false;
	}
}


bool input_is_just_released(const Input *input, InputKey key) {
	return input->state[key] == INPUTSTATE_RELEASED;
}

bool input_is_just_pressed(const Input *input, InputKey key) {
	return input->state[key] == INPUTSTATE_PRESSED;
}

bool input_is_released(const Input *input, InputKey key) {
	switch (input->state[key]) {
	case INPUTSTATE_RELEASED:
	case INPUTSTATE_IDLE:
		return true;
	default:
		return false;
	}
}

void input_key_down(Input* input, SDL_Scancode keycode) {
	InputKey key = input->keymap[keycode];
	if (key == INPUT_SIZE)
		return;
	input->state[key] = INPUTSTATE_PRESSED;
}


void input_key_up(Input* input, SDL_Scancode keycode) {
	InputKey key = input->keymap[keycode];
	if (key == INPUT_SIZE)
		return;
	input->state[key] = INPUTSTATE_RELEASED;
}


void input_update(Input* input) {
	for (int i = 0; i < INPUT_SIZE; i++) {
		switch (input->state[i]) {
		case INPUTSTATE_RELEASED:
			input->state[i] = INPUTSTATE_IDLE;
			break;
		case INPUTSTATE_PRESSED:
			input->state[i] = INPUTSTATE_HELD;
			break;
		default:
			break;
		}
	}
}
