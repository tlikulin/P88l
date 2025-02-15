#pragma once

#include <SFML/Graphics.hpp>

class Trajectory
{
public:
    enum TrajectoryMode : std::uint8_t
    {
        None = 0,
        Minimum,
        Normal,
        Detailed,
        All
    }; 
public:
    explicit Trajectory(TrajectoryMode mode);
    void update(const sf::Vector2f& chargeStart, const sf::Vector2f& mousePos);
    void draw(sf::RenderWindow& window);
    void cycleMode();
private:
    void setColor(const sf::Color& color);
    void updateReflection();
    void updateExtra1();
    void updateExtra2();
private:
    sf::Vertex m_segment1[2];
    sf::Vertex m_segment1L[2];
    sf::Vertex m_segment1R[2];
    sf::Vertex m_segment2[2];
    sf::Vertex m_segment2L[2];
    sf::Vertex m_segment2R[2];
    sf::CircleShape m_ballPrev1;
    sf::CircleShape m_ballPrev2;
    bool m_isExtensionNeeded = false;
    TrajectoryMode m_mode;
};
