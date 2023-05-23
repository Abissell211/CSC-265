//Andrew Bissell, Daniel Nash, Noelle Nieves
//GROUP 1 
//Tech Computing Using Java CET-350
//File Copy GUI
//bis3683@calu.edu, nas8662@calu.edu, nie9236@calu.edu
package Program3;

import java.awt.*;
import java.awt.event.*;
import java.io.*;

// inherit Frame and implement the WindowListener
public class Main extends Frame implements WindowListener, ActionListener {
	private static final long serialVersionUID = 1L;	
//-----------------------------------------Labels----------------------------------------//
	Label srcLblHeader = new Label("Source:");
	Label srcLblInfo = new Label("");
	Label fileNameLblHeader = new Label("File Name:");
	Label targetLblInfo = new Label("Select Target Directory:");
	Label msg = new Label("");	
//----------------------------------------Buttons---------------------------------------//
	Button btnTarget = new Button("Target");
	Button btnOk = new Button("OK");	
//------------------------------------------List----------------------------------------//
	List list = new List(13);				// create a 13 row List	
//---------------------------------------TextField--------------------------------------//
	TextField FileName = new TextField(100);	// creates an empty 100 coulumn TextField called FileName
	String fileName;	
//---------------------------------------Flags------------------------------------------//
	boolean isSourceSet;
	boolean isTargetSet;
	boolean isOutFileSet;

