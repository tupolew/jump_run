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

#include "tile_engine.hpp"
#include <list>
#include <SDL/SDL.h>


#ifndef PLAYER_HPP_
#define PLAYER_HPP_

struct Pos {
	double x;
	double y;
};

typedef struct Pos position;

class Player {
public:
	enum {
		TOP = 0,
		BOTTOM = 1,
		LEFT = 2,
		RIGHT = 3
	};
	enum {
		ACTIVE = 0,
		PASSIVE = 1
	};
public:
	virtual ~Player() {}
	virtual char get_priority();
	virtual void set_priority(char priority);
	virtual position get_position() = 0;
	virtual position get_size() = 0;

	virtual void event(int event, position pos, Player *enemy, bool state) = 0;

	virtual double get_x_size() = 0;
	virtual double get_y_size() = 0;
	virtual double get_x_pos() = 0;
	virtual double get_y_pos() = 0;
	virtual void force_push(double _pos_x, double _pos_y) = 0;
	virtual void kill();
	position calculate(double time) = 0;
	virtual SDL_Surface *getTexture() = 0;
	virtual void setTexture(SDL_Surface *surface) = 0;
};


#endif /* PLAYER_HPP_ */
