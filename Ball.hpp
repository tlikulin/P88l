#pragma once

#include <SFML/Graphics.hpp>
#include "Specs.hpp"

class Ball
{
public:
    enum class BallType
    {
        Default = 0,
        Cue
    };

public:
    Ball(float radius, sf::Color color, sf::Vector2f position, sf::Vector2f velocity = sf::Vector2f(0.0f, 0.0f), BallType type = BallType::Default);

    void draw(sf::RenderWindow& window) const;
    void update(float deltaTime);

    bool checkCollisionWithBall(Ball& other);
    bool checkCollisionWithBorder();
    bool isWithinBall(float x, float y);

    void scaleVelocity(float xScale, float yScale);
    
    void setVelocity(sf::Vector2f velocity) { m_velocity = velocity; }

    sf::Vector2f getVelocity()  const { return m_velocity; }
    float getRadius()           const { return m_body.getRadius(); }
    sf::Vector2f getPosition()  const { return m_body.getPosition(); }
    BallType getType()          const { return m_type; }

private:
    sf::CircleShape m_body;
    sf::Vector2f m_velocity;
    BallType m_type;
};
