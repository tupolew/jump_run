/*
 * Copyright (c) 2012, Samuel Memmel
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of the FreeBSD Project.#include "graphic_engine.hpp"
 */
#include "tile_engine.hpp"

#include <iostream>
#include <cstdio>
#include <cstdlib>

Tile_Engine::Tile_Engine(const char *file) {
	auto func = [](Tile_Engine *tile_engine, char *row, int y_pos) {
		union {
			unsigned long ptr;
			struct {
				unsigned char type;
				unsigned char event;
				unsigned char options;
				unsigned char surface;
			} tile_struct;
		} union_tile;
		for (int i = 0; i < tile_engine->x_size; i++) {
			int k;
			for (k = 0; row[k] != ' ' && row[k] != '\n' && row[k] != '\0'; k++);
			row[k]='\0';
			union_tile.ptr = (unsigned long)atol(row);
			tile_engine->tiles[y_pos][i].setAll(union_tile.tile_struct.type, union_tile.tile_struct.event, union_tile.tile_struct.options, union_tile.tile_struct.surface);
			switch (tile_engine->tiles[y_pos][i].getEvent()) {
			case 4:
				/*tw->player.pos_x=32*i;
				tw->player.pos_y=32*y_pos;
				tw->tiles[y_pos][i].event = 0;*/
				break;
			case 3:
				/*tw->enemys[enemys_count].pos_x = 32*i;
				tw->enemys[enemys_count].pos_y = 32*y_pos;
				tw->enemys[enemys_count].dir = LEFT_1;
				tw->tiles[y_pos][i].event = 0;
				enemys_count=enemys_count+1;*/
				break;
			}
			row+=(k+1);
		}
	};
	FILE *level_file = fopen(file, "r");
	if (level_file == NULL) {
		std::cerr << "Error while fopen(" << file << ")\n";
		exit(1);
	}
	fscanf(level_file, "%ix%i\n", &x_size, &y_size);
	tiles = new Tile*[y_size];
	for (int i = 0; i < y_size; i++) {
		tiles[i] = new Tile;
	}
	char *buf=(char *)malloc(sizeof(char)*11*x_size);
	for (int i = 0; i < y_size; i++) {
		fgets(buf, x_size*11, level_file);
		func(this, buf, i);
	}
}

Tile_Engine::~Tile_Engine() {
	// TODO Auto-generated destructor stub
}

Tile *Tile_Engine::getTile(int x, int y) {
	return (y < y_size && x < x_size)?tiles[y][x]:NULL;
}
