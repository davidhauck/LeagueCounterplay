#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<vector>
#include<algorithm>
#include "champion.h"
using namespace std;

void evaluate(vector<Champion>, vector<Champion>);
void LaunchChampionSelect(map<string, Champion>, vector<string>);
Champion getPick(map<string, Champion>, vector<string>);
int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Usage: <stats file path>" << endl;
		return 0;
	}

	map<string, Champion> champions;
	vector<string> championNames;

	string fileName = argv[1];
	string line;
	ifstream file("Counterplay.csv");
	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			Champion champion;
			champion.SetStats(line);
			champions[champion.getName()] = champion;
			championNames.push_back(champion.getName());
		}
		file.close();
	}
	else
	{
		cout << "Cannot find file: " << fileName << endl;
	}
	
	cout << "Welcome to League Counterplay!" << endl;
	cout << "Please enter an option:" << endl;
	cout << "1) Champion Select" << endl;
	string input;
	cin >> input;
	int value = atoi(input.c_str());
	switch (value)
	{
		case 1:
			LaunchChampionSelect(champions, championNames);
			break;
	}
}

void LaunchChampionSelect(map<string, Champion> champions, vector<string> championNames)
{
	vector<Champion> playerChampions;
	vector<Champion> opposingChampions;
	bool pickFirst = false;
	string input;
	while (input == "")
	{
		cout << "Do you pick first?(y/n)" << endl;
		cin >> input;
		if (input == "y")
		{
			pickFirst = true;
		}
		else if (input != "n")
		{
			input = "";
		}
	} 
	if (pickFirst)
	{
		cout << "enter your first pick:" << endl;
		playerChampions.push_back(getPick(champions, championNames));
		cout << "Enter their next two picks:" << endl;
		opposingChampions.push_back(getPick(champions, championNames));
		opposingChampions.push_back(getPick(champions, championNames));
		evaluate(playerChampions, opposingChampions);
		cout << "Enter your next two picks:" << endl;
		playerChampions.push_back(getPick(champions, championNames));
		playerChampions.push_back(getPick(champions, championNames));
		cout << "Enter their next two picks:" << endl;
		opposingChampions.push_back(getPick(champions, championNames));
		opposingChampions.push_back(getPick(champions, championNames));
		evaluate(playerChampions, opposingChampions);
		cout << "Enter your next two picks:" << endl;
		playerChampions.push_back(getPick(champions, championNames));
		playerChampions.push_back(getPick(champions, championNames));
		cout << "Enter their last pick:" << endl;
		opposingChampions.push_back(getPick(champions, championNames));
		evaluate(playerChampions, opposingChampions);
	}
}

void evaluate(vector<Champion> playerChampions, vector<Champion> opposingChampions)
{
	for(int i = 0; i < playerChampions.size(); i++)
	{
		cout << playerChampions[i].getName() << endl;
	}
	
	for(int i = 0; i < opposingChampions.size(); i++)
	{
		cout << opposingChampions[i].getName() << endl;
	}
}

Champion getPick(map<string, Champion> champions, vector<string> championNames)
{
	string input;
	while (input == "")
	{
		cout << ">";
		cin >> input;
		if (find(championNames.begin(), championNames.end(), input) != championNames.end())
		{
			return champions[input];
		}
		else
		{
			input = "";
			cout << "Invalid Champion Name, please try again" << endl;
		}
	}
}
