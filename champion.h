#include<string>
using namespace std;
#ifndef CHAMPION_H
#define CHAMPION_H

#define SIZE 13

#define NAME_POS 0
#define AD_POS 1
#define AP_POS 2
#define BURST_POS 3
#define CARRY_POS 4
#define HEALTH_POS 5
#define TRUE_DMG_POS 6
#define HEALTH_DMG_POS 7
#define GAP_CLOSING_POS 8
#define ESCAPING_POS 9
#define AOE_DMG_POS 10
#define INDV_CC_POS 11
#define AOE_CC_POS 12

class Champion
{
	public:
		int SetStats(string);
		string getName();
	private:
		string values[SIZE];
};
#endif
