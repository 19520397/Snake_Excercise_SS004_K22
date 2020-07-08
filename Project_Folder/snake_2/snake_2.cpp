#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
#include <string>
using namespace sf;
using std::cin;
using std::cout;

bool isAlive = false;
bool foodeating = false;

enum DIRECTION
{
    DIRECTION_RIGHT, DIRECTION_UP, DIRECTION_LEFT, DIRECTION_DOWN
};

int score;

// Width and Height of window in grid
int N = 40, M = 40;

// Size of image in pixels
float img_size = 24;

// Width of board in pixels
float width_board = img_size * N;
// Height of board in pixels
float height_board = img_size * M;

// Width of UI space in pixels
float width_UI = img_size * 15;
// Height of UI space in pixels
float height_UI = height_board;


DIRECTION direction;
int length;

struct Snake
{
    int x, y;
};

struct Fruit
{
    int x, y;
};

void loadScreen();
int start(RenderWindow&);
void update(Snake*&, Fruit&, Sound&);
void gameOver();
int show_credit(RenderWindow&);
int checkPlayAgain(RenderWindow&);
int checkResume(RenderWindow&);

void update(Snake*& s, Fruit& f, Sound& sound)
{
    // Update snake's body position
    for (int i = length; i > 0; --i)
    {
        s[i].x = s[i - 1].x; 
		s[i].y = s[i - 1].y;
    }

    // Update snake's head position
    if (direction == DIRECTION_UP) s[0].y -= 1;
    else if (direction == DIRECTION_LEFT) s[0].x -= 1;
    else if (direction == DIRECTION_RIGHT) s[0].x += 1;
    else if (direction == DIRECTION_DOWN) s[0].y += 1;

    // Check whether snake eat food
    if ((s[0].x == f.x) && (s[0].y == f.y))
    {
        f.x = rand() % (N - 2) + 1; // Range is 1-> N-2
        f.y = rand() % (M - 2) + 1; // Range is 1-> M-2

        for (int i = 0; i < length; i++)
        {
            if (s[i].x == f.x && s[i].y == f.y)
            {
                f.x = rand() % (N - 2) + 1; // Range is 1-> N-2
                f.y = rand() % (M - 2) + 1; // Range is 1-> M-2
                i = 0;
            }
        }
        sound.play();
        score+=10;
        length++;
		foodeating = true;
    }
	else { foodeating = false; }

    // Check whether snake's head has collision with border
    if (s[0].x >= N-1) // Hit right border
    {
        cout << "Hit right border\n";
        gameOver();
    }
    if (s[0].x <= 0) // Hit left border
    {
        cout << "Hit left border\n";
        gameOver();
    }
    if (s[0].y >= M-1) // Hit bottom border
    {
        cout << "Hit bottom border\n";
        gameOver();
    }
    if (s[0].y <= 0) // Hit top border
    {
        //s[0].y = M-1;
        cout << "Hit top border\n";
        gameOver();
    }

    // Check whether snake's head hit its-self
    for (int i = 1; i < length; i++)
    {
        if (s[0].x == s[i].x && s[0].y == s[i].y)
        {
            //length = i;
            cout << "Hit its-self\n";
            gameOver();
        }
    }
}

