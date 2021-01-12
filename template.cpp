#include <iostream>
#include <string>
using namespace std;

// переопределение функции to_string для string и char
// для корректной работы класса (функции перевода в строку) с этими типами

string to_string(string str) {
    return str;
}

string to_string(char c) {
    string str;
    str.push_back(c);
    return str;
}

// шаблонный класс
template <class T>
class List {
private:
    // структура для хранения узла списка
    struct Node {
        T data;
        Node *next;
        Node *prev;
    };
    Node *first, *last; // первый и последний элементы
public:
    List(); // конструктор
    ~List(); // деструктор
    void push_front(T); // вставка в начало
    void push_back(T); // вставка в конец
    T pop_front(); // удаление из начала
    T pop_back(); // удаление из конца
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
        T& operator*(); // доступ к данным по ссылке
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

template <class T>
List<T>::List() {
    first = last = nullptr; // создаем пустой список
}

template <class T>
List<T>::~List() {
    // уничтожаем список
    Node *current = first;
    while (current)
    {
        current = current->next;
        delete first;
        first = current;
    }
}

template <class T>
void List<T>::push_front(T n) {
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

template <class T>
void List<T>::push_back(T n) {
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

template <class T>
T List<T>::pop_front() {
    T n = first->data; // запоминаем данные
    Node *toDel = first; // запоминаем элемент для удаления
    first = first->next; // меняем первый элемент
    if (!first) // если элемент был единственный, меняем последний
        last = nullptr;
    else
        first->prev = nullptr;
    delete toDel; // удаляем элемент
    return n; // возвращаем данные
}

template <class T>
T List<T>::pop_back() {
    T n = last->data; // запоминаем данные
    Node *toDel = last; // запоминаем элемент для удаления
    last = last->prev; // меняем последний элемент
    if (!last) // если элемент был единственный, меняем первый
        first = nullptr;
    else
        last->next = nullptr;
    delete toDel; // удаляем элемент
    return n; // возвращаем данные
}

template <class T>
string List<T>::toString() {
    Node *current = first;
    string str;
    while (current) { // проходим по списку
        str += to_string(current->data)+" ";
        current = current->next;
    }
    return str;
}

// итератор для прохождения по элементам

template <class T>
List<T>::iterator::iterator() {
    current = nullptr;
}

template <class T>
List<T>::iterator::~iterator() {
    
}

template <class T>
typename List<T>::iterator& List<T>::iterator::operator=(const iterator& it) {
    current = it.current;
    return *this;
}

template <class T>
typename List<T>::iterator List<T>::iterator::operator++() {
    current = current->next;
    return *this;
}

template <class T>
typename List<T>::iterator List<T>::iterator::operator++(int) {
    iterator it;
    it.current = current;
    current = current->next;
    return it;
}

template <class T>
typename List<T>::iterator List<T>::iterator::operator--() {
    current = current->prev;
    return *this;
}

template <class T>
typename List<T>::iterator List<T>::iterator::operator--(int) {
    iterator it;
    it.current = current;
    current = current->prev;
    return it;
}

template <class T>
T& List<T>::iterator::operator*() {
    return current->data;
}

template <class T>
bool List<T>::iterator::operator==(const iterator& it) {
    return current == it.current;
}

template <class T>
bool List<T>::iterator::operator!=(const iterator& it) {
    return current != it.current;
}

template <class T>
typename List<T>::iterator List<T>::begin() {
    iterator it;
    it.current = first;
    return it;
}

template <class T>
typename List<T>::iterator List<T>::end() {
    iterator it;
    it.current = nullptr;
    return it;
}

// шаблонная функция для тестирования на разных типах
template <class T>
void test() {
    // проверяем созданную структуру данных с помощью меню
    List<T> list; // создаем список
    int menu;
    T n;
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
                for (typename List<T>::iterator it = list.begin(); it != list.end(); it++) {
                    cout << *it << endl;
                }
                
            default:
                break;
        }
    } while (menu != 0);
}

int main()
{
    setlocale(LC_ALL, "Russian");

    // выбираем тип для тестирования
    int type;
    cout << "Выбор типа данных: 1 - int, 2 - double, 3 - char, 4 - string" << endl;
    cin >> type;
    switch (type) {
        case 1:
            test<int>();
            break;
        case 2:
            test<double>();
            break;
        case 3:
            test<char>();
            break;
        case 4:
            test<string>();
            break;
        default:
            break;
    }
    
    return 0;
}
