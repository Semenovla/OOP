#include <iostream>
#include "Container.h"
#include <time.h>

class ParentClass {
protected: 
	int field;
public:
	ParentClass() {
		field = 0;
	}
	int getter() {
		return field;
	}
	void setter(int field) {
		this->field = field;
	}
};

class ChildClass: public ParentClass {
public:
	ChildClass() : ParentClass() {
		field = 1;
	}
};

int main() {
	setlocale(LC_ALL, "rus");
	Container <ParentClass> container;
	srand(time(0));
	int count = 100;
	double timer = 0;
	clock_t start = clock();
	int addCount = 0;
	int delCount = 0;
	int setCount = 0;
	int getCount = 0;
	
	while (count < 10001){
		for (int i = 0; i < count; i++) {
			//container.addObject(rand() % container.getSize(), new ChildClass()); // добавление элемента
			//std::cout << "addObject" << "\n";
			//addCount++;
			switch (rand() % 2) {
			case 0:
				container.addObject(rand() % container.getSize(), new ChildClass()); // добавление элемента
				std::cout << "addObject" << "\n";
				addCount++;
				break;
			case 1:
				switch (rand() % 3){
				case 0:
					container.setObject(rand() % container.getSize(), new ChildClass()); // setter
					std::cout << "setObject" << "\n";
					setCount++;
					break;
				case 1:
					container.getObject(rand() % container.getSize()); // getter
					std::cout << "getObject" << "\n";
					getCount++;
					break;
				case 2:
					container.deleteObject(rand() % container.getSize()); // удаление
					std::cout << "deleteObject" << "\n";
					delCount++;
					break;
				
				}
			}
		}
		clock_t end = clock();
		timer += (double)(end - start) / CLOCKS_PER_SEC;
		std::cout.precision(15);
		std::cout.setf(std::ios::showpoint);
		std::cout << count << "\t" << "Время работы:   " << timer << "\t" << "Кол-во элементов: " << container.getSize() << "\n";
		
		system("pause");
		count *= 10;
	}
	return 0;
}


