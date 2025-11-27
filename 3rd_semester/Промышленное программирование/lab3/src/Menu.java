import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Iterator;
import java.util.Scanner;

public class Menu {
    private CarList carList;
    private CarMap carMap;
    private FileHandler fileHandler;
    private Scanner scanner;
    
    public Menu(CarList carList, CarMap carMap, FileHandler fileHandler) {
        this.carList = carList;
        this.carMap = carMap;
        this.fileHandler = fileHandler;
        this.scanner = new Scanner(System.in);
    }
    
    public void show() {
        while (true) {
            System.out.println("\n=== Car Management System ===");
            System.out.println("1. Add new car");
            System.out.println("2. Edit car");
            System.out.println("3. Remove car");
            System.out.println("4. Show all cars");
            System.out.println("5. Sort cars");
            System.out.println("6. Save to file");
            System.out.println("7. Load from file");
            System.out.println("8. Cipher");
            System.out.println("9. Decipher");
            System.out.println("10. Archieve to .zip");
            System.out.println("11. Exit");
            System.out.print("Choose option: ");
            
            try {
                int choice = Integer.parseInt(scanner.nextLine());
                
                switch (choice) {
                    case 1: 
                        addCar();
                        break;
                    case 2: 
                        editCar();
                        break;
                    case 3: 
                        removeCar();
                        break;
                    case 4: 
                        showAllCars();
                        break;
                    case 5: 
                        sortCars();
                        break;
                    case 6: 
                        saveToFile();
                        break;
                    case 7: 
                        loadFromFile();
                        break;
                    case 8:
                    	cipher();
                    	break;
                    case 9:
                    	decipher();
                    	break;
                    case 10:
                    	zipCarList();
                    case 11: 
                        System.out.println("Goodbye!");
                        return;
                    default: 
                        System.out.println("Invalid option!");
                        break;
                }
            } catch (NumberFormatException e) {
                System.out.println("Please enter a valid number!");
            }
        }
    }
    
    private void addCar() {
        try {
            System.out.print("Enter model: ");
            String model = scanner.nextLine();
            
            System.out.print("Enter country: ");
            String country = scanner.nextLine();
            
            System.out.print("Enter lifting capacity: ");
            double liftingCapacity = Double.parseDouble(scanner.nextLine());
            
            System.out.print("Enter height: ");
            double height = Double.parseDouble(scanner.nextLine());
            
            System.out.print("Enter width: ");
            double width = Double.parseDouble(scanner.nextLine());
            
            System.out.print("Enter length: ");
            double length = Double.parseDouble(scanner.nextLine());
            
            System.out.print("Enter production date (yyyy-MM-dd): ");
            String dateStr = scanner.nextLine();
            Date productionDate = new SimpleDateFormat("yyyy-MM-dd").parse(dateStr);
            
            System.out.print("Enter price: ");
            double price = Double.parseDouble(scanner.nextLine());
            
            Car car = new Car(model, country, liftingCapacity, height, width, length, productionDate, price);
            carList.add(car);
            carMap.add(car);
            
            System.out.println("Car added successfully!");
            
        } catch (Exception e) {
            System.out.println("Error adding car: " + e.getMessage());
        }
    }
    
    private void editCar() {
        showAllCars();
        if (carList.getSize() == 0) return;
        
        System.out.print("Enter car ID to edit: ");
        try {
            int id = Integer.parseInt(scanner.nextLine());
            Car car = carMap.getById(id);
            
            if (car == null) {
                System.out.println("Car not found!");
                return;
            }
            
            Car editedCar = new Car(car.getModel(), car.getCountry(), car.getLiftingCapacity(),
                                  car.getHeight(), car.getWidth(), car.getLength(),
                                  car.getProductionDate(), car.getPrice());
            editedCar.setId(car.getId());
            
            System.out.println("Editing car: " + car);
            System.out.println("Leave field empty to keep current value");
            
            System.out.print("Enter new model [" + car.getModel() + "]: ");
            String model = scanner.nextLine();
            if (!model.isEmpty()) editedCar.setModel(model);
            
            System.out.print("Enter new country [" + car.getCountry() + "]: ");
            String country = scanner.nextLine();
            if (!country.isEmpty()) editedCar.setCountry(country);
            
            System.out.print("Enter new lifting capacity [" + car.getLiftingCapacity() + "]: ");
            String liftingCapacityStr = scanner.nextLine();
            if (!liftingCapacityStr.isEmpty()) {
                editedCar.setLiftingCapacity(Double.parseDouble(liftingCapacityStr));
            }
            
            System.out.print("Enter new height [" + car.getHeight() + "]: ");
            String heightStr = scanner.nextLine();
            if (!heightStr.isEmpty()) {
                editedCar.setHeight(Double.parseDouble(heightStr));
            }
            
            System.out.print("Enter new width [" + car.getWidth() + "]: ");
            String widthStr = scanner.nextLine();
            if (!widthStr.isEmpty()) {
                editedCar.setWidth(Double.parseDouble(widthStr));
            }
            
            System.out.print("Enter new length [" + car.getLength() + "]: ");
            String lengthStr = scanner.nextLine();
            if (!lengthStr.isEmpty()) {
                editedCar.setLength(Double.parseDouble(lengthStr));
            }
            
            System.out.print("Enter new production date (yyyy-MM-dd) [" + 
                           new SimpleDateFormat("yyyy-MM-dd").format(car.getProductionDate()) + "]: ");
            String dateStr = scanner.nextLine();
            if (!dateStr.isEmpty()) {
                editedCar.setProductionDate(new SimpleDateFormat("yyyy-MM-dd").parse(dateStr));
            }
            
            System.out.print("Enter new price [" + car.getPrice() + "]: ");
            String priceStr = scanner.nextLine();
            if (!priceStr.isEmpty()) {
                editedCar.setPrice(Double.parseDouble(priceStr));
            }
            
            carList.update(car, editedCar);
            carMap.update(car, editedCar);
            System.out.println("Car updated successfully!");
            
        } catch (NumberFormatException e) {
            System.out.println("Invalid ID format!");
        } catch (Exception e) {
            System.out.println("Error editing car: " + e.getMessage());
        }
    }
    
