//Andrew Bissell, Daniel Nash
//GROUP 1 
//Tech Computing Using Java CET-350
//Bouncing Object Program
//bis3683@calu.edu, nas8662@calu.edu, nie9236@calu.edu
package Bounce;

import java.awt.*;
import java.awt.event.*;
import java.io.*;

public class Bounce extends Frame implements WindowListener, ComponentListener, ActionListener, AdjustmentListener, Runnable{
//**************************************************************************************//
//-------------------------------------Constants----------------------------------------//
//**************************************************************************************//
	private static final long serialVersionUID = 10L;
// Constants are created by using the final declaration:
	private final int 	WIDTH = 640;			// initial frame width
	private final int 	HEIGHT = 400;			// initial frame height
	private final int 	BUTTONH = 20;			// button height
	private final int 	BUTTONHS = 5;			// button height spacing
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
	private Insets 		I;						// insets of frame
// Buttons
	Button Start, Shape, Clear, Tail, Quit;
// Constants for Scrollbars/rectangle/circle
	private final int 	MAXObj = 100;			// maximum object size
	private final int 	MINObj = 10;			// minimum object size
	private final int 	SPEED = 100;				// initial speed
	private final int 	SBvisible = 10;			// visible Scroll Bar
	private final int 	SBunit = 1;				// Scrollbar unit step size
	private final int 	SBblock = 10;			// Scrollbar block step size
	private final int 	SCROLLBARH = BUTTONH;	// scrollbar height
	private final int 	SOBJ = 21;				// initial object width
// Variables for Scrollbars/rectangle/circle	
	private int 		SObj = SOBJ;			// initial object width
	private int 		SpeedSBmin = 1;			// speed scrollbar minimum value
	private int 		SpeedSBmax = 200+SBvisible;	//speed scrollbar maximum value with visible offset
	private int 		SpeedSBinit = SPEED;	// Initial speed scrollbar value
	private int 		ScrollBarW;				// scrollbar width
// Add objects
	private 			Objc Obj;				// object to draw
	private Label SPEEDL = new Label("Speed", Label.CENTER);	// label for speed scroll bar
	private Label SIZEL = new Label("Size", Label.CENTER);		// label for size scroll bar
	Scrollbar 			SpeedScrollBar, ObjSizeScrollBar;					// scroll bars
// Run class	
	private final double DELAY = 500;				// timer delay constant
	
	private boolean run;						// for the program loop
	private boolean TimePause;					// to identify run/pause
	private boolean started;					// to identify if the animation started
	private boolean tailflag = true;			// to identify if tail is on/off (true/false)
	private int 	delay;						// for the current time delay
	
	private Thread thethread;					// thread for timer delay
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
		started = false;
		setLayout(null);				// use null layout of frame
		setVisible(true);				// make it visible
		MakeSheet();					// Determine the sizes for the sheet
		try {
			initComponents();			// try to initialize the components
		}
		catch (Exception e) {e.printStackTrace();}
		SizeScreen();					// size the items on the screen
		start();
	}
