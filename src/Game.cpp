#include "Game.hpp"
#include "Spec.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <string>

Game::Game() :
    m_trajectory{Trajectory::Detailed}
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    m_window.create(sf::VideoMode(Spec::SCREEN_WIDTH, Spec::SCREEN_HEIGHT), Spec::TITLE, sf::Style::Titlebar | sf::Style::Close, settings);
    m_window.setFramerateLimit(144);

    m_balls.emplace_back(Spec::BALL_RADIUS, sf::Color::White, sf::Vector2f(600.0f, 300.0f), Ball::Cue);
    m_balls.emplace_back(Spec::BALL_RADIUS, sf::Color{0xff0000ff}, sf::Vector2f(600.0f, 500.0f), Ball::Default);
    for (int i = 0, n = 5; i < n; i++)
    {
        m_balls.emplace_back(Spec::BALL_RADIUS, sf::Color{0xffff3cff}, sf::Vector2f((i + 1) * Spec::TABLE_WIDTH / n, 400.0f), Ball::Default);
    }
}

bool Game::loadResources()
{
    if (!m_font.loadFromFile("media/fonts/MesloLGS NF Regular.ttf"))
        return false;
    m_fpsCounter.setFont(m_font);
    if (!m_bufferCollision.loadFromFile("media/audio/ball_collision.wav"))
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
        handleMouseButtonPressed(event, sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)));
        break;
    case sf::Event::MouseButtonReleased:
        handleMouseButtonReleased(event, sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)));
        break;
    case sf::Event::KeyPressed:
        handleKeyPressed(event);
        break;
    default:
        break;
    }
}

void Game::handleMouseButtonPressed(const sf::Event& event, const sf::Vector2f& mousePos)
{
    if (m_isEquilibrium 
        && event.mouseButton.button == sf::Mouse::Left 
        && m_balls[m_cueIndex].isWithinBall(mousePos))
    {
        m_isCharging = true;
        m_window.setTitle(Spec::TITLE_CHARGING);
    }
}

void Game::handleMouseButtonReleased(const sf::Event& event, const sf::Vector2f& mousePos)
{
    if (m_isCharging && event.mouseButton.button == sf::Mouse::Left)
    {
        if (!m_balls[m_cueIndex].isWithinBall(mousePos))
        {
            sf::Vector2f chargeVelocity = m_balls[m_cueIndex].getPosition() - mousePos;
            chargeVelocity *= 3.5f;
            if (std::hypot(chargeVelocity.x, chargeVelocity.y) > Spec::MAX_CHARGE_VELOCITY)
            {
                chargeVelocity *= Spec::MAX_CHARGE_VELOCITY / std::hypot(chargeVelocity.x, chargeVelocity.y);
            }
            m_balls[m_cueIndex].setVelocity(chargeVelocity);
            m_soundCollision.play();
        }

        m_isCharging = false;
        m_window.setTitle(Spec::TITLE);
    }
}

void Game::handleKeyPressed(const sf::Event& event)
{
    if (event.key.code == sf::Keyboard::P)
    {
        m_trajectory.cycleMode();
    }
    else if (event.key.code == sf::Keyboard::Tilde)
    {
        m_isFpsShown = !m_isFpsShown;
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

    m_isEquilibrium = checkEquilibrium();

    if (m_isCharging)
        m_trajectory.update(m_balls[m_cueIndex].getPosition(), static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window)));

    m_fpsCounter.update(m_deltaTime);
}

bool Game::checkEquilibrium()
{
    for (const Ball& ball : m_balls)
        if (ball.getVelocity() != sf::Vector2f(0.0f, 0.0f))
            return false;
    return true;
}

void Game::draw()
{
    m_window.clear(Spec::BG_COLOUR);
    m_table.draw(m_window);
    m_pockets.draw(m_window);
    for (const Ball& ball : m_balls)
        ball.draw(m_window);
    if (m_isCharging)
        m_trajectory.draw(m_window);
    if (m_isFpsShown)
        m_fpsCounter.draw(m_window);
    m_window.display();
}
