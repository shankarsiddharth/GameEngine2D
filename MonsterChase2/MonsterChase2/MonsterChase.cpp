#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <crtdbg.h>
#include "Monster.h"
#include "Player.h"
#include "DataStructure/LinkedList.h"
#include "Initialization.h"

bool ReadInteger(int& OutInteger, int InMinimumValue = 1)
{
	int is_valid_input = scanf_s("%d", &OutInteger);
	fseek(stdin, 0, SEEK_END);
	if (is_valid_input == EOF)
	{
		return false;
	}
	else if (is_valid_input == 0)
	{		
		return false;
	}
	else if (OutInteger < InMinimumValue)
	{
		return false;
	}
	return true;
}

int GetNumberOfMonsters()
{
	int number_of_monsters;
	printf_s("\nHow many monsters to start: ");
	bool is_input_valid = ReadInteger(number_of_monsters, 1);
	while (!is_input_valid)
	{
		printf_s("Bad input. Please enter an integer greater than 0. How many monsters to start: ");
		is_input_valid = ReadInteger(number_of_monsters, 1);
	}
	return number_of_monsters;
}

//String GetNameForMonster(int monsterIndex)
//{
//	printf_s("\nEnter a name for monster %d: ", monsterIndex);
//
//	String name_for_monster;
//	name_for_monster.ReadUserInput();
//
//	while (name_for_monster.GetLength() == 0)
//	{
//		printf_s("\nEmpty name not allowed. Enter a name for monster %d: ", monsterIndex);
//		name_for_monster.ReadUserInput();
//	}
//	return name_for_monster;
//}

void GetNameForMonster(String* monster_name, int monsterIndex)
{	
	fseek(stdin, 0, SEEK_END);
	printf_s("\nEnter a name for monster %d : ", monsterIndex);		
	monster_name->ReadUserInput();

	while (monster_name->GetLength() == 0)
	{
		printf_s("Empty name not allowed. Enter a name for monster %d: ", monsterIndex);
		monster_name->ReadUserInput();
	}	
}

void GetNameForPlayer(String& object_name)
{
	fseek(stdin, 0, SEEK_END);
	printf_s("\nEnter a name for the player: ");
	object_name.ReadUserInput();
	while (object_name.GetLength() == 0)
	{
		printf_s("Empty name not allowed. Enter a name for player: ");
		object_name.ReadUserInput();
	}	
}

void Test()
{
	{
		/*String* s1 = new String();
		s1->ReadUserInput();
		printf_s("\n%p\n", s1);

		String* s2 = new String();
		s2->ReadUserInput();
		printf_s("\n%p\n", s2);
		s2->CopyString(s1->GetString());
		printf_s("\n%p\n", s2);

		delete s1;
		s1 = nullptr;

		printf_s("%s", s2->GetString());

		delete s2;
		s2 = nullptr;*/

		GameObject* go = new GameObject[2];
		{
			String s1, s2;
			s1.ReadUserInput();
			//go = new GameObject();
			go[0].SetName(s1.GetString());
			printf_s("\n%s", s1.GetString());
			s2.ReadUserInput();
			//go = new GameObject();
			go[1].SetName(s2.GetString());
			printf_s("\n%s", s2.GetString());
		}		
		
		printf_s("\n%s", go[0].GetName()->GetString());
		printf_s("\n%s", go[1].GetName()->GetString());

		if (go)
		{
			delete[] go;
			go = nullptr;
		}
	}
	_CrtDumpMemoryLeaks();
}

//void DisplayStats(const Monster* monsters, int monster_count, Player& player)
//{
//	printf_s("\n");
//	printf_s("\nMonsters:");
//	for (int i = 0; i < monster_count; i++)
//	{
//		printf_s("\n%s is at [ %d, %d]", 
//			monsters[i].GetName()->GetString(), 
//			monsters[i].GetPosition().X(),
//			monsters[i].GetPosition().Y());
//	}
//	printf_s("\n");
//	printf_s("\nPlayer:");
//	printf_s("\n%s is at [ %d, %d]",
//		player.GetName()->GetString(),
//		player.GetPosition().X(),
//		player.GetPosition().Y());
//	printf_s("\n");
//}

