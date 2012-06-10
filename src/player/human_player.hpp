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
	Human_Player(double _pos_x, double _pos_y, double _size_x, double _size_y, double _gravity, Tile_Engine *_tile_engine);
	~Human_Player() {};
	double get_x_size() {return size_x;}
	double get_y_size() {return size_y;}
	double get_x_pos() {return pos_x;}
	double get_y_pos() {return pos_y;}
	void remove_player (Player *player);
	void add_player_top_food_chain(Player *player);
	void add_player_bottom_food_chain(Player *player);
	void add_player_collision(Player *player);
	void force_push(double _pos_x, double _pos_y);
	//void player_y_collision(double y1, double y2);
	bool check_y_bottom_collision();
	void calculate(double time);
	void key_event(SDL_Event *event);
	void setTexture(SDL_Surface *surface) {texture = surface;}
	SDL_Surface *getTexture() {return texture;}
private:
	Tile_Engine *tile_engine;
	std::list<Player *> players_collision;
	std::list<Player *> players_top_food_chain;
	std::list<Player *> players_bottom_food_chain;
	SDL_Surface *texture;
	double pos_x;
	double pos_y;
	double vel_x;
	double vel_y;
	double size_x;
	double size_y;
	double gravity;
};


#endif /* HUMAN_PLAYER_HPP_ */
