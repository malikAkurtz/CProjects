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
#include <time.h>

using namespace std;

const int SCREEN_HEIGHT = 700;
const int SCREEN_WIDTH = 480;

bool gameRunning = false;

class Shape;

void spawnSingleCube();

vector<Shape*> shapesOnBoard;

Shape *fallingShape;

int SHAPE_BLOCK_SIZE = 30;



class Shape {
    public:
    vector<sf::RectangleShape> parts;
    bool isFalling;

    virtual ~Shape() {} // destructor

};



class SingleCube : public Shape {
    public:
    SingleCube(float x, float y) {
        sf::RectangleShape oneCube(sf::Vector2f(SHAPE_BLOCK_SIZE, SHAPE_BLOCK_SIZE));
        oneCube.setFillColor(sf::Color(100, 250, 50));
        sf::Vector2f initialpos(x, y);
        oneCube.setPosition(initialpos);
        parts.push_back(oneCube);
        shapesOnBoard.push_back(this);
        isFalling = true;
    }
};



void setup() {
    gameRunning = true;
    spawnSingleCube();
}



void draw(sf::RenderWindow &window) {
    window.clear();

    // Used chat to help me out with these pointers
    if (shapesOnBoard.size() > 0) {
        for (int i = 0; i < shapesOnBoard.size(); i++) {
            Shape *curShape = shapesOnBoard[i];
            for (int j = 0; j < curShape->parts.size(); j++) {
                window.draw(curShape->parts[j]);
            }
        }
    }
    

    window.display();
}



void spawnSingleCube() {
    cout << "Spawned a cube";
    SingleCube *newSingleCube = new SingleCube(SCREEN_WIDTH/2, 0.0);
    shapesOnBoard.push_back(newSingleCube);
}



void gameLogic(sf::Keyboard::Key &keypress) {

    // If there are shapes on the board
    if (shapesOnBoard.size() > 0) {
        // get the last shape appended to the board since this will be the recent shape that is falling
        fallingShape = shapesOnBoard.back();
        // while the shape is in a falling state
            // for each part of the shape
        for (auto &part : fallingShape->parts) {
            // so long as the part is not at the bottom of the screen 
            if (part.getGlobalBounds().getPosition().y < SCREEN_HEIGHT - part.getGlobalBounds().height) {
                // move the part down
                part.move(0,0.03);
            }
            else {
                fallingShape->isFalling = false;
                break;
            }
        }

        for (auto &part : fallingShape->parts) {
            for (auto &otherShape : shapesOnBoard) {
                if (otherShape == fallingShape) {continue;} // jump over ourselves
                for (auto &otherShapePart : otherShape->parts) {
                    if (part.getGlobalBounds().intersects(otherShapePart.getGlobalBounds())) {
                        fallingShape->isFalling = false;
                        break;
                    }
                }
            }
        }

        if (!fallingShape->isFalling) {
            spawnSingleCube();
        }        
    }
    

    
    if (keypress == sf::Keyboard::Left) {
        cout << "left" << endl;
        for (auto &part : fallingShape->parts) {
            if (part.getGlobalBounds().left > 0) {
                part.move(-30.0, 0.0);
            }
            
        }
    }
    else if (keypress == sf::Keyboard::Right) {
        cout << "right" << endl;
        for (auto &part : fallingShape->parts) {
            if ((part.getGlobalBounds().left+part.getGlobalBounds().width) < SCREEN_WIDTH) {
                part.move(30.0, 0.0);
            }
            
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