int checkPlayAgain(RenderWindow& window)
{
    int op = 1;
    Texture t;
    t.create(window.getSize().x, window.getSize().y);
    t.update(window);
    Sprite last_state(t);
    Font font;

    Sound sound_die,sound_choose;
    SoundBuffer buffer_die,buffer_choose;
    buffer_die.loadFromFile("audio/message.ogg");
    buffer_choose.loadFromFile("audio/beforegame.ogg");
    sound_die.setBuffer(buffer_die);
    sound_die.setVolume(50.f);
    sound_choose.setBuffer(buffer_choose);
    sound_choose.setVolume(50.f);

    if (!font.loadFromFile("Fonts/ARCADECLASSIC.TTF"))
    {
        cout << "ERROR: Could not load font";
    }
    Text txt;
    txt.setFont(font);

    Font font2;
    if (!font2.loadFromFile("Fonts/manaspc.ttf"))
    {
        cout << "ERROR: Could not load font";
    }
    Text txt2;
    txt2.setFont(font2);
    txt2.setFillColor(Color::Black);
    txt2.setString(">");
    txt2.setCharacterSize(70);

    bool isChanged = true;
    sound_die.play();
    while (window.isOpen())
    {
        if (Keyboard::isKeyPressed(Keyboard::Enter))
        {
            while (Keyboard::isKeyPressed(Keyboard::Enter))
            {
                // wait to key up
            }
            break;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            if (op < 1) op++;
            isChanged = true;
            //while (Keyboard::isKeyPressed(Keyboard::Up)) {}
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            if (op > 0) op--;
            isChanged = true;
            //while (Keyboard::isKeyPressed(Keyboard::Down)) {}
        }

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
        }

        if (isChanged)
        {
            window.clear();
            window.draw(last_state);
            sound_choose.play();

            txt.setFillColor(Color::Red);
            txt.setCharacterSize(180);
            txt.setString("You Died");
            txt.setPosition((width_board) / 2 - txt.getGlobalBounds().width / 2, height_board / 3 - txt.getGlobalBounds().height / 2);
            window.draw(txt);

            float temp = txt.getPosition().y + txt.getGlobalBounds().height + 100;
            txt.setCharacterSize(txt2.getCharacterSize());
            txt.setFillColor(Color::Blue);
            txt.setString("Play again");
            txt.setPosition(txt.getPosition().x + 80, temp);
            window.draw(txt);

            if (op == 1)
            {
                txt2.setPosition(txt.getPosition().x - txt2.getGlobalBounds().width - 10, txt.getPosition().y);
                window.draw(txt2);
            }

            txt.setString("Main Menu");
            txt.setPosition(txt.getPosition().x, txt.getPosition().y + txt.getGlobalBounds().height + 15);
            window.draw(txt);

            if (op == 0)
            {
                txt2.setPosition(txt.getPosition().x - txt2.getGlobalBounds().width - 10, txt.getPosition().y);
                window.draw(txt2);
            }

            window.display();
            while (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Down)) {/*Wait to release key*/}
            isChanged = false;
        }

    }

    if (op == 1)
    {
        cout << "Play Again\n";
        return 1;
    }
    else
    {
        cout << "Back\n";
        return -1;
    }
}

int checkResume(RenderWindow& window)
{
    int op = 2;

#pragma region Initialize

#pragma endregion

    Texture t;
    t.create(window.getSize().x, window.getSize().y);
    t.update(window);
    t.update(window);
    Sprite last_state(t);
    Font font;

    Sound sound_choose;
    SoundBuffer buffer_choose;
    buffer_choose.loadFromFile("audio/beforegame.ogg");
    sound_choose.setBuffer(buffer_choose);
    sound_choose.setVolume(50.f);

    if (!font.loadFromFile("Fonts/ARCADECLASSIC.TTF"))
    {
        cout << "ERROR: Could not load font";
    }
    Text txt;
    txt.setFont(font);

    Font font2;
    if (!font2.loadFromFile("Fonts/manaspc.ttf"))
    {
        cout << "ERROR: Could not load font";
    }
    Text txt_selection;
    txt_selection.setFont(font2);
    txt_selection.setFillColor(Color::Black);
    txt_selection.setString(">");
    txt_selection.setCharacterSize(70);

    bool isChanged = true;
    while (window.isOpen())
    {
        if (Keyboard::isKeyPressed(Keyboard::Enter))
        {
            while (Keyboard::isKeyPressed(Keyboard::Enter)) {/*Wait to key up*/}
            break;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            if (op < 2) op++;
            isChanged = true;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            if (op > 0) op--;
            isChanged = true;
        }

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
        }

        if (isChanged)
        {
            window.clear();
            window.draw(last_state);
            sound_choose.play();

            txt.setFillColor(Color::Red);
            txt.setCharacterSize(180);
            txt.setString("Paused");
            txt.setPosition((width_board) / 2 - txt.getGlobalBounds().width / 2, height_board / 3 - txt.getGlobalBounds().height / 2);
            window.draw(txt);

            float temp = txt.getPosition().y + txt.getGlobalBounds().height + 100;
            txt.setCharacterSize(txt_selection.getCharacterSize());
            txt.setFillColor(Color::Blue);
            txt.setString("Resume");
            txt.setPosition(txt.getPosition().x + 80, temp);
            window.draw(txt);

            if (op == 2)
            {
                txt_selection.setPosition(txt.getPosition().x - txt_selection.getGlobalBounds().width - 10, txt.getPosition().y);
                window.draw(txt_selection);
            }

            txt.setString("Main Menu");
            txt.setPosition(txt.getPosition().x, txt.getPosition().y + txt.getGlobalBounds().height + 15);
            window.draw(txt);

            if (op == 1)
            {
                txt_selection.setPosition(txt.getPosition().x - txt_selection.getGlobalBounds().width - 10, txt.getPosition().y);
                window.draw(txt_selection);
            }

            txt.setString("Quit");
            txt.setPosition(txt.getPosition().x, txt.getPosition().y + txt.getGlobalBounds().height + 15);
            window.draw(txt);

            if (op == 0)
            {
                txt_selection.setPosition(txt.getPosition().x - txt_selection.getGlobalBounds().width - 10, txt.getPosition().y);
                window.draw(txt_selection);
            }

            window.display();
            while (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Down))
            {
                // wait for key up
            }
            isChanged = false;
        }

    }

    if (op == 2)
    {
        cout << "Resume\n";
        return 2;
    }
    else if (op == 1)
    {
        cout << "Main Menu\n";
        return 1;
    }
    else
    {
        cout << "Back\n";
        return 0;
    }
}

