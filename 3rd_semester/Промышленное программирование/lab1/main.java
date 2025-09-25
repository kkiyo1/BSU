import java.util.Scanner;
import java.util.Formatter;
import java.math.BigDecimal;
import java.math.BigInteger;

class myClass {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int choice = -1;
        System.out.println("Common data - 1\nBig data - 2\n");
        choice = input.nextInt();
        if(1 == choice){
            int k = 0;
            while (k <= 0) {
                System.out.println("Enter positive k: ");
                k = input.nextInt();
            }
            double x = -2;
            while (x < -1 || x > 1) {
                System.out.println("Enter x (-1; 1): ");
                x = input.nextDouble();
            }
            Formatter formatter = new Formatter();
            formatter.format("k (octal): %#o%n", k);
            formatter.format("k (hex): %x%n", k);
            formatter.format("x = %+6." + (k + 1) + "f%n", x);
            formatter.format("Result = %+6." + (k + 1) + "f%n", Row.calculate(k, x));
            
            System.out.println("\n=== Formatted Output ===");
            System.out.print(formatter);
            System.out.println("\n========================");
            
            System.out.println("My result: " + Row.calculate(k, x));
            System.out.println("Default function result: " + Math.asin(x));
            
            formatter.close();
        }
        else{
            BigInteger k = BigInteger.ZERO;
            while (k.compareTo(BigInteger.ZERO) <= 0) {
                System.out.println("Enter positive k: ");
                k = input.nextBigInteger();
            }
            
            BigDecimal x = new BigDecimal("-2");
            BigDecimal lowerBound = new BigDecimal("-1");
            BigDecimal upperBound = new BigDecimal("1");
            
            while (x.compareTo(lowerBound) < 0 || x.compareTo(upperBound) > 0) {
                System.out.println("Enter x (-1; 1): ");
                x = input.nextBigDecimal();
            }
            
            Formatter formatter = new Formatter();
            formatter.format("k (octal): %s%n", k.toString(8));
            formatter.format("k (hex): %s%n", k.toString(16));
            formatter.format("x = %s%n", x.toPlainString());
            
            BigDecimal result = Row.calculateBig(k, x);
            formatter.format("Result = %s%n", result.toPlainString());
            
            System.out.println("\n=== Formatted Output (BigDecimal) ===");
            System.out.print(formatter);
            System.out.println("\n===================================");
            
            System.out.println("My result: " + result.toPlainString());
            formatter.close();
        }
        input.close();
    }
}

class Row{
    public static double calculate(int k, double x){
        double eps = Math.pow(10.0, -k);
        double sum = x;
        double term = x;
        int n = 1;
        while (Math.abs(term) >= eps) {
            double coefficient = (double)(2 * n - 1) / (2 * n);
            term = term * coefficient * x * x * (2 * n - 1) / (2 * n + 1);
            sum += term;
            n++;
        }
        return sum;
    }
    
    public static BigDecimal calculateBig(BigInteger k, BigDecimal x) {
        int scale = k.intValue() + 20;
        
        BigDecimal eps = BigDecimal.ONE.divide(
            BigDecimal.TEN.pow(k.intValue()), scale, BigDecimal.ROUND_HALF_UP
        );
        
        BigDecimal sum = x;
        BigDecimal term = x;
        BigInteger n = BigInteger.ONE;
        BigDecimal xSquared = x.multiply(x);
        
        while (term.abs().compareTo(eps) >= 0) {
            BigInteger twoN = n.multiply(BigInteger.valueOf(2));
            BigInteger twoNMinusOne = twoN.subtract(BigInteger.ONE);
            BigInteger twoNPlusOne = twoN.add(BigInteger.ONE);
            
            //term * x² * (2n-1)² / (2n * (2n+1))
            BigDecimal numerator = new BigDecimal(twoNMinusOne.pow(2));
            BigDecimal denominator = new BigDecimal(twoN.multiply(twoNPlusOne));
            
            term = term.multiply(xSquared)
                      .multiply(numerator)
                      .divide(denominator, scale, BigDecimal.ROUND_HALF_UP);
            
            sum = sum.add(term);
            n = n.add(BigInteger.ONE);
        }
        
        return sum.setScale(k.intValue(), BigDecimal.ROUND_HALF_UP);
    }
}