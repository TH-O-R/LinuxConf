// Parent class
class Shape {
    public void draw() {
        System.out.println("Drawing a shape...");
    }
}

// Child class 1
class Circle extends Shape {
    public void draw() {
        System.out.println("Drawing a circle...");
    }
}

// Child class 2
class Rectangle extends Shape {
    public void draw() {
        System.out.println("Drawing a rectangle...");
    }
}

public class ShapeTest {
    public static void main(String[] args) {
        Shape shape1 = new Circle();
        Shape shape2 = new Rectangle();

        shape1.draw();  // Output: Drawing a circle...
        shape2.draw();  // Output: Drawing a rectangle...
    }
}

