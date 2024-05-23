// Library
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

// Class
#include "Button.cpp"

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

    // Font & Text
    sf::Text text;
    sf::Font font;
    sf::Color color;
    if (!font.loadFromFile("Montserrat-Medium.ttf")) throw std::runtime_error("Failed to load font");
    text.setFont(font);
    text.setString("Score: ");
    text.setFillColor(color);
    text.setCharacterSize(40);
    text.setPosition(160,25);

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

    // Sound
    sf::SoundBuffer buffer;
    sf::Sound clickSound;
    if (!buffer.loadFromFile("Click.wav")) return -1;
    clickSound.setBuffer(buffer);    

    Button buttonClick(150, sf::Vector2f(100, 100), button);

    bool isPressed = false;

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
                sf::Vector2f toMouseVector = mousePosition - buttonClick.GetPosition(); // From circle to mouse vector
                float dotVector = toMouseVector.x * toMouseVector.x + toMouseVector.y * toMouseVector.y;

                if (dotVector <= buttonClick.GetRadius() * buttonClick.GetRadius())
                {
                    buttonClick.SetColor(color.Red);
                    clickSound.play();
                    isPressed = true;
                    scoreint++;
                    text.setString("Score: " + std::to_string(scoreint));
                }
            }

            else
            {
                buttonClick.SetColor(color.Green);
                isPressed = false;               
            }

        }

        window.clear(sf::Color(238, 123, 104));

        window.draw(backgroundSprite);
        buttonClick.ButtonDraw(window);
        window.draw(text);
        window.display();
    }
    return 0;
}