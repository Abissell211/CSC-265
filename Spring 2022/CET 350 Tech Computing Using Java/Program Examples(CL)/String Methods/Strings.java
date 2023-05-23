import java.io.*;
class Strings{
	public static void main(String[] args){
		String S;
		int i,l,sl;
		l = args.length;
		if(l >= 2){
			sl = args[0].length();
			S = args[0].concat(args[1]);
			System.out.println("Parameter 1 is: "+args[0]+" Parameter 2 is: "+args[1]);
			System.out.println("Parameter 1 + Parameter 2 is: "+S);
			System.out.println("Parameter 1 as a substring: "+S.substring(0,sl));
			System.out.println("Parameter 1 == Parameter 2: "+(args[0]==args[1]));
			System.out.println("Parameter 1 equals Parameter 2: "+(args[0].equals(args[1])));
			System.out.println("Parameter 1 equals Parameter 2 ignoring case: "+
														(args[0].equalsIgnoreCase(args[1])));
			System.out.println("Parameter 1 contains "+(args[1].substring(0,2))+" :"+					//ERROR
														(args[0].contains(args[1].substring(0,2))));
			System.out.println("Parameter 1 compared to Parameter 2: "+args[0].compareTo(args[1]));
			System.out.println("Parameter 1 compared to Parameter 2 ignoring case: "+
														args[0].compareToIgnoreCase(args[1]));
		}
	}	
}

// for the command line add paramaters after the java command
// ex.
//		>javac Strings.java
//		>java Strings one two
// "one" and "two" are parameters that are loaded into the args array for use in program. 	