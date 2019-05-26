#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include "Ticket.h"
#include "timer.h"
#include "ticketManager.h"
using namespace std;

#define MAX_STRING 32
#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"

void doTask();
void checkYear();
FILE* in_fp, *out_fp;
Timer timer;
ticketManager tickManager;

int main() {
	in_fp = fopen(INPUT_FILE_NAME, "r+");
	out_fp = fopen(OUTPUT_FILE_NAME, "w+");
	doTask();
	return 0;
}

void doTask() {
	int menu_level_1 = 0, menu_level_2 = 0;
	int is_program_exit = 0;

	while (!is_program_exit) {
		fscanf(in_fp, "%d %d", &menu_level_1, &menu_level_2);
		switch (menu_level_1) {
		case 5:
		{
			cout << menu_level_1 << ", " << menu_level_2 << endl;
			checkYear();
			break;
		}
		case 1:
		{
			cout << menu_level_1 << ", " << menu_level_2 << endl;
			cout << "finish" << endl;
			is_program_exit = 1;
			break;
		}
		}
	}
}

void checkYear() {
	// 현재시갑 입력부 구현
	char temp[17];
	fscanf(in_fp, "%s", temp);
	string year(temp, temp + 4);
	string month(temp + 5, temp + 7);
	string day(temp + 8, temp + 10);
	string hour(temp + 11, temp + 13);
	string minute(temp + 14, temp + 16);
	cout << year << ", " << month << ", " << day << ", " << hour << ", " << minute << endl;
	timer.setData(stoi(year), stoi(month), stoi(day), stoi(hour), stoi(minute));

	// 티켓 입력 부분 대신 임시 구현
	Ticket *ticket1 = new Ticket();
	Ticket *ticket2 = new Ticket();
	ticket1->setData(2018, 3, 1, 12, 0);
	ticket2->setData(2019, 4, 1, 12, 0);
	tickManager.setTicketlist(*ticket1);
	tickManager.how_many = 1;
	tickManager.setTicketlist(*ticket2);
	tickManager.how_many = 2;

	// 현재시간 체크용
	cout << "current Time : " << timer.currentYear << ", " << timer.currentMonth << ", " << timer.currentDay << ", " << timer.currentHour << ", " << timer.currentMinute << endl << endl;
	for (int i = 0; i < tickManager.how_many; i++) {
		int _year = tickManager.gerTicketlist(i).getYear();
		int _month = tickManager.gerTicketlist(i).getMonth();
		int _day = tickManager.gerTicketlist(i).getDay();
		int _hour = tickManager.gerTicketlist(i).getHour();
		int _minute = tickManager.gerTicketlist(i).getMinute();

		cout << i << "'s Time : " << _year << ", " << _month << ", " << _day << ", " << _hour << ", " << _minute << endl;
		if (timer.currentYear > _year + 1) {
			cout << "delete : " << i << endl;
		}
		else if (timer.currentYear == _year + 1) {
			if (timer.currentMonth > _month) {
				cout << "delete : " << i << endl;
			}
			else if (timer.currentMonth == _month) {
				if (timer.currentDay > _day) {
					cout << "delete : " << i << endl;
				}
				else if (timer.currentDay == _day) {
					if (timer.currentHour > _hour) {
						cout << "delete : " << i << endl;
					}
					else if (timer.currentHour == _hour) {
						if (timer.currentMinute > _minute) {
							cout << "delete : " << i << endl;
						}
					}
				}
			}
		}
		cout << endl;
	}
}