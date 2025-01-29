#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <algorithm>
#include <cmath>
#include "Ball.hpp"
#include "Trajectory.hpp"
#include "Specs.hpp"

int main()
{
    // INIT OBJECTS
    // window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    sf::RenderWindow window(sf::VideoMode(Specs::SCREEN_WIDTH, Specs::SCREEN_HEIGHT), "P88l", sf::Style::Titlebar | sf::Style::Close, settings);

    // table
    sf::RectangleShape table(sf::Vector2f(Specs::TABLE_WIDTH, Specs::TABLE_HEIGHT));
    table.setPosition(Specs::TABLE_LEFT, Specs::TABLE_TOP);
    table.setFillColor(sf::Color(34, 139, 34));

    // balls
    int cueIndex = 0;
    std::vector<Ball> balls;
    balls.emplace_back(Specs::BALL_RADIUS, sf::Color::White, sf::Vector2f(600.0f, 300.0f), sf::Vector2f(0.0f, 0.0f), Ball::BallType::Cue);
    balls.emplace_back(Specs::BALL_RADIUS, sf::Color::Red, sf::Vector2f(600.0f, 500.0f), sf::Vector2f(0.0f, 0.0f), Ball::BallType::Default);
    for (int i = 0, n = 5; i < n; ++i)
    {
        balls.emplace_back(Specs::BALL_RADIUS, sf::Color::Yellow, sf::Vector2f((i + 1) * Specs::TABLE_WIDTH / n, 400.0f));
    }

    // sounds
    sf::SoundBuffer bufferCollision;
    if (!bufferCollision.loadFromFile("ball_collision.wav"))
        return EXIT_FAILURE;
    sf::Sound soundCollsion;
    soundCollsion.setBuffer(bufferCollision);

    // trajectory line
    Trajectory trajectory;

    // clock
    float deltaTime = 0.0f;
    sf::Clock clock;

    // states
    bool isCharging = false;
    sf::Vector2f chargeStart;
    bool isEquilibrium = false;

    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();

        // EVENTS
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                if (isEquilibrium && event.mouseButton.button == sf::Mouse::Left && balls[cueIndex].isWithinBall(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
                {
                    chargeStart = balls[cueIndex].getPosition();
                    isCharging = true;
                    window.setTitle("P88l - charging");
                }
                break;
            case sf::Event::MouseButtonReleased:
                if (isCharging && event.mouseButton.button == sf::Mouse::Left)
                {
                    if (!balls[cueIndex].isWithinBall(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
                    {
                        sf::Vector2f chargeVelocity = chargeStart - sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y);
                        chargeVelocity *= 3.5f;
                        if (hypotf(chargeVelocity.x, chargeVelocity.y) > Specs::MAX_CHARGE_VELOCITY)
                        {
                            chargeVelocity *= Specs::MAX_CHARGE_VELOCITY / hypotf(chargeVelocity.x, chargeVelocity.y);
                        }
                        balls[cueIndex].setVelocity(chargeVelocity);
                        soundCollsion.play();
                    }

                    isCharging = false;
                    window.setTitle("P88l");
                }
                break;
            default:
                break;
            }
        }

        // UPDATE
        if (!isEquilibrium)
        {
            for (Ball &ball : balls)
            {
                // move
                ball.update(deltaTime);
                // border collision
                if (ball.checkCollisionWithBorder())
                    soundCollsion.play();
            }

            // ball collision
            for (int i = 0, n = balls.size(); i < n; ++i)
                for (int j = i + 1; j < n; ++j)
                    if (balls[i].checkCollisionWithBall(balls[j]))
                        soundCollsion.play();
        }
        // check if all balls stationary
        isEquilibrium = std::all_of(balls.begin(), balls.end(), [](const Ball &ball)
                                    { return ball.getVelocity() == sf::Vector2f(0.0f, 0.0f); });

        // DISPLAY
        window.clear(sf::Color(200, 200, 200));
        // table
        window.draw(table);
        // balls
        for (Ball &ball : balls)
        {
            ball.draw(window);
        }
        // trajectory preview if needed
        if (isCharging)
        {
            trajectory.update(chargeStart, static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
            trajectory.draw(window);
        }

        window.display();
    }

    return 0;
}