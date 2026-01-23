#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Blackjack");
    window.setFramerateLimit(60);
    sf::RectangleShape shape(sf::Vector2f(50.f, 150.f));
    sf::RectangleShape bro(sf::Vector2f(50.f, 150.f));
    bro.setFillColor(sf::Color::Blue);
    bro.move({600.f,0});
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            //Used the getIf function built into sf::Event to check if escape key is pressed and if it is, closes the window
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
                
                if(keyPressed-> scancode == sf::Keyboard::Scancode::W)
                    shape.move({0.f, -100.f});
                else if(keyPressed-> scancode == sf::Keyboard::Scancode::A)
                    shape.move({-100.f, 0.f});
                else if(keyPressed-> scancode == sf::Keyboard::Scancode::S) 
                    shape.move({0.f, 100.f});
                else if(keyPressed-> scancode==sf::Keyboard::Scancode::D)  
                    shape.move({100.f, 0.f});

                //for the blue shape movement
                if(keyPressed-> scancode == sf::Keyboard::Scancode::Up)
                    bro.move({0.f, -100.f});
                else if(keyPressed-> scancode == sf::Keyboard::Scancode::Left)
                    bro.move({-100.f, 0.f});
                else if(keyPressed-> scancode == sf::Keyboard::Scancode::Down)   
                    bro.move({0.f, 100.f});
                else if(keyPressed-> scancode==sf::Keyboard::Scancode::Right)
                    bro.move({100.f, 0.f});
            }
            
        }
        window.clear();
        window.draw(shape);
        window.draw(bro);
        window.display();
    }
}