void DisplayStats(const LinkedList<Monster*> &monsters, int monster_count, Player& player)
{
	printf_s("\n");
	printf_s("\nMonsters:");
	for (int i = 0; i < monster_count; i++)
	{
		printf_s("\n%s is at [ %d, %d]",
			monsters[i]->GetName()->GetString(),
			monsters[i]->GetPosition().X(),
			monsters[i]->GetPosition().Y());
	}
	printf_s("\n");
	printf_s("\nPlayer:");
	printf_s("\n%s is at [ %d, %d]",
		player.GetName()->GetString(),
		player.GetPosition().X(),
		player.GetPosition().Y());
	printf_s("\n");
}

int GetRandomNumberInRange(int upper = 64, int lower = 0)
{
	int number = (rand() % (upper - lower + 1)) + lower;
	return number;
}

//void MoveMonsters(Monster* monsters, int monster_count, int GridX, int GridY)
//{
//	for (int i = 0; i < monster_count; i++)
//	{
//		int newX = GenerateRandomPositionInTheGrid(GridX, -GridX);
//		int newY = GenerateRandomPositionInTheGrid(GridY, -GridY);
//		monsters[i].SetPosition(Point2D(newX, newY));		
//	}
//}

//void MoveMonsters(LinkedList<Monster*> &monsters, int monster_count, int GridX, int GridY)
//{
//	for (int i = 0; i < monster_count; i++)
//	{
//		int newX = GetRandomNumberInRange(GridX, -GridX);
//		int newY = GetRandomNumberInRange(GridY, -GridY);
//		monsters[i]->SetPosition(Point2D(newX, newY));
//	}
//}

void MoveMonsters(LinkedList<Monster*>& monsters, int monster_count, int GridX, int GridY)
{	
	for (int i = 0; i < monster_count; i++)
	{		
		int randomDirection = rand() % 4;
		Point2D deltaPosition;
		switch (randomDirection)
		{
		case 0:
		{
			deltaPosition = Point2D(0, 1);
		}
		break;
		case 1:
		{
			deltaPosition = Point2D(-1, 0);
		}
		break;
		case 2:
		{
			deltaPosition = Point2D(0, -1);
		}
		break;
		case 3:
		default:
		{
			deltaPosition = Point2D(1, 0);
		}
		break;
		}
		Point2D newPos = monsters[i]->GetPosition() + deltaPosition;
		if (newPos.X() < -GridX)
		{
			newPos.X(GridX);
		}
		else if (newPos.X() > GridX)
		{
			newPos.X(-GridX);
		}
		if (newPos.Y() < -GridY)
		{
			newPos.Y(GridY);
		}
		else if (newPos.Y() > GridY)
		{
			newPos.Y(-GridY);
		}
		monsters[i]->SetPosition(newPos);
	}
}

void MovePlayer(Player& player, Point2D deltaPosition, int GridX, int GridY)
{
	Point2D newPos = player.GetPosition() + deltaPosition;
	if (newPos.X() < -GridX)
	{
		newPos.X(GridX);
	}
	else if (newPos.X() > GridX)
	{
		newPos.X(-GridX);
	}
	if (newPos.Y() < -GridY)
	{
		newPos.Y(GridY);
	}
	else if (newPos.Y() > GridY)
	{
		newPos.Y(-GridY);
	}
	player.SetPosition(newPos);
}

