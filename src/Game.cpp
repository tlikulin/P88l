#include "Game.hpp"
#include "Spec.hpp"
#include <cmath>
#include <numbers>

namespace
{
    // fixed incdices
    constexpr size_t CUE_INDEX                  = 0;
    constexpr size_t EIGHTBALL_INDEX            = 11;
    // inital ball postions
    const sf::Vector2f BALL_SPACING             {std::numbers::sqrt3_v<float> * Spec::BALL_RADIUS, Spec::BALL_RADIUS};
    const sf::Vector2f BALL_TOPLEFT_POS         {Spec::TABLE_LEFT + 0.25f * Spec::TABLE_WIDTH, Spec::TABLE_TOP + 0.5f * Spec::TABLE_HEIGHT - 4.0f * Spec::BALL_RADIUS};
    constexpr float CUE_POS_X                   = Spec::TABLE_LEFT + 0.75f * Spec::TABLE_WIDTH;
    constexpr float CUE_POS_Y_MIN               = Spec::TABLE_TOP + 0.3f * Spec::TABLE_HEIGHT;
    constexpr float CUE_POS_Y_MAX               = Spec::TABLE_TOP + 0.7f * Spec::TABLE_HEIGHT;
    // replacement
    constexpr size_t NUM_REPLACEMENT_POSITIONS  = 16;
    const std::array<sf::Vector2f, NUM_REPLACEMENT_POSITIONS> REPLACEMENT_POSITIONS{{
        {Spec::TABLE_LEFT + 0.2f * Spec::TABLE_WIDTH, Spec::TABLE_TOP + 0.2f * Spec::TABLE_HEIGHT},
        {Spec::TABLE_LEFT + 0.4f * Spec::TABLE_WIDTH, Spec::TABLE_TOP + 0.2f * Spec::TABLE_HEIGHT},
        {Spec::TABLE_LEFT + 0.6f * Spec::TABLE_WIDTH, Spec::TABLE_TOP + 0.2f * Spec::TABLE_HEIGHT},
        {Spec::TABLE_LEFT + 0.8f * Spec::TABLE_WIDTH, Spec::TABLE_TOP + 0.2f * Spec::TABLE_HEIGHT},
        {Spec::TABLE_LEFT + 0.2f * Spec::TABLE_WIDTH, Spec::TABLE_TOP + 0.4f * Spec::TABLE_HEIGHT},
        {Spec::TABLE_LEFT + 0.4f * Spec::TABLE_WIDTH, Spec::TABLE_TOP + 0.4f * Spec::TABLE_HEIGHT},
        {Spec::TABLE_LEFT + 0.6f * Spec::TABLE_WIDTH, Spec::TABLE_TOP + 0.4f * Spec::TABLE_HEIGHT},
        {Spec::TABLE_LEFT + 0.8f * Spec::TABLE_WIDTH, Spec::TABLE_TOP + 0.4f * Spec::TABLE_HEIGHT},
        {Spec::TABLE_LEFT + 0.2f * Spec::TABLE_WIDTH, Spec::TABLE_TOP + 0.6f * Spec::TABLE_HEIGHT},
        {Spec::TABLE_LEFT + 0.4f * Spec::TABLE_WIDTH, Spec::TABLE_TOP + 0.6f * Spec::TABLE_HEIGHT},
        {Spec::TABLE_LEFT + 0.6f * Spec::TABLE_WIDTH, Spec::TABLE_TOP + 0.6f * Spec::TABLE_HEIGHT},
        {Spec::TABLE_LEFT + 0.8f * Spec::TABLE_WIDTH, Spec::TABLE_TOP + 0.6f * Spec::TABLE_HEIGHT},
        {Spec::TABLE_LEFT + 0.2f * Spec::TABLE_WIDTH, Spec::TABLE_TOP + 0.8f * Spec::TABLE_HEIGHT},
        {Spec::TABLE_LEFT + 0.4f * Spec::TABLE_WIDTH, Spec::TABLE_TOP + 0.8f * Spec::TABLE_HEIGHT},
        {Spec::TABLE_LEFT + 0.6f * Spec::TABLE_WIDTH, Spec::TABLE_TOP + 0.8f * Spec::TABLE_HEIGHT}, 
        {Spec::TABLE_LEFT + 0.8f * Spec::TABLE_WIDTH, Spec::TABLE_TOP + 0.8f * Spec::TABLE_HEIGHT}
    }};
    // misc
    const sf::Color BG_COLOR                    {0xb8b8b8ff};
    constexpr float botAimingTime               = 1.5f;
}

