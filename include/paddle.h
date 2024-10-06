#pragma once
#include "utils.h"

class Paddle {
public:
    const float OFFSET = 30.0f;
    float width = 20.0f, height = 100.0f, y = static_cast<float>(GetScreenHeight()) / 2 - height / 2, x = OFFSET,
            speed = 10.0f;
    int score = 0;
    Color color = Color{86, 145, 255, 255};
    Rectangle paddle = {x, y, width, height};

    /*
    explicit Paddle() :
        width(20.0f), height(100.0f), y(static_cast<float>(GetScreenHeight()) / 2 - height / 2), x(OFFSET), speed(10.0f),
        score(0), color(Color{86, 145, 255, 255}), paddle{x, y, width, height} {}
        */

    void draw_paddle() const;

    void update_paddle();

    void limit();
};

class PaddleAi : public Paddle {
public:
    PaddleAi() {
        color = Dark_Blue;
        x = static_cast<float>(GetScreenWidth()) - OFFSET - width;
    }

    void move(float ball_y, float diff);
};
