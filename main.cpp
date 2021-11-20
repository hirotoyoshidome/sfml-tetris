#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

const int FIELD_SIZE_X = 10;
const int FIELD_SIZE_Y = 20;
const int TILE_SIZE = 30;
const int WIDTH = FIELD_SIZE_X * TILE_SIZE;
const int HEIGHT = FIELD_SIZE_Y * TILE_SIZE;
const int CENTER_WIDTH = WIDTH / 2 - TILE_SIZE;

const IntRect GREEN_BLOCK = IntRect(0, 0, TILE_SIZE, TILE_SIZE);
const IntRect YELLOW_BLOCK = IntRect(TILE_SIZE, 0, TILE_SIZE, TILE_SIZE);
const IntRect RED_BLOCK = IntRect(TILE_SIZE*2, 0, TILE_SIZE, TILE_SIZE);

Sprite move_left_block(Sprite s, int position[]) {
    std::cout << "left" << position[0] << std::endl;
    position[0] = position[0] - TILE_SIZE;
    if (position[0] < 0) position[0] = 0;
    s.setPosition(position[0], position[1]);
    return s;
}

Sprite move_right_block(Sprite s, int position[]) {
    std::cout << "right" << position[0] << std::endl;
    position[0] = position[0] + TILE_SIZE;
    if (position[0] > WIDTH - TILE_SIZE) position[0] = WIDTH - TILE_SIZE;
    s.setPosition(position[0], position[1]);
    return s;
}

Sprite move_up_block(Sprite s, int position[]) {
    std::cout << "up" << position[1] << std::endl;
    position[1] = position[1] - TILE_SIZE;
    if (position[1] < 0) position[1] = 0;
    s.setPosition(position[0], position[1]);
    return s;
}

Sprite move_down_block(Sprite s, int position[]) {
    std::cout << "down" << position[1] << std::endl;
    position[1] = position[1] + TILE_SIZE;
    if (position[1] > HEIGHT - TILE_SIZE) position[1] = HEIGHT - TILE_SIZE;
    s.setPosition(position[0], position[1]);
    return s;
}

int main() {
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "TETRIS");

    // image.
    Texture t;
    t.loadFromFile("images/tiles.png");

    // // text
    // Font font;
    // font.loadFromFile("fonts/arial.ttf");
    // Text text;
    // text.setFont(font);
    // text.setString("hello");
    // text.setCharacterSize(24);
    // text.setFillColor(Color::Red);
    // text.setPosition(100, 100);
    
    // tmp position.
    int position[2] = {CENTER_WIDTH, 0};
    // block
    Sprite s(t);
    s.setTextureRect(GREEN_BLOCK);
    s.setPosition(position[0], position[1]);

    // window.
    while (window.isOpen())
    {
        Event event;
        // bg-color.
        window.clear(Color::White);

        // close.
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Left) s = move_left_block(s, position);
                if (event.key.code == Keyboard::Right) s = move_right_block(s, position);
                if (event.key.code == Keyboard::Up) s = move_up_block(s, position);
                if (event.key.code == Keyboard::Down) s = move_down_block(s, position);
            }
        }

        // draw.
        window.draw(s);
        // window.draw(text);

        window.display();
    }

    return 0;
}
