/* --------------------------------------------------------
 *    File: functions.h
 *  Author: Luke Hepokoski
 *   Class: COP 2006 Spring 2022 CRN 13969
 * Purpose: adding function definitions
 * -------------------------------------------------------- */
#ifndef PONGFINAL_FUNCTIONS_H
#define PONGFINAL_FUNCTIONS_H

#include <SFML/Graphics.hpp>
#include "pong_defs.h"
/**
 * setup for game objects
 * @param ball - ball parameter
 * @param wall - wall parameter
 * @param paddle - user paddle parameter
 * @param paddle2 - computer paddle parameter
 */
void setup(Borders &wall, MoveBlock &paddle, MoveBlock &paddle2) {

    // define left wall
    wall.leftWall.left = 0.0;
    wall.leftWall.top = 0.0;
    wall.leftWall.width = WALL_THICKNESS;
    wall.leftWall.height = WINDOW_HEIGHT;
    wall.leftWall.rectShape.setSize(sf::Vector2(wall.leftWall.width, wall.leftWall.height));
    wall.leftWall.rectShape.setPosition(wall.leftWall.left, wall.leftWall.top);
    wall.leftWall.rectShape.setFillColor(WALL_COLOR);

    // define right wall
    wall.rightWall.left = WINDOW_WIDTH - WALL_THICKNESS;
    wall.rightWall.top = 0.0;
    wall.rightWall.width = WALL_THICKNESS;
    wall.rightWall.height = WINDOW_HEIGHT;
    wall.rightWall.rectShape.setSize(sf::Vector2(wall.rightWall.width, wall.rightWall.height));
    wall.rightWall.rectShape.setPosition(wall.rightWall.left, wall.rightWall.top);
    wall.rightWall.rectShape.setFillColor(WALL_COLOR);

    // define top wall
    wall.topWall.left = 0.0;
    wall.topWall.top = 0.0;
    wall.topWall.width = WINDOW_WIDTH;
    wall.topWall.height = WALL_THICKNESS;
    wall.topWall.rectShape.setSize(sf::Vector2(wall.topWall.width, wall.topWall.height));
    wall.topWall.rectShape.setPosition(wall.topWall.left, wall.topWall.top);
    wall.topWall.rectShape.setFillColor(WALL_COLOR);

    // define bottom wall
    wall.bottomWall.left = 0.0;
    wall.bottomWall.top = WINDOW_HEIGHT - WALL_THICKNESS;
    wall.bottomWall.width = WINDOW_WIDTH;
    wall.bottomWall.height = WALL_THICKNESS;
    wall.bottomWall.rectShape.setSize(sf::Vector2(wall.bottomWall.width, wall.bottomWall.height));
    wall.bottomWall.rectShape.setPosition(wall.bottomWall.left, wall.bottomWall.top);
    wall.bottomWall.rectShape.setFillColor(WALL_COLOR);


    // initialize MoveBlock variable for paddle
    paddle.location.left = PADDLE_THICKNESS;
    paddle.location.top = (WINDOW_HEIGHT - PADDLE_HEIGHT) / 2.0;
    paddle.location.width = PADDLE_THICKNESS;
    paddle.location.height = PADDLE_HEIGHT;
    paddle.location.color = PADDLE_COLOR;
    paddle.location.rectShape.setSize(sf::Vector2f(PADDLE_THICKNESS, PADDLE_HEIGHT));
    paddle.location.rectShape.setFillColor(PADDLE_COLOR);
    paddle.velocityY = 0.0;
    paddle.velocityX = 0.0;

    paddle2.location.left = WINDOW_WIDTH - 2 * PADDLE_THICKNESS;
    paddle2.location.top = (WINDOW_HEIGHT - PADDLE_HEIGHT) / 2.0;
    paddle2.location.width = PADDLE_THICKNESS;
    paddle2.location.height = PADDLE_HEIGHT;
    paddle2.location.color = PADDLE_COLOR;
    paddle2.location.rectShape.setSize(sf::Vector2f(PADDLE_THICKNESS, PADDLE_HEIGHT));
    paddle2.location.rectShape.setFillColor(PADDLE_COLOR);
    paddle2.velocityY = 0.0;
    paddle2.velocityX = 0.0;


} // end setup

/**
 * convert user keyboard input into recognized enum values
 * for left=Left/up=Up/right=Right/down=Down/enter=Start/X=Exit/
 * @return Direction - user input (default no-input=None, quit=Exit)
 */
Direction processInput() {

    Direction input = None;  // no input

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        input = Left;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        input = Start;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        input = Up;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        input = Right;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        input = Down;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        input = Left;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        input = Right;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        input = Up;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        input = Down;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
        input = Exit;
    }

    return input;
} // end processInput

/**
 * Detect collision between ball and wall
 * @param ball - structure variable with properties for the ball bounding box around circle
 * @param wall - rectangle that is used to determine whether collision is made
 * @return collide - returns a true value if the ball collides with a wall
 */
