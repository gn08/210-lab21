#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;
const int NUM_NAMES = 15;
const int NUM_COLORS = 15;
const int MIN_AGE = 1;
const int MAX_AGE = 20;

void push_back(Goat value);
void push_front(Goat value);
void insert_after(Goat value, int position);
void delete_node(const Goat& value);
void print();
void print_reverse();

// Goat() constructor with random age, name, and color
// return: Goat object
class Goat {
    private:
        int age;
        string name;
        string color;
    public:
        static string names[NUM_NAMES];
        static string colors[NUM_COLORS];

        Goat(){
            age = rand() % (MAX_AGE - MIN_AGE + 1) + MIN_AGE;
            name = names[rand() % NUM_NAMES];
            color = colors[rand() % NUM_COLORS];
        }
//Goat(int a, string n, string c) Goat with specific values
// arguments: int a, string n, string c
//return: Goat object
        Goat(int a, string n, string c) : age(a), name(n), color(c) {}
        int get_age() const {return age;}
        string get_name() const {return name;}
        string get_color() const {return color;}

        void print() const {
            cout << name << "(" << color << "," << age << ")";
        }
//checks if Goat objects are not equal
        bool operator!=(const Goat& other) const {
            return !(age == other.age && name == other.name && color == other.color);
        }
//cgecks if Goat objects are equal
        bool operator==(const Goat& other) const {
            return (age == other.age && name == other.name && color == other.color);
        }
};

string Goat::names[NUM_NAMES] = {
    "Senior" , "Godlike" , "Old", "Old", "Mature" , "Teen", "Teen"
};

string Goat::colors[NUM_COLORS] = {
    "Yellow" , "Red", "Red", "Gold", "Mauve", "Gold" , "White"
};

class DoublyLinkedList {
private:
    struct Node {
        Goat data;
        Node* prev;
        Node* next;
        Node(Goat val, Node* p= nullptr, Node* n= nullptr): data(val), prev(p), next(n){}
    };

    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() : head(nullptr), tail(nullptr){}

//push_back() adds Goat to the end
//arguments: Goat value- goat object
//return: void
    void push_back(Goat value) {
        Node* newNode = new Node(value);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
//push_front() adds Goat to the front 
//arguments: Goat value- goat object
//return: void
    void push_front(Goat value) {
        Node* newNode = new Node(value);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
//insert_after() insert Goat after specific position
//arguments: Goat value- goat object, int position- place where to add Goat
//returns:void
    void insert_after(Goat value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }
//delete_node() delets first Goat objext from list
// arguments: const Goat& value- Goat object
///returns:void
    void delete_node(const Goat& value) {
        if (!head) return; // Empty list

        Node* temp = head;
        while (temp && !(temp->data == value))
            temp = temp->next;

        if (!temp) return; // Value not found

        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }

        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }

        delete temp;
    }
//print() print out Goat objects in list
//returns:void
    void print() {
        if (!head){
            cout << "List empty";
            return;
        }
        Node* current = head;
        while (current) {
            current->data.print();
            cout << " ";
            current = current->next;
        }
        cout << endl;
    }
//print_reverse() print out Goat object in list backwards
//return: void
    void print_reverse() {
       Node* current = tail;
        if (!tail) {
            cout << "List empty";
            return;
        }
        while (current) {
            current->data.print();
            cout << " ";
            current = current->prev;
        }
        cout << endl;
    }
// ~DoublyLinkedList()destructor , deletes nodes
//return: void
    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
int main() {
    srand(time(0));
    DoublyLinkedList list;
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;

    for (int i = 0; i < size; ++i){
        Goat randomGoat;
        list.push_back(randomGoat);
    }
    cout << "List forward: ";
    list.print();

    cout << "List backward: ";
    list.print_reverse();

    cout << "Deleting list, then trying to print.\n";
    cout << "List forward: ";
    list.print();

    return 0;
}
