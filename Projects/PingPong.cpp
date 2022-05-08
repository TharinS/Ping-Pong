#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

bool PlayerOutofBounds(float PlayerPos, float ScreenBounds) {
    if ((PlayerPos > ScreenBounds) || (PlayerPos < 0)) {
        return false;
    } else {
        return true;
    }
}

bool Player_AI_Path(sf::Vector2f Momentum, sf::Vector2f Position) {
    while (true) {
        if ((Position.x = 20) && ((Position.y <= 600) && (Position.y >= 0))) {
            return true;
        } else {
            Position.x += Momentum.x;
            Position.y += Momentum.y;
        }
    }
}

sf::Vector2f Player_AI_Pos(sf::Vector2f Momentum, sf::Vector2f Position) {
    while (true) {
        if ((Position.x = 20) && ((Position.y <= 600) && (Position.y >= 0))) {
            return Position;
        } else {
            Position.x += Momentum.x;
            Position.y += Momentum.y;
        }
    }
}

bool AI_Path(sf::Vector2f Momentum, sf::Vector2f Position) {
    while (true) {
        if ((Position.x = 780) && ((Position.y <= 600) && (Position.y >= 0))) {
            return true;
        } else {
            Position.x += Momentum.x;
            Position.y += Momentum.y;
        }
    }
    return false;
}

sf::Vector2f AI_Pos(sf::Vector2f Momentum, sf::Vector2f Position) {
    while (true) {
        if ((Position.x = 780) && ((Position.y <= 600) && (Position.y >= 0))) {
            return Position;
        } else {
            Position.x += Momentum.x;
            Position.y += Momentum.y;
        }
    }
}