int start(RenderWindow& window)
{
    int op = 1;
    int MAX = (N - 2) * (M - 2);

#pragma region Initialize
    Sound sound_eatfood;
    SoundBuffer buffer;
    buffer.loadFromFile("audio/eatfood.ogg");
    sound_eatfood.setBuffer(buffer);
    sound_eatfood.setVolume(50.f);

    Snake* s = new Snake[MAX];
    Fruit f;

    Texture t1, t2, t3, t4,t_intruct,t_pause;
    t1.loadFromFile("images/white.png");
    t2.loadFromFile("images/red.png");
    t3.loadFromFile("images/purble.jpg");
    t4.loadFromFile("images/green_2.png");
    t_intruct.loadFromFile("images/key.png");
    t_pause.loadFromFile("images/esc.png");

    Sprite sprite_white(t1);
    Sprite sprite_red(t2);
    Sprite sprite_purple(t3);
    Sprite sprite_green(t4);
    Sprite sprite_intruct(t_intruct);
    Sprite sprite_pause(t_pause);

    sprite_white.scale(1.5f, 1.5f);
    sprite_red.scale(1.5f, 1.5f);
    sprite_purple.scale(1.5f, 1.5f);
    sprite_green.scale(1.5f, 1.5f);
    sprite_intruct.scale(0.5f, 0.5f);
    sprite_pause.scale(0.15f, 0.15f);

    sprite_intruct.setPosition(width_board + width_UI/2 - sprite_intruct.getGlobalBounds().width/2 - 10,  height_UI/3 - sprite_intruct.getGlobalBounds().height - 55);
    sprite_pause.setPosition(sprite_intruct.getPosition().x, 30);

    Font font_arcade;
    if (!font_arcade.loadFromFile("Fonts/ARCADECLASSIC.TTF"))
    {
        cout << "ERROR: Could not load font";
    }
	Font font_manaspc;
	if (!font_manaspc.loadFromFile("Fonts/manaspc.TTF"))
	{
		cout << "ERROR: Could not load font";
	}
    Text txt_score;
    txt_score.setFont(font_arcade);
    txt_score.setFillColor(Color::White);
    txt_score.setCharacterSize(50);
    txt_score.setString("Point");
    txt_score.setPosition(width_board + width_UI / 2 - txt_score.getLocalBounds().width / 2, height_UI / 2 - 48);

    Texture text_key;
    text_key.loadFromFile("images/white.png");
    Sprite sprite_key(text_key);
    sprite_key.scale(1.5f, 1.5f);

    Text intruct1,intruct2,intruct3,intruct4,pause;
    intruct1.setFont(font_arcade);
    intruct2.setFont(font_arcade);
    intruct3.setFont(font_arcade);
    intruct4.setFont(font_arcade);
    pause.setFont(font_arcade);

    intruct1.setFillColor(Color::White);
    intruct2.setFillColor(Color::White);
    intruct3.setFillColor(Color::White);
    intruct4.setFillColor(Color::White);
    pause.setFillColor(Color::White);

    intruct1.setCharacterSize(30);
    intruct2.setCharacterSize(30);
    intruct3.setCharacterSize(30);
    intruct4.setCharacterSize(30);
    pause.setCharacterSize(30);

    intruct1.setString("UP");
    intruct2.setString("DOWN");
    intruct3.setString("LEFT");
    intruct4.setString("RIGHT");
    pause.setString("PAUSE");

    intruct1.setPosition(sprite_intruct.getPosition().x + sprite_key.getGlobalBounds().width * 2 + 20, sprite_intruct.getPosition().y - sprite_key.getGlobalBounds().height * 2);
    intruct2.setPosition(sprite_intruct.getPosition().x + sprite_key.getGlobalBounds().width * 5 - intruct2.getGlobalBounds().width, sprite_intruct.getPosition().y + sprite_key.getGlobalBounds().height * 5);
    intruct3.setPosition(sprite_intruct.getPosition().x - sprite_key.getGlobalBounds().width * 3 + 5, sprite_intruct.getPosition().y + sprite_key.getGlobalBounds().height * 3 - 10);
    intruct4.setPosition(sprite_intruct.getPosition().x + sprite_key.getGlobalBounds().width * 7 + 5, sprite_intruct.getPosition().y + sprite_key.getGlobalBounds().height * 3 - 10);
    pause.setPosition(sprite_pause.getPosition().x + sprite_key.getGlobalBounds().width*2 + 30,sprite_pause.getPosition().y + 15);

    Text txt;
    txt.setFont(font_manaspc);
    txt.setFillColor(Color::Magenta);

#pragma endregion

    txt.setCharacterSize(23);
    txt.setPosition(txt_score.getPosition().x + txt_score.getLocalBounds().width / 2 - 32, txt_score.getPosition().y + txt_score.getGlobalBounds().height + 35);
	
	Text txt2;
	txt2.setFont(font_manaspc);
	txt2.setFillColor(Color::Green);
	txt2.setCharacterSize(23);
	txt2.setString("+10");

	Text txt3;
	txt3.setFont(font_manaspc);
	txt3.setFillColor(Color::Cyan);
	txt3.setCharacterSize(23);
	txt3.setString("Nice!");

	Text txt4;
	txt4.setFont(font_manaspc);
	txt4.setFillColor(Color::Yellow);
	txt4.setCharacterSize(23);
	txt4.setString("Perfect;>");

	Text txt5;
	txt5.setFont(font_manaspc);
	txt5.setFillColor(Color::Blue);
	txt5.setCharacterSize(23);
	txt5.setString("Master;)");

    while (op == 1)
    {
        srand(time(0));

        isAlive = true;

        Clock clock;
		Clock clock2;
		
        float timer = 0, delay = 0.1;
		float timer2 = 0, delay2 = 2;
        score = 00;
        length = 3;
        for (int i = 0; i < length; i++)
        {
            s[i].x = 15;
            s[i].y = 15;
        }
        timer = delay * 1.1;
        f.x = 10;
        f.y = 10;
		
        int effect_count_down = 0;
		int k = 0;
        int ran = 0;

        DIRECTION temp_d = DIRECTION::DIRECTION_RIGHT;
        direction = temp_d;

        while (window.isOpen() && isAlive)
        {
			
            float time = clock.getElapsedTime().asSeconds();
			float time2 = clock2.getElapsedTime().asSeconds();
            clock.restart();
			
			timer += time;
			timer2 += time2;
            Event e;
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed)
                {
                    window.close();
                    return -1;
                }
            }

#pragma region Get Input
            if (Keyboard::isKeyPressed(Keyboard::Left)) temp_d = DIRECTION_LEFT;
            else if (Keyboard::isKeyPressed(Keyboard::Right)) temp_d = DIRECTION_RIGHT;
            else if (Keyboard::isKeyPressed(Keyboard::Up)) temp_d = DIRECTION_UP;
            else if (Keyboard::isKeyPressed(Keyboard::Down)) temp_d = DIRECTION_DOWN;
            // Check pause keyboard
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                while (Keyboard::isKeyPressed(Keyboard::Escape)) {/*Wait for key up*/ }
#pragma region Draw
                
                window.clear();

                // Draw background
                for (int x = width_board - img_size; x > -1; x -= img_size) { sprite_purple.setPosition(x, 0);  window.draw(sprite_purple); } // Draw top Border
                for (int y = height_board - 2 * img_size; y > 0; y -= img_size)
                {
                    sprite_purple.setPosition(0, y);  window.draw(sprite_purple); // Draw left Border
                    for (int x = width_board - 2 * img_size; x > 0; x -= img_size)
                    {
                        sprite_white.setPosition(x, y);  window.draw(sprite_white);
                    }
                    sprite_purple.setPosition(width_board - img_size, y);  window.draw(sprite_purple); // Draw right Border
                }
                for (int x = width_board - img_size; x > -1; x -= img_size) { sprite_purple.setPosition(x, height_board - img_size);  window.draw(sprite_purple); } // Draw bottom Border

                // Draw snake
                for (int i = 0; i < length; i++)
                {
                    sprite_red.setPosition(s[i].x * img_size, s[i].y * img_size);  window.draw(sprite_red);
                }

                // Draw food
                sprite_green.setPosition(f.x * img_size, f.y * img_size);  window.draw(sprite_green);

                // Draw UI
                txt.setString(std::to_string(score)); window.draw(txt); window.draw(txt_score);

                window.display();
#pragma endregion
                int sl = checkResume(window);
                if (sl == 0) return -1; // Quit
                else if (sl == 1)// main menu
                {
                    delete[] s;
                    return 2;
                }
                else {} // Resume
            }
