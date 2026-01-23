package exam;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;

public class Task implements Comparable<Task> {
    private int id;
    private String title;
    private LocalDate deadline;
    private String description;
    private Priority priority;
    
    public enum Priority {
        LOW, MEDIUM, HIGH
    }

    public Task(int id, String title, LocalDate deadline, String description, Priority priority) {
        this.id = id;
        this.title = title;
        this.deadline = deadline;
        this.description = description;
        this.priority = priority;
    }

    public Task(int id, String title, String deadlineStr, String description, String priorityStr) {
        this.id = id;
        this.title = title;
        this.description = description;
        
        this.deadline = parseDeadline(deadlineStr);
        
        try {
            this.priority = Priority.valueOf(priorityStr.toUpperCase());
        } catch (IllegalArgumentException e) {
            this.priority = Priority.MEDIUM;
        }
    }
    
    private LocalDate parseDeadline(String deadlineStr) {
        if (deadlineStr == null || deadlineStr.trim().isEmpty()) {
            return null;
        }
        
        String dateStr = deadlineStr.trim();
        DateTimeFormatter[] formatters = {
            DateTimeFormatter.ofPattern("yyyy-MM-dd"),
            DateTimeFormatter.ofPattern("dd.MM.yyyy"),
            DateTimeFormatter.ofPattern("dd/MM/yyyy"),
            DateTimeFormatter.ofPattern("MM/dd/yyyy"),
            DateTimeFormatter.ISO_LOCAL_DATE
        };
        
        for (DateTimeFormatter formatter : formatters) {
            try {
                return LocalDate.parse(dateStr, formatter);
            } catch (DateTimeParseException e) {
            }
        }
        
        System.err.println("Warning: Could not parse deadline: " + dateStr + " for task: " + title);
        return null;
    }


    public int getId() { return id; }
    public String getTitle() { return title; }
    public LocalDate getDeadline() { return deadline; }
    public String getDescription() { return description; }
    public Priority getPriority() { return priority; }
    
    public boolean isOverdue() {
        if (deadline == null) return false;
        LocalDate today = LocalDate.now();
        return deadline.isBefore(today);
    }
    
    public String getFormattedDeadline() {
        if (deadline == null) return "Not set";
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd.MM.yyyy");
        return deadline.format(formatter);
    }
    
    public String getDeadlineForParsing() {
        if (deadline == null) return "";
        return deadline.format(DateTimeFormatter.ISO_LOCAL_DATE);
    }

    @Override
    public String toString() {
        String deadlineStr = getFormattedDeadline();
        String overdue = isOverdue() ? " [OVERDUE!]" : "";
        return String.format("Task %d: %s%s\n  Deadline: %s\n  Priority: %s\n  Description: %s", 
                id, title, overdue, deadlineStr, priority, description);
    }
    
    public String toFormattedString() {
        return String.format("Task ID: %d\nTitle: %s\nDeadline: %s\nPriority: %s\nDescription: %s\n", 
                id, title, getFormattedDeadline(), priority, description);
    }
    
    public String toCSV() {
        String deadlineStr = (deadline != null) ? getDeadlineForParsing() : "";
        return String.format("%d,\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"", 
                id, title, deadlineStr, description, priority, isOverdue() ? "OVERDUE" : "ACTIVE");
    }

    @Override
    public int compareTo(Task other) {
        if (this.deadline == null && other.deadline == null) return 0;
        if (this.deadline == null) return 1;
        if (other.deadline == null) return -1;
        return this.deadline.compareTo(other.deadline);
    }
    
    public static class PriorityComparator implements java.util.Comparator<Task> {
        @Override
        public int compare(Task t1, Task t2) {
            return t2.priority.compareTo(t1.priority);
        }
    }
    
    public static class DeadlineComparator implements java.util.Comparator<Task> {
        @Override
        public int compare(Task t1, Task t2) {
            return t1.compareTo(t2);
        }
    }
}