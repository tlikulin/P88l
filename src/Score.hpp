#include <SFML/Graphics.hpp>
#include "Ball.hpp"

class Score
{
public:
    Score();
    void setFont(const sf::Font& font);
    void update(Ball::BallType type);
    void draw(sf::RenderWindow& window);
private:
    int m_player1 = 0;
    int m_player2 = 0;
    sf::Text m_textPlayer1;
    sf::Text m_textSeparator;
    sf::Text m_textPlayer2;
};