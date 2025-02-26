#include "Game.hpp"
#include "Spec.hpp"
#include <cmath>

namespace
{
    float botAimingTime = 1.5f;
}

Game::Game(const char* path) :
    m_trajectory{Trajectory::Normal},
    m_path{std::filesystem::canonical(std::filesystem::path{path}).parent_path().parent_path()},
    m_state{InMenu}
{
    m_font.loadFromFile(m_path / Spec::PATH_TO_FONT);
    m_fpsCounter.setFont(m_font);
    m_ui.setFont(m_font);
    
    sf::Listener::setPosition(Spec::TABLE_LEFT + 0.5f * Spec::TABLE_WIDTH, 0.0f, Spec::TABLE_BOTTOM);
    sf::Listener::setGlobalVolume(100.0f);
    m_bufferCue.loadFromFile(m_path / Spec::PATH_TO_CUE_SOUND);
    m_soundCue.setBuffer(m_bufferCue);
    m_soundCue.setAttenuation(0.0f);
    m_bufferCollision.loadFromFile(m_path / Spec::PATH_TO_COLLISION_SOUND);
    m_bufferPotting.loadFromFile(m_path / Spec::PATH_TO_POTTING_SOUND);
    m_pockets.setBuffer(m_bufferPotting);
    
    m_textureEightball.loadFromFile(m_path / Spec::PATH_TO_EIGHTBALL_TEXTURE);
    m_textureEightball.setSmooth(true);
    m_menuInfo.loadFromFile(m_path / Spec::PATH_TO_MENU_INFO);
    m_menu.setFontAndTexture(m_font, m_menuInfo);
    
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    m_window.create(sf::VideoMode(Spec::SCREEN_WIDTH, Spec::SCREEN_HEIGHT), Spec::TITLE, sf::Style::Titlebar | sf::Style::Close, settings);
    m_window.setFramerateLimit(200);

    m_balls.reserve(Spec::BALLS_TOTAL);
}

void Game::initializeBalls()
{
    if (!m_balls.empty())
    {
        m_balls.clear();
    }

    std::uniform_int_distribution distrib{0, 1};
    std::uniform_real_distribution<float> rdistrib{Spec::CUE_POS_Y_MIN, Spec::CUE_POS_Y_MAX};

    m_balls.emplace_back(sf::Vector2f{Spec::CUE_POS_X, rdistrib(*m_rng)}, Ball::Cue, nullptr, m_bufferCollision);

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
            if (player2Left == 0 || (player1Left > 0 && distrib(*m_rng)))
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

        m_balls.emplace_back(pos + sf::Vector2f{0.0f, 2.0f * Spec::BALL_RADIUS * currIndex}, type, 
                             m_isMysteryEnabled || type == Ball::Eightball ? &m_textureEightball : nullptr, m_bufferCollision);

        currIndex++;
        if (currIndex == currColumn)
        {
            currColumn--;
            currIndex = 0;
            pos += sf::Vector2f{Spec::BALL_SPACING, Spec::BALL_RADIUS};
        }
    }
}

void Game::run()
{
    while (m_window.isOpen())
    {
        gameLoop();
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
        return;
    case sf::Event::MouseButtonPressed:
        handleMouseButtonPressed(event, sf::Vector2f{static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)});
        return;
    case sf::Event::MouseButtonReleased:
        handleMouseButtonReleased(event, sf::Vector2f{static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)});
        return;
    case sf::Event::KeyPressed:
        handleKeyPressed(event);
        return;
    default:
        return;
    }
}

void Game::handleMouseButtonPressed(const sf::Event& event, const sf::Vector2f& mousePos)
{
    if (m_state == PlayerToMove
        && event.mouseButton.button == sf::Mouse::Left 
        && !m_balls[Spec::CUE_INDEX].isPotted()
        && m_balls[Spec::CUE_INDEX].isWithinBall(mousePos))
    {
        m_state = PlayerAiming;
    }
    else if (m_state == InMenu
            && event.mouseButton.button == sf::Mouse::Left
            && m_menu.isWithinButton1(mousePos))
    {
        m_botPlaysAs = 0;
        newGame();
    }
    else if (m_state == InMenu
            && event.mouseButton.button == sf::Mouse::Left
            && m_menu.isWithinButton2(mousePos))
    {
        std::uniform_int_distribution<> distrib{1, 2};
        m_botPlaysAs = distrib(*m_rng);
        newGame();
    }
    else if (m_state == InMenu
            && event.mouseButton.button == sf::Mouse::Left
            && m_menu.isWithinButtonMystery(mousePos))
    {
        m_isMysteryEnabled = !m_isMysteryEnabled;
        m_menu.setMystery(m_isMysteryEnabled);
        m_soundCue.setPosition(Spec::TABLE_LEFT + 0.5f * Spec::TABLE_WIDTH, 0.0f, Spec::TABLE_BOTTOM);
        m_soundCue.play();
    }
}

