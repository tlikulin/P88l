#pragma once

#include <SFML/Graphics.hpp>
#include "Specs.hpp"

class Trajectory
{
public:
    void update(const sf::Vector2f& chargeStart, const sf::Vector2f& mousePosition);
    void draw(sf::RenderWindow& window);

private:
    sf::Vertex segment1[2];
    sf::Vertex segment2[2];
    bool isExtensionNeeded = false;
};
