#include "../include/ball.h"

#include "../include/utils.h"
#include <raylib.h>
#include <raymath.h>

void Ball::update_ball(const float difficulty) {
    static int call_count = 0;
    if (call_count == 0) {
        set_ball_velocity(difficulty);
    }
    call_count++;
    position = Vector2Add(position, velocity);
}

void Ball::scale_velocity(const float scale) { velocity.x *= scale; }

void Ball::draw_ball() const { DrawCircleV(position, radius, Yellow); }

void Ball::set_ball_velocity(const float difficulty) {
    velocity = Vector2{4 * difficulty, 2};
    const int randomX = GetRandomValue(0, 1);
    const int randomY = GetRandomValue(0, 1);
    velocity.x *= static_cast<float>(direction[randomX]);
    velocity.y *= static_cast<float>(direction[randomY]);
}

Ball::Ball() { position = {static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2}; }

void Ball::check_bounds() {
    if (position.y <= 0 || position.y >= static_cast<float>(GetScreenHeight())) {
        velocity.y *= -1;
    }
}

int Ball::score() const {
    if (position.x - velocity.x < -2 * radius) {
        // cpu scored → 1
        return 1;
    }
    if (position.x - velocity.x > static_cast<float>(GetScreenWidth()) + radius * 2) {
        // player scored → -1
        return -1;
    }
    return 0;
}

void Ball::limit() {
    if (position.y + velocity.y <= -radius) {
        position.y = radius;
    }
    if (position.y + velocity.y >= static_cast<float>(GetScreenHeight()) + radius) {
        position.y = static_cast<float>(GetScreenHeight()) - radius;
    }
    if (velocity.x >= 30 + difficulty) {
        velocity.x = 30 + difficulty;
    }
    if (velocity.x <= -30 - difficulty) {
        velocity.x = -30 - difficulty;
    }
    if (velocity.y > 10) {
        velocity.y = 10;
    }
}
