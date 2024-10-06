#include <raylib.h>
#include "../include/game.h"
#include "../include/utils.h"

// TODO:
//  -[x] add a way to set the difficulty (start menu)
//  -[x] add end menu (wins first at 21)
//  -[x] limit ball speed
//  -[x] check bounds for ball (limit the movement to 0+radius and screen height - radius)
//  -[x] add possibility to "sprint" with paddle

Sound soundCollision;
Sound blip;
Font font;

int main() {
  InitWindow(screen_width, screen_height, "Pong");
  InitAudioDevice();
  soundCollision = LoadSound("/Users/antonino/Desktop/Code/CLionProjects/Pong/resources/coll_sound.wav");
  blip = LoadSound("/Users/antonino/Desktop/Code/CLionProjects/Pong/resources/blip.wav");
  font = LoadFontEx("/Users/antonino/Desktop/Code/CLionProjects/Pong/resources/Aptos-Serif.ttf", 60, nullptr, 250);
  SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);
  SetTargetFPS(75);
  bool paused = false;
  Game game;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(Dark_Blue);
    if (game.showing_menu) {
      DrawTextEx(font, "Select a difficulty", Vector2{425, 250}, 40, 2, BLACK);
      game.draw_menu();
      DrawTextEx(font, "Tip: use left shift to get a boost.", Vector2{40, screen_height / 2 + 300}, 28, 2, LIGHTGRAY);
    }
    if (!game.showing_menu && !game.match_ended) {
      if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_P)) {
        paused = !paused;
      }
      game.draw();

      if (!paused) {
        game.run();
      }
      if (paused) {
        DrawRectangleRounded(Rectangle{screen_width / 2 - 30, screen_height / 2 - 35, 10, 70}, 0.7, 10, BLACK);
        DrawRectangleRounded(Rectangle{screen_width / 2 + 20, screen_height / 2 - 35, 10, 70}, 0.7, 10, BLACK);

        game.ball.draw_ball();
        game.player.draw_paddle();
        game.ai.draw_paddle();
      }
    }
    if (game.match_ended) {
      game.show_end_menu();
    }
    EndDrawing();
  }
  CloseWindow();
  UnloadSound(soundCollision);
  CloseAudioDevice();
  return 0;
}
