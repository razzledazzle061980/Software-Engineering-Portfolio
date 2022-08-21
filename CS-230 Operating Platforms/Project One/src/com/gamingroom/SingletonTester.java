package com.gamingroom;

/**
 * A class to test a singleton's behavior
 * 
 * @author coce@snhu.edu
 */
public class SingletonTester {

	public void testSingleton() {
		
		System.out.println("\nAbout to test the singleton...");

		// Reference the instance of the GameService class
		GameService instance = GameService.getInstance(); // replace null with ???
		
		// a simple for loop to print the games
		for (int i = 0; i < instance.getGameCount(); i++) {
			System.out.println(instance.getGame(i));

		}

	}
	
}
