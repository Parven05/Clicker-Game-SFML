#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

int main()
{   
    // Settings
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    // Window
    sf::RenderWindow window;
    window.create(sf::VideoMode(500, 500), "Click Game", sf::Style::Titlebar | sf::Style::Close, settings);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    // Circle shape
    sf::CircleShape circle;
    sf::Color color;
    circle.setRadius(150);
    circle.setPosition(100, 100);
    sf::Vector2f circlePosition = circle.getPosition() + sf::Vector2f(circle.getRadius(), circle.getRadius());
    bool isPressed = false;

    // Font & Text
    sf::Font font;
    sf::Text text;
    if (!font.loadFromFile("Montserrat-Medium.ttf")) return -1;
    text.setFont(font);
    text.setString("Score: 0");
    text.setFillColor(color.Black);
    text.setCharacterSize(40);
    text.setPosition(162, 20);
    int scoreint = 0;

    // Texture & Sprite
    sf::Sprite backgroundSprite;
    sf::Texture background;
    sf::Texture button;
    if (!background.loadFromFile("Background.jpg")) return -1;
    if (!button.loadFromFile("Button.png")) return -1;
    background.setSmooth(true);
    button.setSmooth(true);
    backgroundSprite.setTexture(background);
    circle.setTexture(&button);

    // Sound
    sf::SoundBuffer buffer;
    sf::Sound clickSound;
    if (!buffer.loadFromFile("Click.wav")) return -1;
    clickSound.setBuffer(buffer);    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            sf::Mouse mouse;
            if (mouse.isButtonPressed(mouse.Left) && isPressed == false)
            {
                // Mouse position
                sf::Vector2i mousePositionint = mouse.getPosition(window);
                sf::Vector2f mousePosition = static_cast<sf::Vector2f>(mousePositionint);

                // Dot Product
                sf::Vector2f toMouseVector = mousePosition - circlePosition; // From circle to mouse vector
                float dotVector = toMouseVector.x * toMouseVector.x + toMouseVector.y * toMouseVector.y;

                if (dotVector <= circle.getRadius() * circle.getRadius())
                {
                    circle.setFillColor(color.Red);
                    clickSound.play();
                    isPressed = true;
                    scoreint++;
                    text.setString("Score: " + std::to_string(scoreint));
                }
            }
            else
            {
                circle.setFillColor(color.Green);
                isPressed = false;               
            }

        }

        window.clear(sf::Color(238, 123, 104));

        window.draw(backgroundSprite);
        window.draw(circle);
        window.draw(text);
        window.display();
    }
    return 0;
}