#pragma once
#include <raylib.h>
inline constexpr float screen_width = 1200.0f, screen_height = 800.0f;
inline constexpr auto Light_Green = Color{129, 204, 184, 255};
inline constexpr auto Blue = Color{66, 135, 245, 255};
inline constexpr auto Dark_Blue = Color{35, 90, 200, 255};
inline constexpr auto Light_Blue = Color{173, 216, 230, 255};
inline constexpr auto Yellow = Color{243, 213, 91, 255};
/*inline constexpr Color Green = Color{38, 185, 154, 255};
inline constexpr Color Dark_Green = Color{20, 160, 133, 255};*/
inline constexpr float maxBounceAngle = 75 * (PI / 180.0);
extern Sound soundCollision;
extern Sound blip;
extern Font font;

struct Timer {
    double lifeTime;
};


inline void StartTimer(Timer *timer, const double lifetime) {
    if (timer != nullptr)
        timer->lifeTime = lifetime;
}

inline bool TimerDone(const Timer *timer) {
    if (timer != nullptr) {
        return timer->lifeTime <= 0;
    }
    return false;
}

inline void UpdateTimer(Timer *timer) {
    if (timer != nullptr && timer->lifeTime > 0.0f) {
        timer->lifeTime -= GetFrameTime();
    }
}

inline int getSign(float n) { return n < 0 ? -1 : 1; }
