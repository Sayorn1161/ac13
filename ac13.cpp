#include <iostream>

template<typename T>
class Node {
public:
    T data;
    Node* next;

    Node(const T& value) : data(value), next(nullptr) {}
};

template<typename T>
class LinkedList {
private:
    Node<T>* head;

    void clear() {
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

public:
    LinkedList() : head(nullptr) {}

    LinkedList(const LinkedList& other) : head(nullptr) {
        if (other.head) {
            head = new Node<T>(other.head->data);
            Node<T>* current = head;
            Node<T>* otherCurrent = other.head->next;
            while (otherCurrent) {
                current->next = new Node<T>(otherCurrent->data);
                current = current->next;
                otherCurrent = otherCurrent->next;
            }
        }
    }

    LinkedList(LinkedList&& other) noexcept : head(other.head) {
        other.head = nullptr;
    }

    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear();
            if (other.head) {
                head = new Node<T>(other.head->data);
                Node<T>* current = head;
                Node<T>* otherCurrent = other.head->next;
                while (otherCurrent) {
                    current->next = new Node<T>(otherCurrent->data);
                    current = current->next;
                    otherCurrent = otherCurrent->next;
                }
            }
        }
        return *this;
    }

    LinkedList& operator=(LinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            other.head = nullptr;
        }
        return *this;
    }

    ~LinkedList() {
        clear();
    }

    void add(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (!head) {
            head = newNode;
        } else {
            Node<T>* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void display() const {
        Node<T>* temp = head;
        while (temp) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
};
