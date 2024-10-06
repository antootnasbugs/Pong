#pragma once
#include <raylib.h>

class Ball {
public:
    float radius = 10;
    int direction[2] = {-1, 1};
    float difficulty = 4.0f;
    Vector2 position{};
    Vector2 velocity = {4 * difficulty, 2};

    explicit Ball();

    void update_ball(float difficulty);

    void scale_velocity(float scale);

    void draw_ball() const;

    void set_ball_velocity(float difficulty);

    void check_bounds();

    int score() const;

    void limit();
};