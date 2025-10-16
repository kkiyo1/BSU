import org.junit.Test;
import org.junit.Before;
import org.junit.After;
import static org.junit.Assert.*;
import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;

public class test {

    private final ByteArrayOutputStream outContent = new ByteArrayOutputStream();
    private final PrintStream originalOut = System.out;

    @Before
    public void setUpStreams() {
        System.setOut(new PrintStream(outContent));
    }

    @After
    public void restoreStreams() {
        System.setOut(originalOut);
    }

    private void createTestFile(String filename, String content) throws IOException {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(filename))) {
            writer.write(content);
        }
    }

    private String readOutputFile() throws IOException {
        return new String(Files.readAllBytes(Paths.get("output.txt")));
    }

    @Test
    public void testTimeFormatProcessing() throws IOException {
        // Arrange
        createTestFile("input.txt", "meeting.at.30:12:45\n.");
        
        // Act
        myClass.main(new String[]{});
        
        // Assert
        String output = readOutputFile();
        assertTrue(output.contains("30:12:45"));
    }

    @Test
    public void testRemoveWordFunctionality() {
        // Arrange
        String input = "abc 123d 45test 6seven 890xyz";
        String divider = " ";
        
        // Act
        String result = Solution.removeWord(input, divider);
        
        // Assert
        assertFalse(result.contains("123d"));
    }

    @Test
    public void testSingleCharacterDivider() throws IOException {
        createTestFile("input.txt", "word1,word2,word3\n,");
        
        Solution.solve("word1,word2,word3", ",");
        
        // Assert
        String output = readOutputFile();
        assertTrue(output.contains("word1"));
        assertTrue(output.contains("word2"));
        assertTrue(output.contains("word3"));
    }

    @Test
    public void testMultiCharacterDivider() throws IOException {
        // Arrange
        createTestFile("input.txt", "word1;word2;word3\n;");
        
        // Act
        Solution.solve("word1;word2;word3", ";");
        
        // Assert
        String output = readOutputFile();
        assertTrue(output.contains("word1"));
        assertTrue(output.contains("word2"));
        assertTrue(output.contains("word3"));
    }

    @Test
    public void testNoBinaryNumbers() throws IOException {
        // Arrange
        createTestFile("input.txt", "hello world test\n ");
        
        // Act
        Solution.solve("hello world test", " ");
        
        // Assert
        String output = readOutputFile();
        assertTrue(output.contains("Числа в двоичной системе"));
    }

    @Test
    public void testEmptyInput() throws IOException {
        // Arrange
        createTestFile("input.txt", "\n ");
        
        // Act
        Solution.solve("", " ");
        
        // Assert
        String output = readOutputFile();
        assertTrue(output.contains("Разделенные лексемы:"));
    }
}