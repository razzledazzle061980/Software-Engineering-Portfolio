package milestone;

import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.Objects;
import java.util.Random;

/**
 * The type Contact service.
 */
public class ContactService {
    private static String contactID;
    private static ArrayList<Contact> contacts = new ArrayList<Contact>();

    private static String generateID() {
        byte[] array = new byte[10];
        new Random().nextBytes(array); // length is bounded by 7
        return new String(array, StandardCharsets.UTF_8);
    }

    /**
     * Instantiates a new Contact service.
     */
    public ContactService() {
            contactID = generateID();
        }

    public static ArrayList<Contact> getContactList() {
            return contacts;
        }
    /**
     * Gets contact.
     *
     * @param contactID the contact id
     * @return the contact
     */
    public static Contact getContact(String contactID) {
        if (contactID == null || contactID.length() > 10) {
            throw new IllegalArgumentException("Invalid contact ID");
        }
            for (Contact contact : contacts) {
                if (contact.getContactID().equals(contactID)) {
                    return contact;
                }
            }
            return null;
        }

    /**
     * Add contact.
     *
     * @param firstName the first name
     * @param lastName  the last name
     * @param phone     the phone
     * @param address   the address
     */
    public static void addContact(String firstName, String lastName, String phone, String address) {
            contactID = generateID();
            contacts.add(new Contact(contactID, firstName, lastName, phone, address));
        }

    /**
     * Remove contact.
     *
     * @param contactID the contact id
     * @return
     */
    public static void delContact(String contactID) {
        if (contactID == null || contactID.length() > 10) {
            throw new IllegalArgumentException("Invalid contact ID");
        }
        contacts.removeIf(contact -> contact.getContactID().equals(contactID));
    }

    public Integer getLastIndex() {
        int numOfContacts = contacts.size();
        return numOfContacts - 1;
    }

    public String getLastID() {
        return contacts.get(getLastIndex()).getContactID();
    }

    /**
     * Update first name.
     *
     * @param contactID the contact id
     * @param firstName the first name
     */
    public static void updateFirstName(String contactID, String firstName) {
            Objects.requireNonNull(getContact(contactID)).setFirstName(firstName);
        }

    /**
     * Update last name.
     *
     * @param contactID the contact id
     * @param lastName  the last name
     */
    public static void updateLastName(String contactID, String lastName) {
            Objects.requireNonNull(getContact(contactID)).setLastName(lastName);
        }

    /**
     * Update phone.
     *
     * @param contactID the contact id
     * @param phone     the phone
     */
    public static void updatePhone(String contactID, String phone) {
            Objects.requireNonNull(getContact(contactID)).setPhone(phone);
        }

    /**
     * Update address.
     *
     * @param contactID the contact id
     * @param address   the address
     */
    public static void updateAddress(String contactID, String address) {
            Objects.requireNonNull(getContact(contactID)).setAddress(address);
        }
}
