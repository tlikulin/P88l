#pragma once

#include <SFML/Graphics.hpp>
#include <array>

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
    void updateMiddle(const sf::Vector2f& chargeStart, const sf::Vector2f& mousePos);
    void updateLateral();
private:
    static constexpr size_t SEGMENTS_MAX = 4;
    
    std::array<sf::Vertex, 2*SEGMENTS_MAX> m_segmentsMiddle;
    std::array<sf::Vertex, 2*SEGMENTS_MAX> m_segmentsLeft;
    std::array<sf::Vertex, 2*SEGMENTS_MAX> m_segmentsRight;
    std::array<sf::CircleShape, SEGMENTS_MAX> m_ballPreviews;

    size_t m_numSegmentsNeeded = 1;
    TrajectoryMode m_mode;
};
