//
// Copyright (c) 2012, Samuel Memmel
// All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// The views and conclusions contained in the software and documentation are those
// of the authors and should not be interpreted as representing official policies,
// either expressed or implied, of the FreeBSD Project.#include "graphic_engine.hpp"
//

#include <iostream>
#include <cstdlib>
//#include <fenv.h>
#include <math.h>

#include <SDL/SDL.h>

#include "graphic_engine.hpp"

Graphic_Engine::Graphic_Engine(Tile_Engine *tile_engine, Uint16 x_res, Uint16 y_res, std::list<Player *> _players) {
	players = _players;
	this->tile_engine = tile_engine;
	/*if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1) {
		std::cerr << "Error while SDL_Init: " << SDL_GetError();
		exit(EXIT_FAILURE);
	}*/
	this->x_res = x_res;
	this->y_res = y_res;
	screen = SDL_SetVideoMode(x_res, y_res, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_HWACCEL | SDL_SRCALPHA);
	if (screen == NULL) {
		std::cerr << "Error while SDL_SetVideoMode(): " << SDL_GetError();
		exit(EXIT_FAILURE);
	}
	SDL_Surface *background_tmp = IMG_Load("./textures/background_01.png");
	background = SDL_DisplayFormat(background_tmp);
	//background = IMG_Load("./textures/background_01.png");
	SDL_FreeSurface(background_tmp);
	SDL_Surface** textures_tmp = new SDL_Surface*[38];
	textures_tmp[1] = IMG_Load("./textures/oben_1.png");
	textures_tmp[2] = IMG_Load("./textures/oben_2_1.png");
	textures_tmp[3] = IMG_Load("./textures/oben_2_2.png");
	textures_tmp[4] = IMG_Load("./textures/oben_3.png");
	textures_tmp[5] = IMG_Load("./textures/oben_4.png");
	textures_tmp[6] = IMG_Load("./textures/oben_5.png");
	textures_tmp[7] = IMG_Load("./textures/mitte_0.png");
	textures_tmp[8] = IMG_Load("./textures/rechts_1_1.png");
	textures_tmp[9] = IMG_Load("./textures/rechts_1_2.png");
	textures_tmp[10] = IMG_Load("./textures/links_1_1.png");
	textures_tmp[11] = IMG_Load("./textures/links_1_2.png");
	textures_tmp[12] = IMG_Load("./textures/oben_6_1.png");
	textures_tmp[13] = IMG_Load("./textures/oben_6_2.png");
	textures_tmp[14] = IMG_Load("./textures/oben_7.png");
	textures_tmp[15] = IMG_Load("./textures/oben_7.png");
	textures_tmp[16] = IMG_Load("./textures/skellet_1_1.png");
	textures_tmp[17] = IMG_Load("./textures/skellet_2_1.png");
	textures_tmp[18] = IMG_Load("./textures/skellet_3_1.png");
	textures_tmp[19] = IMG_Load("./textures/skellet_1_2.png");
	textures_tmp[20] = IMG_Load("./textures/skellet_2_2.png");
	textures_tmp[21] = IMG_Load("./textures/skellet_3_2.png");
	textures_tmp[22] = IMG_Load("./textures/skellet_2_3.png");
	textures_tmp[23] = IMG_Load("./textures/skellet_3_3.png");
	textures_tmp[24] = IMG_Load("./textures/bone_1_1.png");
	textures_tmp[25] = IMG_Load("./textures/bone_1_2.png");
	textures_tmp[26] = IMG_Load("./textures/human_1_1.png");
	textures_tmp[27] = IMG_Load("./textures/human_2_1.png");
	textures_tmp[28] = IMG_Load("./textures/human_3_1.png");
	textures_tmp[29] = IMG_Load("./textures/human_4_1.png");
	textures_tmp[30] = IMG_Load("./textures/human_5_1.png");
	textures_tmp[31] = IMG_Load("./textures/human_1_2.png");
	textures_tmp[32] = IMG_Load("./textures/human_2_2.png");
	textures_tmp[33] = IMG_Load("./textures/human_3_2.png");
	textures_tmp[34] = IMG_Load("./textures/human_4_2.png");
	textures_tmp[35] = IMG_Load("./textures/human_5_2.png");
	textures_tmp[36] = IMG_Load("./textures/human_4_3.png");
	textures_tmp[37] = IMG_Load("./textures/kiste_1.png");
	textures = new SDL_Surface*[38];
	textures[1] = SDL_DisplayFormat(textures_tmp[1]);
	textures[2] = SDL_DisplayFormat(textures_tmp[2]);
	textures[3] = SDL_DisplayFormat(textures_tmp[3]);
	textures[4] = SDL_DisplayFormat(textures_tmp[4]);
	textures[5] = SDL_DisplayFormat(textures_tmp[5]);
	textures[6] = SDL_DisplayFormat(textures_tmp[6]);
	textures[7] = SDL_DisplayFormat(textures_tmp[7]);
	textures[8] = SDL_DisplayFormat(textures_tmp[8]);
	textures[9] = SDL_DisplayFormatAlpha(textures_tmp[9]);
	textures[10] = SDL_DisplayFormatAlpha(textures_tmp[10]);
	textures[11] = SDL_DisplayFormat(textures_tmp[11]);
	textures[12] = SDL_DisplayFormat(textures_tmp[12]);
	textures[13] = SDL_DisplayFormat(textures_tmp[13]);
	textures[14] = SDL_DisplayFormat(textures_tmp[14]);
	textures[15] = SDL_DisplayFormat(textures_tmp[15]);
	textures[16] = SDL_DisplayFormat(textures_tmp[16]);
	textures[17] = SDL_DisplayFormat(textures_tmp[17]);
	textures[18] = SDL_DisplayFormat(textures_tmp[18]);
	textures[19] = SDL_DisplayFormat(textures_tmp[19]);
	textures[20] = SDL_DisplayFormat(textures_tmp[20]);
	textures[21] = SDL_DisplayFormat(textures_tmp[21]);
	textures[22] = SDL_DisplayFormat(textures_tmp[22]);
	textures[23] = SDL_DisplayFormat(textures_tmp[23]);
	textures[24] = SDL_DisplayFormat(textures_tmp[24]);
	textures[25] = SDL_DisplayFormat(textures_tmp[25]);
	textures[26] = SDL_DisplayFormat(textures_tmp[26]);
	textures[27] = SDL_DisplayFormat(textures_tmp[27]);
	textures[28] = SDL_DisplayFormat(textures_tmp[28]);
	textures[29] = SDL_DisplayFormat(textures_tmp[29]);
	textures[30] = SDL_DisplayFormat(textures_tmp[30]);
	textures[31] = SDL_DisplayFormat(textures_tmp[31]);
	textures[32] = SDL_DisplayFormat(textures_tmp[32]);
	textures[33] = SDL_DisplayFormat(textures_tmp[33]);
	textures[34] = SDL_DisplayFormat(textures_tmp[34]);
	textures[35] = SDL_DisplayFormat(textures_tmp[35]);
	textures[36] = SDL_DisplayFormat(textures_tmp[36]);
	textures[37] = SDL_DisplayFormat(textures_tmp[37]);
	SDL_FreeSurface(textures_tmp[1]);
	SDL_FreeSurface(textures_tmp[2]);
	SDL_FreeSurface(textures_tmp[3]);
	SDL_FreeSurface(textures_tmp[4]);
	SDL_FreeSurface(textures_tmp[5]);
	SDL_FreeSurface(textures_tmp[6]);
	SDL_FreeSurface(textures_tmp[7]);
	SDL_FreeSurface(textures_tmp[8]);
	SDL_FreeSurface(textures_tmp[9]);
	SDL_FreeSurface(textures_tmp[10]);
	SDL_FreeSurface(textures_tmp[11]);
	SDL_FreeSurface(textures_tmp[12]);
	SDL_FreeSurface(textures_tmp[13]);
	SDL_FreeSurface(textures_tmp[14]);
	SDL_FreeSurface(textures_tmp[15]);
	SDL_FreeSurface(textures_tmp[16]);
	SDL_FreeSurface(textures_tmp[17]);
	SDL_FreeSurface(textures_tmp[18]);
	SDL_FreeSurface(textures_tmp[19]);
	SDL_FreeSurface(textures_tmp[20]);
	SDL_FreeSurface(textures_tmp[21]);
	SDL_FreeSurface(textures_tmp[22]);
	SDL_FreeSurface(textures_tmp[23]);
	SDL_FreeSurface(textures_tmp[24]);
	SDL_FreeSurface(textures_tmp[25]);
	SDL_FreeSurface(textures_tmp[26]);
	SDL_FreeSurface(textures_tmp[27]);
	SDL_FreeSurface(textures_tmp[28]);
	SDL_FreeSurface(textures_tmp[29]);
	SDL_FreeSurface(textures_tmp[30]);
	SDL_FreeSurface(textures_tmp[31]);
	SDL_FreeSurface(textures_tmp[32]);
	SDL_FreeSurface(textures_tmp[33]);
	SDL_FreeSurface(textures_tmp[34]);
	SDL_FreeSurface(textures_tmp[35]);
	SDL_FreeSurface(textures_tmp[36]);
	SDL_FreeSurface(textures_tmp[37]);
}

