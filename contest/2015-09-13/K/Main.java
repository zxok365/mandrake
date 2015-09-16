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
	int size = 1000000;
	
	int primes;
	int[] prime = new int[size + 1];
	
	public boolean square(BigInteger number) {
		BigInteger left = BigInteger.ZERO, right = number;
		while (left.compareTo(right) < 0) {
			BigInteger mid = left.add(right).divide(BigInteger.valueOf(2));
			if (mid.multiply(mid).compareTo(number) < 0) {
				left = mid.add(BigInteger.ONE);
			} else {
				right = mid;
			}
		}
		return number.compareTo(BigInteger.ONE) != 0 && left.multiply(left).compareTo(number) == 0;
	}
	
	public BigInteger get_square(BigInteger number) {
		BigInteger left = BigInteger.ZERO, right = number;
		while (left.compareTo(right) < 0) {
			BigInteger mid = left.add(right).divide(BigInteger.valueOf(2));
			if (mid.multiply(mid).compareTo(number) < 0) {
				left = mid.add(BigInteger.ONE);
			} else {
				right = mid;
			}
		}
		return left;
	}
	
	public boolean triple(BigInteger number) {
		BigInteger left = BigInteger.ZERO, right = number;
		while (left.compareTo(right) < 0) {
			BigInteger mid = left.add(right).divide(BigInteger.valueOf(2));
			if (mid.multiply(mid).multiply(mid).compareTo(number) < 0) {
				left = mid.add(BigInteger.ONE);
			} else {
				right = mid;
			}
		}
		return number.compareTo(BigInteger.ONE) != 0 && left.multiply(left).multiply(left).compareTo(number) == 0;
	}
	
	public long calc(BigInteger number, BigInteger a) {
		long answer = 1;
		long counter = 0;
		while (number.mod(a).compareTo(BigInteger.ZERO) == 0) {
			number = number.divide(a);
			counter++;
		}
		answer *= counter;
		if (square(number)) {
			answer *= 2;
		}
		return answer;
	}
	
    public void solve(int testNumber, InputReader in, PrintWriter out) {
    	if (testNumber == 1) {
    		boolean[] mark = new boolean[size + 1];
    		for (int i = 2; i <= size; ++i) {
    			mark[i] = false;
    		}
    		primes = 0;
    		for (long i = 2; i <= size; ++i) {
    			if (!mark[(int)i]) {
    				prime[primes++] = (int)i;
    			}
				for (long j = i * i; j <= size; j += i) {
					mark[(int)j] = true;
				}
    		}
    	}
    	
        long answer1 = 1, answer2 = 1;
        
        BigInteger number1 = new BigInteger(in.next());
        BigInteger number2 = new BigInteger(in.next());
        
        for (int i = 0; i < primes; ++i) {
        	BigInteger divisor = BigInteger.valueOf(prime[i]);
        	if (number1.compareTo(divisor) < 0) {
        		break;
        	}
        	if (number1.mod(divisor).compareTo(BigInteger.ZERO) == 0) {
        		long counter = 0;
        		while (number1.mod(divisor).compareTo(BigInteger.ZERO) == 0) {
        			number1 = number1.divide(divisor);
        			counter++;
        		}
        		answer1 *= counter;
        	}
        }
        
        for (int i = 0; i < primes; ++i) {
        	BigInteger divisor = BigInteger.valueOf(prime[i]);
        	if (number2.compareTo(divisor) < 0) {
        		break;
        	}
        	if (number2.mod(divisor).compareTo(BigInteger.ZERO) == 0) {
        		long counter = 0;
        		while (number2.mod(divisor).compareTo(BigInteger.ZERO) == 0) {
        			number2 = number2.divide(divisor);
        			counter++;
        		}
        		answer2 *= counter;
        	}
        }
                
        BigInteger divisor = number1.gcd(number2);
        if (divisor.compareTo(BigInteger.ONE) != 0) {
		    if (square(divisor)) {
		    	BigInteger a = get_square(divisor);
		    	answer1 *= calc(number1, a);
		    	answer2 *= calc(number2, a);
		    } else if (triple(divisor)) {
		    	answer1 *= 3;
		    	answer2 *= 3;
		    } else {
		    	BigInteger check1 = divisor.gcd(number1.divide(divisor));
		    	if (check1.compareTo(BigInteger.ONE) == 0) {
		    		if (square(number1.divide(divisor))) {
		    			answer1 *= 2;
		    		}
		    	} else {
		    		answer1 *= calc(number1, check1);
		    	}
		    	
		    	BigInteger check2 = divisor.gcd(number2.divide(divisor));
		    	if (check2.compareTo(BigInteger.ONE) == 0) {
		    		if (square(number2.divide(divisor))) {
		    			answer2 *= 2;
		    		}
		    	} else {
		    		answer2 *= calc(number2, check2);
		    	}
		    }
		}
        
        out.print(answer1);
        out.print(" ");
        out.print(answer2);
        out.println();
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
