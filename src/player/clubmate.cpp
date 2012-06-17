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

#include "player/clubmate.hpp"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

ClubMate::ClubMate(position _pos, position _size, SDL_Surface *_surface, Tile_Engine *_tile_engine) {
	surface = _surface;
	pos = _pos;
	size = _size;
	vel.x = 30;
	vel.y = 0;
	priority = 1;
}

ClubMate::~ClubMate() {
	// TODO Auto-generated destructor stub
}

char ClubMate::get_priority() {
	return priority;
}

void ClubMate::set_priority(char _priority) {
	priority = _priority;
}

position ClubMate::get_position() {
	return pos;
}

position ClubMate::get_size() {
	return size;
}

void ClubMate::event(int event, position pos, Player *enemy, bool state) {
	enemy->set_size(position{64, 64});
	enemy->setTexture(SDL_DisplayFormatAlpha(IMG_Load("./textures/tux_big_1.png")));
}

bool ClubMate::can_collide_player(char _priority) {
	return Player::N_COLLIDE;
}

void ClubMate::add_collision_player(Player *player) {

}

void ClubMate::rem_collision_player(Player *player) {

}

void ClubMate::force_push(position _pos) {

}

void ClubMate::kill() {

}

void ClubMate::set_size(position _size) {

}

position ClubMate::calculate(double time) {
	position _pos;
	return _pos;
}

SDL_Surface *ClubMate::getTexture() {
	return surface;
}

void ClubMate::setTexture(SDL_Surface *_surface) {
	surface = _surface;
}
