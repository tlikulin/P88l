#pragma once
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <array>
#include <numbers>
#include <cmath>

namespace Spec
{
    //Window
    inline constexpr unsigned int SCREEN_WIDTH          = 1300u;
    inline constexpr unsigned int SCREEN_HEIGHT         = 800u;
    inline constexpr const char* const TITLE            = "P88l";
    //Table
    inline constexpr float TABLE_TOP                    = 150.0f;
    inline constexpr float TABLE_LEFT                   = 50.0f;
    inline constexpr float TABLE_WIDTH                  = 1200.0f;
    inline constexpr float TABLE_HEIGHT                 = 600.0f;
    inline constexpr float TABLE_BOTTOM                 = TABLE_TOP + TABLE_HEIGHT;
    inline constexpr float TABLE_RIGHT                  = TABLE_LEFT + TABLE_WIDTH;
    inline constexpr float TABLE_RAIL_WIDTH             = 45.0f;
    inline constexpr float TABLE_CONTOUR_WIDTH          = 3.0f;
    //Balls
    inline constexpr float BALL_RADIUS                  = 15.0f;
    inline constexpr float MAX_CHARGE_VELOCITY          = 3000.0f;
    inline constexpr float CHARGE_VELOCITY_COEF         = 3.0f;
    inline constexpr float FRICTION_COEF                = 80.0f;
    inline constexpr float SPEED_FRICTION_COEF          = 0.00065f;
    inline constexpr float REBOUND_COEF                 = 0.95f;
    inline constexpr float POTTING_ANIM_DURATION        = 1.2f;
    //starting position
    inline constexpr float BALL_SPACING                 = std::numbers::sqrt3_v<float> * BALL_RADIUS;
    inline constexpr size_t CUE_INDEX                   = 0;
    inline constexpr size_t EIGHTBALL_INDEX             = 11;
    inline constexpr size_t BALLS_PER_PLAYER            = 7;
    inline constexpr size_t BALLS_TOTAL                 = 2 * BALLS_PER_PLAYER + 2;
    inline constexpr float CUE_POS_X                    = TABLE_LEFT + 0.75f * TABLE_WIDTH;
    inline constexpr float CUE_POS_Y_MIN                = TABLE_TOP + 0.3f * TABLE_HEIGHT;
    inline constexpr float CUE_POS_Y_MAX                = TABLE_TOP + 0.7f * TABLE_HEIGHT;
    inline const sf::Vector2f BALL_TOPLEFT_POS          {TABLE_LEFT + 0.25f * TABLE_WIDTH, TABLE_TOP + 0.5f * TABLE_HEIGHT - 4.0f * BALL_RADIUS};
    //replacement
    inline constexpr size_t NUM_REPLACEMENT_POSITIONS   = 16;
    const std::array<sf::Vector2f, NUM_REPLACEMENT_POSITIONS> REPLACEMENT_POSITIONS{{
        {Spec::TABLE_LEFT + 0.2f * Spec::TABLE_WIDTH, Spec::TABLE_TOP + 0.2f * Spec::TABLE_HEIGHT},
        {Spec::TABLE_LEFT + 0.4f * Spec::TABLE_WIDTH, Spec::TABLE_TOP + 0.2f * Spec::TABLE_HEIGHT},
        {Spec::TABLE_LEFT + 0.6f * Spec::TABLE_WIDTH, Spec::TABLE_TOP + 0.2f * Spec::TABLE_HEIGHT},
        {Spec::TABLE_LEFT + 0.8f * Spec::TABLE_WIDTH, Spec::TABLE_TOP + 0.2f * Spec::TABLE_HEIGHT},
        {Spec::TABLE_LEFT + 0.2f * Spec::TABLE_WIDTH, Spec::TABLE_TOP + 0.4f * Spec::TABLE_HEIGHT},
        {Spec::TABLE_LEFT + 0.4f * Spec::TABLE_WIDTH, Spec::TABLE_TOP + 0.4f * Spec::TABLE_HEIGHT},
        {Spec::TABLE_LEFT + 0.6f * Spec::TABLE_WIDTH, Spec::TABLE_TOP + 0.4f * Spec::TABLE_HEIGHT},
        {Spec::TABLE_LEFT + 0.8f * Spec::TABLE_WIDTH, Spec::TABLE_TOP + 0.4f * Spec::TABLE_HEIGHT},
        {Spec::TABLE_LEFT + 0.2f * Spec::TABLE_WIDTH, Spec::TABLE_TOP + 0.6f * Spec::TABLE_HEIGHT},
        {Spec::TABLE_LEFT + 0.4f * Spec::TABLE_WIDTH, Spec::TABLE_TOP + 0.6f * Spec::TABLE_HEIGHT},
        {Spec::TABLE_LEFT + 0.6f * Spec::TABLE_WIDTH, Spec::TABLE_TOP + 0.6f * Spec::TABLE_HEIGHT},
        {Spec::TABLE_LEFT + 0.8f * Spec::TABLE_WIDTH, Spec::TABLE_TOP + 0.6f * Spec::TABLE_HEIGHT},
        {Spec::TABLE_LEFT + 0.2f * Spec::TABLE_WIDTH, Spec::TABLE_TOP + 0.8f * Spec::TABLE_HEIGHT},
        {Spec::TABLE_LEFT + 0.4f * Spec::TABLE_WIDTH, Spec::TABLE_TOP + 0.8f * Spec::TABLE_HEIGHT},
        {Spec::TABLE_LEFT + 0.6f * Spec::TABLE_WIDTH, Spec::TABLE_TOP + 0.8f * Spec::TABLE_HEIGHT},
        {Spec::TABLE_LEFT + 0.8f * Spec::TABLE_WIDTH, Spec::TABLE_TOP + 0.8f * Spec::TABLE_HEIGHT}
    }};
    //Pockets
    inline constexpr size_t NUM_POCKETS                 = 6;
    inline constexpr float POCKETS_OFFSET               = 5.0f;
    inline const std::array<sf::Vector2f, NUM_POCKETS> POCKETS_POS{{
        {TABLE_LEFT + POCKETS_OFFSET, TABLE_TOP + POCKETS_OFFSET}, 
        {TABLE_LEFT + POCKETS_OFFSET, TABLE_BOTTOM - POCKETS_OFFSET},
        {(TABLE_LEFT + TABLE_RIGHT)/2.0f, TABLE_TOP - POCKETS_OFFSET},
        {(TABLE_LEFT + TABLE_RIGHT)/2.0f, TABLE_BOTTOM + POCKETS_OFFSET},
        {TABLE_RIGHT - POCKETS_OFFSET, TABLE_TOP + POCKETS_OFFSET},
        {TABLE_RIGHT - POCKETS_OFFSET, TABLE_BOTTOM - POCKETS_OFFSET} 
    }};
    inline constexpr float POCKET_RADIUS                = 20.0f;
    inline constexpr float POCKET_THRESHOLD             = 0.9f * (Spec::BALL_RADIUS + Spec::POCKET_RADIUS);
    // UI
    inline constexpr unsigned int SCORE_CHAR_SIZE       = 40u;
    inline const sf::Vector2f SCORE1_POS                {static_cast<float>(SCREEN_WIDTH / 2 - SCORE_CHAR_SIZE / 4) - 60.0f, 25.0f};
    inline const sf::Vector2f SCORE_SEP_POS             {static_cast<float>(SCREEN_WIDTH / 2 - SCORE_CHAR_SIZE / 4), 20.0f}; 
    inline const sf::Vector2f SCORE2_POS                {static_cast<float>(SCREEN_WIDTH / 2 - SCORE_CHAR_SIZE / 4) + 60.0f, 25.0f}; 
    //Colors
    inline const sf::Color BG_COLOR                     {0xb8b8b8ff};
    inline const sf::Color TABLE_COLOR                  {0x62a66fff};
    inline const sf::Color TABLE_RAIL_COLOR             {0x7b4336ff};
    inline const sf::Color EIGHTBALL_COLOR              {0x010414ff};
    inline const sf::Color PLAYER1_COLOR                {0xfcd700ff};
    inline const sf::Color PLAYER2_COLOR                {0x720004ff}; 
    //Paths
    inline const std::filesystem::path MEDIA_DIR                = "media";
    inline const std::filesystem::path AUDIO_DIR                = MEDIA_DIR / "audio";
    inline const std::filesystem::path FONTS_DIR                = MEDIA_DIR / "fonts";
    inline const std::filesystem::path PATH_TO_CUE_SOUND        = AUDIO_DIR / "cue_strike.wav";
    inline const std::filesystem::path PATH_TO_COLLISION_SOUND  = AUDIO_DIR / "ball_collision.wav";
    inline const std::filesystem::path PATH_TO_POTTING_SOUND    = AUDIO_DIR / "potting.wav";
    inline const std::filesystem::path PATH_TO_FONT             = FONTS_DIR / "MesloLGS NF Regular.ttf";

    inline float hypot(const sf::Vector2f& vec)
    {
        return std::hypot(vec.x, vec.y);
    }
}
