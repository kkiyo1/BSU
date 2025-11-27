import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Iterator;
import java.util.List;

public class CarList extends Container<Car> {
    private List<Car> cars;
    
    public CarList() {
        this.cars = new ArrayList<>();
        this.size = 0;
    }
    
    @Override
    public void add(Car car) {
        cars.add(car);
        size++;
    }
    
    @Override
    public void remove(Car car) {
        cars.remove(car);
        size--;
    }
    
    @Override
    public void update(Car oldCar, Car newCar) {
        int index = cars.indexOf(oldCar);
        if (index != -1) {
            cars.set(index, newCar);
        }
    }
    
    @Override
    public Iterator<Car> iterator() {
        return cars.iterator();
    }
    
    public List<Car> getCars() {
        return cars;
    }
    
    public void sortByModel() {
        Collections.sort(cars, new Comparator<Car>() {
            @Override
            public int compare(Car c1, Car c2) {
                return c1.getModel().compareTo(c2.getModel());
            }
        });
    }

    public void sortByLiftingCapacity() {
        Collections.sort(cars, new Comparator<Car>() {
            @Override
            public int compare(Car c1, Car c2) {
                return Double.compare(c1.getLiftingCapacity(), c2.getLiftingCapacity());
            }
        });
    }

    public void sortByProductionDate() {
        Collections.sort(cars, new Comparator<Car>() {
            @Override
            public int compare(Car c1, Car c2) {
                return c1.getProductionDate().compareTo(c2.getProductionDate());
            }
        });
    }
}