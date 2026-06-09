#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// Represents a single book
class Book {
private:
    string title;
    string author;
    int year;
    int price;

public:
    Book() : title(""), author(""), year(0), price(0) {}
    Book(string t, string a, int y, int p) : title(t), author(a), year(y), price(p) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    int getPrice() const { return price; }

    void print() const {
        cout << title << " | " << author << " | " << year << " | INR " << price << "\n";
    }
    
    string serialize() const {
        return title + "," + author + "," + to_string(year) + "," + to_string(price);
    }
};

// Linked List Node
class Node {
public:
    Book data;
    Node* next;
    Node(Book b) : data(b), next(nullptr) {}
};

// Abstract Base Class
class Bookshelf {
protected:
    Node* head;
    Node* tail;

    void updateTail() {
        if (!head) { tail = nullptr; return; }
        Node* curr = head;
        while (curr->next) curr = curr->next;
        tail = curr;
    }

    Node* reverseKNodes(Node* curr, int k) {
        if (!curr) return nullptr;
        Node *current = curr, *next = nullptr, *prev = nullptr;
        int count = 0;
        
        while (current != nullptr && count < k) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
            count++;
        }
        if (next != nullptr) curr->next = reverseKNodes(next, k);
        return prev;
    }

public:
    Bookshelf() : head(nullptr), tail(nullptr) {}
    virtual ~Bookshelf() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    virtual void addBook(Book b) = 0;
    
    // Removes 'n' books from the front
    virtual void removeBook(int n) {
        for (int i = 0; i < n && head != nullptr; ++i) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        if (!head) tail = nullptr;
    }

    virtual void list() {
        if (!head) { cout << "[Empty Shelf]\n"; return; }
        Node* current = head;
        while (current) {
            current->data.print();
            current = current->next;
        }
    }

    virtual void reverse() {
        if (!head || !head->next) return;
        Node *current = head, *prev = nullptr, *next = nullptr;
        tail = head;
        while (current) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }

    virtual void reverseK(int k) {
        if (k <= 1 || !head) return;
        head = reverseKNodes(head, k);
        updateTail();
    }

    // Generic search covering all attributes
    void search(const string& attr, const string& value) {
        if (!head) { cout << "[Shelf Empty]\n"; return; }
        Node* curr = head;
        bool found = false;
        
        while (curr) {
            bool match = false;
            if (attr == "TITLE" && curr->data.getTitle() == value) match = true;
            else if (attr == "AUTHOR" && curr->data.getAuthor() == value) match = true;
            else if (attr == "YEAR" && to_string(curr->data.getYear()) == value) match = true;
            else if (attr == "PRICE" && to_string(curr->data.getPrice()) == value) match = true;
            
            if (match) { curr->data.print(); found = true; }
            curr = curr->next;
        }
        if (!found) cout << "No matches found.\n";
    }

    void showAnalytics() {
        if (!head) { cout << "No data available.\n"; return; }
        
        int totalBooks = 0, totalValue = 0;
        Book mostExpensive = head->data, oldest = head->data;

        Node* curr = head;
        while (curr) {
            totalBooks++;
            totalValue += curr->data.getPrice();
            if (curr->data.getPrice() > mostExpensive.getPrice()) mostExpensive = curr->data;
            if (curr->data.getYear() < oldest.getYear()) oldest = curr->data;
            curr = curr->next;
        }

        cout << "Total Books: " << totalBooks << "\n"
             << "Inventory Value: INR " << totalValue << "\n"
             << "Average Price: INR " << (totalValue / totalBooks) << "\n"
             << "Most Expensive: " << mostExpensive.getTitle() << "\n"
             << "Oldest Book: " << oldest.getTitle() << " (" << oldest.getYear() << ")\n";
    }

    void saveToFile(const string& filename) {
        ofstream outFile(filename);
        if (!outFile) { cout << "Error: Cannot open " << filename << "\n"; return; }
        
        Node* curr = head;
        while (curr) {
            outFile << curr->data.serialize() << "\n";
            curr = curr->next;
        }
        cout << "Saved to " << filename << "\n";
    }
};

// LIFO Implementation (Stack)
class VerticalBookshelf : public Bookshelf {
public:
    void addBook(Book b) override {
        Node* newNode = new Node(b);
        if (!head) head = tail = newNode;
        else {
            newNode->next = head;
            head = newNode;
        }
    }
};

// FIFO Implementation (Queue)
class HorizontalBookshelf : public Bookshelf {
public:
    void addBook(Book b) override {
        Node* newNode = new Node(b);
        if (!head) head = tail = newNode;
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }
};

// Command Interface
int main() {
    VerticalBookshelf vShelf;
    HorizontalBookshelf hShelf;
    string line;

    cout << "System ready. Type commands (e.g., ADD V Book Author 2020 500) or 'EXIT'.\n";

    while (true) {
        cout << "> ";
        if (!getline(cin, line) || line == "EXIT") break;

        stringstream ss(line);
        string cmd, type;
        ss >> cmd;

        if (cmd == "ADD") {
            string title, author;
            int year, price;
            if (ss >> type >> title >> author >> year >> price) {
                if (type == "V") vShelf.addBook(Book(title, author, year, price));
                else if (type == "H") hShelf.addBook(Book(title, author, year, price));
                else cout << "Error: Invalid shelf type (V/H).\n";
            } else cout << "Error: Invalid ADD format.\n";
            
        } else if (cmd == "REMOVE" || cmd == "REVERSEK") {
            int val;
            if (ss >> val >> type) {
                Bookshelf* shelf = (type == "V") ? (Bookshelf*)&vShelf : (type == "H") ? (Bookshelf*)&hShelf : nullptr;
                if (!shelf) cout << "Error: Invalid shelf type (V/H).\n";
                else if (cmd == "REMOVE") shelf->removeBook(val);
                else shelf->reverseK(val);
            } else cout << "Error: Invalid format.\n";
            
        } else if (cmd == "LIST" || cmd == "REVERSE" || cmd == "ANALYTICS") {
            if (ss >> type) {
                Bookshelf* shelf = (type == "V") ? (Bookshelf*)&vShelf : (type == "H") ? (Bookshelf*)&hShelf : nullptr;
                if (!shelf) cout << "Error: Invalid shelf type (V/H).\n";
                else if (cmd == "LIST") shelf->list();
                else if (cmd == "REVERSE") shelf->reverse();
                else shelf->showAnalytics();
            } else cout << "Error: Invalid format.\n";
            
        } else if (cmd == "SEARCH") {
            string attr, value;
            if (ss >> attr >> value) {
                cout << "[Vertical]\n"; vShelf.search(attr, value);
                cout << "[Horizontal]\n"; hShelf.search(attr, value);
            } else cout << "Error: Invalid SEARCH format.\n";
            
        } else if (cmd == "SAVE") {
            string filename;
            if (ss >> filename) {
                vShelf.saveToFile("V_" + filename);
                hShelf.saveToFile("H_" + filename);
            } else cout << "Error: Missing filename.\n";
            
        } else if (!cmd.empty()) {
            cout << "Error: Unknown Command.\n";
        }
    }
    return 0;
}