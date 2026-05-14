#include <iostream>
#include <string>

using namespace std;

// Базовый класс
class ClassA {
protected:
    int AField;
public:
    ClassA(int n) : AField(n) {}
    
    void setPA(int m) { AField = m; }
    int getPA() const { return AField; }

    virtual void Info() {
        cout << "Класс A: Поле A = " << AField << endl;
    }
};

// Производный класс
class ClassB : public ClassA {
private:
    int BField;
public:
    ClassB(int n1, int n2) : ClassA(n1), BField(n2) {}

    void setPB(int m) { BField = m; }
    int getPB() const { return BField; }

    void Info() override {
        cout << "Класс B: Поле A = " << AField << ", Поле B = " << BField << endl;
    }
};

int main() {
    ClassA* a1 = new ClassA(4);
    ClassB* b1 = new ClassB(5, 6);

    cout << "Первоначальные значения:" << endl;
    a1->Info();
    b1->Info();

    // Изменение значений полей
    a1->setPA(10);
    b1->setPA(20);
    b1->setPB(30);

    cout << "\nИзмененные значения:" << endl;
    a1->Info();
    b1->Info();

    delete a1;
    delete b1;
    return 0;
}