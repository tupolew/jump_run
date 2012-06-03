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

#include <SDL/SDL.h>

#include "player/human_player.hpp"

#include <cmath>

Human_Player::Human_Player(double pos_x, double pos_y, double size_x, double size_y, double gravity, Tile_Engine *tile_engine) {
	_pos_x = pos_x;
	_pos_y = pos_y;
	_gravity = gravity;
	_tile_engine = tile_engine;
	_size_x = size_x;
	_size_y = size_y;
	keys[0] = false;
	keys[1] = false;
	keys[2] = false;
	keys[3] = false;
}

void Human_Player::calculate(double time) {
	if (_vel_x == 0) {
		if (keys[right]) {
			_vel_x = 9.0;
		} else if (keys[left]) {
			_vel_x = -9.0;
		}
	}
	if (_tile_engine->does_bottom_collide(_pos_x, _pos_y, _size_x, _size_y) == Tile_Engine::COLLIDES) {
			if (keys[up]) {
				_vel_y = -40.0;
			}
			if (_vel_x != 0){
				if (keys[right])
					_vel_x = ( 2.0*time+_vel_x >  30.0)? 30.0: 2.0*time+_vel_x;
				if (keys[left])
					_vel_x = (-2.0*time+_vel_x < -30.0)?-30.0:-2.0*time+_vel_x;
			}
			_vel_x=(_vel_x > 0)?_vel_x-0.8*time:_vel_x+0.8*time;
	} else {
		_vel_y = _vel_y+7*time;
	}
	if (_vel_y != 0) {
		double _pos_y_2 = _pos_y+time*_vel_y;
		_pos_y = _tile_engine->get_y_collision_move(_pos_y, _pos_y_2,_pos_x,_size_x,_size_y);
		if (_pos_y_2 != _pos_y)
			_vel_y = 0;
	}
	if (_vel_x != 0) {
		double _pos_x_2 = _pos_x+time*_vel_x;
		_pos_x = _tile_engine->get_x_collision_move(_pos_x, _pos_x_2,_pos_y,_size_x,_size_y);
		if (_pos_x_2 != _pos_x) {
			_vel_x = 0;
		}
	}
}


void Human_Player::key_event(SDL_Event *event) {
	if (SDL_PollEvent( event )) {
		switch(event->type) {
			case SDL_KEYDOWN:
				switch(event->key.keysym.sym){
					case SDLK_LEFT:
						keys[left]=true;
						break;
					case SDLK_RIGHT:
						keys[right]=true;
						break;
					case SDLK_SPACE:
						keys[up]=true;
						break;
					case SDLK_DOWN:
						keys[down]=true;
						break;
					case SDLK_UP:
						break;
					default:
						break;
					}
				break;
			case SDL_KEYUP:
				switch(event->key.keysym.sym){
					case SDLK_LEFT:
						keys[left]=false;
						break;
					case SDLK_RIGHT:
						keys[right]=false;
						break;
					case SDLK_SPACE:
						keys[up]=false;
						break;
					case SDLK_DOWN:
						keys[down]=false;
						break;
					case SDLK_UP:
						break;
					default:
						exit(0);
					}
			break;
		}
	}
}