Game::Game(const char* path) :
    m_trajectory{Trajectory::Normal},
    m_path{std::filesystem::canonical(std::filesystem::path{path}).parent_path().parent_path()},
    m_state{InMenu}
{
    // loading from files
    m_bufferCue.loadFromFile(m_path / Spec::PATH_TO_CUE_SOUND);
    m_bufferCollision.loadFromFile(m_path / Spec::PATH_TO_COLLISION_SOUND);
    m_bufferPotting.loadFromFile(m_path / Spec::PATH_TO_POTTING_SOUND);
    m_font.loadFromFile(m_path / Spec::PATH_TO_FONT);
    m_textureEightball.loadFromFile(m_path / Spec::PATH_TO_EIGHTBALL_TEXTURE);
    m_textureEightball.setSmooth(true);
    m_menuInfo.loadFromFile(m_path / Spec::PATH_TO_MENU_INFO);
    // setting font (and texture)
    m_fpsCounter.setFont(m_font);
    m_ui.setFont(m_font);
    m_menu.setFontAndTexture(m_font, m_menuInfo);
    // setting sounds
    sf::Listener::setPosition(Spec::TABLE_LEFT + 0.5f * Spec::TABLE_WIDTH, 0.0f, Spec::TABLE_BOTTOM);
    sf::Listener::setGlobalVolume(100.0f);
    m_soundCue.setBuffer(m_bufferCue);
    m_soundCue.setAttenuation(0.0f);
    m_pockets.setBuffer(m_bufferPotting);
    // creating window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    m_window.create(sf::VideoMode(Spec::SCREEN_WIDTH, Spec::SCREEN_HEIGHT), Spec::TITLE, sf::Style::Titlebar | sf::Style::Close, settings);
    m_window.setFramerateLimit(200);
    {
        sf::Image icon;
        icon.loadFromFile(m_path / Spec::PATH_TO_EIGHTBALL_TEXTURE);
        m_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
    // reserve space for all balls
    m_balls.reserve(Spec::BALLS_TOTAL);
}

void Game::run()
{
    while (m_window.isOpen())
    {
        gameLoop();
    }
}

// Initializes all balls; random order for player balls
void Game::initializeBalls()
{
    if (!m_balls.empty())
    {
        m_balls.clear();
    }

    std::uniform_int_distribution distrib{0, 1};
    std::uniform_real_distribution<float> rdistrib{CUE_POS_Y_MIN, CUE_POS_Y_MAX};
    // cue ball
    m_balls.emplace_back(sf::Vector2f{CUE_POS_X, rdistrib(*m_rng)}, Ball::Cue, nullptr, m_bufferCollision);

    size_t player1Left = Spec::BALLS_PER_PLAYER;
    size_t player2Left = Spec::BALLS_PER_PLAYER;
    size_t currColumn = 5;
    size_t currIndex = 0;
    sf::Vector2f pos = BALL_TOPLEFT_POS;
    Ball::BallType type;
    // player balls and eight-ball, in a triangle, going from top to bottom, then from left to right 
    for (size_t i = 1; i < Spec::BALLS_TOTAL; i++)
    {
        if (i == EIGHTBALL_INDEX)
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
            pos += BALL_SPACING;
        }
    }
}


// DeltaTime is measured, events are handled, everything that needed is updated and drawn.
void Game::gameLoop()
{
    m_deltaTime = m_clock.restart().asSeconds();

    sf::Event event;
    while (m_window.pollEvent(event))
    {
        handleEvent(event);
    }
    
    update();
    draw();
}

