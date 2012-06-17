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
#include "player_engine.hpp"
#include "tile_engine.hpp"
#include "player/player.hpp"
#include "player/human_player.hpp"
#include "player/evelator.hpp"
#include "player/clubmate.hpp"
#include "player/cannon.hpp"

#include <iostream>
#include <list>
#include <SDL/SDL.h>

#include "player/human_player.hpp"


int main(int argc, char *argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTTHREAD) == -1) {
		std::cerr << "Error while SDL_Init: " << SDL_GetError();
		exit(EXIT_FAILURE);
	}
	atexit(SDL_Quit);

	Tile_Engine tile_engine("01.level");
	Player_Engine player_engine(&tile_engine);
	Graphic_Engine graphic_engine(&tile_engine, 1024, 768, &player_engine);



	Uint32 t0=0;
	Uint32 t1=0;
	Uint32 delta_t=0;
	while(1) {
		t1 = SDL_GetTicks();
		delta_t = t1-t0;
		t0 = t1;
		//std::cout << 1000/delta_t << "\n";
		player_engine.run((double)delta_t/80.0);
		graphic_engine.drawWorld(player_engine.get_human_player()->get_position().x-300,0);
		//std::cout << player.get_y_pos() << "\n";
		//SDL_Delay(50);
	}
	SDL_Quit();
	return 0;
}
