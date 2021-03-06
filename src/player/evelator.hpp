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
// either expressed or implied, of the FreeBSD Project.
//

#include "player/player.hpp"
#include "tile_engine.hpp"

#ifndef EVELATOR_HPP_
#define EVELATOR_HPP_

class Evelator : public Player {
public:
	Evelator(position _pos, position _size, position _vel, SDL_Surface *_surface, Tile_Engine *_tile_engine);
	~Evelator() {}
	char get_priority();
	void set_priority(char _priority);
	void kill();
	position get_position();
	position get_size();
	void set_size(position _size);

	void event(int event, position pos, Player *enemy, bool state);
	position calculate(double time);
	void setTexture(SDL_Surface *surface) {texture = surface;}
	void force_push(position _pos) {}
	bool can_collide_player(char _priority);
	void add_collision_player(Player *_player);
	void rem_collision_player(Player *_player);
	SDL_Surface *getTexture() {return texture;}
private:
	SDL_Surface *texture;
	std::list<Player *> players;
	Tile_Engine *tile_engine;
	position pos;
	position size;
	position vel;
	char priority;
};


#endif /* EVELATOR_HPP_ */
