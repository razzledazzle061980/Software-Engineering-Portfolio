package test;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import AppointmentService.Appointment;
import AppointmentService.AppointmentService;

import java.time.LocalDateTime;

import static org.junit.jupiter.api.Assertions.*;
import static Utility.Util.*;

/**
 * The type Appointment service test.
 */
public class AppointmentServiceTest {
    /**
     * The constant appointmentID.
     */
    protected static String appointmentID;
    /**
     * The constant appointmentDate.
     */
    protected static LocalDateTime appointmentDate;
    /**
     * The constant appointmentDescription.
     */
    protected static String appointmentDescription;
    /**
     * The constant invalidAppointmentID.
     */
    protected static String invalidAppointmentID;
    /**
     * The constant invalidAppointmentDate.
     */
    protected static LocalDateTime invalidAppointmentDate;
    /**
     * The constant invalidAppointmentDescription.
     */
    protected static String invalidAppointmentDescription;

    /**
     * Initialize variables.
     */
    @BeforeEach
    void initializeVariables() {
        appointmentID = generateID();
        appointmentDate = LocalDateTime.now().plusDays(5);
        appointmentDescription = "If you're not first, you're last";
        invalidAppointmentID = "01234567890";
        invalidAppointmentDate = generateInvalidDate();
        invalidAppointmentDescription = " Ricky Bobby says, If you're not first, you're last and you are not winning...";
    }

    /**
     * Test get appointment.
     */
    @Test
    void testGetAppointment() {
        AppointmentService.addAppointment(appointmentDate, appointmentDescription);
        assertThrows(IllegalArgumentException.class, () ->
                AppointmentService.getAppointment(invalidAppointmentID));
        assertThrows(IllegalArgumentException.class, () ->
                AppointmentService.getAppointment(null));
    }

    /**
     * Test add appointment.
     */
    @Test
    void testAddAppointment() {
        AppointmentService.addAppointment(appointmentDate, appointmentDescription);
        String lastID = AppointmentService.getLastID();
        Appointment appointment;
        appointment = AppointmentService.getAppointment(lastID);
        assertAll(
                () -> assertEquals(appointmentDate, Appointment.getAppointmentDate()),
                () -> assertEquals(appointmentDescription, Appointment.getAppointmentDescription()),
                () -> assertThrows(IllegalArgumentException.class, () -> AppointmentService.addAppointment(invalidAppointmentDate, appointmentDescription)),
                () -> assertThrows(IllegalArgumentException.class, () -> AppointmentService.addAppointment(appointmentDate, invalidAppointmentDescription)),
                () -> assertThrows(IllegalArgumentException.class, () -> AppointmentService.addAppointment(null, appointmentDescription)),
                () -> assertThrows(IllegalArgumentException.class, () -> AppointmentService.addAppointment(appointmentDate, null))
        );
    }

    /**
     * Test remove appointment.
     */
    @Test
    void testRemoveAppointment() {
        AppointmentService.addAppointment(appointmentDate, appointmentDescription);
        String lastID = AppointmentService.getLastID();
        assertThrows(IllegalArgumentException.class, () ->
                AppointmentService.removeAppointment(invalidAppointmentID));
        assertThrows(IllegalArgumentException.class, () ->
                AppointmentService.removeAppointment(null));
        AppointmentService.removeAppointment(lastID);
    }

    /**
     * Test update appointment.
     */
    @Test
    void testUpdateAppointment() {
        AppointmentService.addAppointment(appointmentDate, appointmentDescription);
        String lastID = AppointmentService.getLastID();
        assertAll(
                () -> assertThrows(IllegalArgumentException.class, () -> AppointmentService.updateAppointment(lastID, invalidAppointmentDate, appointmentDescription)),
                () -> assertThrows(IllegalArgumentException.class, () -> AppointmentService.updateAppointment(lastID, null, appointmentDescription)),
                () -> assertThrows(IllegalArgumentException.class, () -> AppointmentService.updateAppointment(lastID, appointmentDate, invalidAppointmentDescription)),
                () -> assertThrows(IllegalArgumentException.class, () -> AppointmentService.updateAppointment(lastID, appointmentDate, null))
        );
    }

    /**
     * Test update appointment description.
     */
    @Test
    void testUpdateAppointmentDescription() {
        AppointmentService.addAppointment(appointmentDate, appointmentDescription);
        String lastID = AppointmentService.getLastID();
        AppointmentService.updateAppointmentDescription(lastID, appointmentDescription);
        assertAll(
                () -> assertEquals(appointmentDescription, AppointmentService.getAppointmentList().get(AppointmentService.getLastIndex()).getAppointmentDescription()),
                () -> assertThrows(IllegalArgumentException.class, () -> AppointmentService.updateAppointmentDescription(lastID, invalidAppointmentDescription)),
                () -> assertThrows(IllegalArgumentException.class, () -> AppointmentService.updateAppointmentDescription(lastID, null))
        );
    }

    /**
     * Test update appointment date.
     */
    @Test
    void testUpdateAppointmentDate() {
        AppointmentService.addAppointment(appointmentDate, appointmentDescription);
        String lastID = AppointmentService.getLastID();
        AppointmentService.updateAppointmentDate(lastID, appointmentDate);
        assertAll(
                () -> assertEquals(appointmentDate, AppointmentService.getAppointmentList().get(AppointmentService.getLastIndex()).getAppointmentDate()),
                () -> assertThrows(IllegalArgumentException.class, () -> AppointmentService.updateAppointmentDate(lastID, invalidAppointmentDate)),
                () -> assertThrows(IllegalArgumentException.class, () -> AppointmentService.updateAppointmentDate(lastID, null))
        );
    }
}
