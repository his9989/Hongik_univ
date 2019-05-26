#pragma once
class Ticket {
public:
	int saveYear;
	int saveMonth;
	int saveDay;
	int saveHour;
	int saveMinute;
	void setData(int y, int m, int d, int h, int mi) {
		saveYear = y;
		saveMonth = m;
		saveDay = d;
		saveHour = h;
		saveMinute = mi;
	}
	int getYear() {
		return saveYear;
	}
	int getMonth() {
		return saveMonth;
	}
	int getDay() {
		return saveDay;
	}
	int getHour() {
		return saveHour;
	}
	int getMinute() {
		return saveMinute;
	}
};