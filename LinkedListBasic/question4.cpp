#include <cstddef>
#include <iostream>
#include <cassert>
#include <stdexcept>

template<typename T>
class SLinkedList {
public:
    class Node;// Forward declaration
    class Iterator;

protected:
    Node *head = nullptr;
    Node *tail = nullptr;
    int count = 0;

public:
    ~SLinkedList(){};
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

    std::string toString() const;

    Iterator begin() {
        return Iterator(this, true);
    }
    Iterator end() {
        return Iterator(this, false);
    }

    class Node {
    private:
        T data;
        Node *next;
        friend class SLinkedList<T>;

    public:
        Node() {
            next = 0;
        }
        Node(Node *next) {
            this->next = next;
        }
        Node(T data, Node *next = nullptr) {
            this->data = data;
            this->next = next;
        }
    };

    class Iterator {
    private:
        SLinkedList<T> *pList;
        Node *current;
        int index;// corresponding with current node
    public:
        Iterator(SLinkedList<T> *pList, bool begin);
        Iterator &operator=(const Iterator &iterator);

        Iterator() = default;

        void set(const T &e);
        T &operator*();
        bool operator!=(const Iterator &iterator);

        // Prefix ++ overload
        Iterator &operator++();

        // Postfix ++ overload
        Iterator operator++(int);

        void remove();
    };
};

template<class T>
T SLinkedList<T>::get(int index) {
    /* Give the data of the element at given index in the list. */
    if (index < 0 || index >= count) {
        return T(-1);
    }
    auto *ptr = head;
    for (int i = 0; i < index; i++) {
        ptr = ptr->next;
    }
    return ptr->data;
}

template<class T>
void SLinkedList<T>::set(int index, const T &e) {
    /* Assign new value for element at given index in the list */
    if (index < 0 || index >= count) {
        return;
    }
    auto ptr = head;
    for (int i = 0; i < index; i++) {
        ptr = ptr->next;
    }
    ptr->data = e;
}

template<class T>
bool SLinkedList<T>::empty() {
    return count == 0;
}

template<class T>
int SLinkedList<T>::indexOf(const T &item) {
    /* Return the first index wheter item appears in list, otherwise return -1 */
    auto index = 0;
    for (auto *ptr = head; ptr != nullptr; ptr = ptr->next) {
        if (ptr->data == item) {
            return index;
        }
        index++;
    }

    return -1;
}

template<class T>
bool SLinkedList<T>::contains(const T &item) {
    /* Check if item appears in the list */
    for (auto *ptr = head; ptr != nullptr; ptr = ptr->next) {
        if (ptr->data == item) {
            return true;
        }
    }
    return false;
}

template<class T>
void SLinkedList<T>::add(const T &e) {
    count++;
    if (tail == nullptr) {
        tail = new Node(e, nullptr);
        head = tail;
        return;
    }
    tail->next = new Node(e, nullptr);
    tail = tail->next;
}

template<class T>
void SLinkedList<T>::add(int index, const T &e) {
    /* Insert an element into the list at given index. */
    if (index > count || index < 0) {
        return;
    }
    if (index == 0 && tail == nullptr) {
        tail = new Node(e, nullptr);
        head = tail;
        count++;
        return;
    }
    if (index == 0 && tail != nullptr) {
        auto *newNode = new Node(e, head);
        head = newNode;
        count++;
        return;
    }

    auto *current = head;
    for (auto a = 0; a < index - 1; a++) {
        current = current->next;
    }
    auto *newNode = new Node(e, current->next);
    current->next = newNode;
    if (current == tail) {
        tail = current->next;
    }
    count++;
}

template<class T>
int SLinkedList<T>::size() {
    /* Return the length (size) of list */
    return count;
}

template<typename T>
std::string SLinkedList<T>::toString() const {
    std::string output;
    output += '[';
    for (auto *ptr = head; ptr != nullptr; ptr = ptr->next) {
        output += std::to_string(ptr->data);
        output += ',';
    }
    if (*output.end() == ',') {
        output.pop_back();
    }
    output += ']';
    return output;
}

