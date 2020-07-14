#pragma once
#include <SFML/Graphics.hpp>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream> 

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
	~high_score_board()
	{
		delete font, txt;
	}
	static std::string get_player_name(sf::RenderWindow& window, float width_board, float height_board, int score) {
		
		cout << "Get player name\n";
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
		if (!font2.loadFromFile("Fonts/Oswald-Medium.ttf"))
		{
			cout << "ERROR: Could not load font";
		}
		std::string  filter("qwertyuioplkjhgfdsazxcvbnm1234567890QWERTYUIOPLKJHGFDSAZXCVBNM ");

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
			txt.setOutlineColor(sf::Color::Blue);
			txt.setOutlineThickness(2.5f);
			txt.setPosition((width_board) / 2 - txt.getGlobalBounds().width / 2, height_board / 3 - txt.getGlobalBounds().height / 2);


			your_scoreTxt.setFillColor(sf::Color::Magenta);
			your_scoreTxt.setFont(font);
			your_scoreTxt.setCharacterSize(100);
			your_scoreTxt.setString("NEW HIGH SCORE");
			your_scoreTxt.setOutlineColor(sf::Color::Black);
			your_scoreTxt.setOutlineThickness(2.0f);
			your_scoreTxt.setPosition((width_board) / 2 - your_scoreTxt.getGlobalBounds().width / 2, height_board / 3 - your_scoreTxt.getGlobalBounds().height / 2 - 100);


			playerText.setFillColor(sf::Color::Black);
			playerText.setCharacterSize(100);
			playerText.setFont(font2);



			sf::Event e;

			while (window.pollEvent(e))
			{
				if (e.type == sf::Event::Closed)
				{
					window.close();
					break;
				}

				if (e.text.unicode != sf::Keyboard::BackSpace)
				{
					if (e.type == sf::Event::TextEntered)
					{
						tmp.push_back(e.text.unicode);

						if (filter.find(tmp.back()) == std::string::npos)
						{
							tmp.pop_back();
						}
						if (tmp.size() > 12)
						{
							tmp.pop_back();
						}
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
		// cout << "name got : " << tmp;
	
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
	static bool is_high_score_classic(int score) {
		std::vector<int> score_vec;
		std::ifstream myfile_in("high_score/high_score.txt");
		if (myfile_in.is_open()) //set String line by line
		{
			
			std::string temp;
			int dow = 0;
			while (getline(myfile_in, temp))
			{

				std::size_t pos1 = temp.find("@");
				std::string str3 = temp.substr(pos1 + 1);
				std::stringstream geek(str3);
				int thom;
				geek >> thom;
				score_vec.push_back(thom);
			}
			myfile_in.close();
		}
		else { cout << "Failed to read file\n"; }
		return score>score_vec.back()||score_vec.size()<5;
	}
	static bool is_high_score_modern(int score) {
		std::vector<int> score_vec;
		std::ifstream myfile_in("high_score/morden.txt");
		if (myfile_in.is_open()) //set String line by line
		{
			//cout << "Read file success\n";
			std::string temp;
			int dow = 0;
			while (getline(myfile_in, temp))
			{

				std::size_t pos1 = temp.find("@");
				std::string str3 = temp.substr(pos1 + 1);
				std::stringstream geek(str3);
				int thom;
				geek >> thom;
				score_vec.push_back(thom);
			}
			myfile_in.close();
		}
		else { cout << "Failed to read file\n"; }
		return score > score_vec.back() || score_vec.size() < 5;
	}
	struct top_player
	{
		int rank;
		std::string name;
		int score;
	};
	void load()
	{
		std::vector<top_player> liss;
		std::vector<top_player> liss2;
		std::string line;
		std::string line2;
		std::ifstream myfile("high_score/high_score.txt");
		std::ifstream myfile2("high_score/morden.txt");
	
		cout << line;
		//top_player* temp = new top_player;
		//top_player* temp2 = new top_player;
		
		
		window->clear();


		txt->setFillColor(sf::Color::Green);
		txt->setCharacterSize(27);

		txt->setPosition(50, 50);
		txt->setString(">Esc<");
		window->draw(*txt);
	
		txt->setCharacterSize(70);
		txt->setFillColor(sf::Color::Magenta);
		txt->setPosition(50, height / 3 - 65-70);
		txt->setString("Classic mode");
		window->draw(*txt);

		txt->setCharacterSize(70);
		txt->setFillColor(sf::Color::Magenta);
		txt->setPosition(740, height / 3 - 65 - 70);
		txt->setString("Morden mode");
		window->draw(*txt);

		txt->setCharacterSize(60);
		txt->setFillColor(sf::Color::White);
		txt->setPosition(65, height / 3 - 65);
		txt->setString("name     score");
		window->draw(*txt);

		txt->setPosition(740, height / 3 - 65);
		txt->setString("name     score");
		window->draw(*txt);
		
		txt->setCharacterSize(50);
		txt->setFillColor(sf::Color::Yellow);

		if (myfile.is_open()) //set String line by line 1
		{
			//cout << "Read file success\n";
			std::string temp;
			int dow = 0;
			while (getline(myfile, temp))
			{
				std::size_t pos = temp.find("@");
				std::string str2 = temp.substr(0,pos);
				txt->setString(str2);
				txt->setPosition(25, height / 3 + dow);
				window->draw(*txt);

				std::size_t pos1 = temp.find("@");	      
				std::string str3 = temp.substr(pos1+1);
				txt->setString(str3);
				txt->setPosition(450 , height / 3 + dow );
				window->draw(*txt);
				dow += 60;
			}
			myfile.close();
		}
		else { cout << "Failed to read file\n"; }
		if (myfile2.is_open()) //set String line by line 2
		{
			//cout << "Read file2 success\n";
			std::string temp;
			int dow = 0;
			while (getline(myfile2, temp))
			{
				std::size_t pos = temp.find("@");
				std::string str2 = temp.substr(0, pos);
				txt->setString(str2);
				txt->setPosition(700, height / 3 + dow);
				window->draw(*txt);

				std::size_t pos1 = temp.find("@");
				std::string str3 = temp.substr(pos1 + 1);
				txt->setString(str3);
				txt->setPosition(1125, height / 3 + dow);
				window->draw(*txt);
				dow += 60;
			}
			myfile2.close();
		}
		else { cout << "Failed to read file\n"; }
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
		while (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {}
		cout << "Back from High Score Board\n";
		return;
	}
};

