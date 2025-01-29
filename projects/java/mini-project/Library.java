// Library.java
import java.io.*;
import java.util.*;

public class Library {
    private List<Book> books;
    private String libraryFile;

    // Constructor
    public Library(String libraryFile) {
        this.books = new ArrayList<>();
        this.libraryFile = libraryFile;
        loadLibraryData();
    }

    // Load library data from a file
    public void loadLibraryData() {
        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(libraryFile))) {
            books = (List<Book>) ois.readObject();
        } catch (IOException | ClassNotFoundException e) {
            System.out.println("No previous library data found. Starting fresh.");
        }
    }

    // Save library data to a file
    public void saveLibraryData() {
        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(libraryFile))) {
            oos.writeObject(books);
        } catch (IOException e) {
            System.out.println("Error saving library data.");
        }
    }

    // Add a book to the library
    public void addBook(Book book) {
        books.add(book);
        saveLibraryData();
    }

    // Display all books
    public void displayBooks() {
        if (books.isEmpty()) {
            System.out.println("No books available.");
        } else {
            for (Book book : books) {
                System.out.println(book);
            }
        }
    }

    // Borrow a book by ISBN
    public void borrowBook(String isbn) {
        Book book = findBookByIsbn(isbn);
        if (book != null) {
            book.borrowBook();
            saveLibraryData();
        } else {
            System.out.println("Book not found!");
        }
    }

    // Return a book by ISBN
    public void returnBook(String isbn) {
        Book book = findBookByIsbn(isbn);
        if (book != null) {
            book.returnBook();
            saveLibraryData();
        } else {
            System.out.println("Book not found!");
        }
    }

    // Find a book by ISBN
    private Book findBookByIsbn(String isbn) {
        for (Book book : books) {
            if (book.getIsbn().equals(isbn)) {
                return book;
            }
        }
        return null;
    }

    // Search for books by title
    public void searchBooksByTitle(String title) {
        List<Book> results = new ArrayList<>();
        for (Book book : books) {
            if (book.getTitle().toLowerCase().contains(title.toLowerCase())) {
                results.add(book);
            }
        }
        if (results.isEmpty()) {
            System.out.println("No books found with the title: " + title);
        } else {
            results.forEach(System.out::println);
        }
    }

    // Search for books by author
    public void searchBooksByAuthor(String author) {
        List<Book> results = new ArrayList<>();
        for (Book book : books) {
            if (book.getAuthor().toLowerCase().contains(author.toLowerCase())) {
                results.add(book);
            }
        }
        if (results.isEmpty()) {
            System.out.println("No books found by the author: " + author);
        } else {
            results.forEach(System.out::println);
        }
    }
}