// Updated objects depend on the game state.
void Game::update()
{
    switch (m_state)
    {
    // if the balls are moving, update their velocities and positions, check for collisions and potting
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
                        m_menu.setMessage(sf::String{getActivePlayerName()} + " won by potting!",
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
    // while aiming, only the trajectory is updated
    case PlayerAiming:
        m_trajectory.update(m_balls[CUE_INDEX].getPosition(), static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window)));
        break;
    // simulate gradual change in trajectory while the bot is aiming
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
            m_trajectory.update(m_balls[CUE_INDEX].getPosition(), m_botMousePos);
        }
        break;
    // if the active player is bot, set the final aiming position at the closest ball of their color (or eight-ball when ready) and add some random shift and power; nothing otherwise
    case PlayerToMove:
        if (m_activePlayer == m_botPlaysAs)
        {
            std::uniform_real_distribution<float> distribPower{0.65f, 1.2f};
            std::uniform_real_distribution<float> distribSpread{-7.5f, 7.5f};

            m_botMousePos = m_balls[CUE_INDEX].getPosition();
            m_botMouseShift = m_balls[CUE_INDEX].getPosition() - botFindClosestBall();
            m_botMouseShift /= Spec::hypot(m_botMouseShift); // now unit
            m_botMouseShift *= distribPower(*m_rng) * (Spec::MAX_CHARGE_SPEED / Spec::CHARGE_VELOCITY_COEF); // random power
            m_botMouseShift.x += distribSpread(*m_rng); // random spread
            m_botMouseShift.y += distribSpread(*m_rng);
            m_botAimingProgress = 0.0f;
            m_trajectory.update(m_balls[CUE_INDEX].getPosition(), m_botMousePos);
            m_state = BotAiming;
        }
        break;
    default:
        break;
    }
    // also update the displayed state and fps
    m_ui.setString(m_activePlayer, std::string{getActivePlayerName()} + '\n' + getStateAsString());
    m_fpsCounter.update(m_deltaTime);
}

// Draws different objects depending on the game state
void Game::draw()
{
    m_window.clear(BG_COLOR);
    // while in menu, only menu is displayed
    if (m_state == InMenu)
    {
        m_menu.draw(m_window);
    }
    // otherwise draw table, pockets, balls, ui, and trajectory if aiming
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
    // draw fps if it's turned on
    if (m_isFpsShown)
    {
        m_fpsCounter.draw(m_window);
    }
    // flush
    m_window.display();
}

// handle events of closing, pressing a mouse button or a key, releasing a mouse button
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
    if (event.mouseButton.button != sf::Mouse::Left)
    {
        return;
    }
    // if in menu, check if any menu button is hit
    if (m_state == InMenu)
    {
        // 2 players
        if (m_menu.isWithinButtonMode1(mousePos))
        {
            m_botPlaysAs = 0;
            newGame();
        }
        // against bot
        else if (m_menu.isWithinButtonMode2(mousePos))
        {
            std::uniform_int_distribution<> distrib{1, 2};
            m_botPlaysAs = distrib(*m_rng);
            newGame();
        }
        // togle mystery mode
        else if (m_menu.isWithinButtonMystery(mousePos))
        {
            m_isMysteryEnabled = !m_isMysteryEnabled;
            m_menu.setMystery(m_isMysteryEnabled);
            m_soundCue.setPosition(Spec::TABLE_LEFT + 0.5f * Spec::TABLE_WIDTH, 0.0f, Spec::TABLE_BOTTOM);
            m_soundCue.play();
        }
    }
    // start aiming if pressed inside cue ball
    else if (m_state == PlayerToMove
        && !m_balls[CUE_INDEX].isPotted()
        && m_balls[CUE_INDEX].isWithinBall(mousePos))
    {
        m_state = PlayerAiming;
    }
}

