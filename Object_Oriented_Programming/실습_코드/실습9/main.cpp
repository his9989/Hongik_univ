#include<iostream>
#include"Shape.h"
#include"Rect.h"
#include"Line.h"
#include"Circle.h"
using namespace std;

int main() {
	Shape *pStart = NULL;
	Shape *pLast;

	pStart = new Circle(); // pStart �����ʹ� Circle ��ü
	pLast = pStart; // pLast �����ʹ� Circle ��ü
	
	pLast = pLast->add(new Rect()); // Circle ��ü�� next�� Rect ��ü. pLast �����ʹ� Rect ��ü
	pLast = pLast->add(new Circle()); // Rect�� next�� Cirle
	pLast = pLast->add(new Line());
	pLast = pLast->add(new Rect());
	// ��������� Circle-Rect-Circle-Line-Rect ������ �̾����ִ� ������ ��ũ�� ����Ʈ

	Shape *p = pStart; // ������(Circle)�� p Shape �����Ϳ� ����
	while (p != NULL) {
		p->paint();
		p = p->getNext();
	}

	// ����� ��� ���� ����
	p = pStart;
	while (p != NULL) {
		Shape *q = p->getNext();
		delete p;
		p = q;
	}
}