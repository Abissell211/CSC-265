import java.io.*;
import java.util.*;
public class Directory {	
	public static void main(String[] args) {
		int l = 0;
		String line = "";
		l = args.length;
		if(l>=1) {
			try {
				line = args[0];
				String dir = "C:\\Users\\andre\\Desktop\\Calu\\2022\\Spring\\CET 350 Tech Computing using Java\\Program Examples(CL)";
				File filedir = new File(line);
				File direct = new File(dir);
				filedir.createNewFile();
				direct.createNewFile();
				System.out.println("Input file is a directory: "+filedir.isDirectory());
				System.out.println("Input file is a directory: "+direct.isDirectory());
			}
			catch(Exception e) {
				e.printStackTrace();
			}
		}
	}
}