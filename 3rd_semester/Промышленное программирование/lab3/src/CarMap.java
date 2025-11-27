import java.util.Collection;
import java.util.Iterator;
import java.util.Map;
import java.util.TreeMap;

public class CarMap extends Container<Car> {
    private Map<Integer, Car> cars;
    private int nextId;
    
    public CarMap() {
        this.cars = new TreeMap<>();
        this.nextId = 1;
        this.size = 0;
    }
    
    @Override
    public void add(Car car) {
        car.setId(nextId);
        cars.put(nextId, car);
        nextId++;
        size++;
    }
    
    @Override
    public void remove(Car car) {
        cars.remove(car.getId());
        size--;
    }
    
    @Override
    public void update(Car oldCar, Car newCar) {
        newCar.setId(oldCar.getId());
        cars.put(oldCar.getId(), newCar);
    }
    
    @Override
    public Iterator<Car> iterator() {
        return cars.values().iterator();
    }
    
    public Car getById(int id) {
        return cars.get(id);
    }
    
    public void removeById(int id) {
        Car car = cars.remove(id);
        if (car != null) {
            size--;
        }
    }
    
    public Collection<Car> getAllCars() {
        return cars.values();
    }
}