import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
    public static void main(String[] args) throws Exception {
	(new Main()).run();
    }

    void run() throws Exception {
	Scanner sc = new Scanner(new FileInputStream("cantor.in"));
	int n = sc.nextInt();
	BigInteger[] res = solve(n);
	PrintWriter out = new PrintWriter(new FileOutputStream("cantor.out"));
	out.print(res[0]);
	out.print("/");
	out.print(res[1]);
	out.println();
	out.flush();
	out.close();
    }

    BigInteger[] solve(int n) {
	memo = new BigInteger[n+1][];
	ONE = BigInteger.ONE;
	TWO = new BigInteger("2");
	THREE = new BigInteger("3");
	memo[0] = new BigInteger[]{ BigInteger.ONE, BigInteger.ONE} ;
	return f(n);
    }

    BigInteger ONE, TWO, THREE;

    BigInteger[][] memo;
    BigInteger[] f(int n) {
	if (memo[n] != null)
	    return memo[n];

	BigInteger[] res = new BigInteger[]{BigInteger.ZERO, BigInteger.ONE};

	for(int k = 0; k <= n-1; k++) {
	    BigInteger[] subresorg = f(k);
	    BigInteger[] subres = new BigInteger[2];
	    subres[0] = subresorg[0].multiply(choose(n, k));
	    subres[1] = subresorg[1];
	    fracadd(res, subres);
	}
	res[0] = res[0].add(res[1]);
	res[1] = res[1].multiply(TWO).multiply( THREE.multiply(TWO.pow(n-1)).subtract(ONE) );

	BigInteger g = res[0].gcd(res[1]);
	res[0] = res[0].divide(g);
	res[1] = res[1].divide(g);
	memo[n] = res;
	return res;
    }

    void fracadd(BigInteger[] a, BigInteger[] b) {
	BigInteger g = a[1].gcd(b[1]);
	BigInteger l = b[1].divide(g);
	BigInteger r = a[1].divide(g);
	for(int i = 0; i < 2; i++)
	    a[i] = a[i].multiply(l);
	for(int i = 0; i < 2; i++)
	    b[i] = b[i].multiply(r);
	a[0] = a[0].add(b[0]);
    }

    BigInteger[][] choose0 = new BigInteger[60][60];

    BigInteger choose(int n, int k) {
	if (n == 0)
	    return (k == 0 ? ONE : BigInteger.ZERO);
	if (k < 0)
	    return BigInteger.ZERO;
	if (choose0[n][k] == null)
	    choose0[n][k] = choose(n-1, k).add(choose(n-1, k-1));
	return choose0[n][k];
    }

}
