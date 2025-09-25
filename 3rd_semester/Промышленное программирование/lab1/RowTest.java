import static org.junit.Assert.*;
import org.junit.Test;

public class RowTest extends Row {

	@Test
	public void testCommonData() {
	    double result = Row.calculate(5, 0.5);
	    double expected = Math.asin(0.5);
	    assertEquals("Calculation should be close to Math.asin()", expected, result, 0.001);    
	}
	
	@Test
	public void testNegativeCommonDate(){
		 double result = Row.calculate(5, -0.265);
		 double expected = Math.asin(-0.265);
		 assertEquals("Negative calculation should be close to Math.asin()", expected, result, 0.001);
	}	
}