#include <SFML/Graphics.hpp>

class Button
{
public:
    sf::CircleShape circle;
    sf::Vector2f position;

    Button(float radius, sf::Vector2f position, sf::Texture& button)
    {
        circle.setRadius(radius);
        circle.setPosition(position);
        circle.setTexture(&button);
        this->position = position + sf::Vector2f(radius, radius);
    }
    sf::Vector2f GetPosition() const
    {
        return position;
    }

    float GetRadius() const
    {
        return circle.getRadius();
    }

    void SetColor(const sf::Color& color)
    {
        circle.setFillColor(color);
    }

    void ButtonDraw(sf::RenderWindow& window) const
    {
        window.draw(circle);
    }
};