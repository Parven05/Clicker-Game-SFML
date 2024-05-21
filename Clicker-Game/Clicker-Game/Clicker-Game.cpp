#include <iostream>
#include <SFML/Graphics.hpp>
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

    settings.antialiasingLevel = 8;

    // Window
    window.create(sf::VideoMode(500, 500), "Click Game", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    // Circle position
    circle.setPosition(100, 100);
    sf::Vector2f circlePosition = circle.getPosition() + sf::Vector2f(circle.getRadius(), circle.getRadius());

    //add Text
    if (!font.loadFromFile("Montserrat.ttf"))
    {
        std::cout << "Font not set" << std::endl;
    }

    text.setFont(font);
    text.setString("Score: 0");
    text.setFillColor(color.Yellow);
    text.setCharacterSize(50);
    text.setStyle(text.Bold);
    text.setPosition(145, 20);

    // score initialize
    int scoreint = 0;

    while (window.isOpen())
    {
        // Mouse position
        sf::Vector2i mousePositionint = mouse.getPosition(window);
        sf::Vector2f mousePosition = static_cast<sf::Vector2f>(mousePositionint);

        // Dot Product
        sf::Vector2f toMouseVector = mousePosition - circlePosition; // From circle to mouse vector
        float dotVector = toMouseVector.x * toMouseVector.x + toMouseVector.y * toMouseVector.y;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (mouse.isButtonPressed(mouse.Left))
            {
                if (dotVector <= circle.getRadius() * circle.getRadius())
                {
                    circle.setFillColor(color.Red);
                    scoreint++;
                    text.setString("Score: " + std::to_string(scoreint));
                }
            }
            else
            {
                circle.setFillColor(color.White);
                // text.setString("Hmm");
            }


        }


        window.clear();

        window.draw(text);
        // write code here
        window.draw(circle);
        window.display();
    }

    return 0;
}