    private void removeCar() {
        showAllCars();
        if (carList.getSize() == 0) return;
        
        System.out.print("Enter car ID to remove: ");
        try {
            int id = Integer.parseInt(scanner.nextLine());
            Car car = carMap.getById(id);
            
            if (car != null) {
                carList.remove(car);
                carMap.remove(car);
                System.out.println("Car removed successfully!");
            } else {
                System.out.println("Car not found!");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid ID format!");
        }
    }
    
    private void showAllCars() {
        System.out.println("\n=== All Cars ===");
        if (carList.getSize() == 0) {
            System.out.println("No cars available.");
            return;
        }
        
        Iterator<Car> iterator = carList.iterator();
        while (iterator.hasNext()) {
            System.out.println(iterator.next());
        }
    }
    
    private void sortCars() {
        if (carList.getSize() == 0) {
            System.out.println("No cars to sort!");
            return;
        }
        
        System.out.println("\n=== Sort Options ===");
        System.out.println("1. Sort by model");
        System.out.println("2. Sort by lifting capacity");
        System.out.println("3. Sort by production date");
        System.out.print("Choose sort option: ");
        
        try {
            int choice = Integer.parseInt(scanner.nextLine());
            
            switch (choice) {
                case 1:
                    carList.sortByModel();
                    System.out.println("Sorted by model!");
                    break;
                case 2:
                    carList.sortByLiftingCapacity();
                    System.out.println("Sorted by lifting capacity!");
                    break;
                case 3:
                    carList.sortByProductionDate();
                    System.out.println("Sorted by production date!");
                    break;
                default:
                    System.out.println("Invalid option!");
                    return;
            }
            showAllCars();
        } catch (NumberFormatException e) {
            System.out.println("Please enter a valid number!");
        }
    }
    
    private void saveToFile() {
        if (carList.getSize() == 0) {
            System.out.println("No cars to save!");
            return;
        }
        
        System.out.print("Enter filename to save: ");
        String filename = scanner.nextLine();
        fileHandler.saveToFile(filename, carList);
        System.out.println("Data saved to " + filename);
    }
        
    private void loadFromFile() {
        System.out.print("Enter filename to load: ");
        String filename = scanner.nextLine();
        
        CarList newCarList = new CarList();
        CarMap newCarMap = new CarMap();
        
        fileHandler.loadFromFile(filename, newCarList, newCarMap);
        
        this.carList = newCarList;
        this.carMap = newCarMap;
        
        System.out.println("Data loaded from " + filename);
        System.out.println("Loaded " + carList.getSize() + " cars");
    }
    
    private void cipher() {
        System.out.print("Enter filename to save: ");
        String filename = scanner.nextLine();
        System.out.print("Enter key to cipher: ");
        String key = scanner.nextLine();
        fileHandler.vernamCipher(filename, key, carList);
        System.out.println("Ciphered data saved to " + filename);
    }
    
    private void decipher() {
    	System.out.print("Enter filename with ciphered text: ");
        String filename = scanner.nextLine();
        System.out.print("Enter key to cipher: ");
        String key = scanner.nextLine();
        fileHandler.vernamDecipher(filename, key);
        System.out.println("File " + filename + " deciphered");
    }
    
    private void zipCarList() {
        if (carList.getSize() == 0) {
            System.out.println("No cars to zip!");
            return;
        }
        
        System.out.print("Enter zip filename (with .zip extension): ");
        String filename = scanner.nextLine();
        fileHandler.zipCarList(filename, carList);
        System.out.println("Car list zipped to " + filename);
    }
}