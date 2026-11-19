#include <stdio.h>
#include <string.h>
#define MAX_BOOKS 30
#define MAX_LOANS 50

typedef struct {
    int id;
    char title[50];
    int totalCopies;
    int availableCopies;
    int reservedBy;
} Book;

typedef struct {
int bookId;
int borrowerId;
int active;
} Loan;

//in class 1
int addBook(Book books[], int *count, int id, const char title[], int copies);
void displayBooks(const Book books[], int bookCount);
int borrowBook(Book books[], int bookCount, Loan loans[], int *loanCount, int bookId, int borrowerId);
int returnBook(Book books[], int bookCount,
Loan loans[], int loanCount,
int bookId, int borrowerId);
void displayActiveLoans(const Loan loans[],
int loanCount);
void displayStatistics(const Book books[],
int bookCount,
const Loan loans[],
int loanCount);

//in class 2
int findBookRecursive(const Book books[], int bookCount,
int bookId, int index);
int countActiveLoansRecursive(const Loan loans[],
int loanCount, int index);
int sumAvailableCopiesRecursive(const Book books[],
int bookCount, int index);


int main(void) {
    Book books[MAX_BOOKS];
    Loan loans[MAX_LOANS];

    int bookCount = 0;
    int loanCount = 0;
    int choice;

    do {

        printf("\n===== LIBRARY MANAGEMENT SYSTEM =====\n");
        printf("1. Add a book\n");
        printf("2. Display all books\n");
        printf("3. Borrow a book\n");
        printf("4. Return a book\n");
        printf("5. Reserve a book\n");
        printf("6. Display active loans\n");
        printf("7. Display library statistics\n");
        printf("8. Search for a book (recursive)\n");
        printf("9. Display recursive summary\n");
        printf("0. Exit\n");
        printf("\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice < 0 || choice > 9) {
            printf("Invalid Input. Please pick between 0-9\n");
        }

        switch (choice) {

            //add a book
            case 1: {
                int id;
                int copies;
                char title[50];

                printf("Enter book ID: ");
                scanf("%d", &id);
                if (id < 0) {
                    printf("Invalid Book ID. Must be positive number.\n");
                    break;
                }

                printf("Enter book title: ");
                scanf("%49s", title);

                printf("Enter number of copies: ");
                scanf("%d", &copies);

                if (addBook(books, &bookCount, id, title, copies)) {
                    printf("Book added successfully\n");
                } else {
                    printf("Failed to add book.\n");
                    }
                printf("\n");
                break;
                }
            
            //display all books
            case 2: {
                printf("Book List:\n");
                displayBooks(books, bookCount);
                printf("\n");
                break;
            }

            //borrow a book
            case 3: {
                int borrower_id;
                int borrowed_book_id;
                int result;
                
                printf("Enter borrower ID: ");
                scanf("%d", &borrower_id);
                
                printf("Enter ID of book you want to borrow: ");
                scanf("%d", &borrowed_book_id);

                result = borrowBook(books, bookCount, loans, &loanCount, borrowed_book_id, borrower_id);

                if (result == 0) {
                    printf("Borrow process failed.\n");
                } else {
                    printf("Borrowed successfully.\n");
                }

                break;

            }

            //return a book
            case 4: {
                int bookId;
                int borrowerId;

                printf("Enter book ID: ");
                scanf("%d", &bookId);

                printf("Enter borrower ID: ");
                scanf("%d", &borrowerId);

                if (returnBook(books, bookCount, loans, loanCount, bookId, borrowerId)) {
                    printf("Book returned successfully.\n");
                } else {
                    printf("Failed to return book. Invalid book or loan.\n");
                }

                break;
            }

            //reserve a book
            case 5: {
                

                break;
            }

            case 6: {
                displayActiveLoans(loans, loanCount);
                break;
            }

            //display library statistics
            case 7: {
                displayStatistics(books, bookCount, loans, loanCount);
                break;
            }

            //search for a book recursive
            case 8: {
                int book_id;
                do {
                    printf("Enter book ID: ");
                    
                    //check if positive int
                    if (scanf("%d", &book_id) != 1 || book_id <= 0) {
                        printf("Invalid book ID. Enter a positive integer.\n");

                        //clear invalid input
                        while (getchar() != '\n');
                        book_id = 0;
                    } 
                    
                } while (book_id <= 0);

                int index = findBookRecursive(books, bookCount, book_id, 0);

                if (index == -1) {
                    printf("Book does not exist.\n");
                    
                } else {
                    printf("Book found.\n");
                    printf("Book id: %d\n", books[index].id);
                    printf("Book title: %.49s\n", books[index].title );
                    printf("Total copies: %d\n", books[index].totalCopies);
                    printf("Available copies: %d\n", books[index].availableCopies);
                    
                }
                break;
            }

            //display recursive summary
            case 9: {
                int activeLoans = countActiveLoansRecursive(loans, loanCount, 0);
                
                int availableCopies = sumAvailableCopiesRecursive(books, bookCount, 0);

                printf("\n===== RECURSIVE LIBRARY STATISTICS =====\n");
                printf("Total active loans: %d\n", activeLoans);
                printf("Total available book copies: %d\n", availableCopies);
                
               break; 
            }

            //exit
            case 0: {
                printf("Bye, thank you!");
                break;
            }

            default: {
                break;
            }
                            

        } 
    } while (choice != 0);

    return 0;
}