//**************************************************************************************//
//---------------------------------------Functions--------------------------------------//
//**************************************************************************************//
	//---------------------------------------MakeSheet--------------------------------------//
	// New Frame information and recalculation of Frame sizes.
	// Gets the insets and adjusts the sizes of the items
	private void MakeSheet() {			
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
		ScrollBarW = 2*BUTTONW;			// determine the scroll bar width
	}
	//------------------------------------initComponents------------------------------------//
	// Adding the objects
	public void initComponents() throws Exception, IOException {
		// Run
		TimePause = true;
		run = true;
		
		// Buttons
		Start = new Button("Run");		// create the start button
		Shape = new Button("Circle");	// create the Shape button
		Clear = new Button("Clear");	// create the clear button
		Tail = new Button("No Tail");	// create the tail button
		Quit = new Button("Quit");		// create the quit button
		
		// ScrollBar SPEED	
		SpeedScrollBar = new Scrollbar(Scrollbar.HORIZONTAL);	// create the speed scroll bar
		SpeedScrollBar.setMaximum(SpeedSBmax);					// set the max speed	
		SpeedScrollBar.setMinimum(SpeedSBmin);					// set the min speed
		SpeedScrollBar.setUnitIncrement(SBunit);				// set the unit increment
		SpeedScrollBar.setBlockIncrement(SBblock);				// set the block increment
		SpeedScrollBar.setValue(SpeedSBinit);					// set the initial value
		SpeedScrollBar.setVisibleAmount(SBvisible);				// set the visible size
		SpeedScrollBar.setBackground(Color.gray);				// set the background color
		setTimeDelay();
		
		// ScrollBar SIZE
		ObjSizeScrollBar = new Scrollbar(Scrollbar.HORIZONTAL);	// create the size scroll bar
		ObjSizeScrollBar.setMaximum(MAXObj);					// set the max speed	
		ObjSizeScrollBar.setMinimum(MINObj);					// set the min speed
		ObjSizeScrollBar.setUnitIncrement(SBunit);				// set the unit increment
		ObjSizeScrollBar.setBlockIncrement(SBblock);			// set the block increment
		ObjSizeScrollBar.setValue(SOBJ);						// set the initial value
		ObjSizeScrollBar.setVisibleAmount(SBvisible);			// set the visible size
		ObjSizeScrollBar.setBackground(Color.gray);				// set the background color
		Obj = new Objc(SObj, ScreenWidth, ScreenHeight);		// create the object
		Obj.setBackground(Color.cyan);							// set the background color
		// Buttons
		add("Center",Start);			// add the start button to the frame
		add("Center",Shape);			// add the shape button to the frame
		add("Center",Tail);				// add the tail button to the frame
		add("Center",Clear);			// add the clear button to the frame
		add("Center",Quit);				// add the quit button to the frame
		// Scrollbar
		add(SpeedScrollBar);			// add the speed scroll bar to the frame
		add(ObjSizeScrollBar);			// add the size scroll bar to the frame
		add(SPEEDL);					// add the speed label to the frame
		add(SIZEL);						// add the size label to the frame
		add(Obj);						// add the object to the frame
		// Buttons
		Start.addActionListener(this); 	// add the start button listener
		Shape.addActionListener(this); 	// add the shape button listener
		Tail.addActionListener(this); 	// add the tail button listener
		Clear.addActionListener(this); 	// add the clear button listener
		Quit.addActionListener(this); 	// add the quit button listener
		// Scrollbar
		SpeedScrollBar.addAdjustmentListener(this); 	// add the speed scroll bar listener
		ObjSizeScrollBar.addAdjustmentListener(this); 	// add the size scroll bar listener
		
		this.addComponentListener(this);		// add the component listener
		this.addWindowListener(this); 			// add the window listener
		setPreferredSize(new Dimension(WIDTH,HEIGHT));
		setMinimumSize(getPreferredSize());
		setBounds(WinLeft,WinTop,WIDTH,HEIGHT);	// size and position the frame
		validate();								// validate the layout
		}
	
	//updates time delay relative to speed scrollbar
	private void setTimeDelay() {
		delay = (int)(DELAY/(double)SpeedScrollBar.getValue());
	}
	//--------------------------------------SizeScreen--------------------------------------//
	private void SizeScreen() {
		// position the buttons
					   //(					X				  ,				Y			   )
		Start.setLocation(CENTER-2*(BUTTONW+BUTTONS)-BUTTONW/2,	ScreenHeight+BUTTONHS+I.top);
		Shape.setLocation(CENTER-BUTTONW-BUTTONS-BUTTONW/2,		ScreenHeight+BUTTONHS+I.top);
		Tail.setLocation(CENTER-BUTTONW/2,						ScreenHeight+BUTTONHS+I.top);
		Clear.setLocation(CENTER+BUTTONS+BUTTONW/2,				ScreenHeight+BUTTONHS+I.top);
		Quit.setLocation(CENTER+BUTTONW+2*BUTTONS+BUTTONW/2,	ScreenHeight+BUTTONHS+I.top);
		
		// size the buttons
					// (Width,Height)
		Start.setSize(BUTTONW,BUTTONH);
		Shape.setSize(BUTTONW,BUTTONH);
		Tail.setSize(BUTTONW,BUTTONH);
		Clear.setSize(BUTTONW,BUTTONH);
		Quit.setSize(BUTTONW,BUTTONH);
		
		// size and position the drawing object, scrollbars and labels
								  //(				  X  				,				Y			   )
		SpeedScrollBar.setLocation(I.left+BUTTONS, ScreenHeight+BUTTONHS+I.top);
		ObjSizeScrollBar.setLocation(WinWidth-ScrollBarW-I.right-BUTTONS, ScreenHeight+BUTTONHS+I.top);
		SPEEDL.setLocation(I.left+BUTTONS, ScreenHeight+BUTTONHS+BUTTONH+I.top);
		SIZEL.setLocation(WinWidth-ScrollBarW-I.right, ScreenHeight+BUTTONHS+BUTTONH+I.top);
							  //(	  X    ,		Y	  )
		SpeedScrollBar.setSize(ScrollBarW, SCROLLBARH);
		ObjSizeScrollBar.setSize(ScrollBarW, SCROLLBARH);
		SPEEDL.setSize(ScrollBarW, BUTTONH);
		SIZEL.setSize(ScrollBarW, SCROLLBARH);
								//(	  X  ,	Y  ,   Width   ,   Height	)
		Obj.setBounds(I.left, I.top, ScreenWidth, ScreenHeight);
	}
	//----------------------------------------start-----------------------------------------//
	public void start() {
		Obj.repaint();					// repaint the object
		
		if (thethread == null) {
			thethread = new Thread(this);
			thethread.start();
		}
	}
	//-----------------------------------------stop-----------------------------------------//
	// Quit button and window closing button
	public void stop() {
		run = false;
		thethread.interrupt();
		
		// Buttons
		Start.removeActionListener(this);
		Shape.removeActionListener(this);
		Clear.removeActionListener(this);
		Tail.removeActionListener(this);
		Quit.removeActionListener(this);
		// Scrollbar
		SpeedScrollBar.removeAdjustmentListener(this);
		ObjSizeScrollBar.removeAdjustmentListener(this);
		
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
		
		//check the object size
		
		MakeSheet();
		SizeScreen();
		
		//check the object size
		//if smaller than the 
		
		Obj.reSize(ScreenWidth, ScreenHeight);  //updates the private vars of the object. Recalculates min and max values
		checkObjSize();
	}
	public void componentHidden(ComponentEvent e) {
		
	}
	public void componentShown(ComponentEvent e) {
		
	}
	public void componentMoved(ComponentEvent e) {
		
	}
	public void actionPerformed(ActionEvent e) {
		Object source = e.getSource();
		
		if(source==Start) {					// Start button pressed
			if(Start.getLabel()=="Pause") {		// if the button label is Paused
				Start.setLabel("Run");				// set label to Run
				TimePause = true;					// Set the Pause flag false
			} else {							// else
				Start.setLabel("Pause");			// set label to Pause
				TimePause = false;					// set the Pause flag true
				thethread.interrupt();				// interrupt the thread
			}
		}
		
		if(source==Shape) {					// Shape button pressed
			//clears if not begun yet
			if (!started) {
				Obj.Clear();
			}
			
			if(Shape.getLabel()=="Circle") {	// if the button label is Circle
				Shape.setLabel("Square");			// set label to Square
				Obj.rectangle(false);				// change object to a circle
			} else {							// else
				Shape.setLabel("Circle");			// set label to Circle
				Obj.rectangle(true);				// change object to a rectangle
			}
			
			Obj.repaint();						// Repaint the object
		}
		
		if(source==Tail) {					// Tail button pressed
			if(Tail.getLabel()=="Tail") {		// if the button label is Tail
				Tail.setLabel("No Tail");			// set label to No tail
				tailflag = true;					
			} else {							// else
				Tail.setLabel("Tail");				// set label to Tail
				tailflag = false;					
			}
			
			Obj.ChangeTailFlag(tailflag);  //updates object's tail flag
		}
		
		if(source==Clear) {					// Clear button pressed
			Obj.Clear();						// Clear object(s)
			Obj.repaint();						// Repaint the object
		}
		
		if(source==Quit) {					// Quit button pressed
			stop();								// Stop the program and close
		}
		
	}
	public void adjustmentValueChanged(AdjustmentEvent e) {
		int TS;
		int prevSize = Obj.GetSize();  //gets SObj from object
		Scrollbar sb = (Scrollbar)e.getSource();// get the scrollbar that triggered the event
		
		// Set the speed of the object via scrollbar
		if(sb==SpeedScrollBar) {
			setTimeDelay();  //updates the time delay
			thethread.interrupt();
		}				
		
		if(sb==ObjSizeScrollBar)  {				// Set the size of the object via scrollbar
			TS = e.getValue(); 						// get the value
			TS = (TS/2)*2+1;						// Make odd to account for center position i.e. +

			int newXMax = Obj.GetXValue() + ((TS-1)/2);
			int newYMax = Obj.GetYValue() + ((TS-1)/2);
			
			int newXMin = Obj.GetXValue() - ((TS-1)/2);
			int newYMin = Obj.GetYValue() - ((TS-1)/2);
			
			//check if new size fits screen
			if (newXMax >= ScreenWidth-2 || newXMin <= 1) {
				sb.setValue(prevSize);
			} else if (newYMax >= ScreenHeight-2 || newYMin <= 1) {
				sb.setValue(prevSize);
			} else {
				Obj.update(TS);
			}
			//update if fits
			
			//Obj.update(TS);							// change the size in the drawing object
		}
		
		Obj.repaint();							// force repaint
	}
