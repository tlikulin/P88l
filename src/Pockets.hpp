#include <SFML/Graphics.hpp>
#include "Spec.hpp"
#include "Ball.hpp"
#include <array>
#include <utility>

class Pockets
{
public:
    Pockets();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    bool isBallPotted(Ball& ball);
private:
    std::array<sf::CircleShape, Spec::NUM_POCKETS> m_pockets;
    std::array<std::pair<sf::CircleShape, float>, Spec::NUM_POCKETS> m_effects;
};