#include "Table.hpp"
#include "Specs.hpp"

Table::Table()
{
    m_cloth.setSize(sf::Vector2f(Specs::TABLE_WIDTH, Specs::TABLE_HEIGHT));
    m_cloth.setPosition(Specs::TABLE_LEFT, Specs::TABLE_TOP);
    m_cloth.setFillColor(Specs::TABLE_COLOUR);

    m_rails[0].setPointCount(4);
    m_rails[0].setPoint(0, {Specs::TABLE_LEFT, Specs::TABLE_TOP});
    m_rails[0].setPoint(1, {Specs::TABLE_LEFT - Specs::TABLE_RAIL_WIDTH, Specs::TABLE_TOP - Specs::TABLE_RAIL_WIDTH});
    m_rails[0].setPoint(2, {Specs::TABLE_RIGHT + Specs::TABLE_RAIL_WIDTH, Specs::TABLE_TOP - Specs::TABLE_RAIL_WIDTH});
    m_rails[0].setPoint(3, {Specs::TABLE_RIGHT, Specs::TABLE_TOP});
    m_rails[0].setFillColor(Specs::TABLE_RAIL_COLOUR);
    m_rails[1].setPointCount(4);
    m_rails[1].setPoint(0, {Specs::TABLE_RIGHT, Specs::TABLE_TOP});
    m_rails[1].setPoint(1, {Specs::TABLE_RIGHT + Specs::TABLE_RAIL_WIDTH, Specs::TABLE_TOP - Specs::TABLE_RAIL_WIDTH});
    m_rails[1].setPoint(2, {Specs::TABLE_RIGHT + Specs::TABLE_RAIL_WIDTH, Specs::TABLE_BOTTOM + Specs::TABLE_RAIL_WIDTH});
    m_rails[1].setPoint(3, {Specs::TABLE_RIGHT, Specs::TABLE_BOTTOM});
    m_rails[1].setFillColor(Specs::TABLE_RAIL_COLOUR);
    m_rails[2].setPointCount(4);
    m_rails[2].setPoint(0, {Specs::TABLE_RIGHT, Specs::TABLE_BOTTOM});
    m_rails[2].setPoint(1, {Specs::TABLE_RIGHT + Specs::TABLE_RAIL_WIDTH, Specs::TABLE_BOTTOM + Specs::TABLE_RAIL_WIDTH});
    m_rails[2].setPoint(2, {Specs::TABLE_LEFT - Specs::TABLE_RAIL_WIDTH, Specs::TABLE_BOTTOM + Specs::TABLE_RAIL_WIDTH});
    m_rails[2].setPoint(3, {Specs::TABLE_LEFT, Specs::TABLE_BOTTOM});
    m_rails[2].setFillColor(Specs::TABLE_RAIL_COLOUR);
    m_rails[3].setPointCount(4);
    m_rails[3].setPoint(0, {Specs::TABLE_LEFT, Specs::TABLE_BOTTOM});
    m_rails[3].setPoint(1, {Specs::TABLE_LEFT - Specs::TABLE_RAIL_WIDTH, Specs::TABLE_BOTTOM + Specs::TABLE_RAIL_WIDTH});
    m_rails[3].setPoint(2, {Specs::TABLE_LEFT - Specs::TABLE_RAIL_WIDTH, Specs::TABLE_TOP - Specs::TABLE_RAIL_WIDTH});
    m_rails[3].setPoint(3, {Specs::TABLE_LEFT, Specs::TABLE_TOP});
    m_rails[3].setFillColor(Specs::TABLE_RAIL_COLOUR);
}

void Table::draw(sf::RenderWindow& window)
{
    window.draw(m_cloth);
    for (const auto& rail : m_rails)
        window.draw(rail);
}