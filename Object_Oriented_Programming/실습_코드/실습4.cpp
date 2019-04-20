#include<iostream>
using namespace std;

class Color {
	int red, green, blud;
public:
	Color() { red = green = 0; }
	Color(int r, int g, int b) {
		red = r, green = g, blud = b;
	}
	void setColor(int r, int g, int b) {
		red = r, green = g, blud = b;
	}
	void show() {
		cout << red << ", " << green << ", " << blud << endl;
	}
};

int main() {
	Color screenColor(255, 0, 0);
	Color *p;
	p = &screenColor;
	p->show();
	Color colors[3];
	p = colors;
	p[0].setColor(255, 0, 0);
	p[1].setColor(0, 255, 0);
	p[2].setColor(0, 0, 255);
	p[0].show();
	p[1].show();
	p[2].show();
}
