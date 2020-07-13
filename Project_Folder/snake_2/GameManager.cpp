#include "GameManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "MainMenu.h"
#include "Selection.h"
#include "Screen_Classic.h"
#include "Credit.h"
#include "Screen_Modern.h"

using namespace sf;

using std::cin;
using std::cout;

void GameManager::start()
{
    RenderWindow window(VideoMode(width_board + width_UI, height_board), "Snake Game!", Style::Titlebar | Style::Close);
    window.setPosition(Vector2i(VideoMode::getDesktopMode().width / 2 - window.getSize().x / 2, VideoMode::getDesktopMode().height / 2 - window.getSize().y / 2));

    Selection mainMenu(&window, width_board + width_UI, height_board);
    mainMenu.setTitle_String("Snake Game");
    mainMenu.setTitle_Color(Color::Green);
    mainMenu.setTitle_Size(120);
    mainMenu.setOptions_List(new vector<std::string>{"Quit", "Credit", "High Score", "Start"});
    mainMenu.setOption_Color(Color::Yellow);
    mainMenu.setOption_Size(80);
    mainMenu.load();

    Screen_Classic* screen_game = NULL;

    while (mainMenu.getOption() != 0)
    {
        if (mainMenu.getOption() == 1)
        {
            cout << "Launch Credit\n";

            Credit credit(&window, width_board + width_UI, height_board);

            credit.load();
        }
        else if (mainMenu.getOption() == 2)
        {
            cout << "Launch High Score Board\n";
        }
        else if (mainMenu.getOption() == 4)
        {
            cout << "Launch Screen Classic\n";

            screen_game = new Screen_Classic(&window, N, M, img_size, width_UI);
            screen_game->start();
        }
        else if (mainMenu.getOption() == 3) 
        {
<<<<<<< Updated upstream
            cout << "Launch Screen Modern\n";

            screen_game = new Screen_Modern(&window, N, M, img_size, width_UI);
            screen_game->start();
=======
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
                Screen_Modern* screen_modern = new Screen_Modern(&window, N, M, img_size, width_UI);
                
                if (screen_modern->start() == 1)
                {
                    delete screen_modern;
                    if (!window.isOpen()) { 
                        cout << "Window has been closed\n"; break; 
                    }
                    else
                    {
                        mainMenu.op = 3;
                        continue;
                    }
                }
                delete screen_modern;
            }
            else if (lv == 2)
            {
                Screen_Classic* screen_classic = new Screen_Classic(&window, N, M, img_size, width_UI);

                if (screen_classic->start() == 1)
                {
                    delete screen_classic;
                    if (!window.isOpen()) { 
                        cout << "Window has been closed\n"; break; 
                    }
                    else
                    {
                        mainMenu.op = 3;
                        continue;
                    }
                }
                delete screen_classic;
            }
            else cout << "ERROR: Out of range\n";
>>>>>>> Stashed changes
        }
        else cout << "ERROR: Out of range\n";
        if (!window.isOpen())
        {
            delete screen_game;
            screen_game = NULL;
            cout << "Closed window\n";
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