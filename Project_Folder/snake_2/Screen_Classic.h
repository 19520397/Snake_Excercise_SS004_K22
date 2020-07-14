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
	Sound* sound_die;
	SoundBuffer* buffer_die;
	SoundBuffer* buffer;

	const std::string path_tip = "images/tip_classic.png";

public:
	Screen_Classic(RenderWindow* window, int n, int m, float img_size, float width_UI);
	~Screen_Classic();
	int getScore() { return score; }
	virtual const std::string getPath_Tip() { return path_tip; }
	virtual void write_to_file(std::string tmp, int score)
	{

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

	}
	virtual bool is_high_score(int score) {
		return high_score_board::is_high_score_classic(score);
	}
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

