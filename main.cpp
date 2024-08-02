#include <iostream>

#include <Graphics.hpp>
#include <System.hpp>
#include <Window.hpp>
#include <Audio.hpp>
#include <Network.hpp>


int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML Works!", sf::Style::Default);
    window.setFramerateLimit(120);

    float hoop_radius = 80.f;
    float hoop_speed = 5.f;
    int hoop_movment_status = 0;

    sf::CircleShape hoop(hoop_radius);
    hoop.setFillColor(sf::Color::White);
    hoop.setOutlineThickness(10.f);
    hoop.setOutlineColor(sf::Color(135,134,133,255));
    hoop.setPosition(0.f, 10.f);

    sf::CircleShape ball(20.f);
    bool is_shoot = false;
    ball.setFillColor(sf::Color::Blue);
    ball.setPosition(0.f, window.getSize().y - ball.getRadius()*3);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();

            if(event.KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        // Update hoop
        if(hoop.getPosition().x + hoop_radius*2.f > 1920.f)
            hoop_movment_status = 1;
        if(hoop.getPosition().x < 0)
            hoop_movment_status = 0;

        if(hoop_movment_status == 0)
        {
            hoop.move(hoop_speed, 0.f);
        }
        else
        {
            hoop.move(-hoop_speed, 0.f);
        }

        // update ball
        if(!is_shoot)
            ball.setPosition(sf::Mouse::getPosition(window).x, ball.getPosition().y);
        else
            ball.move(0.f, -10.f);

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            is_shoot = true;
        }

        // Colision ball
        if(ball.getPosition().y < 0 || ball.getGlobalBounds().intersects(hoop.getGlobalBounds()))
        {
            is_shoot = false;
            ball.setPosition(ball.getPosition().x, window.getSize().y - ball.getRadius()*3);
        }

        // Draw
        window.clear();
        // Draw stuff
        window.draw(hoop);
        window.draw(ball);

        window.display();
    }

    return 0;
}

