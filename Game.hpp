#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Ball.hpp"
#include "Trajectory.hpp"
#include "Table.hpp"

class Game
{
public:
    Game();
    bool loadResources();
    bool isRunning();
    void gameLoop();
private:
    void handleEvent(const sf::Event& event);
    void handleMouseButtonPressed(const sf::Event& event, const sf::Vector2f& mousePos);
    void handleMouseButtonReleased(const sf::Event& event, const sf::Vector2f& mousePos);
    void update();
    bool checkEquilibrium();
    void draw();
private:
    // game objects
    sf::RenderWindow m_window;
    Table m_table;
    std::vector<Ball> m_balls;
    Trajectory m_trajectory;
    // resources
    sf::SoundBuffer m_bufferCollision;
    sf::Sound m_soundCollision;
    // time
    sf::Clock m_clock;
    float m_deltaTime = 0.0f;
    // states
    bool m_isCharging = false;
    bool m_isEquilibrium = false;
    const int m_cueIndex = 0;
};
