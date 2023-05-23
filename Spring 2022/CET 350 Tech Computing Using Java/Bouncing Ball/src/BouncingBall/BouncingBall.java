//Andrew Bissell, Daniel Nash
//GROUP 1 
//Tech Computing Using Java CET-350
//Bouncing Ball Program
//bis3683@calu.edu, nas8662@calu.edu
package BouncingBall;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.Vector;

public class BouncingBall extends Frame implements WindowListener, ComponentListener,
ActionListener, AdjustmentListener, Runnable, MouseListener, MouseMotionListener{
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
// Inset: the spacings around the Frame that are used by the Frame border.
	private Insets 		I;						// insets of frame
// Buttons
	Button 				Start, Pause, Quit;
// Constants for Scrollbars/rectangle/circle
	private final int 	MAXObj = 100;			// maximum object size
	private final int 	MINObj = 10;			// minimum object size
	private final int 	SPEED = 500;			// initial speed
	private final int 	SBvisible = 10;			// visible Scroll Bar
	private final int 	SBunit = 1;				// Scrollbar unit step size
	private final int 	SBblock = 10;			// Scrollbar block step size
	private final int 	SOBJ = 21;				// initial object width
// Variables for Scrollbars/rectangle/circle	
	private int 		SObj = SOBJ;			// initial object width
	private int 		SpeedSBmin = 1;			// speed scrollbar minimum value
	private int 		SpeedSBmax = 1000+SBvisible;//speed scrollbar maximum value with visible offset
	private int 		SpeedSBinit = SPEED;	// Initial speed scrollbar value
// Add objects
	private Objc 		Obj;					// object to draw
	private Label 		SPEEDL = new Label("Speed", Label.CENTER);	// label for speed scroll bar
	private Label 		SIZEL = new Label("Size", Label.CENTER);	// label for size scroll bar
	Scrollbar 			SpeedScrollBar, ObjSizeScrollBar;			// scroll bars
// Run class	
	private final double DELAY = 500;			// timer delay constant
	
	private boolean 	run;					// for the program loop
	private boolean 	TimePause;				// to identify run/pause
	private boolean 	ok = true;
	private int 		delay;					// for the current time delay
	
	private Thread 		thethread;				// thread for timer delay
// Panel
	private Panel		sheet = new Panel();
	private Panel		control = new Panel();
//GridBagLayout
	private GridBagLayout 		displ = new GridBagLayout();
	private GridBagConstraints 	c = new GridBagConstraints();
//Points
	private Point 		FrameSize = new Point(640,400);// initial frame size
	private Point 		Screen = new Point(FrameSize.x-1, FrameSize.y-1);// drawing screen size
	private Point 		m1 = new Point(0,0);
	private Point		m2 = new Point(0,0);
//Rectangles
	private Rectangle	Perimeter = new Rectangle(0,0,Screen.x,Screen.y);// bouncing perimeter
	private Rectangle	db = new Rectangle();	// drag box rectangle
	private Rectangle 	temp = new Rectangle();	// Temp Rectangle to check for next position
	
	private final int 	EXPAND = 5;				// buffer on resize
	private final int	lw = 13;
	private final int	lh = 43;
	
	private Vector<Rectangle> Walls = new Vector <Rectangle>();
	
	private static final Rectangle ZERO = new Rectangle(0, 0, 0, 0); //will be returned from a function
//**************************************************************************************//
//----------------------------------------main------------------------------------------//
//**************************************************************************************//	
	public static void main(String[] args) {
		BouncingBall b = new BouncingBall();		// create an object
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
	public BouncingBall() {
		MakeSheet();					// Determine the sizes for the sheet
		try {
			initComponents();			// try to initialize the components
		}		
		catch (Exception e) {e.printStackTrace();}
		
		start();
	}
//**************************************************************************************//
//----------------------------------------Methods---------------------------------------//
//**************************************************************************************//
	//---------------------------------------MakeSheet--------------------------------------//
	// New Frame information and recalculation of Frame sizes.
	// Gets the insets and adjusts the sizes of the items
	private void MakeSheet() {			
		I = getInsets();				
		ScreenWidth = WinWidth - I.left - I.right;
		ScreenHeight = WinHeight - I.top - 2*(BUTTONH + BUTTONHS) - I.bottom + 3;
		setSize(WinWidth, WinHeight);			// set the frame size
		control.setBackground(Color.lightGray);	// set the background color
	}
	//------------------------------------initComponents------------------------------------//
	// Adding the objects
	public void initComponents() throws Exception, IOException {
		//GridBagLayout
		double colWeight[] = {1,1,1,1,1};
		double rowWeight[] = {1,1,1};
		int colWidth[] = {1,1,1,1,1};
		int rowHeight[] = {1,1,1};
		displ.columnWeights = colWeight;
		displ.rowWeights = rowWeight;
		displ.columnWidths = colWidth;
		displ.rowHeights = rowHeight;
		// Run
		TimePause = true;
		run = true;
		
		//-------------------------------------Buttons--------------------------------------//
		Start = new Button("Run");		// create the start button
		Pause = new Button("Pause");	// create the Shape button
		Quit = new Button("Quit");		// create the quit button
		Start.setEnabled(true);
		Pause.setEnabled(false);
		//------------------------------------Scrollbars------------------------------------//
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
		//--------------------------------------Object--------------------------------------//
		Obj = new Objc(SObj, ScreenWidth, ScreenHeight);		// create the object
		Obj.setBackground(Color.red);							// set the background color
		
		//-------------------------------control GridBagLayout------------------------------//
		c.anchor = GridBagConstraints.CENTER;	//places component into the center of the cell
		c.weightx = 1;  						//specifies resizing behavior
		c.weighty = 1;  						//specifies resizing behavior
		c.gridheight = 1;  						//# of cells in a col
		c.gridwidth = 1;    					//# of cells in a row
		c.fill = GridBagConstraints.BOTH;  		//fills the component horizontally and vertically for resizing	
		
		//adds components to their respective cells in GridBagLayout
		//Speed ScrollBar
		c.gridx = 0;
		c.gridy = 0;
		displ.setConstraints(SpeedScrollBar, c);
		control.add(SpeedScrollBar);
		
		//Run Button
		c.gridx = 1;
		displ.setConstraints(Start, c);
		control.add(Start);
		
		//Pause Button
		c.gridx = 2;
		displ.setConstraints(Pause, c);
		control.add(Pause);
		
		//Quit Button
		c.gridx = 3;
		displ.setConstraints(Quit, c);
		control.add(Quit);
		
		//ObjectSize ScrollBar
		c.gridx = 4;
		displ.setConstraints(ObjSizeScrollBar, c);
		control.add(ObjSizeScrollBar);
		
		//Speed Label
		c.gridx = 0;
		c.gridy = 1;
		displ.setConstraints(SPEEDL, c);
		control.add(SPEEDL);
		
		//Size Label
		c.gridx = 4;
		displ.setConstraints(SIZEL, c);
		control.add(SIZEL);
		//---------------------------------------Mouse--------------------------------------//
		//Init both mouse points to 0
		m1.setLocation(0,0);
		m2.setLocation(0,0);
		
		Perimeter.setBounds(0,0,Screen.x,Screen.y);
		Perimeter.grow(-1, -1);
	
		sheet.setBounds(0, 0, WIDTH, HEIGHT);		//size and position the frame
		
		setBackground(Color.white);
		setVisible(true);
		
		
		control.setLayout(displ);
		control.setVisible(true);
		
		sheet.setLayout(new BorderLayout(0,0));
		//--------------------------------Add Object to sheet-------------------------------//
		sheet.add("Center", Obj);							// add the object to the frame
		sheet.setVisible(true);
		
		add("Center", sheet);
		add("South", control);

		Screen.setLocation(sheet.getWidth() - 1, sheet.getHeight() - 1);// update the Screen Point
		Perimeter.setBounds(getX(), getY(), Screen.x, Screen.y); 		// update the perimeter Rectangle
		Perimeter.grow(-1, -1); 										// shrink for border

		//-------------------------------------Listeners------------------------------------//	
		// Buttons
		Start.addActionListener(this); 			// add the start button listener
		Pause.addActionListener(this); 			// add the shape button listener
		Quit.addActionListener(this); 			// add the quit button listener
		
		// Scrollbar
		SpeedScrollBar.addAdjustmentListener(this); 	// add the speed scroll bar listener
		ObjSizeScrollBar.addAdjustmentListener(this); 	// add the size scroll bar listener
		
		// Mouse
		Obj.addMouseMotionListener(this);
		Obj.addMouseListener(this);
		
		// Frame
		this.setTitle("BouncingBall Group 1");
		this.addComponentListener(this);		// add the component listener
		this.addWindowListener(this); 			// add the window listener
		
		revalidate();							// validate the layout
		}
	
	//updates time delay relative to speed scrollbar
	private void setTimeDelay() {
		delay = (int)(DELAY/(double)SpeedScrollBar.getValue());
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
		Pause.removeActionListener(this);
		Quit.removeActionListener(this);
		Obj.removeMouseMotionListener(this);
		Obj.removeMouseListener(this);
		// Scrollbar
		SpeedScrollBar.removeAdjustmentListener(this);
		ObjSizeScrollBar.removeAdjustmentListener(this);
		
		this.removeComponentListener(this);
		this.removeWindowListener(this);
		dispose();
		System.exit(0);
	}
//**************************************************************************************//
//-----------------------------------Component Events-----------------------------------//
//**************************************************************************************//
// When the Frame (Component) is resized we just need to get the new size, recalculate the
//  the sizes and apply the new sizes to the objects.
	
	// resize the Frame and the objects:
	public void componentResized(ComponentEvent e) {
		Rectangle r = new Rectangle();
		int i = 0;
		int mr = 0;  //most right
		int mb = 0;  //most bottom

		WinWidth  = getWidth();						//current WINDOW width
		WinHeight = getHeight();					//current WINDOW height
		
		MakeSheet();
		
		//is there at least one rectangle?
		if(Obj.getWallSize() > 0) {
			//initialize the loop
			r.setBounds(Obj.getOne(i));				// get the 0th rectangle
			mr = r.x + r.width;						// init max right
			mb = r.y + r.height;					// init max bottom
			i++;  									//increment to next element prior to loop
			
			while(i < Obj.getWallSize()) {
				//check if new max right and max bottom
				r.setBounds(Obj.getOne(i));			// get ith rectangle
				mr = Math.max((r.x + r.width), mr);	// keep max right
				mb = Math.max((r.y + r.height), mb);// keep max bottom
				i++;
			}
		}
		
		
		//we checked rectangles, now check the ball
		r.setBounds(Obj.GetObject()); 			// Process the ball
				
		mr = Math.max((r.x + r.width), mr);		// keep max right
		mb = Math.max((r.y + r.height), mb);	// keep max bottom
		
		// check and see if the farthest right and bottom of the rectangle outside the screen.
		if(mr > ScreenWidth || mb > ScreenHeight) {
			// if it is resize the screen to just touching the object without getting it stuck.
			setSize(Math.max((mr + EXPAND), ScreenWidth) + lw, Math.max((mb + EXPAND), 
					ScreenHeight) + lh + 2*BUTTONH);
		}
		
 		Screen.setLocation(sheet.getWidth() - 1, sheet.getHeight() - 1);// update the Screen Point
		Perimeter.setBounds(getX(), getY(), Screen.x, Screen.y); 		// update the perimeter Rectangle
		Perimeter.grow(-1, -1); 										// shrink for border
		Obj.reSize(Screen); 											// resize the ball screen
		Obj.repaint();												 	// repaint

	}
	public void componentHidden(ComponentEvent e) {}
	public void componentShown(ComponentEvent e) {}
	public void componentMoved(ComponentEvent e) {}
	public void actionPerformed(ActionEvent e) {
		Object source = e.getSource();
		
		if(source==Start) {					// Start button pressed
			if(TimePause) {							
				Start.setEnabled(false);
				Pause.setEnabled(true);
				TimePause = false;					// set the Pause flag true
				thethread.interrupt();				// interrupt the thread
			}
		}
		
		if(source==Pause) {					// Shape button pressed
			if(!TimePause) {					// if the button label is Paused
				Pause.setEnabled(false);
				Start.setEnabled(true);
				TimePause = true;					// Set the Pause flag false
				thethread.interrupt();
			} 
		}
		
		if(source==Quit) {					// Quit button pressed
			stop();								// Stop the program and close
		}		
	}
	public void adjustmentValueChanged(AdjustmentEvent e) {
		//Variables
		ok = true;  //global variable, therefore needs to be resized
		int TS, half;
		int i=0;						 		// index for vector of rectangles.
		int prevSize = Obj.GetSize();  			// gets SObj from object
		int newXMax; int newXMin; int newYMax; int newYMin;
		Scrollbar sb = (Scrollbar)e.getSource();// get the scrollbar that triggered the event
		
		//----------------------------------SpeedScrollBar----------------------------------//
		if(sb==SpeedScrollBar) {
			setTimeDelay();  //updates the time delay
			thethread.interrupt();
		}				
		//-----------------------------------SizeScrollBar----------------------------------//
		if(sb==ObjSizeScrollBar)  {					// Set the size of the object via scrollbar
			TS = e.getValue(); 						// get the value
			TS = (TS/2)*2+1;						// Make odd to account for center position i.e. +
			half = (TS - 1)/2;
			
			//sets a temp rectangle to test if new value is valid 
			temp.setBounds(Obj.GetXValue()-half-1,	Obj.GetYValue()-half-1,	TS+2,	TS+2);
			
			//if no intersection
			if(temp.equals(Perimeter.intersection(temp))) {
				//calculate the new extreme values
				newXMax = Obj.GetXValue() + ((TS-1)/2);
				newYMax = Obj.GetYValue() + ((TS-1)/2);
				
				newXMin = Obj.GetXValue() - ((TS-1)/2);
				newYMin = Obj.GetYValue() - ((TS-1)/2);
				
				//check if new size fits screen
				if (newXMax >= ScreenWidth-2 || newXMin <= 1) {
					ok = false;
				} else if (newYMax >= ScreenHeight-2 || newYMin <= 1) {
					ok = false;
				}
				while(i < Obj.getWallSize() && ok) {
					Rectangle t = Obj.getOne(i);	// get the ith rectangle
					if(t.intersects(temp)) {		// check for intersection
						ok = false;
					} else {
						i++;
					}
				}
			} else {
				ok = false;
			}
			if(ok) {
				Obj.update(TS); 
				//update the new max values to prevent stale data??
				Obj.calcExtremes(ScreenWidth, ScreenHeight);
			} else {
				//reset the scrolllbar to the previous size
				sb.setValue(prevSize);
			}
		}	
		Obj.repaint();							// force repaint
	}
//**************************************************************************************//
//-------------------------------------Mouse Events-------------------------------------//
//**************************************************************************************//
	public void mousePressed(MouseEvent e) {
		// records the location of the mouse position
		m1.setLocation(e.getPoint());
	}
	public void mouseReleased(MouseEvent e) {
		// check if the object intersects with the rectangle and not store the rectangle.
		int i = 0;								// index for vector
		
		boolean keep = false;					// keep flag
			
		Rectangle t = new Rectangle();			// temp rectangle
		Rectangle b = new Rectangle(Obj.GetObject());	// Our Object rectangle with its current size
		b.grow(1,1);							// expand it by 1 pixel to check for its next location
		
		//If the ball (b) is in any part of the new rectangle (db) it will not be kept and no point in checking anything.
		if(!b.intersects(db)) {
//System.out.println("ball: "+b+"  db: "+db+" Perimeter: "+Perimeter);						// ||TESTING||
			if (Perimeter.intersects(db)) {	// Checks if the rectangle exceeds the drawing screen
//System.out.print("part is inside.  Corrected rectangle is: "+Perimeter.intersection(db));	// ||TESTING||
				db = Perimeter.intersection(db);	// Set the db rect to the intersection 
													//	the dragbox made with the Perimeter rect							
//System.out.println("  updated db: "+db);													// ||TESTING||
			}
			i = 0;						// reset the index
			while(i < Walls.size()) {	// step through the vector
				t = Obj.getOne(i);			// set temp rectangle with current vector at index i
//System.out.println("n = "+Walls.size()+" t: "+t+" db.contains(t)");							// ||TESTING||
				if(db.contains(t)) {	// if the db overlaps the current vector rectangle set to temp
					Obj.removeOne(i);		// remove that rectangle from the vector.
//System.out.println(t+" was covered and removed");											// ||TESTING||
				} else					// else...	
					i++;					// step to next vector
			}
			i = 0;						// reset the index
			keep = true;				// set the keep flag initially to know if the follow rectangle is 
										//	covered already
			while(i < Walls.size()&&keep) {	// step through the vector as long as it is not covered
				t = Obj.getOne(i);				// set temp rectangle with current vector at index i
				if(t.contains(db))				// if temp vector rect covers the db
					keep = false;					//it is covered, don't add it
					i++;							// set to next vector
			}
			if(keep) {					//if keep, add it
				Obj.addOne(db);
//System.out.println("New rectangle was added");												// ||TESTING||
			}
		}
	}
	public void mouseClicked(MouseEvent e) {
		Point p = new Point(e.getX(), e.getY());// get the moused clicked position and create a point
		Rectangle b = new Rectangle();
		int i = 0;		
		while(i < Walls.size()) {				// step through the vector
			// see if the point is contained in the rectangle
			b = Obj.getOne(i);
			if(b.contains(p))
			{
				Obj.removeOne(i);
//System.out.println(b+" was removed");														// ||TESTING||
			}
			else
				i++;
		}
	}
	public void mouseMoved(MouseEvent e) {
		// Light Show!
		if(MouseInfo.getPointerInfo().getLocation().x < (Screen.x)/2 && (MouseInfo.getPointerInfo().getLocation().y < (Screen.y)/2))
			Obj.setBackground(Color.blue);
		if(MouseInfo.getPointerInfo().getLocation().x >= (Screen.x)/2 && MouseInfo.getPointerInfo().getLocation().y >= (Screen.y)/2)
			Obj.setBackground(Color.pink);
		if(MouseInfo.getPointerInfo().getLocation().x > (Screen.x)/2 && (MouseInfo.getPointerInfo().getLocation().y < (Screen.y)/2))
			Obj.setBackground(Color.white);
		if(MouseInfo.getPointerInfo().getLocation().x < (Screen.x)/2 && (MouseInfo.getPointerInfo().getLocation().y >= (Screen.y)/2))
			Obj.setBackground(Color.orange);
		Obj.repaint();
	}
	public void mouseDragged(MouseEvent e) {
		// Check if the requested Rectangle created by dragging the mouse is within the perimeter of the
		//	screen.
		db.setBounds(getDragBox(e));
		if(Perimeter.contains(db)) {
			if(db.y < Perimeter.getMinY())
				db.y = (int)Perimeter.getMinY();
			if(db.y > Perimeter.getMaxY() - SObj)
				db.y = (int)Perimeter.getMaxY();
			if(db.x < Perimeter.getMinX())
				db.x = (int)Perimeter.getMinX();
			if(db.x > Perimeter.getMaxX() - SObj)
				db.x = (int)Perimeter.getMaxX();
			Obj.repaint();
		}
	}
	public void mouseEntered(MouseEvent e) {
		Obj.repaint();
		Obj.setBackground(Color.cyan);
	}
	public void mouseExited(MouseEvent e) {
		Obj.setBackground(Color.green);
	}
	public Rectangle getDragBox(MouseEvent e) {
		int h = 0;
		int w = 0;
		int width, width1, height, height1;
		Rectangle DragBox = new Rectangle();
		m2.setLocation(e.getPoint());
		width = Math.min(m1.x, m2.x);
		width1 = Math.max(m1.x, m2.x);
		height = Math.min(m1.y, m2.y);
		height1 = Math.max(m1.y, m2.y);
		w = width1 - width;
		h = height1 - height;
		DragBox.setBounds(width, height, w, h);		
		return DragBox;
	}
//**************************************************************************************//
//------------------------------------Thread Methods------------------------------------//
//**************************************************************************************//	
	public void run() {
		while(run) {
			try {
				Thread.sleep(1);
			} catch(InterruptedException e) {}
			if(!TimePause) {
				try {
					Thread.sleep(delay);
					// update the size in the object to the new size
					Obj.reSize(FrameSize);  //update the size of the object within the object
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
		if (right > sheet.getWidth() && bottom > sheet.getHeight()) {
			//exceeds both width AND height, change x and y
			
			//move x and y to a valid coordinate within the frame (may need to consider if they are EQUAL)
			Obj.SetXValue(sheet.getWidth() - ((Obj.GetSize()-1)/2) - 1);
			Obj.SetYValue(sheet.getHeight() - ((Obj.GetSize()-1)/2) - 1);
			
		} else if (right > sheet.getWidth()) {
			//exceeds width only, change x only
			Obj.SetXValue(sheet.getWidth() - ((Obj.GetSize()-1)/2) -1);
			
		} else if (bottom > sheet.getHeight()) {
			//exceeds height only, change y only
			Obj.SetYValue(sheet.getHeight() - ((Obj.GetSize()-1)/2) - 1);
		}
		
		//Obj.repaint();
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Obj Class<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class Objc extends Canvas {
	//**************************************************************************************//
	//-------------------------------------Constants----------------------------------------//
	//**************************************************************************************//
		private static final long serialVersionUID = 11L;
		private int 	ScreenWidth;
		private int 	ScreenHeight;
		private int 	SObj;
		
		private int 	xVal, yVal;
		
		private int 	ymin, ymax, xmin, xmax;
		private boolean right, down;
		
		Image buffer;
		Graphics g;
	//**************************************************************************************//
	//------------------------------Drawing Object Constructor------------------------------//
	//**************************************************************************************//	
		public Objc(int SB, int w, int h) {
		// Set the screen width/height, init the flags, and determine the center of the screen for the obj
			ScreenWidth = w;
			ScreenHeight = h;
			
			SObj = SB;
			right = true;
			down = true;
			
			calcExtremes(w, h);  //sets the xmin, xmax, ymin, and ymax for the object 
			
			yVal = (SObj-1)/2 + 2;  //need to add one to move away from border at beginning
			xVal = (SObj-1)/2 + 2;
		}
	//**************************************************************************************//
	//--------------------------------Drawing Object Mutators-------------------------------//
	//**************************************************************************************//
		//calculate min and max x/y sizes for the current display size and current object size
		public void calcExtremes(int ScreenWidth, int ScreenHeight) {
			xmax = sheet.getWidth() - ((SObj-1)/2);  //closest obj can get to the right side
			xmin = ((SObj - 1)/2);  //closest the obj can get to the left side
			
			ymax = sheet.getHeight() - ((SObj-1)/2);  //closest obj can get to the bottom 
			ymin = ((SObj - 1)/2);  //closest the obj can get to the top side
			
		}
		//Checks if current x coordinate is within boundaries of frame. Returns boolean accordingly
		public boolean checkX() {
			boolean fits;
			if (xVal >= xmax-2 || xVal-1 <= xmin) {
				fits = false;
			} else {
				fits = true;
			}
			
			return fits;
			
		}
		//Checks if current y coordinate is within boundaries of frame. Returns boolean accordingly
		public boolean checkY() {
			boolean fits;
			if (yVal >= ymax-2 || yVal-1 <= ymin) {
				fits = false;
			} else {
				fits = true;
			}
			
			return fits;
		}
		// Update the size
		public void update(int NS) {
			SObj = NS;
		}
		// UPDATES THE VALUES for screen size and the min and max x/y values. doesnt change anything on screen
		public void reSize(Point r) {
			
			ScreenWidth = r.x;
			ScreenHeight = r.y;
			calcExtremes(ScreenWidth, ScreenHeight);
		}
		public void SetXValue(int in) {
			xVal = in;
		}
		public void SetYValue(int in) {
			yVal = in;
		}
	//**************************************************************************************//
	//-------------------------------Drawing Object Accessors-------------------------------//
	//**************************************************************************************//
		public int GetXValue() {
			return xVal;
		}
		public int GetYValue() {
			return yVal;
		}
		public int GetSize() {
			return SObj;
		}
		public Rectangle GetObject() {
			Rectangle t = new Rectangle();
			int rectX = xVal - ((SObj-1)/2);
			int rectY  = yVal - ((SObj-1)/2);
			
			t.setBounds(rectX, rectY, SObj, SObj);
			//t.setSize(x, y); //would set at 0, 0 but of size x and y
			
			return t;
		}
	//**************************************************************************************//
	//-----------------------------------------Paint----------------------------------------//
	//**************************************************************************************//
		// When the clear flag is set, a call to the super component will be made to clear the Canvas
		public void paint(Graphics cg) {
			Rectangle t = new Rectangle();
			
			//Double Buffering																			 
			buffer = createImage(Screen.x+1, Screen.y+1);		//+1 here for full screen					  
			if(g!=null)
				g.dispose();	
			g = buffer.getGraphics();
			
			// Paint for the border
			g.setColor(Color.red);
			g.drawRect(0, 0, sheet.getWidth()-1, sheet.getHeight()-1);
			
			// Paint for the Object(ball)
			g.setColor(Color.cyan);
			g.fillOval(xVal-(SObj-1)/2,	yVal-(SObj-1)/2,	SObj,	SObj);
			g.setColor(Color.black);
			g.drawOval(xVal-(SObj-1)/2,	yVal-(SObj-1)/2,	SObj-1,	SObj-1);
			
			// Painting all of the vector Rectangles
			for(int i = 0; i < Walls.size(); i++) {
				t = Walls.elementAt(i);
				g.fillRect(t.x, t.y, t.width, t.height);
			}
			
			// Double Buffering
			cg.drawImage(buffer,0,0,null);		
		}
		public void update(Graphics g) {	// found online because the dang ball and rectangles kept flickering
			paint(g);	
		}
	//**************************************************************************************//
	//------------------------------------------Move----------------------------------------//
	//**************************************************************************************//
		public void moveObject() {
			//checks if current coordinates are valid and compliments motion flags accordingly
			if (!checkX()) {
				right = !(right);  //compliments the right flag
			}
			if (!checkY()) {
				down = !(down); //compliments the down flag
			}
			
			//we've checked border contact, now check rectangle contact (border and vector contact wont be simultaneous)
			Rectangle r = new Rectangle(VectorContact());
			//if there is a contact vector
			if (!r.equals(ZERO)) {
				//creates x-edges to be tested
				Rectangle xLeft = new Rectangle(r.x-1, r.y+1, 1, r.height-2);
				Rectangle xRight = new Rectangle(r.x + r.width, r.y+1, 1, r.height-2);
				//Creates y-edges to be tested
				Rectangle yTop = new Rectangle(r.x+1, r.y-1, r.width-2, 1);
				Rectangle yBottom = new Rectangle(r.x+1, r.y+r.height, r.width-2, 1);
				
				Rectangle b = new Rectangle(GetObject());  //returns the current ball
				b.grow(1, 1);
				
				//check x edges
				if (b.intersects(xLeft)) {
					right = false;
				}
				if (b.intersects(xRight)) {
					right = true;
				}
				if (b.intersects(yTop)) {
					down = false;
				}
				if (b.intersects(yBottom)) {
					down = true;
				}
			}
			
			//horizontal motion
			if (right) {
				xVal = xVal + 1;
			} else {
				xVal = xVal - 1;
			}
			
			//vertical motion
			if (down) {
				yVal = yVal + 1;
			} else {
				yVal = yVal - 1;
			}	
		}
	//**************************************************************************************//
	//-----------------------------------Rectangle Mutators---------------------------------//
	//**************************************************************************************//
		public void addOne(Rectangle r) {
			Walls.addElement(new Rectangle(r));
		}
		public void removeOne(int i) {
			Walls.removeElementAt(i);
		}
	//**************************************************************************************//
	//-----------------------------------Rectangle Accessors--------------------------------//
	//**************************************************************************************//
		public Rectangle getOne(int i) {
			return Walls.elementAt(i);
		}
		public int getWallSize() {
			return Walls.size();
		}
	//**************************************************************************************//
	//----------------------------------VectorContact Method--------------------------------//
	//**************************************************************************************//
		public Rectangle VectorContact() {
			//final Rectangle ZERO = new Rectangle(0,0,0,0);
			ok = true;  //resets to true
			int i = 0;
			
			Rectangle r = new Rectangle(ZERO);
			Rectangle b = new Rectangle(GetObject());  //returns the current ball
			b.grow(1, 1);
			
			while((i < Walls.size()) && ok) {
				r = Walls.elementAt(i);
				
				if(r.intersects(b)) {
					ok = false;
				}
				else {
					i++;	
				}
			}			
			return r;
		}
	}
}