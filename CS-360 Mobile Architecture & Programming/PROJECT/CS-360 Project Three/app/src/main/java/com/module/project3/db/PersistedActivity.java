package com.module.project3.db;

import android.content.SharedPreferences;
import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;

/**
 * The type Persisted activity.
 */
public  class PersistedActivity extends AppCompatActivity{

    /**
     * The constant PREFS_NAME.
     */
    public static final String PREFS_NAME = "Inventory App";
    /**
     * The M editor.
     */
    public SharedPreferences.Editor mEditor;
    /**
     * The M prefs.
     */
    public SharedPreferences mPrefs;

    
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mPrefs = getSharedPreferences(PREFS_NAME, 0);
         mEditor = mPrefs.edit();
    }

    /**
     * Gets pref string.
     *
     * @param key      the key
     * @param defValue the def value
     * @return the pref string
     */
    public String getPrefString(String key, String defValue) {
        return mPrefs.getString(key, defValue);
    }

    /**
     * Gets pref int.
     *
     * @param key      the key
     * @param defValue the def value
     * @return the pref int
     */
    public Integer getPrefInt(String key, Integer defValue) {
        return mPrefs.getInt(key, defValue);
    }

    /**
     * Gets pref boolean.
     *
     * @param key      the key
     * @param defValue the def value
     * @return the pref boolean
     */
    public Boolean getPrefBoolean(String key, Boolean defValue) {
        return mPrefs.getBoolean(key, defValue);
    }

    /**
     * Sets string.
     *
     * @param key   the key
     * @param value the value
     */
    public void setString(String key, String value) {
        SharedPreferences.Editor mEditor = mPrefs.edit();
        mEditor.putString(key, value);
        mEditor.commit();
    }

    /**
     * Sets int.
     *
     * @param key   the key
     * @param value the value
     */
    public void setInt(String key, Integer value) {
        SharedPreferences.Editor mEditor = mPrefs.edit();
        mEditor.putInt(key, value);
        mEditor.commit();
    }

}
