#include "../include/game.h"

#include <cmath>
#include <raymath.h>
#include "../include/utils.h"

constexpr float height = 80.0f;
constexpr float width = 250.0f;
constexpr Rectangle easy = {25, screen_height / 2 - height / 2, width, height};
constexpr Rectangle medium = {325, screen_height / 2 - height / 2, width, height};
constexpr Rectangle hard = {625, screen_height / 2 - height / 2, width, height};
constexpr Rectangle extreme = {925, screen_height / 2 - height / 2, width, height};
Timer timer;

void DrawLeftSemiCircle() {
    DrawRing(Vector2{static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2}, 0, 145.7, 90,
             270, 100, Blue);
}

void DrawRightSemiCircle() {
    DrawRing(Vector2{static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2}, 0, 145.7,
             270,
             450, 100, Dark_Blue);
}

Vector2 CalculateBallDirection(const Rectangle paddle, const Vector2 ballPosition, const Vector2 ballVelocity) {
    const float relativeIntersectY = ballPosition.y - (paddle.y + paddle.height / 2);
    const float normalizedRelativeIntersectionY = relativeIntersectY / (paddle.height / 2);

    Vector2 newDirection = {-ballVelocity.x, ballVelocity.y};
    float bounceAngle = normalizedRelativeIntersectionY * 3.0f;
    bounceAngle = Clamp(bounceAngle, -1.0f, 1.0f);
    newDirection.y += bounceAngle * fabs(ballVelocity.x);

    return newDirection;
}

void Game::checkCollision() {
    player.paddle.y = player.y;
    player.paddle.x = player.x;
    ai.paddle.x = ai.x;
    ai.paddle.y = ai.y;
    if (CheckCollisionCircleRec(ball.position, ball.radius, player.paddle)) {
        PlaySound(soundCollision);
        ball.velocity = CalculateBallDirection(player.paddle, ball.position, ball.velocity);
        ball.scale_velocity(1.05f);
    }
    if (CheckCollisionCircleRec(ball.position, ball.radius, ai.paddle)) {
        PlaySound(soundCollision);
        ball.velocity = CalculateBallDirection(ai.paddle, ball.position, ball.velocity);
        ball.scale_velocity(1.05f);
    }
}

void Game::run() {
    count++;
    if (ball.position.x < 720 && ball.position.x > 80 && count % 180 == 0) {
        // update speed only if the ball is not close to paddle.
        scale += 0.01;
        ball.scale_velocity(scale);
    }
    update_after_score();
    update_objects();
    draw_objects();
    checkCollision();
    ball.check_bounds();
    ball.limit();
    if (player.score == 21 || ai.score == 21) {
        match_ended = true;
        show_end_menu();
    }

    if (IsKeyPressed(KEY_Q)) {
        ai.score = 21;
    }
}

void Game::draw_objects() const {
    player.draw_paddle();
    ai.draw_paddle();
    ball.draw_ball();
}

void Game::update_objects() {
    if (pause_after_goal) {
        UpdateTimer(&timer);
        if (TimerDone(&timer)) {
            pause_after_goal = false;
            ball.set_ball_velocity(difficulty);
        } else {
            ball.position = {static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2};
            player.y = static_cast<float>(GetScreenHeight()) / 2 - height / 2;
            ai.y = static_cast<float>(GetScreenHeight()) / 2 - height / 2;
        }
    } else {
        ai.move(ball.position.y, difficulty);
        player.update_paddle();
        ball.update_ball(difficulty);
    }
}

void Game::reset_after_goal() {
    if (pause_after_goal) {
        UpdateTimer(&timer);
        if (TimerDone(&timer)) {
            pause_after_goal = false;
            ball.set_ball_velocity(difficulty);
        }
    }
    ball.set_ball_velocity(difficulty);
}

void Game::update_after_score() {
    if (const int var = ball.score(); var != 0) {
        StartTimer(&timer, 0.6);
        pause_after_goal = true;
        var == 1 ? ai.score++ : player.score++;
    }
}

