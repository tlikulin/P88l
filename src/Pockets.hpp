#include <SFML/Graphics.hpp>
#include "Spec.hpp"
#include "Ball.hpp"
#include <array>

class Pockets
{
public:
    Pockets();
    void draw(sf::RenderWindow& window);
    bool isBallPotted(Ball& ball);
private:
    std::array<sf::CircleShape, Spec::NUM_POCKETS> m_pockets;
};