//**************************************************************************************//
//------------------------------------Thread Methods------------------------------------//
//**************************************************************************************//	
	public void run() {
		while(run) {
			if(!TimePause) {
				try {
					started = true;
					Thread.sleep(delay);
					// update the size in the object to the new size
					Obj.reSize(ScreenWidth, ScreenHeight);  //update the size of the object within the object
					Obj.repaint();				// repaint the object
					// move the object to its next location
						// the old size, x, and y values are kept to erase the current object
						//	before drawing the new object when no tails are requested.
					Obj.moveObject();
				} catch (InterruptedException e) {}
			}
			try {
				Thread.sleep(1);
			} catch (InterruptedException e) {}
		}
		// exit run method and the animation will stop
	}	
	
	//checks if the object is beyond the screen size, repositions back inside boundaries if it is beyond
	public void checkObjSize() {
		int right;
		int bottom;
		int x = Obj.GetXValue();  //temp to work with x coordinate
		int y = Obj.GetYValue();  //temp to work with y coordinate
		
		//get the x, y, and object size
		//calculate the right and bottom of the object
		right = x + ((Obj.GetSize() - 1) / 2);   //minus 1 to get an even value since SObj is odd
		bottom = y + ((Obj.GetSize() - 1) / 2);  //minus 1 to get an even value since SObj is odd

		
		//test if object is beyond the new screen size
		if (right > ScreenWidth && bottom > ScreenHeight) {
			//exceeds both width AND height, change x and y
			
			//move x and y to a valid coordinate within the frame (may need to consider if they are EQUAL)
			Obj.SetXValue(ScreenWidth - ((Obj.GetSize()-1)/2) - 1);
			Obj.SetYValue(ScreenHeight - ((Obj.GetSize()-1)/2) - 1);
			
		} else if (right > ScreenWidth) {
			//exceeds width only, change x only
			Obj.SetXValue(ScreenWidth - ((Obj.GetSize()-1)/2) -1);
			
		} else if (bottom > ScreenHeight) {
			//exceeds height only, change y only
			Obj.SetYValue(ScreenHeight - ((Obj.GetSize()-1)/2) - 1);
		}
		
		//Obj.repaint();
	}
	


}

