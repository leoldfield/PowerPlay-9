#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <map>

#include "Item.h"
#include "Object.h"
#include "Player.h"
#include "Monster.h"

std::vector<Object*> createMonsters(std::vector<Object*> objects);

void displayBattle(std::vector<Object*> objects);
void bringOutYourDead(std::vector<Object*> objects);


int main()
{
	std::vector<Object*> objects;
	Player newPlayer;
	objects.push_back(&newPlayer);

	while (!(*objects.at(0)).isDead())
	{
		static_cast<Player*>(objects.at(0))->levelUp();
		createMonsters(objects);

		std::cout << objects.size() << " monster(s) approaches!!" << std::endl;
		system("pause");
		system("cls");

		while (!(*objects.at(0)).isDead() && objects.size() > 0)
		{

			displayBattle(objects);

			static_cast<Player*>(objects.at(0))->update((*objects.at(0)), objects);

			bringOutYourDead(objects);

			std::cout << std::endl;
			std::for_each((*monsters).begin(), (*monsters).end(), [&](Monster& monster)
				{
					monster.update(*player, *monsters);
				});

			system("PAUSE");
			system("CLS");
		}
	}

	if ((*objects.at(0)).isDead())
	{
		std::cout << "You Have Died" << std::endl;
	}
	if ((*objects.at(0)).isDead() && objects.size() == 1)
	{
		std::cout << "BUT" << std::endl;
	}
	if (objects.size() == 1)
	{
		std::cout << "You have killed the monsters!!!" << std::endl;
	}
	system("PAUSE");

}



void displayBattle(std::vector<Object*> objects)
{
	Object::nameOnly = false; //TODO:: get rid of this and just dot he full cout.
	std::cout << objects.at(0) << std::endl;
	std::cout << std::endl << "  Monsters: " << std::endl;
	{
		int i{ 1 };
		std::for_each(objects.begin()+1, objects.end(), [&](const Monster& monster)
			{
				std::cout << "   " << i << ". " << monster << std::endl;

				i++;
			});
	}
}

std::vector<Object*> createMonsters(std::vector<Object*> objects)
{
	std::normal_distribution<double> randomNumMonsters((double)(*objects.at(0)).getLevel(), (*objects.at(0)).getLevel() / 2.0);
	std::vector<Monster> ogMonsters(std::max(1, (int)randomNumMonsters(Object::engine)));
	std::generate(ogMonsters.begin(), ogMonsters.end(), [&]()
		{
			return Monster(objects.at(0));
		});

	std::vector<Monster*> monsters{ &ogMonsters };

	//appends monsters to the end of objects
	objects.insert(objects.end(), monsters.begin(), monsters.end());

	return objects;
}


void bringOutYourDead(std::vector<Object*> objects)
{
	Object::nameOnly = true;
	(objects).erase(
		std::remove_if(objects.begin(), objects.end(),
			[](Object* monster)
			{
				if ((*monster).isDead())
				{

					std::cout << monster << " has died!!!" << std::endl << std::endl;
					return true;
				}
				return false;
			}),
		objects.end());

}
