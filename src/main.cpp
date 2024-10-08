#include <raylib.h>
#include "../include/game.h"
#include "../include/utils.h"

// TODO:
//  -[x] add a way to set the difficulty (start menu)
//  -[x] add end menu (wins first at 21)
//  -[x] limit ball speed
//  -[x] check vertical bounds for ball (limit the movement to 0+radius and screen height - radius)
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

    Game game;
    game.run_game();

    CloseWindow();
    UnloadSound(soundCollision);
    CloseAudioDevice();
    return 0;
}
