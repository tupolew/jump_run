/*
 * Cannon_Ball_ball.cpp
 *
 *  Created on: 16.06.2012
 *      Author: tupolew
 */

#include "cannon_ball.hpp"

Cannon_Ball::Cannon_Ball(position _pos, position _size, position _vel, Tile_Engine *_tile_engine, Player_Engine *_player_engine) {
	pos = _pos;
	size = _size;
	vel = _vel;
	priority = 126;
	tile_engine = _tile_engine;
	player_engine = _player_engine;
}

Cannon_Ball::~Cannon_Ball() {
	// TODO Auto-generated destructor stub
}

char Cannon_Ball::get_priority() {
	return priority;
}
void Cannon_Ball::set_priority(char _priority) {
	priority = _priority;
}
position Cannon_Ball::get_position() {
	return pos;
}
position Cannon_Ball::Cannon_Ball::get_size() {
	return size;
}

void Cannon_Ball::set_size(position _size) {
	size = _size;
}

void Cannon_Ball::event(int event, position pos, Player *enemy, bool state) {
	player_engine->rem_player(this);
	enemy->kill();
}

bool Cannon_Ball::can_collide_player(char _priority) {
	return N_COLLIDE;
}
void Cannon_Ball::add_collision_player(Player *_player) {
	players.push_back(_player);
}
void Cannon_Ball::rem_collision_player(Player *_player) {
	players.remove(_player);
}

void Cannon_Ball::force_push(position _pos) {
}
void Cannon_Ball::kill() {
}
position Cannon_Ball::calculate(double time) {
	position new_pos = pos;
	if (vel.x != 0) {
		double new_x = pos.x + time*vel.x;
		new_pos.x = tile_engine->get_x_collision_move(pos.x, new_x, pos.y, size.x, size.y);
		if (new_pos.x != new_x) {
			player_engine->rem_player(this);
		}
		pos.x = new_pos.x;
	}
	if (vel.y != 0) {
		double new_y = pos.y + time*vel.y;
		new_pos.y = tile_engine->get_y_collision_move(pos.y, new_y, pos.x, size.x, size.y);
		if (new_pos.y != new_y) {
			player_engine->rem_player(this);
		}
		pos.y = new_pos.y;
	}
	return new_pos;
}
SDL_Surface * Cannon_Ball::getTexture() {
	return surface;
}
void Cannon_Ball::setTexture(SDL_Surface *_surface) {
	surface = _surface;
}
