package milestone;

import java.nio.charset.StandardCharsets;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Date;
import java.util.Random;

/**
 * The type Appointment service.
 */
public class AppointmentService {
    private static String appointmentID;

    private static ArrayList<Appointment> appointments = new ArrayList<Appointment>();

    public static String generateApptID() {
        byte[] array = new byte[10];
        new Random().nextBytes(array); // length is bounded by 7
        return new String(array, StandardCharsets.UTF_8);
    }


    /**
     * Instantiates a new Appointment service.
     */
    public AppointmentService() {

        appointmentID = generateApptID();
    }

    /**
     * Gets appointment list.
     *
     * @return the appointment list
     */
    public static ArrayList<Appointment> getAppointmentList() {
        return appointments;
    }

    /**
     * Gets appointment.
     *
     * @param appointmentID the appointment id
     * @return the appointment
     */
    public static Appointment getAppointment(String appointmentID) {
        if (appointmentID == null || appointmentID.length() > 10) {
            throw new IllegalArgumentException("Invalid appointment ID");
        }
        for (Appointment appointment : appointments) {
            if (appointment.getAppointmentID().equals(appointmentID)) {
                return appointment;
            }
        }
        return null;
    }

    /**
     * Add appointment.
     *
     * @param appointmentDescription the appointment description
     */
    public static void addAppointment(LocalDateTime appointmentDate, String appointmentDescription) {
        String appointmentID = generateApptID();
        appointments.add(new Appointment(appointmentID, appointmentDate, appointmentDescription));
    }

    /**
     * Remove appointment.
     *
     * @param appointmentID the appointment id
     */
    public static void removeAppointment(String appointmentID) {
        if (appointmentID == null || appointmentID.length() > 10) {
            throw new IllegalArgumentException("Invalid appointment ID");
        }
        appointments.removeIf(appointment -> appointment.getAppointmentID().equals(appointmentID));
    }
    /**
     * Gets last index.
     *
     * @return the last index
     */
    public static Integer getLastIndex() {
        return appointments.size() - 1;
    }

    /**
     * Gets last id.
     *
     * @return the last id
     */
    public static String getLastID() {
        return appointments.get(getLastIndex()).getAppointmentID();
    }

    /**
     * Update appointment.
     *
     * @param appointmentID          the appointment id
     * @param appointmentDate        the appointment date
     * @param appointmentDescription the appointment description
     */
    public static void updateAppointment(String appointmentID, LocalDateTime appointmentDate, String appointmentDescription) {
        for (Appointment appointment : appointments) {
            if (appointment.getAppointmentID().equals(appointmentID)) {
                appointment.setAppointmentDate(appointmentDate);
                appointment.setAppointmentDescription(appointmentDescription);
            }
        }

    }

    /**
     * Update appointment date.
     *
     * @param appointmentID   the appointment id
     * @param appointmentDate the appointment date
     */
    public static void updateAppointmentDate(String appointmentID, LocalDateTime appointmentDate) {
        for (Appointment appointment : appointments) {
            if (appointment.getAppointmentID().equals(appointmentID)) {
                appointment.setAppointmentDate(appointmentDate);
            }
        }
    }

    /**
     * Update appointment description.
     *
     * @param appointmentID          the appointment id
     * @param appointmentDescription the appointment description
     */
    public static void updateAppointmentDescription(String appointmentID, String appointmentDescription) {
        for (Appointment appointment : appointments) {
            if (appointment.getAppointmentID().equals(appointmentID)) {
                appointment.setAppointmentDescription(appointmentDescription);
            }
        }
    }
}

