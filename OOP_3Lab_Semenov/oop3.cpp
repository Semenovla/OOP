#include <iostream>
#include <vector>
using namespace std;
class object {// класс-родитель для всех объектов в папке
public:
    object() {
        cout << "Конструктор по умолчанию класса object" << endl;
    }

    ~object() {
        cout << "Диструктор класса object" << endl;
    }
    virtual void name_yourself() {
        cout << "yooou Object" << endl;
    }
};
// класс папки
class folder {
public:
    object** objects;// массив указателей на объекты
    int folder_size;// размер папки

private:// увеличение размера массива объектов в папке
    void increase_array(object** old_objects, int array_size, int new_array_size) {
        // создаем новый массив нужного размера
        object** new_objects = new object * [new_array_size];
        // копируем элементы из старого массива в новый
        for (int i = 0; i < new_array_size; i++)
            if (i < array_size)
                new_objects[i] = old_objects[i];
            else
                new_objects[i] = nullptr;
        // обновляем размер папки и массив объектов в ней
        this->folder_size = new_array_size;
        this->objects = new_objects;
        // освобождаем память старого массива
        delete[] old_objects;
    }
public:// конструктор папки
    folder(int folder_size) {
        cout << "Конструктор по умолчанию класса folder" << endl;
        // инициализируем массив указателей на объекты в папке
        this->folder_size = folder_size;
        objects = new object * [folder_size];

        for (int i = 0; i < folder_size; i++) {
            objects[i] = nullptr;
        }
    }
    // проверка наличия объекта в папке по индексу
    bool check_by_index(int index) {
        if (index < folder_size) {
            if (objects[index] == nullptr) {
                return false;
            }
            else {
                return true;
            }
        }
        else {
            return false;
        }
    }
    // добавление объекта в папку по индексу
    void set_object(int index, object* something) {
        if (index >= this->folder_size) {
            // если индекс больше размера папки, увеличиваем размер массива объектов в папке
            increase_array(objects, folder_size, index + 1);
            objects[index] = something;
        }
        else
        {// если объект уже есть по данному индексу, добавляем новый объект в следующую свободную ячейку
            bool checker;
            checker = check_by_index(index);

            if (checker == false)
                objects[index] = something;
            else
                add_object(something);
        }
    }

    // добавление объекта в папку (в следующую свободную ячейку)
    void add_object(object* something) {
        bool mesto = false;
        for (int i = 0; i < folder_size; i++) {
            if (objects[i] == nullptr) {
                mesto = true;
                objects[i] = something;
                cout << "Элемент был добавлен в позицию " << i << endl;
            }
        }
        if (mesto == false) {
            set_object(folder_size, something);
            cout << "Элемент был добавлен в позицию " << folder_size << endl;
        }
    }

    // Функция для получения объекта по индексу
// Возвращает указатель на объект, если он существует, иначе возвращает nullptr
// Принимает индекс в качестве параметра
    object* get_object(int index) {
        if (check_by_index(index) == true)
            return objects[index];
        else
            return nullptr;
    }
    // Функция для удаления объекта по индексу
// Если объект существует, то он удаляется и устанавливается указатель на nullptr
// Иначе функция ничего не делает
// Принимает индекс в качестве параметра
    void delete_object(int index) {
        if (check_by_index(index) == true)
            objects[index] = nullptr;
        else
            return;
    }
    // Функция для получения первого объекта
// Возвращает указатель на первый объект, если он существует, иначе возвращает nullptr

    object* get_first_object() {
        if (check_by_index(0) == true)
            return objects[0];
        else
            return nullptr;
    }
    // Функция для получения последнего объекта
// Возвращает указатель на последний объект, если он существует, иначе возвращает nullptr
    object* get_last_object() {
        if (check_by_index(folder_size - 1) == true)
            return objects[folder_size - 1];
        else
            return nullptr;
    }

    void show() {//перебирает все объекты в папке, и для каждого, если он существует, вызывает метод "name_yourself" для отображения информации об объекте.
        for (int i = 0; i < folder_size; i++) {
            if (check_by_index(i) == true) {
                object* something = get_object(i);
                (*something).name_yourself();
            }
        }
    }

    ~folder() {
        cout << "Хранилище было удалено" << endl;
    }
};

class Animal : public object {//бстрактным базовым классом, определяющим общие методы и свойства для всех животных
public:
    Animal() {
        cout << "Конструктор по умолчанию абстрактного класса Animal" << endl;
    }
    void sound() {//пределяет звук, который издает животное
        printf("\n");
    }
    virtual void name_yourself() {//выводит информацию о том, что это за животное.
        cout << "yooou Animal" << endl;
    }

};

class Cat : public Animal {//наследуется от класса "Animal" и добавляет дополнительные свойства и методы, связанные с кошками, такие как цвет шерсти и порода. 
protected:
    string coat_color;
    string breed;
public:
    Cat() : coat_color("gray"), breed("British cat") {
        cout << "Конструктор по умолчанию класса Cat" << endl;
    }
    Cat(string coat_color, string breed) : coat_color(coat_color), breed(breed) {
        cout << "Конструктор с параметрами класса Cat" << endl;
    }

    void sound() {
        printf("Mew−mew␣\n");
    }
    void catchMouse() {//выводит информацию о том, что кошка ловит мышей
        cout << "``` Звуки охоты кошки ```" << endl;
    }

