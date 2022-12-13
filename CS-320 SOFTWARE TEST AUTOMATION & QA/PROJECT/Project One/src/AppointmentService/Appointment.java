package AppointmentService;

import java.time.LocalDateTime;

import static Utility.Util.*;

/**
 * The type Appointment.
 */
public class Appointment {

    // Declaration of variables
    private final String _appointmentID;
    private static LocalDateTime _appointmentDate;
    private static String _appointmentDescription;

    /**
     * Instantiates a new Appointment.
     *
     * @param appointmentID          the appointment id
     * @param appointmentDate        the appointment date
     * @param appointmentDescription the appointment description
     */
    public Appointment(String appointmentID, LocalDateTime appointmentDate, String appointmentDescription) {
        checkID(appointmentID);
        checkDate(appointmentDate);
        checkProperty(appointmentDescription, 50, "description");
        this._appointmentID = appointmentID;
        _appointmentDate = appointmentDate;
        this._appointmentDescription = appointmentDescription;
    }

    /**
     * The entry point of application.
     *
     * @param args the input arguments
     */
    public static void main(String[] args) {
        System.out.println("Hello world!");
    }

    /**
     * Gets appointment id.
     *
     * @return the appointment id
     */
    public String getAppointmentID() {
        return _appointmentID;
    }

    /**
     * Gets appointment date.
     *
     * @return the appointment date
     */
    public static LocalDateTime getAppointmentDate() {

        return _appointmentDate;
    }

    /**
     * Sets appointment date.
     *
     * @param _appointmentDate the appointment date
     */
    public void setAppointmentDate(LocalDateTime _appointmentDate) {
        checkDate(_appointmentDate);
        Appointment._appointmentDate = _appointmentDate;
    }

    /**
     * Gets appointment description.
     *
     * @return the appointment description
     */
    public static String getAppointmentDescription() {
        return _appointmentDescription;
    }

    /**
     * Sets appointment description.
     *
     * @param _appointmentDescription the appointment description
     */
    public void setAppointmentDescription(String _appointmentDescription) {
        checkProperty(_appointmentDescription, 50, "description");
        Appointment._appointmentDescription = _appointmentDescription;
    }
}