import java.io.*;
import java.util.*;
import java.math.*;


public class monkey {

    static final String PROBLEM_NAME = "monkey";

    public static void main(String[] args) throws Exception {
	Scanner sc = new Scanner(new FileInputStream(PROBLEM_NAME + ".in"));
	PrintWriter out = new PrintWriter(new FileOutputStream(PROBLEM_NAME + ".out"));

	try {

	    monkey obj = new monkey();

	    int m = sc.nextInt();
	    String str = sc.next();

	    BigInteger res = obj.solve(m, str);

	    out.println(res);

	}
	finally {
	    out.flush();
	    out.close();
	}

    }

    static final int N = 32000;

    int n, m;
    String str;
    int[] seq = new int[N];
    int[] kmp = new int[N];
    int[][] am = new int[N][26];
    BigInteger[][] x = new BigInteger[N][2];

    static final BigInteger ZERO = new BigInteger("0");
    static final BigInteger ONE = new BigInteger("1");
    static final BigInteger TWO = new BigInteger("2");

    public BigInteger solve(int m, String str) {
	this.m = m;
	this.str = str;
	this.n = str.length();

	for(int i = 0; i < n; i++)
	    seq[i] = (int)(str.charAt(i) - 'a');

	{
	    int q = kmp[0] = -1;
	    for(int p = 1; p <= n; p++) {
		while(q >= 0 && seq[q] != seq[p-1])
		    q = kmp[q];
		kmp[p] = ++q;
	    }
	}
	{
	    for(int c = 0; c < m; c++)
		am[0][c] = 0;
	    am[0][seq[0]] = 1;
	    for(int p = 1; p < n; p++) {
		for(int c = 0; c < m; c++) {
		    if (seq[p] == c)
			am[p][c] = p+1;
		    else
			am[p][c] = am[kmp[p]][c];
		}
	    }
	}

	/*
	BigInteger lo = ZERO, hi = ONE;
	while(!go(hi)) {
	    hi = hi.multiply(TWO);
	    System.err.printf("inithi=%s\n", hi);
	}
	while(lo.compareTo(hi) != 0) {
	    System.err.printf("lo=%s, hi=%s\n", lo, hi);
	    BigInteger mid = lo.add(hi).divide(TWO);
	    if (go(mid))
		hi = mid;
	    else
		lo = mid.add(ONE);
	}
	*/

	return go();
    }

    BigInteger go() {
	int[] refcnt = new int[n];
	for(int i = 0; i < n; i++)
	    refcnt[i] = 0;
	for(int i = 0; i < n; i++) {
	    refcnt[i]++;
	    for(int c = 0; c < this.m; c++)
		if (c != seq[i])
		    refcnt[am[i][c]]++;
	}

	BigInteger m = new BigInteger(Integer.toString(this.m));

	x[0][0] = ONE;
	x[0][1] = ZERO;
	for(int i = 0; i < n; i++) {
	    BigInteger[] t = new BigInteger[2];
	    t[0] = m.multiply(x[i][0]);
	    t[1] = m.multiply(x[i][1].subtract(ONE));
	    for(int c = 0; c < this.m; c++) {
		if (c != seq[i]) {
		    t[0] = t[0].subtract(x[am[i][c]][0]);
		    t[1] = t[1].subtract(x[am[i][c]][1]);
		    if (--refcnt[am[i][c]] == 0) {
			//System.err.printf("bye %d\n", am[i][c]);
			x[am[i][c]][0] = null;
			x[am[i][c]][1] = null;
		    }
		}
	    }
	    x[i+1] = t;
	    if (--refcnt[i] == 0) {
		//System.err.printf("bye %d\n", i);
		x[i][0] = null;
		x[i][1] = null;
	    }
	    //System.err.printf("%d/%d\n", i, n);
	    //System.err.printf("%d: %s\n",
	    //i, 
	    //t[1].negate().divide(t[0]));
	}
	return x[n][1].negate().divide(x[n][0]);
    }

}
