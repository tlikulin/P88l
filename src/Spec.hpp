#pragma once
#include <SFML/Graphics.hpp>
#include <array>

namespace Spec
{
    //Window
    constexpr unsigned int SCREEN_WIDTH     = 1300u;
    constexpr unsigned int SCREEN_HEIGHT    = 800u;
    constexpr const char* TITLE             = "P88l";
    constexpr const char* TITLE_CHARGING    = "P88l - charging";
    //Table
    constexpr float TABLE_TOP               = 150.0f;
    constexpr float TABLE_LEFT              = 50.0f;
    constexpr float TABLE_WIDTH             = 1200.0f;
    constexpr float TABLE_HEIGHT            = 600.0f;
    constexpr float TABLE_BOTTOM            = TABLE_TOP + TABLE_HEIGHT;
    constexpr float TABLE_RIGHT             = TABLE_LEFT + TABLE_WIDTH;
    constexpr float TABLE_RAIL_WIDTH        = 45.0f;
    constexpr float TABLE_CONTOUR_WIDTH     = 3.0f;
    //Balls
    constexpr float BALL_RADIUS             = 20.0f;
    constexpr float REBOUND_COEF            = 0.95f;
    constexpr float MAX_CHARGE_VELOCITY     = 2500.0f;
    constexpr float FRICTION_COEF           = 120.0f;
    constexpr float SPEED_FRICTION_COEF     = 600.0f;
    //Pockets
    constexpr size_t NUM_POCKETS            = 6;
    constexpr float POCKETS_OFFSET          = 5.0f;
    const std::array<sf::Vector2f, NUM_POCKETS> POCKETS_POS{{{TABLE_LEFT + POCKETS_OFFSET, TABLE_TOP + POCKETS_OFFSET}, 
                                                             {TABLE_LEFT + POCKETS_OFFSET, TABLE_BOTTOM - POCKETS_OFFSET},
                                                             {(TABLE_LEFT + TABLE_RIGHT)/2.0f, TABLE_TOP},
                                                             {(TABLE_LEFT + TABLE_RIGHT)/2.0f, TABLE_BOTTOM},
                                                             {TABLE_RIGHT - POCKETS_OFFSET, TABLE_TOP + POCKETS_OFFSET},
                                                             {TABLE_RIGHT - POCKETS_OFFSET, TABLE_BOTTOM - POCKETS_OFFSET} }};
    constexpr float POCKET_RADIUS           = 27.5f;
    constexpr float POCKET_ANIM_THICKNESS   = 15.0f;
    constexpr float POCKET_ANIM_RADIUS      = 2.5f * POCKET_RADIUS;
    constexpr float POCKET_ANIM_DURATION    = 1.5f;
    //Colors
    const sf::Color BG_COLOR                {200, 200, 200};
    const sf::Color TABLE_COLOR             {0x62a66fff};
    const sf::Color TABLE_RAIL_COLOR        {0x7b4336ff};
    //Reltive paths
    constexpr const char* PATH_TO_COLLISION_SOUND   = "media/audio/ball_collision.wav";
    constexpr const char* PATH_TO_POTTING_SOUND     = "media/audio/potting.wav";
    constexpr const char* PATH_TO_FONT              = "media/fonts/MesloLGS NF Regular.ttf";
}