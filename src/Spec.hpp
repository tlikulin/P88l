#pragma once
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <cmath>

// Contains window/paths-related values, constants needed across different translation units, and the Vector2f overload of hypot.
namespace Spec
{
    //Window
    inline constexpr unsigned int SCREEN_WIDTH  = 1300u;
    inline constexpr unsigned int SCREEN_HEIGHT = 800u;
    inline constexpr const char* const TITLE    = "P88l";
    //Paths
    inline const std::filesystem::path MEDIA_DIR                    = "media";
    inline const std::filesystem::path AUDIO_DIR                    = MEDIA_DIR / "audio";
    inline const std::filesystem::path FONTS_DIR                    = MEDIA_DIR / "fonts";
    inline const std::filesystem::path IMAGES_DIR                   = MEDIA_DIR / "images";
    inline const std::filesystem::path PATH_TO_CUE_SOUND            = AUDIO_DIR / "cue_strike.wav";
    inline const std::filesystem::path PATH_TO_COLLISION_SOUND      = AUDIO_DIR / "ball_collision.wav";
    inline const std::filesystem::path PATH_TO_POTTING_SOUND        = AUDIO_DIR / "potting.wav";
    inline const std::filesystem::path PATH_TO_FONT                 = FONTS_DIR / "MesloLGS NF Regular.ttf";
    inline const std::filesystem::path PATH_TO_EIGHTBALL_TEXTURE    = IMAGES_DIR / "eightball.png";
    inline const std::filesystem::path PATH_TO_MENU_INFO            = IMAGES_DIR / "menu_info.png";
    
    //Table
    inline constexpr float TABLE_TOP            = 150.0f;
    inline constexpr float TABLE_LEFT           = 50.0f;
    inline constexpr float TABLE_WIDTH          = 1200.0f;
    inline constexpr float TABLE_HEIGHT         = 600.0f;
    inline constexpr float TABLE_BOTTOM         = TABLE_TOP + TABLE_HEIGHT;
    inline constexpr float TABLE_RIGHT          = TABLE_LEFT + TABLE_WIDTH;
    //Balls
    inline constexpr size_t BALLS_PER_PLAYER    = 7;
    inline constexpr size_t BALLS_TOTAL         = 2 * BALLS_PER_PLAYER + 2;
    inline constexpr float BALL_RADIUS          = 15.0f;
    inline constexpr float MAX_CHARGE_SPEED     = 3000.0f;
    inline constexpr float CHARGE_VELOCITY_COEF = 3.5f;
    //Colors
    inline const sf::Color PLAYER1_COLOR        {0xfcd700ff};
    inline const sf::Color PLAYER2_COLOR        {0x720004ff}; 

    //hypot overload
    inline float hypot(const sf::Vector2f& vec)
    {
        return std::hypot(vec.x, vec.y);
    }
}