	File curDir;	
//**************************************************************************************//
//----------------------------------Window Constructor----------------------------------//
//**************************************************************************************//
	Main(File dir) {
		//set dir to curDir
		curDir = new File(dir.getAbsolutePath());
		
		//set flags
		this.isSourceSet = false;
		this.isTargetSet = false;
		this.isOutFileSet = false;
		
		GridBagConstraints c = new GridBagConstraints();
		GridBagLayout displ = new GridBagLayout();
		
		double colWeight[] = {1,1,1,8,8};
		double rowWeight[] = {8,1,1,1,1};
		int colWidth[] = {1,1,1,8,8};
		int rowHeight[] = {8,1,1,1,1};
		
		displ.rowHeights = rowHeight;
		displ.columnWidths = colWidth;
		displ.columnWeights = colWeight;
		displ.rowWeights = rowWeight;
		
		this.setBounds(0,0,1000,500);			// sets it at (x=0, y=0, width = 1000, height = 500)
		this.setLayout(displ);					// set displ as the layout manager
		
		c.anchor = GridBagConstraints.CENTER;
		c.weightx = 1;
		c.weighty = 1;
		c.gridwidth = 1;
		c.gridheight = 1;
		c.fill = GridBagConstraints.BOTH;
//-----------------------------------------Title----------------------------------------//
		this.setTitle(curDir.getAbsolutePath());	
//------------------------------------------List----------------------------------------//
		list.setSize(300,500); 				// set an initial size of 300 pixel by 500 pixel
		c.gridwidth = 5;					
		c.gridheight = 1;					
		c.fill = GridBagConstraints.BOTH;	// stretch to fill both directions
		c.gridx = 0;						// position the List starting in cell 0,0 (upper left)
		c.gridy = 0;
		displ.setConstraints(list, c); 		// apply the constraints
		this.add(list);						// add the List to the Frame
		list.addActionListener(this);		// add the ActionListener to the List
//--------------------------------------Source Label------------------------------------//
		c.gridx = 1;
		c.gridy = 1;
		c.gridwidth = 2;
		c.fill = GridBagConstraints.HORIZONTAL;
		displ.setConstraints(srcLblHeader, c);
		this.add(srcLblHeader);	
//--------------------------------------Target Button------------------------------------//		
		c.gridx = 1;
		c.gridy = 2;
		c.gridwidth = 2;
		c.fill = GridBagConstraints.HORIZONTAL;
		displ.setConstraints(btnTarget, c);
		btnTarget.setEnabled(false);
		this.add(btnTarget);	
//-------------------------------------File Name Label-----------------------------------//		
		c.gridx = 0;
		c.gridy = 3;
		c.gridwidth = 2;
		c.fill = GridBagConstraints.HORIZONTAL;
		displ.setConstraints(fileNameLblHeader, c);
		this.add(fileNameLblHeader);	
//----------------------------------<Source File> Label---------------------------------//
		c.gridx = 3;
		c.gridy = 1;
		c.gridwidth = 9;
		c.fill = GridBagConstraints.HORIZONTAL;
		displ.setConstraints(srcLblInfo, c);
		this.add(srcLblInfo);	
//----------------------------Select Target Directory: Label----------------------------//
		c.gridx = 3;
		c.gridy = 2;
		displ.setConstraints(targetLblInfo, c);
		this.add(targetLblInfo);	
//---------------------------------------TextField--------------------------------------//
		c.gridx = 3;						
		c.gridy = 3;						
		c.gridwidth = 1;					
		displ.setConstraints(FileName, c);	
		this.add(FileName);					
		FileName.addActionListener(this);	
		FileName.setText("");					
//-----------------------------------<Messages> Label-----------------------------------//
		c.gridx = 3;
		c.gridy = 4;
		displ.setConstraints(msg, c);
		this.add(msg);	
//---------------------------------------OK Button--------------------------------------//
		c.gridx = 4;
		c.gridy = 3;
		c.gridwidth = 1;
		c.fill = GridBagConstraints.HORIZONTAL;
		displ.setConstraints(btnOk, c);
		this.add(btnOk);
		
		this.pack();
		this.setVisible(true);				// set the frame visible
		btnTarget.addActionListener(this);
		btnOk.addActionListener(this);
		this.addWindowListener(this);		// add the Window Listener to the frame
		
		display("");  //passed null string in constructor
	}	
//**************************************************************************************//
//-----------------------------------------main-----------------------------------------//
//**************************************************************************************//
	public static void main(String[] args) {
		int paramLen = args.length;						// integer check for parameter
		String paramStr = "";							// String to hold parameter passed
		boolean invalidDirectory = false;				// flag to quit if parameter is not a directory
		
		
		if (paramLen >= 1) {							// if a parameter is found
			try {
				paramStr = args[0]; 					// assign first parameter to the line string
				File filedir = new File(paramStr);		// create a file class object with the input parameter
				//filedir.createNewFile();				// **we do not want to create a new file, only reference the virtual object above
				
				System.out.println("Parameter found attempting to create a directory with "+paramStr);
				
				if(filedir.isDirectory() == true) {		// Check to see if the file is a directory
					new Main(new File(filedir.getAbsolutePath()));
					System.out.println(paramStr + " directory status: " + filedir.isDirectory());
					System.out.println("Found file that was a directory move to constructor");
				} else {								// The file wasn't a directory
					System.out.println(paramStr + " Directory status: " + filedir.isDirectory());
					invalidDirectory = true;			// Set the flag to quit the program
				}
			} catch(Exception e) {						// check for the file creation
				e.printStackTrace();
				System.out.println("ERROR in file creation!");
				invalidDirectory = true;
			}
		} else {										// if no parameter was found
			new Main(new File(new File(System.getProperty("user.dir")).getAbsolutePath()));
			System.out.println("No parameter passed move to constructor using the absolute path");
		}
		
		
		if (invalidDirectory) {  						// if the quit flag was set, quit program
			System.out.println("Parameter was not a directory, quitting program...");
		}				
		
	}
	
//**************************************************************************************//
//--------------------------------WindowListener Methods--------------------------------//
//**************************************************************************************//
	public void windowClosing(WindowEvent e) {
		this.removeWindowListener(this);
		btnTarget.removeActionListener(this);
		btnOk.removeActionListener(this);
		this.dispose();
	}
	public void windowClosed(WindowEvent e) {}
	public void windowOpened(WindowEvent e) {}
	public void windowActivated(WindowEvent e) {}
	public void windowDeactivated(WindowEvent e) {}
	public void windowIconified(WindowEvent e) {}
	public void windowDeiconified(WindowEvent e) {}
	public void actionPerformed(ActionEvent e) {
		Object source = e.getSource();		// get the current event source
		
		if(source == btnTarget) {
			msg.setText("");
			this.targetLblInfo.setText(this.curDir.getAbsolutePath());
			this.isTargetSet = true;
		}
		if(source == btnOk) {
			this.msg.setText("");
			this.fileName = this.FileName.getText();
			if (fileName.length() != 0) {
				this.isOutFileSet = true;
				CopyFile();
			//check for source selected target select on "enter" press
			} else if(this.isSourceSet) {
				this.targetLblInfo.setText(this.curDir.getAbsolutePath());
			//notification if the source wasn't set before to get target from an "enter" press
			} else {
				msg.setText(msg.getText() + "No Source selected, target not set");
			}
		}
		if(source == FileName) {
			//String filename = FileName.getText();  //may not need the shared class String, in which case will use this one
			this.msg.setText("");
			this.fileName = this.FileName.getText();  //gets the FileName text
			
			//check for filecopy
			if (this.fileName.length() != 0) {
				this.isOutFileSet = true;
				CopyFile();
			//check for source selected target select on "enter" press
			}  else if(this.isSourceSet) {
				this.targetLblInfo.setText(this.curDir.getAbsolutePath());
			//notification if the source wasn't set before to get target from an "enter" press
			} else {
				msg.setText(msg.getText() + "No Source selected, target not set");
			}
		}
		if(source == list) {
			String item = list.getSelectedItem();  //get selected item
			this.msg.setText("");
			
			if (item != null) {
				if (item.endsWith("+")) {
					item = item.substring(0, item.length() - 2);  //trim off XS characters
				}
				display(item);  //display new directory
			}
		}
	}
	
	
	public void display(String name) {
		String[] filenames;
		int i, j; 					// loop variables
		boolean foundDir; 		//found child that is a directory
		
		if (name.length() != 0) {  	
			
			//is parent?
			if (name.equals("..")) {  							
				this.curDir = new File(this.curDir.getParent()); 		
				
			} else { 											
				//not parent-->check if directory or file
				File f = new File(this.curDir, name);
				
				if (f.isDirectory()) {
					//is directory-->make new current directory
					this.curDir = new File(this.curDir, name);
					
				} else {
					//is file-->determine program mode
					if (!this.isSourceSet || !this.isTargetSet) {
						this.srcLblInfo.setText(this.curDir.getAbsolutePath() + "\\" + name);
						this.isSourceSet = true;
						this.btnTarget.setEnabled(true);
					} else {
						
						//source and target satisfied, populate output file name and set flag
						this.FileName.setText(name);
						this.isOutFileSet = true;
					}
				}
			}
		}
		
		filenames = this.curDir.list();  // get an array of the files/folders of the current directory
		this.setTitle(this.curDir.getAbsolutePath());
		
		if (filenames != null) {
			//iterate through contents of curDir
			for (i = 0; i < filenames.length; i++) {
				//check if curDir file/folder is a directory itself
				
				File f = new File(this.curDir, filenames[i]);
				if (f.isDirectory()) { 
					
					//is a directory, check its own contents for the presence of a child directory
					String[] children = f.list();  //gets a list of the content(s) of the child directory
					j = 0;
					foundDir = false;
					
					//TEST// System.out.println("parent[" + i + "/"+ (filenames.length-1) +"]:" + filenames[i]); //test
					while (j < children.length && !foundDir) {
						//TEST// System.out.println("children[" + j + "/"+ (children.length-1) +"]:" + children[j]);  //test
						if (f.isDirectory()) {		// if the child is a directory,
							filenames[i] += " +";	// add the '+'
							foundDir = true;
						}
						j++;
					}
				}
			}
		}
		
		//clear existing list
		this.list.removeAll();
		
		//check for parent directory
		if (this.curDir.getParent() != null) {
			this.list.add("..");
		}
		
		//display the list
		for (i = 0; i < filenames.length; i++) {
			this.list.add(filenames[i]);
		}
		
		
	}
	
