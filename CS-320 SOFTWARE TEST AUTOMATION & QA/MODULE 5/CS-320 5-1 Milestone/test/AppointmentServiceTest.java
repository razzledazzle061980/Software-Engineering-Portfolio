package test;

import milestone.AppointmentService;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.time.LocalDateTime;
import java.util.Random;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

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
    protected static String invalidAppointmentID;
    protected static LocalDateTime invalidAppointmentDate;
    protected static String invalidAppointmentDescription;

    /**
     * Initialize variables.
     */
    @BeforeEach
    void initializeVariables() {
        appointmentID = AppointmentService.generateApptID();
        appointmentDate = LocalDateTime.now().plusDays(5);
        appointmentDescription = "If you're not first, you're last";
        invalidAppointmentID = "01234567890";
        invalidAppointmentDate = LocalDateTime.now().minusDays(5);
        invalidAppointmentDescription = " Ricky Bobby says, If you're not first, you're last and you are not winning...";
    }

    /**
     * Test get appointment.
     */
    @Test
    void testGetAppointment() {
        AppointmentService.addAppointment(appointmentDate, appointmentDescription);
        String lastID = AppointmentService.getLastID();
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
        int lastIndex = AppointmentService.getLastIndex();
        assertEquals(appointmentDate, AppointmentService.getAppointmentList().get(lastIndex).getAppointmentDate());
        assertEquals(appointmentDescription, AppointmentService.getAppointmentList().get(lastIndex).getAppointmentDescription());
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
    }

    /**
     * Test update appointment.
     */
    @Test
    void testUpdateAppointment() {
        AppointmentService.addAppointment(appointmentDate, appointmentDescription);
        String lastID = AppointmentService.getLastID();
        assertThrows(IllegalArgumentException.class, () ->
                AppointmentService.updateAppointment(lastID, invalidAppointmentDate, appointmentDescription));
        assertThrows(IllegalArgumentException.class, () ->
                AppointmentService.updateAppointment(lastID, null, appointmentDescription));
        assertThrows(IllegalArgumentException.class, () ->
                AppointmentService.updateAppointment(lastID, appointmentDate, invalidAppointmentDescription));
        assertThrows(IllegalArgumentException.class, () ->
                AppointmentService.updateAppointment(lastID, appointmentDate, null));
    }

    /**
     * Test update appointment description.
     */
    @Test
    void testUpdateAppointmentDescription() {
        AppointmentService.addAppointment(appointmentDate, appointmentDescription);
        String lastID = AppointmentService.getLastID();
        AppointmentService.updateAppointmentDescription(lastID, appointmentDescription);
        assertEquals(appointmentDescription, AppointmentService.getAppointmentList().get(AppointmentService.getLastIndex()).getAppointmentDescription());
        assertThrows(IllegalArgumentException.class, () ->
                AppointmentService.updateAppointmentDescription(lastID, invalidAppointmentDescription));
        assertThrows(IllegalArgumentException.class, () ->
                AppointmentService.updateAppointmentDescription(lastID, null));
    }

    /**
     * Test update appointment date.
     */
    @Test
    void testUpdateAppointmentDate() {
        AppointmentService.addAppointment(appointmentDate, appointmentDescription);
        String lastID = AppointmentService.getLastID();
        AppointmentService.updateAppointmentDate(lastID, appointmentDate);
        assertEquals(appointmentDate, AppointmentService.getAppointmentList().get(AppointmentService.getLastIndex()).getAppointmentDate());
        assertThrows(IllegalArgumentException.class, () ->
                AppointmentService.updateAppointmentDate(lastID, invalidAppointmentDate));
        assertThrows(IllegalArgumentException.class, () ->
                AppointmentService.updateAppointmentDate(lastID, null));
    }
}
