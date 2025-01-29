#pragma once
#include <SFML/Graphics.hpp>

namespace Specs
{
    //Window
    constexpr unsigned int SCREEN_WIDTH = 1300u;
    constexpr unsigned int SCREEN_HEIGHT = 800u;
    constexpr const char* TITLE = "P88l";
    constexpr const char* TITLE_CHARGING = "P88l - charging";
    const sf::Color BG_COLOUR(200, 200, 200);
    //Table
    constexpr float TABLE_TOP = 100.0f;
    constexpr float TABLE_LEFT = 50.0f;
    constexpr float TABLE_WIDTH = 1200.0f;
    constexpr float TABLE_HEIGHT = 600.0f;
    constexpr float TABLE_BOTTOM = TABLE_TOP + TABLE_HEIGHT;
    constexpr float TABLE_RIGHT = TABLE_LEFT + TABLE_WIDTH;
    const sf::Color TABLE_COLOUR(34, 139, 34);
    //Balls
    constexpr float BALL_RADIUS = 25.0f;
    constexpr float REBOUND_COEF = 0.97f;
    constexpr float MAX_CHARGE_VELOCITY = 2500.0f;
    constexpr float FRICTION_COEF = 120.0f;
    constexpr float SPEED_FRICTION_COEF = 600.0f;
    //Misc
    constexpr float PI = 3.1415927f;
}