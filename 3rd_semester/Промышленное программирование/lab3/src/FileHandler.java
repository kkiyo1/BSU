import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Iterator;
import java.util.List;
import java.io.FileInputStream;
import java.io.FileOutputStream;

import java.io.File;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;
import java.io.FileInputStream;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.SerializationFeature;

public class FileHandler {
    private SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");
    private ObjectMapper jsonMapper;
    
    public FileHandler() {
        this.jsonMapper = new ObjectMapper();
        this.jsonMapper.enable(SerializationFeature.INDENT_OUTPUT);
        this.jsonMapper.setDateFormat(new SimpleDateFormat("yyyy-MM-dd"));
    }
    
    public void zipCarList(String zipFilename, CarList carList) {
        try {
            File tempFile = File.createTempFile("cars", ".txt");
            tempFile.deleteOnExit();
            
            try (PrintWriter writer = new PrintWriter(new FileWriter(tempFile))) {
                Iterator<Car> iterator = carList.iterator();
                while (iterator.hasNext()) {
                    Car car = iterator.next();
                    writer.println(carToString(car));
                }
            }
            
            try (FileOutputStream fos = new FileOutputStream(zipFilename);
                 ZipOutputStream zos = new ZipOutputStream(fos)) {
                
                ZipEntry zipEntry = new ZipEntry("cars.txt");
                zos.putNextEntry(zipEntry);
                
                try (FileInputStream fis = new FileInputStream(tempFile)) {
                    byte[] buffer = new byte[1024];
                    int length;
                    while ((length = fis.read(buffer)) > 0) {
                        zos.write(buffer, 0, length);
                    }
                }
                
                zos.closeEntry();
            }
            
            System.out.println("Car list successfully zipped to: " + zipFilename);
            
        } catch (Exception e) {
            String errorMsg = "Error creating zip archive: " + e.getMessage();
            System.err.println(errorMsg);
            e.printStackTrace();
        }
    }
    
    public void vernamCipher(String filename, String key, CarList carList) {
        try {
            StringBuilder allData = new StringBuilder();
            Iterator<Car> iterator = carList.iterator();
            while (iterator.hasNext()) {
                Car car = iterator.next();
                allData.append(carToString(car)).append("\n");
            }
            
            byte[] dataBytes = allData.toString().getBytes("UTF-8");
            byte[] keyBytes = key.getBytes("UTF-8");
            
            byte[] encryptedBytes = new byte[dataBytes.length];
            for (int i = 0; i < dataBytes.length; i++) {
                encryptedBytes[i] = (byte) (dataBytes[i] ^ keyBytes[i % keyBytes.length]);
            }
            
            try (FileOutputStream fos = new FileOutputStream(filename)) {
                fos.write(encryptedBytes);
            }
            
            System.out.println("Data successfully ciphered and saved to: " + filename);
            
        } catch (Exception e) {
            String errorMsg = "Error during Vernam cipher: " + e.getMessage();
            System.err.println(errorMsg);
            e.printStackTrace();
        }
    }
    
    public void vernamDecipher(String filename, String key) {
        try {
            byte[] encryptedData;
            try (FileInputStream fis = new FileInputStream(filename)) {
                encryptedData = fis.readAllBytes();
            }
            
            byte[] keyBytes = key.getBytes("UTF-8");
            
            byte[] decryptedBytes = new byte[encryptedData.length];
            for (int i = 0; i < encryptedData.length; i++) {
                decryptedBytes[i] = (byte) (encryptedData[i] ^ keyBytes[i % keyBytes.length]);
            }
            
            try (FileOutputStream fos = new FileOutputStream(filename)) {
                fos.write(decryptedBytes);
            }
            
            System.out.println("Data successfully deciphered and saved to: " + filename);
            
        } catch (Exception e) {
            String errorMsg = "Error during Vernam decipher: " + e.getMessage();
            System.err.println(errorMsg);
            e.printStackTrace();
        }
    }
    
    public void loadFromFile(String filename, CarList carList, CarMap carMap) {
        String lowerCaseFilename = filename.toLowerCase();
        if (lowerCaseFilename.endsWith(".xml")) {
            loadFromXML(filename, carList, carMap);
        } else if (lowerCaseFilename.endsWith(".json")) {
            loadFromJSON(filename, carList, carMap);
        } else {
            loadFromTextFile(filename, carList, carMap);
        }
    }
    
