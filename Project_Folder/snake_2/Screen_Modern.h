#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
#include <string>
#include "Screen_Classic.h"

class Screen_Modern: public Screen_Classic {
private:
    std::vector<Fruit> barrier;
    int steps_remaining;
    Texture* texture_barrier = NULL;
    Sprite* sprite_barrier = NULL;
public:
    Screen_Modern(RenderWindow* window, int n, int m, float img_size, float width_UI);
    ~Screen_Modern();
    void draw_barrier();
    void tranfer_barrier();
    bool check_barrier();
    void reset_step();
    void delete_barrier();
};