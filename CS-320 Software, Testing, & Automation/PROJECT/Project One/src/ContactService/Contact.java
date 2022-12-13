package ContactService;

import static Utility.Util.*;

/**
 * The type Contact.
 */
public class Contact {

    // Private variables
    private final String _contactID;
    private static String _firstName;
    private static String _lastName;
    private static String _phone;
    private static String _address;


    /**
     * Instantiates a new Contact.
     *
     * @param contactID the contact id
     * @param firstName the first name
     * @param lastName  the last name
     * @param phone     the phone
     * @param address   the address
     */
// Default constructor for Contact class
    public Contact(String contactID, String firstName, String lastName, String phone, String address) {
        checkID(contactID);
        checkProperty(firstName, 10, "first name");
        checkProperty(lastName, 10, "last name");
        checkPhone(phone);
        checkProperty(address, 30, "address");
        this._contactID = contactID;
        _firstName = firstName;
        _lastName = lastName;
        _phone = phone;
        _address = address;
    }

    /**
     * The entry point of application.
     *
     * @param args the input arguments
     */
    public static void main(String[] args) {
        new Contact("1234567890", "John", "Doe", "1234567890", "123 Main St");
    }

    /**
     * Gets contact id.
     *
     * @return the contact id
     */
    public String getContactID() {

        return _contactID;
    }


    /**
     * Gets phone.
     *
     * @return the phone
     */
// Accessors and Mutators
    public static String getPhone() {

        return _phone;
    }

    /**
     * Sets phone.
     *
     * @param _phone the phone
     */
    public void setPhone(String _phone) {
        checkPhone(_phone);
        Contact._phone = _phone;
    }

    /**
     * Gets address.
     *
     * @return the address
     */
    public static String getAddress() {

        return _address;
    }

    /**
     * Sets address.
     *
     * @param _address the address
     */
    public void setAddress(String _address) {
        checkProperty(_address, 30, "address");
        Contact._address = _address;
    }

    /**
     * Gets last name.
     *
     * @return the last name
     */
    public static String getLastName() {

        return _lastName;
    }

    /**
     * Sets last name.
     *
     * @param _lastName the last name
     */
    public void setLastName(String _lastName) {
        checkProperty(_lastName, 10, "last name");
        Contact._lastName = _lastName;
    }

    /**
     * Gets first name.
     *
     * @return the first name
     */
    public static String getFirstName() {

        return _firstName;
    }

    /**
     * Sets first name.
     *
     * @param _firstName the first name
     */
    public void setFirstName(String _firstName) {
        checkProperty(_firstName, 10, "first name");
        Contact._firstName = _firstName;
    }
}