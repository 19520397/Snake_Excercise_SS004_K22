#include "Screen_Classic.h"


Screen_Classic::Screen_Classic(RenderWindow* window, int n, int m, float img_size, float width_UI): width_board(n * img_size), height(m * img_size), width_UI(width_UI), img_size(img_size), M(m), N(n)
{
	if (window == NULL) throw std::invalid_argument("Null pointer");
	else { this->window = window; }

    int MAX = (N - 2) * (M - 2);

    s = new Snake[MAX];
    direction = DIRECTION::DIRECTION_RIGHT;
    length = 0;
    img_size = 24;
    f = new Fruit();
    score = 0;

    effect_count_down_1 = effect_count_down_2 = 0;

    font_arcade = new Font();
    font_manaspc = new Font();
    if (!font_arcade->loadFromFile("Fonts/ARCADECLASSIC.TTF")) { cout << "ERROR: Could not load font"; }
    if (!font_manaspc->loadFromFile("Fonts/manaspc.ttf")) { cout << "ERROR: Could not load font"; }

    t1 = new Texture();
    t2 = new Texture();
    t3 = new Texture();
    t4 = new Texture();
    t5 = new Texture();
    t_intruct = new Texture();
    t_pause = new Texture();
    text_key = new Texture();
    
    t1->loadFromFile("images/white.png");
    t2->loadFromFile("images/red.png");
    t3->loadFromFile("images/purble.jpg");
    t4->loadFromFile("images/green_2.png");
    t5->loadFromFile("images/red_2.png");
    t_intruct->loadFromFile("images/key.png");
    t_pause->loadFromFile("images/esc.png");
    text_key->loadFromFile("images/white.png");

    sprite_white = new Sprite(*t1);
    sprite_red = new Sprite(*t2);
    sprite_red2 = new Sprite(*t5);
    sprite_purple = new Sprite(*t3);
    sprite_green = new Sprite(*t4);
    sprite_intruct = new Sprite(*t_intruct);
    sprite_pause = new Sprite(*t_pause);
    sprite_key = new Sprite(*text_key);

    sprite_white->scale(1.5f, 1.5f);
    sprite_red->scale(1.5f, 1.5f);
    sprite_red2->scale(1.5f, 1.5f);
    sprite_purple->scale(1.5f, 1.5f);
    sprite_green->scale(1.5f, 1.5f);
    sprite_intruct->scale(0.5f, 0.5f);
    sprite_pause->scale(0.15f, 0.15f);
    sprite_key->scale(1.5f, 1.5f);

    sprite_intruct->setPosition(width_board + width_UI / 2 - sprite_intruct->getGlobalBounds().width / 2 - 10, height / 3 - sprite_intruct->getGlobalBounds().height - 55);
    sprite_pause->setPosition(sprite_intruct->getPosition().x, 30);

    txt = new Text();
    txt2 = new Text();
    txt3 = new Text();
    txt4 = new Text();
    txt5 = new Text();
    txt_score = new Text();

    txt_score->setFont(*font_arcade);
    txt_score->setFillColor(Color::White);
    txt_score->setCharacterSize(50);
    txt_score->setString("Point");
    txt_score->setPosition(width_board + width_UI / 2 - txt_score->getLocalBounds().width / 2, height / 2 - 48);

    txt->setFont(*font_manaspc);
    txt->setFillColor(Color::Magenta);
    txt->setCharacterSize(23);
    txt->setPosition(txt_score->getPosition().x + txt_score->getLocalBounds().width / 2 - 32, txt_score->getPosition().y + txt_score->getGlobalBounds().height + 35);

    txt2->setFont(*font_manaspc);
    txt2->setFillColor(Color::Green);
    txt2->setCharacterSize(23);
    txt2->setString("+10");

    txt3->setFont(*font_manaspc);
    txt3->setFillColor(Color::Cyan);
    txt3->setCharacterSize(23);
    txt3->setString("Nice!");

    txt4->setFont(*font_manaspc);
    txt4->setFillColor(Color::Yellow);
    txt4->setCharacterSize(23);
    txt4->setString("Perfect;>");

    txt5->setFont(*font_manaspc);
    txt5->setFillColor(Color::Blue);
    txt5->setCharacterSize(23);
    txt5->setString("Master;)");

    intruct1 = new Text();
    intruct2 = new Text();
    intruct3 = new Text();
    intruct4 = new Text();
    pause = new Text();

    intruct1->setFont(*font_arcade);
    intruct2->setFont(*font_arcade);
    intruct3->setFont(*font_arcade);
    intruct4->setFont(*font_arcade);
    pause->setFont(*font_arcade);

    intruct1->setFillColor(Color::White);
    intruct2->setFillColor(Color::White);
    intruct3->setFillColor(Color::White);
    intruct4->setFillColor(Color::White);
    pause->setFillColor(Color::White);

    intruct1->setCharacterSize(30);
    intruct2->setCharacterSize(30);
    intruct3->setCharacterSize(30);
    intruct4->setCharacterSize(30);
    pause->setCharacterSize(30);

    intruct1->setString("UP");
    intruct2->setString("DOWN");
    intruct3->setString("LEFT");
    intruct4->setString("RIGHT");
    pause->setString("PAUSE");

    intruct1->setPosition(sprite_intruct->getPosition().x + sprite_key->getGlobalBounds().width * 2 + 20, sprite_intruct->getPosition().y - sprite_key->getGlobalBounds().height * 2);
    intruct2->setPosition(sprite_intruct->getPosition().x + sprite_key->getGlobalBounds().width * 5 - intruct2->getGlobalBounds().width, sprite_intruct->getPosition().y + sprite_key->getGlobalBounds().height * 5);
    intruct3->setPosition(sprite_intruct->getPosition().x - sprite_key->getGlobalBounds().width * 3 + 5, sprite_intruct->getPosition().y + sprite_key->getGlobalBounds().height * 3 - 10);
    intruct4->setPosition(sprite_intruct->getPosition().x + sprite_key->getGlobalBounds().width * 7 + 5, sprite_intruct->getPosition().y + sprite_key->getGlobalBounds().height * 3 - 10);
    pause->setPosition(sprite_pause->getPosition().x + sprite_key->getGlobalBounds().width * 2 + 30, sprite_pause->getPosition().y + 15);



    buffer = new SoundBuffer();
    sound_eatfood = new Sound();
    sound_die = new Sound();
    buffer_die = new SoundBuffer();

    buffer->loadFromFile("audio/eatfood.ogg");
    buffer_die->loadFromFile("audio/message.ogg");

    sound_eatfood->setBuffer(*buffer);
    sound_eatfood->setVolume(30.f);
    sound_die->setBuffer(*buffer_die);
    sound_die->setVolume(30.f);
}

