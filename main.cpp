#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <vector>

using namespace sf;
using namespace std;

const int FIELD_SIZE_X = 10;
const int FIELD_SIZE_Y = 20;
const int TILE_SIZE = 30;
const int WIDTH = FIELD_SIZE_X * TILE_SIZE;
const int HEIGHT = FIELD_SIZE_Y * TILE_SIZE;
const int CENTER_WIDTH = WIDTH / 2 - TILE_SIZE;

const int DOWN_CYCLE = 1;
const int BUTTOM = HEIGHT - TILE_SIZE;

const IntRect GREEN_BLOCK = IntRect(0, 0, TILE_SIZE, TILE_SIZE);
const IntRect YELLOW_BLOCK = IntRect(TILE_SIZE, 0, TILE_SIZE, TILE_SIZE);
const IntRect RED_BLOCK = IntRect(TILE_SIZE*2, 0, TILE_SIZE, TILE_SIZE);


class BaseBlock
{
public:

    Texture tiles;
    Sprite block;
    IntRect color;
    int position[2];

public:

    auto move_left_block();
    auto move_right_block();
    auto move_up_block();
    auto move_down_block();

    void init()
    {
        tiles.loadFromFile("images/tiles.png");
        position[0] = CENTER_WIDTH;
        position[1] = 0;
    }
};

class TetrisBlock : public BaseBlock
{
public:
    void move_left_block()
    {
        std::cout << "left" << position[0] << std::endl;
        position[0] = position[0] - TILE_SIZE;
        if (position[0] < 0) position[0] = 0;
        block.setPosition(position[0], position[1]);
    }

    void move_right_block()
    {
        std::cout << "right" << position[0] << std::endl;
        position[0] = position[0] + TILE_SIZE;
        if (position[0] > WIDTH - TILE_SIZE) position[0] = WIDTH - TILE_SIZE;
        block.setPosition(position[0], position[1]);
    }

    void move_up_block()
    {
        std::cout << "up" << position[1] << std::endl;
        position[1] = position[1] - TILE_SIZE;
        if (position[1] < 0) position[1] = 0;
        block.setPosition(position[0], position[1]);
    }

    void move_down_block()
    {
        std::cout << "down" << position[1] << std::endl;
        position[1] = position[1] + TILE_SIZE;
        if (position[1] > BUTTOM) position[1] = BUTTOM;
        block.setPosition(position[0], position[1]);
    }
};











int main()
{
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "TETRIS");
    // // text
    // Font font;
    // font.loadFromFile("fonts/arial.ttf");
    // Text text;
    // text.setFont(font);
    // text.setString("hello");
    // text.setCharacterSize(24);
    // text.setFillColor(Color::Red);
    // text.setPosition(100, 100);

    vector<TetrisBlock> blocks;

    TetrisBlock block;
    block.init();
    block.color = GREEN_BLOCK;
    Sprite s(block.tiles);
    s.setTextureRect(block.color);
    s.setPosition(block.position[0], block.position[1]);
    block.block = s;

    blocks.push_back(block);

    // tiem.
    Clock clock;
    float tm;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        tm += time;

        Event event;
        // bg-color.
        window.clear(Color::White);

        TetrisBlock active = blocks[blocks.size()-1];
        blocks.pop_back();

        // close.
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Left) active.move_left_block();
                if (event.key.code == Keyboard::Right) active.move_right_block();
                if (event.key.code == Keyboard::Up) active.move_up_block();
                if (event.key.code == Keyboard::Down) active.move_down_block();
            }
        }

        if (tm > DOWN_CYCLE) {
            active.move_down_block();
            tm = 0;
        }

        blocks.push_back(active);

        if (active.position[1] >= BUTTOM) {
            TetrisBlock new_block;
            new_block.init();
            new_block.color = YELLOW_BLOCK;
            Sprite new_s(new_block.tiles);
            new_s.setTextureRect(new_block.color);
            new_s.setPosition(new_block.position[0], new_block.position[1]);
            new_block.block = new_s;

            blocks.push_back(new_block);
            // window.draw(new_s);
        }

        // draw.
        for (int i = 0; i < blocks.size(); i++) {
            window.draw(blocks[i].block);
        }
        window.display();
    }

    return 0;
}
