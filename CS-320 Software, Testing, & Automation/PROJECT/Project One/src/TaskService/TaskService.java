package TaskService;

import java.util.ArrayList;

import static Utility.Util.*;

/**
 * The type Task service.
 */
public class TaskService {
    private static String taskID = generateID();
    private static ArrayList<Task> tasks = new ArrayList<Task>();

    /**
     * Instantiates a new Task service.
     */
    public TaskService() {

        taskID = generateID();
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
        checkID(taskID);
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
        taskID = generateID();
        tasks.add(new Task(taskID, taskName, taskDescription));
    }

    /**
     * Remove task.
     *
     * @param taskID the task id
     */
    public static void removeTask(String taskID) {
        checkID(taskID);
        for (Task task : tasks) {
            if (task.getTaskID().equals(taskID)) {
                tasks.remove(task);
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
        return tasks.size() - 1;
    }

    /**
     * Gets last id.
     *
     * @return the last id
     */
    public static String getLastID() {
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
        checkID(taskID);
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
                break;
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
                break;
            }
        }
    }
}
