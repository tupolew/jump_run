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

#include "control.hpp"

#include <SDL/SDL.h>

Control::Control() {
	/*if (SDL_Init(SDL_INIT_TIMER) == -1) {
		std::cerr << "Error while SDL_Init: " << SDL_GetError();
		exit(EXIT_FAILURE);
	}*/
	keys[0] = false;
	keys[1] = false;
	keys[2] = false;
	keys[3] = false;
}


void Control::key_event(SDL_Event *event) {
	if (SDL_PollEvent( event )) {
		switch(event->type) {
			case SDL_KEYDOWN:
				switch(event->key.keysym.sym){
					case SDLK_LEFT:
						keys[left]=true;
						break;
					case SDLK_RIGHT:
						keys[right]=true;
						break;
					case SDLK_SPACE:
						keys[up]=true;
						break;
					case SDLK_DOWN:
						keys[down]=true;
						break;
					default:
						break;
					}
				break;
			case SDL_KEYUP:
				switch(event->key.keysym.sym){
					case SDLK_LEFT:
						keys[left]=false;
						break;
					case SDLK_RIGHT:
						keys[right]=false;
						break;
					case SDLK_SPACE:
						keys[up]=false;
						break;
					case SDLK_DOWN:
						keys[down]=false;
						break;
					default:
						exit(0);
					}
			break;
		}
	}
}