	public void CopyFile() {
		if (this.isOutFileSet && this.isSourceSet && this.isTargetSet) {
			int c;
			File testMe = new File(this.targetLblInfo.getText() + "\\" + this.FileName.getText());  //to check if output file exists in target directory
			
			if (testMe.exists()) {
				//file exists, print message
				this.msg.setText("");
				this.msg.setText(this.msg.getText() + "You will be overwriting the existing file: \"" + this.FileName.getText() + "\"");
			}
			try {
				BufferedReader infile = new BufferedReader(new FileReader(this.srcLblInfo.getText()));
				PrintWriter outfile = new PrintWriter(this.targetLblInfo.getText() + "\\" + this.FileName.getText());
				
				while ((c = infile.read()) != -1) {
					outfile.write(c);
				}
				
				infile.close();
				outfile.close();
				
			} catch (FileNotFoundException e) {
				System.out.println("File not found!");
			} catch (IOException e) {
				System.out.println("IOException when trying to read from file!");
			}
			
			//resets everything
			this.isOutFileSet = false;
			this.isSourceSet = false;
			this.isTargetSet = false;
			
			this.FileName.setText("");
			this.msg.setText("File Copied");
			this.srcLblInfo.setText("");
			this.targetLblInfo.setText("");
			this.btnTarget.setEnabled(false);			
		} else {
			msg.setText(msg.getText() + "Target not set!");
		}				
	}	
}