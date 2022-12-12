package com.module.project3.Items;

/**
 * The type Item.
 */
public class Item {


    private int id;
    private String title;
    private String description;
    private byte[] image;
    private double price;
    private Integer quantity;
    private Boolean favorite;

    /**
     * Instantiates a new Item.
     *
     * @param title       the title
     * @param description the description
     * @param price       the price
     * @param quantity    the quantity
     * @param favorite    the favorite
     */
    public Item(String title, String description, double price, Integer quantity, Boolean favorite) {
        this.title = title;
        this.description = description;
        this.price = price;
        this.quantity = quantity;
        this.favorite = favorite;
    }

    /**
     * Instantiates a new Item.
     *
     * @param id          the id
     * @param title       the title
     * @param description the description
     * @param quantity    the quantity
     * @param price       the price
     * @param favorite    the favorite
     * @param image       the image
     */
    public Item(Integer id, String title, String description, Integer quantity, double price, boolean favorite, byte[] image) {
        this.id = id;
        this.title = title;
        this.description = description;
        this.price = price;
        this.quantity = quantity;
        this.favorite = favorite;
        this.image = image;
    }


    /**
     * Gets id.
     *
     * @return the id
     */
// Mutators and Accessors
    public int getId() {
        return id;
    }

    /**
     * Sets id.
     *
     * @param id the id
     */
    public void setId(int id) {
        this.id = id;
    }

    /**
     * Gets title.
     *
     * @return the title
     */
    public String getTitle() {
        return title;
    }

    /**
     * Sets title.
     *
     * @param title the title
     */
    public void setTitle( String title) {
        this.title = title;
    }

    /**
     * Gets description.
     *
     * @return the description
     */
    public String getDescription() {
        return description;
    }

    /**
     * Sets description.
     *
     * @param description the description
     */
    public void setDescription( String description) {
        this.description = description;
    }

    /**
     * Get image byte [ ].
     *
     * @return the byte [ ]
     */
    public byte[] getImage() {
        return image;
    }

    /**
     * Sets image.
     *
     * @param image the image
     */
    public void setImage(byte[] image) {
        this.image = image;
    }

    /**
     * Gets price.
     *
     * @return the price
     */
    public double getPrice() {
        return price;
    }

    /**
     * Sets price.
     *
     * @param price the price
     */
    public void setPrice(double price) {
        this.price = price;
    }

    /**
     * Gets quantity.
     *
     * @return the quantity
     */
    public Integer getQuantity() {
        return quantity;
    }

    /**
     * Sets quantity.
     *
     * @param quantity the quantity
     */
    public void setQuantity(Integer quantity) {
        this.quantity = quantity;
    }

    /**
     * Gets favorite.
     *
     * @return the favorite
     */
    public Boolean getFavorite() {
        return favorite;
    }

    /**
     * Sets favorite.
     *
     * @param favorite the favorite
     */
    public void setFavorite(Boolean favorite) {
        this.favorite = favorite;
    }

    /**
     * Gets item.
     *
     * @return the item
     */
    public Item getItem() {
        return this;
    }
}