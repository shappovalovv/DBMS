#include <iostream>
#include <string>
using namespace std;

class List {
private:
    // структура для хранения узла списка
    struct Node {
        int data;
        Node *next;
        Node *prev;
    };
    Node *first, *last; // первый и последний элементы
public:
    List(); // конструктор
    ~List(); // деструктор
    void push_front(int); // вставка в начало
    void push_back(int); // вставка в конец
    int pop_front(); // удаление из начала
    int pop_back(); // удаление из конца
    string toString(); // вывод в строку
    // итератор для прохождения по элементам
    class iterator {
    private:
        Node *current;
    public:
        iterator(); // конструктор
        ~iterator(); // деструктор
        iterator& operator=(const iterator&); // присваивание
        iterator operator++(); // переход к следующему элементу
        iterator operator++(int); // постфиксная форма
        iterator operator--(); // переход к предыдущему элементу
        iterator operator--(int); // постфиксная форма
        int& operator*(); // доступ к данным по ссылке
        bool operator==(const iterator&); // сравнение
        bool operator!=(const iterator&); // сравнение
        friend class List;
    };
    // функции для получения итератора на начало и конец
    iterator begin();
    iterator end();
    
    // проверка на пустоту
    bool isEmpty() {return first == nullptr;}
};

List::List() {
    first = last = nullptr; // создаем пустой список
}

List::~List() {
    // уничтожаем список
    Node *current = first;
    while (current)
    {
        current = current->next;
        delete first;
        first = current;
    }
}

void List::push_front(int n) {
    // создаем новый узел
    Node *node = new Node;
    node->data = n;
    node->prev = nullptr;
    node->next = first;
    if (first) { // если список не пуст
        first->prev = node;
        first = node; // делаем элемент первым
    }
    else { // если пуст
        first = last = node; // делаем элемент и первым, и последним
    }
}

void List::push_back(int n) {
    // создаем новый узел
    Node *node = new Node;
    node->data = n;
    node->prev = last;
    node->next = nullptr;
    if (first) { // если список не пуст
        last->next = node;
        last = node; // делаем элемент последним
    }
    else { // если пуст
        first = last = node; // делаем элемент и первым, и последним
    }
}

int List::pop_front() {
    int n = first->data; // запоминаем данные
    Node *toDel = first; // запоминаем элемент для удаления
    first = first->next; // меняем первый элемент
    if (!first) // если элемент был единственный, меняем последний
        last = nullptr;
    else
        first->prev = nullptr;
    delete toDel; // удаляем элемент
    return n; // возвращаем данные
}

int List::pop_back() {
    int n = last->data; // запоминаем данные
    Node *toDel = last; // запоминаем элемент для удаления
    last = last->prev; // меняем последний элемент
    if (!last) // если элемент был единственный, меняем первый
        first = nullptr;
    else
        last->next = nullptr;
    delete toDel; // удаляем элемент
    return n; // возвращаем данные
}

string List::toString() {
    Node *current = first;
    string str;
    while (current) { // проходим по списку
        str += to_string(current->data)+" ";
        current = current->next;
    }
    return str;
}

// итератор для прохождения по элементам

List::iterator::iterator() {
    current = nullptr;
}

List::iterator::~iterator() {
    
}

List::iterator& List::iterator::operator=(const iterator& it) {
    current = it.current;
    return *this;
}

List::iterator List::iterator::operator++() {
    current = current->next;
    return *this;
}

List::iterator List::iterator::operator++(int) {
    iterator it;
    it.current = current;
    current = current->next;
    return it;
}

List::iterator List::iterator::operator--() {
    current = current->prev;
    return *this;
}

List::iterator List::iterator::operator--(int) {
    iterator it;
    it.current = current;
    current = current->prev;
    return it;
}

int& List::iterator::operator*() {
    return current->data;
}

bool List::iterator::operator==(const iterator& it) {
    return current == it.current;
}

bool List::iterator::operator!=(const iterator& it) {
    return current != it.current;
}

List::iterator List::begin() {
    iterator it;
    it.current = first;
    return it;
}

List::iterator List::end() {
    iterator it;
    it.current = nullptr;
    return it;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    // проверяем созданную структуру данных с помощью меню
    List list; // создаем список
    int menu;
    int n;
    do {
        cout << "1 - добавить элемент в начало списка" << endl;
        cout << "2 - добавить элемент в конец списка" << endl;
        cout << "3 - удалить элемент из начала списка" << endl;
        cout << "4 - удалить элемент из конца списка" << endl;
        cout << "5 - вывод списка в виде строки" << endl;
        cout << "6 - проход по списку с помощью итератора" << endl;
        cout << "0 - выход" << endl;
        cin >> menu;
        switch (menu) {
            case 1:
                cout << "Введите значение: ";
                cin >> n;
                list.push_front(n);
                break;
                
            case 2:
                cout << "Введите значение: ";
                cin >> n;
                list.push_back(n);
                break;
                
            case 3:
                if (list.isEmpty())
                    cout << "Список пуст" << endl;
                else {
                    n = list.pop_front();
                    cout << "Удален элемент: " << n << endl;
                }
                break;
                
            case 4:
                if (list.isEmpty())
                    cout << "Список пуст" << endl;
                else {
                    n = list.pop_back();
                    cout << "Удален элемент: " << n << endl;
                }
                break;
            
            case 5:
                cout << "Список в виде строки:" << endl;
                cout << list.toString() << endl;
                break;
            
            case 6:
                cout << "Обход списка с помощью итератора:" << endl;
                for (List::iterator it = list.begin(); it != list.end(); it++) {
                    cout << *it << endl;
                }
                
            default:
                break;
        }
    } while (menu != 0);
    return 0;
}
