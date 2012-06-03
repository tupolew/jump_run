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

#ifndef HUMAN_PLAYER_HPP_
#define HUMAN_PLAYER_HPP_

#include "player/player.hpp"

#include "tile_engine.hpp"

class Human_Player : public Player {
private:
	bool keys[4];
	enum {
		left = 0,
		right = 1,
		up = 2,
		down = 3
	};
public:
	Human_Player() = delete;
	Human_Player(double pos_x, double pos_y, double size_x, double size_y, double gravity, Tile_Engine *tile_engine);
	~Human_Player() {};
	double get_x_size() {return _size_x;}
	double get_y_size() {return _size_y;}
	double get_x_pos() {return _pos_x;}
	double get_y_pos() {return _pos_y;}
	std::list<Player*> get_enemys() {return enemies;}
	void set_enemys(std::list<Player*> enemies) {this->enemies = enemies;}
	void remove_enemy (Player *enemy) {enemies.remove(enemy);}
	void calculate(double time);
	void key_event(SDL_Event *event);
	void setTexture(SDL_Surface *surface) {texture = surface;}
	SDL_Surface *getTexture() {return texture;}
private:
	Tile_Engine *_tile_engine;
	std::list<Player*> enemies;
	SDL_Surface *texture;
	double _pos_x;
	double _pos_y;
	double _vel_x;
	double _vel_y;
	double _size_x;
	double _size_y;
	double _gravity;
};


#endif /* HUMAN_PLAYER_HPP_ */
