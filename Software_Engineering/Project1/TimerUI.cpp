#include "stdafx.h"
#include<cstdio>
#include "TimerUI.h"
#include "Timer.h"


TimerUI::TimerUI(){}
TimerUI::~TimerUI(){}

struct currentTime {
	int year;
	int month;
	int day;
	int hour;
	int minute;
};

void TimerUI::checkTicket(string inputData) {
	// inputData�� �ڷ����� �°� ��ȯ
	string year = inputData.substr(0, 4);
	string month = inputData.substr(5, 7);
	string day = inputData.substr(8, 10);
	string hour = inputData.substr(11, 13);
	string minute = inputData.substr(14, 17);
	Timer timer;
	timer.checkToDeleteTicket(stoi(year), stoi(month), stoi(day), stoi(hour), stoi(minute));//����� �Ű����� �ѱ��� ����
}