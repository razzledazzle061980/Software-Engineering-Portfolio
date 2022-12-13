package TaskService;

import static Utility.Util.*;

/**
 * The type Task.
 */
public class Task {

    // Declaration of variables
    private final String _taskID;
    private static String _taskName;
    private static String _taskDescription;

    /**
     * Instantiates a new Task.
     *
     * @param taskID          the task id
     * @param taskName        the task name
     * @param taskDescription the task description
     */
    public Task(String taskID, String taskName, String taskDescription) {
        checkID(taskID);
        checkProperty(taskName, 20, "task name");
        checkProperty(taskDescription, 50, "task description");
        this._taskID = taskID;
        _taskName = taskName;
        _taskDescription = taskDescription;
    }

    /**
     * The entry point of application.
     *
     * @param args the input arguments
     */
// Application entry point
    public static void main(String[] args) {
        new Task("1234567890", "Task 1", "This is a task");
    }

    /**
     * Gets task id.
     *
     * @return the task id
     */
    public String getTaskID() {

        return _taskID;
    }


    /**
     * Gets task name.
     *
     * @return the task name
     */
// Mutators and Accessors
    public static String getTaskName() {

        return _taskName;
    }

    /**
     * Sets task name.
     *
     * @param _taskName the task name
     */
    public void setTaskName(String _taskName) {
        checkProperty(_taskName, 20, "task name");
        Task._taskName = _taskName;
    }

    /**
     * Gets task description.
     *
     * @return the task description
     */
    public static String getTaskDescription() {

        return _taskDescription;
    }

    /**
     * Sets task description.
     *
     * @param _taskDescription the task description
     */
    public void setTaskDescription(String _taskDescription) {
        checkProperty(_taskDescription, 50, "task description");
        Task._taskDescription = _taskDescription;
    }



}