void Game::handleMouseButtonReleased(const sf::Event& event, const sf::Vector2f& mousePos)
{
    // if was already aiming
    if (m_state == PlayerAiming && event.mouseButton.button == sf::Mouse::Left)
    {
        // launch only if outside the cue ball
        if (!m_balls[CUE_INDEX].isWithinBall(mousePos))
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
    // switch the trajectory mode
    if (event.key.code == sf::Keyboard::P)
    {
        m_trajectory.cycleMode();
    }
    // toggle fps
    else if (event.key.code == sf::Keyboard::Tilde)
    {
        m_isFpsShown = !m_isFpsShown;
    }
    // abandon game
    else if (event.key.code == sf::Keyboard::Escape && event.key.shift)
    {
        m_menu.setMessage("You abandoned the game.", sf::Color::Black);
        m_state = InMenu;
    }
}

// Gets ready to start new game
void Game::newGame()
{
    m_ui.reset();
    initializeBalls();
    m_menu.setMystery(m_isMysteryEnabled = false);
    m_state = PlayerToMove;
    m_activePlayer = 1;
    m_soundCue.setPosition(Spec::TABLE_LEFT + 0.5f * Spec::TABLE_WIDTH, 0.0f, Spec::TABLE_BOTTOM);
    m_soundCue.play();
}

// once in equilibrium, checks what should be done before the next turn starts
void Game::nextTurn()
{
    // if both cue ball and eight-ball are potted, a game over
    if (m_balls[CUE_INDEX].isPotted() && m_balls[EIGHTBALL_INDEX].isPotted())
    {
        switchPlayer(); // bc the other one wins
        m_menu.setMessage(sf::String{getActivePlayerName()} + "won by fatal foul!", 
                        m_activePlayer == 1 ? Spec::PLAYER1_COLOR : Spec::PLAYER2_COLOR);
        m_state = InMenu;
    }
    // if cue ball is potted, replace it
    else if (m_balls[CUE_INDEX].isPotted())
    {
        replaceBall(m_balls[CUE_INDEX]);
        m_soundCue.setPosition(m_balls[CUE_INDEX].getPosition().x, 0.0f, m_balls[CUE_INDEX].getPosition().y);
        m_soundCue.play();
        switchPlayer();
    }
    // if eight-ball is potted, replace it
    else if (m_balls[EIGHTBALL_INDEX].isPotted())
    {
        replaceBall(m_balls[EIGHTBALL_INDEX]);
        m_soundCue.setPosition(m_balls[EIGHTBALL_INDEX].getPosition().x, 0.0f, m_balls[EIGHTBALL_INDEX].getPosition().y);
        m_soundCue.play();
        switchPlayer();
    }
    // the first player gets an extra turn
    else if (m_activePlayer == 1 && m_wasP1BallPotted && !m_wasP2BallPotted)
    {
        // extra turn
    }
    // the second player gets an extra turn
    else if (m_activePlayer == 2 && m_wasP2BallPotted && !m_wasP1BallPotted)
    {
        // extra turn
    }
    // no extra turn
    else
    {
        switchPlayer();
    }

    m_state = PlayerToMove;
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

// launch the cue ball and set corresponding states
void Game::launchCueBall(const sf::Vector2f& mousePos)
{
    sf::Vector2f chargeVelocity = Spec::CHARGE_VELOCITY_COEF * (m_balls[CUE_INDEX].getPosition() - mousePos);
    if (Spec::hypot(chargeVelocity) > Spec::MAX_CHARGE_SPEED)
    {
        chargeVelocity /= Spec::hypot(chargeVelocity); 
        chargeVelocity *= Spec::MAX_CHARGE_SPEED;
    }
    m_balls[CUE_INDEX].setVelocity(chargeVelocity);
    m_soundCue.setPosition(m_balls[CUE_INDEX].getPosition().x, 0.0f, m_balls[CUE_INDEX].getPosition().y);
    m_soundCue.play();
    m_state = PlayerMotion;
    m_wasP1BallPotted = false;
    m_wasP2BallPotted = false;
}

// replace the given ball (usually, cue or eight-ball) at a random position from the list; keep trying a new position until valid (garanteed)
void Game::replaceBall(Ball& ball)
{
    std::uniform_int_distribution distrib(0, static_cast<int>(NUM_REPLACEMENT_POSITIONS - 1));
    
    int index;
    do {
        index = distrib(*m_rng);
    } while(!canPlaceBall(REPLACEMENT_POSITIONS[index]));

    ball.replace(REPLACEMENT_POSITIONS[index]);
}

// checks if all balls are stationary/finished playing potting animation
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

// checks if the new position is outside of all balls
bool Game::canPlaceBall(const sf::Vector2f& pos)
{
    for (const Ball& ball : m_balls)
    {
        const float distance = Spec::hypot(ball.getPosition() - pos);
        if (distance <= 2 * Spec::BALL_RADIUS)
        {
            return false;
        }
    }

    return true;
}

// Player 1, PLayer 2, You, Bot, or ??? if invalid; based on active player and presence of bot
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

// to move, aiming, <empty>, or N/A if invalid
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

// finds the closest not potted ball of the bot's color to the cue ball; if there is not such one, then the ball is eight-ball 
sf::Vector2f Game::botFindClosestBall()
{
    sf::Vector2f closest {10'000.f, 10'000.0f};
    for (const Ball& ball : m_balls)
    {
        if (((m_botPlaysAs == 1 && ball.getType() == Ball::Player1) || (m_botPlaysAs == 2 && ball.getType() == Ball::Player2)) 
            && !ball.isPotted() 
            && Spec::hypot(ball.getPosition() - m_balls[CUE_INDEX].getPosition()) < Spec::hypot(closest - m_balls[CUE_INDEX].getPosition()))
        {
            closest = ball.getPosition();
        }
    }
    if (closest == sf::Vector2f{10'000.f, 10'000.0f})
    {
        closest = m_balls[EIGHTBALL_INDEX].getPosition();
    }
    return closest;
}
