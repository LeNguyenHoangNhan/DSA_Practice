#include <iostream>
#include <cassert>

template<typename T>
class SLinkedList {
public:
    class Node;// Forward declaration
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

public:
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

int main() {
    SLinkedList<int> list;
    int values[] = { 10, 15, 2, 6, 4, 7, 40, 8 };
    int index[] = { 0, 0, 1, 3, 2, 3, 5, 0 };
    int expvalues[] = { 8, 15, 2, 4, 7, 10, 40, 6 };

    for (int idx = 0; idx < 8; idx++) {
        list.add(index[idx], values[idx]);
    }

    assert(list.size() == 8);

    for (int idx = 0; idx < 8; idx++) {
        assert(list.get(idx) == expvalues[idx]);
    }
    list.get(8);
    std::cout << list.toString();
}
