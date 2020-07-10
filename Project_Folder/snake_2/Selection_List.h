#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Selection_List
{
private:

	sf::Text* txt_option;
    sf::Text* txt_selection;
	int op;

public:

    static void draw_on_horizontal(sf::RenderWindow* window, std::vector<std::string>* options, sf::Text* txt_option, sf::Text* txt_selection, int op)
    {
        txt_option->setString(options->at(options->size() - 1));

        window->draw(*txt_option);

        if (op == options->size() - 1)
        {
            txt_selection->setPosition(txt_option->getPosition().x - txt_selection->getGlobalBounds().width, txt_option->getPosition().y);
            window->draw(*txt_selection);
        }

        for (int i = options->size() - 2; i > -1; i--)
        {
            txt_option->setString(options->at(i)); // Here are some magic
            txt_option->setPosition(txt_option->getPosition().x, txt_option->getPosition().y + txt_option->getGlobalBounds().height * 1.3);
            window->draw(*txt_option);

            if (op == i)
            {
                txt_selection->setPosition(txt_option->getPosition().x - txt_selection->getGlobalBounds().width, txt_option->getPosition().y);
                window->draw(*txt_selection);
            }
        }
    }

    static void draw_on_vertical(sf::RenderWindow* window, std::vector<std::string>* options, sf::Text* txt_option, sf::Text* txt_selection, int op)
    {
        txt_option->setString(options->at(options->size() - 1));
        window->draw(*txt_option);

        if (op == options->size() - 1)
        {
            txt_selection->setPosition(txt_option->getPosition().x - txt_selection->getGlobalBounds().width, txt_option->getPosition().y);
            window->draw(*txt_selection);
        }

        for (int i = options->size() - 2; i > -1; i--)
        {
            txt_option->setString(options->at(i)); // Here are some magic
            txt_option->setPosition(txt_option->getPosition().x , txt_option->getPosition().y + txt_option->getGlobalBounds().height * 1.5);
            window->draw(*txt_option);

            if (op == i)
            {
                txt_selection->setPosition(txt_option->getPosition().x - txt_selection->getGlobalBounds().width, txt_option->getPosition().y);
                window->draw(*txt_selection);
            }
        }
    }

    static void draw_on_vertical(sf::RenderWindow* window, std::vector<std::string>* options, sf::Text* txt_option, sf::Text* txt_selection, int op, sf::RectangleShape* background)
    {
        txt_option->setString(options->at(options->size() - 1));

        background->scale(txt_option->getGlobalBounds().width / background->getGlobalBounds().width, txt_option->getGlobalBounds().height / background->getGlobalBounds().height);
        background->setPosition(txt_option->getPosition().x, txt_option->getPosition().y);
        window->draw(*background);

        window->draw(*txt_option);

        if (op == options->size() - 1)
        {
            txt_selection->setPosition(txt_option->getPosition().x - txt_selection->getGlobalBounds().width, txt_option->getPosition().y);
            window->draw(*txt_selection);
        }

        for (int i = options->size() - 2; i > -1; i--)
        {
            txt_option->setString(options->at(i)); // Here are some magic
            txt_option->setPosition(txt_option->getPosition().x, txt_option->getPosition().y + txt_option->getGlobalBounds().height * 1.5);

            background->scale(txt_option->getGlobalBounds().width / background->getGlobalBounds().width, txt_option->getGlobalBounds().height / background->getGlobalBounds().height);
            background->setPosition(txt_option->getPosition());
            window->draw(*background);

            window->draw(*txt_option);

            if (op == i)
            {
                txt_selection->setPosition(txt_option->getPosition().x - txt_selection->getGlobalBounds().width, txt_option->getPosition().y);
                window->draw(*txt_selection);
            }
        }
    }

	void draw_on(sf::RenderWindow* window, std::vector<std::string>* options)
	{
        txt_option->setString(options->at(options->size() - 1));
        
        window->draw(*txt_option);

        if (op == options->size() - 1)
        {
            txt_selection->setPosition(txt_option->getPosition().x - txt_selection->getGlobalBounds().width, txt_option->getPosition().y);
            window->draw(*txt_selection);
        }

        for (int i = options->size() - 2; i > -1; i--)
        {
            txt_option->setString(options->at(i)); // Here are some magic
            txt_option->setPosition(txt_option->getPosition().x, txt_option->getPosition().y + txt_option->getGlobalBounds().height * 1.3);
            window->draw(*txt_option);

            if (op == i)
            {
                txt_selection->setPosition(txt_option->getPosition().x - txt_selection->getGlobalBounds().width, txt_option->getPosition().y);
                window->draw(*txt_selection);
            }
        }
	}
};

