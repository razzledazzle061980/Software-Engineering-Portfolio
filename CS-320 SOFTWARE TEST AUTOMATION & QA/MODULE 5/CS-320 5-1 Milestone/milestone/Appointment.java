package milestone;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.time.LocalDateTime;
import java.util.Date;

/**
 * The type Appointment.
 */
public class Appointment {

    // Declaration of variables
    private final String _appointmentID;
    private LocalDateTime _appointmentDate;
    private String _appointmentDescription;

    private final LocalDateTime today = LocalDateTime.now();

    private Boolean checkDate(LocalDateTime date) {
        boolean isBefore = false;
        LocalDateTime today = LocalDateTime.now();

        if (date.isBefore(today)) {
             isBefore = true;
        }
        return isBefore;
    }

    /**
     * Instantiates a new Appointment.
     *
     * @param appointmentID          the appointment id
     * @param appointmentDate        the appointment date
     * @param appointmentDescription the appointment description
     */
    public Appointment(String appointmentID, LocalDateTime appointmentDate, String appointmentDescription) {
        if (appointmentID == null || appointmentID.length() > 10) {
            throw new IllegalArgumentException("Invalid appointmentID");
        }
        if (appointmentDate == null || checkDate(appointmentDate)) {
            throw new IllegalArgumentException("Invalid appointment date");
        }
        if (appointmentDescription == null || appointmentDescription.length() > 50) {
            throw new IllegalArgumentException("Invalid appointment description");
        }
        this._appointmentID = appointmentID;
        this._appointmentDate = appointmentDate;
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
    public LocalDateTime getAppointmentDate() {
        return _appointmentDate;
    }

    /**
     * Sets appointment date.
     *
     * @param _appointmentDate the appointment date
     */
    public void setAppointmentDate(LocalDateTime _appointmentDate) {
        if (_appointmentDate == null || checkDate(_appointmentDate)) {
            throw new IllegalArgumentException("Invalid appointment date");
        }
        this._appointmentDate = _appointmentDate;
    }

    /**
     * Gets appointment description.
     *
     * @return the appointment description
     */
    public String getAppointmentDescription() {
        return _appointmentDescription;
    }

    /**
     * Sets appointment description.
     *
     * @param _appointmentDescription the appointment description
     */
    public void setAppointmentDescription(String _appointmentDescription) {
        if (_appointmentDescription == null || _appointmentDescription.length() > 50) {
            throw new IllegalArgumentException("Invalid appointment description");
        }
        this._appointmentDescription = _appointmentDescription;
    }
}