void Game::handleMouseButtonReleased(const sf::Event& event, const sf::Vector2f& mousePos)
{
    if (m_state == PlayerAiming && event.mouseButton.button == sf::Mouse::Left)
    {
        if (!m_balls[Spec::CUE_INDEX].isWithinBall(mousePos))
        {
            launchCueBall(mousePos);
        }
        else
        {
            m_state = PlayerToMove;
        }
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
    else if (event.key.code == sf::Keyboard::Escape && event.key.shift)
    {
        m_menu.setMessage("You abandoned the game.", sf::Color::Black);
        m_state = InMenu;
    }
}

void Game::update()
{
    switch (m_state)
    {
    case PlayerMotion:
        for (Ball& ball : m_balls)
        {
            ball.update(m_deltaTime);
            if (!ball.isPotted())
            {
                if (m_pockets.checkBallPotted(ball))
                {
                    if (ball.getType() == Ball::Player1)
                    {
                        m_wasP1BallPotted = true;
                    }
                    else if (ball.getType() == Ball::Player2)
                    {
                        m_wasP2BallPotted = true;
                    }

                    if(m_ui.update(ball))
                    {
                        m_menu.setMessage(sf::String{getActivePlayerName()} + " won!\n(by potting)",
                                            m_activePlayer == 1 ? Spec::PLAYER1_COLOR : Spec::PLAYER2_COLOR);
                        m_state = InMenu;
                        return;
                    }
                }
                else
                {
                    ball.checkCollisionWithBorder();
                }
            }
        }
        for (size_t i = 0; i < Spec::BALLS_TOTAL; i++)
        {
            for (size_t j = i + 1; j < Spec::BALLS_TOTAL; j++)
            {
                m_balls[i].checkCollisionWithBall(m_balls[j]);
            }
        }
        if (checkEquilibrium())
        {
            nextTurn();
        }
        break;
    case PlayerAiming:
        m_trajectory.update(m_balls[Spec::CUE_INDEX].getPosition(), static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window)));
        break;
    case BotAiming:
        m_botAimingProgress += m_deltaTime;
        if (m_botAimingProgress >= botAimingTime)
        {
            m_botAimingProgress = 0.0f;
            launchCueBall(m_botMousePos);
            m_state = PlayerMotion;
        }
        else
        {
            m_botMousePos += m_botMouseShift * m_deltaTime / botAimingTime;
            m_trajectory.update(m_balls[Spec::CUE_INDEX].getPosition(), m_botMousePos);
        }
        break;
    case PlayerToMove:
        if (m_activePlayer == m_botPlaysAs)
        {
            std::uniform_real_distribution<float> distribPower{0.65f, 1.2f};
            std::uniform_real_distribution<float> distribSpread{-7.5f, 7.5f};

            m_botMousePos = m_balls[Spec::CUE_INDEX].getPosition();
            m_botMouseShift = m_balls[Spec::CUE_INDEX].getPosition() - botFindClosestBall();
            m_botMouseShift *= distribPower(*m_rng) * (Spec::MAX_CHARGE_SPEED / Spec::CHARGE_VELOCITY_COEF) / Spec::hypot(m_botMouseShift);
            m_botMouseShift.x += distribSpread(*m_rng);
            m_botMouseShift.y += distribSpread(*m_rng);
            m_botAimingProgress = 0.0f;
            m_trajectory.update(m_balls[Spec::CUE_INDEX].getPosition(), m_botMousePos);
            m_state = BotAiming;
        }
        break;
    default:
        break;
    }

    m_ui.setString(m_activePlayer, std::string{getActivePlayerName()} + '\n' + getStateAsString());
    m_fpsCounter.update(m_deltaTime);
}

void Game::nextTurn()
{
    if (m_balls[Spec::CUE_INDEX].isPotted() && m_balls[Spec::EIGHTBALL_INDEX].isPotted())
    {
        m_state = InMenu;
        switchPlayer();
        m_menu.setMessage(sf::String{getActivePlayerName()} + "won!\n(by fatal foul)", 
                          m_activePlayer == 1 ? Spec::PLAYER1_COLOR : Spec::PLAYER2_COLOR);
    } 
    else if (m_balls[Spec::CUE_INDEX].isPotted())
    {
        replaceBall(m_balls[Spec::CUE_INDEX]);
        m_soundCue.setPosition(m_balls[Spec::CUE_INDEX].getPosition().x, 0.0f, m_balls[Spec::CUE_INDEX].getPosition().y);
        m_soundCue.play();
        switchPlayer();
    }
    else if (m_balls[Spec::EIGHTBALL_INDEX].isPotted())
    {
        replaceBall(m_balls[Spec::EIGHTBALL_INDEX]);
        m_soundCue.setPosition(m_balls[Spec::EIGHTBALL_INDEX].getPosition().x, 0.0f, m_balls[Spec::EIGHTBALL_INDEX].getPosition().y);
        m_soundCue.play();
        switchPlayer();
    }
    else if (m_activePlayer == 1 && m_wasP1BallPotted && !m_wasP2BallPotted)
    {
        // extra turn
    }
    else if (m_activePlayer == 2 && m_wasP2BallPotted && !m_wasP1BallPotted)
    {
        // extra turn
    }
    else
    {
        switchPlayer();
    }

    m_state = PlayerToMove;
}

