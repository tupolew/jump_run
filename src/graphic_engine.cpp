/*
 * Copyright (c) 2012, Samuel Memmel
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of the FreeBSD Project.#include "graphic_engine.hpp"
 */

#include <iostream>
#include <cstdlib>

#include <SDL/SDL.h>

Graphic_Engine::Graphic_Engine(Tile_Engine *tile_engine, Uint16 x_res, Uint16 y_res) {
	this->tile_engine = tile_engine;
	if (SDL_Init(SDL_INIT_VIDEO ) == -1) {
		std::cerr << "Error while SDL_Init: " << SDL_GetError();
		exit(EXIT_FAILURE);
	}
	this->x_res = x_res;
	this->y_res = y_res;
	screen = SDL_SetVideoMode(x_res, y_res, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_HWACCEL | SDL_SRCALPHA);
	if (screen == NULL) {
		std::cerr << "Error while SDL_SetVideoMode(): " << SDL_GetError();
		exit(EXIT_FAILURE);
	}
	textures = new SDL_Surface*[10];
	textures[0] = IMG_Load("./textures/texture01.png");
	textures[1] = IMG_Load("./textures/texture02.png");
	textures[2] = IMG_Load("./textures/texture03.png");
	textures[3] = IMG_Load("./textures/texture04.png");
}

Graphic_Engine::~Graphic_Engine() {
	SDL_Quit();
}

void Graphic_Engine::drawWorld(int x, int y) {
	SDL_Rect rect = {0, 0, x_res, y_res};
	SDL_MapRGB( screen->format, 0, 0, 0 );
	for (int i = (y+y_res/2.0)/32; i <= (y-y_res/2.0)/32; i--) {
		for (int k = 0; k <= x_res/32; k++) {

		}
	}
}
