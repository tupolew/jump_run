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

double Evelator::get_x_pos() {
	return size_x;
}

double Evelator::get_y_pos() {
	return size_y;
}

double Evelator::get_x_size() {
	return size_x;
}

double Evelator::get_x_size() {
	return size_y;
}

char Evelator::get_priority() {
	return priority;
}

void Evelator::set_priority(char _priority) {
	priority = _priority;
}

void Evelator::collision_right() {

}

void Evelator::player_y_collision(double y1, double y2) {
	if (y1 > y2) {
		std::list<Player *>::iterator iterator;
		for (iterator = players.begin(); iterator != players.end(); iterator++) {
			if ( ( ( (*iterator)->get_x_pos() <= pos_x && (*iterator)->get_x_pos()+(*iterator)->get_x_size() >= pos_x )
					|| ( (*iterator)->get_x_pos() >= pos_x && (*iterator)->get_x_pos()+(*iterator)->get_x_size() <= pos_x+size_x )
					|| ( (*iterator)->get_x_pos() <= pos_x+size_x &&  (*iterator)->get_x_pos()+(*iterator)->get_x_size() >= pos_x+size_x ) )
				&& ( (*iterator)->get_y_pos()+(*iterator)->get_y_size() <= y1  && (*iterator)->get_y_pos()+(*iterator)->get_y_size() >= y2) ) {
				(*iterator)->force_push((*iterator)->get_x_pos(), y2-(*iterator)->get_y_size());
			}
		}
	} else if (y1 < y2) {
		std::list<Player *>::iterator iterator;
		for (iterator = players.begin(); iterator != players.end(); iterator++) {
			if ( ( ( (*iterator)->get_x_pos() <= pos_x && (*iterator)->get_x_pos()+(*iterator)->get_x_size() >= pos_x )
					|| ( (*iterator)->get_x_pos() >= pos_x && (*iterator)->get_x_pos()+(*iterator)->get_x_size() <= pos_x+size_x )
					|| ( (*iterator)->get_x_pos() <= pos_x+size_x &&  (*iterator)->get_x_pos()+(*iterator)->get_x_size() >= pos_x+size_x ) )
				&& ( (*iterator)->get_y_pos() >= y1+size_y && (*iterator)->get_y_pos() <= y2+size_y)  ) {
				(*iterator)->force_push((*iterator)->get_x_pos(), y2+size_y);
			}
		}
	}
}

void Evelator::calculate(double time) {
	if (vel_x != 0) {
		double _pos_x = pos_x + time*vel_x;
		double __pos_x = pos_x;
		pos_x = tile_engine->get_x_collision_move(pos_x, _pos_x, pos_y, size_x, size_y);
		if (pos_x > __pos_x) {
			std::list<Player *>::iterator iterator;
			for(iterator = players.begin(); iterator != players.end(); iterator++) {
				/*if ((*iterator)->get_x_pos() >= __pos_x+size_x && (*iterator)->get_x_pos() < pos_x+size_x)
					(*iterator)->force_push(pos_x+size_x, (*iterator)->get_y_pos());*/
			}
		} else if (pos_x < _pos_x) {
			std::list<Player *>::iterator iterator;
			for(iterator = players.begin(); iterator != players.end(); iterator++) {
				if ((*iterator)->get_x_pos()+(*iterator)->get_x_size() <= __pos_x && (*iterator)->get_x_pos()+(*iterator)->get_x_size() > pos_x)
					(*iterator)->force_push(pos_x-(*iterator)->get_x_size(), (*iterator)->get_y_pos());
			}
		}
		if (_pos_x != pos_x)
			vel_x = (-1)*vel_x;
	}
	if (vel_y != 0) {
		double _pos_y = pos_y;
		pos_y = tile_engine->get_y_collision_move(pos_y, pos_y+time*vel_y, pos_x, size_x, size_y);
		player_y_collision(_pos_y, pos_y);
		if (_pos_y+time*vel_y != pos_y)
			vel_y = (-1)*vel_y;
	}
}

void Evelator::remove_player(Player *player) {
	players.remove(player);
}

void Evelator::add_player_collision(Player *player) {
	players.push_back(player);
}

void Evelator::add_player_top_food_chain(Player *player) {
	players.push_back(player);
}

void Evelator::add_player_bottom_food_chain(Player *player) {
	players.push_back(player);
}
