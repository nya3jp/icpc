import java.io.*;
import java.util.*;
import java.math.*;


public class partitions {

    public static final String PROBLEM_NAME = "partitions";

    public static void main(String[] args) throws Exception {

	Scanner sc = new Scanner(new FileInputStream(PROBLEM_NAME + ".in"));
	PrintWriter out = new PrintWriter(new FileOutputStream(PROBLEM_NAME + ".out"));

	try {
	    int n, m;
	    n = sc.nextInt();
	    m = sc.nextInt();

	    int[][] avoidSets = new int[m][];
	    int p = 0;
	    for(int i = 0; i < m; i++) {
		int k;
		k = sc.nextInt();
		if (k == 0) {
		    out.println(0);
		    return;
		}
		int[] avoidSet = new int[k];
		boolean ok = true;
		for(int j = 0; j < k; j++) {
		    int x = sc.nextInt();
		    if (!(1 <= x && x <= n))
			ok = false;
		    avoidSet[j] = x-1;
		}
		if (ok)
		    avoidSets[p++] = avoidSet;
	    }

	    int[][] avoidSets2 = new int[p][];
	    while(--p >= 0) {
		avoidSets2[p] = avoidSets[p];
	    }

	    out.println(new partitions().solve(n, avoidSets2));
	}
	finally {
	    out.flush();
	    out.close();
	}

    }





    BigInteger solve(int n, int[][] avoidSets) {

	BigInteger res = BigInteger.ZERO;

	int m = avoidSets.length;

	boolean[][] shared = new boolean[m][m];
	for(int i = 0; i < m; i++)
	    for(int j = 0; j < m; j++)
		shared[i][j] = shares(avoidSets[i], avoidSets[j]);

	for(int p = 0; p < (1<<m); p++) {

	    int msub = 0;
	    int sgn = 1;
	    for(int i = 0; i <= 30; i++) {
		if ((p & (1<<i)) != 0) {
		    sgn *= -1;
		    msub++;
		}
	    }

	    int[] subindices = new int[msub];
	    {
		int isub = 0;
		for(int i = 0; i <= 30; i++) {
		    if ((p & (1<<i)) != 0) {
			subindices[isub++] = i;
		    }
		}
	    }

	    boolean[] used = new boolean[msub];
	    for(int i = 0; i < msub; i++)
		used[i] = false;

	    ArrayList< ArrayList<Integer> > mergedArrays = new ArrayList< ArrayList<Integer> >();
	    for(int s = 0; s < msub; s++) {
		if (!used[s]) {
		    HashSet<Integer> dup = new HashSet<Integer>();
		    ArrayList<Integer> array = new ArrayList<Integer>();
		    for(int i = 0; i < avoidSets[subindices[s]].length; i++)
			array.add(avoidSets[subindices[s]][i]);
		    LinkedList<Integer> q = new LinkedList<Integer>();
		    q.addLast(s);
		    used[s] = true;
		    while(q.size() > 0) {
			int here = q.getFirst();
			q.removeFirst();
			for(int there = 0; there < msub; there++) {
			    if (!used[there] && shared[subindices[here]][subindices[there]]) {
				for(int i = 0; i < avoidSets[subindices[there]].length; i++)
				    array.add(avoidSets[subindices[there]][i]);
				q.addLast(there);
				used[there] = true;
			    }
			}
		    }
		    ArrayList<Integer> uniq = new ArrayList<Integer>();
		    for(Integer a : array) {
			if (dup.add(a)) {
			    uniq.add(a);
			}
		    }
		    mergedArrays.add(uniq);
		}
	    }

	    //System.err.printf("go:\n");
	    int[][] subAvoidSets = new int[mergedArrays.size()][];
	    for(int i = 0; i < subAvoidSets.length; i++) {
		ArrayList<Integer> array = mergedArrays.get(i);
		subAvoidSets[i] = new int[array.size()];
		for(int j = 0; j < array.size(); j++) {
		    subAvoidSets[i][j] = array.get(j);
		    //System.err.printf("%d ", subAvoidSets[i][j]);
		}
		//System.err.println();
	    }

	    res = res.add(subsolve(n, subAvoidSets).multiply(new BigInteger(String.valueOf(sgn))));

	}

	return res;
    }

    boolean shares(int[] a, int[] b) {
	for(int i = 0; i < a.length; i++)
	    for(int j = 0; j < b.length; j++)
		if (a[i] == b[j])
		    return true;
	return false;
    }

    BigInteger subsolve(int n, int[][] avoidSets) {
	int m = avoidSets.length;
	for(int i = 0; i < m; i++)
	    n -= avoidSets[i].length;
	BigInteger res = BigInteger.ZERO;
	for(int i = 0; i <= m; i++)
	    res = res.add(g(m, i).multiply(f(n, i)));
	return res;
    }

    BigInteger[][] g_memo = new BigInteger[20][20];
    BigInteger g(int n, int m) {
	if (n == 0 && m == 0)
	    return BigInteger.ONE;
	if (n == 0 || m == 0)
	    return BigInteger.ZERO;
	if (g_memo[n][m] == null) {
	    g_memo[n][m] = g(n-1, m-1).add(new BigInteger(String.valueOf(n-1)).multiply(g(n-1, m)));
	}
	return g_memo[n][m];
    }

    BigInteger[][] f_memo = new BigInteger[110][110];
    BigInteger f(int n, int k) {
	if (n == 0)
	    return BigInteger.ONE;
	if (f_memo[n][k] != null)
	    return f_memo[n][k];
	BigInteger res = BigInteger.ZERO;
	if (k > 0) {
	    for(int i = 0; i <= n; i++)
		res = res.add(choose(n, i).multiply(f(n-i, k-1)));
	}
	else {
	    for(int i = 1; i <= n; i++)
		res = res.add(choose(n-1, i-1).multiply(f(n-i, 0)));
	}
	return f_memo[n][k] = res;
    }

    BigInteger[][] choose_memo = new BigInteger[110][110];

    BigInteger choose(int n, int m) {
	if (m == 0)
	    return BigInteger.ONE;
	if (n == 0)
	    return BigInteger.ZERO;
	if (choose_memo[n][m] == null)
	    choose_memo[n][m] = choose(n-1, m-1).add(choose(n-1, m));
	return choose_memo[n][m];
    }

}
