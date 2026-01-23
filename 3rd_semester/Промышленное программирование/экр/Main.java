package exam;
import java.io.IOException;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        TaskManager taskManager = new TaskManager();
        Scanner scanner = new Scanner(System.in);
        
        try {
            System.out.println("=== TASK MANAGEMENT APPLICATION ===");
            System.out.println("Current date: " + LocalDate.now());
            
            taskManager.loadFromInputFile();
            taskManager.displayAllTasks();
            
            boolean running = true;
            while (running) {
                System.out.println("\n=== MENU ===");
                System.out.println("1. Show all tasks");
                System.out.println("2. Show overdue tasks");
                System.out.println("3. Sort by priority");
                System.out.println("4. Sort by deadline");
                System.out.println("5. Add new task");
                System.out.println("6. Remove overdue tasks");
                System.out.println("7. Save to output files");
                System.out.println("8. Exit");
                System.out.print("Choose (1-8): ");
                
                String choice = scanner.nextLine();
                
                switch (choice) {
                    case "1":
                        taskManager.displayAllTasks();
                        break;
                        
                    case "2":
                        taskManager.displayOverdueTasks();
                        break;
                        
                    case "3":
                        taskManager.sortByPriority();
                        taskManager.displayAllTasks();
                        break;
                        
                    case "4":
                        taskManager.sortByDeadline();
                        taskManager.displayAllTasks();
                        break;
                        
                    case "5":
                        System.out.print("Task title: ");
                        String title = scanner.nextLine();
                        
                        String deadline = "";
                        while (true) {
                            System.out.print("Deadline (YYYY-MM-DD) or press Enter to skip: ");
                            deadline = scanner.nextLine();
                            if (deadline.isEmpty()) break;
                            
                            try {
                                LocalDate.parse(deadline);
                                break;
                            } catch (DateTimeParseException e) {
                                System.out.println("Invalid date format. Please use YYYY-MM-DD");
                            }
                        }
                        
                        System.out.print("Description: ");
                        String description = scanner.nextLine();
                        
                        System.out.print("Priority (LOW/MEDIUM/HIGH): ");
                        String priority = scanner.nextLine().toUpperCase();
                        
                        if (!priority.equals("LOW") && !priority.equals("MEDIUM") && !priority.equals("HIGH")) {
                            priority = "MEDIUM";
                        }
                        
                        taskManager.addTask(title, deadline, description, priority);
                        break;
                        
                    case "6":
                        int removed = taskManager.removeOverdueTasks();
                        if (removed > 0) {
                            taskManager.displayAllTasks();
                        }
                        break;
                        
                    case "7":
                        taskManager.saveToOutputFile();
                        taskManager.saveToCSVFile();
                        System.out.println("Files saved: output.txt and output.csv");
                        break;
                        
                    case "8":
                        running = false;
                        taskManager.saveToOutputFile();
                        taskManager.saveToCSVFile();
                        System.out.println("Tasks saved. Goodbye!");
                        break;
                        
                    default:
                        System.out.println("Invalid choice.");
                }
            }
            
        } catch (IOException e) {
            System.err.println("Error: " + e.getMessage());
            e.printStackTrace();
        } finally {
            scanner.close();
        }
    }
}