package test;


import milestone.Contact;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * The type Contact test.
 */
public class ContactTest {
    /**
     * The Contact id.
     */
// Declaration of variables
    protected String contactID;
    /**
     * The First name.
     */
    protected String firstName;
    /**
     * The Last name.
     */
    protected String lastName;
    /**
     * The Phone.
     */
    protected String phone;
    /**
     * The Address.
     */
    protected String address;

    /**
     * The Invalid contact id.
     */
// Declaration of invalid variables
    protected String invalidContactID;
    /**
     * The Invalid first name.
     */
    protected String invalidFirstName;
    /**
     * The Invalid last name.
     */
    protected String invalidLastName;
    /**
     * The Invalid phone.
     */
    protected String invalidPhone;
    /**
     * The Invalid address.
     */
    protected String invalidAddress;

    /**
     * Initialize variables.
     */
    @BeforeEach
    void initializeVariables() {
        this.contactID = "1234567890";
        this.firstName = "John";
        this.lastName = "Doe";
        this.phone = "1234567890";
        this.address = "1234 Main St";
        this.invalidContactID = "12345678901";
        this.invalidFirstName = "Ricky Bobby";
        this.invalidLastName = "Talladega Nights";
        this.invalidPhone = "01234567891";
        this.invalidAddress = "1111 if you ain't first, you're last St. SE Atlanta, GA 30303";
    }

    /**
     * Test contact.
     */
    @Test
    void testContact() {
        Contact contact = new Contact(contactID, firstName, lastName, phone, address);
        assertEquals(contactID, contact.getContactID());
        assertEquals(firstName, contact.getFirstName());
        assertEquals(lastName, contact.getLastName());
        assertEquals(phone, contact.getPhone());
        assertEquals(address, contact.getAddress());
    }

    /**
     * Test contact id to long.
     */
    @Test
    void testContactIDToLong() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            new Contact(invalidContactID, firstName, lastName, phone, address);
        });
    }

    /**
     * Test contact id null.
     */
    @Test
    void testContactIDNull() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            new Contact(null, firstName, lastName, phone, address);
        });
    }

    /**
     * Test contact first name to long.
     */
    @Test
    void testContactFirstNameToLong() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            new Contact(contactID, invalidFirstName, lastName, phone, address);
        });
    }

    /**
     * Test contact first name null.
     */
    @Test
    void testContactFirstNameNull() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            new Contact(null, invalidFirstName, lastName, phone, address);
        });
    }

    /**
     * Test contact last name to long.
     */
    @Test
    void testContactLastNameToLong() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            new Contact(contactID, firstName, invalidLastName, phone, address);
        });
    }

    /**
     * Test contact last name null.
     */
    @Test
    void testContactLastNameNull() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            new Contact(null, firstName, invalidLastName, phone, address);
        });
    }

    /**
     * Test contact phone to long.
     */
    @Test
    void testContactPhoneToLong() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            new Contact(contactID, firstName, lastName, invalidPhone, address);
        });
    }

    /**
     * Test contact phone null.
     */
    @Test
    void testContactPhoneNull() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            new Contact(null, firstName, lastName, invalidPhone, address);
        });
    }

    /**
     * Test contact address to long.
     */
    @Test
    void testContactAddressToLong() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            new Contact(contactID, firstName, lastName, phone, invalidAddress);
        });
    }

    /**
     * Test contact address null.
     */
    @Test
    void testContactAddressNull() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            new Contact(null, firstName, lastName, phone, invalidAddress);
        });
    }

    /**
     * Test contact set first name.
     */
    @Test
    void testContactSetFirstName() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            Contact contact = new Contact(contactID, firstName, lastName, phone, address);
            contact.setFirstName(invalidFirstName);
        });
    }

    /**
     * Test contact set last name.
     */
    @Test
    void testContactSetLastName() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            Contact contact = new Contact(contactID, firstName, lastName, phone, address);
            contact.setLastName(invalidLastName);
        });
    }

    /**
     * Test contact set phone.
     */
    @Test
    void testContactSetPhone() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            Contact contact = new Contact(contactID, firstName, lastName, phone, address);
            contact.setPhone(invalidPhone);
        });
    }

    /**
     * Test contact set address.
     */
    @Test
    void testContactSetAddress() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            Contact contact = new Contact(contactID, firstName, lastName, phone, address);
            contact.setAddress(invalidAddress);
        });
    }



}