#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

// --- БАЗОВЫЙ КЛАСС ---
class Circle {
protected:
    double R; // Радиус
    double x, y; // Координаты центра

public:
    // Конструктор
    Circle(double r, double cx, double cy) : R(r), x(cx), y(cy) {}

    // Вывод имени класса и всех полей
    virtual void printInfo() const {
        cout << "Класс: Круг | R=" << R << ", x=" << x << ", y=" << y;
    }

    // Изменение значений на приращения
    void incrementFields(double dr, double dx, double dy) {
        R += dr; x += dx; y += dy;
    }

    // Умножение полей на коэффициент
    void multiplyFields(double k) {
        R *= k; x *= k; y *= k;
    }

    // Расчет площади
    virtual double calcArea() const {
        return M_PI * R * R;
    }

    // Расчет периметра (длины окружности)
    double calcPerimeter() const {
        return 2 * M_PI * R;
    }

    // Вывод площади и периметра
    void outputCalculations() const {
        cout << "Площадь: " << fixed << setprecision(3) << calcArea() 
                  << " | Периметр: " << calcPerimeter() << endl;
    }
};

// --- ПРОИЗВОДНЫЙ КЛАСС ---
class TruncatedCone : public Circle {
private:
    double H; // Высота
    double z; // Координата Z

public:
    // Конструктор (верхний радиус R/2 задан условием)
    TruncatedCone(double r, double cx, double cy, double h, double cz) 
        : Circle(r, cx, cy), H(h), z(cz) {}

    // Умножение всех полей на коэффициент
    void multiplyFields(double k) {
        multiplyFields(k);
        H *= k; z *= k;
    }

    /*
        Скрытие/Переопределение метода площади (Полная площадь поверхности)
        Формула: S = 5/4 * PI * R^2 + 3/8 * PI * R * sqrt(16H^2 + R^2)
    */
    double calcArea() const override {
        double term1 = (5.0 / 4.0) * M_PI * R * R;
        double term2 = (3.0 / 8.0) * M_PI * R * sqrt(16 * H * H + R * R);
        return term1 + term2;
    }

    /*
        Расчет объема
        Формула: V = 7/12 * PI * H * R^2
    */
    double calcVolume() const {
        return (7.0 / 12.0) * M_PI * H * R * R;
    }

    // Вывод площади и объема
    void outputCalculations() {
        cout << "Общая площадь поверхности: " << fixed << setprecision(3) << calcArea() 
                  << " | Объем: " << calcVolume() << endl;
    }

    // Перегрузка метода приращения (добавлены H и Z)
    void incrementFields(double dr, double dx, double dy, double dh, double dz) {
        Circle::incrementFields(dr, dx, dy);
        H += dh; z += dz;
    }

    // Переопределение вывода инфо
    void printInfo() const override {
        cout << "Класс: Усеченный конус | R=" << R << ", x=" << x << ", y=" << y 
                  << ", H=" << H << ", z=" << z;
    }
};

int main() {
    cout << "Программа выполняет расчет площади, периметра и объема для окружностей и усеченных конусов, при этом:" << endl;
    cout << "   - реализует наследование классов Circle (Окружность) и TruncatedCone (Усеченный конус)" << endl;
    cout << "   - демонстрирует работу с полиморфным массивом объектов базового и производного классов" << endl;

    cout << "\nИсполнитель: Новиков Д. А." << endl;
    cout << "Вариант: №14\n" << endl;

    // 3 объекта базового класса
    Circle* circles[3] = {
        new Circle(5.0, 0.0, 0.0),
        new Circle(10.0, 2.5, -1.0),
        new Circle(3.2, 10.0, 10.0)
    };

    cout << "--- Базовые объекты классов ---\n";
    for(int i=0; i<3; i++) {
        circles[i]->printInfo(); cout << " -> ";
        circles[i]->outputCalculations();
        circles[i]->multiplyFields(1.5); // изменение полей
    }

    // 3 объекта производного класса
    TruncatedCone* cones[3] = {
        new TruncatedCone(5.0, 0.0, 0.0, 10.0, 0.0),
        new TruncatedCone(8.0, 1.0, 1.0, 5.0, 2.0),
        new TruncatedCone(2.0, -5.0, 4.0, 12.0, -3.0)
    };

    cout << "\n--- Производные объекты классов ---\n";
    for(int i=0; i<3; i++) {
        cones[i]->printInfo(); cout << "\n";
        cones[i]->outputCalculations();
        cones[i]->incrementFields(1.0, 0.5, 0.5, 2.0, 1.0); // изменение полей
    }

    // Массив из 6 элементов базового класса
    Circle* polyArray[6];
    for(int i=0; i<3; i++) polyArray[i] = circles[i];
    for(int i=0; i<3; i++) polyArray[i+3] = cones[i];

    // Вызов в цикле метода printInfo
    cout << "\n--- Полиморфный массив ---\n";
    for(int i=0; i<6; i++) {
        polyArray[i]->printInfo();
        cout << " | Площадь: " << polyArray[i]->calcArea() << endl;
    }

    // Очистка памяти
    for(int i=0; i<3; i++) {
        delete circles[i];
        delete cones[i];
    }

    return 0;
}