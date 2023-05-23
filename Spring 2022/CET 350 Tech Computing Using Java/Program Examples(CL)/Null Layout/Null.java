import java.awt.*;
import java.awt.event.*;
import java.io.*;

public class Null extends Frame implements WindowListener, ComponentListener, ActionListener{
	private static final long serialVersionUID = 10L;
// Constants are created by using the final declaration:
	private final int 	WIDTH = 640;		// initial frame width
	private final int 	HEIGHT = 400;		// initial frame height
	private final int 	BUTTONH = 20;		// button height
	private final int 	BUTTONHS = 5;		// button height spacing
// Program variable declarations:
	private int 		WinWidth = WIDTH;		// initial frame width
	private int 		WinHeight = HEIGHT;		// initial frame height
	private int 		ScreenWidth;			// drawing screen width
	private int 		ScreenHeight;			// drawing screen height
	private int 		WinTop = 10;			// top of frame
	private int 		WinLeft = 10;			// left side of frame
	private int 		BUTTONW = 50;			// initial button width
	private int 		CENTER = (WIDTH/2);		// initial screen center
	private int 		BUTTONS = BUTTONW/4;	// initial button spacing
// Inset: the spacings around the Frame that are used by the Frame border.
	private Insets 		I;					// insets of frame
// Buttons
	Button Start, Shape, Clear, Tail, Quit;
//**************************************************************************************//
//----------------------------------------main------------------------------------------//
//**************************************************************************************//	
	public static void main(String[] args) {
		Bounce b = new Bounce();		// create an object
	}
//**************************************************************************************//
//--------------------------------WindowListener Methods--------------------------------//
//**************************************************************************************//
	public void windowClosing(WindowEvent e) {
		stop();
	}
	public void windowClosed(WindowEvent e) {}
	public void windowOpened(WindowEvent e) {}
	public void windowActivated(WindowEvent e) {}
	public void windowDeactivated(WindowEvent e) {}
	public void windowIconified(WindowEvent e) {}
	public void windowDeiconified(WindowEvent e) {}
//**************************************************************************************//
//----------------------------------Bounce Constructor----------------------------------//
//**************************************************************************************//	
	public Bounce() {
		setLayout(null);				// use null layout of frame
		setVisible(true);				// make it visible
		MakeSheet();					// Determine the sizes for the sheet
		try {
			initComponents();			// try to initialize the components
		}
		catch (Exception e) {e.printStackTrace();}
		SizeScreen();					// size the items on the screen
	}
//**************************************************************************************//
//---------------------------------------Functions--------------------------------------//
//**************************************************************************************//
	//---------------------------------------MakeSheet--------------------------------------//
	private void MakeSheet() {			// gets the insets and adjusts the sizes of the items
		I = getInsets();				
		// make screen size the width of the frame less then left and right insets
		ScreenWidth = WinWidth - I.left - I.right;
		// make screen height the height of the frame less the top and bottom insets and space
		//  for two rows of buttons and two button spaces
		ScreenHeight = WinHeight - I.top - 2*(BUTTONH + BUTTONHS) - I.bottom;
		setSize(WinWidth, WinHeight);	// set the frame size
		CENTER = (ScreenWidth/2);		// determine the center of the screen
		BUTTONW = ScreenWidth/11;		// determine the width of the buttons (11 units)
		BUTTONS = BUTTONW/4;			// determine the button spacing
		setBackground(Color.lightGray);	// set the background color
	}
	//------------------------------------initComponents------------------------------------//
	public void initComponents() throws Exception, IOException {
		Start = new Button("Run");		// create the start button
		Shape = new Button("Circle");	// create the Shape button
		Clear = new Button("Clear");	// create the clear button
		Tail = new Button("No Tail");	// create the tail button
		Quit = new Button("Quit");		// create the quit button
		
		add("Center",Start);			// add the start button to the frame
		add("Center",Shape);			// add the shape button to the frame
		add("Center",Tail);				// add the tail button to the frame
		add("Center",Clear);			// add the clear button to the frame
		add("Center",Quit);				// add the quit button to the frame
		
		Start.addActionListener(this); 	// add the start button listener
		Shape.addActionListener(this); 	// add the shape button listener
		Tail.addActionListener(this); 	// add the tail button listener
		Clear.addActionListener(this); 	// add the clear button listener
		Quit.addActionListener(this); 	// add the quit button listener
		this.addComponentListener(this);// add the component listener
		this.addWindowListener(this); 	// add the window listener
		setPreferredSize(new Dimension(WIDTH,HEIGHT));
		setMinimumSize(getPreferredSize());
		setBounds(WinLeft,WinTop,WIDTH,HEIGHT);	// size and position the frame
		validate();						// validate the layout
	}
	//--------------------------------------SizeScreen--------------------------------------//
	private void SizeScreen() {
		// position the buttons
		Start.setLocation(CENTER-2*(BUTTONW+BUTTONS)-BUTTONW/2,ScreenHeight+BUTTONHS+I.top);
		Shape.setLocation(CENTER-BUTTONW-BUTTONS-BUTTONW/2,ScreenHeight+BUTTONHS+I.top);
		Tail.setLocation(CENTER-BUTTONW/2,ScreenHeight+BUTTONHS+I.top);
		Clear.setLocation(CENTER+BUTTONS+BUTTONW/2,ScreenHeight+BUTTONHS+I.top);
		Quit.setLocation(CENTER+BUTTONW+2*BUTTONS+BUTTONW/2,ScreenHeight+BUTTONHS+I.top);
		
		// size the buttons
		Start.setSize(BUTTONW,BUTTONH);
		Shape.setSize(BUTTONW,BUTTONH);
		Tail.setSize(BUTTONW,BUTTONH);
		Clear.setSize(BUTTONW,BUTTONH);
		Quit.setSize(BUTTONW,BUTTONH);
	}
	//-----------------------------------------stop-----------------------------------------//
	public void stop() {
		Start.removeActionListener(this);
		Shape.removeActionListener(this);
		Clear.removeActionListener(this);
		Tail.removeActionListener(this);
		Quit.removeActionListener(this);
		this.removeComponentListener(this);
		this.removeWindowListener(this);
		dispose();
		System.exit(0);
	}
//**************************************************************************************//
//-----------------------------------Frame Management-----------------------------------//
//**************************************************************************************//
// When the Frame (Component) is resized we just need to get the new size, recalculate the
//  the sizes and apply the new sizes to the objects.
	
	// resize the Frame and the objects:
	public void componentResized(ComponentEvent e) {
		WinWidth = getWidth();
		WinHeight = getHeight();
		MakeSheet();
		SizeScreen();
	}
	public void componentHidden(ComponentEvent e) {
		
	}
	public void componentShown(ComponentEvent e) {
		
	}
	public void componentMoved(ComponentEvent e) {
		
	}
	public void actionPerformed(ActionEvent e) {
		Object source = e.getSource();
		if(source==Start) {
			if(Start.getLabel()=="Pause")
				Start.setLabel("Run");
			else
				Start.setLabel("Pause");
		}
		if(source==Shape) {
			if(Shape.getLabel()=="Circle") 
				Shape.setLabel("Square");
			else
				Shape.setLabel("Circle");
		}
		if(source==Tail) {
			if(Tail.getLabel()=="Tail")
				Tail.setLabel("No tail");
			else
				Tail.setLabel("Tail");
		}
		if(source==Clear) {}
		if(source==Quit) {
			stop();
		}
	}
}
