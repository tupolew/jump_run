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
	double get_x_size() {return size_x;}
	double get_y_size() {return size_y;}
	double get_x_pos() {return pos_x;}
	double get_y_pos() {return pos_y;}
	std::list<Player*> get_enemys() {return enemies;};
	void set_enemys(std::list<Player *> enemies) {this->enemies = enemies;}
	void remove_enemy(Player *enemy) {enemies.remove(enemy);}
	void calculate(double time);
	void setTexture(SDL_Surface *surface) {texture = surface;}
	SDL_Surface *getTexture() {return texture;}
private:
	SDL_Surface *texture;
	std::list<Player *> enemies;
	Tile_Engine *tile_engine;
	double pos_x;
	double pos_y;
	double vel_y;
	double vel_x;
	double size_x;
	double size_y;
};


#endif /* EVELATOR_HPP_ */
