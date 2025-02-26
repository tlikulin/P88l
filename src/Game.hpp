#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <filesystem>
#include <random>
#include <memory>
#include "Ball.hpp"
#include "Trajectory.hpp"
#include "Table.hpp"
#include "Pockets.hpp"
#include "FPSCounter.hpp"
#include "UI.hpp"
#include "Menu.hpp"

class Game
{
public:
    explicit Game(const char* path);
    void run();
private:
    enum GameState : std::uint8_t
    {
        None = 0,
        InMenu,
        PlayerToMove,
        PlayerAiming,
        BotAiming,
        PlayerMotion,
    };
private:
    void initializeBalls();
    void gameLoop();
    void update();
    void draw();
    void handleEvent(const sf::Event& event);
    void handleMouseButtonPressed(const sf::Event& event, const sf::Vector2f& mousePos);
    void handleMouseButtonReleased(const sf::Event& event, const sf::Vector2f& mousePos);
    void handleKeyPressed(const sf::Event& event);
    void nextTurn();
    bool checkEquilibrium();
    const char* getStateAsString();
    const char* getActivePlayerName();
    void replaceBall(Ball& ball);
    bool canPlaceBall(const sf::Vector2f& pos);
    void newGame();
    void switchPlayer();
    sf::Vector2f botFindClosestBall();
    void launchCueBall(const sf::Vector2f& mousePos);
private:
    // game objects
    sf::RenderWindow m_window;
    Table m_table;
    Pockets m_pockets;
    std::vector<Ball> m_balls;
    Trajectory m_trajectory;
    // UI
    FPSCounter m_fpsCounter;
    UI m_ui;
    Menu m_menu;
    // resources
    std::filesystem::path m_path;
    sf::SoundBuffer m_bufferCue;
    sf::Sound m_soundCue;
    sf::SoundBuffer m_bufferCollision;
    sf::SoundBuffer m_bufferPotting;
    sf::Font m_font;
    sf::Texture m_textureEightball;
    sf::Texture m_menuInfo;
    // time
    sf::Clock m_clock;
    float m_deltaTime = 0.0f;
    // states
    GameState m_state = None;
    unsigned char m_activePlayer = 1;
    unsigned char m_botPlaysAs = 0;
    bool m_wasP1BallPotted = false;
    bool m_wasP2BallPotted = false;
    bool m_isFpsShown = false;
    bool m_isMysteryEnabled = false;
    sf::Vector2f m_botMousePos;
    sf::Vector2f m_botMouseShift;
    float m_botAimingProgress = 0.0f;
    std::unique_ptr<std::mt19937> m_rng = std::make_unique<std::mt19937>(std::random_device{}());
};
