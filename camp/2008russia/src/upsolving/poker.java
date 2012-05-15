import java.io.*;
import java.util.*;
import java.math.*;

public class poker {

    public static final String PROBLEM_NAME = "poker";
    public static final BigInteger TWO = new BigInteger("2");

    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(new FileInputStream(PROBLEM_NAME + ".in"));
        PrintWriter out = new PrintWriter(new FileOutputStream(PROBLEM_NAME + ".out"));

        poker obj = new poker();
        int iCase = 0;
        for(;;) {
            int r, s, d, c;
            r = sc.nextInt();
            s = sc.nextInt();
            d = sc.nextInt();
            c = sc.nextInt();
            if (r == 0)
                break;
            BigInteger[] fl = obj.flash(r, s, d, c);
            BigInteger[] st = obj.straight(r, s, d, c);
            if (iCase++ > 0)
                out.println();
            out.printf("%s/%s\n", st[0], st[1]);
            out.printf("%s/%s\n", fl[0], fl[1]);
        }

        out.flush();
        out.close();
    }

    BigInteger[][][][][] memo_flash = new BigInteger[21][21][21][21][];
    BigInteger[] flash(int r, int s, int d, int c) {
        if (d > s*r)
            return new BigInteger[]{BigInteger.ZERO, BigInteger.ONE};
        if (s == 0) {
            if (c == 0)
                return new BigInteger[]{BigInteger.ONE, BigInteger.ONE};
            return new BigInteger[]{BigInteger.ZERO, BigInteger.ONE};
        }
        if (memo_flash[r][s][d][c] == null) {
            BigInteger[] res = new BigInteger[]{BigInteger.ZERO, BigInteger.ONE};
            for(int i = 0; i <= Math.min(r, d); i++) {
                BigInteger a = choose((s-1)*r, d-i).multiply(choose(r, i));
                BigInteger[] b = (i >= c ?
                                  new BigInteger[]{BigInteger.ONE, BigInteger.ONE} :
                                  flash(r, s-1, d-i, c));
                b[0] = b[0].multiply(a);
                res = fracadd(res, b);
            }
            res[1] = res[1].multiply(choose(s*r, d));
            normalize(res);
            memo_flash[r][s][d][c] = res;
        }
        return copy(memo_flash[r][s][d][c]);
    }

    BigInteger[][][][][][] memo_straight = new BigInteger[21][21][21][21][21][];
    BigInteger[] straight(int r, int s, int d, int c) {
        return straight(r, s, d, c, c);
    }
    BigInteger[] straight(int r, int s, int d, int c, int e) {
        if (e == 0)
            return new BigInteger[]{BigInteger.ONE, BigInteger.ONE};
        if (r == 0)
            return new BigInteger[]{BigInteger.ZERO, BigInteger.ONE};
        if (d > s*r)
            return new BigInteger[]{BigInteger.ZERO, BigInteger.ONE};

        if (memo_straight[r][s][d][c][e] == null) {
            BigInteger[] res = new BigInteger[]{BigInteger.ZERO, BigInteger.ONE};
            for(int i = 0; i <= Math.min(s, d); i++) {
                BigInteger a = choose(s*(r-1), d-i).multiply(choose(s, i));
                BigInteger[] b = straight(r-1, s, d-i, c, (i > 0 ? e-1 : c));
                b[0] = b[0].multiply(a);
                res = fracadd(res, b);
            }
            res[1] = res[1].multiply(choose(s*r, d));
            normalize(res);
            memo_straight[r][s][d][c][e] = res;
        }
        return copy(memo_straight[r][s][d][c][e]);
    }

    static BigInteger[][][][] separate_memo = new BigInteger[21][21][21][21];
    static BigInteger separate(int n, int k, int l, int c) {
        if (l == 0)
            return BigInteger.ZERO;
        if (k == 0)
            return BigInteger.ONE;
        if (n == 0)
            return BigInteger.ZERO;
        if (separate_memo[n][k][l][c] == null)
            separate_memo[n][k][l][c] = separate(n-1, k-1, l-1, c).add(separate(n-1, k, c, c));
        return separate_memo[n][k][l][c];
    }

    static BigInteger[] copy(BigInteger[] a) {
        BigInteger[] b = new BigInteger[]{a[0], a[1]};
        return b;
    }

    static BigInteger[] fracadd(BigInteger[] a, BigInteger[] b) {
        BigInteger[] c = new BigInteger[2];
        c[1] = a[1].multiply(b[1]);
        c[0] = a[0].multiply(b[1]).add(b[0].multiply(a[1]));
        return normalize(c);
    }

    static BigInteger[] normalize(BigInteger[] c) {
        BigInteger g = c[0].gcd(c[1]);
        c[0] = c[0].divide(g);
        c[1] = c[1].divide(g);
        return c;
    }

    static BigInteger[] fracmul(BigInteger[] a, BigInteger[] b) {
        BigInteger[] c = new BigInteger[2];
        c[0] = a[0].multiply(b[0]);
        c[1] = a[1].multiply(b[1]);
        return normalize(c);
    }

    static BigInteger[][] choose_memo = new BigInteger[401][21];

    static BigInteger choose(int n, int k) {
        if (k == 0)
            return BigInteger.ONE;
        if (n == 0)
            return BigInteger.ZERO;
        if (choose_memo[n][k] == null)
            choose_memo[n][k] = choose(n-1, k).add(choose(n-1, k-1));
        return choose_memo[n][k];
    }

}
