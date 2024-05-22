#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

int main()
{
    // Declare constants

    sf::ContextSettings settings;
    sf::Event event;
    sf::RenderWindow window;
    sf::CircleShape circle(150);
    sf::Mouse mouse;
    sf::Color color;
    sf::Text text;
    sf::Font font;

    sf::Sprite backgroundSprite;
    sf::Texture background;
    sf::Texture button;

     sf::SoundBuffer buffer;
     sf::Sound clickSound;

    settings.antialiasingLevel = 8;

    // Window
    window.create(sf::VideoMode(500, 500), "Click Game", sf::Style::Titlebar | sf::Style::Close, settings);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    // Circle position
    circle.setPosition(100, 100);
    sf::Vector2f circlePosition = circle.getPosition() + sf::Vector2f(circle.getRadius(), circle.getRadius());

    // add Text
    if (!font.loadFromFile("Montserrat-Medium.ttf"))
    {
        std::cout << "Font not set" << std::endl;
    }

    // add texture
    if (!background.loadFromFile("Background.jpg"))
    {
        std::cout << "Texture not set" << std::endl;
    }


    if (!button.loadFromFile("Button.png"))
    {
        std::cout << "Texture not set" << std::endl;
    }

    // add sound
    if (!buffer.loadFromFile("Click.wav"))
    {
        std::cout << "Sound not set" << std::endl;
    }

    text.setFont(font);
    text.setString("Score: 0");
    text.setFillColor(color.Black);
    text.setCharacterSize(40);
    //text.setStyle(text.Bold);
    text.setPosition(162, 20);

    // score initialize
    int scoreint = 0;

    // set texture
    button.setSmooth(true);
    backgroundSprite.setTexture(background);
    circle.setTexture(&button);

    // set sound
    clickSound.setBuffer(buffer);

    bool isPressed = false;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

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
                // text.setString("Hmm");
            }


        }


        window.clear(sf::Color(238, 123, 104));

        // write code here
       // window.draw(button);
        window.draw(backgroundSprite);
        window.draw(circle);
        window.draw(text);
        window.display();
    }

    return 0;
}