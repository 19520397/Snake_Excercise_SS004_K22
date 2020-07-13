#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
#include <string>
#include "Selection.h"
#include "high_score_board.h"
#include "GameManager.h"


using namespace sf;
using std::cin;
using std::cout;

class Screen_Classic
{
protected:
	enum class DIRECTION
	{
		DIRECTION_RIGHT, DIRECTION_UP, DIRECTION_LEFT, DIRECTION_DOWN
	};

	struct Snake
	{
		int x, y;
	};

	struct Fruit
	{
		int x, y;
	};

	int N;
	int M;

	float img_size;

	// Width of board in pixels
	float width_board;
	// Height of board in pixels
	float height;

	// Width of UI space in pixels
	float width_UI;

	int score;
	int lv = 2;
	bool isAlive = false;
	bool foodeating = false;
	bool isKeychanged = false;

	int effect_count_down_1; 
	int effect_count_down_2;

	Snake* s;
	DIRECTION direction;
	int length;
	float delay = 0.1;

	Fruit* f;

	RenderWindow* window;

	Texture *t1, *t2, *t3, *t4, *t5, *t_intruct, *t_pause, * text_key;

	Sprite* sprite_white;
	Sprite* sprite_red;
	Sprite* sprite_red2;
	Sprite* sprite_purple;
	Sprite* sprite_green;
	Sprite* sprite_intruct;
	Sprite* sprite_pause;
	Sprite* sprite_key;

	Font* font_arcade;
	Font* font_manaspc;

	Text *intruct1, *intruct2, *intruct3, *intruct4, *pause;
	Text* txt_score, * txt, * txt2, * txt3, * txt4, * txt5;

	Sound* sound_eatfood;
	SoundBuffer* buffer;

	const std::string path_tip = "images/tip_classic.png";

public:
	
	Screen_Classic(RenderWindow* window, int n, int m, float img_size, float width_UI);
	~Screen_Classic();
	int getScore() { return score; }
	virtual const std::string getPath_Tip() { return path_tip; }
	void print_Tips();
	int start();
	void draw();
	void draw_effect();
	void draw_background();
	void draw_snake();
	void draw_food();
	void draw_UI();
	void gameOver();
	void update();

	//belong to class Barrier
	virtual void draw_barrier();
	virtual void tranfer_barrier();
	virtual bool check_barrier();
	virtual void delete_barrier();
	virtual void draw_Steps();
};

