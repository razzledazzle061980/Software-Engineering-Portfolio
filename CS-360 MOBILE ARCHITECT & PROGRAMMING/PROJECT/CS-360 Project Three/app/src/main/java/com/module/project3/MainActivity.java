package com.module.project3;

import static android.Manifest.permission.READ_EXTERNAL_STORAGE;
import static android.Manifest.permission.SEND_SMS;
import static android.Manifest.permission.WRITE_EXTERNAL_STORAGE;


import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.util.Log;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import androidx.navigation.ui.AppBarConfiguration;

import com.module.project3.Items.ItemsActivity;
import com.module.project3.User.LoginActivity;
import com.module.project3.db.PersistedActivity;
import com.module.project3.db.UserDataManager;


/**
 * The type Main activity.
 */
public class MainActivity extends AppCompatActivity {
    /**
     * The Tag.
     */
    String TAG = "Permissions";
    private static final int READ_EXTERNAL_STORAGE_CODE = 101;
    private static final int WRITE_EXTERNAL_STORAGE_CODE = 201;
    private static final int SEND_SMS_CODE = 301;

    /**
     * The Show explanation.
     */
    protected Boolean showExplanation = false;
    /**
     * The Is read permission granted.
     */
    protected Boolean isReadPermissionGranted = false;

    /**
     * The Permissions.
     */
    String[] permissions = {READ_EXTERNAL_STORAGE, WRITE_EXTERNAL_STORAGE, SEND_SMS};

    /**
     * The Firstrun.
     */
    protected boolean firstrun = true;
    private AppBarConfiguration appBarConfiguration;
    private UserDataManager db;
    /**
     * The Is logged in.
     */
    protected Boolean isLoggedIn;
    /**
     * The Username.
     */
    protected String username = "";
    /**
     * The Intent.
     */
    protected Intent intent;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.view_login);

        // Check permissions
        setupPermissions(MainActivity.this);

        db = new UserDataManager(this);
        SharedPreferences mPrefs = getSharedPreferences(PersistedActivity.PREFS_NAME, Context.MODE_PRIVATE);
        SharedPreferences.Editor mEditor = mPrefs.edit();
        firstrun = mPrefs.getBoolean("firstrun", true);
        username = mPrefs.getString("username", "");
        if (firstrun) {
            mEditor.putBoolean("firstrun", false);
            mEditor.apply();
            intent = new Intent(getApplicationContext(), LoginActivity.class);
            startActivity(intent);
            return;
        }
        if (!db.checkUsername(username) || username.length() == 0) {
            Intent intent = new Intent(getApplicationContext(), LoginActivity.class);
            startActivity(intent);
        } else {
            isLoggedIn = db.isLoggedIn(username);
            if (isLoggedIn) {
                Intent intent = new Intent(getApplicationContext(), ItemsActivity.class);
                startActivity(intent);
                return;
            }
            Intent intent = new Intent(getApplicationContext(), LoginActivity.class);
            startActivity(intent);
        }
    }

    /**
     * Sets permissions.
     *
     * @param context the context
     */
    public void setupPermissions(Context context) {
        int readCheck = ContextCompat.checkSelfPermission(context, READ_EXTERNAL_STORAGE);
        int writeCheck = ContextCompat.checkSelfPermission(context, WRITE_EXTERNAL_STORAGE);
        int smsCheck = ContextCompat.checkSelfPermission(context, SEND_SMS);

        if (readCheck != PackageManager.PERMISSION_GRANTED || writeCheck != PackageManager.PERMISSION_GRANTED || smsCheck != PackageManager.PERMISSION_GRANTED) {
            Log.e(TAG, "Permission to feature denied");
            if (ActivityCompat.shouldShowRequestPermissionRationale((Activity) context, READ_EXTERNAL_STORAGE) || ActivityCompat.shouldShowRequestPermissionRationale((Activity) context, WRITE_EXTERNAL_STORAGE) || ActivityCompat.shouldShowRequestPermissionRationale((Activity) context, SEND_SMS)) {
                Log.e(TAG, "Should show dialog");
                AlertDialog.Builder builder = new AlertDialog.Builder(context);
                builder.setView(R.layout.dialog_permissions);
                builder.create().show();
            } else {
                writeRequest();
            }
        }
    }

    /**
     * Write request.
     */
    protected void writeRequest() {
        Log.i(TAG, "Requesting permission");
        ActivityCompat.requestPermissions(this, new String[] {READ_EXTERNAL_STORAGE}, 200);
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);

        switch (requestCode) {
            case READ_EXTERNAL_STORAGE_CODE: {
                if (grantResults.length == 0 || grantResults[0] != PackageManager.PERMISSION_GRANTED) {
                    Log.i(TAG, "Permission read external storage has been denied by user");
                } else {
                    Log.i(TAG, "Permission read external storage has been granted by user");
                }
            }
            case WRITE_EXTERNAL_STORAGE_CODE: {
                if (grantResults.length == 0 || grantResults[0] != PackageManager.PERMISSION_GRANTED) {
                    Log.i(TAG, "Permission write external storage has been denied by user");
                } else {
                    Log.i(TAG, "Permission write external storage has been granted by user");
                }
            }
            case SEND_SMS_CODE: {
                if (grantResults.length == 0 || grantResults[0] != PackageManager.PERMISSION_GRANTED) {
                    Log.i(TAG, "Permission write external storage has been denied by user");
                } else {
                    Log.i(TAG, "Permission write external storage has been granted by user");
                }
            }
        }
    }

}