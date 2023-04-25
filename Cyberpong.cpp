#include <iostream>

int main() {
    // create a 2d graphics window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "HelloSFML");
    window.clear(WINDOW_COLOR);

    // declare a ball variable
    Ball theBall;

    // declare the borders and the moving block
    std::vector<Borders> walls(NUM_WALLS);
    Moving_block user;
    Moving_block aiPlayer;

    // declare the paddle
    Paddle userSpecs;

    // set up the game
    setup(theBall, walls[0], user, aiPlayer, userSpecs);

    // timing variables for the main game loop
    sf::Clock clock;
    sf::Time startTime = clock.getElapsedTime();
    sf::Time stopTime = startTime;
    float delta = 0.0;

    bool started = false, game_Over = false, gameOver = false;

    sf::Event event;
    while (!gameOver) {
        // calculate frame time
        stopTime = clock.getElapsedTime();
        delta += (stopTime.asMilliseconds() - startTime.asMilliseconds());
        startTime = stopTime;

        // process events
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    gameOver = true;
                    break;
            }
        }

        // process user input
        const direction userInput = processInput();
        if (userInput == -1) {
            gameOver = true;
        }

        // process updates
        if (delta >= FRAME_RATE) {
            gameOver = update(userInput, theBall, walls[0], user, aiPlayer, userSpecs, started, game_Over, delta);
            while (delta >= FRAME_RATE) {
                delta -= FRAME_RATE;
            }
        }

        // render the window
        render(window, theBall, walls[0], user, aiPlayer, userSpecs, delta);
    }

    // game ending, close the graphics window
    window.close();
    return 0;
}
void setup(Ball& ball, Borders& theWalls, Moving_block& user, Moving_block& aiPlayer, const Paddle& userSpecs) {

    theWalls.leftWall.left = 0.0;
    theWalls.leftWall.top = 0.0;
    theWalls.leftWall.width = Block_Thickness;
    theWalls.leftWall.height = WINDOW_HEIGHT;
    theWalls.leftWall.rectangle.setSize(sf::Vector2(theWalls.leftWall.width, theWalls.leftWall.height));
    theWalls.leftWall.rectangle.setPosition(theWalls.leftWall.left, theWalls.leftWall.top);
    theWalls.leftWall.rectangle.setFillColor(Block_Color);

    theWalls.rightWall.left = WINDOW_WIDTH - Block_Thickness;
    theWalls.rightWall.top = 0.0;
    theWalls.rightWall.width = Block_Thickness;
    theWalls.rightWall.height = WINDOW_HEIGHT;
    theWalls.rightWall.rectangle.setSize(sf::Vector2(theWalls.rightWall.width, theWalls.rightWall.height));
    theWalls.rightWall.rectangle.setPosition(theWalls.rightWall.left, theWalls.rightWall.top);
    theWalls.rightWall.rectangle.setFillColor(Block_Color);

    theWalls.topWall.left = 0.0;
    theWalls.topWall.top = 0.0;
    theWalls.topWall.width = WINDOW_WIDTH;
    theWalls.topWall.height = Block_Thickness;
    theWalls.topWall.rectangle.setSize(sf::Vector2(theWalls.topWall.width, theWalls.topWall.height));
    theWalls.topWall.rectangle.setPosition(theWalls.topWall.left, theWalls.topWall.top);
    theWalls.topWall.rectangle.setFillColor(Block_Color);

    theWalls.bottomWall.left = 0.0;
    theWalls.bottomWall.top = WINDOW_HEIGHT - Block_Thickness;
    theWalls.bottomWall.width = WINDOW_WIDTH;
    theWalls.bottomWall.height = Block_Thickness;
    theWalls.bottomWall.rectangle.setSize(sf::Vector2(theWalls.bottomWall.width, theWalls.bottomWall.height));
    theWalls.bottomWall.rectangle.setPosition(theWalls.bottomWall.left, theWalls.bottomWall.top);
    theWalls.bottomWall.rectangle.setFillColor(Block_Color);

    // users paddle
    user.usersPaddle.left = userSpecs.PaddleThickness;
    user.usersPaddle.top = (WINDOW_HEIGHT - userSpecs.PaddleHeight) / 2.0f;
    user.usersPaddle.width = userSpecs.PaddleThickness;
    user.usersPaddle.height = userSpecs.PaddleHeight;
    user.usersPaddle.Color = userSpecs.paddleColor;
    user.usersPaddle.rectangle.setSize(sf::Vector2(user.usersPaddle.width, user.usersPaddle.height));
    user.usersPaddle.rectangle
    direction processInput() {
        direction input = None;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            input = LEFT;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            input = UP;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            input = RIGHT;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            input = DOWN;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
            input = EXIT;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            input = Start;
        }
        return input;
    }

    bool update(direction &input, Ball &ball, Borders theWalls, Moving_block &user, Moving_block &aiPlayer, bool &started, bool &game_Over, float delta) {
        game_Over = false;
        if (input) {
            switch (input) {
                case LEFT:
                    ball.velocityX -= BALL_SPEED_X;
                    break;
                case UP:
                    user.velocityY -= userSpecs.PaddleSpeed;
                    ball.velocityY -= BALL_SPEED_Y;
                    break;
                case RIGHT:
                    ball.velocityX += BALL_SPEED_X;
                    break;
                case DOWN:
                    user.velocityY += userSpecs.PaddleSpeed;
                    break;
                case Start:
                    if (!started) {
                        ball.velocityX = BALL_SPEED_X;
                        ball.velocityY = BALL_SPEED_Y;
                        if ((int(delta * 10) & 1) % 2) {
                            ball.velocityX *= -1;
                        }
                        started = true;
                    }
                    break;
            }
            input = None;
        }

        user.usersPaddle.top += user.velocityY * delta;
        aiPlayer.usersPaddle.top += aiPlayer.velocityY * delta;

        if (started) {
            ball.coordinateX += ball.velocityX * delta;
            ball.coordinateY += ball.velocityY * delta;
            if (ball.coordinateY < aiPlayer.usersPaddle.top + aiPlayer.usersPaddle.height / 2.0f) {
                aiPlayer.velocityY -= userSpecs.PaddleSpeed;
            }
            else if (ball.coordinateY > aiPlayer.usersPaddle.top + aiPlayer.usersPaddle.height / 2.0f) {
                aiPlayer.velocityY
