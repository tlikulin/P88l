#include <SFML/Graphics.hpp>
#include "Ball.hpp"
#include <vector>

class Score
{
public:
    Score();
    void setFont(const sf::Font& font);
    void update(Ball& ball);
    void draw(sf::RenderWindow& window);
private:
    unsigned int m_player1 = 0;
    unsigned int m_player2 = 0;
    sf::Text m_textPlayer1;
    sf::Text m_textSeparator;
    sf::Text m_textPlayer2;
    std::vector<sf::CircleShape> m_ballSlots;
};
