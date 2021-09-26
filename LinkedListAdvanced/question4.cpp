#include <iostream>
#include <stdexcept>

template<class T>
class DLinkedList {
public:
    class Node;    // Forward declaration
    class Iterator;//forward declaration
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

    T removeAt(int index);
    bool removeItem(const T &item);
    void clear();
    Iterator begin() {
        return Iterator(this, true);
    }
    Iterator end() {
        return Iterator(this, false);
    }

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
    class Iterator {
    private:
        DLinkedList<T> *pList;
        Node *current;
        int index;// is the index of current in pList
    public:
        Iterator(DLinkedList<T> *pList, bool begin);
        Iterator &operator=(const Iterator &iterator);
        void set(const T &e);
        T &operator*();
        bool operator!=(const Iterator &iterator);
        void remove();

        // Prefix ++ overload
        Iterator &operator++();

        // Postfix ++ overload
        Iterator operator++(int);
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

template<class T>
bool DLinkedList<T>::contains(const T &item) {
    /* Check if item appears in the list */
    return indexOf(item) != -1;
}

template<class T>
T DLinkedList<T>::removeAt(int index) {
    /* Remove element at index and return removed value */
    if (index < 0 || index >= count) {
        return T{ -1 };
    }

    if (count == 1) {
        auto data = head->data;
        delete head;
        head = nullptr;
        tail = nullptr;
        count = 0;
        return data;
    }

    if (index == 0) {
        auto *deleteNode = head;
        auto data = deleteNode->data;

        head = head->next;
        head->previous = nullptr;
        count--;
        delete deleteNode;
        return data;
    }

    if (index == count - 1) {
        auto *deleteNode = tail;
        auto data = deleteNode->data;
        tail = tail->previous;
        tail->next = nullptr;
        count--;
        delete deleteNode;
        return data;
    }

    auto *ptr = head;
    for (int i = 0; i < index; i++) {
        ptr = ptr->next;
    }
    auto *deleteNode = ptr;
    auto data = deleteNode->data;
    deleteNode->next->previous = ptr->previous;
    deleteNode->previous->next = ptr->next;
    count--;
    delete deleteNode;
    return data;
}

template<class T>
bool DLinkedList<T>::removeItem(const T &item) {
    /* Remove the first apperance of item in list and return true, otherwise return false */
    auto index = indexOf(item);
    if (index == -1) {
        return false;
    }
    removeAt(index);
    return true;
}

template<class T>
void DLinkedList<T>::clear() {
    /* Remove all elements in list */
    auto *ptr = head;
    while (ptr != nullptr) {
        auto *deleteNode = ptr;
        ptr = ptr->next;
        delete deleteNode;
    }
    head = nullptr;
    tail = nullptr;
    count = 0;
}

/*
 * TODO: Implement class Iterator's method
 * Note: method remove is different from SLinkedList, which is the advantage of DLinkedList
 */
template<class T>
DLinkedList<T>::Iterator::Iterator(DLinkedList<T> *pList, bool begin) {
    if (begin) {
        if (pList == nullptr) {
            current = nullptr;
            index = 0;
            return;
        }
        this->pList = pList;
        current = this->pList->head;
        index = 0;
        return;
    }
    if (pList == nullptr) {
        current = nullptr;
        index = 0;
        return;
    }
    this->pList = pList;
    current = nullptr;
    index = this->pList->count;
    return;
}

template<class T>
typename DLinkedList<T>::Iterator &DLinkedList<T>::Iterator::operator=(const DLinkedList<T>::Iterator &iterator) {
    pList = iterator.pList;
    index = iterator.index;
    current = iterator.current;
    return *this;
}

template<class T>
void DLinkedList<T>::Iterator::set(const T &e) {
    if (current == nullptr) {
        throw std::out_of_range("Segmentation fault!");
    }
    current->data = e;
}

template<class T>
T &DLinkedList<T>::Iterator::operator*() {
    if (current == nullptr) {
        throw std::out_of_range("Segmentation fault!");
    }
    return current->data;
}

template<class T>
void DLinkedList<T>::Iterator::remove() {
    if (current == nullptr) {
        throw std::out_of_range("Segmentation fault!");
    }
    if (pList->head == current) {
        pList->removeAt(0);
        current = nullptr;
        index = -1;
        return;
    }
    /**
    auto prevIndex = 0;
    auto prevElementPtr = pList->head;

    while (prevElementPtr->next != current) {
        prevElementPtr = prevElementPtr->next;
        prevIndex++;
    }

    auto *toBeDeleteNode = prevElementPtr->next;
    if (toBeDeleteNode == pList->tail) {
        pList->tail = prevElementPtr;
    }
    prevElementPtr->next = toBeDeleteNode->next;

    pList->count--;
    index = prevIndex;

    delete toBeDeleteNode;
    **/
    auto oldIndex = index;
    current = current->previous;
    index--;

    pList->removeAt(oldIndex);
}

template<class T>
bool DLinkedList<T>::Iterator::operator!=(const DLinkedList::Iterator &iterator) {
    return iterator.index != index || iterator.current != current;
}

template<class T>
typename DLinkedList<T>::Iterator &DLinkedList<T>::Iterator::operator++() {
    if (index == pList->count) {
        throw std::out_of_range("Segmentation fault!");
    }
    if (index == -1 && current == nullptr) {
        current = pList->head;
        index = 0;
        return *this;
    }
    current = current->next;
    index++;
    return *this;
}

template<class T>
typename DLinkedList<T>::Iterator DLinkedList<T>::Iterator::operator++(int) {
    auto oldValue = DLinkedList<T>::Iterator(*this);
    if (index == pList->count) {
        throw std::out_of_range("Segmentation fault!");
    }
    if (index == -1 && current == nullptr) {
        current = pList->head;
        index = 0;
        return oldValue;
    }
    current = current->next;
    index++;
    return oldValue;
}

int main() {
    DLinkedList<int> list;
    int size = 10;
    for (int idx = 0; idx < size; idx++) {
        list.add(idx);
    }
}