void Game::draw() const {
    DrawRectangle(0, 0, screen_width / 2, screen_height, Dark_Blue);
    DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, Blue);
    DrawLeftSemiCircle();
    DrawRightSemiCircle();
    DrawRing(Vector2{static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2}, 146, 150, 0,
             360, 100, WHITE);
    DrawLineEx(Vector2{static_cast<float>(GetScreenWidth()) / 2, 0},
               Vector2{static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight())}, 4, WHITE);
    DrawTextEx(font, TextFormat("Player:%2i", player.score), Vector2{800.0f / 4 - 20, 20}, 35, 2, WHITE);
    DrawTextEx(font, TextFormat("CPU:%2i", ai.score), Vector2{3.0f * 600 / 4 - 20, 20}, 35, 2, WHITE);
}

void Game::newBallDirection() {
    // NOLINT(*-convert-member-functions-to-static)
    const float relativeIntersectY = (ball.position.y - (player.paddle.y + player.paddle.height / 2));
    const float normalizedRelativeIntersectionY = relativeIntersectY / (player.paddle.height / 2);

    const float bounceAngle = normalizedRelativeIntersectionY * maxBounceAngle;

    Vector2 newDirection = {ball.velocity.x * cosf(bounceAngle), ball.velocity.x * -sinf(bounceAngle)};

    if (ball.velocity.x < 0)
        newDirection.x = -newDirection.x;

    ball.velocity = newDirection;
}

void Game::draw_menu() {
    DrawRectangleRounded(easy, 0.75, 50, GREEN);
    DrawRectangleRounded(medium, 0.75, 50, ORANGE);
    DrawRectangleRounded(hard, 0.75, 50, RED);
    DrawRectangleRounded(extreme, 0.75, 50, BLACK);

    auto [easy_x, easy_y] = MeasureTextEx(font, "Easy", 20, 2);
    auto [medium_x, medium_y] = MeasureTextEx(font, "Medium", 20, 2);
    auto [hard_x, hard_y] = MeasureTextEx(font, "Hard", 20, 2);
    auto [extreme_x, extreme_y] = MeasureTextEx(font, "Extreme", 20, 2);

    DrawTextEx(font, "Easy", Vector2{25 + width / 2 - easy_x, screen_height / 2 - 20}, 28, 2, WHITE);
    DrawTextEx(font, "Medium", Vector2{325 + width / 2 - 0.8f * medium_x, screen_height / 2 - 20}, 28, 2, WHITE);
    DrawTextEx(font, "Hard", Vector2{625 + width / 2 - 0.8f * hard_x, screen_height / 2 - 20}, 28, 2, WHITE);
    DrawTextEx(font, "Extreme", Vector2{925 + width / 2 - 0.8f * extreme_x, screen_height / 2 - 20}, 28, 2, WHITE);

    const Vector2 mouse_pos = GetMousePosition();

    if (CheckCollisionPointRec(mouse_pos, easy)) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            difficulty = 2.0f;
            showing_menu = false;
            if (match_ended) {
                match_ended = false;
                ai.score = 0;
                player.score = 0;
                reset_after_goal();
            }
        }
    }
    if (CheckCollisionPointRec(mouse_pos, medium)) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            difficulty = 3.0f;
            showing_menu = false;
            if (match_ended) {
                match_ended = false;
                ai.score = 0;
                player.score = 0;
                reset_after_goal();
            }
        }
    }
    if (CheckCollisionPointRec(mouse_pos, hard)) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            difficulty = 4.0f;
            showing_menu = false;
            if (match_ended) {
                match_ended = false;
                ai.score = 0;
                player.score = 0;
                reset_after_goal();
            }
        }
    }
    if (CheckCollisionPointRec(mouse_pos, extreme)) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            difficulty = 5.0f;
            showing_menu = false;
            if (match_ended) {
                match_ended = false;
                ai.score = 0;
                player.score = 0;
                reset_after_goal();
            }
        }
    }
}

void Game::startGame() { ball.difficulty = difficulty; }

void Game::show_end_menu() {
    constexpr float posX = 500, posY = 200;
    constexpr float posX_2 = 264, posY_2 = 270;
    DrawTextEx(font, "Game ended", Vector2{posX, posY}, 40, 2, BLACK);
    DrawTextEx(font, TextFormat("Player %i won! Do you want to play again?", player.score == 21 ? 1 : 2),
               Vector2{posX_2, posY_2}, 40, 2, BLACK);
    draw_menu();
}
