package test;

import milestone.Appointment;
import milestone.AppointmentService;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.time.LocalDateTime;
import java.time.LocalDateTime;


import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

/**
 * The type Appointment test.
 */
public class AppointmentTest {
    /**
     * The Appointment id.
     */
    protected String appointmentID;
    /**
     * The Appointment date.
     */
    protected LocalDateTime appointmentDate;
    /**
     * The Appointment description.
     */
    protected String appointmentDescription;

    /**
     * The Invalid appointment id.
     */
    protected String invalidAppointmentID;
    /**
     * The Invalid appointment date.
     */
    protected LocalDateTime invalidAppointmentDate;
    /**
     * The Invalid appointment description.
     */
    protected String invalidAppointmentDescription;

    /**
     * Initialize variables.
     */
    @BeforeEach
    void initializeVariables() {
        this.appointmentID = AppointmentService.generateApptID();
        this.appointmentDate = LocalDateTime.now().plusDays(5);
        this.appointmentDescription = "If you're not first, you're last";
        this.invalidAppointmentID = "01234567890";
        this.invalidAppointmentDate = LocalDateTime.now().minusDays(5);
        this.invalidAppointmentDescription = " Ricky Bobby says, If you're not first, you're last and you are not winning...";

    }

    /**
     * Test appointment.
     */
    @Test
    void testAppointment() {
        Appointment appointment = new Appointment(appointmentID, appointmentDate, appointmentDescription);
        Integer lastIndex = AppointmentService.getLastIndex();
        assertEquals(appointmentID, appointment.getAppointmentID());
        assertEquals(appointmentDate, appointment.getAppointmentDate());
        assertEquals(appointmentDescription, appointment.getAppointmentDescription());
    }

    /**
     * Test appointment invalid id.
     */
    @Test
    void testAppointmentInvalidID() {
        assertThrows(IllegalArgumentException.class, () ->
                new Appointment(invalidAppointmentID, appointmentDate, appointmentDescription));
        assertThrows(IllegalArgumentException.class, () ->
                new Appointment(null, appointmentDate, appointmentDescription));
    }

    /**
     * Test appointment invalid date.
     */
    @Test
    void testAppointmentInvalidDate() {
        assertThrows(IllegalArgumentException.class, () ->
                new Appointment(appointmentID, invalidAppointmentDate, appointmentDescription));
        assertThrows(IllegalArgumentException.class, () ->
                new Appointment(appointmentID, null, appointmentDescription));
    }

    /**
     * Test appointment invalid description.
     */
    @Test
    void testAppointmentInvalidDescription() {
        assertThrows(IllegalArgumentException.class, () ->
                new Appointment(appointmentID, appointmentDate, invalidAppointmentDescription));
        assertThrows(IllegalArgumentException.class, () ->
                new Appointment(appointmentID, appointmentDate, null));
    }

    /**
     * Test set appointment date.
     */
    @Test
    void testSetAppointmentDate() {
        Appointment appointment = new Appointment(appointmentID, appointmentDate, appointmentDescription);
        appointment.setAppointmentDate(appointmentDate);
        assertEquals(appointmentDate, appointment.getAppointmentDate());
        assertThrows(IllegalArgumentException.class, () ->
                appointment.setAppointmentDate(invalidAppointmentDate));
        assertThrows(IllegalArgumentException.class, () ->
                appointment.setAppointmentDate(null));
    }

    /**
     * Test set appointment description.
     */
    @Test
    void testSetAppointmentDescription() {
        Appointment appointment = new Appointment(appointmentID, appointmentDate, appointmentDescription);
        appointment.setAppointmentDescription(appointmentDescription);
        assertEquals(appointmentDescription, appointment.getAppointmentDescription());
        assertThrows(IllegalArgumentException.class, () ->
                appointment.setAppointmentDescription(invalidAppointmentDescription));
        assertThrows(IllegalArgumentException.class, () ->
                appointment.setAppointmentDescription(null));
    }


}
