//#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include "TimerUI.h"
#include <ctime>

#define MAX_STRING 32
#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"

void doTask();

string currentTime = "";

int main() {
	doTask();
	return 0;
}

void doTask() {
	int menu_level_1 = 0, menu_level_2 = 0;
	int is_program_exit = 0;

	ofstream outFile(OUTPUT_FILE_NAME);
	ifstream inFile(INPUT_FILE_NAME);

	while (!is_program_exit) {
		char inputString[100] = { NULL, };
		inFile.getline(inputString, 100); // 100���� �ϴ� ��Ҿ��.. �������� ��ȯ ���
		menu_level_1 = inputString[0]-48; // �ƽ�Ű ��ȯ
		menu_level_2 = inputString[2]-48; // �ƽ�Ű ��ȯ
		// �������� �����ϴ� string ������ inputData�Դϴ�
		string inputData(inputString + 4 , 50); // 50���� �ϴ� ��Ҿ��.. �������� �ٲ���ؿ�...
		switch (menu_level_1) {
		case 1: {
			switch (menu_level_2) {
			case 1: {
				cout << menu_level_1 << ", " << menu_level_2 << ".";
				printf("ȸ������\n");
				cout << inputData << endl;
				break;
			}
			case 2: {
				cout << menu_level_1 << ", " << menu_level_2 << ".";
				printf("ȸ��Ż��\n");
				break;
			}
			}
			break;
		}
		case 2: {
			switch (menu_level_2) {
			case 1: {
				cout << menu_level_1 << ", " << menu_level_2 << ".";
				printf("�α���\n");
				cout << inputData << endl;
				break;
			}
			case 2: {
				cout << menu_level_1 << ", " << menu_level_2 << ".";
				printf("�α׾ƿ�\n");
				break;
			}
			}
			break;
		}
		case 3: {
			switch (menu_level_2) {
			case 1: {
				cout << menu_level_1 << ", " << menu_level_2 << ".";
				printf("�Ǹ�Ƽ�� ���\n");
				cout << inputData << endl;
				break;
			}
			case 2: {
				cout << menu_level_1 << ", " << menu_level_2 << ".";
				printf("���Ƽ�� ��ȸ\n");
				break;
			}
			}
			break;
		}
		case 4: {
			switch (menu_level_2) {
			case 1: {
				cout << menu_level_1 << ", " << menu_level_2 << ".";
				printf("Ƽ�� �˻�\n");
				cout << inputData << endl;
				break;
			}
			case 2: {
				cout << menu_level_1 << ", " << menu_level_2 << ".";
				printf("Ƽ�� ����\n");
				cout << inputData << endl;
				break;
			}
			case 3: {
				cout << menu_level_1 << ", " << menu_level_2 << ".";
				printf("��� ���� Ƽ�� �˻�\n");
				cout << inputData << endl;
				break;
			}
			case 4: {
				cout << menu_level_1 << ", " << menu_level_2 << ".";
				printf("��� ����\n");
				cout << inputData << endl;
				break;
			}
			case 5: {
				cout << menu_level_1 << ", " << menu_level_2 << ".";
				printf("���� ���� ��ȸ\n");
				break;
			}
			}	
			break;
		}
		case 5: {
			cout << menu_level_1 << ", " << menu_level_2 << ".";
			printf("����ð� ����\n");
			cout << inputData << endl;
			TimerUI timerUI;
			currentTime = inputData;
			timerUI.checkTicket(currentTime);
			break;
		}
		case 6: {
			switch (menu_level_2) {
			case 1: {
				cout << menu_level_1 << ", " << menu_level_2 << ".";
				printf("session ����\n");
				break;
			}
			case 2: {
				cout << menu_level_1 << ", " << menu_level_2 << ".";
				printf("guest session���� ����\n");
				break;
			}
			}
			break;
		}
		case 7: {
			cout << menu_level_1 << ", " << menu_level_2 << ".";
			printf("����\n");
			is_program_exit = 1;
			break;
		}
		}
	}
}