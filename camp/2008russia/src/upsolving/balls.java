import java.io.*;
import java.util.*;
import java.math.*;

public class balls {

    public static final String PROBLEM_NAME = "balls";
    public static final BigInteger TWO = new BigInteger("2");

    public static void main(String[] args) throws Exception {

        Scanner sc = new Scanner(new FileInputStream(PROBLEM_NAME + ".in"));
        PrintWriter out = new PrintWriter(new FileOutputStream(PROBLEM_NAME + ".out"));

        try {
            balls obj = new balls();

            int n, m, k;
            n = sc.nextInt();
            m = sc.nextInt();
            k = sc.nextInt();

            int[] xs = new int[m];
            for(int i = 0; i < m; i++) {
                xs[i] = 0;
            }
            for(int i = 0; i < n; i++) {
                int x;
                x = sc.nextInt();
                x--;
                xs[x]++;
            }
            BigInteger res = obj.solve(xs, k);
            out.println(res);
        }
        finally {
            out.flush();
            out.close();
        }

    }


    BigInteger solve(int[] xs, int k) {
        return solve(xs, 0, k, k);
    }

    BigInteger[][] solve_memo = new BigInteger[210][210];
    BigInteger solve(int[] xs, int pos, int k, int kk) {
        if (pos == xs.length)
            return (k == 0 ? fact(kk) : BigInteger.ZERO);
        if (solve_memo[pos][k] == null) {
            BigInteger lo = BigInteger.ZERO;
            for(int i = 0; i <= Math.min(xs[pos], k); i++)
                lo = lo.add(solve(xs, pos+1, k-i, kk).divide(fact(i)));
            solve_memo[pos][k] = lo;
        }
        return solve_memo[pos][k];
    }

    BigInteger[] fact_memo = new BigInteger[210];

    BigInteger fact(int n) {
        if (n <= 1)
            return BigInteger.ONE;
        if (fact_memo[n] == null)
            fact_memo[n] = new BigInteger(String.valueOf(n)).multiply(fact(n-1));
        return fact_memo[n];
    }
    

}
