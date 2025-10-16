import java.util.*;
import java.io.*;

class myClass {
    public static void main(String[] args) {
        try {
            BufferedReader reader = new BufferedReader(new FileReader("C:\\Users\\user\\Desktop\\javaPrograms\\lab2\\src\\input.txt"));
            String s1 = reader.readLine();
            String divider = reader.readLine();
            reader.close();
            
            System.out.println("������ ������: " + s1);
            System.out.println("������ ������: " + divider);
            
            Solution.solve(s1, divider);
            
        } catch (IOException e) {
            System.out.println("������ ������ �����: " + e.getMessage());
        }
    }
}

class Solution {
    public static void solve(String s, String divider) {
        try {
            BufferedWriter writer = new BufferedWriter(new FileWriter("output.txt"));
            String[] words;
            if (divider.length() == 1) {
               words = s.split(java.util.regex.Pattern.quote(divider));
            } else {
                StringTokenizer tokenizer = new StringTokenizer(s, divider);
                List<String> tokens = new ArrayList<>();
                while (tokenizer.hasMoreTokens()) {
                    tokens.add(tokenizer.nextToken());
                }
                words = tokens.toArray(new String[0]);
            }
            
            writer.write("����������� �������:");
            writer.newLine();
            for (String word : words) {
                writer.write(word + " ");
            }
            writer.newLine();
            
            // ����� ����� � �������� �������
            ArrayList<String> numbers = new ArrayList<>();
            for (String word : words) {
                try {
                    int num = Integer.parseInt(word, 2);
                    numbers.add(word);
                } catch (NumberFormatException e) {}
            }
            
            writer.write("����� � �������� ������� (������������ � ����������): ");
            writer.newLine();
            for (String num : numbers) {
                writer.write(num + " ");
            }
            writer.newLine();
            
            // ����� ������� �� ����������� ��������� � ���������� ���������� �����
            String timeRegex = "([0-5][0-9]):([01][0-9]|2[0-3]):([0-5][0-9])";
            List<String> timeTokens = new ArrayList<>();
            boolean isAdded = false;
            
            for (int i = 0; i < words.length; i++) {
                if (words[i].matches(timeRegex)) {
                	timeTokens.add(words[i]);
                    int randomNum = (int)(Math.random() * 90) + 10;
                    System.out.println(randomNum);
                    writer.write("��������� �����: " + randomNum);
                    writer.newLine();
                    StringBuilder sb = new StringBuilder(words[i]);
                    sb.insert(words[i].length(), randomNum);
                    writer.write("������� �������� �����: " + words[i]);
                    writer.newLine();
                    words[i] = sb.toString();
                    isAdded = true;
                }
            }
           
            
            StringBuilder resultBuilder = new StringBuilder();
            for (String word : words) {
                resultBuilder.append(word);
            }
            String result1 = resultBuilder.toString();
            
            if (!isAdded) {
                int midIndex = result1.length() / 2;
                int randomNum = (int)(Math.random() * 90) + 10;
              
                StringBuilder sb = new StringBuilder(result1);
                sb.insert(midIndex, randomNum);
                result1 = sb.toString();
            }
            
            writer.write("������ �� ��������� ������: " + result1);
            writer.newLine();
            
            // �������� �����, ������� ���������� � ����� � ����� ���������� �����
            String result2 = removeWord(s, divider);
            writer.write("������ ����� �������� ����������� ����� � ������: " + result2);
            writer.newLine();
            
            writer.close();
            System.out.println("���������� �������� � output.txt");
            
        } catch (IOException e) {
            System.out.println("������ ������ � ����: " + e.getMessage());
        }
    }
    
    public static String removeWord(String input, String divider) {
        String[] words;
        if (divider.length() == 1) {
        	words = input.split(java.util.regex.Pattern.quote(divider));
        } else {
            StringTokenizer tokenizer = new StringTokenizer(input, divider);
            List<String> tokens = new ArrayList<>();
            while (tokenizer.hasMoreTokens()) {
                tokens.add(tokenizer.nextToken());
            }
            words = tokens.toArray(new String[0]);
        }
        
        String shortestDigitWord = null;
        int shortestLength = Integer.MAX_VALUE;
        int wordIndex = -1;
        
        for (int i = 0; i < words.length; i++) {
            String word = words[i];
            if (!word.isEmpty() && Character.isDigit(word.charAt(0))) {
                if (word.length() < shortestLength) {
                    shortestLength = word.length();
                    shortestDigitWord = word;
                    wordIndex = i;
                }
            }
        }
        
        if (shortestDigitWord == null) {
            return input;
        }
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < words.length; i++) {
            if (i != wordIndex) {
                result.append(words[i]);
                if (i < words.length - 1 && i != wordIndex - 1) {
                    if (divider.length() > 0) {
                        result.append(divider.charAt(0));
                    }
                }
            }
        }
        
        return result.toString();
    }
}