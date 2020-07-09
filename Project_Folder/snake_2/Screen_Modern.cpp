#include "Screen_Modern.h"
Screen_Modern::Screen_Modern(RenderWindow* window, int n, int m, float img_size, float width_UI) :Screen_Classic(window, n, m, img_size, width_UI) {
    steps_remaining = 3;
    texture_barrier = new Texture;
    if (!texture_barrier->loadFromFile("images/purble.jpg")) {
        cout << "Not load from file images/purble.jbg";
    }
    sprite_barrier = new Sprite(*texture_barrier);
    sprite_barrier->scale(1.5f, 1.5f);

    //set draw step_remaining
    text_steps = new Text();
    text_steps->setFont(*font_arcade);
    text_steps->setFillColor(Color::White);
    text_steps->setCharacterSize(30);
    text_steps->setString("Steps  remain ");
    text_steps->setPosition(width_board + width_UI / 2 - txt_score->getLocalBounds().width, height / 2 + 48 * 2);

    txt_steps = new Text();
    txt_steps->setFont(*font_manaspc);
    txt_steps->setFillColor(Color::Magenta);
    txt_steps->setCharacterSize(23);
    txt_steps->setPosition(text_steps->getPosition().x + text_steps->getLocalBounds().width + 10, text_steps->getPosition().y + 5);
}
Screen_Modern::~Screen_Modern() {
    Screen_Classic::~Screen_Classic();
    delete texture_barrier;
    delete sprite_barrier;
}
void Screen_Modern::tranfer_barrier() {
    if (isKeychanged == true) steps_remaining--;
    if (steps_remaining == 0) {

        //tranfer form food to barrier
        Fruit* coor = new Fruit;
        coor->x = f->x;
        coor->y = f->y;
        barrier.push_back(*coor);

        //create new food
        f->x = rand() % (N - 2) + 1;
        f->y = rand() % (M - 2) + 1;
        int size_barrier = barrier.size();
        for (int i = 0; i < length; i++) {
            if (f->x == s[i].x && f->y == s[i].y) {
                f->x = rand() % (N - 2) + 1;
                f->y = rand() % (M - 2) + 1;
                i = -1;
            }
            else {
                for (int j = 0; j < size_barrier; j++) {
                    if (f->x == barrier[j].x && f->y == barrier[j].y) {
                        f->x = rand() % (N - 2) + 1;
                        f->y = rand() % (M - 2) + 1;
                        i = -1;
                        break;
                    }
                }
            }
        }
        steps_remaining = 3;
    }
}

void Screen_Modern::draw_barrier() {

    int size_barrier = barrier.size();

    for (int i = 0; i < size_barrier; i++) {
        sprite_barrier->setPosition(barrier[i].x * img_size, barrier[i].y * img_size);
        window->draw(*sprite_barrier);
    }
}

bool Screen_Modern::check_barrier() {
    if (foodeating) steps_remaining = 3;
    int size_barrier = barrier.size();
    for (int i = 0; i < size_barrier; i++) {
        if (s[0].x == barrier[i].x && s[0].y == barrier[i].y) {
            isAlive = false;
            cout << "Snake hit the barrier\n";
            return true;
        }
    }
    return false;
}

void Screen_Modern::delete_barrier() {
    barrier.clear();
}

void Screen_Modern::draw_Steps() {
    window->draw(*text_steps);
    txt_steps->setString(std::to_string(steps_remaining)); window->draw(*txt_steps);
}