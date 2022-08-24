/* SNHU IT-145-J2003 5-4 Milestone
 * Driver.java
 * Nov 24, 2021
 */

import java.util.ArrayList;
import java.util.Scanner;


public class Driver {

	// Used for obtaining user input
	private static Scanner scanner = new Scanner(System.in);

	// List used to hold information about the animal
	private static ArrayList<Dog> dogList = new ArrayList<Dog>();
	private static ArrayList<Monkey> monkeyList = new ArrayList<Monkey>();
	private static ArrayList<String> printList = new ArrayList<>();

	// Instance variables (if needed)

	public static void main(String[] args) {

		String menuOption = "";

		initializeDogList();
		initializeMonkeyList();
		
		
		// Loop displays the menu options 
		while ( !menuOption.equalsIgnoreCase("q")) {

			displayMenu();

			menuOption = scanner.nextLine();

			switch (menuOption) {
			case "1":
				intakeNewDog(scanner);
				break;
			case "2":
				intakeNewMonkey(scanner);
				break;
			case "3":
				reserveAnimal(scanner);
				break;
			case "4":
				printAnimals("Dog");
				break;
			case "5":
				printAnimals("Monkey");
				break;
			case "6":
				printAnimals("All");
				break;
			case "q":
				break;
			default:
				System.out.println("Invalid Option:  Please make a valid selection!!");
				displayMenu();
				break;
			} 
		}

	}
	// This method prints the menu options
	public static void displayMenu() {
		System.out.println("\n\n");
		System.out.println("\t\t\t\tRescue Animal System Menu");
		System.out.println("[1] Intake a new dog");
		System.out.println("[2] Intake a new monkey");
		System.out.println("[3] Reserve an animal");
		System.out.println("[4] Print a list of all dogs");
		System.out.println("[5] Print a list of all monkeys");
		System.out.println("[6] Print a list of all animals that are not reserved");
		System.out.println("[q] Quit application");
		System.out.println();
		System.out.println("Enter a menu selection");
	}

	// Adds dogs to a list for testing
	public static void initializeDogList() {
		Dog dog1 = new Dog("Spot", "German Shepherd", "male", "1", "25.6", "05-12-2019", "United States", "intake",
				false, "United States");
		Dog dog2 = new Dog("Rex", "Great Dane", "male", "3", "35.2", "02-03-2020", "United States", "Phase I", false,
				"United States");
		Dog dog3 = new Dog("Bella", "Chihuahua", "female", "4", "25.6", "12-12-2019", "Canada", "in-service", false,
				"Canada");

		dogList.add(dog1);
		dogList.add(dog2);
		dogList.add(dog3);
	}

	// Adds monkeys to a list for testing
	// Optional for testing
	public static void initializeMonkeyList() {
		Monkey monkey1 = new Monkey("Jack", "Guenon", "male", "2", "10.8", "27.8", "29.1", "24.6", "05-22-2017", "United States", "in-service",
				false, "United States");
		Monkey monkey2 = new Monkey("Lucy", "Capuchin", "female", "1", "9.6", "38.2", "21.3", "21.3", "04-012-2021", "Congo", "Phase III", false,
				"Congo");
		Monkey monkey3 = new Monkey("Jacy", "Marmoset", "female", "5", "0.6", "19.7", "8.32", "7.4", "11-12-2021", "Paraguay", "in-service", true,
				"Paraguay");


		monkeyList.add(monkey1);
		monkeyList.add(monkey2);
		monkeyList.add(monkey3);
	}

	// Dog intake method
	public static void intakeNewDog(Scanner scanner) {
		System.out.println("What is the dog's name?");
		String name = scanner.nextLine();
		for (Dog dog : dogList) {
			if (dog.getName().equalsIgnoreCase(name)) {
				System.out.println("\n\nThis dog is already in our system\n\n");
				return; // returns to menu
			}
		}

		System.out.println("What is the dog's breed?");
		String breed = scanner.nextLine();
		System.out.println("What is the dog's gender?");
		String gender = scanner.nextLine();
		System.out.println("What is the dog's age?");
		String age = scanner.nextLine();
		System.out.println("What is the dog's weight?");
		String weight = scanner.nextLine();
		System.out.println("What is the dog's acquisition date?");
		String acqDate = scanner.nextLine();
		System.out.println("What is the dog's location?");
		String acqLocation = scanner.nextLine();
		System.out.println("What is the dog's status?");
		String status = scanner.nextLine();

		Dog newDog = new Dog(name, breed, gender, age, weight, acqDate, acqLocation, status, false, acqLocation);

		dogList.add(newDog);
		System.out.println("Dog " + name + " has been added.");		
		return;

	}

