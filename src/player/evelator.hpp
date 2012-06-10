/*
 * evelator.hpp
 *
 *  Created on: 02.06.2012
 *      Author: tupolew
 */

#include "player/player.hpp"
#include "tile_engine.hpp"

#ifndef EVELATOR_HPP_
#define EVELATOR_HPP_

class Evelator : public Player {
public:
	Evelator(double _pos_x, double _pos_y, double _size_x, double _size_y, double _vel_x, double _vel_y, Tile_Engine *_tile_engine);
	~Evelator() {}
	char get_priority();
	void set_priority(char _priority);
	void kill();
	double get_x_size();
	double get_y_size();
	double get_x_pos();
	double get_y_pos();
	void collision_right();
	void collision_left();
	void collision_top();
	void collision_down();
	void calculate(double time);
	void setTexture(SDL_Surface *surface) {texture = surface;}
	void force_push(double _pos_x, double _pos_y) {}
	void remove_player(Player *player);
	void add_player_top_food_chain(Player *player);
	void add_player_bottom_food_chain(Player *player);
	void add_player_collision(Player *player);
	SDL_Surface *getTexture() {return texture;}
private:
	void player_x_collision(double x1, double x2);
	void player_y_collision(double y1, double y2);
	SDL_Surface *texture;
	std::list<Player *> players;
	Tile_Engine *tile_engine;
	double pos_x;
	double pos_y;
	double vel_y;
	double vel_x;
	double size_x;
	double size_y;
	char priority;
};


#endif /* EVELATOR_HPP_ */
