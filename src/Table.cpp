#include "Table.hpp"
#include "Spec.hpp"

Table::Table()
{
    m_cloth.setSize({Spec::TABLE_WIDTH, Spec::TABLE_HEIGHT});
    m_cloth.setPosition(Spec::TABLE_LEFT, Spec::TABLE_TOP);
    m_cloth.setFillColor(Spec::TABLE_COLOR);
    m_cloth.setOutlineColor(sf::Color::Black);
    m_cloth.setOutlineThickness(Spec::TABLE_CONTOUR_WIDTH);

    m_rails.setSize({Spec::TABLE_WIDTH + 2.0f * Spec::TABLE_RAIL_WIDTH, Spec::TABLE_HEIGHT + 2.0f * Spec::TABLE_RAIL_WIDTH});
    m_rails.setPosition(Spec::TABLE_LEFT - Spec::TABLE_RAIL_WIDTH, Spec::TABLE_TOP - Spec::TABLE_RAIL_WIDTH);
    m_rails.setFillColor(Spec::TABLE_RAIL_COLOR);
    m_rails.setOutlineColor(sf::Color::Black);
    m_rails.setOutlineThickness(Spec::TABLE_CONTOUR_WIDTH);
}

void Table::draw(sf::RenderWindow& window)
{
    window.draw(m_rails);
    window.draw(m_cloth);
}