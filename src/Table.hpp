#include <SFML/Graphics.hpp>

class Table
{
public:
    Table();
    void draw(sf::RenderWindow& window);
private:
    sf::RectangleShape m_cloth;
    sf::RectangleShape m_rails;
};