template<class T>
T SLinkedList<T>::removeAt(int index) {
    /* Remove element at index and return removed value */
    if (index < 0 || index >= count) {
        return T(-1);
    }
    if (index == 0) {
        auto *deleteNode = head;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        auto data = deleteNode->data;
        count--;
        delete deleteNode;
        return data;
    }
    auto *ptr = head;
    for (int i = 0; i < index - 1; i++) {
        ptr = ptr->next;
    }

    auto *deleteNode = ptr->next;
    ptr->next = deleteNode->next;
    if (deleteNode == tail) {
        tail = ptr;
    }
    auto data = deleteNode->data;
    delete deleteNode;
    count--;
    return data;
}

template<class T>
bool SLinkedList<T>::removeItem(const T &item) {
    /* Remove the first apperance of item in list and return true, otherwise return false */
    auto index = indexOf(item);
    if (index == -1) {
        return false;
    }
    removeAt(index);
    count--;
    return true;
}

template<class T>
void SLinkedList<T>::clear() {
    auto *ptr = head;
    while (ptr != nullptr) {
        auto *toBeDeleteNode = ptr;
        ptr = ptr->next;
        delete toBeDeleteNode;
    }
    count = 0;
}

template<class T>
SLinkedList<T>::Iterator::Iterator(SLinkedList<T> *pList, bool begin) {
    /*
        Constructor of iterator
        * Set pList to pList
        * begin = true:
        * * Set current (index = 0) to pList's head if pList is not NULL
        * * Otherwise set to NULL (index = -1)
        * begin = false:
        * * Always set current to NULL
        * * Set index to pList's size if pList is not NULL, otherwise 0
    */
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
typename SLinkedList<T>::Iterator &SLinkedList<T>::Iterator::operator=(const Iterator &iterator) {
    /*
        Assignment operator
        * Set this current, index, pList to iterator corresponding elements.
    */
    pList = iterator.pList;
    index = iterator.index;
    current = iterator.current;
    return *this;
}

template<class T>
void SLinkedList<T>::Iterator::remove() {
    /*
       Remove a node which is pointed by current
        * After remove current points to the previous node of this position (or node with index - 1)
        * If remove at front, current points to previous "node" of head (current = NULL, index = -1)
        * Exception: throw std::out_of_range("Segmentation fault!") if remove when current is NULL
    */
    if (current == nullptr) {
        throw std::out_of_range("Segmentation fault!");
    }
    if (pList->head == current) {
        pList->removeAt(0);
        current = nullptr;
        index = -1;
        return;
    }

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
}

template<class T>
void SLinkedList<T>::Iterator::set(const T &e) {
    /*
        Set the new value for current node
        * Exception: throw std::out_of_range("Segmentation fault!") if current is NULL
    */
    if (current == nullptr) {
        throw std::out_of_range("Segmentation fault!");
    }
    current->data = e;
}

template<class T>
T &SLinkedList<T>::Iterator::operator*() {
    /*
        Get data stored in current node
        * Exception: throw std::out_of_range("Segmentation fault!") if current is NULL
    */
    if (current == nullptr) {
        throw std::out_of_range("Segmentation fault!");
    }
    return current->data;
}

template<class T>
bool SLinkedList<T>::Iterator::operator!=(const Iterator &iterator) {
    /*
        Operator not equals
        * Returns true if two iterators points the same node and index
    */

    return iterator.index != index || iterator.current != current;
}

// Prefix ++ overload
template<class T>
typename SLinkedList<T>::Iterator &SLinkedList<T>::Iterator::operator++() {
    /*
        Prefix ++ overload
        * Set current to the next node
        * If iterator corresponds to the previous "node" of head, set it to head
        * Exception: throw std::out_of_range("Segmentation fault!") if iterator corresponds to the end
    */
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

// Postfix ++ overload
template<class T>
typename SLinkedList<T>::Iterator SLinkedList<T>::Iterator::operator++(int) {
    /*
        Postfix ++ overload
        * Set current to the next node
        * If iterator corresponds to the previous "node" of head, set it to head
        * Exception: throw std::out_of_range("Segmentation fault!") if iterator corresponds to the end
    */
    auto oldValue = SLinkedList<T>::Iterator(*this);
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
    SLinkedList<int> list;

    int size = 10;
    for (int idx = 0; idx < size; idx++) {
        list.add(idx);
    }

    SLinkedList<int>::Iterator it;
    int expvalue = 0;
    for (it = list.begin(); it != list.end(); it++) {
        assert(*it == expvalue);
        expvalue += 1;
    }
}
