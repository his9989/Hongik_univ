#pragma once

#include<iostream>
#include<string>
#include "Ticket.h"
using namespace std;

class ticketManager {
public:
	int how_many = 0;
	Ticket name[100] = { NULL, }; // Ticket ��ü�� ����
	void setTicketlist(Ticket p) {
		name[how_many] = p;
	}
	Ticket gerTicketlist(int i) {
		return name[i];
	}
};