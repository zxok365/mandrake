import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	public static void main(String[] args) {
		InputStream inputStream = System.in;
		OutputStream outputStream = System.out;
		InputReader in = new InputReader(inputStream);
		PrintWriter out = new PrintWriter(outputStream);
		Task solver = new Task();
		solver.solve(1, in, out);
		out.close();
	}
}

class Task {
	public void solve(int testNumber, InputReader in, PrintWriter out) {
		int n = in.nextInt(), k = in.nextInt();
		BigInteger[][] ways = new BigInteger[n + 1][k + 1];
		for (int i = 0; i <= n; ++i) {
			for (int j = 0; j <= k; ++j) {
				ways[i][j] = BigInteger.ZERO;
			}
		}
		ways[0][0] = BigInteger.ONE;
		for (int i = 1; i <= n; ++i) {
			ways[i][1] = BigInteger.ONE;
			for (int j = 2; j <= k; ++j) {
				if (i - j >= 0) {
					ways[i][j] = ways[i - 1][j - 1].add(ways[i - j][j]);
				} else {
					ways[i][j] = ways[i - 1][j - 1];
				}
			}
		}
		out.println(ways[n][k]);
	}
}

class InputReader {
	public BufferedReader reader;
	public StringTokenizer tokenizer;
	
	public InputReader(InputStream stream) {
		reader = new BufferedReader(new InputStreamReader(stream), 32768);
		tokenizer = null;
	}
	
	public String next() {
		while (tokenizer == null || !tokenizer.hasMoreTokens()) {
			try {
				tokenizer = new StringTokenizer(reader.readLine());
			} catch (IOException e) {
				throw new RuntimeException(e);
			}
		}
		return tokenizer.nextToken();
	}
	
	public int nextInt() {
		return Integer.parseInt(next());
	}
	
	public long nextLong() {
		return Long.parseLong(next());
	}
}
