#include <SFML/Graphics.hpp>
#include <array>

class Table
{
public:
    Table();
    void draw(sf::RenderWindow& window);
private:
    sf::RectangleShape m_cloth;
    std::array<sf::ConvexShape, 4> m_rails;
};