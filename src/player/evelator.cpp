/*
 * evelator.cpp
 *
 *  Created on: 02.06.2012
 *      Author: tupolew
 */

#include "player/evelator.hpp"

Evelator::Evelator(double _pos_x, double _pos_y, double _size_x, double _size_y, double _vel_x, double _vel_y, Tile_Engine *_tile_engine) {
	pos_x = _pos_x;
	pos_y = _pos_y;
	size_x = _size_x;
	size_y = _size_y;
	vel_x = _vel_x;
	vel_y = _vel_y;
	tile_engine = _tile_engine;
}

void Evelator::calculate(double time) {
	double _pos_x = pos_x + time*vel_x;
	pos_x = tile_engine->get_x_collision_move(pos_x, _pos_x, pos_y, size_x, size_y);
	if (_pos_x != pos_x)
		vel_x = (-1)*vel_x;
	double _pos_y = pos_y + time*vel_y;
	pos_y = tile_engine->get_y_collision_move(pos_y, _pos_y, pos_x, size_x, size_y);
	if (_pos_y != pos_y)
		vel_y = (-1)*vel_y;
}


