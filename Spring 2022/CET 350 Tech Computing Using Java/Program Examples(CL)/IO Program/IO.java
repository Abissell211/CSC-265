import java.io.*;
class IO
{
	public static void main(String[] args)throws IOException
	{
//------------------------------Open bufferedreader from system input device------------------------------//
		BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in));
//-------------------------------------------Data Declarations--------------------------------------------//																					
		String line;
		int i;
		double d;
//---------------------------------------String Prompt, Read, Print---------------------------------------//		
		System.out.print("Enter a String: ");			// Prompt
		System.out.flush();								// Force print with no new line for curser to be at the end of the prompt.
		line = stdin.readLine();						// Read
		System.out.println("You entered: "+line+"\n");	// Print
//--------------------------------------Integer Prompt, Read, Print---------------------------------------//		
		System.out.print("Enter an integer: ");			// Prompt
		System.out.flush();								// Force print with no new line for curser to be at the end of the prompt.			
		line = stdin.readLine();						// Read String
		i = Integer.parseInt(line);						// To get integer of the string	
		System.out.println("You entered the string: "+line+" which is the integer: "+i+"\n");	// Print
//----------------------------------------Real Prompt, Read, Print----------------------------------------//		
		System.out.print("Enter a real number: ");		// Prompt
		System.out.flush();								// Force print with no new line for curser to be at the end of the prompt.
		line = stdin.readLine();						// Read
		d = Double.valueOf(line).doubleValue();			// Extract double value from object to get double
		System.out.println("You entered the string: "+line+" which is the real: "+d+"\n");		// Print
	}
}
