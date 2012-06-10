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

#include <iostream>

#include <cmath>

Human_Player::Human_Player(double _pos_x, double _pos_y, double _size_x, double _size_y, double _gravity, Tile_Engine *_tile_engine) {
	pos_x = _pos_x;
	pos_y = _pos_y;
	gravity = _gravity;
	tile_engine = _tile_engine;
	size_x = _size_x;
	size_y = _size_y;
	keys[0] = false;
	keys[1] = false;
	keys[2] = false;
	keys[3] = false;
}

bool Human_Player::check_y_bottom_collision() {
	std::list<Player *>::iterator iterator;
	for (iterator = players_collision.begin(); iterator != players_collision.end(); iterator++) {
		if ( (	( (*iterator)->get_x_pos() <= pos_x && (*iterator)->get_x_pos()+(*iterator)->get_x_size() >= pos_x ) ||
			( (*iterator)->get_x_pos() >= pos_x && (*iterator)->get_x_pos()+(*iterator)->get_x_size() <= pos_x+size_x ) ||
			( (*iterator)->get_x_pos() <= pos_x+size_x && (*iterator)->get_x_pos()+(*iterator)->get_x_size() >= pos_x+size_x ) )
			&& (*iterator)->get_y_pos() == pos_y+size_x) {

			return Tile_Engine::COLLIDES;
		}
	}

	return Tile_Engine::N_COLLIDES;
}

void Human_Player::calculate(double time) {
	if (vel_x == 0) {
		if (keys[right]) {
			vel_x = 9.0;
		} else if (keys[left]) {
			vel_x = -9.0;
		}
	}
	if (tile_engine->does_bottom_collide(pos_x, pos_y, size_x, size_y) == Tile_Engine::COLLIDES || check_y_bottom_collision() == Tile_Engine::COLLIDES) {
			if (keys[up]) {
				vel_y = -40.0;
			}
			if (vel_x != 0){
				if (keys[right])
					vel_x = ( 2.0*time+vel_x >  30.0)? 30.0: 2.0*time+vel_x;
				if (keys[left])
					vel_x = (-2.0*time+vel_x < -30.0)?-30.0:-2.0*time+vel_x;
			}
			vel_x=(vel_x > 0)?vel_x-0.8*time:vel_x+0.8*time;
	} else {
		vel_y = vel_y+7*time;
	}
	if (vel_x != 0) {
			double _pos_x = pos_x + time*vel_x;
			double __pos_x = pos_x;
			pos_x = tile_engine->get_x_collision_move(pos_x, _pos_x, pos_y, size_x, size_y);
			if (pos_x > __pos_x) {
				std::list<Player *>::iterator iterator;
				for(iterator = players_collision.begin(); iterator != players_collision.end(); iterator++) {
					/*if ((*iterator)->get_x_pos() >= __pos_x+size_x && (*iterator)->get_x_pos() < pos_x+size_x)
						(*iterator)->force_push(pos_x+size_x, (*iterator)->get_y_pos());*/
				}
			} else if (pos_x < _pos_x) {
				std::list<Player *>::iterator iterator;
				for(iterator = players_collision.begin(); iterator != players_collision.end(); iterator++) {
					if ((*iterator)->get_x_pos()+(*iterator)->get_x_size() <= __pos_x && (*iterator)->get_x_pos()+(*iterator)->get_x_size() > pos_x)
						(*iterator)->force_push(pos_x-(*iterator)->get_x_size(), (*iterator)->get_y_pos());
				}
			}
			if (_pos_x != pos_x)
				vel_x = 0;
		}
		if (vel_y != 0) {
			double _pos_y = pos_y + time*vel_y;
			double __pos_y = pos_y;
			pos_y = tile_engine->get_y_collision_move(pos_y, _pos_y, pos_x, size_x, size_y);
			if (pos_y > __pos_y) {
				std::list<Player *>::iterator iterator;
				for(iterator = players_collision.begin(); iterator != players_collision.end(); iterator++) {
					if ( (	( (*iterator)->get_x_pos() <= pos_x && (*iterator)->get_x_pos()+(*iterator)->get_x_size() >= pos_x ) ||
							( (*iterator)->get_x_pos() >= pos_x && (*iterator)->get_x_pos()+(*iterator)->get_x_size() <= pos_x+size_x ) ||
							//( (*iterator)->get_x_pos() <= pos_x+size_x && (*iterator)->get_x_pos()+(*iterator)->get_x_size() >= pos_x+size_x)
							( (*iterator)->get_x_pos() <= pos_x+size_x && (*iterator)->get_x_pos()+(*iterator)->get_x_size() >= pos_x+size_x ) )
							&& ((*iterator)->get_y_pos() >= __pos_y+size_y && (*iterator)->get_y_pos() < pos_y+size_y))
						pos_y = __pos_y;
				}
			} else if (pos_y < __pos_y) {
				std::list<Player *>::iterator iterator;
				for(iterator = players_collision.begin(); iterator != players_collision.end(); iterator++) {
					if ( (	( (*iterator)->get_x_pos() <= pos_x && (*iterator)->get_x_pos()+(*iterator)->get_x_size() >= pos_x ) ||
							( (*iterator)->get_x_pos() >= pos_x && (*iterator)->get_x_pos()+(*iterator)->get_x_size() <= pos_x+size_x ) ||
							( (*iterator)->get_x_pos() <= pos_x+size_x && (*iterator)->get_x_pos()+(*iterator)->get_x_size() >= pos_x+size_x ) )
							&& ((*iterator)->get_y_pos()+(*iterator)->get_y_size() <= __pos_y && (*iterator)->get_y_pos()+(*iterator)->get_y_size() >= pos_y))
						pos_y = __pos_y;
				}
			}
			if (_pos_y != pos_y)
				vel_y = 0;
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

void Human_Player::remove_player(Player *player) {
	players_collision.remove(player);
	players_top_food_chain.remove(player);
	players_bottom_food_chain.remove(player);
}

void Human_Player::add_player_collision(Player *player) {
	players_collision.push_back(player);
}

void Human_Player::add_player_top_food_chain(Player *player) {
	players_top_food_chain.push_back(player);
}

void Human_Player::add_player_bottom_food_chain(Player *player) {
	players_bottom_food_chain.push_back(player);
}

void Human_Player::force_push(double _pos_x, double _pos_y) {
	pos_x = _pos_x;
	pos_y = _pos_y;
}
