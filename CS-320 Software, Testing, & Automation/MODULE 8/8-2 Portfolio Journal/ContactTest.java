package test;


import ContactService.Contact;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;
import static Utility.Util.*;

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
        this.contactID = generateID();
        this.firstName = "John";
        this.lastName = "Doe";
        this.phone = "1234567890";
        this.address = "1234 Main St";
        this.invalidContactID = generateInvalidID();
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
     * Test contact invalid id.
     */
    @Test
    void testContactInvalidID() {
        assertThrows(IllegalArgumentException.class, () ->
            new Contact(invalidContactID, firstName, lastName, phone, address));
        assertThrows(IllegalArgumentException.class, () ->
            new Contact(null, firstName, lastName, phone, address));
    }

    /**
     * Test contact invalid first name.
     */
    @Test
    void testContactInvalidFirstName() {
        assertThrows(IllegalArgumentException.class, () ->
            new Contact(contactID, invalidFirstName, lastName, phone, address));
        assertThrows(IllegalArgumentException.class, () ->
            new Contact(contactID, null, lastName, phone, address));
    }

    /**
     * Test contact invalid last name.
     */
    @Test
    void testContactInvalidLastName() {
        assertThrows(IllegalArgumentException.class, () ->
            new Contact(contactID, firstName, invalidLastName, phone, address));
        assertThrows(IllegalArgumentException.class, () ->
            new Contact(contactID, firstName, null, phone, address));
    }

    /**
     * Test contact invalid phone.
     */
    @Test
    void testContactInvalidPhone() {
        assertThrows(IllegalArgumentException.class, () ->
            new Contact(contactID, firstName, lastName, invalidPhone, address));
        assertThrows(IllegalArgumentException.class, () ->
            new Contact(contactID, firstName, lastName, null, address));
    }

    /**
     * Test contact invalid address.
     */
    @Test
    void testContactInvalidAddress() {
        assertThrows(IllegalArgumentException.class, () ->
            new Contact(contactID, firstName, lastName, phone, invalidAddress));
        assertThrows(IllegalArgumentException.class, () ->
            new Contact(contactID, firstName, lastName, phone, null));
    }

    /**
     * Test contact set first name.
     */
    @Test
    void testContactSetFirstName() {
        Contact contact = new Contact(contactID, firstName, lastName, phone, address);
        contact.setFirstName(firstName);
        assertEquals(firstName, contact.getFirstName());
        assertThrows(IllegalArgumentException.class, () ->
            contact.setFirstName(invalidFirstName));
        assertThrows(IllegalArgumentException.class, () ->
            contact.setFirstName(null));
    }

    /**
     * Test contact set last name.
     */
    @Test
    void testContactSetLastName() {
        Contact contact = new Contact(contactID, firstName, lastName, phone, address);
        contact.setLastName(lastName);
        assertEquals(lastName, contact.getLastName());
        assertThrows(IllegalArgumentException.class, () ->
            contact.setLastName(invalidLastName));
        assertThrows(IllegalArgumentException.class, () ->
            contact.setLastName(null));
    }

    /**
     * Test contact set phone.
     */
    @Test
    void testContactSetPhone() {
        Contact contact = new Contact(contactID, firstName, lastName, phone, address);
        contact.setPhone(phone);
        assertThrows(IllegalArgumentException.class, () ->
            contact.setPhone(invalidPhone));
        assertThrows(IllegalArgumentException.class, () ->
            contact.setPhone(null));
    }

    /**
     * Test contact set address.
     */
    @Test
    void testContactSetAddress() {
        Contact contact = new Contact(contactID, firstName, lastName, phone, address);
        contact.setAddress(address);
        assertEquals(address, contact.getAddress());
        assertThrows(IllegalArgumentException.class, () ->
            contact.setAddress(invalidAddress));
        assertThrows(IllegalArgumentException.class, () ->
            contact.setAddress(null));
    }



}