bool ballCollision(std::shared_ptr<BallClass> ball, BlockClass wall) {

    bool collide = false;

    // declare variables for ball
    float leftBall = ball->coordinateX - ball->radius;
    float topBall = ball->coordinateY - ball->radius;
    float rightBall = ball->coordinateX + ball->radius;
    float bottomBall = ball->coordinateY + ball->radius;

    // declare Block variables
    float rightWall = wall.left + wall.width;
    float bottomWall = wall.top + wall.height;
    float leftWall = wall.left;
    float topWall = wall.top;

    // detects if the ball collides with wall
    if (leftBall < rightWall &&
        rightBall > leftWall &&
        topBall < bottomWall &&
        bottomBall > topWall) {

        collide = true;

    }
    return collide;
} // end ballCollision

/**
 * detects collision between paddle and wall
 * @param paddle - user paddle
 * @param wall - walls
 * @return collide - returns true or false if collsiion detected
 */
bool blockCollision(MoveBlock paddle, BlockClass wall) {
    bool collide = false;

    // declare variables for paddle dimensions
    float paddleRight = paddle.location.left + paddle.location.width;
    float paddleTop = paddle.location.top;
    float paddleBottom = paddle.location.top + paddle.location.height;
    float paddleLeft = paddle.location.left;

    // declare Block variables
    float rightWall = wall.left + wall.width;
    float bottomWall = wall.top + wall.height;
    float leftWall = wall.left;
    float topWall = wall.top;

    // detects if the ball collides with wall
    if (paddleLeft < rightWall &&
        paddleRight > leftWall &&
        paddleTop < bottomWall &&
        paddleBottom > topWall) {

        collide = true;
    }
    return collide;
} // end blockCollision



/**
 * collision detection function that combines previous collision checking
 * @param ball - ball
 * @param paddle - user paddle
 * @param walls - walls
 * @param paddle2 - computer paddle
 * @return gameOver - returns true/false for collision detection
 */
bool collisionDetect(std::shared_ptr<BallClass> ball, MoveBlock &paddle, Borders &walls, MoveBlock &paddle2) {
    // declare local gameOver variable
    bool gameOver = false;

    // call ballCollision to check collision of ball and paddle
    if (ballCollision(ball, paddle.location)) {
        if (ball->velocityY < 0 && paddle.velocityY < 0) {
            ball->velocityY += 0.05;
        } else if (ball->velocityY > 0 && paddle.velocityY > 0) {
            ball->velocityY += 0.05;
        }
        if (ball->velocityY > 0 && paddle.velocityY < 0) {
            ball->velocityY -= 0.05;
        } else if (ball->velocityY < 0 && paddle.velocityY > 0) {
            ball->velocityY -= 0.05;
        }
        ball->velocityX *= -1;
        ball->coordinateX = paddle.location.left + paddle.location.width + ball->radius + 1;
    }

        // call ballCollision to check horizontal collisions of ball and wall
    else if (ballCollision(ball, walls.leftWall)) {
        ball->velocityX *= -1;
        ball->coordinateX = walls.leftWall.left + walls.leftWall.width + ball->radius + 1;
        gameOver = true;
    } else if (ballCollision(ball, walls.rightWall)) {
        ball->velocityX *= -1;
        ball->coordinateX = walls.rightWall.left - ball->radius - 1;
        gameOver = true;
    }

    // call ballCollision to check vertical collisions
    if (ballCollision(ball, walls.topWall)) {
        ball->velocityY *= -1;
        ball->coordinateY = walls.topWall.top + walls.topWall.height + ball->radius + 1;

    } else if (ballCollision(ball, walls.bottomWall)) {
        ball->velocityY *= -1;
        ball->coordinateY = walls.bottomWall.top - ball->radius - 1;
    }

    // block collision to check collision between paddle and top/bottom wall
    if (blockCollision(paddle, walls.topWall)) {
        paddle.velocityY = 0.0;
        paddle.location.top = walls.topWall.top + walls.topWall.height + 1;
    } else if (blockCollision(paddle, walls.bottomWall)) {
        paddle.velocityY = 0.0;
        paddle.location.top = walls.bottomWall.top - paddle.location.height - 1;
    }

    // collision check between ball and AI paddle
    if (ballCollision(ball, paddle2.location)) {
        if (ball->velocityY < 0 && paddle2.velocityY < 0) {
            ball->velocityY += 0.05;
        } else if (ball->velocityY > 0 && paddle2.velocityY > 0) {
            ball->velocityY += 0.05;
        } else if (ball->velocityY > 0 && paddle2.velocityY < 0) {
            ball->velocityY -= 0.05;
        } else if (ball->velocityY < 0 && paddle2.velocityY > 0) {
            ball->velocityY -= 0.05;
        }

        ball->velocityX *= -1;
        ball->coordinateX = paddle2.location.left - ball->radius - 1;

    }
    // block collision to check collision between AI paddle and top/bottom wall
    if (blockCollision(paddle2, walls.topWall)) {
        paddle2.velocityY = 0.0;
        paddle2.location.top = walls.topWall.top + walls.topWall.height + 1;
    } else if (blockCollision(paddle2, walls.bottomWall)) {
        paddle2.velocityY = 0.0;
        paddle2.location.top = walls.bottomWall.top - paddle2.location.height - 1;
    }

    return gameOver;
} // end collisionDetect


