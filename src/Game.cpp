#include "Game.hpp"
#include "Spec.hpp"
#include <cmath>
#include <random>

Game::Game(const char* path) :
    m_trajectory{Trajectory::Normal},
    m_path{std::filesystem::canonical(std::filesystem::path{path}).parent_path()}
{
    m_font.loadFromFile(m_path / Spec::PATH_TO_FONT);
    m_fpsCounter.setFont(m_font);
    m_score.setFont(m_font);
    m_bufferCollision.loadFromFile(m_path / Spec::PATH_TO_COLLISION_SOUND);
    m_soundCollision.setBuffer(m_bufferCollision);
    m_bufferPotting.loadFromFile(m_path / Spec::PATH_TO_POTTING_SOUND);
    m_soundPotting.setBuffer(m_bufferPotting);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    m_window.create(sf::VideoMode(Spec::SCREEN_WIDTH, Spec::SCREEN_HEIGHT), Spec::TITLE, sf::Style::Titlebar | sf::Style::Close, settings);
    m_window.setFramerateLimit(240);

    m_balls.reserve(Spec::BALLS_TOTAL);
    initializeBalls();
}

void Game::initializeBalls()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution distrib(0, 1);
    std::uniform_real_distribution<float> rdistrib(Spec::CUE_POS_Y_MIN, Spec::CUE_POS_Y_MAX);

    m_balls.emplace_back(sf::Vector2f{Spec::CUE_POS_X, rdistrib(gen)}, Ball::Cue);

    size_t player1Left = Spec::BALLS_PER_PLAYER;
    size_t player2Left = Spec::BALLS_PER_PLAYER;
    size_t currColumn = 5;
    size_t currIndex = 0;
    sf::Vector2f pos = Spec::BALL_TOPLEFT_POS;
    Ball::BallType type;

    for (size_t i = 1; i < Spec::BALLS_TOTAL; i++)
    {
        if (i == Spec::EIGHTBALL_INDEX)
        {
            type = Ball::Eightball;
        }
        else
        {
            if (player2Left == 0 || (player1Left > 0 && distrib(gen)))
            {
                type = Ball::Player1;
                player1Left--;
            }
            else
            {
                type = Ball::Player2;
                player2Left--;
            }
        }

        m_balls.emplace_back(pos + sf::Vector2f{0.0f, 2.0f * Spec::BALL_RADIUS * currIndex}, type);

        currIndex++;
        if (currIndex == currColumn)
        {
            currColumn--;
            currIndex = 0;
            pos += sf::Vector2f{Spec::BALL_SPACING, Spec::BALL_RADIUS};
        }
    }
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
        && m_balls[Spec::CUE_INDEX].isWithinBall(mousePos))
    {
        m_isCharging = true;
        m_window.setTitle(Spec::TITLE_CHARGING);
    }
}

void Game::handleMouseButtonReleased(const sf::Event& event, const sf::Vector2f& mousePos)
{
    if (m_isCharging && event.mouseButton.button == sf::Mouse::Left)
    {
        if (!m_balls[Spec::CUE_INDEX].isWithinBall(mousePos))
        {
            sf::Vector2f chargeVelocity = m_balls[Spec::CUE_INDEX].getPosition() - mousePos;
            chargeVelocity *= 3.5f;
            if (std::hypot(chargeVelocity.x, chargeVelocity.y) > Spec::MAX_CHARGE_VELOCITY)
            {
                chargeVelocity *= Spec::MAX_CHARGE_VELOCITY / std::hypot(chargeVelocity.x, chargeVelocity.y);
            }
            m_balls[Spec::CUE_INDEX].setVelocity(chargeVelocity);
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
    for (Ball& ball : m_balls)
    {
        ball.update(m_deltaTime);
        const Ball::BallType type = ball.getType();
        if (!m_isEquilibrium && type != Ball::Potted)
        {
            if (m_pockets.isBallPotted(ball))
            {
                m_score.update(type);
                m_soundPotting.play();
            }
            else if (ball.checkCollisionWithBorder())
                m_soundCollision.play();
        }
    }

    if (!m_isEquilibrium)
    {
        for (size_t i = 0; i < Spec::BALLS_TOTAL; i++)
        {
            for (size_t j = i + 1; j < Spec::BALLS_TOTAL; j++)
            {
                if (m_balls[i].checkCollisionWithBall(m_balls[j]))
                    m_soundCollision.play();
            }
        }
    }

    m_isEquilibrium = checkEquilibrium();

    if (m_isCharging)
        m_trajectory.update(m_balls[Spec::CUE_INDEX].getPosition(), static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window)));

    m_fpsCounter.update(m_deltaTime);
}

bool Game::checkEquilibrium()
{
    for (const Ball& ball : m_balls)
        if (ball.getType() != Ball::Potted
            && ball.getVelocity() != sf::Vector2f(0.0f, 0.0f))
            return false;
    return true;
}

void Game::draw()
{
    m_window.clear(Spec::BG_COLOR);
    m_table.draw(m_window);
    m_pockets.draw(m_window);
    for (const Ball& ball : m_balls)
        ball.draw(m_window);
    if (m_isCharging)
        m_trajectory.draw(m_window);
    m_score.draw(m_window);
    if (m_isFpsShown)
        m_fpsCounter.draw(m_window);
    m_window.display();
}
