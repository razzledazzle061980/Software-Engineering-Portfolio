package test;

import milestone.Task;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class TaskTest {

    protected String taskID;
    protected String taskName;
    protected String taskDescription;
    protected String invalidTaskID;
    protected String invalidTaskName;
    protected String invalidTaskDescription;

    @BeforeEach
    void initializeVariables() {
        this.taskID = "1234567890";
        this.taskName = "Winning";
        this.taskDescription = "If you're not first, you're last";
        this.invalidTaskID = "01234567890";
        this.invalidTaskName = "Winning...Winning...Winning";
        this.invalidTaskDescription = " Ricky Bobby says, If you're not first, you're last and you are not winning...";
    }


    @Test
    void testTask() {
        Task task = new Task(taskID, taskName, taskDescription);
        assertEquals(taskID, task.getTaskID());
        assertEquals(taskName, task.getTaskName());
        assertEquals(taskDescription, task.getTaskDescription());
    }

    @Test
    void testTaskInvalidID() {
        assertThrows(IllegalArgumentException.class, () ->
                new Task(invalidTaskID, taskName, taskDescription));
        assertThrows(IllegalArgumentException.class, () ->
                new Task(null, taskName, taskDescription));
    }

    @Test
    void testTaskInvalidName() {
        assertThrows(IllegalArgumentException.class, () ->
                new Task(taskID, invalidTaskName, taskDescription));
        assertThrows(IllegalArgumentException.class, () ->
                new Task(taskID, null, taskDescription));
    }

    @Test
    void testTaskInvalidDescription() {
        assertThrows(IllegalArgumentException.class, () ->
                new Task(taskID, taskName, invalidTaskDescription));
        assertThrows(IllegalArgumentException.class, () ->
                new Task(taskID, taskName, null));
    }

    @Test
    void testSetTaskName() {
        Task task = new Task(taskID, taskName, taskDescription);
        task.setTaskName(taskName);
        assertEquals(taskName, task.getTaskName());
        assertThrows(IllegalArgumentException.class, () ->
                task.setTaskName(invalidTaskName));
        assertThrows(IllegalArgumentException.class, () ->
                task.setTaskName(null));
    }

    @Test
    void testSetTaskDescription() {
        Task task = new Task(taskID, taskName, taskDescription);
        task.setTaskDescription(taskDescription);
        assertEquals(taskDescription, task.getTaskDescription());
        assertThrows(IllegalArgumentException.class, () ->
                task.setTaskDescription(invalidTaskDescription));
        assertThrows(IllegalArgumentException.class, () ->
                task.setTaskDescription(null));
    }

    @Test
    void testGetTaskID() {
        Task task = new Task(taskID, taskName, taskDescription);
        assertEquals(taskID, task.getTaskID());
    }

}