int main() {
    bool StartGame = false;
    bool EndGame = false;

    srand(time(NULL));

    sf::RenderWindow Window(sf::VideoMode(800, 600), "Ping Pong", sf::Style::Default | sf::Style::Resize);
    Window.setFramerateLimit(60);

    sf::Font TextFont;
    if (!TextFont.loadFromFile("Fonts\\PlayfairDisplay-Bold.ttf")) {
        cout << "Font file could not be loaded" << endl;
    }

    sf::Text TextStart;
    TextStart.setFont(TextFont);
    TextStart.setFillColor(sf::Color::White);
    TextStart.setCharacterSize(25);
    TextStart.setString("Press Space to Start\n Dont let ball touch the red\nUp to move up\nDown to move down\nGood Luck\n\nGo to code and uncomment\n lines 216 - 221 to see AI vs AI");
    TextStart.setOrigin(TextStart.getLocalBounds().left + TextStart.getLocalBounds().width / 2, TextStart.getLocalBounds().top + TextStart.getLocalBounds().height / 2);
    TextStart.setPosition(sf::Vector2f(399, 249));
    TextStart.setOutlineColor(sf::Color(191, 191, 191, 255));
    TextStart.setOutlineThickness(2.5);

    sf::Text TextEnd;
    TextEnd.setFont(TextFont);
    TextEnd.setFillColor(sf::Color::White);
    TextEnd.setCharacterSize(25);
    TextEnd.setString("Press R to Play Again or Q to Quit\n\nGo to code and uncomment\n lines 194 - 199 to see AI vs AI");
    TextEnd.setOrigin(TextEnd.getLocalBounds().left + TextEnd.getLocalBounds().width / 2, TextEnd.getLocalBounds().top + TextEnd.getLocalBounds().height / 2);
    TextEnd.setPosition(sf::Vector2f(399, 249));
    TextEnd.setOutlineColor(sf::Color(191, 191, 191, 255));
    TextEnd.setOutlineThickness(2.5);

    // Background Sprite
    sf::Texture Background;
    if (!Background.loadFromFile("Assets\\PPBackGround.png")) {
        cout << "Background texture could not be loaded" << endl;
    }

    sf::Sprite BackgroundSprite;
    BackgroundSprite.setTexture(Background);
    BackgroundSprite.setPosition(sf::Vector2f(0, 0));

    // Player Paddle Sprite
    sf::RectangleShape PlayerPaddle;
    PlayerPaddle.setPosition(sf::Vector2f(20, 50 + rand() % 500));
    PlayerPaddle.setSize(sf::Vector2f(10, 50));
    PlayerPaddle.setFillColor(sf::Color::White);
    PlayerPaddle.setOrigin(sf::Vector2f(5, 25));

    // AI Paddle Sprite
    sf::RectangleShape AIPaddle;
    AIPaddle.setPosition(sf::Vector2f(780, 50 + rand() % 500));
    AIPaddle.setSize(sf::Vector2f(10, 50));
    AIPaddle.setFillColor(sf::Color::White);
    AIPaddle.setOrigin(sf::Vector2f(5, 25));

    // Ball
    sf::CircleShape Ball;
    Ball.setRadius(10);
    Ball.setPosition(sf::Vector2f(400, 300));
    Ball.setOrigin(sf::Vector2f(5, 5));
    //
    float DirectionX = 10, DirectionY = 10;

    // Hit Boxes for the Walls
    sf::RectangleShape Wall[2];
    for (int i = 0; i < 2; i++) {
        Wall[i].setFillColor(sf::Color::Red);
        Wall[i].setSize(sf::Vector2f(7, 600));
    }
    Wall[0].setPosition(sf::Vector2f(0, 0));
    Wall[1].setPosition(sf::Vector2f(793, 0));

    sf::Clock DClock;
    while (Window.isOpen()) {
        // Window.clear();
        // Drawing Background
        Window.draw(BackgroundSprite);
        sf::Event EVNT;
        while (Window.pollEvent(EVNT)) {
            switch (EVNT.type) {
                case EVNT.Closed:
                    Window.close();
                    break;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !StartGame) {
            StartGame = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && EndGame) {
            StartGame = true;
            EndGame = false;
            Ball.setPosition(sf::Vector2f(400, 300));
            DirectionX = 10 * ((rand() % 10 > 5) ? -1 : 1), DirectionY = 10 * ((rand() % 10 > 5) ? -1 : 1);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && EndGame) {
            Window.close();
        }

        if (StartGame) {
            sf::Time deltaTime = DClock.restart();

            // KeyBoard Input
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                if (PlayerOutofBounds(PlayerPaddle.getPosition().y - 20.0, Window.getSize().y)) {
                    PlayerPaddle.move(sf::Vector2f(0, -20.0));
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                if (PlayerOutofBounds(PlayerPaddle.getPosition().y + 20.0, Window.getSize().y)) {
                    PlayerPaddle.move(sf::Vector2f(0, 20.0));
                }
            }

            // Ball Movement
            Ball.move(sf::Vector2f(DirectionX, DirectionY));
            // Ball and Wall Collision Code
            if ((Ball.getPosition().x >= 800)) {
                Ball.move(sf::Vector2f(DirectionX *= -1, 0));
            }
            if ((Ball.getPosition().y >= 600)) {
                Ball.move(sf::Vector2f(0, DirectionY *= -1));
            }
            if ((Ball.getPosition().x <= 0)) {
                Ball.move(sf::Vector2f(DirectionX *= -1, 0));
            }
            if ((Ball.getPosition().y <= 0)) {
                Ball.move(sf::Vector2f(0, DirectionY *= -1));
            }
            // Ball and Player Collision Code
            if (Ball.getGlobalBounds().intersects(PlayerPaddle.getGlobalBounds())) {
                Ball.move(sf::Vector2f(DirectionX *= -1, DirectionY *= 1));
            }
            // Ball and EndZone Collision Code
            if ((Ball.getGlobalBounds().intersects(Wall[0].getGlobalBounds())) || (Ball.getGlobalBounds().intersects(Wall[1].getGlobalBounds()))) {
                DirectionY = 0, DirectionX = 0;
                EndGame = true;
            }
            // Ball and AI Collision Code
            if (AI_Path(sf::Vector2f(DirectionX, DirectionY), Ball.getPosition())) {
                AIPaddle.setPosition(AI_Pos(sf::Vector2f(DirectionX, DirectionY), Ball.getPosition()));
                if (Ball.getGlobalBounds().intersects(AIPaddle.getGlobalBounds())) {
                    Ball.move(sf::Vector2f(DirectionX *= -1, DirectionY *= 1));
                }
            }

            // Player AI Movement Uncomment the code below then compile to see AI vs AI
            // if (Player_AI_Path(sf::Vector2f(DirectionX, DirectionY), Ball.getPosition())) {
            //     PlayerPaddle.setPosition(Player_AI_Pos(sf::Vector2f(DirectionX, DirectionY), Ball.getPosition()));
            //     if (Ball.getGlobalBounds().intersects(PlayerPaddle.getGlobalBounds())) {
            //         Ball.move(sf::Vector2f(DirectionX *= -1, DirectionY *= 1));
            //     }
            // }
        }

        // Player Sprite
        if (!StartGame && !EndGame) {
            Window.draw(TextStart);
        }
        if (StartGame && EndGame) {
            Window.draw(TextEnd);
        }
        Window.draw(PlayerPaddle);
        Window.draw(Ball);
        Window.draw(AIPaddle);
        for (int i = 0; i < 2; i++) {
            Window.draw(Wall[i]);
        }
        Window.display();
    }
}