#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <vector>
#include <random>
#include <string>

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


#define ARRAY_LENGTH(array) (sizeof(array) / sizeof(array[0]))


class BaseBlock
{
public:

    Sprite block;
    int position[2];

public:

    auto move_left_block();
    auto move_right_block();
    auto move_up_block();
    auto move_down_block();

    void init()
    {
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


IntRect getColor()
{
    std::random_device rd;
    int t = rd() % 3;
    if (t == 0) return GREEN_BLOCK;
    if (t == 1) return YELLOW_BLOCK;
    if (t == 2) return RED_BLOCK;
}








int main()
{
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "TETRIS");

    // tiles.
    Texture tiles;
    tiles.loadFromFile("images/tiles.png");

    // bg-text.
    Font font;
    font.loadFromFile("fonts/arial.ttf");
    Text text;
    text.setFont(font);
    std::string bgtext = "tetris";
    text.setString(bgtext);
    int fontsize = 16;
    text.setCharacterSize(fontsize);
    text.setFillColor(Color::Red);
    text.setPosition(WIDTH-fontsize * bgtext.length()/2, 0);

    // blocks.
    vector<TetrisBlock> blocks;

    TetrisBlock block;
    block.init();
    Sprite s(tiles);
    s.setTextureRect(getColor());
    s.setPosition(block.position[0], block.position[1]);
    block.block = s;

    blocks.push_back(block);

    // address.
    int address[FIELD_SIZE_Y][FIELD_SIZE_X] = {
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0}
    };

    // tiem.
    Clock clock;
    float tm;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        tm += time;

        TetrisBlock active = blocks[blocks.size()-1];
        blocks.pop_back();

        Event event;
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
            // set address.
            address[active.position[1] / TILE_SIZE][active.position[0] / TILE_SIZE] = 1;

            // create new block.
            TetrisBlock new_block;
            new_block.init();
            Sprite new_s(tiles);
            new_s.setTextureRect(getColor());
            new_s.setPosition(new_block.position[0], new_block.position[1]);
            new_block.block = new_s;
            blocks.push_back(new_block);

            for (int i = 0; i < ARRAY_LENGTH(address); i++) {
                for (int j = 0; j < ARRAY_LENGTH(address[i]); j++) {
                    cout << address[i][j] << ", ";
                }
                cout << " " << endl;
            }

        }

        window.clear(Color::White);

        // draw.
        window.draw(text);
        for (int i = 0; i < blocks.size(); i++) {
            window.draw(blocks[i].block);
        }
        window.display();
    }

    return 0;
}
