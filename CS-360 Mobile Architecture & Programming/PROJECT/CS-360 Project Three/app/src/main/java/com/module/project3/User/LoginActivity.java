package com.module.project3.User;

import static com.module.project3.Util.*;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.module.project3.Items.ItemsActivity;
import com.module.project3.*;
import com.module.project3.db.PersistedActivity;
import com.module.project3.db.UserDataManager;

/**
 * The type Login activity.
 */
public class LoginActivity extends AppCompatActivity {

    /**
     * The Username text.
     */
    EditText usernameText, /**
     * The Password text.
     */
    passwordText;
    /**
     * The Login btn.
     */
    Button loginBtn, /**
     * The Register btn.
     */
    registerBtn;
    /**
     * The User data manager.
     */
    UserDataManager userDataManager;
    /**
     * The Is validated.
     */
    Boolean isValidated;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.view_login);

        usernameText = findViewById(R.id.usernameEdit);
        passwordText = findViewById(R.id.loginPasswordText);
        loginBtn = findViewById(R.id.loginLoginBtn);
        registerBtn = findViewById(R.id.loginRegisterBtn);

        UserDataManager userDataManager = new UserDataManager(this);
        registerBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(getApplicationContext(), RegisterActivity.class);
                startActivity(intent);
            }
        });

        loginBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String username = usernameText.getText().toString();
                String password = passwordText.getText().toString();

                if (inputNull(usernameText)) {
                    usernameText.setError("Username is required");
                    isValidated = false;
                } else {
                    isValidated = true;
                }
                if (inputNull(passwordText)) {
                    passwordText.setError("Password is required");
                    isValidated = false;
                } else {
                    isValidated = true;
                }

                if (isValidated) {
                   boolean isAuth = userDataManager.authenticate(username, password);
                     if (isAuth) {
                         Log.d("username", username);
                         SharedPreferences mPrefs = getSharedPreferences(PersistedActivity.PREFS_NAME, Context.MODE_PRIVATE);
                         SharedPreferences.Editor mEditor = mPrefs.edit();
                         mEditor.putString("username", username).apply();
                          Intent intent = new Intent(getApplicationContext(), ItemsActivity.class);
                          startActivity(intent);
                    } else {
                        Toast.makeText(getApplicationContext(), "Invalid username or password", Toast.LENGTH_SHORT).show();
                    }
                }

            }
        });
    }
}
