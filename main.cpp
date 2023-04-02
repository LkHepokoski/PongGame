/* --------------------------------------------------------
 *    File: main.cpp
 *  Author: Luke Hepokoski
 *   Class: COP 2006 Spring 2022 CRN 13969
 * Purpose: finishing pong game
 * -------------------------------------------------------- */
#include <SFML/Graphics.hpp>
#include "pong_defs.h"
#include "functions.h"


/**
 * The main application
 * @return OS stats message (0=Success)
 */
int main() {

    // create a 2d graphics window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Hello SFML");
    window.clear(WINDOW_COLOR);

    // declare a MoveBlock variable for user and computer paddles
    MoveBlock playerPaddle;
    MoveBlock computerPaddle;

    // declare a Ball and Border variable for ball and walls
    Ball theBall;
    Borders theWalls;
    setup(theBall, theWalls, playerPaddle, computerPaddle);


    // timing variables for the main game loop
    sf::Clock clock;
    sf::Time startTime = clock.getElapsedTime();
    sf::Time stopTime = startTime;
    float delta = 0.0;

    bool started = false;
    bool gameOver = false;
    while (!gameOver) {
        // calculate frame time
        stopTime = clock.getElapsedTime();
        delta += stopTime.asMilliseconds() - startTime.asMilliseconds();
        startTime = stopTime;

        // process events
        sf::Event event;
        while (!gameOver && window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                gameOver = true;
        }

        // Process user input
        // ------------------------------------------------
        Direction userInput = processInput();
        if (userInput == Exit)
            gameOver = true;

        // Process Updates
        // ------------------------------------------------
        if (delta >= FRAME_RATE) {    // if we have made it at least a full frame time

            // ends game if update returns true
            gameOver = update(userInput, theBall, theWalls, playerPaddle, delta, started, computerPaddle);

            // subtract the frame-rate from the current frame-time
            // for each full frame covered by this update
            while (delta >= FRAME_RATE)
                delta -= FRAME_RATE;
        }

        // Render the window
        // ------------------------------------------------
        render(window, theBall, delta, theWalls, playerPaddle, computerPaddle);

    } // end main game loop

    // game ending, close the graphics window
    window.close();

    return 0;   // return success to the OS
} // end main

