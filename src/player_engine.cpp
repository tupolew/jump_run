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
// either expressed or implied, of the FreeBSD Project.#include "graphic_engine.hpp"
//

#include "player_engine.hpp"

Player_Engine::Player_Engine(Tile_Engine * _tile_engine) {
	tile_engine = _tile_engine;
}

void Player_Engine::add_player(Player *_player) {
	players.push_back(_player);
}

void Player_Engine::rem_player(Player *_player) {
	players.remove(_player);
}

void Player_Engine::run(double time) {
	std::list<Player *>::iterator iterator = players.begin();
	for (; iterator != players.end(); iterator++) {
		position size = (*iterator)->get_size();
		position old_pos = (*iterator)->get_position();
		position new_pos = (*iterator)->calculate(time);
		if (old_pos.y > new_pos.y) {
			std::list<Player *>::iterator enemy;
			for (enemy = players.begin(); enemy != players.end(); enemy++) {
				if (*enemy == *iterator)
					continue;
				position enemy_pos = (*enemy)->get_position();
				position enemy_size = (*enemy)->get_size();
				if ( ( ( enemy_pos.x <= old_pos.x && enemy_pos.x+enemy_size.x >= old_pos.x )
						|| ( enemy_pos.x >= old_pos.x && enemy_pos.x+enemy_size.x <= old_pos.x+size.x )
						|| ( enemy_pos.x <= old_pos.x+size.x &&  enemy_pos.x+(*iterator)->get_x_size() >= old_pos.x+size.x ) )
					&& ( enemy_pos.y+enemy_size.y <= old_pos.y  && enemy_pos.y+enemy_size.y >= new_pos.y) ) {
					if ((*enemy)->get_priority() > (*iterator)->get_priority()) {
						(*enemy)->event(Player::BOTTOM, new_pos, *iterator, Player::PASSIVE);
					} else if ((*enemy)->get_priority() < (*iterator)->get_priority()) {
						(*enemy)->event(Player::TOP, new_pos, *enemy, Player::ACTIVE);
					} else {

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
					//TODO
				}
			}
		}
	}
}
