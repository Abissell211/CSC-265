import java.io.*;
class try_example{
	public static void main(String[] args){
//------------------------------Open bufferedreader from system input device------------------------------//
		BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in));
//-------------------------------------------Data Declarations--------------------------------------------//																					
		String line;
		int i;
		double d;
		try{		// try for the entire reading from keyboard
//---------------------------------------String Prompt, Read, Print---------------------------------------//		
			System.out.print("Enter a String: ");			// Prompt
			System.out.flush();								// Force print with no new line for curser to be at the end of the prompt.
			line = stdin.readLine();						// Read
			System.out.println("You entered: "+line+"\n");	// Print
//--------------------------------------Integer Prompt, Read, Print---------------------------------------//	
		    try{	// try for the integer check
				System.out.print("Enter an integer: ");			// Prompt
				System.out.flush();								// Force print with no new line for curser to be at the end of the prompt.			
				line = stdin.readLine();						// Read String
				i = Integer.parseInt(line);						// To get integer of the string	
				System.out.println("You entered the string: "+line+" which is the integer: "+i+"\n");	// Print
			}		// catch for the integer check
			catch(NumberFormatException e){
				System.out.println("The input was not an integer " +e);
			}
//----------------------------------------Real Prompt, Read, Print----------------------------------------//
			try{	// try for the real check	
				System.out.print("Enter a real number: ");		// Prompt
				System.out.flush();								// Force print with no new line for curser to be at the end of the prompt.
				line = stdin.readLine();						// Read
				d = Double.valueOf(line).doubleValue();			// Extract double value from object to get double
				System.out.println("You entered the string: "+line+" which is the real: "+d+"\n");		// Print
			}		// catch for the real check
			catch(NumberFormatException e){
				System.out.println("The input was not a Double " +e);
			}
		}			// catch for the entire reading from keyboard
		catch(IOException e){
			System.out.println("Error occurred while reading from the keyboard: "+e);
		}
	}
}