    public void saveToFile(String filename, CarList carList) {
        String lowerCaseFilename = filename.toLowerCase();
        if (lowerCaseFilename.endsWith(".xml")) {
            saveToXML(filename, carList);
        } else if (lowerCaseFilename.endsWith(".json")) {
            saveToJSON(filename, carList);
        } else {
            saveToTextFile(filename, carList);
        }
    }
    
    private void loadFromJSON(String filename, CarList carList, CarMap carMap) {
        try {
            File jsonFile = new File(filename);
            if (!jsonFile.exists()) {
                System.err.println("JSON file not found: " + filename);
                return;
            }
            
            List<Car> cars = jsonMapper.readValue(jsonFile, new TypeReference<List<Car>>() {});
            
            for (Car car : cars) {
                carList.add(car);
                carMap.add(car);
            }
            
            System.out.println("Successfully loaded " + cars.size() + " cars from JSON file: " + filename);
            
        } catch (Exception e) {
            String errorMsg = "Error reading JSON file: " + e.getMessage();
            System.err.println(errorMsg);
            e.printStackTrace();
        }
    }
    
    private void saveToJSON(String filename, CarList carList) {
        try {
            List<Car> cars = new ArrayList<>();
            Iterator<Car> iterator = carList.iterator();
            while (iterator.hasNext()) {
                cars.add(iterator.next());
            }
            
            jsonMapper.writeValue(new File(filename), cars);
            System.out.println("Data successfully saved to JSON file: " + filename);
            
        } catch (Exception e) {
            String errorMsg = "Error writing JSON file: " + e.getMessage();
            System.err.println(errorMsg);
            e.printStackTrace();
        }
    }
    
   
    private void loadFromTextFile(String filename, CarList carList, CarMap carMap) {
        try (BufferedReader reader = new BufferedReader(new FileReader(filename))) {
            String line;
            int lineNumber = 0;
            
            while ((line = reader.readLine()) != null) {
                lineNumber++;
                try {
                    Car car = parseCarFromString(line);
                    if (car != null) {
                        carList.add(car);
                        carMap.add(car);
                    }
                } catch (Exception e) {
                    String errorMsg = "Error parsing line " + lineNumber + ": " + line + " - " + e.getMessage();
                    System.err.println(errorMsg);
                }
            }
        } catch (IOException e) {
            String errorMsg = "Error reading file: " + e.getMessage();
            System.err.println(errorMsg);
        }
    }
    
    private void saveToTextFile(String filename, CarList carList) {
        try (PrintWriter writer = new PrintWriter(new FileWriter(filename))) {
            Iterator<Car> iterator = carList.iterator();
            while (iterator.hasNext()) {
                Car car = iterator.next();
                writer.println(carToString(car));
            }
        } catch (IOException e) {
            String errorMsg = "Error writing to file: " + e.getMessage();
            System.err.println(errorMsg);
        }
    }
    
    public void loadFromXML(String filename, CarList carList, CarMap carMap) {
        try {
            File xmlFile = new File(filename);
            DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
            DocumentBuilder builder = factory.newDocumentBuilder();
            Document document = builder.parse(xmlFile);
            
            document.getDocumentElement().normalize();
            
            NodeList carNodes = document.getElementsByTagName("car");
            
            for (int i = 0; i < carNodes.getLength(); i++) {
                Node node = carNodes.item(i);
                
                if (node.getNodeType() == Node.ELEMENT_NODE) {
                    try {
                        Car car = parseCarFromXML((Element) node);
                        if (car != null) {
                            carList.add(car);
                            carMap.add(car);
                        }
                    } catch (Exception e) {
                        String errorMsg = "Error parsing car element " + (i + 1) + ": " + e.getMessage();
                        System.err.println(errorMsg);
                    }
                }
            }
            
        } catch (Exception e) {
            String errorMsg = "Error reading XML file: " + e.getMessage();
            System.err.println(errorMsg);
        }
    }
    
