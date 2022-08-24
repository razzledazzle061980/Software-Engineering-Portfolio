/* SNHU IT-145-J2003 5-4 Milestone
 * Monkey.java
 * Nov 24, 2021
 */

import java.util.ArrayList;
import java.util.Arrays;

// Monkey class extends RescueAnimal
public class Monkey extends RescueAnimal {
	// Monkey class attributes
	private String tailLength;
	private String bodyLength;
	private String height;
	private String species;
	private static ArrayList<String> speciesList = new ArrayList<String>(Arrays.asList("Capuchin", "Guenon", "Macaque", "Marmoset", "Squirrel monkey", "Tamarin"));

	// speciesList Mutator Method
	public static ArrayList<String> getSpeciesList() {
		return speciesList;
	}
	
	// Method accepts a species and then 
	public static boolean findSpecies(String species) {
		boolean ans = speciesList.contains(species);
		
		return ans;
	}
	
	// tailLength Mutator Method
public String getTailLength() {
		return tailLength;
	}

	// tailLength Accessor Method
public void setTailLength(String tailLength) {
		this.tailLength = tailLength;
	}

	// bodyLength Mutator Method
public String getBodyLength() {
		return bodyLength;
	}

	// bodyLength Accessor Method
public void setBodyLength(String bodyLength) {
		this.bodyLength = bodyLength;
	}

	// height Mutator Method
public String getHeight() {
		return height;
	}

	// height Accessor Method
public void setHeight(String height) {
		this.height = height;
	}

	// species Mutator Method
public String getSpecies() {
		return species;
	}

	// species Accessor Method
public void setSpecies(String species) {
		this.species = species;
	}

	
	// Monkey class default constructor
	public Monkey(String tailLength, String bodyLength, String height, String species) {
		super();
		setTailLength(this.tailLength);
		setBodyLength(this.bodyLength);
		setHeight(this.height);
		setSpecies(this.species);
	}

	// Monkey Class constructor that sets
	//  values for all inherited attributes
	public Monkey(String name, String species, String gender, String age, String weight,  
	String tailLength, String bodyLength, String height,  
	String acquisitionDate, String acquisitionCountry, String trainingStatus, 
	boolean reserved, String inServiceCountry) {
		setName(name);
		setSpecies(species);
		setAge(age);
		setGender(gender);
		setWeight(weight);
		setTailLength(tailLength);
		setBodyLength(bodyLength);
		setHeight(height);
		setAcquisitionDate(acquisitionDate);
		setAcquisitionLocation(acquisitionCountry);
		setTrainingStatus(trainingStatus);
		setReserved(reserved);
		setInServiceCountry(inServiceCountry);
	}

	public Object getMonkey() {
		String name = getName();
		String status = getTrainingStatus();
		String country = getAcquisitionLocation();
		boolean reserved = getReserved();
		
		Object [] list = {name, status, country, reserved};
		
		return list;
	}

}