Screen_Classic::~Screen_Classic()
{
    delete[] s;
    delete f;
    delete sprite_white;
    delete sprite_red, sprite_red2;
    delete sprite_purple;
    delete sprite_green;
    delete sprite_intruct;
    delete sprite_pause;
    delete sprite_key;

    delete font_arcade;
    delete font_manaspc;

    delete intruct1, intruct2, intruct3, intruct4, pause;
    delete txt_score, txt, txt2, txt3, txt4, txt5;

    delete sound_eatfood;
    delete sound_die;
    delete buffer;
    delete buffer_die;

    delete t1, t2, t3, t4, t5, t_intruct, t_pause, text_key;
}

void Screen_Classic::update()
{
    // Update snake's body position
    for (int i = length; i > 0; --i)
    {
        s[i].x = s[i - 1].x;
        s[i].y = s[i - 1].y;
    }

    // Update snake's head position
    if (direction == DIRECTION::DIRECTION_UP) s[0].y -= 1;
    else if (direction == DIRECTION::DIRECTION_LEFT) s[0].x -= 1;
    else if (direction == DIRECTION::DIRECTION_RIGHT) s[0].x += 1;
    else if (direction == DIRECTION::DIRECTION_DOWN) s[0].y += 1;

    // Check whether steps remaining = 0
    tranfer_barrier();

    // Check whether snake eat food
    if ((s[0].x == f->x) && (s[0].y == f->y))
    {
        f->x = rand() % (N - 2) + 1; // Range is 1-> N-2
        f->y = rand() % (M - 2) + 1; // Range is 1-> M-2

        for (int i = 0; i < length; i++)
        {
            if (s[i].x == f->x && s[i].y == f->y)
            {
                f->x = rand() % (N - 2) + 1; // Range is 1-> N-2
                f->y = rand() % (M - 2) + 1; // Range is 1-> M-2
                i = -1;
            }
        }
        sound_eatfood->play();
        score += 10;
        length++;
        delay -= 0.002f;
        foodeating = true;
    }
    else { foodeating = false; }

    // Check whether snake's head has collision with border
    if (s[0].x >= N - 1) // Hit right border
    {
        cout << "Hit right border\n";
        gameOver();
    }
    if (s[0].x <= 0) // Hit left border
    {
        cout << "Hit left border\n";
        gameOver();
    }
    if (s[0].y >= M - 1) // Hit bottom border
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

    // Check whether snake's head has collision with border
    if (check_barrier()) {
        cout << "Hit barrier\n";
        gameOver();
    }

}

