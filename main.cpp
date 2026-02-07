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
enum game{startScreen, play};
enum gameState{deal, playerTurn, dealerTurn};


//Makes the sprites into more then only sprites. Hold suit, value and a pointer to the sprite
class Card{
    private:
    //variables
    sf::Sprite* sprite = nullptr;
    int suit, value;
    public:
    //constructor and default constructor
    Card(): suit(0), value(0), sprite(nullptr){}
    Card(sf::Texture& texture, int s, int v, float scale){
        //want to look more into doing something different for the sprites that are not poiners
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
    sf::Vector2f getPosition(){ return sprite->getPosition(); }
    //setter methods
    void setPosition(sf::Vector2f position){
        sprite->setPosition(position);
    }
    //method to switch between front and back of card
    void switchCardFront(){
        sprite->setTextureRect(sf::IntRect(sf::Vector2i(((suit * 13) + (value - 1))*CARD_WIDTH,0), sf::Vector2i(CARD_WIDTH, CARD_HEIGHT)));
    }
    void switchCardBack(){
        sprite->setTextureRect(sf::IntRect(sf::Vector2i(NUMBER_CARDS*CARD_WIDTH,0), sf::Vector2i(CARD_WIDTH, CARD_HEIGHT)));
    }
    void move(sf::Vector2f move){
        sprite->move(move);
    }
};
std::vector<Card> deck, playerHand, dealerHand;

void shuffleDeck(std::vector<Card>& deck){
    std::random_device rd;
    std::mt19937 name(rd());
    std::shuffle(deck.begin(), deck.end(), name);
}
//Function to get the value of your hand. Accounts for aces
int getHandValue(std::vector<Card>& hand){
    int value, aces;
    for(int i = 0; i < hand.size(); i++){
        if(hand[i].getValue() >= 10){
            value += 10;
        }
        else if(hand[i].getValue() == 1){
            aces++;
            value += 11;
        }
        else{
            value += hand[i].getValue();
        }
    }
    while(value > 21 and aces > 0){
        value -= 10;
        aces--;
    }
    return value;
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

    enum game setGameMode = startScreen;
    enum gameState turn = deal;
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
                
                switch(setGameMode){
                    case startScreen:
                        //change this to mouse button left
                        if (keyPressed->scancode == sf::Keyboard::Scancode::S){
                            // puts the card into their hands and sets the positions so when drawn will end out correctly
                            for (int i = 0; i < 2; i++)
                            {
                                playerHand.push_back(deck.back());
                                deck.pop_back();
                                dealerHand.push_back(deck.back());
                                deck.pop_back();
                                playerHand[i].setPosition(sf::Vector2f(620 + (i * 30), 500 - (i * 50)));
                                dealerHand[i].setPosition(sf::Vector2f(620 - (i * 30), 20 + (i * 50)));
                            }
                            dealerHand[0].switchCardBack();
                            // Switches from start screen to play
                            setGameMode = play;
                        }
                        break;
                    case play:
                        switch(turn){
                            case deal:
                                if(keyPressed->scancode == sf::Keyboard::Scancode::P){
                                    turn = playerTurn;
                                }
                                break;
                            case playerTurn:
                                if(keyPressed->scancode == sf::Keyboard::Scancode::H){
                                    playerHand.push_back(deck.back());
                                    deck.pop_back();
                                    sf::Vector2f position = playerHand[playerHand.size() - 2].getPosition();
                                    playerHand[playerHand.size()-1].setPosition(position);
                                    playerHand.back().move(sf::Vector2f(50.f, -50.f));
                                }
                                else if(keyPressed->scancode == sf::Keyboard::Scancode::S){
                                    turn = dealerTurn;
                                }
                                break;
                            
                        }
                        break;
                }
            }
        }
        switch(setGameMode){
            case startScreen:
                window.clear(sf::Color::Black);
                //Here is where I can add the startScreen
                
                break;
            case play:
                window.clear(sf::Color(0, 100, 0));
                switch(turn){
                    case deal:
                        for(int i = 0; i < playerHand.size(); i++){
                            window.draw(playerHand[i].getSprite());
                            window.draw(dealerHand[i].getSprite());
                        }
                        break;
                    case playerTurn:
                        /*
                            1. Draw hand function
                            2. Check the value of the current hand
                                3. If value > 21, switch to bust screen ask if they want to play again
                                4. if value < 21, ask if they want to hit or stand
                                    if hit, give another card and set position accordingly
                                    if stand, set turn to dealerTurn
                        */
                       //draw hand
                       for(int i = 0; i < playerHand.size(); i++){
                            window.draw(playerHand[i].getSprite());
                            
                        }
                        for(int i = 0; i < dealerHand.size(); i++){
                            window.draw(dealerHand[i].getSprite());
                        }
                        //check for the value of current hand
                        getHandValue(playerHand);
                        break;
                    case dealerTurn:
                        break;
                }
        }
        window.display();
    }
}