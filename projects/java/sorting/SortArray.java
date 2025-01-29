import java.util.Arrays;

public class SortArray {
    public static void main(String[] args) {
        int[] numbers = {5, 3, 8, 1, 2};

        System.out.println("Before sorting: " + Arrays.toString(numbers));
        
        // Sort the array
        Arrays.sort(numbers);

        System.out.println("After sorting: " + Arrays.toString(numbers));
    }
}

