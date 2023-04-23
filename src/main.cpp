#include "alpha.h"

const char  back_file_name [] = "back.bmp";
const char front_file_name [] = "cat.bmp";

int main ()
{
    FILE * back_file = fopen ( back_file_name, "rb");
    FILE *front_file = fopen (front_file_name, "rb");

    BmpImage  back_img = {};
    BmpImage front_img = {};

    LoadImage (back_file , &back_img );
    LoadImage (front_file, &front_img);

    fclose ( back_file);
    fclose (front_file);

    DrawAlpha (&back_img, &front_img);

    ImgDtor (& back_img);
    ImgDtor (&front_img);

    return 0;
}

void DrawAlpha (BmpImage *back_img, BmpImage *front_img)
{
    const int W = back_img -> width;
    const int H = back_img -> height;

    sf::Clock fps_clk;

    sf::Sprite sprite;
    sf::Texture texture;
    sf::Image img;
    img.create (W, H);

    sf::Font font;
    sf::Text fps;
    font.loadFromFile (font_file_name);
    fps.setPosition (0, 0);
    fps.setFont (font);
    fps.setFillColor (sf::Color::Red);
    fps.setCharacterSize (20);
    char fps_str [BUFSIZE] = "";

    sf::RenderWindow window(sf::VideoMode(W, H), "eeeeeeee");

    while (window.isOpen ())
    {
        sf::Event event;
        while (window.pollEvent (event))
        {
            if (event.type == sf::Event::Closed)
                window.close ();
            
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close ();
            }
        }

        fps_clk.restart ();

        Blend (back_img, front_img, img);

        sprintf (fps_str, "%.3f", 1 / fps_clk.restart().asSeconds());
        fps.setString (fps_str);

        texture.loadFromImage (img);
        sprite.setTexture (texture);

        window.clear ();
        window.draw (sprite);
        window.draw (fps);
        window.display ();
    }
}