bool Game::checkEquilibrium()
{
    for (const Ball& ball : m_balls)
    {
        if (ball.isAnimationPlaying() || (!ball.isPotted() && ball.getVelocity() != sf::Vector2f{0.0f, 0.0f}))
        {
            return false;
        }
    }

    return true;
}

void Game::draw()
{
    m_window.clear(Spec::BG_COLOR);

    if (m_state == InMenu)
    {
        m_menu.draw(m_window);
    }
    else
    {
        m_table.draw(m_window);
        m_pockets.draw(m_window);
        for (const Ball& ball : m_balls)
        {
            ball.draw(m_window);
        }
        if (m_state == PlayerAiming || m_state == BotAiming)
        {
            m_trajectory.draw(m_window);
        }
        m_ui.draw(m_window);
    }

    if (m_isFpsShown)
    {
        m_fpsCounter.draw(m_window);
    }
    
    m_window.display();
}

const char* Game::getStateAsString()
{
    switch (m_state)
    {
    case PlayerToMove:
        return "to move";
    case PlayerAiming:
    case BotAiming:
        return "aiming";
    case PlayerMotion:
        return "";
    default:
        return "N/A";
    }
}

const char* Game::getActivePlayerName()
{
    switch (m_activePlayer)
    {
    case 1:
        if (m_botPlaysAs == 1)
        {
            return "Bot";
        }
        else if (m_botPlaysAs == 2)
        {
            return "You";
        }
        else
        {
            return "Player 1";
        }
    case 2:
        if (m_botPlaysAs == 2)
        {
            return "Bot";
        }
        else if (m_botPlaysAs == 1)
        {
            return "You";
        }
        else
        {
            return "Player 2";
        }
    default:
        return "???";
    }
}

void Game::replaceBall(Ball& ball)
{
    std::uniform_int_distribution distrib(0, 15);
    
    int index;
    do {
        index = distrib(*m_rng);
    } while(!canPlaceBall(Spec::REPLACEMENT_POSITIONS[index]));


    ball.replace(Spec::REPLACEMENT_POSITIONS[index]);
}

bool Game::canPlaceBall(const sf::Vector2f& pos)
{
    for (const Ball& ball : m_balls)
    {
        float distance = Spec::hypot(ball.getPosition() - pos);
        if (distance <= 2 * Spec::BALL_RADIUS)
        {
            return false;
        }
    }

    return true;
}

void Game::newGame()
{
    m_ui.reset();
    initializeBalls();
    m_menu.setMystery(m_isMysteryEnabled = false);
    m_state = PlayerToMove;
    m_activePlayer = 1;
    m_soundCue.setPosition(0.5f * static_cast<float>(Spec::SCREEN_WIDTH), 0.0f, 0.5f * static_cast<float>(Spec::SCREEN_HEIGHT));
    m_soundCue.play();
}

void Game::switchPlayer()
{
    switch (m_activePlayer)
    {
    case 1:
        m_activePlayer = 2;
        return;
    case 2:
        m_activePlayer = 1;
        return;
    default:
        m_activePlayer = 0;
        return;
    }    
}

sf::Vector2f Game::botFindClosestBall()
{
    sf::Vector2f closest = {10'000.f, 10'000.0f};
    for (const Ball& ball : m_balls)
    {
        if (((m_botPlaysAs == 1 && ball.getType() == Ball::Player1) || (m_botPlaysAs == 2 && ball.getType() == Ball::Player2)) 
            && !ball.isPotted() 
            && Spec::hypot(ball.getPosition() - m_balls[Spec::CUE_INDEX].getPosition()) < Spec::hypot(closest - m_balls[Spec::CUE_INDEX].getPosition()))
        {
            closest = ball.getPosition();
        }
    }
    if (closest == sf::Vector2f{10'000.f, 10'000.0f})
    {
        closest = m_balls[Spec::EIGHTBALL_INDEX].getPosition();
    }
    return closest;
}

void Game::launchCueBall(const sf::Vector2f& mousePos)
{
    sf::Vector2f chargeVelocity = Spec::CHARGE_VELOCITY_COEF * (m_balls[Spec::CUE_INDEX].getPosition() - mousePos);
    if (Spec::hypot(chargeVelocity) > Spec::MAX_CHARGE_SPEED)
    {
        chargeVelocity /= Spec::hypot(chargeVelocity); 
        chargeVelocity *= Spec::MAX_CHARGE_SPEED;
    }
    m_balls[Spec::CUE_INDEX].setVelocity(chargeVelocity);
    m_soundCue.setPosition(m_balls[Spec::CUE_INDEX].getPosition().x, 0.0f, m_balls[Spec::CUE_INDEX].getPosition().y);
    m_soundCue.play();
    m_state = PlayerMotion;
    m_wasP1BallPotted = false;
    m_wasP2BallPotted = false;
}
