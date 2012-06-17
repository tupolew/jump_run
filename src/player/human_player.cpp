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


char Human_Player::get_priority() {
	return priority;
}

void Human_Player::set_size(position _size) {
	size = _size;
}

void Human_Player::kill() {
	std::cout << "Game Over" << "\n";
}

void Human_Player::set_priority(char _priority) {
	priority = _priority;
}

Human_Player::Human_Player(position _pos, position _size, double _gravity, SDL_Surface *_surface, Tile_Engine *_tile_engine, Player_Engine *player_engine) {
	texture = _surface;
	pos =_pos;
	gravity = _gravity;
	size = _size;
	tile_engine = _tile_engine;
	keys[0] = false;
	keys[1] = false;
	keys[2] = false;
	keys[3] = false;
	priority = 0;
	event_ = new SDL_Event;
}


position Human_Player::calculate(double time) {
	key_event(event_);
	if (vel.x == 0) {
		if (keys[right]) {
			vel.x = 5.0;
		} else if (keys[left]) {
			vel.x = -5.0;
		}
	}
	if (tile_engine->does_bottom_collide(pos, size) == Tile_Engine::COLLIDES || player_engine->touch_bottom(this, players_collision) == Player::COLLIDE) {
		if (keys[up])
			vel.y = -60.0;
		if (vel.x != 0){
			if (keys[right])
				vel.x = ( 2.0*time+vel.x >  30.0)? 30.0: 2.0*time+vel.x;
			if (keys[left])
				vel.x = (-2.0*time+vel.x < -30.0)?-30.0:-2.0*time+vel.x;
		}
		if (keys[down])
			vel.x = 0;
		vel.x=(vel.x > 0)?vel.x-0.8*time:vel.x+0.8*time;
	} else {
		vel.y = vel.y+15*time;
	}
	position new_pos = pos;
	if (vel.x != 0) {
		double new_x = pos.x + time*vel.x;
		new_pos.x = tile_engine->get_x_collision_move(pos.x, new_x, pos.y, size.x, size.y);
		if (new_pos.x != new_x)
			vel.x = 0;
		pos.x = new_pos.x;
	}
	if (vel.y != 0) {
		double new_y = pos.y + time*vel.y;
		new_pos.y = tile_engine->get_y_collision_move(pos.y, new_y, pos.x, size.x, size.y);
		if (new_pos.y != new_y)
			vel.y = 0;
		pos.y = new_pos.y;
	}
	return new_pos;
}


void Human_Player::key_event(SDL_Event *_event) {
	if (SDL_PollEvent( _event )) {
		switch(_event->type) {
			case SDL_KEYDOWN:
				switch(_event->key.keysym.sym){
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
				switch(_event->key.keysym.sym){
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

void Human_Player::rem_collision_player(Player *_player) {
	players_collision.remove(_player);
}

void Human_Player::add_collision_player(Player *_player) {
	players_collision.push_back(_player);
}

bool Human_Player::can_collide_player(char _priority) {
	return Player::N_COLLIDE;
}

void Human_Player::force_push(position _pos) {
	if (pos.y > _pos.y)
		vel.y = 0;
	else if (_pos.y > pos.y && vel.y < 0)
		vel.y = 0;
	pos.y = tile_engine->get_y_collision_move(pos.y, _pos.y, pos.x, size.x, size.y);
	pos.x = tile_engine->get_x_collision_move(pos.x, _pos.x, pos.y, size.x, size.y);
}


void Human_Player::event(int event, position pos, Player *enemy, bool state) {

}

void Human_Player::setTexture(SDL_Surface *_texture) {
	//if (texture != NULL)
		//SDL_FreeSurface(texture);
	texture = _texture;
}

position Human_Player::get_position() {
	return pos;
}

position Human_Player::get_size() {
	return size;
}
