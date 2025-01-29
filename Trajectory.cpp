#include "Trajectory.hpp"

// Calculates the 2 segments of trajectory with reflection off the wall if needed
// Basically checks which wall the trajectory crosses, if any, and reflects in it
void Trajectory::update(const sf::Vector2f& chargeStart, const sf::Vector2f& mousePosition)
{
    segment1[0].position = chargeStart;
    segment1[1].position = segment1[0].position + 2.5f * (chargeStart - mousePosition);

    isExtensionNeeded = true;
    float gradient = (segment1[0].position.y - segment1[1].position.y) / (segment1[0].position.x - segment1[1].position.x);

    if (segment1[1].position.y < Specs::TABLE_TOP) // top
    {
        float x_intercept = segment1[0].position.x + (Specs::TABLE_TOP - segment1[0].position.y) / gradient;

        if (x_intercept < Specs::TABLE_LEFT) // left wall
        {
            segment2[1].position.x = 2 * Specs::TABLE_LEFT - segment1[1].position.x;
            segment2[1].position.y = segment1[1].position.y;
            segment1[1].position.y = segment1[0].position.y - (segment1[0].position.x - Specs::TABLE_LEFT) * gradient;
            segment1[1].position.x = Specs::TABLE_LEFT;
        }
        else if (x_intercept > Specs::TABLE_RIGHT) // right wall
        {
            segment2[1].position.x = 2 * Specs::TABLE_RIGHT - segment1[1].position.x;
            segment2[1].position.y = segment1[1].position.y;
            segment1[1].position.y = segment1[0].position.y - (segment1[0].position.x - Specs::TABLE_RIGHT) * gradient;
            segment1[1].position.x = Specs::TABLE_RIGHT;
        }
        else // top wall
        {
            segment2[1].position.x = segment1[1].position.x;
            segment2[1].position.y = 2 * Specs::TABLE_TOP - segment1[1].position.y;
            segment1[1].position.x = segment1[0].position.x - (segment1[0].position.y - Specs::TABLE_TOP) / gradient;
            segment1[1].position.y = Specs::TABLE_TOP;
        }
    }
    else if (segment1[1].position.y > Specs::TABLE_BOTTOM) // bottom
    {
        float x_intercept = segment1[0].position.x + (Specs::TABLE_BOTTOM - segment1[0].position.y) / gradient;

        if (x_intercept < Specs::TABLE_LEFT) // left wall
        {
            segment2[1].position.x = 2 * Specs::TABLE_LEFT - segment1[1].position.x;
            segment2[1].position.y = segment1[1].position.y;
            segment1[1].position.y = segment1[0].position.y - (segment1[0].position.x - Specs::TABLE_LEFT) * gradient;
            segment1[1].position.x = Specs::TABLE_LEFT;
        }
        else if (x_intercept > Specs::TABLE_RIGHT) // right wall
        {
            segment2[1].position.x = 2 * Specs::TABLE_RIGHT - segment1[1].position.x;
            segment2[1].position.y = segment1[1].position.y;
            segment1[1].position.y = segment1[0].position.y - (segment1[0].position.x - (Specs::TABLE_RIGHT)) * gradient;
            segment1[1].position.x = Specs::TABLE_RIGHT;
        }
        else // bottom wall
        {
            segment2[1].position.x = segment1[1].position.x;
            segment2[1].position.y = 2 * (Specs::TABLE_BOTTOM) - segment1[1].position.y;
            segment1[1].position.x = segment1[0].position.x - (segment1[0].position.y - (Specs::TABLE_BOTTOM)) / gradient;
            segment1[1].position.y = Specs::TABLE_BOTTOM;
        }
    }
    else // middle
    {
        if (segment1[1].position.x < Specs::TABLE_LEFT) // left wall
        {
            segment2[1].position.x = 2 * Specs::TABLE_LEFT - segment1[1].position.x;
            segment2[1].position.y = segment1[1].position.y;
            segment1[1].position.y = segment1[0].position.y - (segment1[0].position.x - Specs::TABLE_LEFT) * gradient;
            segment1[1].position.x = Specs::TABLE_LEFT;
        }
        else if (segment1[1].position.x > Specs::TABLE_RIGHT) // right wall
        {
            segment2[1].position.x = 2 * (Specs::TABLE_RIGHT) - segment1[1].position.x;
            segment2[1].position.y = segment1[1].position.y;
            segment1[1].position.y = segment1[0].position.y - (segment1[0].position.x - (Specs::TABLE_RIGHT)) * gradient;
            segment1[1].position.x = Specs::TABLE_RIGHT;
        }
        else // neither
        {
            isExtensionNeeded = false; 
        }
    }
}

// Displays the trajectory, the second segment not always needed
void Trajectory::draw(sf::RenderWindow& window)
{
    window.draw(segment1, 2, sf::Lines);

    if (isExtensionNeeded)
    {
        segment2[0].position = segment1[1].position;
        window.draw(segment2, 2, sf::Lines);
    }
}