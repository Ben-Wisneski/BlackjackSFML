#include <SFML/Graphics.hpp>
#include <iostream>

const int CARD_HEIGHT = 42;
const int CARD_WIDTH = 31;
const int NUMBER_CARDS = 52;

std::vector<sf::Sprite> deck;

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Blackjack");
    window.setFramerateLimit(60);


    /*
        Creation of the deck of cards
        1. loads the texture from A-10_Cards.png
        2. Makes a std::vector<sf::Sprite> and stores an individual rectangle for all the cards
        note: can control the position of each card with .setPosition
    */
    sf::Texture cardTexture;
    if(!cardTexture.loadFromFile("spriteSheet.png")){
        sf::err() << "Failed to load card texture!" << std::endl;
        return -1;
    }
    
    sf::Vector2i size(CARD_WIDTH, CARD_HEIGHT);
    sf::Sprite cardSprite(cardTexture);
    for(int i = 0; i < NUMBER_CARDS; i++){
        sf::Vector2i position(i*CARD_WIDTH, 0);
        cardSprite.setTextureRect(sf::IntRect(position, size));
        cardSprite.setScale(sf::Vector2f(4.f,4.f));
        cardSprite.setPosition(sf::Vector2f(i*CARD_WIDTH-2,0));
        deck.push_back(cardSprite);
    }




    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                return -1;
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    return -1;
            }
            
        }
        window.clear(sf::Color::White);
        for(int i = 0; i < NUMBER_CARDS; i++){
            window.draw(deck[i]);
        }
        window.display();
        
    }
}