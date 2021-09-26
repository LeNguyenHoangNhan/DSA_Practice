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

int main() {
    DLinkedList<int> list;
    for (int i = 0; i < 5; i++) {
        list.add(i, i);
    }
    list.add(0, 99);
    list.add(1, 99);
    list.add(2, 99);
    list.add(3, 99);
    list.add(10, 99);
    list.add(-100, 99);
    list.add(999, 99);
}
