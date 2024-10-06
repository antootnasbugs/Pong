#include "../include/paddle.h"
#include <iostream>
#include <raylib.h>

void Paddle::draw_paddle() const { DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8f, 20, color); }

void Paddle::update_paddle() {
  if (IsKeyDown(KEY_LEFT_SHIFT)) {
    speed = 18.0f;
  } else if (!IsKeyDown(KEY_LEFT_SHIFT)) {
    speed = 10.0f;
  }
  if (IsKeyDown(KEY_UP)) {
    y -= speed;
  }
  if (IsKeyDown(KEY_DOWN)) {
    y += speed;
  }

  limit();
}

void Paddle::limit() {
  if (y > static_cast<float>(GetScreenHeight()) - height) {
    y = static_cast<float>(GetScreenHeight()) - height;
  }
  if (y < 0.0f) {
    y = 0.0f;
  }
}

void PaddleAi::move(const float ball_y, float diff) {
  const float distance = ball_y - (y + height / 2);

  float scaleFactor = 250.0f * diff;

  if (const float aiSpeed = scaleFactor * GetFrameTime(); fabs(distance) > aiSpeed) {
    if (distance > 0) {
      y += aiSpeed;
    } else {
      y -= aiSpeed;
    }
  } else {
    y += distance;
  }

  limit();
}
