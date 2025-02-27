#pragma once

#include <SFML/Graphics.hpp>
#include <array>

class Trajectory
{
public:
    // None - none; minimum - middle; normal - middle and circle; detailed - lateral and circle; all - lateral, middle, and circle
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
    void updateMiddle(const sf::Vector2f& chargeStart, const sf::Vector2f& mousePos);
    void updateLateral();

    void setColor(const sf::Color& color);
private:
    static constexpr size_t SEGMENTS_MAX = 4;
    // linear and circluar segments
    std::array<sf::Vertex, 2*SEGMENTS_MAX> m_segmentsMiddle;
    std::array<sf::Vertex, 2*SEGMENTS_MAX> m_segmentsLeft;
    std::array<sf::Vertex, 2*SEGMENTS_MAX> m_segmentsRight;
    std::array<sf::CircleShape, SEGMENTS_MAX> m_ballPreviews;
    // display parameters
    size_t m_numSegmentsNeeded = 1;
    TrajectoryMode m_mode;
};
