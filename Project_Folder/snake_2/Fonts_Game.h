#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
namespace Fonts
{
	static sf::Font font_arcade;
	static sf::Font font_gomarice;
	static sf::Font font_manaspc;
	static sf::Font font_invasion;

	class Font_Game
	{
	private:
		sf::Font font_arcade;
		sf::Font font_gomarice;
		sf::Font font_manaspc;
		sf::Font font_invasion;
	public:
		Font_Game()
		{
			if (!font_arcade.loadFromFile("Fonts/ARCADECLASSIC.TTF")) std::cout << "Cannot load font ARCADECLASSIC.TTF\n";
			if (!font_gomarice.loadFromFile("Fonts/gomarice_game_continue_02.ttf")) std::cout << "Cannot load font gomarice_game_continue_02.ttf\n";
			if (!font_invasion.loadFromFile("Fonts/INVASION2000.TTF")) std::cout << "Cannot load font INVASION2000.TTF\n";
			if (!font_manaspc.loadFromFile("Fonts/manaspc.ttf")) std::cout << "Cannot load font manaspc.ttf\n";
		}
		sf::Font* getFont_arcade() { return &font_arcade; }
		sf::Font* getFont_gomarice() { return &font_gomarice; }
		sf::Font* getFont_manaspc() { return &font_manaspc; }
		sf::Font* getFont_invasion() { return &font_invasion; }
	};
}