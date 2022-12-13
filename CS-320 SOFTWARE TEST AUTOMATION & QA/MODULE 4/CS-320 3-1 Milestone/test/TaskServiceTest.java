package test;

import milestone.TaskService;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

public class TaskServiceTest {
    protected static TaskService service;

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
    void testAddTask() {
        service = new TaskService();
        TaskService.addTask(taskName, taskDescription);
        Integer lastIndex = service.getLastIndex();
        assertEquals(taskName, TaskService.getTaskList().get(lastIndex).getTaskName());
        assertEquals(taskDescription, TaskService.getTaskList().get(lastIndex).getTaskDescription());
    }

    @Test
    void testGetTask() {
        TaskService.addTask(taskName, taskDescription);
        String lastID = service.getLastID();
        assertThrows(IllegalArgumentException.class, () ->
                TaskService.getTask(invalidTaskID));
        assertThrows(IllegalArgumentException.class, () ->
                TaskService.getTask(null));
    }

    @Test
    void testRemoveTask() {
        TaskService.addTask(taskName, taskDescription);
        String lastID = service.getLastID();
        assertThrows(IllegalArgumentException.class, () ->
                TaskService.removeTask(invalidTaskID));
        assertThrows(IllegalArgumentException.class, () ->
                TaskService.removeTask(null));
    }

    @Test
    void testUpdateTask() {
        TaskService.addTask(taskName, taskDescription);
        String lastID = service.getLastID();
        assertThrows(IllegalArgumentException.class, () ->
                TaskService.updateTask(lastID, invalidTaskName, taskDescription));
        assertThrows(IllegalArgumentException.class, () ->
                TaskService.updateTask(lastID, null, taskDescription));
        assertThrows(IllegalArgumentException.class, () ->
                TaskService.updateTask(lastID, taskName, invalidTaskDescription));
        assertThrows(IllegalArgumentException.class, () ->
                TaskService.updateTask(lastID, taskName, null));
    }

    @Test
    void testUpdateTaskName() {
        TaskService.addTask(taskName, taskDescription);
        String lastID = service.getLastID();
        assertThrows(IllegalArgumentException.class, () ->
                TaskService.updateTaskName(lastID, invalidTaskName));
        assertThrows(IllegalArgumentException.class, () ->
                TaskService.updateTaskName(lastID, null));
    }

    @Test
    void testUpdateTaskDescription() {
        TaskService.addTask(taskName, taskDescription);
        String lastID = service.getLastID();
        assertThrows(IllegalArgumentException.class, () ->
                TaskService.updateTaskDescription(lastID, invalidTaskDescription));
        assertThrows(IllegalArgumentException.class, () ->
                TaskService.updateTaskDescription(lastID, null));
    }

    @Test
    void testAddTaskInvalidName() {
        assertThrows(IllegalArgumentException.class, () ->
                TaskService.addTask(invalidTaskName, taskDescription));
        assertThrows(IllegalArgumentException.class, () ->
                TaskService.addTask(null, taskDescription));
    }

    @Test
    void testAddTaskInvalidDescription() {
        assertThrows(IllegalArgumentException.class, () ->
                TaskService.addTask(taskName, invalidTaskDescription));
        assertThrows(IllegalArgumentException.class, () ->
                TaskService.addTask(taskName, null));
    }
    /**
     * The Task id.
     */
}
