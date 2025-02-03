#include "Pockets.hpp"

Pockets::Pockets()
{
    for (size_t i = 0; i < Spec::NUM_POCKETS; i++)
    {
        m_pockets[i].setPosition(Spec::POCKETS_POS[i]);
        m_pockets[i].setOrigin(Spec::POCKET_RADIUS, Spec::POCKET_RADIUS);
        m_pockets[i].setRadius(Spec::POCKET_RADIUS);
        m_pockets[i].setFillColor(sf::Color::Black);
    }
}

void Pockets::draw(sf::RenderWindow& window)
{
    for (const auto& pocket : m_pockets)
        window.draw(pocket);
}
