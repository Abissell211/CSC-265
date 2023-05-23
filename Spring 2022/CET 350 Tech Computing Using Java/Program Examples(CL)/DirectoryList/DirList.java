import java.io*;

class DirList{
	public static void main(String args[]) {
		// REPLACE THIS: \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
		String dirname = "C:\\Users\\andre\\Desktop\\Calu\\2022\\Spring\\CET 350 Tech Computing using Java";
		// WITH A DIRECTORY IN YOUR COMPUTER!
		File f1 = new File(dirname);	// Create a new file object with the directory name above
		
		if(f1.isDirectory()) {			// Check if it actually is a directory
			System.out.println("Directory of "+dirname);	// it was a directory
			String s[] = f1.list();							// create a string array with a list of the following directory
			
			for(int i=0;i<s.length;i++) {					// output for the list and check if the found files are directory or files
				File f = new File(dirname+"/"+s[i]);		
				if(f.isDirectory()) {						// if the current file object is a directory...
					System.out.println(s[i]+" is a directory");		// output directory 
				}
				else{										// the current file object is not a directory...
					System.out.println(s[i]+" is a file");			// output file
				}
			}
		}
		else {							// It was not a directory, so it must be...
			System.out.println(dirname +" is a file");
		}
	}
}	
				