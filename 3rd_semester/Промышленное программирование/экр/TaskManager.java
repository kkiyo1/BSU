package exam;
import java.io.*;
import java.time.LocalDate;
import java.util.*;

public class TaskManager {
    private List<Task> tasks;
    private int nextId;

    public TaskManager() {
        tasks = new ArrayList<>();
        nextId = 1;
    }

    public void loadFromInputFile() throws IOException {
        String inputFile = "input.txt";
        System.out.println("Loading tasks from: " + inputFile);
        
        File file = new File(inputFile);
        if (!file.exists()) {
            System.out.println("Error: input.txt not found!");
            System.out.println("Creating sample input.txt file...");
            createSampleInputFile();
            System.out.println("Please add your tasks to input.txt and restart the program.");
            System.exit(0);
        }

        BufferedReader reader = new BufferedReader(new FileReader(inputFile));
        String line;
        String currentTitle = "";
        String currentDeadline = "";
        String currentDescription = "";
        String currentPriority = "MEDIUM";
        
        while ((line = reader.readLine()) != null) {
            line = line.trim();
            if (line.isEmpty()) continue;
            
            if (line.toLowerCase().startsWith("title:")) {
                if (!currentTitle.isEmpty()) {
                    tasks.add(new Task(nextId++, currentTitle, currentDeadline, 
                                      currentDescription, currentPriority));
                }
                currentTitle = line.substring(6).trim();
                currentDeadline = "";
                currentDescription = "";
                currentPriority = "MEDIUM";
            } 
            else if (line.toLowerCase().startsWith("deadline:")) {
                currentDeadline = line.substring(9).trim();
            } 
            else if (line.toLowerCase().startsWith("description:")) {
                currentDescription = line.substring(12).trim();
            } 
            else if (line.toLowerCase().startsWith("priority:")) {
                currentPriority = line.substring(9).trim().toUpperCase();
            }
            else if (!line.equalsIgnoreCase("Tasks") && !line.equalsIgnoreCase("Задачи")) {
                tasks.add(new Task(nextId++, line, "", "", "MEDIUM"));
            }
        }
        
        if (!currentTitle.isEmpty()) {
            tasks.add(new Task(nextId++, currentTitle, currentDeadline, 
                              currentDescription, currentPriority));
        }
        
        reader.close();
        System.out.println("Loaded " + tasks.size() + " tasks from " + inputFile);
    }

    public void sortByPriority() {
        tasks.sort(new Task.PriorityComparator());
        System.out.println("Tasks sorted by priority (HIGH to LOW)");
    }

    public void sortByDeadline() {
        tasks.sort(new Task.DeadlineComparator());
        System.out.println("Tasks sorted by deadline (earliest first)");
    }

    public int removeOverdueTasks() {
        int initialSize = tasks.size();
        Iterator<Task> iterator = tasks.iterator();
        int removedCount = 0;
        
        while (iterator.hasNext()) {
            Task task = iterator.next();
            if (task.isOverdue()) {
                System.out.println("Removing overdue task: " + task.getTitle());
                iterator.remove();
                removedCount++;
            }
        }
        
        System.out.println("Removed " + removedCount + " overdue tasks");
        return removedCount;
    }

    public void addTask(String title, String deadlineStr, String description, String priorityStr) {
        Task task = new Task(nextId++, title, deadlineStr, description, priorityStr);
        tasks.add(task);
        System.out.println("Task added: " + title);
    }

    public void saveToOutputFile() throws IOException {
        String outputFile = "output.txt";
        try (PrintWriter writer = new PrintWriter(new FileWriter(outputFile))) {
            writer.println("=== TASK LIST ===");
            writer.println("Total tasks: " + tasks.size());
            writer.println("Date: " + LocalDate.now());
            writer.println("=================\n");
            
            for (Task task : tasks) {
                writer.println(task.toFormattedString());
                writer.println("------------------------");
            }
            
            long overdueCount = tasks.stream().filter(Task::isOverdue).count();
            writer.println("\n=== STATISTICS ===");
            writer.println("Overdue tasks: " + overdueCount);
            writer.println("Active tasks: " + (tasks.size() - overdueCount));
        }
        System.out.println("Tasks saved to: " + outputFile);
    }

    public void saveToCSVFile() throws IOException {
        String csvFile = "output.csv";
        try (PrintWriter writer = new PrintWriter(new FileWriter(csvFile))) {
            writer.println("ID,Title,Deadline,Description,Priority,Status");
            
            for (Task task : tasks) {
                writer.println(task.toCSV());
            }
        }
        System.out.println("Tasks saved to CSV: " + csvFile);
    }

    public void displayAllTasks() {
        System.out.println("\n=== ALL TASKS (" + tasks.size() + ") ===");
        if (tasks.isEmpty()) {
            System.out.println("No tasks found.");
        } else {
            for (Task task : tasks) {
                System.out.println(task);
                System.out.println("---");
            }
        }
        System.out.println("================\n");
    }

    public void displayOverdueTasks() {
        System.out.println("\n=== OVERDUE TASKS ===");
        boolean hasOverdue = false;
        for (Task task : tasks) {
            if (task.isOverdue()) {
                System.out.println(task);
                System.out.println("---");
                hasOverdue = true;
            }
        }
        if (!hasOverdue) {
            System.out.println("No overdue tasks.");
        }
        System.out.println("================\n");
    }

    private void createSampleInputFile() throws IOException {
        LocalDate today = LocalDate.now();
        
        try (PrintWriter writer = new PrintWriter(new FileWriter("input.txt"))) {
            writer.println("Tasks");
            writer.println("Title: Prepare quarterly report");
            writer.println("Deadline: " + today.plusDays(7)); // +7 дней от сегодня
            writer.println("Description: Financial report for Q4 2023");
            writer.println("Priority: HIGH");
            writer.println();
            writer.println("Title: Team meeting");
            writer.println("Deadline: " + today.plusDays(14)); // +14 дней
            writer.println("Description: Weekly status update");
            writer.println("Priority: MEDIUM");
            writer.println();
            writer.println("Title: Update documentation");
            writer.println("Deadline: " + today.plusDays(3)); // +3 дня
            writer.println("Description: Update API documentation");
            writer.println("Priority: LOW");
            writer.println();
            writer.println("Title: Call client");
            writer.println("Deadline: " + today.plusDays(10)); // +10 дней
            writer.println("Description: Discuss project requirements");
            writer.println("Priority: MEDIUM");
            writer.println();
            writer.println("Title: Fix critical bug");
            writer.println("Deadline: " + today.minusDays(2)); // -2 дня (просроченная)
            writer.println("Description: Urgent bug fix in production");
            writer.println("Priority: HIGH");
        }
    }
}