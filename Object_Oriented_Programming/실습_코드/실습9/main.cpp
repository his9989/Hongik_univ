#include<iostream>
#include"Shape.h"
#include"Rect.h"
#include"Line.h"
#include"Circle.h"
using namespace std;

int main() {
	Shape *pStart = NULL;
	Shape *pLast;

	pStart = new Circle(); // pStart 포인터는 Circle 객체
	pLast = pStart; // pLast 포인터는 Circle 객체
	
	pLast = pLast->add(new Rect()); // Circle 객체의 next는 Rect 객체. pLast 포인터는 Rect 객체
	pLast = pLast->add(new Circle()); // Rect의 next는 Cirle
	pLast = pLast->add(new Line());
	pLast = pLast->add(new Rect());
	// 결론적으로 Circle-Rect-Circle-Line-Rect 순서로 이어져있는 포인터 링크드 리스트

	Shape *p = pStart; // 시작점(Circle)을 p Shape 포인터에 저장
	while (p != NULL) {
		p->paint();
		p = p->getNext();
	}

	// 연결된 모든 도형 삭제
	p = pStart;
	while (p != NULL) {
		Shape *q = p->getNext();
		delete p;
		p = q;
	}
}