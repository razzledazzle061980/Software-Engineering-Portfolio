package test;

import TaskService.Task;
import TaskService.TaskService;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertAll;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static Utility.Util.*;

/**
 * The type Task service test.
 */
public class TaskServiceTest {
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
     * Test get task.
     */
    @Test
    void testGetTask() {
        TaskService.addTask(taskName, taskDescription);
        assertThrows(IllegalArgumentException.class, () -> TaskService.getTask(invalidTaskID));
        assertThrows(IllegalArgumentException.class, () -> TaskService.getTask(null));
    }

    /**
     * Test add task.
     */
    @Test
    void testAddTask() {
        TaskService.addTask(taskName, taskDescription);
        int lastIndex = TaskService.getLastIndex();
        assertAll(
                () -> assertEquals(taskName, Task.getTaskName()),
                () -> assertEquals(taskDescription, Task.getTaskDescription()),
                () -> assertThrows(IllegalArgumentException.class, () -> TaskService.addTask(invalidTaskName, taskDescription)),
                () -> assertThrows(IllegalArgumentException.class, () -> TaskService.addTask(taskName, invalidTaskDescription)),
                () -> assertThrows(IllegalArgumentException.class, () -> TaskService.addTask(null, taskDescription)),
                () -> assertThrows(IllegalArgumentException.class, () -> TaskService.addTask(taskName, null))
        );
    }

    /**
     * Test remove task.
     */
    @Test
    void testRemoveTask() {
        TaskService.addTask(taskName, taskDescription);
        String lastID = TaskService.getLastID();
        assertThrows(IllegalArgumentException.class, () -> TaskService.removeTask(invalidTaskID));
        assertThrows(IllegalArgumentException.class, () -> TaskService.removeTask(null));
        TaskService.removeTask(lastID);
    }

    /**
     * Test update task.
     */
    @Test
    void testUpdateTask() {
        TaskService.addTask(taskName, taskDescription);
        String lastID = TaskService.getLastID();
        assertAll(
                () -> assertThrows(IllegalArgumentException.class, () -> TaskService.updateTask(lastID, invalidTaskName, taskDescription)),
                () -> assertThrows(IllegalArgumentException.class, () -> TaskService.updateTask(lastID, null, taskDescription)),
                () -> assertThrows(IllegalArgumentException.class, () -> TaskService.updateTask(lastID, taskName, invalidTaskDescription)),
                () -> assertThrows(IllegalArgumentException.class, () -> TaskService.updateTask(lastID, taskName, null))
        );
    }

    /**
     * Test update task name.
     */
    @Test
    void testUpdateTaskName() {
        TaskService.addTask(taskName, taskDescription);
        String lastID = TaskService.getLastID();
        TaskService.updateTaskName(lastID, taskName);
        assertAll(
                () -> assertEquals(taskName, TaskService.getTaskList().get(TaskService.getLastIndex()).getTaskName()),
                () -> assertThrows(IllegalArgumentException.class, () -> TaskService.updateTaskName(lastID, invalidTaskName)),
                () -> assertThrows(IllegalArgumentException.class, () -> TaskService.updateTaskName(lastID, null))
        );
    }

    /**
     * Test update task description.
     */
    @Test
    void testUpdateTaskDescription() {
        TaskService.addTask(taskName, taskDescription);
        String lastID = TaskService.getLastID();
        TaskService.updateTaskName(lastID, taskName);
        assertAll(
                () -> assertEquals(taskDescription, TaskService.getTaskList().get(TaskService.getLastIndex()).getTaskDescription()),
                () -> assertThrows(IllegalArgumentException.class, () -> TaskService.updateTaskDescription(lastID, invalidTaskDescription)),
                () -> assertThrows(IllegalArgumentException.class, () -> TaskService.updateTaskDescription(lastID, null))
        );
    }
}
