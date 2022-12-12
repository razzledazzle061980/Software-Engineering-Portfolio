package com.module.project3.db;

import android.content.Context;
import android.database.Cursor;
import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Log;

import com.google.android.material.snackbar.Snackbar;

import java.time.LocalDateTime;

/**
 * The type User data manager.
 */
public class UserDataManager {

    // This is the database
    private SQLiteDatabase db;

    /**
     * The constant DB_NAME.
     */
// Database name and table name
    protected static final String DB_NAME = "users.db";
    /**
     * The constant DB_TABLE.
     */
    protected static final String DB_TABLE = "users";
    /**
     * The constant DB_VERSION.
     */
    protected static final int DB_VERSION = 3;
    /**
     * The constant COLS.
     */
    protected static final String[] COLS = new String[]{"firstName", "lastName", "password", "email", "username", "image"};

    /**
     * Instantiates a new User data manager.
     *
     * @param context the context
     */
// Constructor that creates a new database
    public UserDataManager(Context context) {
        CustomSQLiteOpenHelper dbHelper = new CustomSQLiteOpenHelper(context);
        db = dbHelper.getWritableDatabase();
        db.execSQL("CREATE TABLE IF NOT EXISTS " + DB_TABLE + " (id INTEGER PRIMARY KEY AUTOINCREMENT, firstName TEXT, lastName TEXT, password TEXT, email TEXT, username TEXT, image BLOB, lastLogin INTEGER);");
    }

    /**
     * Insert.
     *
     * @param firstName the first name
     * @param lastName  the last name
     * @param email     the email
     * @param username  the username
     * @param password  the password
     */
// Insert method to add new record to database table
    public void insert(String firstName, String lastName, String email, String username, String password) {
        String query = "INSERT INTO users (firstName, lastName, email, username, password, image) VALUES ('" + firstName + "', '" + lastName + "', '" + email + "', '" + username + "', '" + password + "', '" + null +"')";
        try {
            db.execSQL(query);
        } catch (SQLException e) {
            Log.e("ProviderWidgets", "Exception creating table", e);
        }
    }

    /**
     * Delete.
     *
     * @param username the username
     */
// Delete a record
    public void delete(String username) {
        String query = "DELETE FROM users WHERE username = '" + username + "'";
        try {
            db.execSQL(query);
        } catch (SQLException e) {
            Log.e("ProviderWidgets", "Exception creating table", e);
        }
    }

    /**
     * Update.
     *
     * @param firstName the first name
     * @param lastName  the last name
     * @param email     the email
     * @param password  the password
     * @param username  the username
     */
// Update a record
    public void update(String firstName, String lastName, String email, String password, String username) {
        String query = "UPDATE users SET firstName = '" + firstName + "', lastName = '" + lastName + "', email = '" + email + "', password = '" + password + "' WHERE username = '" + username + "'";
        try {
            db.execSQL(query);
        } catch (SQLException e) {
            Log.e("ProviderWidgets", "Exception creating table", e);
        }
    }

    /**
     * Select all cursor.
     *
     * @return the cursor
     */
// Select All records
    public Cursor selectAll() {
        try {
            Cursor c = db.rawQuery("SELECT * FROM " + DB_TABLE, null);
            return c;
        } catch (SQLException e) {
            Log.e("ProviderWidgets", "Exception creating table", e);
        }
        return null;
    }

    /**
     * Search cursor.
     *
     * @param searchPhrase the search phrase
     * @return the cursor
     */
// Find a record
    public Cursor search(String searchPhrase) {
        try {
            Cursor c = db.rawQuery("SELECT * FROM " + DB_TABLE + " WHERE username = '" + searchPhrase + "'", null);
            return c;
        } catch (SQLException e) {
            Log.e("ProviderWidgets", "Exception creating table", e);
        }
        return null;
    }


    private static class CustomSQLiteOpenHelper extends SQLiteOpenHelper {
        /**
         * Instantiates a new Custom sq lite open helper.
         *
         * @param context the context
         */
        public CustomSQLiteOpenHelper(Context context) {
            super(context, DB_NAME, null, DB_VERSION);
        }

        @Override
        public void onCreate(SQLiteDatabase db) {
            String queryString = "CREATE TABLE " + DB_TABLE + " (_id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,firstName TEXT NOT NULL, lastName TEXT NOT NULL, email Email NOT NULL, password TEXT NOT NULL, username TEXT NOT NULL, image BLOB, lastLogin INTEGER)";
            try {
                db.execSQL(queryString);
            } catch (SQLException e) {
                Log.e("ProviderWidgets", "Exception creating table", e);
            }
        }

        @Override
        public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
            db.execSQL("DROP TABLE IF EXISTS users");
            onCreate(db);
        }
    }

    private void updateLastLogin(String username) {
        LocalDateTime now = LocalDateTime.now();
        String query = "UPDATE users SET lastLogin = '" + now + "' WHERE username = '" + username + "'";
        try {
            Log.i("Update() = ", query);
            db.execSQL(query);
        } catch (SQLException e) {
            Log.e("ProviderWidgets", "Exception creating table", e);
        }
    }

    /**
     * Is logged in boolean.
     *
     * @param username the username
     * @return the boolean
     */
    public Boolean isLoggedIn(String username) {
        try {
            Cursor c = db.rawQuery("SELECT lastLogin FROM " + DB_TABLE + " WHERE username = '" + username + "'", null);
            if (c != null && c.moveToFirst()) {
                LocalDateTime now = LocalDateTime.now();

                LocalDateTime lastLogin = LocalDateTime.parse(c.getString(0)).plusMinutes(30);
                return lastLogin.isAfter(now);
            }
        } catch (SQLException e) {
            Log.e("ProviderWidgets", "Exception creating table", e);
        }
        return null;
    }

    /**
     * Authenticate boolean.
     *
     * @param username the username
     * @param password the password
     * @return the boolean
     */
    public Boolean authenticate(String username, String password) {
        String query = "SELECT * FROM users WHERE username = '" + username + "' AND password = '" + password + "'";
        Cursor cursor = db.rawQuery(query, null);
        if (cursor != null) {
            updateLastLogin(username);
            return true;
        }
        return false;
    }

    /**
     * Check username boolean.
     *
     * @param username the username
     * @return the boolean
     */
    public Boolean checkUsername(String username) {
        String query = "SELECT * FROM users WHERE username = '" + username + "'";
        Cursor cursor = db.rawQuery(query, null);
        if (cursor.getCount() > 0) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * Insert image.
     *
     * @param imageBytes the image bytes
     * @param username   the username
     */
    public void insertImage(byte[] imageBytes, String username) {
        String query = "UPDATE users SET image = '" + imageBytes + "' WHERE username = '" + username + "'";
        try {
            db.execSQL(query);
        } catch (SQLException e) {
            Log.e("ProviderWidgets", "Exception creating table", e);
        }
    }

    /**
     * Get image byte [ ].
     *
     * @param username the username
     * @return the byte [ ]
     */
    public byte[] getImage(String username) {
        try {
            Cursor c = db.rawQuery("SELECT image FROM " + DB_TABLE + " WHERE username = '" + username + "'", null);
            if (c != null && c.moveToFirst()) {
                return c.getBlob(0);
            }
        } catch (SQLException e) {
            Log.e("ProviderWidgets", "Exception creating table", e);
        }
        return null;
    }
}