    public void saveToXML(String filename, CarList carList) {
        try {
            DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
            DocumentBuilder builder = factory.newDocumentBuilder();
            Document document = builder.newDocument();
            
            Element rootElement = document.createElement("cars");
            document.appendChild(rootElement);
            
            Iterator<Car> iterator = carList.iterator();
            while (iterator.hasNext()) {
                Car car = iterator.next();
                Element carElement = createCarElement(document, car);
                rootElement.appendChild(carElement);
            }
            
            TransformerFactory transformerFactory = TransformerFactory.newInstance();
            Transformer transformer = transformerFactory.newTransformer();
            transformer.setOutputProperty(javax.xml.transform.OutputKeys.INDENT, "yes");
            transformer.setOutputProperty("{http://xml.apache.org/xslt}indent-amount", "4");
            
            DOMSource source = new DOMSource(document);
            StreamResult result = new StreamResult(new File(filename));
            
            transformer.transform(source, result);
            System.out.println("Data successfully saved to XML file: " + filename);
            
        } catch (Exception e) {
            String errorMsg = "Error writing XML file: " + e.getMessage();
            System.err.println(errorMsg);
        }
    }
    
    private Car parseCarFromXML(Element carElement) {
        try {
            String model = getElementText(carElement, "model");
            String country = getElementText(carElement, "country");
            double liftingCapacity = parseDoubleWithValidation(getElementText(carElement, "liftingCapacity"));
            double height = parseDoubleWithValidation(getElementText(carElement, "height"));
            double width = parseDoubleWithValidation(getElementText(carElement, "width"));
            double length = parseDoubleWithValidation(getElementText(carElement, "length"));
            Date productionDate = dateFormat.parse(getElementText(carElement, "productionDate"));
            double price = parseDoubleWithValidation(getElementText(carElement, "price"));
            
            return new Car(model, country, liftingCapacity, height, width, length, productionDate, price);
            
        } catch (Exception e) {
            throw new IllegalArgumentException("Failed to parse car from XML: " + e.getMessage());
        }
    }
    
    private Element createCarElement(Document document, Car car) {
        Element carElement = document.createElement("car");
        
        addTextElement(document, carElement, "model", car.getModel());
        addTextElement(document, carElement, "country", car.getCountry());
        addTextElement(document, carElement, "liftingCapacity", String.format("%.2f", car.getLiftingCapacity()));
        addTextElement(document, carElement, "height", String.format("%.2f", car.getHeight()));
        addTextElement(document, carElement, "width", String.format("%.2f", car.getWidth()));
        addTextElement(document, carElement, "length", String.format("%.2f", car.getLength()));
        addTextElement(document, carElement, "productionDate", dateFormat.format(car.getProductionDate()));
        addTextElement(document, carElement, "price", String.format("%.2f", car.getPrice()));
        
        return carElement;
    }
    
    private String getElementText(Element parent, String tagName) {
        NodeList nodeList = parent.getElementsByTagName(tagName);
        if (nodeList.getLength() > 0) {
            return nodeList.item(0).getTextContent();
        }
        throw new IllegalArgumentException("Missing element: " + tagName);
    }
    
    private void addTextElement(Document document, Element parent, String tagName, String textContent) {
        Element element = document.createElement(tagName);
        element.appendChild(document.createTextNode(textContent));
        parent.appendChild(element);
    }
    
    private Car parseCarFromString(String line) {
        try {
            String[] parts = line.split(",");
            if (parts.length != 8) {
                throw new IllegalArgumentException("Invalid number of fields");
            }
            
            String model = parts[0].trim();
            String country = parts[1].trim();
            double liftingCapacity = parseDoubleWithValidation(parts[2].trim());
            double height = parseDoubleWithValidation(parts[3].trim());
            double width = parseDoubleWithValidation(parts[4].trim());
            double length = parseDoubleWithValidation(parts[5].trim());
            Date productionDate = dateFormat.parse(parts[6].trim());
            double price = parseDoubleWithValidation(parts[7].trim());
            
            return new Car(model, country, liftingCapacity, height, width, length, productionDate, price);
            
        } catch (Exception e) {
            throw new IllegalArgumentException("Failed to parse car data: " + e.getMessage());
        }
    }
    
    private double parseDoubleWithValidation(String value) {
        try {
            double result = Double.parseDouble(value);
            if (result < 0) {
                throw new IllegalArgumentException("Negative value not allowed: " + value);
            }
            return result;
        } catch (NumberFormatException e) {
            throw new IllegalArgumentException("Invalid number format: " + value);
        }
    }
    
    private String carToString(Car car) {
        return String.format("%s, %s, %.2f, %.2f, %.2f, %.2f, %s, %.2f",
                           car.getModel(), car.getCountry(), car.getLiftingCapacity(),
                           car.getHeight(), car.getWidth(), car.getLength(),
                           dateFormat.format(car.getProductionDate()), car.getPrice());
    }
}
