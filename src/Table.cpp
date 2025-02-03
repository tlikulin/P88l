#include "Table.hpp"
#include "Spec.hpp"

Table::Table()
{
    m_cloth.setSize(sf::Vector2f(Spec::TABLE_WIDTH, Spec::TABLE_HEIGHT));
    m_cloth.setPosition(Spec::TABLE_LEFT, Spec::TABLE_TOP);
    m_cloth.setFillColor(Spec::TABLE_COLOUR);

    m_rails[0].setPointCount(4);
    m_rails[0].setPoint(0, {Spec::TABLE_LEFT, Spec::TABLE_TOP});
    m_rails[0].setPoint(1, {Spec::TABLE_LEFT - Spec::TABLE_RAIL_WIDTH, Spec::TABLE_TOP - Spec::TABLE_RAIL_WIDTH});
    m_rails[0].setPoint(2, {Spec::TABLE_RIGHT + Spec::TABLE_RAIL_WIDTH, Spec::TABLE_TOP - Spec::TABLE_RAIL_WIDTH});
    m_rails[0].setPoint(3, {Spec::TABLE_RIGHT, Spec::TABLE_TOP});
    m_rails[0].setFillColor(Spec::TABLE_RAIL_COLOUR);
    m_rails[1].setPointCount(4);
    m_rails[1].setPoint(0, {Spec::TABLE_RIGHT, Spec::TABLE_TOP});
    m_rails[1].setPoint(1, {Spec::TABLE_RIGHT + Spec::TABLE_RAIL_WIDTH, Spec::TABLE_TOP - Spec::TABLE_RAIL_WIDTH});
    m_rails[1].setPoint(2, {Spec::TABLE_RIGHT + Spec::TABLE_RAIL_WIDTH, Spec::TABLE_BOTTOM + Spec::TABLE_RAIL_WIDTH});
    m_rails[1].setPoint(3, {Spec::TABLE_RIGHT, Spec::TABLE_BOTTOM});
    m_rails[1].setFillColor(Spec::TABLE_RAIL_COLOUR);
    m_rails[2].setPointCount(4);
    m_rails[2].setPoint(0, {Spec::TABLE_RIGHT, Spec::TABLE_BOTTOM});
    m_rails[2].setPoint(1, {Spec::TABLE_RIGHT + Spec::TABLE_RAIL_WIDTH, Spec::TABLE_BOTTOM + Spec::TABLE_RAIL_WIDTH});
    m_rails[2].setPoint(2, {Spec::TABLE_LEFT - Spec::TABLE_RAIL_WIDTH, Spec::TABLE_BOTTOM + Spec::TABLE_RAIL_WIDTH});
    m_rails[2].setPoint(3, {Spec::TABLE_LEFT, Spec::TABLE_BOTTOM});
    m_rails[2].setFillColor(Spec::TABLE_RAIL_COLOUR);
    m_rails[3].setPointCount(4);
    m_rails[3].setPoint(0, {Spec::TABLE_LEFT, Spec::TABLE_BOTTOM});
    m_rails[3].setPoint(1, {Spec::TABLE_LEFT - Spec::TABLE_RAIL_WIDTH, Spec::TABLE_BOTTOM + Spec::TABLE_RAIL_WIDTH});
    m_rails[3].setPoint(2, {Spec::TABLE_LEFT - Spec::TABLE_RAIL_WIDTH, Spec::TABLE_TOP - Spec::TABLE_RAIL_WIDTH});
    m_rails[3].setPoint(3, {Spec::TABLE_LEFT, Spec::TABLE_TOP});
    m_rails[3].setFillColor(Spec::TABLE_RAIL_COLOUR);

    m_contour.setSize({Spec::TABLE_WIDTH, Spec::TABLE_HEIGHT});
    m_contour.setFillColor(sf::Color::Transparent);
    m_contour.setOutlineColor(sf::Color::Black);
    m_contour.setOutlineThickness(3.0f);
    m_contour.setPosition(Spec::TABLE_LEFT, Spec::TABLE_TOP);

    m_outerContour.setSize({Spec::TABLE_WIDTH+2.0f*Spec::TABLE_RAIL_WIDTH, Spec::TABLE_HEIGHT+2.0f*Spec::TABLE_RAIL_WIDTH});
    m_outerContour.setFillColor(sf::Color::Transparent);
    m_outerContour.setOutlineColor(sf::Color::Black);
    m_outerContour.setOutlineThickness(3.0f);
    m_outerContour.setPosition(Spec::TABLE_LEFT-Spec::TABLE_RAIL_WIDTH, Spec::TABLE_TOP-Spec::TABLE_RAIL_WIDTH);
}

void Table::draw(sf::RenderWindow& window)
{
    window.draw(m_cloth);
    for (const auto& rail : m_rails)
        window.draw(rail);
    window.draw(m_contour);
    window.draw(m_outerContour);
}