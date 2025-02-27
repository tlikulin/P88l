#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Spec.hpp"
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
private:
    std::array<sf::CircleShape, Spec::NUM_POCKETS> m_pockets;
    sf::Sound m_soundPotting;
};
