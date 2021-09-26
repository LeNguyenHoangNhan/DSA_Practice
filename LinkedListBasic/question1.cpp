#include <iostream>

template<class T>
class SLinkedList {
public:
    class Node;// Forward declaration
protected:
    Node *head = nullptr;
    Node *tail = nullptr;
    int count = 0;

public:
    void add(const T &e);
    void add(int index, const T &e);
    int size();

    std::string toString() const;

    class Node {
    private:
        T data;
        Node *next;
        friend class SLinkedList<T>;

    public:
        Node() { next = 0; }
        Node(Node *next) { this->next = next; }
        Node(T data, Node *next) {
            this->data = data;
            this->next = next;
        }
    };
};

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
    output += ']';
    return output;
}

int main() {
    SLinkedList<int> list;
    list.add(100);
    list.add(200);
    list.add(300);
    list.add(400);
    list.add(500);
    std::cout << list.toString();
}
