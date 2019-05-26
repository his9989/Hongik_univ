#pragma once

class Timer {
public:
	int currentYear;
	int currentMonth;
	int currentDay;
	int currentHour;
	int currentMinute;
	void setData(int y, int m, int d, int h, int mi) {
		currentYear = y;
		currentMonth = m;
		currentDay = d;
		currentHour = h;
		currentMinute = mi;
	}
};