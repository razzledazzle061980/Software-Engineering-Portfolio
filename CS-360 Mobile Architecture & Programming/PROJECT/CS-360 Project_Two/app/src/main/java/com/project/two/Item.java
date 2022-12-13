package com.project.two;

import android.nfc.tech.NfcBarcode;

import java.util.ArrayList;
import java.util.Random;
import java.util.UUID;

public class Item {
    private final String itemID;
    private String title;
    private String description;
    private String image;
    private Float rating;
    private Integer onHand;
    private NfcBarcode barcode;
    private Boolean isActive;
    private Boolean isFavorite;

    protected static ArrayList<Item> items = new ArrayList<Item>();;

    private synchronized static String generateItemID() {
        byte[] bytes = new byte[16];
        new Random().nextBytes(bytes);
        return new UUID(bytes[0], bytes[1]).toString();
    }

    public Item( String title, String description, String image, Integer onHand, Boolean isFav, Float rating) {
        this.itemID = generateItemID();
        this.title = title;
        this.description = description;
        this.image = image;
        this.rating = rating;
        this.isFavorite = isFav;
        this.onHand = onHand;
        this.isActive = true;
    }

    public Item(String title, String description, String image, Integer onHand, NfcBarcode barcode) {
        this.itemID = generateItemID();
        this.title = title;
        this.description = description;
        this.image = image;
        this.onHand = onHand;
        this.isActive = true;
        this.barcode = barcode;
    }

    public static ArrayList<Item> createItemList(int numItems) {
        for (int i = 1; i <= numItems; i++) {
            String description = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Tortor id aliquet lectus proin nibh nisl condimentum id. Hac habitasse platea dictumst quisque sagittis purus. Enim tortor at auctor urna nunc id. Dui nunc mattis enim ut tellus elementum sagittis.";
            String options = "0123456789";
            Float[] ratingOptions = {0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f, 5.0f};
            Boolean[] favOptions = {true, false};
            Boolean isFav = favOptions[new Random().nextInt(favOptions.length)];
            int rand = new Random().nextInt(options.length());
            Float rating = ratingOptions[new Random().nextInt(ratingOptions.length)];
            items.add(new Item("Item " + i, description, "@drawable/image_icon", rand, isFav, rating));
        }

        return items;
    }

    public String getLastItemID() {
        int lastID = items.size();
        return items.get(lastID - 1).getItemID();
    }

    public Integer getLastItemIndex() {
        return items.size() - 1;
    }

    public String getItemID() {
        return itemID;
    }

    public void setIsFavorite(Boolean isFavorite) {
        this.isFavorite = isFavorite;
    }

    public void setIsActive(Boolean isActive) {
        this.isActive = isActive;
    }

    public void setRating(Float rating) {
        this.rating = rating;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public void setImage(String image) {
        this.image = image;
    }

    public void setOnHand(Integer onHand) {
        this.onHand = onHand;
    }

    public void setBarcode(NfcBarcode barcode) {
        this.barcode = barcode;
    }

    public Boolean getIsFavorite() {
        return isFavorite;
    }

    public Boolean getIsActive() {
        return isActive;
    }

    public float getRating() {
        return rating;
    }

    public String getTitle() {
        return title;
    }

    public String getDescription() {
        return description;
    }

    public Integer getOnHand() {
        return onHand;
    }


}
