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
		int n = in.nextInt();
		
		long[] number = new long[n + 1];
		number[0] = number[1] = 0;
		for (int i = 2; i <= n; ++i) {
			number[i] = number[i / 2] + number[(i + 1) / 2] + i - 1;
		}
		
		int[] size = new int[n + 1];
		int[][] array = new int[n + 1][n + 1];
		
		size[0] = 0;
		size[1] = 1;
		array[1][0] = 1;
		
		for (int i = 2; i <= n; ++i) {
			size[i] = 0;
			for (int j = 0; j < size[(i + 1) / 2]; ++j) {
				if (array[(i + 1) / 2][j] == (i + 1) / 2) {
					array[i][size[i]++] = i - 1;
				} else {
					array[i][size[i]++] = array[(i + 1) / 2][j];
				}
			}

			for (int j = 0; j < size[i / 2]; ++j) {
				if (array[i / 2][j] == i / 2) {
					array[i][size[i]++] = i;
				} else {
					array[i][size[i]++] = array[i / 2][j] + (i + 1) / 2 - 1;
				}
			}
		}
		
		BigInteger[][] comb = new BigInteger[n + 1][n + 1];
		for (int i = 0; i <= n; ++i) {
			for (int j = 0; j <= n; ++j) {
				comb[i][j] = BigInteger.ZERO;
			}
		}
		comb[0][0] = BigInteger.ONE;
		for (int i = 1; i <= n; ++i) {
			comb[i][0] = comb[i][i] = BigInteger.ONE;
			for (int j = 1; j < i; ++j) {
				comb[i][j] = comb[i - 1][j].add(comb[i - 1][j - 1]);
			}
		}
		
		BigInteger[] ways = new BigInteger[n + 1];
		ways[0] = ways[1] = BigInteger.ONE;
		for (int i = 2; i <= n; ++i) {
			int left = i / 2, right = (i + 1) / 2;
			ways[i] = comb[left + right - 2][left - 1].multiply(ways[left]).multiply(ways[right]).multiply(BigInteger.valueOf(2));
		}
		
		out.println(number[n]);
		for (int i = 0; i < size[n]; ++i) {
			out.printf("%d%s", array[n][i], (i == size[n] - 1) ? "\n" : " ");
		}
		out.println(ways[n]);
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