void Screen_Classic::draw_effect()
{
    // draw effect
    
    if (effect_count_down_1 > 0)
    {
        txt2->setPosition(txt->getPosition().x + txt->getLocalBounds().width + 16, txt->getPosition().y);
        window->draw(*txt2);
        effect_count_down_1--;
    }

    if (effect_count_down_2 > 0)
    {
        int ran = rand() % 3;
        switch (ran)
        {
        default:
            break;
        case 1:
            txt3->setPosition(txt_score->getPosition().x, txt_score->getPosition().y - 50);
            window->draw(*txt3);
            break;

        case 2:
            txt4->setPosition(txt_score->getPosition().x, txt_score->getPosition().y - 70);
            window->draw(*txt4);
            break;
        case 0:
            txt5->setPosition(txt_score->getPosition().x, txt_score->getPosition().y - 90);
            window->draw(*txt5);
            break;
        }
        effect_count_down_2--;
    }
}

void Screen_Classic::draw_background()
{
    // Draw background
    for (int x = width_board - img_size; x > -1; x -= img_size) { sprite_purple->setPosition(x, 0);  window->draw(*sprite_purple); } // Draw top Border
    for (int y = height - 2 * img_size; y > 0; y -= img_size)
    {
        sprite_purple->setPosition(0, y);  window->draw(*sprite_purple); // Draw left Border
        for (int x = width_board - 2 * img_size; x > 0; x -= img_size)
        {
            sprite_white->setPosition(x, y);  window->draw(*sprite_white);
        }
        sprite_purple->setPosition(width_board - img_size, y);  window->draw(*sprite_purple); // Draw right Border
    }
    for (int x = width_board - img_size; x > -1; x -= img_size) { sprite_purple->setPosition(x, height - img_size);  window->draw(*sprite_purple); } // Draw bottom Border

}

void Screen_Classic::draw_snake()
{
    // Draw snake's body
    for (int i = 1; i < length; i++)
    {
        sprite_red2->setPosition(s[i].x * img_size, s[i].y * img_size);  window->draw(*sprite_red2);
    }
    // Draw snkae's head
    sprite_red->setPosition(s[0].x * img_size, s[0].y * img_size);  window->draw(*sprite_red);
}

void Screen_Classic::draw_food()
{
    // Draw food
    sprite_green->setPosition(f->x * img_size, f->y * img_size);  window->draw(*sprite_green);
}

void Screen_Classic::draw_UI()
{
    // Draw UI
    txt->setString(std::to_string(score)); window->draw(*txt); 
    window->draw(*txt_score);

    window->draw(*intruct1);
    window->draw(*intruct2);
    window->draw(*intruct3);
    window->draw(*intruct4);
    window->draw(*pause);
    window->draw(*sprite_intruct);
    window->draw(*sprite_pause);
}

void Screen_Classic::draw()
{
#pragma region Draw

    window->clear();

    draw_background();
    draw_food();
    draw_barrier();
    draw_effect();
    draw_snake();
    draw_UI();
    draw_Steps();

    window->display();
#pragma endregion
}

void Screen_Classic::gameOver()
{
    cout << "Game Over\n";
    isAlive = false;
}

