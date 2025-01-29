#include "Game.hpp"
#include <cmath>
#include <algorithm>

Game::Game() :
    m_table(sf::Vector2f(Specs::TABLE_WIDTH, Specs::TABLE_HEIGHT))
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    m_window.create(sf::VideoMode(Specs::SCREEN_WIDTH, Specs::SCREEN_HEIGHT), "P88l", sf::Style::Titlebar | sf::Style::Close, settings);

    m_table.setPosition(Specs::TABLE_LEFT, Specs::TABLE_TOP);
    m_table.setFillColor(sf::Color(34, 139, 34));

    m_balls.emplace_back(Specs::BALL_RADIUS, sf::Color::White, sf::Vector2f(600.0f, 300.0f), sf::Vector2f(0.0f, 0.0f), Ball::BallType::Cue);
    m_balls.emplace_back(Specs::BALL_RADIUS, sf::Color::Red, sf::Vector2f(600.0f, 500.0f), sf::Vector2f(0.0f, 0.0f), Ball::BallType::Default);
    for (int i = 0, n = 5; i < n; ++i)
    {
        m_balls.emplace_back(Specs::BALL_RADIUS, sf::Color::Yellow, sf::Vector2f((i + 1) * Specs::TABLE_WIDTH / n, 400.0f));
    }
}

bool Game::loadResources()
{
    if (!m_bufferCollision.loadFromFile("ball_collision.wav"))
        return false;
    m_soundCollision.setBuffer(m_bufferCollision);

    return true;
}

bool Game::isRunning()
{
    return m_window.isOpen();
}

void Game::gameLoop()
{
    m_deltaTime = m_clock.restart().asSeconds();

    sf::Event event;
    while (m_window.pollEvent(event))
        handleEvent(event);
    
    update();
    draw();
}

void Game::handleEvent(const sf::Event& event)
{
    switch (event.type)
    {
    case sf::Event::Closed:
        m_window.close();
        break;
    case sf::Event::MouseButtonPressed:
        if (m_isEquilibrium 
            && event.mouseButton.button == sf::Mouse::Left 
            && m_balls[m_cueIndex].isWithinBall(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
        {
            m_chargeStart = m_balls[m_cueIndex].getPosition();
            m_isCharging = true;
            m_window.setTitle("P88l - charging");
        }
        break;
    case sf::Event::MouseButtonReleased:
        if (m_isCharging && event.mouseButton.button == sf::Mouse::Left)
        {
            if (!m_balls[m_cueIndex].isWithinBall(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
            {
                sf::Vector2f chargeVelocity = m_chargeStart - sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y);
                chargeVelocity *= 3.5f;
                if (hypotf(chargeVelocity.x, chargeVelocity.y) > Specs::MAX_CHARGE_VELOCITY)
                {
                    chargeVelocity *= Specs::MAX_CHARGE_VELOCITY / hypotf(chargeVelocity.x, chargeVelocity.y);
                }
                m_balls[m_cueIndex].setVelocity(chargeVelocity);
                m_soundCollision.play();
            }

            m_isCharging = false;
            m_window.setTitle("P88l");
        }
        break;
    default:
        break;
    }
}

void Game::update()
{
    if (!m_isEquilibrium)
    {
        for (Ball& ball : m_balls)
        {
            ball.update(m_deltaTime);
            if (ball.checkCollisionWithBorder())
                m_soundCollision.play();
        }

        for (int i = 0, n = m_balls.size(); i < n; ++i)
                for (int j = i + 1; j < n; ++j)
                    if (m_balls[i].checkCollisionWithBall(m_balls[j]))
                        m_soundCollision.play();
    }

    m_isEquilibrium = std::all_of(m_balls.begin(), m_balls.end(), [](const Ball &ball)
                                    { return ball.getVelocity() == sf::Vector2f(0.0f, 0.0f); });

    if (m_isCharging)
        m_trajectory.update(m_chargeStart, static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window)));
}

void Game::draw()
{
    m_window.clear(sf::Color(200, 200, 200));
    m_window.draw(m_table);
    for (const Ball& ball : m_balls)
        ball.draw(m_window);
    if (m_isCharging)
        m_trajectory.draw(m_window);
    m_window.display();
}
