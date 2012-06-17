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
// either expressed or implied, of the FreeBSD Project.
//

#include "player_engine.hpp"
#include "player/evelator.hpp"
#include "player/clubmate.hpp"
#include "player/cannon.hpp"

#include "SDL/SDL_image.h"


std::list<Player *> Player_Engine::get_players() {
	return players;
}

Human_Player *Player_Engine::get_human_player() {
	return human_player;
}

Player_Engine::Player_Engine(Tile_Engine * _tile_engine) {
	tile_engine = _tile_engine;
	human_player = new Human_Player(position {480.0, 32.0}, position {48.0, 48.0}, 10.0, IMG_Load("./textures/tux_1.png"), tile_engine, this);
	players.push_back(human_player);
	players.push_back(new Evelator (position {0.0, 0.0}, position {128.0, 16.0}, position {0.0, 8.0}, IMG_Load("./textures/aufzug_1.png"), tile_engine));
	players.push_back(new ClubMate (position {64.0, 256.0}, position {16.0, 63.0}, IMG_Load("./textures/club_mate.png"), tile_engine));
	players.push_back(new Cannon (position {160.0, 259.0}, position {64, 29}, IMG_Load("./textures/cannon.png"), tile_engine, this));
}

void Player_Engine::add_player(Player *_player) {
	char priority = _player->get_priority();
	std::list<Player *>::iterator iterator = players.begin();
	for (;iterator != players.end(); iterator++) {
		if ((*iterator)->can_collide_player(priority) == Player::COLLIDE)
			_player->add_collision_player(*iterator);
		if (_player->can_collide_player((*iterator)->get_priority()) == Player::COLLIDE)
			(*iterator)->add_collision_player(_player);
	}
	players.push_back(_player);
}

bool Player_Engine::touch_bottom(Player *player, std::list<Player *> players) {
	position pos = player->get_position();
	position size = player->get_size();
	std::list<Player *>::iterator iterator;
	for (iterator = players.begin(); iterator != players.end(); iterator++) {
		position i_pos = (*iterator)->get_position();
		position i_size = (*iterator)->get_size();
		if ( ( ( i_pos.x <= pos.x && i_pos.x+i_size.x >= pos.x )
				|| ( i_pos.x >= pos.x && i_pos.x+i_size.x <= pos.x+size.x )
				|| ( i_pos.x <= pos.x+size.x &&  pos.x+i_size.x >= pos.x+size.x ) )
			&& i_pos.y == pos.y+size.y) {
				return Player::COLLIDE;
		}
	}
	return Player::N_COLLIDE;
}

void Player_Engine::rem_player(Player *_player) {
	//players.remove(_player);
	rem_players.push_back(_player);
}