Monster* CreateNewMonster(int& total_newbie, int GridX, int GridY)
{
	total_newbie++;
	Monster* newMonster = new Monster();
	char c = '0' + total_newbie;
	char numberstring[] = { 'n','e','w','b','i','e', char(c),'\0'};
	//sprintf_s(numberstring, "%d", total_newbie);
	newMonster->SetName(numberstring);
	int newX = GetRandomNumberInRange(GridX, -GridX);
	int newY = GetRandomNumberInRange(GridY, -GridY);
	newMonster->SetPosition(Point2D(newX, newY));
	return newMonster;
}

void DisplayUserPrompt()
{
	printf_s("\nPress A to move left, D to move right, W to move up, S to move down or Q to quit");
}

void MonsterChase()
{	
	//_CrtSetBreakAlloc(120);
	{
		Engine::Initialize();

		int newbie_count = 0;
		int GridX = 64, GridY = 64;
		printf_s("\nWelcome to MonsterChase!\n");
		unsigned int number_of_monsters = GetNumberOfMonsters();

		LinkedList<Monster*> monsters;
		//Monster* monsters = new Monster[number_of_monsters];
		for (unsigned int monster_index = 0; monster_index < number_of_monsters; monster_index++)
		{
			Monster* monster = new Monster();
			monsters.insert(monster);
			String* name = new String();
			GetNameForMonster(name, monster_index);
			monsters[monster_index]->SetName(name->GetString());
			delete name;
			name = nullptr;
		}

		MoveMonsters(monsters, number_of_monsters, GridX, GridY);

		Player player;
		String player_name;
		GetNameForPlayer(player_name);
		player.SetName(player_name.GetString());		

		DisplayStats(monsters, number_of_monsters, player);

		do
		{			
			DisplayUserPrompt();

			int randomNumber = rand();
			if (randomNumber % 3 == 0)
			{
				if (number_of_monsters < INT_MAX)
				{
					Monster* newMonster = CreateNewMonster(newbie_count, GridX, GridY);
					monsters.insert(newMonster);
					number_of_monsters = (int)monsters.getLength();
				}
			}
			if (randomNumber % 2 == 0)
			{
				if (number_of_monsters > 0)
				{
					int randomNumber = GetRandomNumberInRange(number_of_monsters - 1);
					Monster* monsterToDelete = monsters[randomNumber];
					monsters.deleteNode(monsterToDelete);
					number_of_monsters = (int)monsters.getLength();
				}
			}

			char input_key = _getch();

			if (input_key == 'Q' || input_key == 'q')
			{
				break;
			}
			else if (input_key == 'W' || input_key == 'w')
			{				
				MoveMonsters(monsters, number_of_monsters, GridX, GridY);
				MovePlayer(player, Point2D(0, 1), GridX, GridY);
				//player.Move(Point2D(0, 1));
				DisplayStats(monsters, number_of_monsters, player);
			}
			else if (input_key == 'A' || input_key == 'a')
			{
				MoveMonsters(monsters, number_of_monsters, GridX, GridY);
				MovePlayer(player, Point2D(-1, 0), GridX, GridY);
				//player.Move(Point2D(-1, 0));
				DisplayStats(monsters, number_of_monsters, player);
			}
			else if (input_key == 'S' || input_key == 's')
			{				
				MoveMonsters(monsters, number_of_monsters, GridX, GridY);
				MovePlayer(player, Point2D(0, -1), GridX, GridY);
				//player.Move(Point2D(0, -1));
				DisplayStats(monsters, number_of_monsters, player);
			}
			else if (input_key == 'D' || input_key == 'd')
			{
				MoveMonsters(monsters, number_of_monsters, GridX, GridY);
				MovePlayer(player, Point2D(1, 0), GridX, GridY);
				//player.Move(Point2D(1, 0));
				DisplayStats(monsters, number_of_monsters, player);
			}
			else
			{
				printf_s("Unknown input");
			}
		} while (true);			
	}
	_CrtDumpMemoryLeaks();	
}

int main()
{	
	//Test();
	MonsterChase();
	return 0;
}