int addBook(Book books[], int *count, int id, const char title[], int copies) {
    //success 1, fail 0
    
    //Reject if array is full or empty
    if (*count >= MAX_BOOKS) {
        printf("Max number of books reached.\n");
        return 0;
    }

    //check copies
    if (copies <= 0) {
        printf("Invalid copy amount.\n");
        return 0;
    }

    //check title
    if (title == NULL || strlen(title) == 0) {
        printf("Invalid empty title.\n");
        return 0;
    }
    //check id
    for (int i = 0; i < *count; i++) {
        if (id == books[i].id) {
            printf("Invalid duplicate ID.\n");
            return 0;
        }
    }
    
    //add new book
    books[*count].id = id;
    strcpy(books[*count].title, title);
    books[*count].totalCopies = copies;
    books[*count].availableCopies = copies;
    books[*count].reservedBy = 0;
    (*count)++;
    return 1;

}

void displayBooks(const Book books[], int bookCount) {
    for (int i = 0; i < bookCount; i++) {
        printf("Book ID: %d\n", books[i].id);
        printf("Book Title: %.49s\n", books[i].title);
        printf("Total Copies: %d\n", books[i].totalCopies);
        printf("Avaliable Copies: %d\n", books[i].availableCopies);
        printf("\n");
    }
    
}

int borrowBook(Book books[], int bookCount, Loan loans[], int *loanCount,
int bookId, int borrowerId) {
    int bookIndex = -1;
    int loanIndex = -1;

    //if no book id
    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == bookId) {
            bookIndex = i;
        }
    }
    if (bookIndex == -1) {
        printf("Book not exist.\n");
        return 0;
    }

    //if no available copies
    if (books[bookIndex].availableCopies <= 0) {
        printf("No available copies.\n");
        return 0;
    }

    //if borrow same book twice
    for (int i = 0; i < *loanCount; i++) {
        if (loans[i].borrowerId == borrowerId && loans[i].bookId == bookId && loans[i].active == 1) {
            printf("Borrower can not borrow the same book twice at one time.\n");
            return 0; 
        }
    }

    //reuse inactive loan slot
    for (int i = 0; i < *loanCount; i++) {
        if (loans[i].active == 0) {
            loanIndex = i;
            break;
        }
    }

    //if no inactive slot
    if (loanIndex == -1) {
        if (*loanCount >= MAX_LOANS) {
            printf("No available loan slots.\n");
            return 0;
        }

        loanIndex = *loanCount;
        (*loanCount)++;
    }

    //successfully borrowed
    loans[loanIndex].bookId = bookId;
    loans[loanIndex].borrowerId = borrowerId;
    loans[loanIndex].active = 1;
    books[bookIndex].availableCopies--;

    return 1;
}

int returnBook(Book books[], int bookCount,
Loan loans[], int loanCount,
int bookId, int borrowerId) {
int bookIndex = -1;

for (int i = 0; i < bookCount; i++) {
    if (books[i].id == bookId) {
        bookIndex = i;
        break;
    } 
}

//reject if book does not exist
if (bookIndex == -1) {
    return 0;
} 

//find the active loan
for (int i = 0; i < loanCount; i++) {
    if (loans[i].bookId == bookId && loans[i].borrowerId == borrowerId && loans[i].active == 1) {
        //Mark loan as inactive
        loans[i].active = 0;

        //increase Avaliable copies
        books[bookIndex].availableCopies++;

        return 1;
    }
}

return 0;
}



void displayActiveLoans(const Loan loans[],
int loanCount) {
    int activeCount = 0;
    printf("Active Loans:\n");
    
    for (int i = 0; i < loanCount; i++) {
        if (loans[i].active == 1) {
            printf("Book ID: %d\n", loans[i].bookId);
            printf("Borrower ID: %d\n", loans[i].borrowerId);
            printf("\n");
            activeCount++;
        }
    }

    if (activeCount == 0) {
        printf("No active loans.\n");
    }

}

//library statistics
void displayStatistics(const Book books[],
int bookCount,
const Loan loans[],
int loanCount) {
    int totalCopies = 0;
    int availableCopies = 0;
    int activeLoans = 0;
    
    //Calculate total and available copies
    for (int i = 0; i < bookCount; i++) {
        totalCopies += books[i].totalCopies;
        availableCopies += books[i].availableCopies;
    }

    //Count active loans
    for (int i = 0; i < loanCount; i++) {
        if (loans[i].active == 1) {
            activeLoans++;
        }
    }
    
    printf("\n===== LIBRARY STATISTICS =====\n");
    printf("Total registered books: %d\n", bookCount);
    printf("Total book copies: %d\n", totalCopies);
    printf("Avaliable copies: %d\n", availableCopies);
    printf("Active loans: %d\n", activeLoans);
}



//in class 2 starts here:
//search for specific book id using recursion
int findBookRecursive(const Book books[], int bookCount,
int bookId, int index) {
    //base case
    if (index >= bookCount) {
        return -1;
    }

    //check current book id
    if (books[index].id == bookId) {
        return index;
    }

    //recursive call check next index
    return findBookRecursive(books, bookCount, bookId, index + 1);
}

int countActiveLoansRecursive(const Loan loans[],
int loanCount, int index) {
    //base case no remaining records to examine
    if (index >= loanCount) {
        return 0;
    }
    
    //recursive call
    //if active add 1 then go to next index
    if (loans[index].active != 0) {
        return 1 + countActiveLoansRecursive(loans, loanCount, index + 1);
    } else { //not active go to next index
        return countActiveLoansRecursive(loans, loanCount, index + 1);
    }
}

int sumAvailableCopiesRecursive(const Book books[],
int bookCount, int index) {
    //base case no remaining book
    if (index >= bookCount) {
        return 0;
    }

    //recursive call
    //sum available copies and go to next index
    return books[index].availableCopies + sumAvailableCopiesRecursive(books, bookCount, index + 1);
}

