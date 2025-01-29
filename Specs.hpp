#pragma once

namespace Specs
{
    //Screen
    constexpr unsigned int SCREEN_WIDTH = 1300u;
    constexpr unsigned int SCREEN_HEIGHT = 800u;
    //Table
    constexpr float TABLE_TOP = 100.0f;
    constexpr float TABLE_LEFT = 50.0f;
    constexpr float TABLE_WIDTH = 1200.0f;
    constexpr float TABLE_HEIGHT = 600.0f;
    constexpr float TABLE_BOTTOM = TABLE_TOP + TABLE_HEIGHT;
    constexpr float TABLE_RIGHT = TABLE_LEFT + TABLE_WIDTH;
    //Balls
    constexpr float BALL_RADIUS = 25.0f;
    constexpr float BORDER_REBOUND_COEF = 0.95f;
    constexpr float MAX_CHARGE_VELOCITY = 2500.0f;
    constexpr float FRICTION_COEF = 120.0f;
    constexpr float SPEED_FRICTION_COEF = 600.0f;
    //Misc
    constexpr float PI = 3.1415927f;
}