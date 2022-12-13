package milestone;

/**
 * The type Task.
 */
public class Task {

    // Declaration of variables
    private final String _taskID;
    private String _taskName;
    private String _taskDescription;

    /**
     * Instantiates a new Task.
     *
     * @param taskID          the task id
     * @param taskName        the task name
     * @param taskDescription the task description
     */
    public Task(String taskID, String taskName, String taskDescription) {
        if (taskID == null || taskID.length() > 10) {
            throw new IllegalArgumentException("Invalid taskID");
        }
        if (taskName == null || taskName.length() > 20) {
            throw new IllegalArgumentException("Invalid task name");
        }
        if (taskDescription == null || taskDescription.length() > 50) {
            throw new IllegalArgumentException("Invalid task description");
        }
        this._taskID = taskID;
        this._taskName = taskName;
        this._taskDescription = taskDescription;
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
     * Gets task name.
     *
     * @return the task name
     */
// Mutators and Accessors
    public String getTaskName() {
        return _taskName;
    }

    /**
     * Sets task name.
     *
     * @param _taskName the task name
     */
    public void setTaskName(String _taskName) {
        if(_taskName == null || _taskName.length() > 20) {
            throw new IllegalArgumentException("Invalid task name");
        }
        this._taskName = _taskName;
    }

    /**
     * Gets task description.
     *
     * @return the task description
     */
    public String getTaskDescription() {
        return _taskDescription;
    }

    /**
     * Sets task description.
     *
     * @param _taskDescription the task description
     */
    public void setTaskDescription(String _taskDescription) {
        if(_taskDescription == null || _taskDescription.length() > 50){
            throw new IllegalArgumentException("Invalid task description");
        }
        this._taskDescription = _taskDescription;
    }

    /**
     * Gets task id.
     *
     * @return the task id
     */
    public String getTaskID() {
        return _taskID;
    }


}