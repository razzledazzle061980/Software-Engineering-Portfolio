package com.module.project3.db;

import android.content.Context;
import android.database.Cursor;
import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Log;

/**
 * The type Item data manager.
 */
public class ItemDataManager {
    // This is the database
    private SQLiteDatabase db;
    /**
     * The constant DB_NAME.
     */
// Database name and table name
    protected static final String DB_NAME = "items.db";
    /**
     * The constant DB_TABLE.
     */
    protected static final String DB_TABLE = "items";
    /**
     * The constant DB_VERSION.
     */
    protected static final int DB_VERSION = 3;

    /**
     * Instantiates a new Item data manager.
     *
     * @param context the context
     */
    public ItemDataManager(Context context) {
        CustomSQLiteOpenHelper dbHelper = new CustomSQLiteOpenHelper(context);
        db = dbHelper.getWritableDatabase();
    }

    /**
     * Insert.
     *
     * @param title       the title
     * @param description the description
     * @param quantity    the quantity
     * @param price       the price
     * @param favorite    the favorite
     */
    public void insert(String title, String description, int quantity, double price, boolean favorite) {
        String query = "INSERT INTO items (title, description, quantity, price, favorite) VALUES ('" + title + "', '" + description + "', '" + quantity + "', '" + price + "', '" + favorite + "')";
        try {
            Log.i("Insert() = ", query);
            db.execSQL(query);
        } catch (SQLException e) {
            Log.e("ProviderWidgets", "Exception creating table", e);
        }
    }

    /**
     * Delete.
     *
     * @param id the id
     */
// Delete a record
    public void delete(int id) {
        String query = "DELETE FROM " + DB_TABLE + " WHERE _id = '" + id + "'";
        try {
            Log.i("Delete() = ", query);
            db.execSQL(query);
        } catch (SQLException e) {
            Log.e("ProviderWidgets", "Exception creating table", e);
        }
    }


    /**
     * Update.
     *
     * @param id          the id
     * @param title       the title
     * @param description the description
     * @param quantity    the quantity
     * @param price       the price
     * @param favorite    the favorite
     */
// Insert method to add new record to database table
    public void update(Integer id, String title, String description, int quantity, double price, boolean favorite) {
        String query = "UPDATE " + DB_TABLE  + " SET title = '" + title + "', description = '" + description + "', price = '" + price + "', quantity = '" + quantity + "' WHERE _id = '" + id + "'";
        try {
            Log.i("Update() = ", query);
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
        String query = "SELECT * FROM " + DB_TABLE;
        try {
            Log.i("SelectAll() = ", query);
            Cursor c = db.rawQuery(query, null);
            return c;

        } catch (SQLException e) {
            Log.e("ProviderWidgets", "Exception creating table", e);
        }
        return null;
    }

    /**
     * Search cursor.
     *
     * @param id the id
     * @return the cursor
     */
// Find a record
    public Cursor search(int id) {
        try {
            Cursor c = db.rawQuery("SELECT * FROM " + DB_TABLE + " WHERE _id = '" + id + "'", null);
            return c;
        } catch (SQLException e) {
            Log.e("ProviderWidgets", "Exception creating table", e);
        }
        return null;
    }

    // Setup database connector
    private static class CustomSQLiteOpenHelper extends SQLiteOpenHelper {
        /**
         * Instantiates a new Custom sq lite open helper.
         *
         * @param context the context
         */
        public CustomSQLiteOpenHelper(Context context) {
            super(context, DB_NAME, null, DB_VERSION);
        }

        // Instantiate database table
        @Override
        public void onCreate(SQLiteDatabase db) {
            String queryString = "CREATE TABLE " + DB_TABLE + " (_id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,title TEXT NOT NULL, description TEXT NOT NULL, quantity INTEGER NOT NULL, price DOUBLE NOT NULL, favorite BOOLEAN NOT NULL, image BLOB)";
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
}
