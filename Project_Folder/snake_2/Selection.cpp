#include "Selection.h"

Selection::Selection(RenderWindow* window, float width, float heigh, float top, float left, sf::Texture* background) : window(window), top(top), left(left), height(heigh - top), width(width - left)
{
	if (window == NULL) throw std::invalid_argument("Null pointer");
	else { this->window = window; }

	if (background != NULL) sprite_backGround = new Sprite(*background);

	txt_title = new Text();
	txt_selection = new Text();
	txt_option = new Text();

	sound = new Sound();
	buffer = new SoundBuffer();

	options = new vector<std::string>{ "Option A", "Option B", "Option C" };
	op = options->size() - 1;

	buffer->loadFromFile("audio/beforegame.ogg");
	sound->setBuffer(*buffer);
	sound->setVolume(30.f);

	font_arcade = new Font();
	if (!font_arcade->loadFromFile("Fonts/ARCADECLASSIC.TTF")) std::cout << "Cannot load font ARCADECLASSIC.TTF\n";
	font_manaspc = new Font();
	if (!font_manaspc->loadFromFile("Fonts/manaspc.ttf")) std::cout << "Cannot load font manaspc.ttf\n";

	txt_title->setFont(*font_arcade);
	txt_title->setFillColor(Color::Green);
	txt_title->setCharacterSize(72);
	txt_title->setString("Selection");
	txt_title->setPosition(left + width / 2 - txt_title->getGlobalBounds().width / 2, top + height / 3 - txt_title->getGlobalBounds().height / 2);

	txt_option->setFont(*font_arcade);
	txt_option->setFillColor(Color::Yellow);
	txt_option->setCharacterSize(50);

	txt_selection->setFont(*font_manaspc);
	txt_selection->setFillColor(sf::Color::White);
	txt_selection->setString("> ");
	txt_selection->setCharacterSize(txt_option->getCharacterSize());
}

Selection::~Selection()
{
	delete font_arcade;
	delete font_manaspc;
	delete txt_option;
	delete txt_selection;
	delete txt_title;
	delete sound;
	delete buffer;
	delete options;
}

int Selection::load()
{
	bool isChanged = true;

	/*float back_ground_padding = 20;
	float back_ground_height = txt_title->getGlobalBounds().height;
	float back_ground_width = txt_title->getGlobalBounds().width;

	sf::RectangleShape* back_ground = new sf::RectangleShape(sf::Vector2f(back_ground_width, back_ground_height));
	back_ground->setPosition(txt_title->getPosition().x, txt_title->getPosition().y );
	back_ground->setFillColor(Color::Black);
	back_ground->setOutlineColor(Color::Green);
	back_ground->setOutlineThickness(2.0f);*/

	while (window->isOpen())
	{
		if (Keyboard::isKeyPressed(Keyboard::Enter))
		{
			while (Keyboard::isKeyPressed(Keyboard::Enter)) {}
			break;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			if (op < options->size() - 1) op++;
			else op = 0;
			isChanged = true;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			if (op > 0) op--;
			else op = options->size() - 1;
			isChanged = true;
		}

		sf::Event e;
		while (window->pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window->close();
		}

		if (isChanged)
		{
			window->clear();

			sound->play();

			if (sprite_backGround != NULL) window->draw(*sprite_backGround);
			//window->draw(*back_ground);

			window->draw(*txt_title);

			txt_option->setString(options->at(options->size() - 1));
			txt_option->setPosition(txt_title->getPosition().x + txt_title->getGlobalBounds().width * 0.2f, txt_title->getPosition().y + (txt_title->getGlobalBounds().height * 1.6f));

			Selection_List::draw_on_vertical(window, options, txt_option, txt_selection, op);

			window->display();
			while (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Down))
			{
				// wait for key up
			}
			isChanged = false;
		}

	}

	if (window->isOpen())
	{
		return op;
	}
	else return 0;
}

void Selection::setOptions_List(vector<std::string>* options)
{
	if (options == NULL) throw std::invalid_argument("Null pointer");
	else
	{
		this->options = options;
		op = options->size() - 1;
	}
}

void Selection::setTitle_String(sf::String str)
{
	txt_title->setString(str);
	txt_title->setPosition(left + width / 2 - txt_title->getGlobalBounds().width / 2, top + height / 3 - txt_title->getGlobalBounds().height / 2);
}
void Selection::setTitle_Size(int size)
{
	txt_title->setCharacterSize(size);
	txt_title->setPosition(left + width / 2 - txt_title->getGlobalBounds().width / 2, top + height / 3 - txt_title->getGlobalBounds().height / 2);
}

void Selection::setTitle_Font(Font& font)
{
	txt_title->setFont(font);
	txt_title->setPosition(left + width / 2 - txt_title->getGlobalBounds().width / 2, top + height / 3 - txt_title->getGlobalBounds().height / 2);
}
