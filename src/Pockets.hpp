#include <SFML/Graphics.hpp>
#include "Spec.hpp"
#include <array>

class Pockets
{
public:
    Pockets();
    void draw(sf::RenderWindow& window);
private:
    std::array<sf::CircleShape, Spec::NUM_POCKETS> m_pockets;
};