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
#ifndef GRAPHIC_ENGINE_H_
#define GRAPHIC_ENGINE_H_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "tile_engine.hpp"
#include "tile.hpp"

class Graphic_Engine {
public:
	Graphic_Engine() = delete;
	Graphic_Engine(Tile_Engine *tile_engine, Uint16 x_res, Uint16 y_res);
	~Graphic_Engine();
	void drawWorld(int x, int y);
private:
	Uint16 x_res;
	Uint16 y_res;
	bool fullscreen;
	SDL_Surface **textures;
	SDL_Surface *screen;
	Tile_Engine *tile_engine;
};

#endif /* GRAPHIC_ENGINE_H_ */