package milestone;

import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.Random;

/**
 * The type Task service.
 */
public class TaskService {
    private static String taskID;
    private static ArrayList<Task> tasks = new ArrayList<Task>();

    private static String generateTaskID() {
        byte[] array = new byte[10];
        new Random().nextBytes(array); // length is bounded by 7
        return new String(array, StandardCharsets.UTF_8);
    }

    /**
     * Instantiates a new Task service.
     */
    public TaskService() {
        taskID = generateTaskID();
    }

    /**
     * Gets task list.
     *
     * @return the task list
     */
    public static ArrayList<Task> getTaskList() {
        return tasks;
    }

    /**
     * Gets task.
     *
     * @param taskID the task id
     * @return the task
     */
    public static Task getTask(String taskID) {
        if (taskID == null || taskID.length() > 10) {
            throw new IllegalArgumentException("Invalid task ID");
        }
        for (Task task : tasks) {
            if (task.getTaskID().equals(taskID)) {
                return task;
            }
        }
        return null;
    }

    /**
     * Add task.
     *
     * @param taskName        the task name
     * @param taskDescription the task description
     */
    public static void addTask(String taskName, String taskDescription) {
        taskID = generateTaskID();
        tasks.add(new Task(taskID, taskName, taskDescription));
    }

    /**
     * Remove task.
     *
     * @param taskID the task id
     */
    public static void removeTask(String taskID) {
        if (taskID == null || taskID.length() > 10) {
            throw new IllegalArgumentException("Invalid task ID");
        }
        tasks.removeIf(task -> task.getTaskID().equals(taskID));
    }

    /**
     * Gets last index.
     *
     * @return the last index
     */
    public Integer getLastIndex() {
        int numOfTasks = tasks.size();
        return numOfTasks - 1;
    }

    /**
     * Gets last id.
     *
     * @return the last id
     */
    public String getLastID() {
        return tasks.get(getLastIndex()).getTaskID();
    }

    /**
     * Update task.
     *
     * @param taskID          the task id
     * @param taskName        the task name
     * @param taskDescription the task description
     */
    public static void updateTask(String taskID, String taskName, String taskDescription) {
        for (Task task : tasks) {
            if (task.getTaskID().equals(taskID)) {
                task.setTaskName(taskName);
                task.setTaskDescription(taskDescription);
            }
        }
    }

    /**
     * Update task name.
     *
     * @param taskID   the task id
     * @param taskName the task name
     */
    public static void updateTaskName(String taskID, String taskName) {
        for (Task task : tasks) {
            if (task.getTaskID().equals(taskID)) {
                task.setTaskName(taskName);
            }
        }
    }

    /**
     * Update task description.
     *
     * @param taskID          the task id
     * @param taskDescription the task description
     */
    public static void updateTaskDescription(String taskID, String taskDescription) {
        for (Task task : tasks) {
            if (task.getTaskID().equals(taskID)) {
                task.setTaskDescription(taskDescription);
            }
        }
    }
}
