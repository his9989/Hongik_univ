#include<iostream>
#include<string>
using namespace std;

class Tower{
private:
	int height;
public:
	Tower();
	Tower(int _height);
	int getHeight() {
		return height;
	}
	// Tower class의 멤버함수로 구현한 경우
	//Tower operator+ (Tower op2);

	// Tower class의 외부함수로 구현한 경우
	friend Tower operator+(Tower op1, Tower op2);
};

Tower::Tower() {
	height = 1;
}

Tower::Tower(int _height) {
	height = _height;
}

/*
// Tower class의 멤버함수로 구현한 경우
Tower Tower::operator+(Tower op2) {
	Tower temp;
	temp.height = this->height + op2.height;
	return temp;
}
*/

// Tower class의 외부함수로 구현한 경우
Tower operator+(Tower op1, Tower op2) {
	Tower tmp;
	tmp.height = op1.height + op2.height;
	return tmp;
}

int main() {
	Tower ta(10), tb(20), tc;
	cout << "Before the operation, the height of the tower was " << tc.getHeight() << endl;
	tc = ta + tb;
	cout << "After the operation, the height of the tower was " << tc.getHeight() << endl;
}
