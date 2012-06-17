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

#include "player/evelator.hpp"

#include <iostream>
#include <cstdlib>

#include "SDL/SDL_image.h"

void Evelator::set_size(position _size) {
	size = _size;
}

Evelator::Evelator(position _pos, position _size, position _vel, SDL_Surface *_surface, Tile_Engine *_tile_engine) {
	texture =  _surface;
	pos = _pos;
	size = _size;
	vel = _vel;
	priority = 127;
	tile_engine = _tile_engine;
}

void Evelator::kill() {

}

position Evelator::get_position() {
	return pos;
}
position Evelator::get_size() {
	return size;
}

bool Evelator::can_collide_player(char _priority) {
	return COLLIDE;
	//return (_priority >= priority)?Player::COLLIDE:Player::N_COLLIDE;
}

void Evelator::event(int _event, position _pos, Player *_enemy, bool _state) {
	if (_state == Evelator::ACTIVE) {
		switch(_event) {
		case Evelator::TOP:
			_enemy->force_push(position {_enemy->get_position().x, pos.y-_enemy->get_size().y});
			break;
		case Evelator::BOTTOM:
			_enemy->force_push(position {_enemy->get_position().x, pos.y+size.y});
			break;
		default:
			std::cerr << "Error: Got an impossible event at Evelator::event(). Eventnumber is " << _event << "\n";
			exit(1);
		}
	} else {
		switch(_event) {
		case Evelator::LEFT:
			_enemy->force_push(position {pos.x-_enemy->get_size().x, _enemy->get_position().y} );
			break;
		case Evelator::RIGHT:
			_enemy->force_push(position {pos.x+size.x, _enemy->get_position().y} );
			break;
		case Evelator::TOP:
			_enemy->force_push(position {_enemy->get_position().x, pos.y-_enemy->get_size().y} );
			break;
		case Evelator::BOTTOM:
			_enemy->force_push(position {_enemy->get_position().x, pos.y+size.y} );
			break;
		}

	}
}

char Evelator::get_priority() {
	return priority;
}

void Evelator::set_priority(char _priority) {
	priority = _priority;
}

position Evelator::calculate(double time) {
	position calc_pos = pos;
	position new_pos = pos;
	if (vel.x != 0) {
		calc_pos.x = pos.x + time*vel.x;
		new_pos.x = tile_engine->get_x_collision_move(pos.x, calc_pos.x, pos.y, size.x, size.y);
		if (new_pos.x != calc_pos.x)
			vel.x = (-1)*vel.x;
	}
	if (vel.y != 0) {
		calc_pos.y = pos.y + time*vel.y;
		new_pos.y = tile_engine->get_y_collision_move(pos.y, calc_pos.y, pos.x, size.x, size.y);
		if (new_pos.y != calc_pos.y)
			vel.y = (-1)*vel.y;
	}
	pos = new_pos;
	return new_pos;
}

void Evelator::rem_collision_player(Player *_player) {
	players.remove(_player);
}

void Evelator::add_collision_player(Player *_player) {
	players.push_back(_player);
}



