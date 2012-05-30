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

Graphic_Engine::Graphic_Engine(Tile_Engine *tile_engine, Uint16 x_res, Uint16 y_res, Player *player) {
	this->tile_engine = tile_engine;
	/*if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1) {
		std::cerr << "Error while SDL_Init: " << SDL_GetError();
		exit(EXIT_FAILURE);
	}*/
	human_player = player;
	this->x_res = x_res;
	this->y_res = y_res;
	screen = SDL_SetVideoMode(x_res, y_res, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_HWACCEL | SDL_SRCALPHA);
	if (screen == NULL) {
		std::cerr << "Error while SDL_SetVideoMode(): " << SDL_GetError();
		exit(EXIT_FAILURE);
	}
	player_human = IMG_Load("./textures/tux_1.png");
	background = IMG_Load("./textures/background_01.png");
	textures = new SDL_Surface*[36];
	textures[1] = IMG_Load("./textures/oben_1.png");
	textures[2] = IMG_Load("./textures/oben_2_1.png");
	textures[3] = IMG_Load("./textures/oben_2_2.png");
	textures[4] = IMG_Load("./textures/oben_3.png");
	textures[5] = IMG_Load("./textures/oben_4.png");
	textures[6] = IMG_Load("./textures/oben_5.png");
	textures[7] = IMG_Load("./textures/mitte_0.png");
	textures[8] = IMG_Load("./textures/rechts_1_1.png");
	textures[9] = IMG_Load("./textures/rechts_1_2.png");
	textures[10] = IMG_Load("./textures/links_1_1.png");
	textures[11] = IMG_Load("./textures/links_1_2.png");
	textures[12] = IMG_Load("./textures/oben_6_1.png");
	textures[13] = IMG_Load("./textures/oben_6_2.png");
	textures[14] = IMG_Load("./textures/oben_7.png");
	textures[15] = IMG_Load("./textures/oben_7.png");
	textures[16] = IMG_Load("./textures/skellet_1_1.png");
	textures[17] = IMG_Load("./textures/skellet_2_1.png");
	textures[18] = IMG_Load("./textures/skellet_3_1.png");
	textures[19] = IMG_Load("./textures/skellet_1_2.png");
	textures[20] = IMG_Load("./textures/skellet_2_2.png");
	textures[21] = IMG_Load("./textures/skellet_3_2.png");
	textures[22] = IMG_Load("./textures/skellet_2_3.png");
	textures[23] = IMG_Load("./textures/skellet_3_3.png");
	textures[24] = IMG_Load("./textures/bone_1_1.png");
	textures[25] = IMG_Load("./textures/bone_1_2.png");
	textures[26] = IMG_Load("./textures/human_1_1.png");
	textures[27] = IMG_Load("./textures/human_2_1.png");
	textures[28] = IMG_Load("./textures/human_3_1.png");
	textures[29] = IMG_Load("./textures/human_4_1.png");
	textures[30] = IMG_Load("./textures/human_5_1.png");
	textures[31] = IMG_Load("./textures/human_1_2.png");
	textures[32] = IMG_Load("./textures/human_2_2.png");
	textures[33] = IMG_Load("./textures/human_3_2.png");
	textures[34] = IMG_Load("./textures/human_4_2.png");
	textures[35] = IMG_Load("./textures/human_5_2.png");
	textures[36] = IMG_Load("./textures/human_4_3.png");

}

Graphic_Engine::~Graphic_Engine() {
	SDL_Quit();
}

void Graphic_Engine::drawWorld(int x, int y) {
	fesetround(FE_DOWNWARD);
	SDL_BlitSurface(background, &SDL_Rect {0, 0, x_res, y_res}, screen, &SDL_Rect {0, 0, x_res, y_res});
	SDL_MapRGB( screen->format, 0, 0, 0 );
	for (int i1 = tile_engine->get_y_size()*32-y, i2 = y_res-fmod(fmod(y,32),32); i2 >= 0 && i1 >= 0; i1-=32, i2-=32) {
		for (int k1 = tile_engine->get_x_size()*32-x, k2 = 0-fmod(x,32); k2 <= x_res && k1 >= 0; k2+=32, k1-=32) {
			Tile *tile = tile_engine->getTile((k2+x)/32, i1/32);
			SDL_BlitSurface(textures[tile->getSurface()], &SDL_Rect {0, 0, 32, 32}, screen, &SDL_Rect {(Sint16)k2, (Sint16)i2, 32, 32});
		}
	}
	SDL_BlitSurface(player_human, &SDL_Rect {0, 0, 32, 32}, screen, &SDL_Rect {(Sint16)human_player->get_x_pos(), (Sint16)human_player->get_y_pos()-(tile_engine->get_y_size()*32-y_res-y), 32, 32});
	SDL_Flip(screen);
}
