//-----------------------------------------------------------------------------
//
// $Id:$
//
// Copyright (C) 2016 by Gareth Nelson (gareth@garethnelson.com)
//
// This file is part of the Lambda engine.
//
// The Lambda engine is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// The Lambda engine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
//
// $Log:$
//
// DESCRIPTION:
//      Part of the lambda_video module, used to create an OpenGL context
//
//-----------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

SDL_Window *screen;
SDL_GLContext glcontext;

void __attribute__((constructor)) init_module() {
     printf("lambda_video/v_init.c:init_module() - module loaded\n");
}

void video_pre_render() {
     glClearColor ( 1.0, 0.0, 0.0, 1.0 );
     glClear ( GL_COLOR_BUFFER_BIT );
}

void video_post_render() {
     SDL_GL_SwapWindow(screen);
}

int video_init() {
    printf("lambda_video/v_init.c:video_init() - Querying SDL\n");
    if(SDL_WasInit(0)==0) {
       SDL_Init(0);
    }
    SDL_InitSubSystem(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    SDL_GL_SetSwapInterval(1);
    
    printf("lambda_video/v_init.c:video_init() - Creating window\n");
    screen = SDL_CreateWindow("Lambda Engine",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,1024,768,
                                              SDL_WINDOW_OPENGL);

    glcontext = SDL_GL_CreateContext(screen);
    return 0;
}