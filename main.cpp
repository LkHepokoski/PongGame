#include <SFML/Graphics.hpp>
#include "pong_defs.h"
#include "functions.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pong");
    window.setFramerateLimit(60);  // Limit the frame rate to 60 FPS

    MoveBlock playerPaddle;
    MoveBlock computerPaddle;
    Borders theWalls;
    setup(theWalls, playerPaddle, computerPaddle);
    // Create a shared pointer to a ball object
    auto ball = std::make_shared<BallClass>();
    // Set up the ball object
    ball->setup(ball);

    bool started = false;
    bool gameOver = false;
    sf::Clock clock;
    sf::Time startTime, stopTime;
    float delta = 0;

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
            gameOver = update(userInput, ball, theWalls, playerPaddle, delta, started, computerPaddle);

            // subtract the frame-rate from the current frame-time
            // for each full frame covered by this update
            while (delta >= FRAME_RATE)
                delta -= FRAME_RATE;
        }

        // Render the window
        // ------------------------------------------------
        render(window, ball, delta, theWalls, playerPaddle, computerPaddle);

    } // end main game loop

    // game ending, close the graphics window
    window.close();

    return 0;
}