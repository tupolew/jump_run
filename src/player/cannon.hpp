/*
 * cannon.hpp
 *
 *  Created on: 16.06.2012
 *      Author: tupolew
 */

#ifndef CANNON_HPP_
#define CANNON_HPP_

#include "player/player.hpp"
#include "player_engine.hpp"
#include "tile_engine.hpp"

#include "SDL/SDL.h"

class Cannon: public Player {
public:
	Cannon(position _pos, position _size, SDL_Surface *_surface, Tile_Engine *_tile_engine, Player_Engine *player_engine);
	~Cannon();
	char get_priority();
	void set_priority(char priority);
	position get_position();
	position get_size();

	void set_size(position _size);

	void event(int event, position pos, Player *enemy, bool state);

	bool can_collide_player(char _priority);
	void add_collision_player(Player *player);
	void rem_collision_player(Player *player);

	void force_push(position _pos);
	void kill();
	position calculate(double time);
	SDL_Surface *getTexture();
	void setTexture(SDL_Surface *surface);
private:
	Player_Engine *player_engine;
	Tile_Engine *tile_engine;
	SDL_Surface *cannon_ball_surface;
	SDL_Surface *surface;
	position pos;
	position size;
	char priority;
	double time;
};

#endif /* CANNON_HPP_ */
