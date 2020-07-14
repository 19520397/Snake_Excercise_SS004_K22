#include "Screen_Modern.h"
Screen_Modern::Screen_Modern(RenderWindow* window, int n, int m, float img_size, float width_UI) :Screen_Classic(window, n, m, img_size, width_UI) {
    steps_remaining = 3;
    texture_barrier = new Texture;
    if (!texture_barrier->loadFromFile("images/poison.png")) {
        cout << "Not load from file images/poison.png";
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
Screen_Modern::~Screen_Modern() {
    //Screen_Classic::~Screen_Classic();
    delete txt_steps;
    delete text_steps;
    delete texture_barrier;
    delete sprite_barrier;
}
void Screen_Modern::tranfer_barrier() {
    if (isKeychanged == true) steps_remaining--;
    if (steps_remaining == -1) {

        //tranfer form food to barrier
        Fruit coor;
        coor.x = f->x;
        coor.y = f->y;
        barrier.push_back(coor);

        //create new food
        f->x = rand() % (N - 2) + 1;
        f->y = rand() % (M - 2) + 1;
        int size_barrier = barrier.size();
        bool isOk = true;
        while (!isOk)
        {
            isOk=true;
            for (int i = 0; i < length; i++) {
                //check duplicated snake
                if (f->x == s[i].x && f->y == s[i].y) {
                    f->x = rand() % (N - 2) + 1;
                    f->y = rand() % (M - 2) + 1;
                    isOk = false;
                    break;
                }
                else {
                    //check duplicated barrier

                }
            }
            for (int j = 0; j < size_barrier && isOk; j++) {
                if (f->x == barrier[j].x && f->y == barrier[j].y) {
                    f->x = rand() % (N - 2) + 1;
                    f->y = rand() % (M - 2) + 1;
                    isOk = false;
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


