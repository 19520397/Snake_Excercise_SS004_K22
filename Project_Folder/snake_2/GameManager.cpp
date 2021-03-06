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
	mainMenu.setTitle_Outline(Color::Red, 2.0f);
	mainMenu.setOptions_List(new vector<std::string>{ "Quit", "Credit", "High Score", "Start" });
	mainMenu.setOption_Font(font_arcade);
	mainMenu.setOption_Color(Color::Blue);
	mainMenu.setOption_Size(80);
	mainMenu.setOption_OutLine(Color::Yellow, 2.0f);
	mainMenu.setCursor_Outline(Color::Red, 3.0f);

	Selection chooseLevel(&window, width_board + width_UI, height_board);
	chooseLevel.setTitle_String("Choose a level");
	chooseLevel.setTitle_Font(font_gomarice);
	chooseLevel.setTitle_Color(Color::White);
	chooseLevel.setTitle_Size(100);
	chooseLevel.setTitle_Outline(Color::Red, 2.0f);
	chooseLevel.setOptions_List(new vector<std::string>{"Modern", "Classic" });
	chooseLevel.setOption_Font(font_arcade);
	chooseLevel.setOption_Color(Color::White);
	chooseLevel.setOption_Size(72);
	chooseLevel.setOption_OutLine(Color::Red, 2.0f);
	chooseLevel.setCursor_Outline(Color::Red, 3.0f);

	while (window.isOpen() )
	{
		mainMenu.load();
		if (mainMenu.getOption() == 0) break; // Quit
		else if (mainMenu.getOption() == 1) // Credit
		{
			Credit credit(&window, width_board + width_UI, height_board);

			credit.load();
		}
		else if (mainMenu.getOption() == 2) // High Score Board
		{
			cout << "Launch High Score Board\n";
			high_score_board* high = new high_score_board(&window, width_board + width_UI, height_board);
			
			high->load();

			delete high;
		}
		else if (mainMenu.getOption() == 3) // Start
		{
			cout << "Choose Level\n";
			int lv = chooseLevel.load();
			if (lv == 3)
			{
				cout << "Start screen challenge\n";
			}
			else if (lv == 0)
			{
				cout << "Start screen modern\n";
				Screen_Modern* screen_modern = new Screen_Modern(&window, N, M, img_size, width_UI);
				screen_modern->print_Tips();
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
				else delete screen_modern;
			}
			else if (lv == 1)
			{
				cout << "Start Screen Classic\n";
				Screen_Classic* screen_classic = new Screen_Classic(&window, N, M, img_size, width_UI);
				screen_classic->print_Tips();
				if (screen_classic->start() == 1)
				{
					delete screen_classic;
					if (!window.isOpen()) {
						cout << "Window has been closed\n"; 
						break;
					}
					else
					{
						mainMenu.op = 3;
						continue;
					}
				}
				else delete screen_classic;
			}
			else if (!window.isOpen())
			{
				cout << "Window has been closed\n";
			}
			else cout << "ERROR: Out of range\n";
		}
		else if (!window.isOpen())
		{
			cout << "Window has been closed\n";
		}
		else cout << "ERROR: Out of range\n";
		
	}

	if (!window.isOpen()) { window.close(); }
}

int main()
{
	GameManager gameManager;
	gameManager.start();
}