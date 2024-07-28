//
// Created by ADMIN on 7/28/2024.
//

#ifndef GAME_LTNC_TIMER_H
#define GAME_LTNC_TIMER_H


class timer {
public:
    timer();
    ~timer();

    void start();
    void stop();
    void pause();
    void unpause();

    int get_ticks();

    bool is_started();
    bool is_paused();
private:
    int startTick;
    int pausedTick;

    bool paused;
    bool started;
};


#endif //GAME_LTNC_TIMER_H
