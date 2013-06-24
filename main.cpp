#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<vector>
#include<algorithm>
#include "champion.h"
using namespace std;

struct team_comp
{
	short engage;
	short disengage;
	short aoe;
	short indv_cc;
	short health;
	short ad;
	short ap;
	short burst;
	short carry;
};

team_comp checkTeamComp(vector<Champion>);
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
	ifstream file(fileName.c_str());
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
	else
	{		
		cout << "enter their first pick:" << endl;
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
		cout << "Enter their next two picks:" << endl;
		opposingChampions.push_back(getPick(champions, championNames));
		opposingChampions.push_back(getPick(champions, championNames));
		evaluate(playerChampions, opposingChampions);
		cout << "Enter your last pick:" << endl;
		playerChampions.push_back(getPick(champions, championNames));
	}
}

void evaluate(vector<Champion> playerChampions, vector<Champion> opposingChampions)
{
//	for(int i = 0; i < playerChampions.size(); i++)
//	{
//		cout << playerChampions[i].getName() << endl;
//	}
//	
//	for(int i = 0; i < opposingChampions.size(); i++)
//	{
//		cout << opposingChampions[i].getName() << endl;
//	}
	team_comp comp = checkTeamComp(opposingChampions);
	cout << "Their disengage: " << comp.disengage << endl;
}

team_comp checkTeamComp(vector<Champion> champions)
{
	team_comp comp;
	for (int j = 1; j < SIZE; j++)
	{
		float value = 0;
		int total = 0;
		for (int i = 0; i < champions.size(); i++)
		{
			total += champions[i].getValue(j);
		}
		value = (float)total / champions.size();
		switch (j)
		{
			case ESCAPE_POS:
				comp.disengage = value;
				break;
			case GAP_CLOSING_POS:
				comp.engage = value;
				break;
			case AOE_DMG_POS:
				comp.aoe += value / 2.0;
				break;
			case AOE_CC_POS:
				comp.aoe += value / 2.0;
				break;
			case INDV_CC_POS:
				comp.indv_cc = value;
				break;
			case HEALTH_POS:
				comp.health = value;
				break;
			case AD_POS:
				comp.ad = value;
				break;
			case AP_POS:
				comp.ap = value;
				break;
			case BURST_POS:
				comp.burst = value;
				break;
			case CARRY_POS:
				comp.carry = value;
				break;
			
		}
	}
	return comp;
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
