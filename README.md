# C_Program-Library-book-collection-management
A simple C program for managing a library’s book collection. Users can add, borrow, return, and view available or borrowed books through a text-based menu.

# Library Book Management System

A simple C program for managing a library's book collection. Users can add, borrow, return, and view available or borrowed books through a text-based menu.

## Features

- **Add Book:** Add new books to the library by entering the book title.
- **Borrow Book:** Borrow a book by specifying its title. If the book exists, it is moved to the borrowed queue.
- **Return Book:** Return the first book from the borrowed queue back to the available books.
- **View Available Books:** Display all books currently available in the library.
- **View Borrowed Books:** Display all books that are currently borrowed.
- **Exit:** Safely exit the program, freeing all allocated memory.

## How It Works

- The program uses a singly linked list to manage available books.
- Borrowed books are managed using a queue (also implemented as a linked list).
- All user interactions are handled through a simple text-based menu.

## Usage

1. Compile the program:
    ```sh
    gcc -o library ypoergasia_2_Vivliothiki.c
    ```

2. Run the executable:
    ```sh
    ./library
    ```

3. Follow the on-screen menu to manage the library.

## Example Menu

```
|----------------------------------|
|------- Library Menu --------|
1. Add book
2. Borrow book
3. Return book
4. View available books
5. View borrowed books
6. Exit
Choice:
```
