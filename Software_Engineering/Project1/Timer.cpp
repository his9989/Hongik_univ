#include "stdafx.h"
#include "Timer.h"
#include "Ticket.h"

Timer::Timer(){}
Timer::~Timer(){}

void Timer::checkToDeleteTicket(int year, int month, int day, int hour, int minute) {
	// Timer�ȿ� ������ ������ ���� �ֵ��� ��׸� �����ؾߵȴ�.
	// Ticket�� ���� �̰� �Ű������� ������ �ʰ�, Ƽ���ʿ��� Ÿ�̸ӿ� �����ؼ� ������ ��ߵȴ�.
	Ticket ticket;
	ticket.deleteTicket(year, month, day, hour, minute);
}

int Timer::getDate() {
	return this->year, this->month, this->day, this->hour, this->minute;
}