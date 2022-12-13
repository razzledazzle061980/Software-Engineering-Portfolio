package Utility;

import java.nio.charset.StandardCharsets;
import java.time.LocalDateTime;
import java.util.Random;

/**
 * The type Util.
 */
public class Util {

    /**
     * Generate id string.
     *
     * @return the string
     */
    public static String generateID() {
        byte[] array = new byte[10];
        new Random().nextBytes(array); // length is bounded by 7
        return new String(array, StandardCharsets.UTF_8);
    }

    /**
     * Generate invalid id string.
     *
     * @return the string
     */
    public static String generateInvalidID() {
        byte[] array = new byte[12];
        new Random().nextBytes(array); // length is bounded by 7
        return new String(array, StandardCharsets.UTF_8);
    }

    /**
     * Check date.
     *
     * @param date the date
     */
    public static void checkDate(LocalDateTime date) {
        LocalDateTime today = LocalDateTime.now();
        if (date == null || date.isBefore(today)) {
            throw new IllegalArgumentException("Invalid date, date must not occur before today");
        }
    }

    /**
     * Check id.
     *
     * @param id the id
     */
    public static void checkID(String id) {
        if(id == null || id.length() > 10) {
            throw new IllegalArgumentException("Invalid ID");
        }
    }

    /**
     * Check property.
     *
     * @param property the property
     * @param length   the length
     * @param name     the name
     */
    public static void checkProperty(String property, Integer length, String name) {
        if(property == null || property.length() > length) {
            throw new IllegalArgumentException("Invalid " + name);
        }
    }

    /**
     * Check phone.
     *
     * @param phone the phone
     */
    public static void checkPhone(String phone) {
        if(phone == null || phone.length() != 10) {
            throw new IllegalArgumentException("Invalid phone number");
        }
    }

    /**
     * Generate invalid date local date time.
     *
     * @return the local date time
     */
    public static LocalDateTime generateInvalidDate() {
        return LocalDateTime.now().minusDays(5);
    }

}
