package com.gamingroom;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * A singleton service for the game engine
 * 
 * @author coce@snhu.edu
 */
public class GameService {

	/**
	 * A list of the active games
	 */
	private static List<Game> games = new ArrayList<Game>();

	/*
	 * Holds the next game identifier
	 */
	private static long nextGameId = 0;

	/*
	 * Holds the next team identifier
	 */
	private static long nextTeamId = 1;

	/*
	 * Holds the next player identifier
	 */
	private static long nextPlayerId = 1;

	/**
	 *  Create private variable service with type of GameService
	 */
	private static GameService instance;

	/*
	 * Create private constructor of GameService class. It is a singleton to have
	 *  a constructor. So, we don't instantiate more instances outside the
	 *  GameService class
	 */
	private GameService() {
	}

	 /**
	 * Public accessor for the instance of the GameService class. This
	 * allows access to the GameService class from outside by other classes
	 *
	 * @return
	 */
	public static GameService getInstance() {
		// Check if service exists
		if (instance == null) {
			instance = new GameService();

			System.out.println("New Game Service created");
		} else {
			System.out.println("Game Service already instantiated");
		}

		return instance;
	}

	/***************************************************************************
 	* GAMES SECTION
    ****************************************************************************

	/**
	 * Construct a new game instance
	 * 
	 * @param name the unique name of the game
	 * @return the game instance (new or existing)
	 */
	public Game addGame(String name) {

		// Create local variable game of type game that is null
		Game game = null;

		// Create iterator of the Game instance
		Iterator<Game> gamesIterator = games.iterator();

		// Iterates over the games list to find
		// a player with the same name
		while(gamesIterator.hasNext()) {
			// Sets a local game variable to the next game in the list
			Game gameInstance = gamesIterator.next();

			// Checks if the current gameInstance equals
			// the game passed into the method
			if (gameInstance.getName().equalsIgnoreCase(name)) {
				// If game exists, return game
				game = gameInstance;
			}
		}
		game = new Game(nextGameId++, name);
		games.add(game);
		// Return the new/existing game instance to the caller
		return game;
	}

	/**
	 * Returns the game instance with the specified id.
	 * 
	 * @param id unique identifier of game to search for
	 * @return requested game instance
	 */
	public Game getGame(long id) {

		// Create local variable game of type game that is null
		Game game = null;

		// Create iterator of the Game instance
		Iterator<Game> gamesIterator = games.iterator();

		// Iterates over the games list to find
		// a player with the same name
		while(gamesIterator.hasNext()) {
			// Sets a local game variable to the next game in the list
			Game gameInstance = gamesIterator.next();

			// Checks if the current gameInstance equals
			// the game passed into the method
			if (gameInstance.getId() == id) {
				// If game exists, return game
				return gameInstance;
			}
		}
		return game;
	}

	/**
	 * Returns the game instance with the specified name.
	 * 
	 * @param name unique name of game to search for
	 * @return requested game instance
	 */
	public Game getGame(String name) {

		// Create local variable game of type game that is null
		Game game = null;

		// Create iterator of the Game instance
		Iterator<Game> gamesIterator = games.iterator();

		// Iterates over the games list to find
		// a player with the same name
		while(gamesIterator.hasNext()) {
			// Sets a local game variable to the next game in the list
			Game gameInstance = gamesIterator.next();

			// Checks if the current gameInstance equals
			// the game passed into the method
			if (gameInstance.getName().equalsIgnoreCase(name)) {
				// If game exists, return game
				game = gameInstance;
			}
		}
		return game;
	}

	/**
	 * Returns the number of games currently active
	 * 
	 * @return the number of games currently active
	 */
	public int getGameCount() {
		return games.size();
	}

/***************************************************************************
* PLAYER SECTION
****************************************************************************

	* Returns the player whose turn is next
	*
	* @return next player
	*/
	public long getNextPlayerId() {
		return nextPlayerId;
	}


/***************************************************************************
 * TEAM SECTION
 ****************************************************************************

	 * Returns the team whose turn is next
	 *
	 * @return next team
	 */
	public long getNextTeamId() {
		return nextTeamId;
	}

}
