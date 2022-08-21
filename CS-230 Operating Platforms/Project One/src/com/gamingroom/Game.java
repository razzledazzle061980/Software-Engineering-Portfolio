package com.gamingroom;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * A simple class to hold information about a game
 * 
 * <p>
 * Notice the overloaded constructor that requires
 * an id and name to be passed when creating.
 * Also note that no mutators (setters) defined so
 * these values cannot be changed once a game is
 * created.
 * </p>
 * 
 * @author coce@snhu.edu
 *
 */
public class Game extends Entity {

	/**
	 * List of all active teams
	 */
	private List<Team> teams = new ArrayList<Team>();

	/**
	 * Constructor with an identifier and name
	 */
	public Game(long id, String name) {
		super(id, name);
	}

	/**
	 * Add a team if one does not exist, if
	 * the current team exists, return that team
	 *
	 * @param name
	 * @return Team instance
	 */
	public Team addTeam(String name) {

		// Create local variable game of type game that is null
		Team team = null;

		// Create iterator of the Team instance
		Iterator<Team> teamsIterator = teams.iterator();

		// Iterates over the team list to find
		// a team with the same name
		while (teamsIterator.hasNext()){
			// Sets a local team variable to the next item in the list
			Team teamInstance = teamsIterator.next();
			// Checks if the current teamInstance equals
			// the team name passed into the method
			if (teamInstance.getName().equalsIgnoreCase(name)) {
				// If team exists, return the current teamInstance of team
				team = teamInstance;
			} else {
				teams.add(team);
			}
		}
		return team;
	}


	@Override
	public String toString() {
		
		return "Game [id=" + super.getId() + ", name=" + super.getName() + "]";
	}

}
