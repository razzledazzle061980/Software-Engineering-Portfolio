package test;

import ContactService.Contact;
import ContactService.ContactService;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;
import static Utility.Util.*;

/**
 * The type Contact service test.
 */
public class ContactServiceTest {
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
        this.firstName = "Ricky";
        this.lastName = "Bobby";
        this.phone = "1234527890";
        this.address = "1111 Ricky Bobby Way";
        this.invalidContactID = generateInvalidID();
        this.invalidFirstName = "Ricky Bobby";
        this.invalidLastName = "Talladega Nights";
        this.invalidPhone = "01234567891";
        this.invalidAddress = "2222 if you ain't first, you're last St. SE Atlanta, GA 30303";
    }

    /**
     * Test get contact.
     */
    @Test
    void testGetContact() {
        ContactService.addContact(firstName, lastName, phone, address);
        assertThrows(IllegalArgumentException.class, () -> ContactService.getContact(null));
        assertThrows(IllegalArgumentException.class, () -> ContactService.getContact(invalidContactID));
    }

    /**
     * Test add contact.
     */
    @Test
    void testAddContact() {
        ContactService.addContact(firstName, lastName, phone, address);
        assertAll(
                () -> assertEquals(firstName, Contact.getFirstName()),
                () -> assertEquals(lastName, Contact.getLastName()),
                () -> assertEquals(phone, Contact.getPhone()),
                () -> assertEquals(address, Contact.getAddress()),
                () -> assertThrows(IllegalArgumentException.class, () -> ContactService.addContact(null, lastName, phone, address)),
                () -> assertThrows(IllegalArgumentException.class, () -> ContactService.addContact(invalidFirstName, lastName, phone, address)),
                () -> assertThrows(IllegalArgumentException.class, () -> ContactService.addContact(firstName, null, phone, address)),
                () -> assertThrows(IllegalArgumentException.class, () -> ContactService.addContact(firstName, invalidLastName, phone, address)),
                () -> assertThrows(IllegalArgumentException.class, () -> ContactService.addContact(firstName, lastName, null, address)),
                () -> assertThrows(IllegalArgumentException.class, () -> ContactService.addContact(firstName, lastName, invalidPhone, address)),
                () -> assertThrows(IllegalArgumentException.class, () -> ContactService.addContact(firstName, lastName, phone, null)),
                () -> assertThrows(IllegalArgumentException.class, () -> ContactService.addContact(firstName, lastName, phone, invalidAddress))
        );
    }

    /**
     * Test remove contact.
     */
    @Test
    void testRemoveContact() {
        ContactService.addContact(firstName, lastName, phone, address);
        String lastID = ContactService.getLastID();
        assertThrows(IllegalArgumentException.class, () -> ContactService.removeContact(null));
        assertThrows(IllegalArgumentException.class, () -> ContactService.removeContact(invalidContactID));
        ContactService.removeContact(lastID);
    }

    /**
     * Test update contact.
     */
    @Test
    void testUpdateContact() {
        ContactService.addContact(firstName, lastName, phone, address);
        String lastID = ContactService.getLastID();
        assertAll(
                () ->assertThrows(IllegalArgumentException.class, () -> ContactService.updateContact(null, firstName, lastName, phone, address)),
                () ->assertThrows(IllegalArgumentException.class, () -> ContactService.updateContact(invalidContactID, firstName, lastName, phone, address)),
                () ->assertThrows(IllegalArgumentException.class, () -> ContactService.updateContact(lastID, null, lastName, phone, address)),
                () ->assertThrows(IllegalArgumentException.class, () -> ContactService.updateContact(lastID, invalidFirstName, lastName, phone, address)),
                () ->assertThrows(IllegalArgumentException.class, () -> ContactService.updateContact(lastID, firstName, null, phone, address)),
                () ->assertThrows(IllegalArgumentException.class, () -> ContactService.updateContact(lastID, firstName, invalidLastName, phone, address)),
                () ->assertThrows(IllegalArgumentException.class, () -> ContactService.updateContact(lastID, firstName, lastName, null, address)),
                () ->assertThrows(IllegalArgumentException.class, () -> ContactService.updateContact(lastID, firstName, lastName, invalidPhone, address)),
                () ->assertThrows(IllegalArgumentException.class, () -> ContactService.updateContact(lastID, firstName, lastName, phone, null)),
                () ->assertThrows(IllegalArgumentException.class, () -> ContactService.updateContact(lastID, firstName, lastName, phone, invalidAddress))
        );
    }

    /**
     * Test update first name.
     */
    @Test
    void testUpdateFirstName() {
        ContactService.addContact(firstName, lastName, phone, address);
        String lastID = ContactService.getLastID();
        ContactService.updateFirstName(lastID, firstName);
        assertAll(
                () -> assertEquals(firstName, ContactService.getContactList().get(ContactService.getLastIndex()).getFirstName()),
                () -> assertThrows(IllegalArgumentException.class, () -> ContactService.updateFirstName(lastID, invalidFirstName)),
                () -> assertThrows(IllegalArgumentException.class, () -> ContactService.updateFirstName(lastID, null))
        );
    }

    /**
     * Test update last name.
     */
    @Test
    void testUpdateLastName() {
        ContactService.addContact(firstName, lastName, phone, address);
        String lastID = ContactService.getLastID();
        ContactService.updateLastName(lastID, lastName);
        assertAll(
                () -> assertEquals(lastName, ContactService.getContactList().get(ContactService.getLastIndex()).getLastName()),
                () -> assertThrows(IllegalArgumentException.class, () -> ContactService.updateLastName(lastID, invalidLastName)),
                () -> assertThrows(IllegalArgumentException.class, () -> ContactService.updateLastName(lastID, null))
        );
    }

    /**
     * Test update phone.
     */
    @Test
    void testUpdatePhone() {
        ContactService.addContact(firstName, lastName, phone, address);
        String lastID = ContactService.getLastID();
        ContactService.updatePhone(lastID, phone);
        assertAll(
                () -> assertEquals(phone, ContactService.getContactList().get(ContactService.getLastIndex()).getPhone()),
                () -> assertThrows(IllegalArgumentException.class, () -> ContactService.updatePhone(lastID, invalidPhone)),
                () -> assertThrows(IllegalArgumentException.class, () -> ContactService.updatePhone(lastID, null))
        );
    }

    /**
     * Test update address.
     */
    @Test
    void testUpdateAddress() {
        ContactService.addContact(firstName, lastName, phone, address);
        String lastID = ContactService.getLastID();
        ContactService.updateAddress(lastID, address);
        assertAll(
                () -> assertEquals(address, ContactService.getContactList().get(ContactService.getLastIndex()).getAddress()),
                () -> assertThrows(IllegalArgumentException.class, () -> ContactService.updateAddress(lastID, invalidAddress)),
                () -> assertThrows(IllegalArgumentException.class, () -> ContactService.updateAddress(lastID, null))
        );
    }

}
