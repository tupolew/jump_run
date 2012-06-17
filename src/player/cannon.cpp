/*
 * Cannon.cpp
 *
 *  Created on: 16.06.2012
 *      Author: tupolew
 */

#include "player/cannon.hpp"
#include "player/cannon_ball.hpp"

#include <cmath>

#include <SDL/SDL_image.h>

#include <iostream>


Cannon::Cannon(position _pos, position _size, SDL_Surface *_surface, Tile_Engine *_tile_engine, Player_Engine *_player_engine) {
	surface = _surface;
	pos = _pos;
	size = _size;
	player_engine = _player_engine;
	tile_engine = _tile_engine;
	priority = 127;
	cannon_ball_surface = IMG_Load("./textures/cannon_ball.png");
}

Cannon::~Cannon() {
	// TODO Auto-generated destructor stub
}

char Cannon::get_priority() {
	return priority;
}
void Cannon::set_priority(char _priority) {
	priority = _priority;
}
position Cannon::get_position() {
	return pos;
}
position Cannon::Cannon::get_size() {
	return size;
}

void Cannon::set_size(position _size) {
	size = _size;
}

void Cannon::event(int _event, position pos, Player *_enemy, bool _state) {
}

bool Cannon::can_collide_player(char _priority) {
	return Player::COLLIDE;
}
void Cannon::add_collision_player(Player *player) {
}
void Cannon::rem_collision_player(Player *player) {
}

void Cannon::force_push(position _pos) {
}
void Cannon::kill() {
}
position Cannon::calculate(double _time) {
	time+=_time;
	if (time > 25) {
		Cannon_Ball *cannon_ball = new Cannon_Ball(position {pos.x+size.x, pos.y}, position {8, 8}, position{30, 2}, tile_engine, player_engine);
		cannon_ball->setTexture(cannon_ball_surface);
		player_engine->add_player(cannon_ball);
		time = fmod(time, 25);
	}
	return pos;
}
SDL_Surface * Cannon::getTexture() {
	return surface;
}
void Cannon::setTexture(SDL_Surface *_surface) {
	surface = _surface;
}
