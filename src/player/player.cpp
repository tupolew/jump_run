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

#include "player.hpp"

#include <cmath>

Player::Player(double pos_x, double pos_y, double size_x, double size_y, double gravity, Tile_Engine *tile_engine, Control *control) {
	_pos_x = pos_x;
	_pos_y = pos_y;
	_gravity = gravity;
	_tile_engine = tile_engine;
	_control = control;
	_size_x = size_x;
	_size_y = size_y;
}

void Player::calculate(double time) {
	if (_vel_x == 0) {
		if (_control->is_pressed(Control::right)) {
			_vel_x = 9.0;
		} else if (_control->is_pressed(Control::left)) {
			_vel_x = -9.0;
		}
	}
	if (_tile_engine->does_bottom_collide(_pos_x, _pos_y, _size_x, _size_y) == Tile_Engine::COLLIDES) {
			if (_control->is_pressed(Control::up) == true) {
				_vel_y = -40.0;
			} else if (_control->is_pressed(Control::right) == true && _vel_x != 0) {
				_vel_x = (1.2*time+_vel_x > 30.0)?30.0:1.2*time+_vel_x;
			} else if (_control->is_pressed(Control::left) == 1 && _vel_x != 0) {
				_vel_x = (-1.2*time+_vel_x < -30.0)?-30.0:-1.2*time+_vel_x;
			} else {
				_vel_x = 0;
			}
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



