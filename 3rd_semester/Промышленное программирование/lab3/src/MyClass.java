public class MyClass {
    public static void main(String[] args) {
        CarList list = new CarList();
        CarMap map = new CarMap();
        FileHandler fileHandler = new FileHandler();
        Menu menu = new Menu(list, map, fileHandler);
        fileHandler.loadFromFile("cars.txt", list, map); 
        menu.show();
    }
}