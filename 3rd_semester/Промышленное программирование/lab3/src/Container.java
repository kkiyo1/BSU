import java.util.Iterator;

public abstract class Container<T> {
    protected int size;
    
    public int getSize() {
        return size;
    }
    
    public abstract void add(T item);
    public abstract void remove(T item);
    public abstract void update(T oldItem, T newItem);
    public abstract Iterator<T> iterator();
}