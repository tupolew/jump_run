/*
 * cannon_ball.h
 *
 *  Created on: 16.06.2012
 *      Author: tupolew
 */

#ifndef CANNON_BALL_H_
#define CANNON_BALL_H_

#include "player/player.hpp"
#include "tile_engine.hpp"
#include "player_engine.hpp"

#include <list>

class Cannon_Ball: public Player {
public:
	Cannon_Ball(position pos, position size, position vel, Tile_Engine *tile_engine, Player_Engine *player_engine);
	~Cannon_Ball();
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
	SDL_Surface *surface;
	std::list<Player *> players;
	position size;
	position pos;
	position vel;
	char priority;
};

#endif /* CANNON_BALL_H_ */
