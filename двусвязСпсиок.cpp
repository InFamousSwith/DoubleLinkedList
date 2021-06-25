#include <iostream>
using namespace std;

struct Node
{
    int value;
    Node* next;
    Node* prev;
    bool IsEqual(const Node& other) const {
        return value == other.value;
    }
};

struct Iterator {
    Node* ptr;
};

Iterator ToNext(const Iterator& it) {
    if (it.ptr != nullptr) {
        return Iterator{ it.ptr->next };
    }
    else {
        return Iterator{ nullptr };
    }
}

bool operator==(const Iterator& first, const Iterator& second) {
    return first.ptr == second.ptr;
}

bool operator!=(const Iterator& first, const Iterator& second) {
    return !(first == second);
}

Iterator operator++(Iterator& it) {
    it.ptr = it.ptr->next;
    return it;
}


class List
{
private:

    Node* start;
    Node* finish;
    int number;


public:
    List() : start(nullptr), finish(nullptr), number(0) {}

    void push_back(int val)
    {
        Node* newNode = new Node;
        newNode->value = val;
        newNode->next = nullptr;
        newNode->prev = finish;

        if (number == 0)
        {
            start = newNode;
            finish = newNode;
        }
        else
        {
            finish->next = newNode;
            finish = newNode;
        }
        ++number;
    }



    void push_front(int val)
    {
        Node* newNode = new Node;
        newNode->value = val;
        newNode->next = nullptr;
        newNode->prev = nullptr;

        if (number == 0)
        {
            start = newNode;
            finish = newNode;
        }
        else
        {
            newNode->next = start;
            start->prev = newNode;
            start = newNode;
        }
        ++number;
    }

    void pop_back() {
        if (number == 1) {
            delete finish;
            start = nullptr;
            finish = nullptr;
        }
        else {
            finish = finish->prev;
            delete finish->next;
            finish->next = nullptr;
        }
        --number;
    }

    void push_in_place(int place, int newValue) {
        if (place < 1 || place > number) {
            cout << "Error" << endl;
            return;
        }

        if (place > 1 && place < number) {
            Iterator it = begin();
            int tmp_index = 1;
            while (tmp_index != place) {
                ++it;
                ++tmp_index;
            }
            Node* newNode = new Node;
            newNode->value = newValue;
            newNode->next = it.ptr;
            newNode->prev = it.ptr->prev;

            newNode->prev->next = newNode;
            newNode->next->prev = newNode;

            ++number;
        }

        else if (place == 1) {
            push_front(newValue);
        }

        else if (place == number) {
            push_back(newValue);
        }
    }


    void pop_from_place(int place) {
        if (place < 1 || place > number) {
            cout << "Error" << endl;
            return;
        }

        if (place != 1 && place != number) {
            int tmp_index = 1;
            Iterator it = begin();

            while (tmp_index != place) {
                ++it;
                ++tmp_index;
            }
            it.ptr->next->prev = it.ptr->prev;
            it.ptr->prev->next = it.ptr->next;
            delete it.ptr;
            --number;
        }

        else if (place == 1) {
            pop_front();
        }

        else if (place == number) {
            pop_back();
        }
    }

    void pop_front()
    {
        if (number == 1) {
            delete start;
            start = nullptr;
            finish = nullptr;
        }
        else {
            start = start->next;
            delete start->prev;
            start->prev = nullptr;
        }

        --number;
    }

    Iterator begin() {
        return Iterator{ start };
    }

    Iterator end() {
        return Iterator{ finish->next };
    }

    Iterator Find(const int& value) {
        for (Iterator it = begin(); it != end(); ++it) {
            if (it.ptr->value == value) {
                return it;
            }
        }
        return Iterator{ nullptr };
    }

    void Print() {
        for (Iterator it = begin(); it != end(); ++it) {
            cout << it.ptr->value << endl;
        }
        cout << endl;
    }


    ~List() {
        while (number > 0) {
            pop_front();
        }
    }
};


int main() {
    List list;
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        list.push_back(i);
    }

    list.Print();

    list.push_in_place(3, 13);

    list.Print();

    list.pop_from_place(6);

    for (Iterator it = list.begin(); it != list.end(); ++it) {
        if (it == list.Find(3)) {
            cout << "Next value after 3 is " << ToNext(it).ptr->value << endl;
        }
    }

    list.Print();

    return 0;
}
