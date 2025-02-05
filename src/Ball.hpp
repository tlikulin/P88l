#pragma once

#include <SFML/Graphics.hpp>

class Ball
{
public:
    enum BallType : std::uint8_t
    {
        Potted = 0,
        Cue,
        Player1,
        Player2,
        Eightball
    };
public:
    Ball(sf::Vector2f position, BallType type);

    void draw(sf::RenderWindow& window) const;
    void update(float deltaTime);

    bool checkCollisionWithBall(Ball& other);
    bool checkCollisionWithBorder();
    bool isWithinBall(float x, float y);
    bool isWithinBall(const sf::Vector2f& pos);
    void pot();

    void scaleVelocity(float xScale, float yScale);
    void setVelocity(sf::Vector2f velocity) { m_velocity = velocity; }

    sf::Vector2f getVelocity()  const { return m_velocity; }
    sf::Vector2f getPosition()  const { return m_body.getPosition(); }
    BallType getType()          const { return m_type; }

    static sf::Color colorFromType(BallType type);
private:
    sf::CircleShape m_body;
    sf::Vector2f m_velocity;
    BallType m_type;
};