#pragma endregion

            if (timer > delay)
            {
                if (!((temp_d == DIRECTION_LEFT && direction == DIRECTION_RIGHT)
                    || (temp_d == DIRECTION_RIGHT && direction == DIRECTION_LEFT)
                    || (temp_d == DIRECTION_UP && direction == DIRECTION_DOWN)
                    || (temp_d == DIRECTION_DOWN && direction == DIRECTION_UP)))
                {
                    direction = temp_d;
                }

                // Delay time has reached, reset timer
                timer = 0;
                // Update position of object 
                 update(s, f, sound_eatfood);

#pragma region Draw

                window.clear();

                // Draw background
                for (int x = width_board - img_size; x > -1; x -= img_size) { sprite_purple.setPosition(x, 0);  window.draw(sprite_purple); } // Draw top Border
                for (int y = height_board - 2 * img_size; y > 0; y -= img_size)
                {
                    sprite_purple.setPosition(0, y);  window.draw(sprite_purple); // Draw left Border
                    for (int x = width_board - 2 * img_size; x > 0; x -= img_size)
                    {
                        sprite_white.setPosition(x, y);  window.draw(sprite_white);
                    }
                    sprite_purple.setPosition(width_board - img_size, y);  window.draw(sprite_purple); // Draw right Border
                }
                for (int x = width_board - img_size; x > -1; x -= img_size) { sprite_purple.setPosition(x, height_board - img_size);  window.draw(sprite_purple); } // Draw bottom Border

                // Draw snake
                for (int i = 0; i < length; i++)
                {
                    sprite_red.setPosition(s[i].x * img_size, s[i].y * img_size);  window.draw(sprite_red);
                }

                // Draw food
                sprite_green.setPosition(f.x * img_size, f.y * img_size);  window.draw(sprite_green);

                // Draw UI
                txt.setString(std::to_string(score)); window.draw(txt); window.draw(txt_score);
                window.draw(intruct1);
                window.draw(intruct2);
                window.draw(intruct3);
                window.draw(intruct4);
                window.draw(pause);
                window.draw(sprite_intruct);
                window.draw(sprite_pause);

				// draw effect
                ran = rand() % 3;
				if (foodeating)
				{
					effect_count_down = 7;
                    k = 18;
				}
				if (effect_count_down > 0)
				{
					txt2.setPosition(txt.getPosition().x + txt.getLocalBounds().width + 16, txt.getPosition().y);
					window.draw(txt2);
					effect_count_down--;
				}

				switch (ran)
				{
				default:
					break;
				case 1:
					if (k > 0) {
						txt3.setPosition(txt_score.getPosition().x, txt_score.getPosition().y - 50);
						window.draw(txt3);
						k--;
					}
					break;

				case 2:
					if (k > 0) {
						txt4.setPosition(txt_score.getPosition().x, txt_score.getPosition().y - 70);
						window.draw(txt4);
						k--;
					}
					break;
				case 0:
					if (k > 0) {
						txt5.setPosition(txt_score.getPosition().x, txt_score.getPosition().y - 90);
						window.draw(txt5);
						k--;
					}
					break;
				}
				
                window.display();
#pragma endregion
            }
            else
            {
                // Wait delay time
                
            }

        }
        if (window.isOpen()) {
            if (!isAlive)
            {
                // Player is died, ask if player want to try again
#pragma region Draw

                window.clear();

                // Draw background
                for (int x = width_board - img_size; x > -1; x -= img_size) { sprite_purple.setPosition(x, 0);  window.draw(sprite_purple); } // Draw top Border
                for (int y = height_board - 2 * img_size; y > 0; y -= img_size)
                {
                    sprite_purple.setPosition(0, y);  window.draw(sprite_purple); // Draw left Border
                    for (int x = width_board - 2 * img_size; x > 0; x -= img_size)
                    {
                        sprite_white.setPosition(x, y);  window.draw(sprite_white);
                    }
                    sprite_purple.setPosition(width_board - img_size, y);  window.draw(sprite_purple); // Draw right Border
                }
                for (int x = width_board - img_size; x > -1; x -= img_size) { sprite_purple.setPosition(x, height_board - img_size);  window.draw(sprite_purple); } // Draw bottom Border

                // Draw snake
                for (int i = 0; i < length; i++)
                {
                    sprite_red.setPosition(s[i].x * img_size, s[i].y * img_size);  window.draw(sprite_red);
                }

                // Draw food
                sprite_green.setPosition(f.x * img_size, f.y * img_size);  window.draw(sprite_green);

                // Draw UI
                txt.setString(std::to_string(score)); window.draw(txt); window.draw(txt_score);
                window.draw(intruct1); 
                window.draw(intruct2);
                window.draw(intruct3);
                window.draw(intruct4);
                window.draw(pause);
                window.draw(sprite_intruct);
                window.draw(sprite_pause);

                window.display();
#pragma endregion
                op = checkPlayAgain(window);
            }
            else
            {
                cout << " Not died yet but the start()'s loop has been break?\n";
                delete[] s;
                return 2;
            }
        }
        else
        {
            delete[] s;
            return -1;
        }
    }
    delete[] s;
    return 2;
}