	// Monkey intake method
	public static void intakeNewMonkey(Scanner scanner) {
		System.out.println("What is the monkey's name?");
		String name = scanner.nextLine();
		for (Monkey monkey : monkeyList) {
			if (monkey.getName().equalsIgnoreCase(name)) {
				System.out.println("\n\nThis monkey is already in our system\n\n");
				return; // returns to menu
			}
		}

		ArrayList<String> speciesList = Monkey.getSpeciesList();

		System.out.print("What is the monkey's species? ");
		System.out.println("Available species: " + speciesList);
		String species = scanner.nextLine();
		while(!speciesList.contains(species)) {
			System.out.println("Incorrect Entry: Please enter a correct species.");
			species = scanner.nextLine();
		}
		System.out.println("What is the monkey's gender?");
		String gender = scanner.nextLine();
		System.out.println("What is the monkey's age?");
		String age = scanner.nextLine();
		System.out.println("What is the monkey's weight?");
		String weight = scanner.nextLine();
		System.out.println("What is the monkey's tail length?");
		String tailLength = scanner.nextLine();
		System.out.println("What is the monkey's body length?");
		String bodyLength = scanner.nextLine();
		System.out.println("What is the monkey's height?");
		String height = scanner.nextLine();
		System.out.println("What is the monkey's acquisition date?");
		String acqDate = scanner.nextLine();
		System.out.println("What is the monkey's location?");
		String acqLocation = scanner.nextLine();
		System.out.println("What is the monkey's status?");
		String status = scanner.nextLine();

		Monkey newMonkey = new Monkey(name, species, gender, age, weight, tailLength, bodyLength, height, acqDate, acqLocation, status, false, acqLocation);

		monkeyList.add(newMonkey);
		System.out.println("Monkey " + name + " has been added.");
		return;

	}

	// Used to reserve an animal, takes type of animal
	// and the name of the animal
	public static void reserveAnimal(Scanner scanner) {
		System.out.println("What type of animal would you like to reserve?");		
		System.out.println("[1] Dog");
		System.out.println("[2] Monkey");
		String type = scanner.nextLine();

		if ( type.equals("1")) {
			System.out.println("What is the name of the dog you would like to reserve?");
			String name = scanner.nextLine();

			for (Dog dog : dogList) {
				if ( dog.getName().equals(name) ) {
					if ( dog.getReserved() == true) {
						System.out.println(name + " is already reserved.");
						return;
					}
					else {
						dog.setReserved(true);	
						System.out.println(name + " has been reserved.");
						return;
					}
				}
				else {
					System.out.println("Incorrect Entry: Name is not found is list");
					return;
				}
			}
		}
		else if (type.equals("2")) {
			System.out.println("What is the name of the monkey you would like to reserve?");
			String name = scanner.nextLine();
			for (Monkey monkey : monkeyList) {
				if ( monkey.getName().equals(name) ) {
					if ( monkey.getReserved() == true) {
						System.out.println(name + " is already reserved.");
						return;
					}
					else {
						monkey.setReserved(true);					
						System.out.println(name + " has been reserved.");
						return;
					}
				}
				else {
					System.out.println("Incorrect Entry: Name is not found is list");
					return;
				}
			}
		}
		else {
			System.out.println("Incorrect Entry:  Wrong type of animal entered");
			return;
		}

	}

	// Prints list of dog, monkey or all with status of in-service and not reserved
	public static void printAnimals(String type) {
		if (type.equals("Dog")) {
			if (dogList.size() == 0) {
				System.out.println("No dogs were found...");
				return;
			} 
			else {
				for (Dog dog : dogList) {
					System.out.println("Name: " + dog.getName() + " Status: " + dog.getTrainingStatus() + " Location: " + dog.getAcquisitionLocation() + " Reserved: " + dog.getReserved());
				}
				return;
			}
		}
		else if (type.equals("Monkey")) {
			if (monkeyList.size() == 0) {
				System.out.println("No monkeys were found...");
				return;
			}
			else {
				for (Monkey monkey : monkeyList) {
					System.out.println("Name: " + monkey.getName() + " Status: " + monkey.getTrainingStatus() + " Location: " + monkey.getAcquisitionLocation() + " Reserved: " + monkey.getReserved());
				}
				return;
			}
		}
		else if ( type.equals("All")) {
			for (Dog dog : dogList) {
				if (dog.getTrainingStatus().equals("in-service") && dog.getReserved() == false) {
					String list = "Animal Type: Dog Name: " + dog.getName() + " Location: " + dog.getAcquisitionLocation();
					printList.add(list);
					// System.out.println("Animal Type: Dog Name: " + dog.getName() + " Location: " + dog.getAcquisitionLocation());
				}
			}
			for (Monkey monkey : monkeyList) {
				if (monkey.getTrainingStatus().equals("in-service") && monkey.getReserved() == false) {
					String list = "Animal Type: Monkey Name: " + monkey.getName() + " Location: " + monkey.getAcquisitionLocation();
					printList.add(list);
					// System.out.println("Animal Type: Monkey Name: " + monkey.getName() + " Location: " + monkey.getAcquisitionLocation());
				}
			}
			if(printList.size() > 0) {
				for (String list : printList) {
					System.out.println(list);
				}
				return;
			}
			else {
				System.out.println("There are no animals in service and not reserved");
				return;
			}
		}

	}
}
