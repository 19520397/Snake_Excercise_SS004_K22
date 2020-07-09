#pragma once
#include <SFML/Graphics.hpp>
#include <string.h>
#include <iostream>

using std::cout;
class high_score_board
{
private:
	sf::RenderWindow* window;
	sf::Font* font;
	sf::Text* txt;

	float height;
	float width;
public:
	static std::string get_player_name(sf::RenderWindow& window,float width_board, float height_board, int score) {
		cout << "get player name\n";
		sf::Texture t;
		t.create(window.getSize().x, window.getSize().y);
		t.update(window);
		sf::Sprite player_name(t);
		sf::Font font;
		sf::Font font2;

		if (!font.loadFromFile("Fonts/ARCADECLASSIC.TTF"))
		{
			cout << "ERROR: Could not load font";
		}
		if (!font2.loadFromFile("Fonts/MAGNETOB.TTF"))
		{
			cout << "ERROR: Could not load font";
		}

		sf::Text txt;
		txt.setFont(font);
		sf::Text playerText;
		std::string  tmp;
		sf::Text your_scoreTxt;

		while (window.isOpen())
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				while (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					// wait to key up
				}
				break;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
			{
				while (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
				{
					// wait to key up
				}
			}


			window.clear();
			window.draw(player_name);
			txt.setFillColor(sf::Color::Yellow);
			txt.setCharacterSize(100);
			txt.setString("Your name please");
			txt.setPosition((width_board) / 2 - txt.getGlobalBounds().width / 2, height_board / 3 - txt.getGlobalBounds().height / 2);


			your_scoreTxt.setFillColor(sf::Color::Magenta);
			your_scoreTxt.setFont(font);
			your_scoreTxt.setCharacterSize(100);
			your_scoreTxt.setString("Your Score " + std::to_string(score));
			your_scoreTxt.setPosition((width_board) / 2 - your_scoreTxt.getGlobalBounds().width / 2, height_board / 3 - your_scoreTxt.getGlobalBounds().height / 2 - 100);


			playerText.setFillColor(sf::Color::Black);
			playerText.setCharacterSize(100);
			playerText.setFont(font2);



			sf::Event e;

			while (window.pollEvent(e))
			{
				if (e.text.unicode != sf::Keyboard::BackSpace)
				{
					if (e.type == sf::Event::TextEntered)
					{
						tmp.push_back(e.text.unicode);
					}
				}
				else
				{
					if (!tmp.empty())
					{
						tmp.pop_back();
					}
				}
			}

			playerText.setString(tmp);
			playerText.setPosition((width_board) / 2 - playerText.getGlobalBounds().width / 2, height_board / 3 - playerText.getGlobalBounds().height / 2 + 100);
			window.draw(playerText);
			window.draw(your_scoreTxt);
			window.draw(txt);



			window.display();

		}
		cout << "name got\n";
		return tmp;
	}
	high_score_board(sf::RenderWindow* window, float width, float height) : window(window), width(width), height(height)
	{
		font = new sf::Font();
		if (!font->loadFromFile("Fonts/manaspc.ttf"))
		{
			cout << "ERROR: Could not load font";
		}
		txt = new sf::Text();
		txt->setFont(*font);
	}
	void load()
	{
		window->clear();


		txt->setFillColor(sf::Color::Green);
		txt->setCharacterSize(32);

		txt->setPosition(50, 50);
		txt->setString(">Esc<");
		window->draw(*txt);
	

		txt->setCharacterSize(50);
		txt->setFillColor(sf::Color::Yellow);
		txt->setString("Authors :\n ~ Nguyen Pham Duy Bang - Dragnell\n ~ Nguyen Trong Nhan - C0R3M3N\n ~ Vu Ngoc Thach - DragonPow");
		txt->setPosition(100, height / 3 - txt->getGlobalBounds().height);
		window->draw(*txt);

		window->display();
		while (window->isOpen() && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
		{
			// Wait until user want to return
			sf::Event e;
			while (window->pollEvent(e))
			{
				if (e.type == sf::Event::Closed)
					window->close();
			}
		}
		cout << "Back to Main Menu\n";
		return;
	}
};

