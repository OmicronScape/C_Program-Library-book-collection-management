/*Library book collection management*/
/*The purpose of the program is to manage a library's book collection.
  The user can add books, borrow or return books,
  as well as view the list of available and borrowed books.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE_LENGTH 100

/*|---------------------------------INSTRUCTIONS-EXPLANATION OF LIBRARY PROGRAM USAGE-----------------------------------------|
    -->The user starts the program and the main menu appears (function menu()).<---                                          |
    -->The user selects numerically one of the following functions:                                                          |
        1.Add Book: The user selects 1 from the menu, enters the book title, and the book is added                           |
           to the list of available books (function add_book()).                                                             |
        2.Borrow Book: The user selects 2 from the menu, if the book exists it is removed from the list of available         |
           books (function: remove_book()) and immediately added to the borrowed queue (function: borrow_book()).            |
           If it does not exist, a relevant error message appears.                                                           |
        3.Return Book: The user selects 3 from the menu, if there are books in the borrowed queue, the first book            |
           in the queue is automatically returned and added again to the available list (function: return_book()             |
           and internally add_book()). If there are no books to return, a corresponding message appears.                     |
        4.View Available Books: The user selects 4 from the menu, a list of all available book titles appears                |
           (function: display_books()).                                                                                      |
        5.View Borrowed Books: The user selects 5 from the menu. A list of all borrowed books appears                        |
           (function: display_borrowed_books()).                                                                             |
        6.Exit: The user selects 6 from the menu, an exit message appears and the program terminates.                        |
----------------------------------------------------------------------------------------------------------------------------| */       



// Node for the book list
typedef struct BookNode
{
    char title[MAX_TITLE_LENGTH];
    struct BookNode* next;
} BookNode;

// Node for the borrowed books queue
typedef struct QueueNode
{
    char title[MAX_TITLE_LENGTH];
    struct QueueNode* next;
} QueueNode;

// Queue structure
typedef struct
{
    QueueNode* front;
    QueueNode* rear;
} Queue;

// Structure for the library
typedef struct
{
    BookNode* book_list; // List of available books
    Queue borrowed_queue; // Queue of borrowed books
} Library;

// Initialize library
void initialize_library(Library* library)
{
    library->book_list = NULL;
    library->borrowed_queue.front = NULL;
    library->borrowed_queue.rear = NULL;
}

// Add book to the list
void add_book(Library* library, const char* title)
{
    BookNode* new_book = (BookNode*)malloc(sizeof(BookNode));
    if (!new_book)
    {
        printf("Error: Memory allocation failed.\n");
        return;
    }
    strcpy(new_book->title,title);
    new_book->next = library->book_list;
    library->book_list = new_book;
    printf("The book '%s' was added to the library.\n",title);

}

// Remove book from the list
BookNode* remove_book(Library* library, const char* title)
{
    BookNode* current = library->book_list;
    BookNode* previous = NULL;

    while (current != NULL)
    {
        if(strcmp(current->title, title) == 0)
        {
            if(previous == NULL)
            {
                library->book_list = current->next;
            } else
            {
                previous->next = current->next;
            }
            return current; /*Return the removed node*/
        }
        previous = current;
        current = current->next;
    }
    printf("The book '%s' was not found in the library.\n", title);
    
}

