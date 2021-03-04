#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

// переопределение функции to_string для string и char
// для корректной работы класса (функции перевода в строку) с этими типами

// для строки просто возвращаем ее же
string to_string(string str) {
    return str;
}

// для символа создаем строку с этим единственным символом
string to_string(char c) {
    stringstream ss;
    ss << c;
    return ss.str();
}

// предварительное объявление дружественного шаблонного оператора
template <class T>
class List;
template <class T>
ostream& operator<<(ostream&, const List<T>&);

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
    Node *first, *last;
public:
    List();
    ~List();
    void push_front(T);
    void push_back(T);
    T pop_front();
    T pop_back();
    string toString();
    friend ostream& operator<< <>(ostream&, const List&);
    // итератор для прохождения по элементам
    class iterator {
    private:
        Node *current;
    public:
        iterator();
        ~iterator();
        iterator& operator=(const iterator&);
        iterator operator++();
        iterator operator++(int);
        iterator operator--();
        iterator operator--(int);
        T& operator*();
        bool operator==(const iterator&);
        bool operator!=(const iterator&);
        friend class List;
    };
    // функции для получения итератора на начало и конец
    iterator begin();
    iterator end();
    
    // проверка на пустоту
    bool isEmpty() {return first == nullptr;}
};

// конструктор
template <class T>
List<T>::List() {
    first = last = nullptr;
}

// деструктор
template <class T>
List<T>::~List() {
    // уничтожаем список
    // проходим по списку и удаляем каждый элемент
    // сохраняя указатель на следующий
    Node *current = first;
    while (current)
    {
        current = current->next;
        delete first;
        first = current;
    }
}

// добавление в начало списка
template <class T>
void List<T>::push_front(T data) {
    // создаем новый узел
    Node *node = new Node;
    node->data = data;
    node->prev = nullptr;
    node->next = first;
    if (first) {
        first->prev = node;
        first = node;
    }
    else {
        first = last = node;
    }
}

// добавление в конец списка
template <class T>
void List<T>::push_back(T data) {
    // создаем новый узел
    Node *node = new Node;
    node->data = data;
    node->prev = last;
    node->next = nullptr;
    if (first) {
        last->next = node;
        last = node;
    }
    else {
        first = last = node;
    }
}

// удаление из начала
template <class T>
T List<T>::pop_front() {
    T data = first->data;
    Node *toDel = first;
    first = first->next;
    if (!first)
        last = nullptr;
    else
        first->prev = nullptr;
    delete toDel;
    return data;
}

// удаление из конца
template <class T>
T List<T>::pop_back() {
    T data = last->data;
    Node *toDel = last;
    last = last->prev;
    if (!last)
        first = nullptr;
    else
        last->next = nullptr;
    delete toDel;
    return data;
}

// перевод в строку
template <class T>
string List<T>::toString() {
    Node *current = first;
    stringstream ss;
    while (current) {
        // переводим данные текущего элемента в строку и добавляем к результату
        ss << to_string(current->data) << " ";
        current = current->next;
    }
    return ss.str();
}

// итератор для прохождения по элементам

// конструктор (создаем нулевой указатель)
template <class T>
List<T>::iterator::iterator() {
    current = nullptr;
}

// деструктор
template <class T>
List<T>::iterator::~iterator() {
    // в деструкторе ничего делать не нужно
    // собственную память итератор не использует
}

// присваивание
template <class T>
typename List<T>::iterator& List<T>::iterator::operator=(const iterator& it) {
    current = it.current;
    return *this;
}

// инкремент (переход к следующему элементу)
template <class T>
typename List<T>::iterator List<T>::iterator::operator++() {
    current = current->next;
    return *this;
}

// инкремент в постфиксной форме
template <class T>
typename List<T>::iterator List<T>::iterator::operator++(int) {
    // сохраняем значение
    iterator it;
    it.current = current;
    current = current->next;
    return it;
}

// декремент (переход к предыдущему элементу)
template <class T>
typename List<T>::iterator List<T>::iterator::operator--() {
    current = current->prev;
    return *this;
}

// декремент в постфиксной форме
template <class T>
typename List<T>::iterator List<T>::iterator::operator--(int) {
    // сохраняем значение
    iterator it;
    it.current = current;
    current = current->prev;
    return it;
}

// оператор разыменования
// доступ к элементу (получение ссылки на данные)
template <class T>
T& List<T>::iterator::operator*() {
    return current->data;
}

// сравнение

// проверка на равенство
template <class T>
bool List<T>::iterator::operator==(const iterator& it) {
    return current == it.current;
}

// проверка на неравенство
template <class T>
bool List<T>::iterator::operator!=(const iterator& it) {
    return current != it.current;
}

// получение итератора на начало списка
template <class T>
typename List<T>::iterator List<T>::begin() {
    // создаем итератор с указателем на перывый элемент
    iterator it;
    it.current = first;
    return it;
}

// получение итератора на конец списка (элемент за последним)
template <class T>
typename List<T>::iterator List<T>::end() {
    // элемент за последним - нулевой указатель
    iterator it;
    it.current = nullptr;
    return it;
}

// потоковый вывод
template <class T>
ostream& operator<<(ostream& os, const List<T>& list) {
    typename List<T>::Node *current = list.first;
    while (current) {
        os << to_string(current->data) << " ";
        current = current->next;
    }
    return os;
}

// шаблонная функция для тестирования на разных типах
template <class T>
void test() {
    // проверяем созданную структуру данных с помощью меню
    List<T> list;
    int menu;
    T data;
    ofstream file;
    string filename = "list.txt";
    do {
        // вывод меню
        cout << "1 - добавить элемент в начало списка" << endl;
        cout << "2 - добавить элемент в конец списка" << endl;
        cout << "3 - удалить элемент из начала списка" << endl;
        cout << "4 - удалить элемент из конца списка" << endl;
        cout << "5 - вывод списка в виде строки" << endl;
        cout << "6 - проход по списку с помощью итератора" << endl;
        cout << "7 - вывод списка с помощью оператора вывода" << endl;
        cout << "8 - вывод списка в файл" << endl;
        cout << "0 - выход" << endl;
        cin >> menu;
        // выбор по меню
        switch (menu) {
            case 1:
                cout << "Введите значение: ";
                cin >> data;
                list.push_front(data);
                break;
                
            case 2:
                cout << "Введите значение: ";
                cin >> data;
                list.push_back(data);
                break;
                
            case 3:
                if (list.isEmpty())
                    cout << "Список пуст" << endl;
                else {
                    data = list.pop_front();
                    cout << "Удален элемент: " << data << endl;
                }
                break;
                
            case 4:
                if (list.isEmpty())
                    cout << "Список пуст" << endl;
                else {
                    data = list.pop_back();
                    cout << "Удален элемент: " << data << endl;
                }
                break;
                
            case 5:
                cout << "Список в виде строки:" << endl;
                cout << list.toString() << endl;
                break;
                
            case 6:
                cout << "Обход списка с помощью итератора:" << endl;
                // проход по списку с помощью итератора в цикле
                for (typename List<T>::iterator it = list.begin(); it != list.end(); it++) {
                    cout << *it << endl;
                }
                break;
                
            case 7:
                cout << list << endl;
                break;
                
            case 8:
                file.open(filename);
                if (file.is_open()) {
                    file << list << endl;
                    file.close();
                    cout << "Список выведен в файл " << filename << endl;
                }
                else {
                    cout << "Не удалось открыть файл " << filename << endl;
                }
                break;
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
    
    // выбор в зависимости от ввода пользователя
    // вызываем шаблонную функцию с соответствующим типом
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


