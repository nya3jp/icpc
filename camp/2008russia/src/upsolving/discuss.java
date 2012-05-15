import java.io.*;
import java.util.*;
import java.math.*;

public class discuss {

    public static final BigInteger TWO = new BigInteger("2");

    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(new FileInputStream("discuss.in"));

        BigInteger res = (new discuss()).run(sc.nextBigInteger());
        PrintWriter out = new PrintWriter(new FileOutputStream("discuss.out"));
        out.println(res);
        out.flush();
        out.close();
    }

    BigInteger run(BigInteger z) {

        BigInteger res = z;
        BigInteger last_n = z;
        for(int k = 1; ; k++) {
            //System.err.printf("k=%d\n", k);
            BigInteger zk = z.multiply(factorial(new BigInteger(Integer.toString(k)), k));
            BigInteger n = findRoot(zk, new BigInteger(Integer.toString(k)), last_n, k);
            //System.out.printf("k=%d, zk=%s, n=%s, nPk=%s\n",
            //k, zk, n, factorial(n, k));
            if (factorial(n, k).equals(zk)) {
                //System.out.printf("   OK!\n");
                if (n.compareTo(res) < 0)
                    res = n;
            }
            if (n.compareTo(new BigInteger(Integer.toString(k)).multiply(TWO)) < 0)
                break;
            last_n = n;
        }

        return res;
    }

    static BigInteger factorial(BigInteger n, int k) {
        BigInteger r = BigInteger.ONE;
        for(int i = 0; i < k; i++) {
            r = r.multiply(n);
            n = n.subtract(BigInteger.ONE);
        }
        return r;
    }

    static BigInteger findRoot(BigInteger zk, BigInteger lo, BigInteger hi, int k) {
        //System.out.printf("findRoot(zk=%s, lo=%s, hi=%s, k=%d)\n", zk, lo, hi, k);
        if (lo.compareTo(hi) > 0)
            return lo.add(BigInteger.ONE);
        BigInteger mid = lo.add(hi).divide(TWO);
        BigInteger t = factorial(mid, k);
        //System.out.printf("   t = %s\n", t);
        int res = t.compareTo(zk);
        if (res == 0)
            return mid;
        return findRoot(zk,
                        (res < 0 ? mid.add(BigInteger.ONE) : lo),
                        (res > 0 ? mid.subtract(BigInteger.ONE) : hi),
                        k);
    }

}
