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
						if (filter.find(tmp.back())==std::string::npos)
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
		cout << "name got : "<< tmp;
		//out put to file
		std::vector<int> score_vec;
		std::vector<std::string> name_vec;
		std::ifstream myfile_in("high_score/high_score.txt");
		if (myfile_in.is_open()) //set String line by line
		{
			cout << "Read file success\n";
			std::string temp;
			int dow = 0;
			while (getline(myfile_in, temp))
			{

				std::size_t pos1 = temp.find("@");
				std::string str3 = temp.substr(pos1 + 1);
				std::stringstream geek(str3);
				int thom;
				geek >> thom;
				name_vec.push_back(temp);
				score_vec.push_back(thom);
			}
			myfile_in.close();
		}
		std::ofstream myfile("high_score/high_score.txt");
		if (myfile.is_open()) {
			int count = 0;
			bool is_high_score = false;

			
				for (int i = 0; i < name_vec.size(); i++)
				{
					if (score_vec[i] >= score)
					{
						myfile << name_vec[i] << "\n";
					}
					else
					{
						if (!is_high_score)
						{
							is_high_score = true;
							cout << "you are in high score board! \n";
							myfile << tmp << "@" << std::to_string(score) << "\n";
							count++;
							if (count >= 5)break;
						}
						myfile << name_vec[i] << "\n";
					}
					count++;
					if (count >= 5)break;
				}
				if (name_vec.size() < 5 && !is_high_score)
				{
					is_high_score = true;
					cout << "you are in high score board! \n";
					myfile << tmp << "@" << std::to_string(score) << "\n";
				}

			
			myfile.close();
		}
		else cout << "Unable to open file";
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
	struct top_player
	{
		int rank;
		std::string name;
		int score;
	};
	void load()
	{
		std::vector<top_player> liss;
		std::string line;
		std::ifstream myfile("high_score/high_score.txt");
		
	
		cout << line;
		top_player* temp = new top_player;
		
		
		window->clear();


		txt->setFillColor(sf::Color::Green);
		txt->setCharacterSize(32);

		txt->setPosition(50, 50);
		txt->setString(">Esc<");
		window->draw(*txt);
	

		txt->setCharacterSize(50);
		txt->setFillColor(sf::Color::Yellow);
		
		if (myfile.is_open()) //set String line by line
		{
			cout << "Read file success\n";
			std::string temp;
			int dow = 0;
			while (getline(myfile, temp))
			{
				std::size_t pos = temp.find("@");
				std::string str2 = temp.substr(0,pos);
				txt->setString(str2);
				txt->setPosition(400, height / 3 + dow);
				window->draw(*txt);

				std::size_t pos1 = temp.find("@");	      
				std::string str3 = temp.substr(pos1+1);
				txt->setString(str3);
				txt->setPosition(900 , height / 3 + dow );
				window->draw(*txt);
				dow += 75;
			}
			myfile.close();
		}
		

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

