#include "GameManager.h"
#include <SFML/Window.hpp>
#include "Screen_Classic.h"
#include "Credit.h"
#include "Screen_Modern.h"

using namespace sf;

using std::cin;
using std::cout;

void GameManager::start()
{
    RenderWindow window(VideoMode(width_board + width_UI, height_board), "Snake Game!", Style::Titlebar | Style::Close);
    window.setPosition(Vector2i(10, 10));

    sf::Font font_arcade;
    sf::Font font_gomarice;
    sf::Font font_manaspc;
    sf::Font font_invasion;

    if (!font_arcade.loadFromFile("Fonts/ARCADECLASSIC.TTF")) std::cout << "Cannot load font ARCADECLASSIC.TTF\n";
    if (!font_gomarice.loadFromFile("Fonts/gomarice_game_continue_02.ttf")) std::cout << "Cannot load font gomarice_game_continue_02.ttf\n";
    if (!font_invasion.loadFromFile("Fonts/INVASION2000.TTF")) std::cout << "Cannot load font INVASION2000.TTF\n";
    if (!font_manaspc.loadFromFile("Fonts/manaspc.ttf")) std::cout << "Cannot load font manaspc.ttf\n";

    Selection mainMenu(&window, width_board + width_UI, height_board);
    mainMenu.setTitle_String("Snake Game");
    mainMenu.setTitle_Font(font_gomarice);
    mainMenu.setTitle_Color(Color::Green);
    mainMenu.setTitle_Size(120);
    mainMenu.setOptions_List(new vector<std::string>{"Quit", "Credit", "High Score", "Start"});
    mainMenu.setOption_Font(font_arcade);
    mainMenu.setOption_Color(Color::Yellow);
    mainMenu.setOption_Size(80);
    mainMenu.load();

    Selection chooseLevel(&window, width_board + width_UI, height_board);
    chooseLevel.setTitle_String("Choose a level");
    chooseLevel.setTitle_Font(font_gomarice);
    chooseLevel.setTitle_Color(Color::White);
    chooseLevel.setTitle_Size(100);
    chooseLevel.setOptions_List(new vector<std::string>{ "Challenge", "Modern", "Classic" });
    chooseLevel.setOption_Font(font_arcade);
    chooseLevel.setOption_Color(Color::White);
    chooseLevel.setOption_Size(72);

    while (mainMenu.getOption() != 0)
    {
        if (mainMenu.getOption() == 1) // Credit
        {
            Credit credit(&window, width_board + width_UI, height_board);

            credit.load();
        }
        else if (mainMenu.getOption() == 2) // High Score Board
        {
            cout << "Launch High Score Board\n";

			high_score_board high(&window, width_board + width_UI, height_board);

			high.load();
        }
        else if (mainMenu.getOption() == 3) // Start
        {
            cout << "Choose Level\n";
            chooseLevel.load();
            int lv = chooseLevel.getOption();
            if (lv == 0)
            {
                cout << "Start screen challenge\n";
            }
            else if (lv == 1)
            {
                cout << "Start screen modern\n";
            }
            else if (lv == 2)
            {
                Screen_Classic screen_classic(&window, N, M, img_size, width_UI);

                if (screen_classic.start() == 1)
                {
                    if (!window.isOpen()) { cout << "Window has been closed\n"; break; }
                    else
                    {
                        mainMenu.op = 3;
                        continue;
                    }
                }
            }
            else cout << "ERROR: Out of range\n";
        }
        else cout << "ERROR: Out of range\n";

        if (!window.isOpen())
        {
            cout << "Window has been closed\n";
            break;
        }
        else mainMenu.load();
    }

    if (!window.isOpen()) { window.close(); }
}

int main()
{
    GameManager gameManager;
    gameManager.start();
}