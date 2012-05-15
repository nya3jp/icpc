import java.io.*;
import java.util.*;
import java.math.*;

public class lesson {

    public static final String PROBLEM_NAME = "lesson";

    public static void main(String[] args) throws Exception {

	Scanner sc = new Scanner(new FileInputStream(PROBLEM_NAME + ".in"));
	PrintWriter out = new PrintWriter(new FileOutputStream(PROBLEM_NAME + ".out"));

	try {

	    int n, m;
	    n = sc.nextInt();
	    m = sc.nextInt();

	    out.println(new lesson().solve(n, m));

	}
	finally {
	    out.flush();
	    out.close();
	}

    }

    BigInteger solve(int n, int m) {

	BigInteger two = new BigInteger("2");

	return two.pow(n).add(two.pow(m)).subtract(two);
    }

}