Graphic_Engine::~Graphic_Engine() {
	SDL_Quit();
}

void Graphic_Engine::drawWorld(int x, int y) {
	//fesetround(FE_DOWNWARD);
	SDL_BlitSurface(background, &SDL_Rect {0, 0, x_res, y_res}, screen, &SDL_Rect {0, 0, x_res, y_res});
	SDL_MapRGB( screen->format, 0, 0, 0 );
	int surface_num;
	for (int i1 = tile_engine->get_y_size()*32-y, i2 = y_res-fmod(fmod(y,32),32); i2 >= 0 && i1 >= 0; i1-=32, i2-=32) {
		for (int k1 = tile_engine->get_x_size()*32-x, k2 = 0-fmod(x,32); k2 <= x_res && k1 >= 0; k2+=32, k1-=32) {
			Tile *tile = tile_engine->getTile((k2+x)/32, i1/32);
			if (tile != NULL && (surface_num = tile->getSurface()) != 0) {
				SDL_BlitSurface(textures[surface_num], &SDL_Rect {0, 0, 32, 32}, screen, &SDL_Rect {(Sint16)k2, (Sint16)i2, 32, 32});
			}
		}
	}
	std::list<Player *>::iterator iterator;
	for(iterator = players.begin(); iterator != players.end(); iterator++) {
		SDL_BlitSurface((*iterator)->getTexture(), &SDL_Rect {0, 0, (*iterator)->get_x_size(), (*iterator)->get_y_size()}, screen, &SDL_Rect {(*iterator)->get_x_pos()-x, (*iterator)->get_y_pos()-(tile_engine->get_y_size()*32-y_res-y), (*iterator)->get_x_size(), (*iterator)->get_y_size()});
	}
	//SDL_BlitSurface(player_human, &SDL_Rect {0, 0, 32, 32}, screen, &SDL_Rect {(Sint16)human_player->get_x_pos()-x, (Sint16)human_player->get_y_pos()-(tile_engine->get_y_size()*32-y_res-y), 32, 32});
	SDL_Flip(screen);
}
