/**
 * 
 */
/**
 * @author Eric Wallace
 *
 */

public class Pet {
		private int petType;
		private String petName;
		private int petAge;
		private int dogSpaces;
		private int catSpaces;
		private int daysStay;
		private double amountDue;
	
		public Pet(String name, int age, int type) {
			petName = name;
			petAge = age;
			petType = type;
		}
		
		private void setPetType(int value) {
		   this.petType = value;
		}
		
		private int getPetType() {
		   return this.petType;
		}
	
		private void setPetName(String value) {
		   this.petName = value;
		}
		
		private String getPetName() {
		   return this.petName;
		}
	
		private void setPetAge(int value) {
		   this.petAge = value;
		}
		
		private int getPetAge() {
		   return this.petAge;
		}
		
		private void setDogSpaces(int value) {
		   this.dogSpaces = value;
		}
		
		private int getDogSpaces() {
		   return this.dogSpaces;
		}
		
		private void setCatSpaces(int value) {
		   this.catSpaces = value;
		}
		
		private int getCatSpaces() {
		   return this.catSpaces;
		}
		
		private void setDaysStay(int value) {
		   this.daysStay = value;
		}
		
		private int getDaysStay() {
		   return this.daysStay;
		}
		
		
		
		private void setAmountDue(double value) {
		   this.amountDue = value;
		}
		
		private double getAmountDue() {
		   return this.amountDue;
		}
		

}
