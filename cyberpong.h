#include <SFML/Graphics.hpp>

#ifndef cyberPONG_DEFS_H
#define cyberPONG_DEFS_H

namespace pong {

// Ball properties
    const float ballRadius = 10.0f;

// Block properties
    const float blockThickness = 10.0f;
    const sf::Color blockColor = sf::Color::Green;

// Window properties
    const int windowWidth = 640;
    const int windowHeight = 480;
    const sf::Color windowColor = sf::Color::White;

// Drawing properties
    const float frameRate = 1000.0f / 60.0f;  // FPS in ms
    const sf::Color ballColor = sf::Color::Blue;

// These are just for fun
// Speed that the ball can accelerate at to span window in
// n-seconds (in ms) broken up for each frame
    const float speedTime = 3.0f * 1000.0f * 30.0f;  //
    const float ballSpeedX = ballRadius * 10.0f / 1000.0f;   // Speed horizontally
    const float ballSpeedY = ballRadius * 8.5f / 1000.0f;   // Span vertically

// Enum
    enum class Direction {
        EXIT = -1,
        None = 0,
        LEFT = 1,
        UP = 2,
        RIGHT = 3,
        DOWN = 4,
        START = 5
    };

// Ball properties
    struct Ball {
        float radius;
        float coordinateX;
        float coordinateY;
        float velocityX;
        float velocityY;
        sf::Color color;
    };

// Block borders for walls
    struct Block {
        float left;
        float top;
        float width;
        float height;
        sf::Color color;
        sf::RectangleShape rectangle;
    };

// Borders for walls
    struct Borders {
        Block leftWall;
        Block topWall;
        Block rightWall;
        Block bottomWall;
    };

    struct MovingBlock {
        Block usersPaddle;
        float velocityX;
        float velocityY;
    };

    class Paddle {
    public:
        const float height = 80.0f;
        const float thickness = 10.0f;
        const sf::Color color = sf::Color::Blue;
        const float speed = height / 10.0f / 100.0f;
    };

}  // namespace pong

#endif  // PONG_DEFS_H
