#pragma once

#include "ball.h"
#include "paddle.h"

class Game {
public:
    bool showing_menu = true, match_ended = false, pause_after_goal = false;
    float difficulty = 2;
    float scale = 1.0f;
    int count = 0;

    Paddle player;
    PaddleAi ai;
    Ball ball;

    void startGame();

    void show_end_menu();

    void run();

    void draw_objects() const;

    void update_objects();

    void reset_after_goal();

    void update_after_score();

    void checkCollision();

    void draw() const;

    void newBallDirection();

    void draw_menu();

    static void createBall();

    void show_end_menu() const;
};