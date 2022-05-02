/* --------------------------------------------------------
 *    File: main.cpp
 *  Author: Luke Hepokoski
 *   Class: COP 2006 Spring 2022 CRN 13969
 * Purpose: adding paddle definition
 * -------------------------------------------------------- */
#include <SFML/Graphics.hpp>

#ifndef PONGPADDLE_PONG_DEFS_H
#define PONGPADDLE_PONG_DEFS_H

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

struct Block {
    float left;
    float top;
    float width;
    float height;
    sf::Color color;
    sf::RectangleShape rectShape;
};

// Paddle Block structure declaration

struct MoveBlock {

    float velocityX;
    float velocityY;
    Block location;

};

// Border structure declaration

struct Borders {
    Block leftWall;
    Block rightWall;
    Block topWall;
    Block bottomWall;
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
struct Ball {
    float radius;
    float coordinateX;
    float coordinateY;
    float velocityX;
    float velocityY;
    sf::Color color;
};


#endif //PONGPADDLE_PONG_DEFS_H
