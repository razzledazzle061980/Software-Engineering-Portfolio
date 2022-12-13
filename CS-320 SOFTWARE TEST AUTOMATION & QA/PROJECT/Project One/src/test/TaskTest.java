package test;

import TaskService.Task;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;
import static TaskService.Task.getTaskDescription;
import static TaskService.Task.getTaskName;
import static Utility.Util.*;

/**
 * The type Task test.
 */
public class TaskTest {

    /**
     * The Task id.
     */
    protected String taskID;
    /**
     * The Task name.
     */
    protected String taskName;
    /**
     * The Task description.
     */
    protected String taskDescription;
    /**
     * The Invalid task id.
     */
    protected String invalidTaskID;
    /**
     * The Invalid task name.
     */
    protected String invalidTaskName;
    /**
     * The Invalid task description.
     */
    protected String invalidTaskDescription;

    /**
     * Initialize variables.
     */
    @BeforeEach
    void initializeVariables() {
        this.taskID = generateID();
        this.taskName = "Winning";
        this.taskDescription = "If you're not first, you're last";
        this.invalidTaskID = generateInvalidID();
        this.invalidTaskName = "Winning...Winning...Winning";
        this.invalidTaskDescription = " Ricky Bobby says, If you're not first, you're last and you are not winning...";
    }


    /**
     * Test task.
     */
    @Test
    void testTask() {
        Task task = new Task(taskID, taskName, taskDescription);
        assertEquals(taskID, task.getTaskID());
        assertEquals(taskName, getTaskName());
        assertEquals(taskDescription, getTaskDescription());
    }

    /**
     * Test task invalid id.
     */
    @Test
    void testTaskInvalidID() {
        assertThrows(IllegalArgumentException.class, () ->
                new Task(invalidTaskID, taskName, taskDescription));
        assertThrows(IllegalArgumentException.class, () ->
                new Task(null, taskName, taskDescription));
    }

    /**
     * Test task invalid name.
     */
    @Test
    void testTaskInvalidName() {
        assertThrows(IllegalArgumentException.class, () ->
                new Task(taskID, invalidTaskName, taskDescription));
        assertThrows(IllegalArgumentException.class, () ->
                new Task(taskID, null, taskDescription));
    }

    /**
     * Test task invalid description.
     */
    @Test
    void testTaskInvalidDescription() {
        assertThrows(IllegalArgumentException.class, () ->
                new Task(taskID, taskName, invalidTaskDescription));
        assertThrows(IllegalArgumentException.class, () ->
                new Task(taskID, taskName, null));
    }

    /**
     * Test task set task name.
     */
    @Test
    void testTaskSetTaskName() {
        Task task = new Task(taskID, taskName, taskDescription);
        task.setTaskName(taskName);
        assertEquals(taskName, getTaskName());
        assertThrows(IllegalArgumentException.class, () ->
                task.setTaskName(invalidTaskName));
        assertThrows(IllegalArgumentException.class, () ->
                task.setTaskName(null));
    }

    /**
     * Test task set task description.
     */
    @Test
    void testTaskSetTaskDescription() {
        Task task = new Task(taskID, taskName, taskDescription);
        task.setTaskDescription(taskDescription);
        assertEquals(taskDescription, getTaskDescription());
        assertThrows(IllegalArgumentException.class, () ->
                task.setTaskDescription(invalidTaskDescription));
        assertThrows(IllegalArgumentException.class, () ->
                task.setTaskDescription(null));
    }

}