void gameOver()
{
    cout << "Game Over\n";
    isAlive = false;
}

int show_credit(RenderWindow& window)
{
    window.clear();

    Font font;
    if (!font.loadFromFile("Fonts/manaspc.ttf"))
    {
        cout << "ERROR: Could not load font";
    }
    Text txt;
    txt.setFont(font);
    txt.setFillColor(Color::Green);
    txt.setCharacterSize(32);

    txt.setPosition(50, 50);
    txt.setString(">Esc<");
    window.draw(txt);
    txt.setString("This is exercise for class SS004.K22");
    txt.setPosition(window.getSize().x / 2 - txt.getGlobalBounds().width / 2, height_board * 3 / 4 - txt.getGlobalBounds().height);
    window.draw(txt);
    txt.setString("~ VNUHCM ~ UIT ~");
    txt.setPosition(window.getSize().x / 2 - txt.getGlobalBounds().width / 2, txt.getPosition().y +  txt.getGlobalBounds().height + 15);
    window.draw(txt);

    txt.setFillColor(Color::Yellow);
    txt.setString("Authors :\n ~ Nguyen Pham Duy Bang - Dragnell\n ~ Nguyen Trong Nhan - C0R3M3N\n ~ Vu Ngoc Thach - DragonPow");
    txt.setPosition(100, height_board/3 - txt.getGlobalBounds().height);
    window.draw(txt);

    window.display();
    while (window.isOpen() && !(Keyboard::isKeyPressed(Keyboard::Escape)))
    {
        // Wait until user want to return
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
        }
    }

    if (window.isOpen()) return 2;
    else return -1;
}