int Screen_Classic::start()
{
    int op = 1;
    Clock clock;
    Clock clock2;

    Texture temp_texture;
    temp_texture.create(window->getSize().x, window->getSize().y);

    sf::Font font_gomarice;
    sf::Font font_invasion;

    if (!font_gomarice.loadFromFile("Fonts/gomarice_game_continue_02.ttf")) std::cout << "Cannot load font gomarice_game_continue_02.ttf\n";
    if (!font_invasion.loadFromFile("Fonts/INVASION2000.TTF")) std::cout << "Cannot load font INVASION2000.TTF\n";
    
    while (op)
    {
        sound_die->play();

        srand(time(0));

        isAlive = true;

        float timer = 0;

        score = 0;
        length = 3;

        for (int i = 0; i < length; i++)
        {
            s[i].x = 15;
            s[i].y = 15;
        }

        timer = delay * 1.1;
        f->x = 10;
        f->y = 10;

        effect_count_down_1 = effect_count_down_2 = 0;

        DIRECTION temp_d = DIRECTION::DIRECTION_RIGHT;
        direction = temp_d;

        while (window->isOpen() && isAlive)
        {

            float time = clock.getElapsedTime().asSeconds();
            clock.restart();

            timer += time;
            Event e;
            while (window->pollEvent(e))
            {
                if (e.type == Event::Closed)
                {
                    window->close();
                    return 0;
                }
            }

#pragma region Get Input
            if (Keyboard::isKeyPressed(Keyboard::Left)) temp_d = DIRECTION::DIRECTION_LEFT;
            else if (Keyboard::isKeyPressed(Keyboard::Right)) temp_d = DIRECTION::DIRECTION_RIGHT;
            else if (Keyboard::isKeyPressed(Keyboard::Up)) temp_d = DIRECTION::DIRECTION_UP;
            else if (Keyboard::isKeyPressed(Keyboard::Down)) temp_d = DIRECTION::DIRECTION_DOWN;
            // Check pause keyboard
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                while (Keyboard::isKeyPressed(Keyboard::Escape)) {/*Wait for key up*/ }
                cout << "Pressed Pause\n";
                draw();

                temp_texture.update(*window);

                Selection selection(window, width_board, height, 0.0f, 0.0f, &temp_texture);
                selection.setTitle_String("Paused Game");
                selection.setTitle_Color(Color::Red);
                selection.setTitle_Size(150);
                selection.setTitle_Outline(Color::Black, 3.0f);
                selection.setOptions_List(new vector<std::string>{ "MAIN MENU", "CHANGE LEVEL" , "CONTINUE" });
                selection.setOption_Font(font_invasion);
                selection.setOption_Color(Color::Blue);
                selection.setOption_Size(65);
                selection.setOption_OutLine(Color::Black, 3.0f);
                selection.setCursor_Color(Color::Green);
                selection.setCursor_Outline(Color::Black, 3.0f);

                selection.load();

                if (selection.getOption() == 0)// Main menu
                {
                    cout << "Back to Main Menu\n";
                    return 0;
                }
                else if (selection.getOption() == 1) // Change Level
                {
                    return 1;
                }
                else  if (selection.getOption() == 2)/* Resume*/
                {
                    cout << "Resumed\n";
                    timer = 1.1f * delay;
                }
                else if (!window->isOpen())
                {
                    cout << "Window has been closed\n";
                }
                else cout << "ERROR: Out of range\n";
            }
#pragma endregion

            if (timer > delay)
            {
                if (!((temp_d == DIRECTION::DIRECTION_LEFT && direction == DIRECTION::DIRECTION_RIGHT)
                    || (temp_d == DIRECTION::DIRECTION_RIGHT && direction == DIRECTION::DIRECTION_LEFT)
                    || (temp_d == DIRECTION::DIRECTION_UP && direction == DIRECTION::DIRECTION_DOWN)
                    || (temp_d == DIRECTION::DIRECTION_DOWN && direction == DIRECTION::DIRECTION_UP)))
                {
                    if (direction != temp_d) isKeychanged = true;
                    direction = temp_d;
                }

                // Delay time has reached, reset timer
                timer = 0;
                // Update position of object 
                update();
                isKeychanged = false;
                if (foodeating)
                {
                    effect_count_down_1 = 7;
                    effect_count_down_2 = 18;
                }
                draw();
            }
            else
            {
                // Wait delay time
            }

        }
        if (window->isOpen()) {
            if (!isAlive)
            {
                sound_die->play();
                draw();
                // Player is died, ask if player want to try again
				if (is_high_score(score))
				{
					std::string tmp = high_score_board::get_player_name(*window, width_board, height, score);
					write_to_file(tmp, score);
				}
                draw();
                draw();
                delete_barrier();

                temp_texture.update(*window);

                Selection selection(window, width_board, height, 0.0f, 0.0f, &temp_texture);
                selection.setTitle_String("Game Over");
                selection.setTitle_Color(Color::Red);
                selection.setTitle_Size(150);
                selection.setTitle_Outline(Color::Black, 3.0f);
                selection.setOptions_List(new vector<std::string>{ "MAIN MENU", "HIGH SCORE" , "CHANGE LEVEL", "TRY AGAIN" });
                selection.setOption_Font(font_invasion);
                selection.setOption_Color(Color::Blue);
                selection.setOption_Size(65);
                selection.setOption_OutLine(Color::Black, 3.0f);
                selection.setCursor_Color(Color::Green);
                selection.setCursor_Outline(Color::Black, 3.0f);

                while (window->isOpen())
                {
                    selection.load();
                    if (selection.getOption() == 2) // Change level
                    {
                        return 1;
                    }
                    else if (selection.getOption() == 1) // High Score board
                    {
                        cout << "Launch High Score board\n";
                        draw();
                        high_score_board high(window, width_board + width_UI, height);

                        high.load();
                    }
                    else if (selection.getOption() == 0)// Main Menu
                    {
                        cout << "Back to Main Menu\n";
                        return 0;
                    }
                    else if (selection.getOption() == 3)// Play Again
                    {
                        // getOption() == 3
                        cout << "Play again\n";
                        op = 1;
                    }
                    else if (!window->isOpen())
                    {
                        cout << "Window has been closed\n";
                    }
                    else cout << "ERROR: Out of range\n";
                   
                }
            }
            else
            {
                cout << " Not died yet but the start()'s loop has been break?\n";
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    return 0;
}

void Screen_Classic::draw_barrier() {
    return;
}

void Screen_Classic::tranfer_barrier() {
    return;
}

bool Screen_Classic::check_barrier() {
    return false;
}

void Screen_Classic::delete_barrier() {
    return;
}

void Screen_Classic::draw_Steps() {
    return;
}

void Screen_Classic::print_Tips()
{    
    SoundBuffer* buffer_tip = new SoundBuffer();
    buffer_tip->loadFromFile("audio/beforegame.ogg");
    Sound* sound_tip = new Sound();
    sound_tip->setBuffer(*buffer);
    sound_tip->setVolume(30.f);

    sound_tip->play();

    Texture* t = new Texture();
    t->loadFromFile(getPath_Tip());

    Sprite* sprite_tip = new Sprite(*t);
    sprite_tip->setPosition(width_board / 2 - sprite_tip->getGlobalBounds().width / 2, height / 2 - sprite_tip->getLocalBounds().height / 2);

    Text* txt_ok = new Text();
    txt_ok->setFont(*font_manaspc);
    txt_ok->setString("> Okay");

    txt_ok->setFillColor(Color::Black);
    txt_ok->setOutlineColor(Color::Red);
    txt_ok->setOutlineThickness(3.0f);
    txt_ok->setCharacterSize(72);
    txt_ok->setPosition(width_board / 2 - txt_ok->getGlobalBounds().width / 2, sprite_tip->getPosition().y + sprite_tip->getGlobalBounds().height + 20);

    window->clear();

    draw_background();
    draw_UI();
    window->draw(*sprite_tip);
    window->draw(*txt_ok);

    window->display();

    while (window->isOpen())
    {
        Event e;
        while (window->pollEvent(e))
        {
            if (e.type == Event::Closed)
            {
                window->close();
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Enter))
        {
            while (Keyboard::isKeyPressed(Keyboard::Enter)) { /*Wait for key up*/ }
            break;
        }
    }

    delete t;
    delete sprite_tip;
    delete txt_ok;
    delete buffer_tip;
    delete sound_tip;
}