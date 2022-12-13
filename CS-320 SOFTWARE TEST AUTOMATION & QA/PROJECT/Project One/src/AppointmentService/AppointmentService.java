package AppointmentService;

import java.time.LocalDateTime;
import java.util.ArrayList;

import static Utility.Util.*;

/**
 * The type Appointment service.
 */
public class AppointmentService {
    
    private static String appointmentID = generateID();

    private static ArrayList<Appointment> appointments = new ArrayList<Appointment>();


    /**
     * Instantiates a new Appointment service.
     */
    public AppointmentService() {

        appointmentID = generateID();
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
        checkID(appointmentID);
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
     * @param appointmentDate        the appointment date
     * @param appointmentDescription the appointment description
     */
    public static void addAppointment(LocalDateTime appointmentDate, String appointmentDescription) {
        appointmentID = generateID();
        appointments.add(new Appointment(appointmentID, appointmentDate, appointmentDescription));
    }

    /**
     * Remove appointment.
     *
     * @param appointmentID the appointment id
     */
    public static void removeAppointment(String appointmentID) {
        checkID(appointmentID);
        for (Appointment appointment : appointments) {
            if (appointment.getAppointmentID().equals(appointmentID)) {
                appointments.remove(appointment);
                break;
            }
        }
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
        checkID(appointmentID);
        for (Appointment appointment : appointments) {
            if (appointment.getAppointmentID().equals(appointmentID)) {
                appointment.setAppointmentDate(appointmentDate);
                appointment.setAppointmentDescription(appointmentDescription);
                break;
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
        checkID(appointmentID);
        for (Appointment appointment : appointments) {
            if (appointment.getAppointmentID().equals(appointmentID)) {
                appointment.setAppointmentDate(appointmentDate);
                break;
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
                break;
            }
        }
    }
}

