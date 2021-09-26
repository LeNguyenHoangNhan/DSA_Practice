#include <iostream>

template<class T>
class DLinkedList {
public:
    class Node;// Forward declaration
protected:
    Node *head = nullptr;
    Node *tail = nullptr;
    int count = 0;

public:
    ~DLinkedList();
    void add(const T &e);
    void add(int index, const T &e);
    int size();

    bool empty();
    T get(int index);
    void set(int index, const T &e);
    int indexOf(const T &item);
    bool contains(const T &item);

public:
    class Node {
    private:
        T data;
        Node *next;
        Node *previous;
        friend class DLinkedList<T>;

    public:
        Node() {
            this->previous = nullptr;
            this->next = nullptr;
        }

        Node(const T &data) {
            this->data = data;
            this->previous = nullptr;
            this->next = nullptr;
        }
    };
};

template<typename T>
DLinkedList<T>::~DLinkedList() {
    auto *ptr = head;
    while (ptr != nullptr) {
        auto *deleteNode = ptr;
        ptr = ptr->next;
        delete deleteNode;
    }
}

template<class T>
void DLinkedList<T>::add(const T &e) {
    /* Insert an element into the end of the list. */
    if (tail == nullptr) {
        head = new Node(e);
        tail = head;
        count++;
        return;
    }
    tail->next = new Node(e);
    tail->next->previous = tail;
    tail = tail->next;
    count++;
}

template<class T>
void DLinkedList<T>::add(int index, const T &e) {
    if (index < 0 || index > count) {
        return;
    }
    if (count == 0) {
        head = new Node(e);
        tail = head;
        count++;
        return;
    }

    if (index == 0) {
        auto *newNode = new Node(e);
        newNode->next = head;
        head->previous = newNode;
        head = newNode;
        count++;
        return;
    }

    if (index == count) {
        auto *newNode = new Node(e);
        newNode->previous = tail;
        tail->next = newNode;
        tail = newNode;
        count++;
        return;
    }

    /* Insert an element into the list at given index. */
    auto *ptr = head;
    for (int i = 0; i < index; i++) {
        ptr = ptr->next;
    }

    auto *newNode = new Node(e);

    newNode->next = ptr;
    newNode->previous = ptr->previous;
    ptr->previous->next = newNode;
    ptr->previous = newNode;
    count++;

    return;
}

template<class T>
int DLinkedList<T>::size() {
    /* Return the length (size) of list */
    return count;
}
template<class T>
T DLinkedList<T>::get(int index) {
    /* Give the data of the element at given index in the list. */
    if (index < 0 || index >= count) {
        return T{ -1 };
    }
    auto *ptr = head;
    for (int i = 0; i < index; i++) {
        ptr = ptr->next;
    }
    return ptr->data;
}

template<class T>
void DLinkedList<T>::set(int index, const T &e) {
    /* Assign new value for element at given index in the list */
    if (index < 0 || index >= count) {
        return;
    }
    auto *ptr = head;
    for (int i = 0; i < index; i++) {
        ptr = ptr->next;
    }
    ptr->data = e;
}

template<class T>
bool DLinkedList<T>::empty() {
    /* Check if the list is empty or not. */
    return count == 0;
}

template<class T>
int DLinkedList<T>::indexOf(const T &item) {
    /* Return the first index wheter item appears in list, otherwise return -1 */
    auto index = 0;
    for (auto ptr = head; ptr != nullptr; ptr = ptr->next) {
        if (ptr->data == item) {
            return index;
        }
    }
    return -1;
}

int main() {
    DLinkedList<int> list;
    int size = 10;
    for (int idx = 0; idx < size; idx++) {
        list.add(idx);
    }
    for (int idx = 0; idx < size; idx++) {
        std::cout << list.get(idx) << " |";
    }
}
