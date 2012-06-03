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
#include "graphic_engine.hpp"
#include "tile_engine.hpp"
#include "player/player.hpp"
#include "player/human_player.hpp"
#include "player/evelator.hpp"

#include <iostream>
#include <list>
#include <SDL/SDL.h>


int main(int argc, char *argv[]) {
	Tile_Engine tile("01.level");
	Human_Player human_player(0, 32.0, 32.0, 32.0, 10.0, &tile);
	Evelator evelator(64.0, 32.0, 128.0, 16.0, 0.0, 15.0, &tile);
	std::list<Player *> players;
	players.push_front(dynamic_cast<Player *>(&human_player));
	players.push_front(dynamic_cast<Player *>(&evelator));
	Graphic_Engine graphic(&tile, 1024, 768, players);
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTTHREAD) == -1) {
		std::cerr << "Error while SDL_Init: " << SDL_GetError();
		exit(EXIT_FAILURE);
	}
	atexit(SDL_Quit);
	human_player.setTexture(SDL_DisplayFormatAlpha(IMG_Load("./textures/tux_1.png")));
	evelator.setTexture(SDL_DisplayFormat(IMG_Load("./textures/aufzug_1.png")));
	SDL_Event event;
	Uint32 t0=0;
	Uint32 t1=0;
	Uint32 delta_t=0;
	while(1) {
		human_player.key_event(&event);
		t1 = SDL_GetTicks();
		delta_t = t1-t0;
		t0 = t1;
		std::cout << 1000/delta_t << "\n";
		human_player.calculate((double)delta_t/80.0);
		evelator.calculate((double)delta_t/80.0);
		graphic.drawWorld(human_player.get_x_pos()-300,0);
		//std::cout << player.get_y_pos() << "\n";
		//SDL_Delay(50);
	}
	SDL_Quit();
	return 0;
}
