/*
 * Copyright (c) 2012, Samuel Memmel
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of the FreeBSD Project.#include "graphic_engine.hpp"
 */

#include "player.hpp"

Player::Player(double pos_x, double pos_y, double gravity, Tile_Engine *tile_engine, Control *control) {
	_pos_x = pos_x;
	_pos_y = pos_y;
	_gravity = gravity;
	_tile_engine = tile_engine;
	_control = control;
}

void Player::calculate(double time) {
	if (_x_vel == 0) {
		if (_control->is_pressed(Control::right)) {
			_x_vel = 9.0;
		} else if (_control->is_pressed(Control::left)) {
			_x_vel = -9.0;
		}
	}
	if (_tile_engine->get_collision(_pos_x, _pos_y+32.0) == Tile_Engine::COLLIDES || _tile_engine->get_collision(_pos_x+31.9999999999999, _pos_y+32.0) == Tile_Engine::COLLIDES) {
			if (_control->is_pressed(Control::up) == true) {
				_y_vel = -40.0;
			} else if (_control->is_pressed(Control::right) == true && _x_vel != 0) {
				_x_vel = (1.2*time+_x_vel > 30.0)?30.0:1.2*time+_x_vel;
			} else if (_control->is_pressed(Control::left) == 1 && _x_vel != 0) {
				_x_vel = (-1.2*time+_x_vel < -30.0)?-30.0:-1.2*time+_x_vel;
			} else {
				_x_vel = 0;
			}
	} else {
		_y_vel = _y_vel+7*time;
	}
	double _pos_y_2 = _pos_y+time*_y_vel;
	_pos_y = _tile_engine->get_y_collision(_pos_y, _pos_y_2,_pos_x,31.9999999999999,31.9999999999999);
	if (_pos_y_2 != _pos_y) {
		_y_vel = 0;
	}
}



