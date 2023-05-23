import java.io.*;
class command_line{
	public static void main(String[] args)throws IOException{
		String S;
		int i,j,l,sl;
		l = args.length;
		for(i = 0;i < l;i++){
			System.out.println("Parameter "+(i+1)+" is: "+args[i]);
			S = args[i];
			sl = S.length();
			for(j = 0;j < sl;j++)		// steps through all the characters in the string
				System.out.println("Character "+(j+1)+" is: "+S.charAt(j));
		}
	}
}

// for the command line add paramaters after the java command
// ex.
//		>javac command_line.java
//		>java command_line one two
// "one" and "two" are parameters that are loaded into the args array for use in program. 	