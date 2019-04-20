#include<iostream>
#include<string>
using namespace std;

class Person {
private:
	string name;
	int height;
	int weight;
	static int num;
public:
	Person(string name = "Grace", int height = 160, int weight = 50);
/*
	Person(string name);
	Person(string name, int height);
	Person(string name, int height, int weight);
	*/
	void show() {
		cout << name << ", " << height << ", " << weight << endl;
	}
	static int getNumPerson() {
		return num;
	}
};

int Person::num = 0;

Person::Person(string name, int height, int weight) {
	this->name = name;
	this->height = height;
	this->weight = weight;
	this->num += 1;
}

/*
Person::Person(string name) {
	this->name = name;
	this->height = 160;
	this->weight = 50;
	this->num += 1;
}

Person::Person(string name, int height) {
	this->name = name;
	this->height = height;
	this->weight = 50;
	this->num += 1;
}

Person::Person(string name, int height, int weight) {
	this->name = name;
	this->height = height;
	this->weight = weight;
	this->num += 1;
}
*/

int main() {
	Person grace("Grace"), ashley("Ashley", 165), helen("Helen", 180, 60);
	cout << "Number of Persons : " << Person::getNumPerson() << endl;
	grace.show();
	ashley.show();
	helen.show();
}
