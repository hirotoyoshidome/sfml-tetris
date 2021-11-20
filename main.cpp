#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

const int FIELD_SIZE_X = 10;
const int FIELD_SIZE_Y = 20;
const int TILE_SIZE = 30;

int main() {
    RenderWindow window(VideoMode(FIELD_SIZE_X * TILE_SIZE, FIELD_SIZE_Y * TILE_SIZE), "TETRIS");

    // text
    Font font;
    font.loadFromFile("fonts/arial.ttf");
    Text text;
    text.setFont(font);
    text.setString("hello");
    text.setCharacterSize(24);
    text.setFillColor(Color::Red);
    text.setPosition(100, 100);

    // image.
    Texture t;
    t.loadFromFile("images/tiles.png");
    Sprite s(t);
    s.setTextureRect(IntRect(0,0 , TILE_SIZE, TILE_SIZE));
	s.setPosition(200, 100);

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
        }

        // draw.
        window.draw(s);
        window.draw(text);

        window.display();
    }

    return 0;
}
