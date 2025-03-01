#include "Table.hpp"
#include "Spec.hpp"

namespace
{
    constexpr float TABLE_RAIL_WIDTH     = 45.0f;
    constexpr float TABLE_CONTOUR_WIDTH  = 3.0f;
    const sf::Color TABLE_COLOR          {0x62a66fff};
    const sf::Color TABLE_RAIL_COLOR     {0x7b4336ff};
}

Table::Table()
{
    m_cloth.setSize({Spec::TABLE_WIDTH, Spec::TABLE_HEIGHT});
    m_cloth.setPosition(Spec::TABLE_LEFT, Spec::TABLE_TOP);
    m_cloth.setFillColor(TABLE_COLOR);
    m_cloth.setOutlineColor(sf::Color::Black);
    m_cloth.setOutlineThickness(TABLE_CONTOUR_WIDTH);

    m_rails.setSize({Spec::TABLE_WIDTH + 2.0f * TABLE_RAIL_WIDTH, Spec::TABLE_HEIGHT + 2.0f * TABLE_RAIL_WIDTH});
    m_rails.setPosition(Spec::TABLE_LEFT - TABLE_RAIL_WIDTH, Spec::TABLE_TOP - TABLE_RAIL_WIDTH);
    m_rails.setFillColor(TABLE_RAIL_COLOR);
    m_rails.setOutlineColor(sf::Color::Black);
    m_rails.setOutlineThickness(TABLE_CONTOUR_WIDTH);
}

void Table::draw(sf::RenderWindow& window)
{
    window.draw(m_rails);
    window.draw(m_cloth);
}