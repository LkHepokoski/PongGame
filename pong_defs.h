/* --------------------------------------------------------
 *    File: pong_defs.cpp
 *  Author: Luke Hepokoski
 *   Class: COP 2006 Spring 2022 CRN 13969
 * Purpose: adding paddle definition
 * -------------------------------------------------------- */


#ifndef PONGPADDLE_PONG_DEFS_H
#define PONGPADDLE_PONG_DEFS_H
#include <SFML/Graphics.hpp>
#include <memory>
// Global Constants
// --------------------------------------------------------

// window properties
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const sf::Color WINDOW_COLOR = sf::Color::White;

// wall properties
const float WALL_THICKNESS = 2.0;
const sf::Color WALL_COLOR = sf::Color::Red;

// ball properties
const float BALL_RADIUS = 10.0;

// paddle properties
const float PADDLE_HEIGHT = 80.0;
const float PADDLE_THICKNESS = 10.0;
sf::Color PADDLE_COLOR = sf::Color::Black;
const float PADDLE_SPEED = PADDLE_HEIGHT / 9.0 / 1000.0;

// drawing properties
const float FRAME_RATE = (1.0 / 60.0) * 1000.0;       // FPS in ms
const sf::Color BALL_COLOR = sf::Color::Blue;

// These are just for fun
// speed that the can accelerate at to span window in
// n-seconds (in ms) broken up for each frame

const float SPEED_TIME = (3.0 * 1000.0) * 30.0;     //
const float BALL_SPEED_X = BALL_RADIUS * 12.0 / 1000.0;    // speed horizontally
const float BALL_SPEED_Y = BALL_RADIUS * 10.5 / 1000.0;   // span  vertically

// Block structure declaration

class BlockClass {
public:
    float left;
    float top;
    float width;
    float height;
    sf::Color color;
    sf::RectangleShape rectShape;

};

// Paddle Block structure declaration

class MoveBlock : public BlockClass {
public:
    float velocityX;
    float velocityY;
    BlockClass location;


};

// Border structure declaration

class Borders : public BlockClass {
public:
    BlockClass leftWall;
    BlockClass rightWall;
    BlockClass topWall;
    BlockClass bottomWall;

    void setup (std::shared_ptr<Borders> wall){
        // define left wall
        wall->leftWall.left = 0.0;
        wall->leftWall.top = 0.0;
        wall->leftWall.width = WALL_THICKNESS;
        wall->leftWall.height = WINDOW_HEIGHT;
        wall->leftWall.rectShape.setSize(sf::Vector2(wall->leftWall.width, wall->leftWall.height));
        wall->leftWall.rectShape.setPosition(wall->leftWall.left, wall->leftWall.top);
        wall->leftWall.rectShape.setFillColor(WALL_COLOR);

        // define right wall
        wall->rightWall.left = WINDOW_WIDTH - WALL_THICKNESS;
        wall->rightWall.top = 0.0;
        wall->rightWall.width = WALL_THICKNESS;
        wall->rightWall.height = WINDOW_HEIGHT;
        wall->rightWall.rectShape.setSize(sf::Vector2(wall->rightWall.width, wall->rightWall.height));
        wall->rightWall.rectShape.setPosition(wall->rightWall.left, wall->rightWall.top);
        wall->rightWall.rectShape.setFillColor(WALL_COLOR);

        // define top wall
        wall->topWall.left = 0.0;
        wall->topWall.top = 0.0;
        wall->topWall.width = WINDOW_WIDTH;
        wall->topWall.height = WALL_THICKNESS;
        wall->topWall.rectShape.setSize(sf::Vector2(wall->topWall.width, wall->topWall.height));
        wall->topWall.rectShape.setPosition(wall->topWall.left, wall->topWall.top);
        wall->topWall.rectShape.setFillColor(WALL_COLOR);

        // define bottom wall
        wall->bottomWall.left = 0.0;
        wall->bottomWall.top = WINDOW_HEIGHT - WALL_THICKNESS;
        wall->bottomWall.width = WINDOW_WIDTH;
        wall->bottomWall.height = WALL_THICKNESS;
        wall->bottomWall.rectShape.setSize(sf::Vector2(wall->bottomWall.width, wall->bottomWall.height));
        wall->bottomWall.rectShape.setPosition(wall->bottomWall.left, wall->bottomWall.top);
        wall->bottomWall.rectShape.setFillColor(WALL_COLOR);
    }

};


// Type definitions
// --------------------------------------------------------

// <direction enum here>
enum Direction {
    Exit = -1,
    None,
    Left,
    Up,
    Right,
    Down,
    Start
};

// ball properties
class BallClass {
public:
    float radius;
    float coordinateX;
    float coordinateY;
    float velocityX;
    float velocityY;
    sf::Color color;


    void setup(std::shared_ptr<BallClass> ball){

        // declare a ball variable and populate it in the center of the window
        ball->radius = BALL_RADIUS;
        ball->coordinateX = WINDOW_WIDTH / 2;
        ball->coordinateY = WINDOW_HEIGHT / 2;
        ball->velocityX = BALL_SPEED_X;
        ball->velocityY = BALL_SPEED_Y;
        ball->color = BALL_COLOR;
    }

};


#endif //PONGPADDLE_PONG_DEFS_H
