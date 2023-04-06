//Это программный код на языке C++, который объявляет классы Point, Rectangle и Square и содержит функцию main, которая создает и уничтожает объекты этих классов.
#include <iostream>
#include <stdexcept>

using namespace std;
class Point
{// имеет два целочисленных поля x и y
public:
	int x, y;
	// Конструкторы класса Point
	Point()// Конструктор без параметров
	{
		cout << "Point()" << endl;
		x = 0;
		y = 0;

	};
	Point(int x, int y)// Конструктор с двумя параметрами
	{
		cout << "Point(int x, int y)" << endl;
		this->x = x;
		this->y = y;
	};
	Point(Point& point)// Копирующий конструктор
	{
		cout << "Point(Point &point)" << endl;
		x = point.x;
		y = point.y;
	};

	~Point() // Деструктор класса Point
	{
		printf_s("~Point()\t x=%d, y=%d\n", x, y);
	};

	void Offset(int dx, int dy);// Метод класса Point для изменения координат точки
};
// Определение метода Offset класса Point
void Point::Offset(int dx, int dy) {
	x += dx;
	y += dy;
};
// Объявление класса Rectangle
class Rectangle {
protected:
	double width, height;// Защищенные поля класса Rectangle
public:
	Point* Location;// Указатель на объект класса Point, который определяет местоположение верхнего левого угла прямоугольника
   
	Rectangle()// Конструкторы класса Rectangle
	{
		cout << "Rectangle()" << endl; // Конструктор без параметров
		Location = new Point();
		width = 0;
		height = 0;
	}

	Rectangle(int width, int height, Point& location) // Конструктор с параметрами
	{
		cout << "Rectangle(int x, int y, Point &location)" << endl;
		Location = new Point(location);
		this->width = width;
		this->height = height;
	}
	Rectangle(Rectangle& rectangle) // Копирующий конструктор
	{
		cout << "Rectangle(Rectangle &rectangle)" << endl;
		Location = new Point(*rectangle.Location);
		width = rectangle.width;
		height = rectangle.height;
	}
	//функции для получения и изменения ширины и высоты и площади
	double GetHeight() {//возвращают значения height и width 
		return height;
	}

	double GetWidth() {
		return width;
	}
	//задают значения height и width переданным аргументам
	void SetHeight(double height) {
		this->height = height;
	}

	void SetWidth(double width) {
		this->width = width;
	}
	//вычисляет и возвращает площадь прямоугольника
	double GetArea() {
		return width * height;
	}
	// Виртуальный метод класса Rectangle для изменения размеров прямоуголь
	virtual void Resize(double newWidth, double newHeight) {
		SetWidth(newWidth);
		SetHeight(newHeight);
	}
	//
	~Rectangle() {
		printf_s("~Rectangle()\tWidth=%lf, Height(высота)=%lf, Location={ %d, %d }\n", width, height, Location->x, Location->y);
		delete Location; //деструктор, который освобождает память, выделенную для Location.
	};
};

class Square : public Rectangle { //наследует класс треугольника и имеет один дополнительный конструктор и дополнительную функцию Resize. 
public:
	Square() {
		cout << "Square()" << endl;
	}
	//В конструкторе Square указывается ширина квадрата и его местоположение.
	Square(int width, Point& location) : Rectangle(width, width, location) {
		cout << "Square(int width, Point &location) : Rectangle(width, width, location)" << endl;
	}

	Square(Square& square) : Rectangle(square) {
		cout << "Square(Square &square) : Rectangle(square) \n" << endl;
	}

	~Square();
	//если нет деструктора, то просто вызовется конструктор класса-родителя

	virtual void Resize(double newWidth, double newHeight) override {
		if (newWidth != newHeight)
			throw invalid_argument("Высота должна быть равна ширине у квадрата \n");

		SetWidth(newWidth);
		SetHeight(newWidth);
	}
	//принимает два двойных значения.аргументы(newWidth и newHeight) и устанавливает значения width и height
	virtual void Resize(double newWidth) {
		Resize(newWidth, newWidth); //принимает два двойных значения. аргументы (newWidth и newHeight) и устанавливает значения width и height 
	}

};

Square::~Square() 
{
	printf_s("~Square()\tWidth=%lf, Location={ %d, %d }\n", width, Location->x, Location->y);
}


int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Создаются 3 объекта и уничтожаются \n " << endl;
	{
		Point p1;
		Point p2(22, 22);
		Point p3(p2);
	} //произойдут вызовы деструктора для p1-p3

	cout << endl;
	cout << "Создаются 3 объекта и уничтожатся вручную \n" << endl;
	Point* p4 = new Point();
	Point* p5 = new Point(55, 55);
	Point* p6 = new Point(*p5);

	p6->Offset(5, 5);

	delete p4;
	delete p5;
	delete p6;
	cout << endl;

	Point location(4, 8);

	cout << endl;
	cout << "Композиция: \n" << endl;
	//создается объект класса Square с шириной 5 и местоположением (4, 8), который изменяется с помощью метода Offset
	Square square(5, location);
	square.Location->Offset(6, 2);

	try
	{//Resize, которая должна вызвать исключение из-за несовпадения высоты и ширины, и сообщение об ошибке выводится в консоль.
		square.Resize(12, 13);
	}
	catch (const std::invalid_argument& e)
	{
		cerr << e.what() << endl;
	}

}