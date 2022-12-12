package com.module.project3.User;

import static com.module.project3.Util.compareInput;
import static com.module.project3.Util.inputNull;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;

import com.module.project3.*;
import com.module.project3.db.UserDataManager;

/**
 * The type Register activity.
 */
public class RegisterActivity extends AppCompatActivity {

    /**
     * The Register.
     */
    Button register;
    /**
     * The First name text.
     */
    EditText firstNameText, /**
     * The Last name text.
     */
    lastNameText, /**
     * The Username text.
     */
    usernameText, /**
     * The Password text.
     */
    passwordText, /**
     * The Confirm password text.
     */
    confirmPasswordText, /**
     * The Email text.
     */
    emailText;
    /**
     * The Db helper.
     */
    UserDataManager dbHelper;


    /**
     * The Is validated.
     */
    Boolean isValidated = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        dbHelper = new UserDataManager(this);
        super.onCreate(savedInstanceState);
        setContentView(R.layout.view_register);
        firstNameText = findViewById(R.id.firstNameEdit);
        lastNameText = findViewById(R.id.lastNameEdit);
        usernameText = findViewById(R.id.usernameEdit);
        passwordText = findViewById(R.id.passwordEdit);
        confirmPasswordText = findViewById(R.id.confirmPasswordEdit);
        emailText = findViewById(R.id.emailAddressEdit);
        register = findViewById(R.id.itemSaveBtn);

        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbarMain);
        setSupportActionBar(toolbar);

        register.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String firstName = firstNameText.getText().toString();
                String lastName = lastNameText.getText().toString();
                String username = usernameText.getText().toString();
                String password = passwordText.getText().toString();
                String confirmPassword = confirmPasswordText.getText().toString();
                String email = emailText.getText().toString();

                if (inputNull(firstNameText)) {
                    firstNameText.setError("First name is required");
                    isValidated = false;
                } else {
                    isValidated = true;
                }
                if (inputNull(lastNameText)) {
                    lastNameText.setError("Last name is required");
                    isValidated = false;
                } else {
                    isValidated = true;
                }
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
                if (inputNull(confirmPasswordText)) {
                    confirmPasswordText.setError("Confirm password is required");
                    isValidated = false;
                } else {
                    isValidated = true;
                }
                if (inputNull(emailText)) {
                    emailText.setError("Email is required");
                    isValidated = false;
                } else {
                    isValidated = true;
                }
                if (isValidated) {
                    if (compareInput(password, confirmPassword)) {
                        try {
                            dbHelper.insert(firstName, lastName, email, username, password);
                            Toast.makeText(RegisterActivity.this, "User registered successfully", Toast.LENGTH_SHORT).show();
                            Intent intent = new Intent(getApplicationContext(), LoginActivity.class);
                            startActivity(intent);
                        } catch (Exception e) {
                            Toast.makeText(RegisterActivity.this, "User registration failed" + e, Toast.LENGTH_SHORT).show();
                        }
                    } else {
                        Toast.makeText(RegisterActivity.this, "Passwords do not match", Toast.LENGTH_SHORT).show();
                    }
                }
            }
        });
    };

    /**
     * Register.
     *
     * @param view the view
     */
    public void register(View view) {
        String firstName = firstNameText.getText().toString();
        String lastName = lastNameText.getText().toString();
        String username = usernameText.getText().toString();
        String password = passwordText.getText().toString();
        String confirmPassword = confirmPasswordText.getText().toString();
        String email = emailText.getText().toString();

        if (inputNull(firstNameText) || firstNameText.length() < 4) {
            firstNameText.setError("First name is required and must be at least 4 characters");
            isValidated = false;
        } else {
            isValidated = true;
        }
        if (inputNull(lastNameText) || lastNameText.length() < 5) {
            lastNameText.setError("Last name is required and must be at least 5 characters");
            isValidated = false;
        } else {
            isValidated = true;
        }
        if (inputNull(usernameText) || usernameText.length() < 5) {
            usernameText.setError("Username is required and must be at least 5 characters");
            isValidated = false;
        } else {
            isValidated = true;
        }
        if (inputNull(passwordText) || passwordText.length() < 8) {
            passwordText.setError("Password is required and must be at least 8 characters");
            isValidated = false;
        } else {
            isValidated = true;
        }
        if (!compareInput(password, confirmPassword)) {
            confirmPasswordText.setError("Passwords do not match");
            isValidated = false;
        } else {
            isValidated = true;
        }
        if (inputNull(emailText) || !emailText.getText().toString().contains("@") || !emailText.getText().toString().contains(".") || emailText.length() < 10) {
            emailText.setError("Email is required, must contain an @ symbol, a . symbol, and must be at least 10 characters");
            isValidated = false;
        } else {
            isValidated = true;
        }

        if (isValidated) {
            Boolean userCheckExist = dbHelper.checkUsername(username);
            if (!userCheckExist) {
                Toast.makeText(RegisterActivity.this, "User already exists", Toast.LENGTH_SHORT).show();
            } else {
                try {
                User user = new User(firstName, lastName, email, username, password);
                 dbHelper.insert(firstName, lastName, email, username, password);
                    Toast.makeText(RegisterActivity.this, "Registered successfully", Toast.LENGTH_SHORT).show();
                    Intent intent = new Intent(getApplicationContext(), LoginActivity.class);
                    startActivity(intent);
                } catch (Exception e) {
                    Toast.makeText(RegisterActivity.this, "Registration failed" + e, Toast.LENGTH_SHORT).show();
                }
            }
        } else {
            Toast.makeText(RegisterActivity.this, "Please fill out all fields", Toast.LENGTH_SHORT).show();
        }
    }
}