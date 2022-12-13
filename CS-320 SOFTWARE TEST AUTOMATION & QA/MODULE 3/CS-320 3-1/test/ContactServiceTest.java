package test;

import milestone.ContactService;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static milestone.ContactService.getContact;
import static org.junit.jupiter.api.Assertions.*;

public class ContactServiceTest {
    private static ContactService service;
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
        this.contactID = "ju83kdjlw9";
        this.firstName = "Ricky";
        this.lastName = "Bobby";
        this.phone = "1234527890";
        this.address = "1111 Ricky Bobby Way";
        this.invalidContactID = "12325678901";
        this.invalidFirstName = "Ricky Bobby";
        this.invalidLastName = "Talladega Nights";
        this.invalidPhone = "01234567891";
        this.invalidAddress = "2222 if you ain't first, you're last St. SE Atlanta, GA 30303";
    }

    @Test
    void testAddContact() {
        service = new ContactService();
        ContactService.addContact(firstName, lastName, phone, address);
        Integer lastIndex = service.getLastIndex();
        assertAll("Contact",
                () -> assertEquals(firstName, ContactService.getContactList().get(lastIndex).getFirstName()),
                () -> assertEquals(lastName, ContactService.getContactList().get(lastIndex).getLastName()),
                () -> assertEquals(phone, ContactService.getContactList().get(lastIndex).getPhone()),
                () -> assertEquals(address, ContactService.getContactList().get(lastIndex).getAddress()),
                () -> assertNotNull(ContactService.getContactList().get(lastIndex).getFirstName()),
                () -> assertNotNull(ContactService.getContactList().get(lastIndex).getLastName()),
                () -> assertNotNull(ContactService.getContactList().get(lastIndex).getPhone()),
                () -> assertNotNull(ContactService.getContactList().get(lastIndex).getAddress()),
                () -> assertThrows(IllegalArgumentException.class, () -> ContactService.addContact(invalidFirstName, lastName, phone, address)),
                () -> assertThrows(IllegalArgumentException.class, () -> ContactService.addContact(firstName, invalidLastName, phone, address)),
                () -> assertThrows(IllegalArgumentException.class, () -> ContactService.addContact(firstName, lastName, invalidPhone, address)),
                () -> assertThrows(IllegalArgumentException.class, () -> ContactService.addContact(firstName, lastName, phone, invalidAddress))
        );
    }

    @Test
    void testDelContact() {
        service = new ContactService();
        ContactService.addContact(firstName, lastName, phone, address);
        String lastID = service.getLastID();
        Assertions.assertThrows(Exception.class, () -> ContactService.delContact(null));
        assertThrows(Exception.class, () -> ContactService.delContact(invalidContactID));
    }

    @Test
    void testGetContact() {
        service = new ContactService();
        ContactService.addContact(firstName, lastName, phone, address);
        String lastID = service.getLastID();
        Assertions.assertThrows(Exception.class, () -> ContactService.getContact(null));
        assertThrows(Exception.class, () -> getContact(invalidContactID));
    }

    @Test
    void testUpdateFirstName() {
        service = new ContactService();
        ContactService.addContact(firstName, lastName, phone, address);
        Integer lastIndex = service.getLastIndex();
        String lastID = service.getLastID();
        assertEquals(firstName, ContactService.getContactList().get(lastIndex).getFirstName(), firstName);
        Assertions.assertThrows(IllegalArgumentException.class, () -> ContactService.updateFirstName(null, firstName));
        Assertions.assertThrows(IllegalArgumentException.class, () -> ContactService.updateFirstName(invalidContactID, firstName));
        Assertions.assertThrows(IllegalArgumentException.class, () -> ContactService.updateFirstName(lastID, invalidFirstName));
        Assertions.assertThrows(IllegalArgumentException.class, () -> ContactService.updateFirstName(lastID, null));
    }

    @Test
    void testUpdateLastName() {
        service = new ContactService();
        ContactService.addContact(firstName, lastName, phone, address);
        Integer lastIndex = service.getLastIndex();
        String lastID = service.getLastID();
        assertEquals(lastName, ContactService.getContactList().get(lastIndex).getLastName(), lastName);
        assertThrows(IllegalArgumentException.class, () -> ContactService.updateLastName(null, lastName));
        assertThrows(IllegalArgumentException.class, () -> ContactService.updateLastName(invalidContactID, lastName));
        assertThrows(IllegalArgumentException.class, () -> ContactService.updateLastName(lastID, invalidLastName));
        assertThrows(IllegalArgumentException.class, () -> ContactService.updateLastName(lastID, null));
    }

    @Test
    void testUpdatePhone() {
        service = new ContactService();
        ContactService.addContact(firstName, lastName, phone, address);
        Integer lastIndex = service.getLastIndex();
        String lastID = service.getLastID();
        assertEquals(phone, ContactService.getContactList().get(lastIndex).getPhone(), phone);
        assertThrows(IllegalArgumentException.class, () -> ContactService.updatePhone(null, phone));
        assertThrows(IllegalArgumentException.class, () -> ContactService.updatePhone(invalidContactID, phone));
        assertThrows(IllegalArgumentException.class, () -> ContactService.updatePhone(lastID, invalidPhone));
        assertThrows(IllegalArgumentException.class, () -> ContactService.updatePhone(lastID, null));
    }

    @Test
    void testUpdateAddress() {
        service = new ContactService();
        ContactService.addContact(firstName, lastName, phone, address);
        Integer lastIndex = service.getLastIndex();
        String lastID = service.getLastID();
        assertEquals(address, ContactService.getContactList().get(lastIndex).getAddress(), address);
        assertThrows(IllegalArgumentException.class, () -> ContactService.updateAddress(null, address));
        assertThrows(IllegalArgumentException.class, () -> ContactService.updateAddress(invalidContactID, address));
        assertThrows(IllegalArgumentException.class, () -> ContactService.updateAddress(lastID, invalidAddress));
        assertThrows(IllegalArgumentException.class, () -> ContactService.updateAddress(lastID, null));
    }

}
