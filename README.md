# Smart-Bookshelf-Library-Inventory-Management-System
# 📚 Smart Bookshelf & Library Inventory Management System

A C++-based Smart Bookshelf and Library Inventory Management System that simulates real-world bookshelf operations using Linked Lists and Object-Oriented Programming concepts. The project extends traditional bookshelf management by supporting multiple shelf behaviors, advanced linked list manipulations, inventory analytics, search capabilities, and persistent storage.

---

## 🚀 Overview

Managing large collections of books efficiently requires more than simple storage and retrieval operations. This project implements a modular bookshelf management framework that supports different shelf behaviors while demonstrating key software engineering principles such as:

- Object-Oriented Design
- Inheritance & Polymorphism
- Dynamic Memory Management
- Linked List Manipulation
- Data Structures & Algorithms
- File Handling

The system models two types of bookshelves:

### Vertical Bookshelf (LIFO)
Books are added and removed from the same end, behaving like a Stack.

### Horizontal Bookshelf (FIFO)
Books are added from one end and removed from the opposite end, behaving like a Queue.

---

## ✨ Features

### Core Features

- Add books to shelves
- Remove books from shelves
- Display shelf contents
- Reverse complete bookshelf
- Reverse books in groups of K
- Dynamic linked-list implementation
- Abstract bookshelf framework
- Function overriding for shelf-specific behavior

### Advanced Features

- Search books by title, author, year, or price
- Sort books using linked-list-based sorting algorithms
- Book transfer between shelves
- Shelf inventory statistics
- Most expensive and oldest book analysis
- Persistent storage using file handling
- Operation history tracking
- Undo functionality (Optional Enhancement)

---

## 🏗️ System Architecture

```text
                    +----------------+
                    |      Book      |
                    +----------------+
                             |
                             v
                    +----------------+
                    |      Node      |
                    +----------------+
                             |
                             v
                    +----------------+
                    |   Bookshelf    |
                    |  (Abstract)    |
                    +----------------+
                      /            \
                     /              \
                    v                v
       +------------------+   +--------------------+
       | VerticalBookshelf|   |HorizontalBookshelf |
       +------------------+   +--------------------+
```

---

## 📖 Class Design

### Book

Stores information about a book.

```cpp
class Book {
private:
    string title;
    string author;
    int year;
    int price;
};
```

### Node

Represents a linked-list node containing book data.

```cpp
class Node {
public:
    Book data;
    Node* next;
};
```

### Bookshelf (Abstract Base Class)

Provides common functionality shared by all shelf types.

```cpp
class Bookshelf {
protected:
    Node* head;
    Node* tail;

public:
    virtual void addBook(Book b) = 0;
    virtual void removeBook(int n) = 0;
    virtual void list() = 0;
    virtual void reverse() = 0;
    virtual void reverseK(int k) = 0;
};
```

### Derived Classes

- VerticalBookshelf
- HorizontalBookshelf

Each class overrides operations according to its storage policy.

---

## 🔄 Supported Operations

### Add Book

```text
ADD V CleanCode Martin 2008 500
ADD H CPPPrimer Lippman 2013 700
```

### Remove Books

```text
REMOVE 2 V
REMOVE 1 H
```

### Display Shelf

```text
LIST V
LIST H
```

### Reverse Shelf

```text
REVERSE V
```

### Reverse in Groups

```text
REVERSEK 3 H
```

---

## 🔍 Search Operations

```text
SEARCH TITLE CleanCode
SEARCH AUTHOR Martin
SEARCH YEAR 2015
SEARCH PRICE 500
```

---

## 📊 Analytics

The system can generate useful inventory insights:

- Total Books
- Total Inventory Value
- Average Book Price
- Most Expensive Book
- Oldest Book
- Newest Book

Example:

```text
Total Books: 50
Inventory Value: ₹25000
Most Expensive: DesignPatterns
```

---

## 💾 Persistent Storage

Bookshelf data can be stored and retrieved using files.

### Save

```text
SAVE books.dat
```

### Load

```text
LOAD books.dat
```

Benefits:

- Data survives program restart
- Easy backup and recovery
- Improved usability

---

## 🧠 Algorithms Used

### Linked List Operations

- Insertion
- Deletion
- Traversal
- Complete Reversal
- K-Group Reversal

### Searching

- Linear Search
- Multi-Attribute Search

### Sorting

- Merge Sort on Linked Lists
- Quick Sort on Linked Lists

---

## ⚡ Time Complexity

| Operation | Complexity |
|------------|------------|
| Add Book | O(1) |
| Remove Book | O(1) |
| Search Book | O(n) |
| List Books | O(n) |
| Reverse Shelf | O(n) |
| ReverseK | O(n) |
| Sort Books | O(n log n) |

---

## 🛠️ Technologies Used

- C++
- Object-Oriented Programming
- Linked Lists
- Inheritance
- Polymorphism
- Dynamic Memory Allocation
- File Handling
- Data Structures & Algorithms

---

## 🎯 Learning Outcomes

This project demonstrates:

- Abstract Class Design
- Function Overriding
- Dynamic Data Structures
- Memory Management
- Algorithm Design
- Software Architecture
- Clean Code Practices

---

## 📸 Sample Output

```text
ADD V B1 A1 2010 100
ADD V B2 A2 2011 200

LIST V

Output:
B2 A2 2011 200
B1 A1 2010 100
```

---

## 👨‍💻 Author

Developed as an Object-Oriented Programming and Data Structures project to demonstrate practical applications of Linked Lists, Inheritance, Polymorphism, Dynamic Memory Management, and Software Engineering principles.

### Key Highlights

- Implemented stack-based and queue-based bookshelf behaviors using linked lists.
- Designed an extensible object-oriented architecture using abstract classes and function overriding.
- Developed advanced linked-list algorithms including complete reversal and k-group reversal.
- Incorporated search, sorting, and inventory analytics functionalities.
- Applied clean coding practices and modular software design principles.

---