    void name_yourself() {//выводит информацию о том, что это кошка
        cout << "I am is a cat" << endl;
    }
    ~Cat() {
        cout << "Работа диструктора класса Car" << endl;
    }
};

class Dog : public Animal {
protected:
    string coat_color;
    string breed;
public:
    Dog() : coat_color("gray"), breed("British cat") {
        cout << "Конструктор по умолчанию класса Dog" << endl;
    }
    Dog(string coat_color, string breed) : coat_color(coat_color), breed(breed) {
        cout << "Конструктор с параметрами класса Dog" << endl;
    }

    void sound() {
        printf("Gaf - gaf␣\n");
    }
    void chaseCat() {
        cout << "``` звуки погони собаки за котом ```" << endl;
    }
    void name_yourself() {
        cout << "I am is a dog" << endl;
    }
    ~Dog() {
        cout << "Работа диструктора класса Dog" << endl;
    }
};

class ground_vehicle : public object {
protected:
    int number_of_wheels;
    string color;
public:
    ground_vehicle() : number_of_wheels(4), color("white") {
        cout << "Конструктор по умолчанию класса ground_vehicle: " << endl;
        cout << "number_of_wheels: " << number_of_wheels << ", color: " << color << endl;
        cout << "\n";
    }
    ground_vehicle(int number_of_wheels, string color) : number_of_wheels(number_of_wheels), color(color) {
        cout << "Конструктор с параметрами класса ground_vehicle: " << endl;
        cout << "number_of_wheels: " << this->number_of_wheels << ", color: " << this->color << endl;
        cout << "\n";
    }
    ground_vehicle(const ground_vehicle& vehicle) : number_of_wheels(vehicle.number_of_wheels), color(vehicle.color) {
        cout << "Конструктор копирования класса ground_vehicle: " << endl;
        cout << "number_of_wheels: " << number_of_wheels << ", color: " << color << endl;
        cout << "\n";
    }

    void go_straight() {
        cout << "``` is going straight ```" << endl;
    }

    void name_yourself() {
        cout << "I am is a vehicle" << endl;
    }

    ~ground_vehicle() {
        cout << "Диструктор класса ground_vehicle:" << endl;
        cout << "number_of_wheels: " << number_of_wheels << ", color: " << color << endl;
        cout << "\n";
    }

};


int main()
{
    setlocale(LC_ALL, "rus");

    int folder_size = 1; // Создаем объект класса folder размером 1
    folder objects(folder_size);
    // Создаем несколько объектов разных классов и добавляем их в объект folder
    object* object_1 = new Cat("White", "British");
    object* object_2 = new Dog("Black", "Bulderer");
    object* object_3 = new Dog();
    object* object_4 = new Dog("White", "British");
    object* object_5 = new ground_vehicle();

    objects.set_object(0, object_1);
    objects.set_object(1, object_2);
    objects.set_object(2, object_3);
    objects.set_object(3, object_5);
    // Получаем объект с индексом 1 и вызываем метод name_yourself()
    object* something_1 = objects.get_object(1);
    (*something_1).name_yourself();
    // Получаем первый объект в списке и вызываем метод name_yourself()
    object* something_2 = objects.get_first_object();
    (*something_2).name_yourself();
    // Получаем последний объект в списке и вызываем метод name_yourself()
    object* something_3 = objects.get_last_object();
    (*something_3).name_yourself();

    // Добавляем новый объект object_4 в объект folder
    objects.add_object(object_4);
    // Создаем несколько объектов разных классов в цикле и добавляем/удаляем их из объекта folder

    int range_size = 1000;


    for (int i = 4; i < range_size; i++) {
        int random_number = (rand() % range_size + 1);

        cout << "RANDOM NUMBER IS " << random_number << endl;
        // Проверяем остаток от деления на несколько чисел и в зависимости от этого добавляем/удаляем объект или выводим информацию о нем
        if (random_number % 2 == 0) {

            object* something = new Cat("White", "British");
            cout << "Кошка была добавлена" << endl;
            objects.set_object(i, something);
            cout << "\n" << endl;

        }
        else if (random_number % 3 == 0) {

            object* something = new Dog("White", "British");
            cout << "Собака была добавлена" << endl;
            objects.set_object(i, something);
            cout << "\n" << endl;

        }
        else if (random_number % 7 == 0) {

            object* something = new ground_vehicle();
            cout << "Машина была добавлена" << endl;
            objects.set_object(i, something);
            cout << "\n" << endl;

        }
        else if (random_number % 5 == 0) {
            objects.delete_object(random_number);
            cout << "Объект удален" << endl;
            cout << "\n" << endl;

        }
        else {

            bool check = objects.check_by_index(random_number);
            cout << "Check point 1 " << endl;
            if (check == true) {
                cout << "Check point 2 " << endl;
                object* something = objects.get_object(random_number);
                cout << "Check point 3 " << endl;
                cout << objects.folder_size << endl;
                cout << random_number << endl;
                (*something).name_yourself();

                cout << "Check point 4 " << endl;
            }
            else {
                cout << "There is no element on " << random_number << " position " << endl;
            }
            cout << "\n" << endl;
        }
    }

    objects.show();


    return 0;
}
