package milestone;

import java.util.ArrayList;

/**
 * The type Contact.
 */
public class Contact {

    // Private variables
    private final String _contactID;
    private String _firstName;
    private String _lastName;
    private String _phone;
    private String _address;


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
        if (contactID == null || contactID.length() > 10) {
            throw new IllegalArgumentException("Invalid contactID");
        }
        if (firstName == null || firstName.length() > 10) {
            throw new IllegalArgumentException("Invalid first name");
        }
        if (lastName == null || lastName.length() > 10) {
            throw new IllegalArgumentException("Invalid last name");
        }
        if (phone == null || phone.length() != 10) {
            throw new IllegalArgumentException("Invalid phone number");
        }
        if (address == null || address.length() > 30) {
            throw new IllegalArgumentException("Invalid address");
        }
        this._contactID = contactID;
        this._firstName = firstName;
        this._lastName = lastName;
        this._phone = phone;
        this._address = address;
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
     * Gets phone.
     *
     * @return the phone
     */
// Accessors and Mutators
    public String getPhone() {
        return _phone;
    }

    /**
     * Sets phone.
     *
     * @param _phone the phone
     */
    public void setPhone(String _phone) {
        if (_phone == null || _phone.length() != 10) {
            throw new IllegalArgumentException("Invalid phone number");
        }
        this._phone = _phone;
    }

    /**
     * Gets address.
     *
     * @return the address
     */
    public String getAddress() {
        return _address;
    }

    /**
     * Sets address.
     *
     * @param _address the address
     */
    public void setAddress(String _address) {
        if (_address == null || _address.length() > 30) {
            throw new IllegalArgumentException("Invalid address");
        }
        this._address = _address;
    }

    /**
     * Gets last name.
     *
     * @return the last name
     */
    public String getLastName() {
        return _lastName;
    }

    /**
     * Sets last name.
     *
     * @param _lastName the last name
     */
    public void setLastName(String _lastName) {
        if (_lastName == null || _lastName.length() > 10) {
            throw new IllegalArgumentException("Invalid last name");
        }
        this._lastName = _lastName;
    }

    /**
     * Gets first name.
     *
     * @return the first name
     */
    public String getFirstName() {
        return _firstName;
    }

    /**
     * Sets first name.
     *
     * @param _firstName the first name
     */
    public void setFirstName(String _firstName) {
        if (_firstName == null || _firstName.length() > 10) {
            throw new IllegalArgumentException("Invalid first name");
        }
        this._firstName = _firstName;
    }

    /**
     * Gets contact id.
     *
     * @return the contact id
     */
    public String getContactID() {
        return _contactID;
    }

}