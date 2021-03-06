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
#ifndef TILE_ENGINE_HPP_
#define TILE_ENGINE_HPP_

#include "tile.hpp"
#include "player/player.hpp"

class Tile_Engine {
public:
	Tile_Engine() = delete;
	Tile_Engine(const char *file);
	~Tile_Engine();
	Tile *getTile(int x, int y);
	bool does_bottom_collide(position _pos, position _size);
	bool get_collision(double x, double y) {return (y <= y_size*32.0 && x <= x_size*32.0 && x >= 0 && y >=0 )?getTile(x/32,y/32)->getType():true;}
	double get_x_collision_move(double x1, double x2, double y1, double x_size, double y_size);
	double get_y_collision_move(double y1, double y2, double x1, double x_size, double y_size);
	int get_x_size() {return x_size;};
	int get_y_size() {return y_size;};
	Tile null;
private:
	int x_size;
	int y_size;
	Tile **tiles;
public:
	enum {
		N_COLLIDES = false,
		COLLIDES = true
	};
};

#endif /* TILE_ENGINE_HPP_ */
