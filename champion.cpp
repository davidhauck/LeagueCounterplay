#include "champion.h"
#include<iostream>
#include<string>
using namespace std;

int Champion::SetStats(string args)
{
	int pos;
	int i = 0;
	string token;
	while((pos = args.find(",")) != string::npos)
	{
		if (i > 13)
		{
			return 0;
		}
		token = args.substr(0, pos);
		values[i] = token;
		args.erase(0, pos + 1);
		i++;
	}
	if (i < 13)
	{
		return 0;
	}
	return 1;
}

string Champion::getName()
{
	return values[NAME_POS];
}
