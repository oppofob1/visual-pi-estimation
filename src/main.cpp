#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <math.h>
#include <cmath>
#include <iostream>

float randomFloat(float min, float max)
{
    return min + static_cast<float>(std::rand()) / RAND_MAX * (max - min);
}


int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({720u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(144);

    sf::RectangleShape buttonBg;
    buttonBg.setSize({640.f, 90.f});
    buttonBg.setFillColor({100, 100, 150});
    buttonBg.setOrigin(buttonBg.getGeometricCenter());
    buttonBg.setPosition({360.f, 80.f});


    const sf::Font font("../../ARIAL.TTF");
    sf::Text buttonText(font, "PRESS THIS BUTTON", 50);
    buttonText.setFillColor(sf::Color::Black);
    buttonText.setPosition({105.f, 50.f});

    sf::Text piText(font, "Pi: ", 50);
    piText.setFillColor(sf::Color::Black);
    piText.setPosition({20.f, 880.f});

    sf::RectangleShape square;
    square.setSize({640.f, 640.f});
    square.setFillColor(sf::Color(50, 50, 100));
    square.setOrigin(square.getGeometricCenter());
    square.setPosition({360.f, 540.f});

    sf::CircleShape circle(320.f);
    circle.setFillColor(sf::Color(100, 100, 150));
    circle.setOrigin(circle.getGeometricCenter());
    circle.setPosition({360.f, 540.f});

    sf::CircleShape point(5.f);
    point.setFillColor(sf::Color::Red);
    circle.setOrigin(circle.getGeometricCenter());

    std::vector<sf::Vector2f> pointPos;

    std::srand(std::time({}));

    sf::Clock clock;

    int pointOnSquare = 1;
    int pointOnCircle = 1;

    bool wasMousePressed = false;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        

        window.clear(sf::Color(220, 220, 250));
        window.draw(buttonBg);
        window.draw(buttonText);
        
        window.draw(square);
        window.draw(circle);



        bool isMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

        if (isMousePressed && !wasMousePressed)
        {
            int mouseX = sf::Mouse::getPosition().x - (window.getPosition().x + window.getSize().x / 2);
            int mouseY = sf::Mouse::getPosition().y - (window.getPosition().y + window.getSize().y / 2);

            if (330 > mouseX && mouseX > -310 && -380 > mouseY && mouseY > -470)
            {
                float randomX = randomFloat(40, 680);
                float randomY = randomFloat(220, 860);
                pointPos.push_back({randomX, randomY});
            }
        }
        wasMousePressed = isMousePressed;

        for (const auto& pos : pointPos)
        {   
            point.setPosition(pos);
            if ((pos.x - circle.getPosition().x) * (pos.x - circle.getPosition().x) + (pos.x - circle.getPosition().x) * (pos.x - circle.getPosition().x) < 400)
            {
                pointOnCircle++;
                pointOnSquare++;
                std::cout << std::to_string(pointOnCircle);
                std::cout << std::to_string(pointOnSquare);
            } else
            {
                pointOnSquare++;
                std::cout << std::to_string(pointOnSquare);
            }

            float pi = 4 * (pointOnCircle / pointOnSquare);
            piText.setString(std::to_string(pi));
            window.draw(point);
        }
        window.draw(piText);
        window.display();
    }
}
