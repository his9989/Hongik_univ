#include "stdafx.h"
#include"Ticket.h"
#include"Timer.h"
using namespace std;

Ticket::Ticket(){}
Ticket::~Ticket(){}

// �ӽ�
struct TicketData {
	int year;
	int month;
	int day;
	int hour;
	int minute;
};

void compare(TicketData, int, int, int, int, int);

void Ticket::deleteTicket(int year, int month, int day, int hour, int minute) {
	// ��� �ݷ��Ϳ� Ȩ�� �ݷ��͸� �ҷ����� ȣ��� ���� �ʿ�
	// ����� �ӽ÷� Ƽ�ϵ����Ͷ�� ����ü ���
	TicketData t1, t2;
	t1.year = 2018, t1.month = 01, t1.day = 01, t1.hour = 11, t1.minute = 00;
	t2.year = 2019, t2.month = 05, t2.day = 11, t2.hour = 10, t2.minute = 00;
	for (int i = 0; i < 1; i++) { // member �ݷ��� ���� ���ͷ����ͷ� �湮�ϴ� ����
		for (int j = 0; j < 1; j++) { // member ���� �ϳ��� Ƽ�� �ݷ��� ���� ���ͷ����ͷ� �湮�ϴ� ����
			cout << "delete?" << endl;
			compare(t1, year, month, day, hour, minute);
		}
	}
	for (int i = 0; i < 1; i++) { // Ȩ�� �ݷ��� ���� ���ͷ����ͷ� �湮�ϴ� ����
		for (int j = 0; j < 1; j++) { // Ȩ�� ���� �ϳ��� Ƽ�� �ݷ��� ���� ���ͷ����ͷ� �湮�ϴ� ����
			compare(t2, year, month, day, hour, minute);
		}
	}
}

// Ƽ�� ������ ���� �ʿ�
void compare(TicketData s, int year, int month, int day, int hour, int minute) {
	cout << s.year << " " << s.month << " " << s.day << " " << s.hour << " " << s.minute << endl;
	if (year > s.year + 1) {
		cout << "delete " << endl;
	}
	else if (year == s.year+ 1) {
		if (month > s.month) {
			cout << "delete : " << endl;
		}
		else if (month == s.month) {
			if (day > s.day) {
				cout << "delete : " << endl;
			}
			else if (day == s.day) {
				if (hour > s.hour) {
					cout << "delete : " << endl;
				}
				else if (hour == s.hour) {
					if (minute > s.minute) {
						cout << "delete : " << endl;
					}
				}
			}
		}
	}
	cout << endl;
}