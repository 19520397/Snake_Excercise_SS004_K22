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
    Text* txt_steps = NULL;
    Text* text_steps = NULL;

    const std::string path_tip = "images/tip_modern.png";
    
public:
    Screen_Modern(RenderWindow* window, int n, int m, float img_size, float width_UI);
    ~Screen_Modern();
	void write_to_file(std::string tmp, int score) {

		//out put to file
		std::vector<int> score_vec;
		std::vector<std::string> name_vec;
		std::ifstream myfile_in("high_score/morden.txt");
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
		std::ofstream myfile("high_score/morden.txt");
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
	bool is_high_score(int score) {
		return high_score_board::is_high_score_modern(score);
	}
    const std::string getPath_Tip() { return path_tip; }
    void draw_barrier();
    void tranfer_barrier();
    bool check_barrier();
    void reset_step();
    void delete_barrier();
    void draw_Steps();
    
};