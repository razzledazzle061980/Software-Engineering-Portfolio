package com.gamingroom;

public class Entity {

    // Private attributes
    private long id;
    private String name;

    /*
     * Create private constructor of Entity class. It is a singleton to have
     *  a constructor. So, we don't instantiate more instances outside the
     *  Entity class
     */
    private Entity() {
    }

    /*
     * Constructor with identifier and name
     */
    public Entity(long id, String name) {
        this();
        this.id = id;
        this.name = name;
    }

    // Public accessor of id
    public long getId() {
        return this.id;
    }

    // Public accessor of name
    public String getName() {
        return this.name;
    }

    // Used to convert information into a string
    public String toString() {
        return "Entity[id=" + id + ", name=" + name + "]";
    }
}