void loadScreen()
{
    RenderWindow window(VideoMode(width_board + width_UI, height_board), "Snake Game!", Style::Titlebar | Style::Close);
    window.setPosition(Vector2i(15, 15));
    float width = width_board + width_UI;
    int op = 2;
    while (op > 0)
    {
        {
            Sound sound;
            SoundBuffer buffer;
            buffer.loadFromFile("audio/beforegame.ogg");
            sound.setBuffer(buffer);
            sound.setVolume(30.f);
            Font font;

            if (!font.loadFromFile("Fonts/ARCADECLASSIC.TTF"))
            {
                cout << "ERROR: Could not load font";
            }
            Text txt;
            txt.setFont(font);

            Font font2;
            if (!font2.loadFromFile("Fonts/manaspc.ttf"))
            {
                cout << "ERROR: Could not load font";
            }
            Text txt2;
            txt2.setFont(font2);
            txt2.setFillColor(Color::White);
            txt2.setString(">");
            txt2.setCharacterSize(50);

            bool isChanged = true;
            while (window.isOpen())
            {
                if (Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    break;
                }
                else if (Keyboard::isKeyPressed(Keyboard::Up))
                {
                    if (op < 2) op++;
                    isChanged = true;
                    //while (Keyboard::isKeyPressed(Keyboard::Up)) {}
                }
                else if (Keyboard::isKeyPressed(Keyboard::Down))
                {
                    if (op > 0) op--;
                    isChanged = true;
                    //while (Keyboard::isKeyPressed(Keyboard::Down)) {}
                }

                Event e;
                while (window.pollEvent(e))
                {
                    if (e.type == Event::Closed)
                        window.close();
                }

                if (isChanged)
                {
                    window.clear();
                    sound.play();

                    txt.setFillColor(Color::Green);
                    txt.setCharacterSize(72);
                    txt.setString("Snake Game");
                    txt.setPosition(width / 2 - txt.getGlobalBounds().width / 2, height_board / 3 - txt.getGlobalBounds().height / 2);
                    window.draw(txt);

                    float temp = txt.getPosition().y + txt.getGlobalBounds().height + 30;
                    txt.setCharacterSize(50);
                    txt.setFillColor(Color::Yellow);
                    txt.setString("Start");
                    txt.setPosition(width / 2 - txt.getGlobalBounds().width / 2, temp);
                    window.draw(txt);

                    if (op == 2)
                    {
                        txt2.setPosition(txt.getPosition().x - txt2.getGlobalBounds().width - 10, txt.getPosition().y);
                        window.draw(txt2);
                    }

                    txt.setString("Credit");
                    txt.setPosition(txt.getPosition().x, txt.getPosition().y + txt.getGlobalBounds().height + 15);
                    window.draw(txt);

                    if (op == 1)
                    {
                        txt2.setPosition(txt.getPosition().x - txt2.getGlobalBounds().width - 10, txt.getPosition().y);
                        window.draw(txt2);
                    }

                    txt.setString("Quit");
                    txt.setPosition(txt.getPosition().x, txt.getPosition().y + txt.getGlobalBounds().height + 15);
                    window.draw(txt);

                    if (op == 0)
                    {
                        txt2.setPosition(txt.getPosition().x - txt2.getGlobalBounds().width - 10, txt.getPosition().y);
                        window.draw(txt2);
                    }

                    window.display();
                    while (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Down))
                    {
                        // wait for key up
                    }
                    isChanged = false;
                }

            }
        }

        if (op == 2) op = start(window);
        else if (op == 1) op = show_credit(window);
    }
}

int main()
{
    loadScreen();

    return 0;
}


