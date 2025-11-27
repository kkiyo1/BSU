import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Objects;
import com.fasterxml.jackson.annotation.JsonFormat;

public class Car {
    private int id;
    private String model;
    private String country;
    private double liftingCapacity;
    private double height;
    private double width;
    private double length;
    
    @JsonFormat(shape = JsonFormat.Shape.STRING, pattern = "yyyy-MM-dd")
    private Date productionDate;
    private double price;
    
    public Car() {
        this.id = 0;
        this.model = "none";
        this.country = "none";
        this.liftingCapacity = 0.0;
        this.height = 0.0;
        this.width = 0.0;
        this.length = 0.0;
        this.productionDate = new Date();
        this.price = 0.0;
    }
    
    public Car(String model, String country, double liftingCapacity, 
               double height, double width, double length, Date productionDate, double price) {
        this.model = model;
        this.country = country;
        this.liftingCapacity = liftingCapacity;
        this.height = height;
        this.width = width;
        this.length = length;
        this.productionDate = productionDate;
        this.price = price;
    }
    
    // ������� � �������
    public int getId() { return id; }
    public String getModel() { return model; }
    public String getCountry() { return country; }
    public double getLiftingCapacity() { return liftingCapacity; }
    public double getHeight() { return height; }
    public double getWidth() { return width; }
    public double getLength() { return length; }
    public Date getProductionDate() { return productionDate; }
    public double getPrice() { return price; }
    
    public void setId(int id) { this.id = id; }
    public void setModel(String model) { this.model = model; }
    public void setCountry(String country) { this.country = country; }
    public void setLiftingCapacity(double liftingCapacity) { this.liftingCapacity = liftingCapacity; }
    public void setHeight(double height) { this.height = height; }
    public void setWidth(double width) { this.width = width; }
    public void setLength(double length) { this.length = length; }
    public void setProductionDate(Date productionDate) { this.productionDate = productionDate; }
    public void setPrice(double price) { this.price = price; }
    
    @Override
    public String toString() {
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");
        return String.format("Car{id=%d, model='%s', country='%s', liftingCapacity=%.2f, " +
                           "height=%.2f, width=%.2f, length=%.2f, productionDate=%s, price=%.2f}",
                           id, model, country, liftingCapacity, height, width, length, 
                           dateFormat.format(productionDate), price);
    }
    
    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Car car = (Car) obj;
        return id == car.id;
    }
    
    @Override
    public int hashCode() {
        return Objects.hash(id);
    }
}
