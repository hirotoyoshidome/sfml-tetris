#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

const int FIELD_SIZE_X = 10;
const int FIELD_SIZE_Y = 20;
const int TILE_SIZE = 30;

int main() {
    RenderWindow window(VideoMode(FIELD_SIZE_X * TILE_SIZE, FIELD_SIZE_Y * TILE_SIZE), "TETRIS");
    // CircleShape shape(100.f);
    // shape.setFillColor(Color::Green);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        // window.draw(shape);
        window.display();
    }

    return 0;
}
