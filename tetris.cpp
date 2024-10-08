// My name is Malik Kurtz and I made this game 

/* 

1. ) create main shape class

2.) create sub shape classes

3.) 

*/

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;

const int SCREEN_HEIGHT = 700;
const int SCREEN_WIDTH = 500;

bool gameRunning = false;

class Shape;

void spawnSingleCube();

vector<Shape*> shapesOnBoard;

Shape *fallingShape;



class Shape {
    public:
    vector<sf::RectangleShape> parts;

    virtual ~Shape() {} // destructor

};



class SingleCube : public Shape {
    public:
    SingleCube(float x, float y) {
        sf::RectangleShape oneCube(sf::Vector2f(30, 30));
        oneCube.setFillColor(sf::Color(100, 250, 50));
        sf::Vector2f initialpos(x, y);
        oneCube.setPosition(initialpos);
        parts.push_back(oneCube);
        shapesOnBoard.push_back(this);
    }
};



void setup() {
    gameRunning = true;
    spawnSingleCube();
}



void draw(sf::RenderWindow &window) {
    window.clear();

    // Used chat to help me out with these pointers
    for (int i = 0; i < shapesOnBoard.size(); i++) {
        Shape *curShape = shapesOnBoard[i];
        for (int j = 0; j < curShape->parts.size(); j++) {
            window.draw(curShape->parts[j]);
        }
    }

    window.display();
}



void spawnSingleCube() {
    SingleCube *newSingleCube = new SingleCube(SCREEN_WIDTH/2, 0.0);
    shapesOnBoard.push_back(newSingleCube);
}



void gameLogic(sf::Keyboard::Key &keypress) {
    fallingShape = shapesOnBoard.back();

    if (keypress == sf::Keyboard::Up) {
        cout << "up" << endl;
    }
    else if (keypress == sf::Keyboard::Down) {
        cout << "down" << endl;
    }
    else if (keypress == sf::Keyboard::Left) {
        cout << "left" << endl;
        for (auto &part : fallingShape->parts) {
            part.move(-12.0, 0.0);
        }
    }
    else if (keypress == sf::Keyboard::Right) {
        cout << "right" << endl;
        for (auto &part : fallingShape->parts) {
            part.move(12.0, 0.0);
        }
    }


    if (shapesOnBoard.size() > 0) {
        for (auto &part : fallingShape->parts) {
            part.move(0,0.05);
        }
    }
    
}



sf::Keyboard::Key getInput(sf::Event &event){

    switch (event.key.code) {
        case sf::Keyboard::Up:
            return sf::Keyboard::Up;
        case sf::Keyboard::Down:
            return sf::Keyboard::Down;
        case sf::Keyboard::Left:
            return sf::Keyboard::Left;
            break;
        case sf::Keyboard::Right:
            return sf::Keyboard::Right;
        default:
            return sf::Keyboard::Unknown;
    }

}



int main () {

    setup();

    sf::RenderWindow gameWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Tetris");

    sf::Event event;
    sf::Keyboard::Key keyPressed;
    
    while (gameWindow.isOpen() && gameRunning) {
        keyPressed = sf::Keyboard::Unknown;
        
        while(gameWindow.pollEvent(event)){

            if (event.type == sf::Event::Closed ) {
                gameRunning = false;
                gameWindow.close();
            }
            else if (event.type == sf::Event::KeyPressed)
                keyPressed = getInput(event);
        }

        gameLogic(keyPressed);
        
        draw(gameWindow);
    
    }

    return 0;
}