void Player_Engine::run(double time) {
	std::list<Player *>::iterator iterator = players.begin();
	for (; iterator != players.end(); iterator++) {
		Player *player = (*iterator);
		position size = player->get_size();
		position old_pos = player->get_position();
		position new_pos = player->calculate(time);
		//Spieler bewegt sich nach links
		if (old_pos.x > new_pos.x) {
			std::list<Player *>::iterator enemy;
			for (enemy = players.begin(); enemy != players.end(); enemy++) {
				if (*enemy == *iterator)
					continue;
				position enemy_pos = (*enemy)->get_position();
				position enemy_size = (*enemy)->get_size();
				if ( ( ( enemy_pos.y <= old_pos.y && enemy_pos.y+enemy_size.y >= old_pos.y )
					|| ( enemy_pos.y >= old_pos.y && enemy_pos.y+enemy_size.y <= old_pos.y+size.y )
					|| ( enemy_pos.y <= old_pos.y+size.y &&  enemy_pos.y+enemy_size.y >= old_pos.y+size.y ) )
					&& ( enemy_pos.x+enemy_size.x <= old_pos.x  && enemy_pos.x+enemy_size.x >= new_pos.x) ) {
				if ((*enemy)->get_priority() > player->get_priority()) {
						(*enemy)->event(Player::RIGHT, new_pos, *iterator, Player::PASSIVE);
					} else if ((*enemy)->get_priority() < player->get_priority()) {
						player->event(Player::LEFT, new_pos, *enemy, Player::ACTIVE);
					} else {
						//TODO
					}
				}
			}
		//Spieler bewegt sich nach rechts
		} else if (old_pos.x < new_pos.x) {
			std::list<Player *>::iterator enemy;
			for (enemy = players.begin(); enemy != players.end(); enemy++) {
				if (*enemy == *iterator)
					continue;
				position enemy_pos = (*enemy)->get_position();
				position enemy_size = (*enemy)->get_size();
				if ( ( ( enemy_pos.y <= old_pos.y && enemy_pos.y+enemy_size.y >= old_pos.y )
					|| ( enemy_pos.y >= old_pos.y && enemy_pos.y+enemy_size.y <= old_pos.y+size.y )
					|| ( enemy_pos.y <= old_pos.y+size.y &&  enemy_pos.y+enemy_size.y >= old_pos.y+size.y ) )
					&& ( enemy_pos.x >= old_pos.x+size.x && enemy_pos.x <= new_pos.x+size.x)  ) {
					if ((*enemy)->get_priority() > player->get_priority()) {
						(*enemy)->event(Player::LEFT, new_pos, *iterator, Player::PASSIVE);
					} else if ( player->get_priority() > (*enemy)->get_priority() ) {
						player->event(Player::RIGHT, new_pos, *enemy, Player::ACTIVE);
					} else {
						//TODO
					}
				}
			}
		}
	if (old_pos.y > new_pos.y) {
			std::list<Player *>::iterator enemy;
			for (enemy = players.begin(); enemy != players.end(); enemy++) {
				if (*enemy == *iterator)
					continue;
				position enemy_pos = (*enemy)->get_position();
				position enemy_size = (*enemy)->get_size();
				if ( ( ( enemy_pos.x <= old_pos.x && enemy_pos.x+enemy_size.x >= old_pos.x )
						|| ( enemy_pos.x >= old_pos.x && enemy_pos.x+enemy_size.x <= old_pos.x+size.x )
						|| ( enemy_pos.x <= old_pos.x+size.x &&  enemy_pos.x+enemy_size.x >= old_pos.x+size.x ) )
					&& ( enemy_pos.y+enemy_size.y <= old_pos.y  && enemy_pos.y+enemy_size.y >= new_pos.y) ) {
					if ((*enemy)->get_priority() > player->get_priority()) {
						(*enemy)->event(Player::BOTTOM, new_pos, *iterator, Player::PASSIVE);
					} else if ((*enemy)->get_priority() < player->get_priority()) {
						player->event(Player::TOP, new_pos, *enemy, Player::ACTIVE);
					} else {
						//TODO
					}
				}
			}
		} else if (old_pos.y < new_pos.y) {
			std::list<Player *>::iterator enemy;
			for (enemy = players.begin(); enemy != players.end(); enemy++) {
				if (*enemy == *iterator)
					continue;
				position enemy_pos = (*enemy)->get_position();
				position enemy_size = (*enemy)->get_size();
				if ( ( ( enemy_pos.x <= old_pos.x && enemy_pos.x+enemy_size.x >= old_pos.x )
						|| ( enemy_pos.x >= old_pos.x && enemy_pos.x+enemy_size.x <= old_pos.x+size.x )
						|| ( enemy_pos.x <= old_pos.x+size.x &&  enemy_pos.x+enemy_size.x >= old_pos.x+size.x ) )
				&& ( enemy_pos.y >= old_pos.y+size.y && enemy_pos.y <= new_pos.y+size.y)  ) {
					if ((*enemy)->get_priority() > player->get_priority()) {
						//Von enemy ausgesehen fällt iterator auf die Oberseite
						(*enemy)->event(Player::TOP, new_pos, *iterator, Player::PASSIVE);
					} else if ( player->get_priority() > (*enemy)->get_priority() ) {
						//Von iterator ausgesehen fällt er mit der Unterseite auf enemy
						player->event(Player::BOTTOM, new_pos, *enemy, Player::ACTIVE);
					} else {
						//TODO
					}
				}
			}
		}
	}
	iterator = rem_players.begin();
	for (; iterator != rem_players.end(); iterator++) {
		players.remove(*iterator);
		delete (*iterator);
	}
	rem_players.erase(rem_players.begin(), iterator);
}