/**
 * update the state of game objects and returns bool value
 * @param input - user keyboard input
 * @param ball  - update ball position and speed
 * @param delta - current frame time
 * @param walls - border struct variable for four walls
 * @param started - returns true value if the game is started
 * @param paddle - user paddle
 * @param paddle2 - computer paddle
 * @return gameOver - returns true if ball hits left wall
 */
bool
update(Direction &input, std::shared_ptr<BallClass> ball, Borders walls, MoveBlock &paddle, float delta, bool &started, MoveBlock &paddle2) {

    paddle.location.color = PADDLE_COLOR;
    paddle2.location.color = PADDLE_COLOR;

    bool gameOver = false;
    // adjust velocity directions for user input
    if (input) {
        switch (input) {
            case Start:
                if (!started) {
                    ball->velocityX = BALL_SPEED_X;
                    ball->velocityY = BALL_SPEED_Y;
                    /* randomly set vertical velocity to positive or negative
                     * by seeing if tenths place of current delta is
                     * odd or even */
                    if ((int(delta * 10) & 1) % 2) {
                        ball->velocityY *= -1;
                    }
                    started = true;
                }
                break;
            case Left:
                //paddle.velocityX -= PADDLE_SPEED;
                break;
            case Up:
                // adjust paddle Y velocity to move up
                paddle.velocityY -= PADDLE_SPEED;
                break;
            case Right:
                //paddle.velocityX += BALL_SPEED_X;
                break;
            case Down:
                // adjust paddle Y velocity to move down
                paddle.velocityY += PADDLE_SPEED;
        }
        // clear input
        input = None;
    }

    // adjust location of paddle for speed * time
    paddle.location.top += paddle.velocityY * delta;
    paddle2.location.top += paddle2.velocityY * delta;

    // adjust the location of the ball for speed * time if game started
    if (started) {
        ball->coordinateX += ball->velocityX * delta;
        ball->coordinateY += ball->velocityY * delta;
        //adjust the location of the AI paddle according to ball location
        if (ball->coordinateY < (paddle2.location.top + paddle2.location.height / 2.0)) {
            paddle2.velocityY -= PADDLE_SPEED;
        } else if (ball->coordinateY > (paddle2.location.top + paddle2.location.height / 2.0)) {
            paddle2.velocityY += PADDLE_SPEED;
        }
    }
        // adjusts location of ball to paddle location if not started
    else {
        ball->coordinateX = paddle.location.left + paddle.location.width + BALL_RADIUS + 1;
        ball->coordinateY = paddle.location.top + (paddle.location.height / 2.0);
    }
    gameOver = collisionDetect(ball, paddle, walls, paddle2);
    return gameOver;
} // end update


/**
 * draw the ball on the graphics window
 * @param window - handle to open graphics window
 * @param ball   - structure variable with properties for the ball
 * @param delta  - amount of frame time plus lag (in ms)
 * @param border - four walls
 * @param paddle - user paddle
 * @param paddle2 - comptuer paddle
 */
void render(sf::RenderWindow &window, std::shared_ptr<BallClass> ball, float delta, Borders border, MoveBlock paddle, MoveBlock paddle2) {
    // Render drawing objects
    // ------------------------------------------------
    // clear the window with the background color
    window.clear(WINDOW_COLOR);

    // draw the ball
    // ------------------------------------------------
    sf::CircleShape circle;
    circle.setFillColor(ball->color);
    circle.setRadius(ball->radius);
    // set screen coordinates relative to the center of the circle
    circle.setOrigin(ball->radius, ball->radius);
    // calculate current drawing location relative to speed and frame-time
    float xPosition = ball->coordinateX + ball->velocityX * delta;
    float yPosition = ball->coordinateY + ball->velocityY * delta;
    circle.setPosition(xPosition, yPosition);
    window.draw(circle);

    // draw walls
    // -------------------------------------------------
    window.draw(border.bottomWall.rectShape);
    window.draw(border.leftWall.rectShape);
    window.draw(border.rightWall.rectShape);
    window.draw(border.topWall.rectShape);

    // calculate current drawing location relative to speed and frame-time
    float paddleCoordX = paddle.location.left + paddle.velocityX * delta;
    float paddleCoordY = paddle.location.top + paddle.velocityY * delta;


    // draw user paddle
    paddle.location.rectShape.setPosition(paddleCoordX, paddleCoordY);
    window.draw(paddle.location.rectShape);

    // calculate current drawing location relative to speed and frame-time
    float computerPaddleX = paddle2.location.left + paddle2.velocityX * delta;
    float computerPaddleY = paddle2.location.top + paddle2.velocityY * delta;

    // draw AI paddle
    paddle2.location.rectShape.setPosition(computerPaddleX, computerPaddleY);
    window.draw(paddle2.location.rectShape);

    // show the new window
    // ------------------------------------------------
    window.display();
} // end render




#endif //PONGFINAL_FUNCTIONS_H