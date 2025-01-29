// Book.java
import java.io.Serializable;

public class Book implements Serializable {
    private String title;
    private String author;
    private String isbn;
    private boolean isBorrowed;

    // Constructor
    public Book(String title, String author, String isbn) {
        this.title = title;
        this.author = author;
        this.isbn = isbn;
        this.isBorrowed = false;  // Initially, books are not borrowed
    }

    // Getter and Setter methods
    public String getTitle() {
        return title;
    }

    public String getAuthor() {
        return author;
    }

    public String getIsbn() {
        return isbn;
    }

    public boolean isBorrowed() {
        return isBorrowed;
    }

    public void borrowBook() {
        if (!isBorrowed) {
            isBorrowed = true;
            System.out.println("The book has been borrowed: " + title);
        } else {
            System.out.println("This book is already borrowed.");
        }
    }

    public void returnBook() {
        if (isBorrowed) {
            isBorrowed = false;
            System.out.println("The book has been returned: " + title);
        } else {
            System.out.println("This book wasn't borrowed.");
        }
    }

    @Override
    public String toString() {
        return "Title: " + title + ", Author: " + author + ", ISBN: " + isbn + ", Borrowed: " + (isBorrowed ? "Yes" : "No");
    }
}

