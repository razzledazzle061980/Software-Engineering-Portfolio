package com.module.project3.User;

import androidx.annotation.NonNull;
import androidx.room.Ignore;

import java.sql.Blob;

/**
 * The type User.
 */
public class User {

    private static int id;
    private String firstName;
    private String lastName;
    private String email;
    private String password;
    private String username;
    private Blob image;

    /**
     * Instantiates a new User.
     *
     * @param firstName the first name
     * @param lastName  the last name
     * @param email     the email
     * @param username  the username
     * @param password  the password
     */
    public User( String firstName, String lastName, String email, String username, String password) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.email = email;
        this.password = password;
        this.username = username;
    }

    /**
     * Instantiates a new User.
     *
     * @param id        the id
     * @param firstName the first name
     * @param lastName  the last name
     * @param email     the email
     * @param username  the username
     * @param image     the image
     */
    public User(Integer id, String firstName, String lastName, String email, String username, Blob image) {
        User.id = id;
        this.firstName = firstName;
        this.lastName = lastName;
        this.email = email;
        this.username = username;
        this.image = image;
    }

    /**
     * Instantiates a new User.
     */
    @Ignore
    public User(){
        username = null;
    }

    /**
     * Gets id.
     *
     * @return the id
     */
// Mutators and Accessors
    public static int getId() {
        return id;
    }

    /**
     * Sets id.
     *
     * @param id the id
     */
    public void setId(int id) {
        User.id = id;
    }

    /**
     * Gets first name.
     *
     * @return the first name
     */
    @NonNull
    public String getFirstName() {
        return firstName;
    }

    /**
     * Sets first name.
     *
     * @param firstName the first name
     */
    public void setFirstName(@NonNull String firstName) {
        this.firstName = firstName;
    }

    /**
     * Gets last name.
     *
     * @return the last name
     */
    @NonNull
    public String getLastName() {
        return lastName;
    }

    /**
     * Sets last name.
     *
     * @param lastName the last name
     */
    public void setLastName(@NonNull String lastName) {
        this.lastName = lastName;
    }

    /**
     * Gets email.
     *
     * @return the email
     */
    @NonNull
    public String getEmail() {
        return email;
    }

    /**
     * Sets email.
     *
     * @param email the email
     */
    public void setEmail(@NonNull String email) {
        this.email = email;
    }

    /**
     * Gets password.
     *
     * @return the password
     */
    @NonNull
    public String getPassword() {
        return password;
    }

    /**
     * Sets password.
     *
     * @param password the password
     */
    public void setPassword(@NonNull String password) {
        this.password = password;
    }

    /**
     * Gets username.
     *
     * @return the username
     */
    @NonNull
    public String getUsername() {
        return username;
    }

    /**
     * Sets username.
     *
     * @param username the username
     */
    public void setUsername(@NonNull String username) {
        this.username = username;
    }

    /**
     * Gets image.
     *
     * @return the image
     */
    public Blob getImage() {
        return image;
    }

    /**
     * Sets image.
     *
     * @param image the image
     */
    public void setImage(Blob image) {
        this.image = image;
    }

}
