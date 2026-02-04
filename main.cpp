#include <SFML/Graphics.hpp>
#include <iostream>
#include <String>
#include <windows.h>

const int CARD_HEIGHT = 42;
const int CARD_WIDTH = 31;
const int NUMBER_CARDS = 52;

class Card{
    private:
    sf::Sprite* sprite;
    int suit, value;
    public:
    Card(sf::Texture& texture, int s, int v, float scale){
        sprite = new sf::Sprite(texture);
        sprite->setTextureRect(sf::IntRect(sf::Vector2i(((s * 13) + (v - 1))*CARD_WIDTH,0), sf::Vector2i(CARD_WIDTH, CARD_HEIGHT)));
        sprite->setScale(sf::Vector2f(scale,scale));
        suit = s;
        value = v;
    }
    int getSuit(){ return suit; }
    int getValue(){ return value; }
    sf::Sprite& getSprite() { return *sprite; }
    void setPosition(int x, int y){
        sf::Vector2f position(x,y);
        sprite->setPosition(position);
    }
};

std::vector<Card> deck;

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Blackjack");
    window.setFramerateLimit(60);
    /*
        Creation of the deck of cards with the card class
        1. loads the texture from spriteSheet.png
        2. Makes a std::vector<sf::Sprite> and stores an individual rectangle for all the cards
    */
    sf::Texture cardTexture;
    if(!cardTexture.loadFromFile("spriteSheet.png")){
        sf::err() << "Failed to load card texture!" << std::endl;
        return -1;
    }
    sf::Vector2i size(CARD_WIDTH, CARD_HEIGHT);
    int position = 0;
    for(int suit = 0; suit < 4; suit++){
        for(int value = 1; value <= 13; value++){
            Card card(cardTexture, suit, value, 4);
            card.setPosition(position*CARD_WIDTH-2,0);
            deck.push_back(card);
            position++;
        } 
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
                else if(keyPressed->scancode == sf::Keyboard::Scancode::S){
                    deck[22].setPosition(300,300);
                }
            }
            
        }
        
        window.clear(sf::Color::Blue);
        for(int i = 0; i < NUMBER_CARDS; i++){
            window.draw(deck[i].getSprite());
        }
        window.display();
        
    }
}
