#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Ball.hpp"
#include <array>

// The 6 pockets that are drawn, play sound, and check if balls are potted.
class Pockets
{
public:
    Pockets();
    void setBuffer(const sf::SoundBuffer& buffer);

    void draw(sf::RenderWindow& window);

    bool checkBallPotted(Ball& ball);
public:
    static constexpr size_t NUM_POCKETS = 6;
private:

    std::array<sf::CircleShape, NUM_POCKETS> m_pockets;
    sf::Sound m_soundPotting;
};
