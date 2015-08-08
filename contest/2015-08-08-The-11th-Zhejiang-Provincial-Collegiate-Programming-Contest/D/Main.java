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
		int tests = in.nextInt();
		for (int i = 1; i <= tests; ++i) {
			solver.solve(i, in, out);
		}
		out.close();
	}
}

class Task {
	public void solve(int testNumber, InputReader in, PrintWriter out) {
		BigInteger[] number = new BigInteger[17];
		
		number[0] = new BigInteger("0");
		number[1] = new BigInteger("0");
		number[2] = new BigInteger("0");
		number[3] = new BigInteger("0");
		number[4] = new BigInteger("576");
		number[5] = new BigInteger("587520");
		number[6] = new BigInteger("133583040");
		number[7] = new BigInteger("7912114560");
		number[8] = new BigInteger("183561517440");
		number[9] = new BigInteger("2100291379200");
		number[10] = new BigInteger("13489759180800");
		number[11] = new BigInteger("52314638745600");
		number[12] = new BigInteger("126988114176000");
		number[13] = new BigInteger("193984151961600");
		number[14] = new BigInteger("180982132531200");
		number[15] = new BigInteger("94152554496000");
		number[16] = new BigInteger("20922789888000");
		
		long n = in.nextLong();
		
		BigInteger answer = BigInteger.ZERO;
		for (long i = 1; i <= n && i <= 16; ++i) {
			BigInteger comb = BigInteger.ONE;
			for (long j = n; j >= n - i + 1; --j) {
				comb = comb.multiply(BigInteger.valueOf(j));
			}
			for (long j = 1; j <= i; ++j) {
				comb = comb.divide(BigInteger.valueOf(j));
			}
			answer = answer.add(number[(int)i].multiply(comb));
		}
		
		BigInteger result = answer.multiply(answer).multiply(answer).multiply(answer);
		out.println(result);
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
