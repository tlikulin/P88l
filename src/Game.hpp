#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <filesystem>
#include "Ball.hpp"
#include "Trajectory.hpp"
#include "Table.hpp"
#include "Pockets.hpp"
#include "FPSCounter.hpp"
#include "Score.hpp"

class Game
{
public:
    explicit Game(const char* path);
    void run();
private:
    enum GameState : std::uint8_t
    {
        None = 0,
        P1toMove,
        P1Aiming,
        P1Motion
    };
private:
    void initializeBalls();
    bool isRunning() { return m_window.isOpen(); }
    void gameLoop();
    void update();
    void draw();
    void handleEvent(const sf::Event& event);
    void handleMouseButtonPressed(const sf::Event& event, const sf::Vector2f& mousePos);
    void handleMouseButtonReleased(const sf::Event& event, const sf::Vector2f& mousePos);
    void handleKeyPressed(const sf::Event& event);
    bool checkEquilibrium();
    const char* getStateAsString();
    void replaceBall(Ball& ball);
    bool canPlaceBall(const sf::Vector2f& pos);
private:
    // game objects
    sf::RenderWindow m_window;
    Table m_table;
    Pockets m_pockets;
    std::vector<Ball> m_balls;
    Trajectory m_trajectory;
    // UI
    FPSCounter m_fpsCounter;
    Score m_score;
    sf::Text m_phase;
    // resources
    std::filesystem::path m_path;
    sf::SoundBuffer m_bufferCue;
    sf::Sound m_soundCue;
    sf::SoundBuffer m_bufferCollision;
    sf::Sound m_soundCollision;
    sf::SoundBuffer m_bufferPotting;
    sf::Sound m_soundPotting;
    sf::Font m_font;
    // time
    sf::Clock m_clock;
    float m_deltaTime = 0.0f;
    // states
    GameState m_state = None;
    bool m_isFpsShown = true;
};
