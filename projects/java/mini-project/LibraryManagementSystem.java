// LibraryManagementSystem.java
import java.util.Scanner;

public class LibraryManagementSystem {
    private static Library library;
    private static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        library = new Library("libraryData.ser");

        while (true) {
            showMenu();
            int choice = scanner.nextInt();
            scanner.nextLine();  // Consume the newline character

            switch (choice) {
                case 1:
                    addBook();
                    break;
                case 2:
                    library.displayBooks();
                    break;
                case 3:
                    borrowBook();
                    break;
                case 4:
                    returnBook();
                    break;
                case 5:
                    searchBookByTitle();
                    break;
                case 6:
                    searchBookByAuthor();
                    break;
                case 7:
                    System.out.println("Exiting system...");
                    library.saveLibraryData();
                    System.exit(0);
                    break;
                default:
                    System.out.println("Invalid choice! Please try again.");
            }
        }
    }

    public static void showMenu() {
        System.out.println("\n--- Library Management System ---");
        System.out.println("1. Add a Book");
        System.out.println("2. Display All Books");
        System.out.println("3. Borrow a Book");
        System.out.println("4. Return a Book");
        System.out.println("5. Search Book by Title");
        System.out.println("6. Search Book by Author");
        System.out.println("7. Exit");
        System.out.print("Enter your choice: ");
    }

    public static void addBook() {
        System.out.print("Enter book title: ");
        String title = scanner.nextLine();
        System.out.print("Enter author name: ");
        String author = scanner.nextLine();
        System.out.print("Enter ISBN: ");
        String isbn = scanner.nextLine();

        Book book = new Book(title, author, isbn);
        library.addBook(book);
        System.out.println("Book added successfully!");
    }

    public static void borrowBook() {
        System.out.print("Enter ISBN of the book to borrow: ");
        String isbn = scanner.nextLine();
        library.borrowBook(isbn);
    }

    public static void returnBook() {
        System.out.print("Enter ISBN of the book to return: ");
        String isbn = scanner.nextLine();
        library.returnBook(isbn);
    }

    public static void searchBookByTitle() {
        System.out.print("Enter title to search: ");
        String title = scanner.nextLine();
        library.searchBooksByTitle(title);
    }

    public static void searchBookByAuthor() {
        System.out.print("Enter author to search: ");
        String author = scanner.nextLine();
        library.searchBooksByAuthor(author);
    }
}

