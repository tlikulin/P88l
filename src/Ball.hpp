#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// A single ball of a type with physics, display, and collision sound.
class Ball
{
public:
    enum BallType : std::uint8_t
    {
        None = 0,
        Cue,
        Eightball,
        Player1,
        Player2
    };
public:
    explicit Ball(sf::Vector2f position, BallType type, const sf::Texture* texture, const sf::SoundBuffer& buffer);

    static sf::Color colorFromType(BallType type);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;
    
    void checkCollisionWithBall(Ball& other);
    void checkCollisionWithBorder();
    
    void pot(const sf::Vector2f& pocket);
    void replace(const sf::Vector2f& pos);
    void playSound();
    
    void setVelocity(sf::Vector2f velocity)         { m_velocity = velocity; }
    void setScoredPosition(const sf::Vector2f& pos) { m_scoredPosition = pos; }
    
    sf::Vector2f getVelocity()  const { return m_velocity; }
    sf::Vector2f getPosition()  const { return m_body.getPosition(); }
    BallType getType()          const { return m_type; }
    float getVolume()           const { return m_soundCollision.getVolume(); }
    bool isPotted()             const { return m_isPotted; }
    bool isAnimationPlaying()   const { return m_animationDuration != 0.0f; }
    bool isWithinBall(const sf::Vector2f& pos) const;
private:
    float calculateAnimationRadiusFactor();
private:
    // Physics/state
    sf::CircleShape m_body;
    sf::Vector2f m_velocity;
    const BallType m_type;
    bool m_isPotted = false;
    // Amimation
    float m_animationDuration = 0.0f;
    sf::Vector2f m_animationShift{0.0f, 0.0f};
    sf::Vector2f m_scoredPosition{0.0f, 0.0f};
    // Sound
    sf::Sound m_soundCollision;
};
