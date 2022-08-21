package com.gamingroom;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

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
	private static long nextGameId = 1;

	/*
	 * Create instance variable of GameService class.  The constructor
	 * is private therefore we will only need one instance of this object
	 */
	private static GameService instance = new GameService();

	/*
	 * Create private constructor of GameService class. It is a singleton of
	 * a constructor. So, we don't instantiate more instances outside of the
	 * GameService class
	 */
	private void GameService() {
	}

	/*
	 * Public accessor for the instance of the GameService class. This
	 * allows access to the GameService class from outside by other classes
	 */
	public static GameService getInstance() {
		return instance;
	}

	/**
	 * Construct a new game instance
	 * 
	 * @param name the unique name of the game
	 * @return the game instance (new or existing)
	 */
	public Game addGame(String name) {

		// a local game instance
		Game game = null;

		// Return existing instances if one exists, 
		// this does not add anything to the game data
		for (Game currentGame : games) {
			if (currentGame.getName().equals(name)) {
				return currentGame;
			}
		}
		
		// If game is not found create a new instance 
		// and add to the games list
		game = new Game(nextGameId++, name);
		games.add(game);

		// return the new/existing game instance to the caller
		return game;
	}

	/**
	 * Returns the game instance at the specified index.
	 * <p>
	 * Scope is package/local for testing purposes.
	 * </p>
	 * @param index index position in the list to return
	 * @return requested game instance
	 */
	Game getGame(int index) {
		return games.get(index);
	}

	/**
	 * Returns the game instance with the specified id.
	 *
	 * @param id unique identifier of game to search for
	 * @return requested game instance
	 */
	public Game getGame(long id) {

		// a local game instance
		Game game = null;

		// Iterate over the current list of games, game exists with the same id,
		// return the instance of that Game.  This ensures that only one instance
		// of
		for (Game currentGame : games) {
			if (currentGame.getId() == id) {
				game = currentGame;
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

		// a local game instance
		Game game = null;

		// Iterate over the current list of games, if
		// game exists with the same name,
		// return the instance of that Game
		for (Game currentGame : games) {
			if (currentGame.getName().equals(name)) {
				game = currentGame;
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
}
