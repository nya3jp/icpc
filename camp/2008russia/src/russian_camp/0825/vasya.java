import java.io.*;
import java.util.*;
import java.math.*;

public class vasya {

    public static final String PROBLEM_NAME = "vasya";

    public static void main(String[] args) throws Exception {

	Scanner sc = new Scanner(new FileInputStream(PROBLEM_NAME + ".in"));
	PrintWriter out = new PrintWriter(new FileOutputStream(PROBLEM_NAME + ".out"));

	try {

	    BigInteger a, b;
	    int k;

	    a = sc.nextBigInteger();
	    b = sc.nextBigInteger();
	    k = sc.nextInt();

	    out.println(new vasya().solve(a, b, k));

	}
	finally {
	    out.flush();
	    out.close();
	}

    }

    static BigInteger[][] choose_memo = new BigInteger[30][30];

    static BigInteger choose(int n, int k) {
	if (k == 0)
	    return BigInteger.ONE;
	if (n == 0)
	    return BigInteger.ZERO;
	if (choose_memo[n][k] == null)
	    choose_memo[n][k] = choose(n-1, k).add(choose(n-1, k-1));
	return choose_memo[n][k];
    }

    BigInteger solve(BigInteger a, BigInteger b, int k) {

	BigInteger res = BigInteger.ZERO;
	for(int i = 0; i <= k; i++) {
	    res = res.add(choose(k, i).multiply(a.pow(i)).multiply(b.pow(k-i)));
	}

	return res;
    }

}

