import java.io.*;
import java.util.*;
import java.math.*;

class Main {

    static private BigInteger TWO = new BigInteger("2");

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        for(int i = 0; i < n; i++) {
            boolean res = solve(sc.nextBigInteger());
            System.out.println(res ? "Yes." : "No.");
        }
    }

    static boolean solve(BigInteger c) {
        BigInteger low = BigInteger.ONE;
        BigInteger high = c.add(BigInteger.ONE);
        while(high.subtract(low).compareTo(BigInteger.ONE) > 0) {
            BigInteger mid = low.add(high).divide(TWO);
            // low < mid < high
            int order = choose2(mid).compareTo(c);
            if (order == 0) {
                low = mid;
                break;
            }
            else if (order > 0) {
                high = mid;
            }
            else {
                low = mid.add(BigInteger.ONE);
            }
        }
        return choose2(low).equals(c);
    }

    static BigInteger choose2(BigInteger n) {
        return n.multiply(n.add(BigInteger.ONE)).divide(TWO);
    }

}
