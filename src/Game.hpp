#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <filesystem>
#include "Ball.hpp"
#include "Trajectory.hpp"
#include "Table.hpp"
#include "Pockets.hpp"
#include "FPSCounter.hpp"

class Game
{
public:
    Game(const char* path);
    bool isRunning() { return m_window.isOpen(); }
    void gameLoop();
private:
    void initializeBalls();
    void handleEvent(const sf::Event& event);
    void handleMouseButtonPressed(const sf::Event& event, const sf::Vector2f& mousePos);
    void handleMouseButtonReleased(const sf::Event& event, const sf::Vector2f& mousePos);
    void handleKeyPressed(const sf::Event& event);
    void update();
    bool checkEquilibrium();
    void draw();
private:
    // game objects
    sf::RenderWindow m_window;
    Table m_table;
    Pockets m_pockets;
    std::vector<Ball> m_balls;
    Trajectory m_trajectory;
    // UI
    FPSCounter m_fpsCounter;
    bool m_isFpsShown = true;
    // resources
    std::filesystem::path m_path;
    sf::SoundBuffer m_bufferCollision;
    sf::Sound m_soundCollision;
    sf::SoundBuffer m_bufferPotting;
    sf::Sound m_soundPotting;
    sf::Font m_font;
    // time
    sf::Clock m_clock;
    float m_deltaTime = 0.0f;
    // states
    bool m_isCharging = false;
    bool m_isEquilibrium = false;
};
