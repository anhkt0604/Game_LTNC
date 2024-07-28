//
// Created by ADMIN on 7/28/2024.
//

#include "header/timer.h"
#include "header/utils.h"

timer::timer() {
    startTick = 0;
    pausedTick = 0;
    paused = false;
    started = false;
}

timer::~timer() {

}

void timer::start() {
    started = true;
    paused = false;
    startTick = SDL_GetTicks();
}

void timer::stop() {
    paused = false;
    started = false;
}

void timer::pause() {
    if (started && !paused) {
        paused = true;
        pausedTick = SDL_GetTicks() - startTick;
    }
}

void timer::unpause() {
    if (paused) {
        paused = false;
        startTick = SDL_GetTicks() - pausedTick;
        pausedTick = 0;
    }
}

int timer::get_ticks() {
    if (started) {
        if (paused) {
            return pausedTick;
        } else {
            return SDL_GetTicks() - startTick;
        }
    }
}

bool timer::is_started() {
    return started;
}

bool timer::is_paused() {
    return paused;
}
