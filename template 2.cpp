#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

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
        Node(const T& data, Node *next, Node *prev) : data(data), next(next), prev(prev) {
            
        }
    };
    Node *first, *last; // первый и последний элементы
public:
    List();
    ~List();
    void push_front(const T&);
    void push_back(const T&);
    void pop_front();
    void pop_back();
    const T& front();
    const T& back();
    string toString() const;
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
    iterator cbegin();
    iterator cend();
    
    // проверка на пустоту
    bool isEmpty() {return first == nullptr;}
};

// конструктор
template <class T>
List<T>::List() {
    first = last = nullptr; // создаем пустой список
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
void List<T>::push_front(const T& data) {
    // создаем новый узел
    Node *node = new Node(data, first, nullptr);
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
void List<T>::push_back(const T& data) {
    // создаем новый узел
    Node *node = new Node(data, nullptr, last);
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
void List<T>::pop_front() {
    Node *toDel = first;
    first = first->next;
    if (!first)
        last = nullptr;
    else
        first->prev = nullptr;
    delete toDel;
}

// удаление из конца
template <class T>
void List<T>::pop_back() {
    Node *toDel = last;
    last = last->prev;
    if (!last)
        first = nullptr;
    else
        last->next = nullptr;
    delete toDel;
}

// доступ к первому
template <class T>
const T& List<T>::front() {
    return first->data;
}

// доступ к последнему
template <class T>
const T& List<T>::back() {
    return last->data;
}

// перевод в строку
template <class T>
string List<T>::toString() const {
    Node *current = first;
    stringstream ss;
    while (current) {
        // переводим данные текущего элемента в строку и добавляем к результату
        ss << current->data << " ";
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
typename List<T>::iterator List<T>::cbegin() {
    // создаем итератор с указателем на перывый элемент
    iterator it;
    it.current = first;
    return it;
}

// получение итератора на конец списка (элемент за последним)
template <class T>
typename List<T>::iterator List<T>::cend() {
    // элемент за последним - нулевой указатель
    iterator it;
    it.current = nullptr;
    return it;
}

// потоковый вывод
template <class T>
ostream& operator<<(ostream& os, const List<T>& list) {
    typename List<T>::Node *current = list.first; // указатель для прохода по списку
    while (current) {
        os << current->data << " ";
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
    string filename = "list.txt"; // имя файла для вывода
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
            case 1: // добавление в начало
                cout << "Введите значение: ";
                cin >> data;
                list.push_front(data);
                break;
                
            case 2: // добавление в конец
                cout << "Введите значение: ";
                cin >> data;
                list.push_back(data);
                break;
                
            case 3: // удаление из начала
                if (list.isEmpty())
                    cout << "Список пуст" << endl;
                else {
                    data = list.front();
                    list.pop_front();
                    cout << "Удален элемент: " << data << endl;
                }
                break;
                
            case 4: // удаление из конца
                if (list.isEmpty())
                    cout << "Список пуст" << endl;
                else {
                    data = list.back();
                    list.pop_back();
                    cout << "Удален элемент: " << data << endl;
                }
                break;
                
            case 5: // получение строки
                cout << "Список в виде строки:" << endl;
                cout << list.toString() << endl;
                break;
                
            case 6: // обход с помощью итератора
                cout << "Обход списка с помощью итератора:" << endl;
                // проход по списку с помощью итератора в цикле
                for (typename List<T>::iterator it = list.cbegin(); it != list.cend(); it++) {
                    cout << *it << endl;
                }
                break;
                
            case 7: // вывод на экран
                cout << list << endl;
                break;
                
            case 8: // вывод в файл
                file.open(filename); // открываем файл
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
    } while (menu != 0); // завершаем цикл при вводе 0
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
        case 1: // целый
            test<int>();
            break;
        case 2: // вещественный
            test<double>();
            break;
        case 3: // символьный
            test<char>();
            break;
        case 4: // строка
            test<string>();
            break;
        default:
            break;
    }
    
    return 0;
}

