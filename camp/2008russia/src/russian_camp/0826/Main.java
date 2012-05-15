import java.util.*;
import java.io.*;
import java.math.*;


public class Main {

    static BigInteger[][] mat;
    static int n;
    static final int N = 22;
    static BigInteger minus = new BigInteger("-1");
    static BigInteger[][][] memo = new BigInteger[20][1<<20][];
    static BigInteger[] POLY_ONE;

    static PrintWriter out;
    static FileInputStream in;

    public static void main(String[] args) throws IOException {

	in = new FileInputStream("ballistic.in");
	out = new PrintWriter(new FileOutputStream("ballistic.out"));

	POLY_ONE = new BigInteger[N];
	POLY_ONE[0] = BigInteger.ONE;
	for(int k = 1; k < N; k++)
	    POLY_ONE[k] = BigInteger.ZERO;

	Scanner sc = new Scanner(in);
	n = sc.nextInt();
	mat = new BigInteger[n][n];
	for(int i = 0; i < n; i++) {
	    for(int j = 0; j < n; j++) {
		mat[i][j] = sc.nextBigInteger();
	    }
	}

	solve();
    }

    public static void solve() {
	BigInteger[] res = solve(0, 0);
	for(int k = n; k >= 0; k--) {
	    out.println(res[k]);
	    /*
	    System.err.println(k);
	    System.err.println(res[k]);
	    */
	}
	out.flush();
	out.close();
    }

    public static BigInteger[] solve(int j, int p) {

	if (j == n)
	    return POLY_ONE;

	if (memo[j][p] != null)
	    return memo[j][p];

	int m = n-j;

	BigInteger sgn = BigInteger.ONE;
	BigInteger[] res = new BigInteger[m+1];
	for(int i = 0; i < m+1; i++)
	    res[i] = BigInteger.ZERO;

	for(int i = 0; i < n; i++) {
	    if ((p & (1<<i)) != 0)
		continue;
	    BigInteger[] suborg = solve(j+1, p|(1<<i));
	    BigInteger[] sub = new BigInteger[m];
	    for(int k = 0; k < m; k++)
		sub[k] = suborg[k].multiply(sgn);
	    if (i == j) {
		/*
		BigInteger[] lam = new BigInteger[m+1];
		lam[0] = BigInteger.ZERO;
		for(int k = 0; k < m; k++)
		    lam[k+1] = sub[k].multiply(minus);
		polyadd(res, lam);
		*/
		for(int k = 0; k < m; k++)
		    res[k+1] = res[k+1].subtract(sub[k]);
	    }
	    /*
	    for(int k = 0; k < N; k++)
		sub[k] = sub[k].multiply(mat[i][j]);
	    polyadd(res, sub);
	    */
	    for(int k = 0; k < m; k++)
		res[k] = res[k].add(sub[k].multiply(mat[i][j]));
	    sgn = sgn.multiply(minus);
	}

	/*
	System.err.printf("solve(%d,%d) =", j, p);
	for(int k = 0; k <= n; k++)
	    System.err.printf(" %s", res[k].toString());
	System.err.println();
	*/

	memo[j][p] = res;
	return res;
    }

    public static void polyadd(BigInteger[] a, BigInteger[] b) {
	for(int k = 0; k < N; k++)
	    a[k] = a[k].add(b[k]);
    }

}
