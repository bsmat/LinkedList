
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

template<class T>
class List
{
    class Node
    {
    public:
        T data;
        Node* next;

        Node(T t = T(), Node* n = nullptr);
    };
    Node* head;
    int size;

public:
    List();
    ~List();
    void pushBack(T value);
    void pushFront(T value);
    int getSize() const;
    T& operator[] (int);
    void popFront();
    void popBack();
    void clear();
    void insert(T value, int index);
    void removeAt(int index);
    int getPositionMax();
    int getValueMax();
    int getPositionMin();
    int getValueMin();
    int findValuePosition(int value);
    void writeListToFile();
};

template<class T>
void show(List<T>&);

template<class T>
int removeByValue(List<T>&, int value);

template<class T>
void removeAllByValue(List<T>&, int value);

template<class T>
void addFromFile(List<T>&);

int getIntFromString(string s);

int main()
{
    setlocale(0, "");
    List<int> list;
    for (int i = 0; i < 5; i++) list.pushBack(i);
    show(list);
    list.popBack();
    list.popFront();
    list[1] = 777;
    list.pushBack(13);
    list.pushFront(13);
    show(list);

    cout << "--------------" << endl;

    cout << "max pos: " << list.getPositionMax() << endl;
    cout << "max value: " << list.getValueMax() << endl;
    cout << "min pos: " << list.getPositionMin() << endl;
    cout << "min value: " << list.getValueMin() << endl;

    cout << "--------------" << endl;

    removeByValue(list, 777);
    show(list);
    removeAllByValue(list, 13);
    show(list);

    cout << "--------------" << endl;

    list.writeListToFile();
    addFromFile(list);
    show(list);
    return 0;
}

template <class T>
List<T>::Node::Node(T t, Node* n)
{
    data = t;
    next = n;
}

template<class T>
List<T>::List()
{
    size = 0;
    head = nullptr;
}

template<class T>
List<T>::~List()
{
    clear();
}

template<class T>
void List<T>::pushBack(T value)
{
    if (head == nullptr)
        head = new Node(value);
    else
    {
        for (Node* current = head; ; current = current->next)
            if (current->next == nullptr)
            {
                current->next = new Node(value);
                break;
            }
    }
    size++;
}

template<class T>
void List<T>::pushFront(T value)
{
    head = new Node(value, head);
    size++;
}

template<class T>
int List<T>::getSize() const
{
    return size;
}

template<class T>
T& List<T>::operator[](int index)
{
    if (index > size - 1 || index < 0)
    {
        string message = "Недопустимый индекс ";
        message.append(to_string(index));
        throw out_of_range(message);
    }
    Node* current = head;
    for (int i = 0; i < index; i++)
        current = current->next;
    return current->data;
}

template<class T>
void List<T>::popFront()
{
    if (size <= 0) return;
    Node* temp = head;
    head = head->next;
    delete temp;
    size--;
}

template<class T>
void List<T>::popBack()
{
    removeAt(size - 1);
}

template<class T>
void List<T>::clear()
{
    while (size) popFront();
}

template<class T>
void List<T>::insert(T value, int index)
{
    if (index > size || index < 0)
    {
        string message = "Недопустимый индекс ";
        message.append(to_string(index));
        throw out_of_range(message);
    }
    if (index == 0) pushFront(value);
    else
    {
        Node* previous = head;
        for (int i = 0; i < index - 1; i++)
            previous = previous->next;
        previous->next = new Node(value, previous->next);
        size++;
    }
}

template<class T>
void List<T>::removeAt(int index)
{
    if (index > size - 1 || index < 0)
    {
        string message = "Недопустимый индекс ";
        message.append(to_string(index));
        throw out_of_range(message);
    }
    if (index == 0) popFront();
    else
    {
        Node* previous = head;
        for (int i = 0; i < index - 1; i++)
            previous = previous->next;
        Node* temp = previous->next;
        previous->next = temp->next;
        delete temp;
        size--;
    }
}

template<class T>
void show(List<T>& list)
{
    cout << "size = " << list.getSize() << endl;
    for (int i = 0; i < list.getSize(); i++) cout << list[i] << "  ";
    cout << endl;
}

template<class T>
int List<T>::getPositionMax()
{
    if (size <= 0)
    {
        cout << "empty list, no maximum" << endl;
    } else
    {
        Node* pointer = head;
        int maxValue = pointer->data;
        int maxPosition = 0;
        for (int i = 1; i < size - 1; i++)
        {
            pointer = pointer->next;
            if (pointer->data > maxValue)
            {
                maxValue = pointer->data;
                maxPosition = i;
            }
        }
        return maxPosition;
    }
}

template<class T>
int List<T>::getValueMax()
{
    if (size <= 0)
    {
        cout << "empty list, no maximum" << endl;
    } else
    {
        Node* pointer = head;
        int maxValue = pointer->data;
        int maxPosition = 0;
        for (int i = 1; i < size - 1; i++)
        {
            pointer = pointer->next;
            if (pointer->data > maxValue)
            {
                maxValue = pointer->data;
                maxPosition = i;
            }
        }
        return maxValue;
    }
}

template<class T>
int List<T>::getPositionMin()
{
    if (size <= 0)
    {
        cout << "empty list, no maximum" << endl;
    } else
    {
        Node* pointer = head;
        int minValue = pointer->data;
        int minPosition = 0;
        for (int i = 1; i < size - 1; i++)
        {
            pointer = pointer->next;
            if (pointer->data < minValue)
            {
                minValue = pointer->data;
                minPosition = i;
            }
        }
        return minPosition;
    }
}

template<class T>
int List<T>::getValueMin()
{
    if (size <= 0)
    {
        cout << "empty list, no maximum" << endl;
    } else
    {
        Node* pointer = head;
        int minValue = pointer->data;
        int minPosition = 0;
        for (int i = 1; i < size - 1; i++)
        {
            pointer = pointer->next;
            if (pointer->data < minValue)
            {
                minValue = pointer->data;
                minPosition = i;
            }
        }
        return minValue;
    }
}

template<class T>
int List<T>::findValuePosition(int value){
    if (size <= 0)
    {
        cout << "empty list, no maximum" << endl;
    } else
    {
        Node* pointer = head;
        int position = -1;
        for (int i = 0; i < size - 1; i++)
        {
            if (pointer->data == value)
            {
                return i;
            }
            else
            {
                pointer = pointer->next;
            }
        }

        if (pointer->data == value)
        {
            position = size - 1;
        }

        return position;
    }
}

template<class T>
int removeByValue(List<T>& list, int value){
    int valuePos = list.findValuePosition(value);
    if (valuePos != -1)
    {
        list.removeAt(valuePos);
        return valuePos;
    }else
    {
        return -1;
    }
}

template<class T>
void removeAllByValue(List<T>& list, int value){

    int valuePos = list.findValuePosition(value);
    while (valuePos != -1)
    {
        list.removeAt(valuePos);
        valuePos = list.findValuePosition(value);
    }
}

template<class T>
void List<T>::writeListToFile(){
    ofstream myfile;
    myfile.open ("src.txt");
    Node* pointer = head;
    for (int i = 0; i < size; i++)
    {
        myfile << pointer->data << "\n";
        pointer = pointer->next;
    }
    myfile.close();
}

template<class T>
void addFromFile(List<T>& list){
    string line;
    ifstream myfile ("src.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            list.pushBack(getIntFromString(line));
        }
        myfile.close();
    }
}

int getIntFromString(string s){
    stringstream geek(s);
    int x = 0;
    geek >> x;
    return x;
}