// Borrow book
void borrow_book(Library* library, const char* title)
{
    // Remove the book from the list
    BookNode* book_to_borrow = remove_book(library, title);
    if (!book_to_borrow)
    {
        printf("The book '%s' was not found in the library.\n", title);
        return;  // If the book was not found, return
    }

    // Allocate memory for the new queue node
    QueueNode* new_queue_node = (QueueNode*)malloc(sizeof(QueueNode));
    if (!new_queue_node) {
        printf("Error: Memory allocation failed.\n");
        free(book_to_borrow);  // Free memory for the book
        return;
    }

    // Copy title
    strncpy(new_queue_node->title, book_to_borrow->title, MAX_TITLE_LENGTH - 1);
    new_queue_node->title[MAX_TITLE_LENGTH - 1] = '\0'; // Ensure null-termination
    new_queue_node->next = NULL;

    // Add the node to the queue
    if (library->borrowed_queue.rear == NULL)
    {
        library->borrowed_queue.front = new_queue_node;
    } else {
        library->borrowed_queue.rear->next = new_queue_node;
    }
    library->borrowed_queue.rear = new_queue_node;

    // Free memory for the removed book
    free(book_to_borrow);
    printf("The book '%s' was borrowed.\n", title);
}

// Return book
void return_book(Library* library)
{
    if (library->borrowed_queue.front == NULL)
    {
        printf("There are no borrowed books to return.\n");
        return;
    }

    QueueNode* node_to_return = library->borrowed_queue.front;
    library->borrowed_queue.front = node_to_return->next;

    if (library->borrowed_queue.front == NULL)
    {
        library->borrowed_queue.rear = NULL;
    }

    add_book(library, node_to_return->title);
    free(node_to_return);
    printf("The book was returned to the library.\n");

}

// Display available books
void display_books(const Library* library)
{
    BookNode* current = library->book_list;
    if(!current)
    {
        printf("There are no available books.\n");
        return;
    }

    printf("Available books: \n");
    while(current)
    {
        printf("- %s\n", current->title);
        current = current->next;
    }
}

// Display borrowed books
void display_borrowed_books(const Library* library)
{
   QueueNode* current = library->borrowed_queue.front;
   if(!current)
   {
    printf("There are no borrowed books.\n");
    return;
   } 

   printf("Borrowed books: \n");
   while (current)
   {
    printf("-%s\n", current->title);
    current = current->next;
   }
}

// Clear library memory
void clear_library(Library* library)
{
    // Clear book list
    BookNode* current_book = library->book_list;
    while (current_book)
    {
        BookNode* temp = current_book;
        current_book = current_book->next;
        free(temp);
    }

    // Clear borrowed queue
    QueueNode* current_queue = library->borrowed_queue.front;
    while (current_queue)
    {
        QueueNode* temp = current_queue;
        current_queue = current_queue->next;
        free(temp);
    }
}

// Menu options
void menu()
{
    printf("|----------------------------------|");
    printf("\n|------- Library Menu --------|\n");
    printf("1. Add book\n");            
    printf("2. Borrow book\n");
    printf("3. Return book\n");
    printf("4. View available books\n");
    printf("5. View borrowed books\n");
    printf("6. Exit\n");
    printf("Choice:  ");
}

int main()
{
    Library library;
    initialize_library(&library);
    
    while (1) {
        menu();
        int choice;
        scanf("%d", &choice);
        getchar();  // Clear buffer after scanf

        if (choice == 1)
        {
            printf("Enter the book title: ");
            char title[MAX_TITLE_LENGTH];
            fgets(title, MAX_TITLE_LENGTH, stdin);
            title[strcspn(title, "\n")] = 0; // Remove newline
            add_book(&library, title);
        } else if (choice == 2)
        {
            printf("Enter the book title to borrow: ");
            char title[MAX_TITLE_LENGTH];
            fgets(title, MAX_TITLE_LENGTH, stdin);
            title[strcspn(title, "\n")] = 0; // Remove newline
            borrow_book(&library, title);
        } else if (choice == 3)
        {
            return_book(&library);
        } else if (choice == 4)
        {
            display_books(&library);
        } else if (choice == 5)
        {
            display_borrowed_books(&library);
        } else if (choice == 6)
        {
            printf("Exiting the system.\n");
            break;
        } else
        {
            printf("Invalid choice. Please try again.\n");
        }

        printf("\nPress Enter to return to the menu...\n");
        getchar();
        
    }

    clear_library(&library); // Clear memory before exit
    return 0;
}
