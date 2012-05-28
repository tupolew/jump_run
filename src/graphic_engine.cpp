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
#include <fenv.h>
#include <math.h>

#include <SDL/SDL.h>

#include "graphic_engine.hpp"

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
	textures[1] = IMG_Load("./textures/texture01.png");
	textures[2] = IMG_Load("./textures/texture02.png");
	textures[3] = IMG_Load("./textures/texture03.png");
	textures[4] = IMG_Load("./textures/texture04.png");
}

Graphic_Engine::~Graphic_Engine() {
	SDL_Quit();
}

void Graphic_Engine::drawWorld(int x, int y) {
	fesetround(FE_DOWNWARD);
	//SDL_Rect rect = {0, 0, x_res, y_res};
	SDL_MapRGB( screen->format, 0, 0, 0 );
	for (int i1 = tile_engine->get_y_size()*32-y, i2 = y_res-32+fmod(y,32)+32; i2 >= 0; i1-=32, i2-=32) {
		for (int k = 0-fmod(x,32); k <= x_res; k+=32) {
			Tile *tile = tile_engine->getTile((k+x)/32, i1/32);
			SDL_BlitSurface(textures[tile->getSurface()], &SDL_Rect {0, 0, 32, 32}, screen, &SDL_Rect {(Sint16)k, (Sint16)i2, 32, 32});
		}
	}
	SDL_Flip(screen);
}
