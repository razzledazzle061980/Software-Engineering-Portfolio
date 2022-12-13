package ContactService;

import java.util.ArrayList;

import static Utility.Util.*;

/**
 * The type Contact service.
 */
public class ContactService {
    private static String contactID = generateID();
    private static ArrayList<Contact> contacts = new ArrayList<Contact>();

    /**
     * Instantiates a new Contact service.
     */
    public ContactService() {

        contactID = generateID();
        }

    /**
     * Gets contact list.
     *
     * @return the contact list
     */
    public static ArrayList<Contact> getContactList() {
            return contacts;
        }

    /**
     * Gets contact.
     *
     * @param contactID the contact id
     */
    public static Contact getContact(String contactID) {
        checkID(contactID);
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
     */
    public static void removeContact(String contactID) {
        checkID(contactID);
        for (Contact contact : contacts) {
            if (contact.getContactID().equals(contactID)) {
                contacts.remove(contact);
                break;
            }
        }

    }

    /**
     * Gets last index.
     *
     * @return the last index
     */
    public static Integer getLastIndex() {

        return  contacts.size() -1;
    }

    /**
     * Gets last id.
     *
     * @return the last id
     */
    public static String getLastID() {
        return contacts.get(getLastIndex()).getContactID();
    }

    /**
     * Update contact.
     *
     * @param contactID the contact id
     * @param firstName the first name
     * @param lastName  the last name
     * @param phone     the phone
     * @param address   the address
     */
    public static void updateContact(String contactID, String firstName, String lastName, String phone, String address) {
        checkID(contactID);
        for (Contact contact : contacts) {
            if (contact.getContactID().equals(contactID)) {
                contact.setFirstName(firstName);
                contact.setLastName(lastName);
                contact.setPhone(phone);
                contact.setAddress(address);
                break;
            }
        }
    }

    /**
     * Update first name.
     *
     * @param contactID the contact id
     * @param firstName the first name
     */
    public static void updateFirstName(String contactID, String firstName) {
        checkID(contactID);
        for (Contact contact : contacts) {
            if (contact.getContactID().equals(contactID)) {
                contact.setFirstName(firstName);
                break;
            }
        }
    }

    /**
     * Update last name.
     *
     * @param contactID the contact id
     * @param lastName  the last name
     */
    public static void updateLastName(String contactID, String lastName) {
        checkID(contactID);
        for (Contact contact : contacts) {
            if (contact.getContactID().equals(contactID)) {
                contact.setLastName(lastName);
                break;
            }
        }
    }

    /**
     * Update phone.
     *
     * @param contactID the contact id
     * @param phone     the phone
     */
    public static void updatePhone(String contactID, String phone) {
        checkID(contactID);
        for (Contact contact : contacts) {
            if (contact.getContactID().equals(contactID)) {
                contact.setPhone(phone);
                break;
            }
        }
    }

    /**
     * Update address.
     *
     * @param contactID the contact id
     * @param address   the address
     */
    public static void updateAddress(String contactID, String address) {
        checkID(contactID);
        for (Contact contact : contacts) {
            if (contact.getContactID().equals(contactID)) {
                contact.setAddress(address);
                break;
            }
        }
    }
}