class Objc extends Canvas {
//**************************************************************************************//
//-------------------------------------Constants----------------------------------------//
//**************************************************************************************//
	private static final long serialVersionUID = 11L;
	private int 	ScreenWidth;
	private int 	ScreenHeight;
	private int 	SObj;
	
	private int 	x,y;
	private boolean rect = true;
	private boolean clear = false;
	
	private boolean tail;				// to identify if tail is on/off (true/false)
	
	private int 	ymin, ymax, xmin, xmax, xold, yold;
	private boolean right, down;
//**************************************************************************************//
//------------------------------Drawing Object Constructor------------------------------//
//**************************************************************************************//	
	public Objc(int SB, int w, int h) {
	// Set the screen width/height, init the flags, and determine the center of the screen for the obj
		ScreenWidth = w;
		ScreenHeight = h;
		
		SObj = SB;
		rect = true;
		clear = false;
		right = true;
		down = true;
		tail = true;
		
		calcExtremes(w, h);  //sets the xmin, xmax, ymin, and ymax for the object 
		
		y = (SObj-1)/2 + 2;  //need to add one to move away from border at beginning
		x = (SObj-1)/2 + 2;
	}
//**************************************************************************************//
//--------------------------------Drawing Object Mutators-------------------------------//
//**************************************************************************************//
	//calculate min and max x/y sizes for the current display size and current object size
	public void calcExtremes(int ScreenWidth, int ScreenHeight) {
		xmax = ScreenWidth - ((SObj-1)/2);  //closest obj can get to the right side
		xmin = ((SObj - 1)/2);  //closest the obj can get to the left side
		
		ymax = ScreenHeight - ((SObj-1)/2);  //closest obj can get to the bottom 
		ymin = ((SObj - 1)/2);  //closest the obj can get to the top side
		
	}
	//Checks if current x coordinate is within boundaries of frame. Returns boolean accordingly
	public boolean checkX() {
		boolean fits;
		if (x >= xmax-2 || x-1 <= xmin) {
			fits = false;
		} else {
			fits = true;
		}
		
		return fits;
		
	}
	//Checks if current y coordinate is within boundaries of frame. Returns boolean accordingly
	public boolean checkY() {
		boolean fits;
		if (y >= ymax-2 || y-1 <= ymin) {
			fits = false;
		} else {
			fits = true;
		}
		
		return fits;
	}
	// Change the shape (flag)
	public void rectangle(boolean r) {
		rect = r;
	}
	// Update the size
	public void update(int NS) {
		SObj = NS;
	}
	// UPDATES THE VALUES for screen size and the min and max x/y values. doesnt change anything on screen
	public void reSize(int w, int h) {
		ScreenWidth = w;
		ScreenHeight = h;
		//calcExtremes(ScreenWidth, ScreenHeight);
	}
	// Set the clear flag
	public void Clear() {
		clear = true;
	}
	public void ChangeTailFlag(boolean input) {
		if(input)
			tail = true;
		else
			tail = false;
	}
	public void SetXValue(int in) {
		x = in;
	}
	public void SetYValue(int in) {
		y = in;
	}
//**************************************************************************************//
//-------------------------------Drawing Object Accessors-------------------------------//
//**************************************************************************************//
	public boolean GetTailFlag() {
		return tail;
	}
	public int GetXValue() {
		return x;
	}
	public int GetYValue() {
		return y;
	}
	public int GetSize() {
		return SObj;
	}
//**************************************************************************************//
//-----------------------------------------Paint----------------------------------------//
//**************************************************************************************//
	// Draw a red border around the screen then preform the drawing, passing the Graphics page to update
	public void paint(Graphics g) {
		g.setColor(Color.red);
		g.drawRect(0, 0, ScreenWidth-1, ScreenHeight-1);
		update(g);
	}
//**************************************************************************************//
//-----------------------------------------Update---------------------------------------//
//**************************************************************************************//
	// When the clear flag is set, a call to the super component will be made to clear the Canvas
	public void update(Graphics g) {
		if(clear) {
			super.paint(g);
			clear = false;
			g.setColor(Color.red);
			g.drawRect(0, 0, ScreenWidth-1, ScreenHeight-1);
		}
		
		//no tail so remove old object
		if(!tail) {
			g.setColor(getBackground());
			if(rect)
				g.fillRect(xold-(SObj-1)/2-1, yold-(SObj-1)/2-1, SObj+2, SObj+2);
			else
				g.fillOval(xold-(SObj-1)/2-1, yold-(SObj-1)/2-1, SObj+2, SObj+2);
		}
		
		//draw NEW object at new position
		if(rect) {
			g.setColor(Color.lightGray);
			g.fillRect(x-(SObj-1)/2,	y-(SObj-1)/2,	SObj,	SObj);
			g.setColor(Color.black);
			g.drawRect(x-(SObj-1)/2,	y-(SObj-1)/2,	SObj-1,	SObj-1);
		}
		else {	// Circle
			g.setColor(Color.lightGray);
			g.fillOval(x-(SObj-1)/2,	y-(SObj-1)/2,	SObj,	SObj);
			g.setColor(Color.black);
			g.drawOval(x-(SObj-1)/2,	y-(SObj-1)/2,	SObj-1,	SObj-1);
		}
		
		//new coordinates-->old
		xold = x;
		yold = y;
	}
//**************************************************************************************//
//------------------------------------------Move----------------------------------------//
//**************************************************************************************//
	public void moveObject() {
		//checks if curr coordinates are valid and compliments motion flags accordingly
		if (!checkX()) {
			right = !(right);  //compliments the right flag
		}
		if (!checkY()) {
			down = !(down); //compliments the down flag
		}
		
		//horizontal motion
		if (right) {
			x = x + 1;
		} else {
			x = x - 1;
		}
		
		//vertical motion
		if (down) {
			y = y + 1;
		} else {
			y = y - 1;
		}
			
			
	}
}