import java.util.Scanner;

public class Paint {
    static Scanner scnr = new Scanner(System.in);

    // Get wall height from user input, if wrong input type or number is less than 1
    // prompts user to input 20another value
    public static double getHeight() {
        while (true) {
            System.out.println("Enter wall height (feet): ");
            String input = scnr.next();
            double height;
            try {
                height = Double.parseDouble(input);
                if ( height < 1.0 ) {
                    throw new Exception();
                }
                return height;
            } catch (Exception excpt) {
                System.out.println("Invalid Entry:  Input must be a number greater than 1");
                continue;
            }
        }
    }

    // Get wall width from user input, if wrong input type or number is less than 1
    // prompts user to input another value
    public static double getWidth() {
        while (true) {
            System.out.println("Enter wall width (feet): ");
            String input = scnr.next();
            double width;
            try {
                width = Double.parseDouble(input);
                if ( width < 1.0 ) {
                    throw new Exception();
                }
                return width;
            } catch (Exception excpt) {
                System.out.println("Invalid Entry:  Input must be a number greater than 1");
                continue;
            }
        }
    }

    // Calculate the area needing painted
    public static double calculateArea(double height, double width) {
        double area = 0.0;
        area = height * width;
        return area;
    }

    // Calculate gallons needed to paint area
    public static double calculateGallons(double area, double feetPerGallon) {
        double gallonsNeeded = 0.0;
        gallonsNeeded = area / feetPerGallon;
        return gallonsNeeded;
    }
    // Calculates the number of cans needed by rounding up gallons needed 
    // to the nearest whole number  
    public static double calculateCans(double gallons) {
        double cansNeeded = 0.0;
        cansNeeded = Math.ceil(gallons);
        return cansNeeded;
    }

    // Main execution
    public static void main(String[] args) {
        final double squareFeetPerGallons = 350.0;
        double wallWidth = 0.0;
        double wallHeight = 0.0;
        double wallArea = 0.0;
        double gallonsPaintNeeded = 0.0;
        double cansPaintNeeded = 0.0;

        do {
            // Loop to detect valid input
            wallWidth = getWidth(); // Method to prompt user to enter wall width
            wallHeight = getHeight(); // Method to prompt user to enter wall height

            wallArea = calculateArea(wallHeight, wallWidth); // Method to calculate area
            System.out.println("Wall area: " + wallArea + " square feet"); // Print area needing printed

            gallonsPaintNeeded = calculateGallons(wallArea, squareFeetPerGallons); // Method to calculate gallons needed
            cansPaintNeeded = calculateCans(gallonsPaintNeeded); // Method to calculate the number of cans needed
            System.out.println("Paint needed: " + gallonsPaintNeeded + " gallons"); // Print gallons needed to paint
            System.out.println("Cans needed: " + cansPaintNeeded + " can(s)"); // Print gallons needed to paint
            break;
        } while (true);
    }
}
