#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;

// Ітератор - абстракція для обходу елементів
class Iterator {
public:
    virtual int next() = 0;         // Повертає наступний елемент
    virtual bool hasNext() = 0;      // Перевіряє, чи є наступний елемент
    virtual void reset() = 0;        // Скидає ітератор на початок
    virtual ~Iterator() = default;
};

// Колекція - абстракція для зберігання елементів
class Aggregate {
public:
    virtual Iterator* createIterator() = 0;  // Створює ітератор для обходу елементів
    virtual ~Aggregate() = default;
};

// Конкретний ітератор для обходу чисел
class ConcreteIterator : public Iterator {
private:
    vector<int>& collection;  // Колекція для обходу
    size_t index;

public:
    ConcreteIterator(vector<int>& collection) : collection(collection), index(0) {}

    int next() override {
        if (hasNext()) {
            return collection[index++];
        }
        return -1; // Якщо наступного елемента немає
    }

    bool hasNext() override {
        return index < collection.size();
    }

    void reset() override {
        index = 0;
    }
};

// Конкретна колекція (список чисел)
class ConcreteAggregate : public Aggregate {
private:
    vector<int> collection;

public:
    ConcreteAggregate(const vector<int>& elements) : collection(elements) {}

    Iterator* createIterator() override {
        return new ConcreteIterator(collection);
    }
};


int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Створення колекції
    vector<int> numbers = { 1, 2, 3, 4, 5 };
    ConcreteAggregate aggregate(numbers);

    // Створення ітератора для обходу колекції
    Iterator* it = aggregate.createIterator();

    // Обхід колекції за допомогою ітератора
    cout << "Елементи колекції: ";
    while (it->hasNext()) {
        cout << it->next() << " ";
    }
    cout << endl;


    delete it;

}

