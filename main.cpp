#include <SFML/Graphics.hpp>
#include <iostream>
#include <String>
#include <bits/stdc++.h>
//#include <random> //For the random, makes it so I can shuffle the deck when needed
#include <windows.h> //used for debugging, can pause time so I can see what is happening
//constant variables
const int CARD_HEIGHT = 42;
const int CARD_WIDTH = 31;
const int NUMBER_CARDS = 52;
int game = 0;

//Makes the sprites into more then only sprites. Hold suit, value and a pointer to the sprite
class Card{
    private:
    //variables
    sf::Sprite* sprite = nullptr;
    int suit, value;
    public:
    //constructor and default constructor
    Card(): suit(0), value(0), sprite(nullptr){

    }
    Card(sf::Texture& texture, int s, int v, float scale){
        sprite = new sf::Sprite(texture);
        sprite->setTextureRect(sf::IntRect(sf::Vector2i(((s * 13) + (v - 1))*CARD_WIDTH,0), sf::Vector2i(CARD_WIDTH, CARD_HEIGHT)));
        sprite->setScale(sf::Vector2f(scale,scale));
        suit = s;
        value = v;
    }
    //getter methods
    int getSuit(){ return suit; }
    int getValue(){ return value; }
    sf::Sprite& getSprite() { return *sprite; }
    //setter methods
    void setPosition(int x, int y){
        sf::Vector2f position(x,y);
        sprite->setPosition(position);
    }
};

std::vector<Card> deck, playerHand, dealerHand;


void shuffleDeck(std::vector<Card>& deck){
    std::random_device rd;
    std::mt19937 name(rd());
    std::shuffle(deck.begin(), deck.end(), name);
}

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
    for(int suit = 0; suit < 4; suit++){
        for(int value = 1; value <= 13; value++){
            Card card(cardTexture, suit, value, 4);
            deck.push_back(card);
        } 
    }
    shuffleDeck(deck);
    /*
    for(int i = 0; i<NUMBER_CARDS; i++){
        deck[i].setPosition(i*50,0);
    }
    */
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
                        //puts the card into their hands and sets the positions so when drawn will end out correctly
                        playerHand.push_back(deck[1]);
                        deck.erase(deck.begin());
                        playerHand.push_back(deck[1]);
                        deck.erase(deck.begin());
                        dealerHand.push_back(deck[1]);
                        deck.erase(deck.begin());
                        dealerHand.push_back(deck[1]);
                        deck.erase(deck.begin());
                        game++;
                        
                }
            }
            
        }
        switch(game){
            case 1:
                window.clear(sf::Color::Black);
                window.draw(playerHand[1].getSprite());
                window.display();
                break;
        }
    }
}
