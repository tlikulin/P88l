#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Ball.hpp"
#include "Trajectory.hpp"
#include "Specs.hpp"

class Game
{
public:
    Game();
    bool loadResources();
    bool isRunning();
    void gameLoop();
private:
    void handleEvent(const sf::Event& event);
    void update();
    void draw();
private:
    // game objects
    sf::RenderWindow m_window;
    sf::RectangleShape m_table;
    std::vector<Ball> m_balls;
    Trajectory m_trajectory;
    // resources
    sf::SoundBuffer m_bufferCollision;
    sf::Sound m_soundCollision;
    // time keeping
    sf::Clock m_clock;
    float m_deltaTime = 0.0f;
    // states
    sf::Vector2f m_chargeStart;
    bool m_isCharging = false;
    bool m_isEquilibrium = false;
    int m_cueIndex = 0;
};
