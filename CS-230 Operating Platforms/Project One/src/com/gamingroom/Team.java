package com.gamingroom;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * A simple class to hold information about a team
 * <p>
 * Notice the overloaded constructor that requires
 * an id and name to be passed when creating.
 * Also note that no mutators (setters) defined so
 * these values cannot be changed once a team is
 * created.
 * </p>
 * @author coce@snhu.edu
 *
 */
public class Team extends Entity {

	/**
	 * List of all Players on Team
	 */
	private List<Player> players = new ArrayList<Player>();

	/*
	 * Constructor with an identifier and name
	 */
	public Team(long id, String name) { super(id, name); }

	/**
	 * Add a player if one does not exist, if the current player
	 * exits, return that players
	 *
	 * @param name
	 * @return Player instance
	 */
	public Player addPlayer(String name) {

		// Create local variable player of type Player that is null
		Player player = null;

		// Create iterator of the Player instance
		Iterator<Player> playersIterator = players.iterator();

		// Iterates over the player list to find
		// a player with the same name
		while(playersIterator.hasNext()) {
			// Sets a local team variable to the next item in the list
			Player playerInstance = playersIterator.next();

			// Checks if the current playerInstance equals
			// the player name passed into the method
			if (playerInstance.getName().equalsIgnoreCase(name)) {
				player = playerInstance;
			} else {
				players.add(player);
			}
		}
		return player;

	}


	@Override
	public String toString() {
		return "Team [id=" + super.getId() + ", name=" + super.getName() + "]";
	}
}
