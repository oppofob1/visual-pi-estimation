#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <math.h>
#include <cmath>
#include <iostream>

//random flat selecter between values
float randomFloat(float min, float max)
{
    return min + static_cast<float>(std::rand()) / RAND_MAX * (max - min);
}

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({720u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(144);

    //background rectangle of the button
    sf::RectangleShape buttonBg;
    buttonBg.setSize({640.f, 90.f});
    buttonBg.setFillColor({100, 100, 150});
    buttonBg.setOrigin(buttonBg.getGeometricCenter());
    buttonBg.setPosition({360.f, 80.f});

    //text of the button
    const sf::Font font("../../ARIAL.TTF");
    sf::Text buttonText(font, "PRESS THIS BUTTON", 50);
    buttonText.setFillColor(sf::Color::Black);
    buttonText.setPosition({105.f, 50.f});

    //pi text
    sf::Text piText(font, "Pi: ", 50);
    piText.setFillColor(sf::Color::Black);
    piText.setPosition({20.f, 880.f});

    //square 
    sf::RectangleShape square;
    square.setSize({640.f, 640.f});
    square.setFillColor(sf::Color(50, 50, 100));
    square.setOrigin(square.getGeometricCenter());
    square.setPosition({360.f, 540.f});

    //circle
    sf::CircleShape circle(320.f);
    circle.setFillColor(sf::Color(100, 100, 150));
    circle.setOrigin(circle.getGeometricCenter());
    circle.setPosition({360.f, 540.f});

    //points
    sf::CircleShape point(5.f);
    point.setFillColor(sf::Color::Red);
    circle.setOrigin(circle.getGeometricCenter());

    //position vector for points
    std::vector<sf::Vector2f> pointPos;

    //set to 1 so doesnt divide by 0
    int pointOnSquare = 1;
    int pointOnCircle = 1;

    //mouse press
    bool wasMousePressed = false;

    //defin point coordinates
    float randomX;
    float randomY;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        //draw background, button, square, circle
        window.clear(sf::Color(220, 220, 250));
        window.draw(buttonBg);
        window.draw(buttonText);
        
        window.draw(square);
        window.draw(circle);

        //mouse press
        bool isMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

        //check for mouse press
        if (isMousePressed && !wasMousePressed)
        {  
            //mouse coordinate relative to screen center
            int mouseX = sf::Mouse::getPosition().x - (window.getPosition().x + window.getSize().x / 2);
            int mouseY = sf::Mouse::getPosition().y - (window.getPosition().y + window.getSize().y / 2);

            //checks for button press, adds random coordinates to point pos vector
            if (330 > mouseX && mouseX > -310 && -380 > mouseY && mouseY > -470)
            {
                randomX = randomFloat(40, 680);
                randomY = randomFloat(220, 860);
                pointPos.push_back({randomX, randomY});
            }
            
            pointOnSquare+=1;

            //check for point positions that are on circle
            if ((randomX - circle.getPosition().x) * (randomX - circle.getPosition().x)
             + (randomY - circle.getPosition().y) * (randomY - circle.getPosition().y) < 320 * 320)
            {
                pointOnCircle+=1;
            }
        }
        //mouse press
        wasMousePressed = isMousePressed;

        //for pos in pointpos vector
        for (const auto& pos : pointPos)
        {   
            //draws point and calculates pi
            point.setPosition(pos);
            float pi = 4 * (static_cast<float>(pointOnCircle) / static_cast<float>(pointOnSquare));
            piText.setString(std::to_string(pi));
            window.draw(point);
        }

        //last renders
        window.draw(piText);
        window.display();
    }
}
