//Andrew Bissell, Daniel Nash
//GROUP 1 
//Tech Computing Using Java CET-350
//Cannon VS Ball
//bis3683@calu.edu, nas8662@calu.edu
package CannonVSBall;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.*;

public class CannonVSBall implements WindowListener, ComponentListener, ActionListener,
						AdjustmentListener, Runnable, MouseListener, MouseMotionListener, ItemListener{
//**************************************************************************************//
//-------------------------------------Constants----------------------------------------//
//**************************************************************************************//
	private static final long serialVersionUID = 10L;
// Constants are created by using the final declaration:
	private final int 	WIDTH = 900;			// initial frame width
	private final int 	HEIGHT = 600;			// initial frame height
	private Frame		CBFrame;				//Window frame since not extending Frame
	private final int 	BUTTONH = 20;			// button height
	private final int 	BUTTONHS = 5;			// button height spacing
// Program variable declarations:
	private int 		WinWidth = WIDTH;		// initial frame width
	private int 		WinHeight = HEIGHT;		// initial frame height
	private int 		ScreenWidth;			// drawing screen width
	private int 		ScreenHeight;			// drawing screen height
// Inset: the spacings around the Frame that are used by the Frame border.
	private Insets 		I;						// insets of frame
// Constants for Scrollbars/rectangle/circle
	private final int 	MAXObj = 100;			// maximum object size
	private final int 	MINObj = 0;				// minimum object size
	private final int 	VELOCITY = 50;			// initial velocity
	private final int 	SBvisible = 10;			// visible Scroll Bar
	private final int 	SBunit = 1;				// Scrollbar unit step size
	private final int 	SBblock = 10;			// Scrollbar block step size
	private final int 	SOBJ = 21;				// initial object width
	private final int	CBbase = 50;			// Circle for the cannon base
// Variables for Scrollbars/rectangle/circle	
	private int 		SObj = SOBJ;			// initial object width
	private int 		velocitySBmin = 50;			// speed scrollbar minimum value
	private int 		velocitySBmax = 200 + SBvisible;//speed scrollbar maximum value with visible offset
	private int 		velocitySBinit = VELOCITY;	// Initial speed scrollbar value
// Add objects
	private Objc 		Obj;					// object to draw
	private Label 		INITVEL = new Label("Velocity("+VELOCITY+")", Label.CENTER);	// label for speed scroll bar
	private Label 		ANGLE = new Label("Angle(45)", Label.CENTER);	// label for size scroll bar
	Scrollbar 			VeloScrollBar, AngleScrollBar;			// scroll bars
// projectile
	private Objc		projectile;				//projectile object
	private boolean		projectileExists;		//indicates if drawn
	private boolean		collision;
// Run class		
	private boolean 	run;					// for the program loop
	private boolean 	TimePause;				// to identify run/pause
	private boolean 	ok = true;
	private int 		Objdelay;				// for the current time Objdelay
// Threads	
	private Thread 		Objthread;				// thread for timer Objdelay
	private Thread		CBallthread;			// thread for the cannon ball
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
	
	private Vector<Rectangle> Walls = new Vector <Rectangle>();
	
	private static final Rectangle ZERO = new Rectangle(0, 0, 0, 0); //will be returned from a function
// Labels
	private Label		message = new Label("", Label.CENTER);// for the status message between the scrollbar
	private int			t = 0;
	private Label		time = new Label("Time: "+t,Label.LEFT);		// Time label 
	private int			bScore = 0;
	private Label		ballS = new Label("Ball: "+bScore,Label.CENTER);		// Ball's score label
	private int			pScore = 0;
	private Label		playerS = new Label("Player: "+pScore,Label.RIGHT);	// Player's score label

// Menu
	private MenuBar 	MMB;			// the menu bar
	// Main Menus
	private Menu		CONTROL, PARA, ENVI;
	// Sub Menus
	private Menu		SIZE, MSPEED;
	// Control menu items
	private MenuItem	PAUSE, RUN, RESTART, QUIT;
	// Parameter menu items
		// SIZE
	private CheckboxMenuItem	XS, S, M, L, XL;		// x-small, small, medium, large, x-large
		// MSPEED
	private CheckboxMenuItem	XSL, SL, MSL, FA, XFA;	// x-slow, slow, medium, fast, x-fast
	// Environment menu items
	private CheckboxMenuItem	MER, VEN, EAR, MOO, MAR, JUP, SAT, URA, NEP, PLU;	// Mercury, Venus, Earth, Moon, Mars, Jupitor, Saturn, Uranus, Neptune, Pluto
// Polygon
	private Polygon 	Cannon = new Polygon();
	private int			l = 100;				// Cannon length
	private int			w = 25;					// Cannon barrel width (25mm cannon!)
	private double		deg = 45;				// degrees
	private double		rad;					// radians
	private double		x1;
	private double		y1;
	private double		xt;
	private double 		yt;
	private double		cxt;
	private double		cyt;
	private Point 		c1 = new Point(0,0);
	private Point 		c2 = new Point(0,0);
	private Point 		a1 = new Point(0,0);
	private Point 		a2 = new Point(0,0);
	private double velY;
	private double velX;
	
// Planet Gravity Constants (m/s^2)
	private double		mer = 3.7, ven = 8.87, ear = 9.81, moo = 1.62, mar = 3.72, jup = 24.79, sat = 10.44, ura = 8.87, nep = 11.15, plu = 0.62;
	private double		g;	// gravity
	private	double 		T = 0.1;
	private	int			x,y;
	
	private final long	milsec = System.currentTimeMillis();
//**************************************************************************************//
//----------------------------------------main------------------------------------------//
//**************************************************************************************//	
	public static void main(String[] args) {
		CannonVSBall b = new CannonVSBall();		// create an object
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
	public CannonVSBall() {
		CBFrame = new Frame("CannonVSBall");
		CBFrame.setLayout(new BorderLayout(0,0));
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
		I = CBFrame.getInsets();				
		ScreenWidth = WinWidth - I.left - I.right;
		ScreenHeight = WinHeight - I.top - 2*(BUTTONH + BUTTONHS) - I.bottom + 3;

		CBFrame.setSize(WinWidth, WinHeight);			// set the frame size
		control.setBackground(Color.lightGray);	// set the background color
	}
	//------------------------------------initComponents------------------------------------//
	// Adding the objects
	public void initComponents() throws Exception, IOException {
		//---------------------------------------Menu---------------------------------------//

//*********************************
g = ear;
//*******************************
		MMB = new MenuBar();							// create the menu bar
		
		// Control Menu
		CONTROL = new Menu("Control");					// create first menu, control
			PAUSE = CONTROL.add(new MenuItem("Pause",new MenuShortcut(KeyEvent.VK_P))); 	// add Pause to the control menu
			RUN = CONTROL.add(new MenuItem("Run", new MenuShortcut(KeyEvent.VK_R)));		// add Run to the control menu
			RESTART = CONTROL.add(new MenuItem("Restart", new MenuShortcut(KeyEvent.VK_C))); 								// add Restart to the control menu
			CONTROL.addSeparator();
			QUIT = CONTROL.add(new MenuItem("Quit", new MenuShortcut(KeyEvent.VK_Q)));	 									// add Quit to the contorl menu
			
		// Parameter Menu
		PARA = new Menu("Parameter");					// create second menu, parameter
			SIZE = new Menu("Size");						// create 1st submenu, Size
				SIZE.add(XS = new CheckboxMenuItem("x-small"));		// create x-small menu item w/ checkbox
				SIZE.add(S = new CheckboxMenuItem("small"));		// create small menu item w/ checkbox
				SIZE.add(M = new CheckboxMenuItem("medium"));		// create medium menu item w/ checkbox
				SIZE.add(L = new CheckboxMenuItem("large"));		// create large menu item w/ checkbox
				SIZE.add(XL = new CheckboxMenuItem("x-large"));		// create x-large menu item w/ checkbox
				M.setState(true);									// init checkbox to medium
				PARA.add(SIZE);
			MSPEED = new Menu("Speed");						// create 2nd submenu, Speed
				MSPEED.add(XSL = new CheckboxMenuItem("x-slow"));	// create x-slow menu item w/ checkbox
				MSPEED.add(SL = new CheckboxMenuItem("slow"));		// create slow menu item w/ checkbox
				MSPEED.add(MSL = new CheckboxMenuItem("medium"));	// create medium menu item w/ checkbox
				MSPEED.add(FA = new CheckboxMenuItem("fast"));		// create fast menu item w/ checkbox
				MSPEED.add(XFA = new CheckboxMenuItem("x-fast"));	// create x-fast menu item w/ checkbox
				MSL.setState(true);									// init checkbox to medium
				PARA.add(MSPEED);
				
		// Environment Menu
		ENVI = new Menu("Environment");					// create second menu, environment
			ENVI.add(MER = new CheckboxMenuItem("Mercury"));
			ENVI.add(VEN = new CheckboxMenuItem("Venus"));
			ENVI.add(EAR = new CheckboxMenuItem("Earth"));
			ENVI.add(MOO = new CheckboxMenuItem("Moon"));
			ENVI.add(MAR = new CheckboxMenuItem("Mars"));
			ENVI.add(JUP = new CheckboxMenuItem("Jupiter"));
			ENVI.add(SAT = new CheckboxMenuItem("Saturn"));
			ENVI.add(URA = new CheckboxMenuItem("Uranus"));
			ENVI.add(NEP = new CheckboxMenuItem("Neptune"));
			ENVI.add(PLU = new CheckboxMenuItem("Pluto"));
			EAR.setState(true);
			
		// add to the menu bar
		MMB.add(CONTROL);
		MMB.add(PARA);
		MMB.add(ENVI);
		
		//GridBagLayout
		double colWeight[] = {2,1,5,1,2};
		double rowWeight[] = {1,1,1,1};
		int colWidth[] = {2,1,5,1,2};
		int rowHeight[] = {1,1,1,1};
		displ.columnWeights = colWeight;
		displ.rowWeights = rowWeight;
		displ.columnWidths = colWidth;
		displ.rowHeights = rowHeight;
		// Run
		TimePause = true;
		run = true;
		
		//------------------------------------Scrollbars------------------------------------//
		// ScrollBar SPEED
		VeloScrollBar = new Scrollbar(Scrollbar.HORIZONTAL);	// create the speed scroll bar
		VeloScrollBar.setMaximum(velocitySBmax);					// set the max speed	
		VeloScrollBar.setMinimum(velocitySBmin);					// set the min speed
		VeloScrollBar.setUnitIncrement(SBunit);				// set the unit increment
		VeloScrollBar.setBlockIncrement(SBblock);				// set the block increment
		VeloScrollBar.setValue(velocitySBinit);					// set the initial value
		VeloScrollBar.setVisibleAmount(SBvisible);				// set the visible size
		VeloScrollBar.setBackground(Color.gray);				// set the background color
		setTimeDelay();
		// ScrollBar SIZE
		AngleScrollBar = new Scrollbar(Scrollbar.HORIZONTAL);	// create the size scroll bar
		AngleScrollBar.setMaximum(MAXObj);					// set the max speed	
		AngleScrollBar.setMinimum(MINObj);					// set the min speed
		AngleScrollBar.setUnitIncrement(SBunit);				// set the unit increment
		AngleScrollBar.setBlockIncrement(SBblock);			// set the block increment
		AngleScrollBar.setValue(SOBJ);						// set the initial value
		AngleScrollBar.setVisibleAmount(SBvisible);			// set the visible size
		AngleScrollBar.setBackground(Color.gray);				// set the background color
		//--------------------------------------Object--------------------------------------//
		Obj = new Objc(SObj, ScreenWidth, ScreenHeight);		// create the object
		Obj.setBackground(Color.cyan);							// set the background color
		
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
		displ.setConstraints(VeloScrollBar, c);
		control.add(VeloScrollBar);
		
		//message label
		c.gridx = 2;
		displ.setConstraints(message, c);
		control.add(message);
		
		//Angle ScrollBar
		c.gridx = 4;
		displ.setConstraints(AngleScrollBar, c);
		control.add(AngleScrollBar);
		
		//time label
		c.gridx = 1;
		c.gridy = 1;
		displ.setConstraints(time, c);
		control.add(time);
		
		//Ball's score label
		c.gridx = 2;
		c.gridy = 1;
		displ.setConstraints(ballS, c);
		control.add(ballS);
		
		//player's score label
		c.gridx = 3;
		c.gridy = 1;
		displ.setConstraints(playerS, c);
		control.add(playerS);
		
		//Speed Label
		c.gridx = 0;
		c.gridy = 1;
		displ.setConstraints(INITVEL, c);
		control.add(INITVEL);
		
		//Size Label
		c.gridx = 4;
		displ.setConstraints(ANGLE, c);
		control.add(ANGLE);
		//---------------------------------------Mouse--------------------------------------//
		//Init both mouse points to 0
		m1.setLocation(0,0);
		m2.setLocation(0,0);
		
		Perimeter.setBounds(0,0,Screen.x,Screen.y);
		Perimeter.grow(-1, -1);
	
		sheet.setBounds(0, 0, WIDTH, HEIGHT);		//size and position the frame
		
		CBFrame.setBackground(Color.white);
		CBFrame.setVisible(true);
		CBFrame.setMinimumSize(new Dimension((int)FrameSize.getX(), (int)FrameSize.getY()));
		
		control.setLayout(displ);
		control.setVisible(true);
		
		sheet.setLayout(new BorderLayout(0,0));
		//--------------------------------Add Object to sheet-------------------------------//
		sheet.add("Center", Obj);							// add the object to the frame
		sheet.setVisible(true);
		
		CBFrame.add("Center", sheet);
		CBFrame.add("South", control);

		Screen.setLocation(sheet.getWidth() - 1, sheet.getHeight() - 1);// update the Screen Point
		Perimeter.setBounds(CBFrame.getX(), CBFrame.getY(), Screen.x, Screen.y); 		// update the perimeter Rectangle
		Perimeter.grow(-1, -1); 										// shrink for border
		
		// action listeners 
		PAUSE.addActionListener(this);
		RUN.addActionListener(this);
		RESTART.addActionListener(this);
		QUIT.addActionListener(this);
		// item listeners
		
			// SIZE
		XS.addItemListener(this);
		S.addItemListener(this);
		M.addItemListener(this);
		L.addItemListener(this);
		XL.addItemListener(this);
			// MSPEED
		XSL.addItemListener(this);
		SL.addItemListener(this);
		MSL.addItemListener(this);
		FA.addItemListener(this);
		XFA.addItemListener(this);
			// ENVI
		MER.addItemListener(this);
		VEN.addItemListener(this);
		EAR.addItemListener(this);
		MOO.addItemListener(this);
		MAR.addItemListener(this);
		JUP.addItemListener(this);
		SAT.addItemListener(this);
		URA.addItemListener(this);
		NEP.addItemListener(this);
		PLU.addItemListener(this);
		
		//-------------------------------------Listeners------------------------------------//			
		// Scrollbar
		VeloScrollBar.addAdjustmentListener(this); 	// add the speed scroll bar listener
		AngleScrollBar.addAdjustmentListener(this); 	// add the size scroll bar listener
		
		// Mouse
		Obj.addMouseMotionListener(this);
		Obj.addMouseListener(this);
		
		// Frame
		CBFrame.setMenuBar(MMB);					// add the menubar to the frame
		CBFrame.setTitle("CannonVSBall Group 1");
		CBFrame.addComponentListener(this);			// add the component listener
		CBFrame.addWindowListener(this); 			// add the window listener
		
		CBFrame.revalidate();						// validate the layout
		}
	
	//updates time Objdelay relative to speed scrollbar
	private void setTimeDelay() {
		//Objdelay = (int)(Objdelay/(double)VeloScrollBar.getValue());
		Objdelay = 15;
	}
	//----------------------------------------start-----------------------------------------//
	public void start() {
		Obj.repaint();					// repaint the object
		
		if (Objthread == null) {
			Objthread = new Thread(this);
			Objthread.setName("Objthread");
			Objthread.start();
		}
		if (CBallthread == null) {
			CBallthread = new Thread(this);
			CBallthread.setName("CBallthread");
			CBallthread.start();
		}
	}
	//-----------------------------------------stop-----------------------------------------//
	// Quit button and window closing button
	public void stop() {
		run = false;
		Objthread.interrupt();
		CBallthread.interrupt();
		
		// Mouse
		Obj.removeMouseMotionListener(this);
		Obj.removeMouseListener(this);
		// Scrollbar
		VeloScrollBar.removeAdjustmentListener(this);
		AngleScrollBar.removeAdjustmentListener(this);
		
		CBFrame.removeComponentListener(this);
		CBFrame.removeWindowListener(this);
		CBFrame.dispose();
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

		WinWidth  = CBFrame.getWidth();						//current WINDOW width
		WinHeight = CBFrame.getHeight();					//current WINDOW height
		
		MakeSheet();	
		//is there at least one rectangle?
		if(Obj.getWallSize() > 0) {
			//initialize the loop
			r.setBounds(Obj.getOne(i));				// get the 0th rectangle
			mr = r.x + r.width;						// init max right
			mb = r.y + r.height;					// init max bottom
			i++;  									// increment to next element prior to loop
			
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
		if(mr > sheet.getWidth() || mb > sheet.getHeight()) {
			// if it is resize the screen to just touching the object without getting it stuck.
			CBFrame.setSize(Math.max((mr + EXPAND), ScreenWidth), Math.max((mb + EXPAND), 
					ScreenHeight) + 2*BUTTONH);
		}	
 		Screen.setLocation(sheet.getWidth() - 1, sheet.getHeight() - 1);// update the Screen Point
		Perimeter.setBounds(CBFrame.getX(), CBFrame.getY(), Screen.x, Screen.y); 		// update the perimeter Rectangle
		Perimeter.grow(-1, -1); 										// shrink for border
		Obj.reSize(Screen); 											// resize the ball screen
		Obj.repaint();												 	// repaint
		// Output message to user.
		message.setText("Screen Resized to, Width: "+CBFrame.getWidth()+" Height: "+CBFrame.getHeight());

	}
	public void componentHidden(ComponentEvent e) {}
	public void componentShown(ComponentEvent e) {}
	public void componentMoved(ComponentEvent e) {}
	public void actionPerformed(ActionEvent e) {
		Object source = e.getSource();
		
		if (source == QUIT) {
			stop();
		}
		if (source == RUN) {
			if(TimePause) {							// else
				message.setText("Game Started!");
				TimePause = false;					// set the Pause flag true
				Objthread.interrupt();				// interrupt the thread
				CBallthread.interrupt();
			}
		}
		if (source == PAUSE) {
			if(!TimePause) {		// if the button label is Paused
				message.setText("Game Paused");
				TimePause = true;					// Set the Pause flag false
				Objthread.interrupt();
				CBallthread.interrupt();
			} 
		}
		if (source == RESTART) {
			message.setText("Game Restarted");
			// reset the ball in the top left corner
			Obj.SetXValue((SObj-1)/2 + 2);
			Obj.SetYValue((SObj-1)/2 + 2);
			
			// reset the score and the labels
			bScore = 0;
			ballS.setText("Ball: "+bScore);
			pScore = 0;
			playerS.setText("Player: "+pScore);
			
			// pause the game
			TimePause = true;
			
			// clear all rectangles
			Walls.clear();
		}
				
	}
	public void adjustmentValueChanged(AdjustmentEvent e) {
		Scrollbar sb = (Scrollbar)e.getSource();// get the scrollbar that triggered the event
		
		//----------------------------------VeloScrollBar----------------------------------//
		if(sb==VeloScrollBar) {
			INITVEL.setText("Velocity("+ VeloScrollBar.getValue() +")");	// label for speed scroll bar
		}				
		//-----------------------------------AngleScrollBar----------------------------------//
		if(sb==AngleScrollBar)  {
			ANGLE.setText("Angle("+((int)deg)+")");
			deg = sb.getValue();
		}					// Set the size of the object via scrollbar	
		Obj.repaint();
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
		if(!b.intersects(db) && !Cannon.intersects(db)) {
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
			while(i < Walls.size() && keep) {	// step through the vector as long as it is not covered
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
		if(e.getClickCount() == 2) {
			while(i < Walls.size()) {				// step through the vector
				// see if the point is contained in the rectangle
				b = Obj.getOne(i);
				if(b.contains(p)) {
					Obj.removeOne(i); 
	//System.out.println(b+" was removed");														// ||TESTING||
				}
				else
					i++;
			}
		}
		
		//checks left click
		if (e.getButton() == MouseEvent.BUTTON1) {
			//fire projectile if within the rectangle of canon
			if (e.getX() >= ScreenWidth - l - (CBbase/2) && e.getY() >= ScreenHeight - l - (CBbase/2)) {
				//fire projectile if not one alreay fired
				System.out.println("works");
				fireProjectile();
			}
		}
	}
	public void mouseMoved(MouseEvent e) {
		// Light Show!
//		if(MouseInfo.getPointerInfo().getLocation().x < (Screen.x)/2 && (MouseInfo.getPointerInfo().getLocation().y < (Screen.y)/2))
//			Obj.setBackground(Color.blue);
//		if(MouseInfo.getPointerInfo().getLocation().x >= (Screen.x)/2 && MouseInfo.getPointerInfo().getLocation().y >= (Screen.y)/2)
//			Obj.setBackground(Color.pink);
//		if(MouseInfo.getPointerInfo().getLocation().x > (Screen.x)/2 && (MouseInfo.getPointerInfo().getLocation().y < (Screen.y)/2))
//			Obj.setBackground(Color.white);
//		if(MouseInfo.getPointerInfo().getLocation().x < (Screen.x)/2 && (MouseInfo.getPointerInfo().getLocation().y >= (Screen.y)/2))
//			Obj.setBackground(Color.orange);
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
		//Obj.repaint();
		//Obj.setBackground(Color.cyan);
	}
	public void mouseExited(MouseEvent e) {
		//Obj.setBackground(Color.green);
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
	
	public void fireProjectile() {
		//check if projectile already exists
		
		//check if projectile exists and running
		if (run && !projectileExists) {
			//create object, initialize starting position
			projectile = new Objc(21, ScreenWidth, ScreenHeight);
			velX = VeloScrollBar.getValue() * Math.cos(rad);
			velY = VeloScrollBar.getValue() * Math.sin(rad);
			//set the initial coordinates
			projectile.SetXValue(((int)((sheet.getWidth()-(CBbase/2)) - cxt)));
			projectile.SetYValue(((int)((sheet.getHeight()-(CBbase/2)) - cyt)));
			projectileExists = true;
		}
		
	}
	
	public int GetRandomNumber(int min, int max) {
		Random random = new Random();
		return random.nextInt(max - min) + min;
	}
	
//**************************************************************************************//
//------------------------------------Thread Methods------------------------------------//
//**************************************************************************************//	
	public void run() {
		while(run) {
			t = getSeconds();
			time.setText("Time: "+t);
			try {
				if (Thread.currentThread().getName() == "Objthread") {
					Objthread.sleep(1);
				} else {
					CBallthread.sleep(1);
				}

			} catch(InterruptedException e) {}
			if(!TimePause) {
				try {
					if (Thread.currentThread().getName() == "Objthread") {
						//Objthread running
						Objthread.sleep(Objdelay);
						
						// update the size in the object to the new size
						Obj.reSize(FrameSize);  	//update the size of the object within the object
						Obj.repaint();				// repaint the object
						Obj.moveObject();
					} else {
						//CBall thread running
						//CBallthread.sleep(CBalldelay);
						if (projectileExists) {
							//move object
							projectile.reSize(FrameSize);  	//update the size of the object within the object
							projectile.repaint();				// repaint the object

							// Projectile movement
							velY = velY-g*T;
							x = projectile.GetXValue() - (int)(velX * T);
							y = projectile.GetYValue() - (int)(velY * T - 0.5*g * T * T);
		
							projectile.SetXValue((int)x);
							projectile.SetYValue((int)y);
							
							projectile.Collision();							
						}
					}
				} catch (InterruptedException e) {}
			}
			try {
				if (Thread.currentThread().getName() == "Objthread") {
					Objthread.sleep(1);	
				} else {
					CBallthread.sleep(1);
				}
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
	
	public void itemStateChanged(ItemEvent e) {
		Object source = e.getSource();
		
		//SIZE SELECTIONS
		if (source == XS || source == S || source == M || source == L || source == XL) {
			
			if (source == XS) {
				if(CheckObjResize(11)) {
					message.setText("Size set to x-small");
					XS.setState(true);
					Obj.updateSize(11);
					
					S.setState(false);
					M.setState(false);
					L.setState(false);
					XL.setState(false);
				} else {
					XS.setState(false);	
					message.setText("ERROR: Not enough room!");
				}
			}
			if (source == S) {
				if(CheckObjResize(21)) {
					message.setText("Size set to small");
					S.setState(true);
					Obj.updateSize(21);

					XS.setState(false);
					M.setState(false);
					L.setState(false);
					XL.setState(false);
				} else {
					S.setState(false);
					message.setText("ERROR: Not enough room!");
				}
			}
			if (source == M) {
				if(CheckObjResize(31)) {
					message.setText("Size set to medium");
					M.setState(true);
					Obj.updateSize(31);

					XS.setState(false);
					S.setState(false);
					L.setState(false);
					XL.setState(false);
				} else {
					M.setState(false);
					message.setText("ERROR: Not enough room!");
				}
			}
			if (source == L) {
				if(CheckObjResize(41)) {
					message.setText("Size set to large");
					L.setState(true);
					Obj.updateSize(41);

					XS.setState(false);
					S.setState(false);
					M.setState(false);
					XL.setState(false);
				} else {
					L.setState(false);
					message.setText("ERROR: Not enough room!");
				}
			}
			if (source == XL) {
				if(CheckObjResize(51)) {
					message.setText("Size set to x-large");
					XL.setState(true);
					Obj.updateSize(51);

					XS.setState(false);
					S.setState(false);
					M.setState(false);
					L.setState(false);
				} else {
					XL.setState(false);
					message.setText("ERROR: Not enough room!");
				}
			}
		}
		
		
		//SPEED SELECTIONS
		if (source == XSL || source == SL || source == MSL || source == FA || source == XFA) {
			//Clears all exisitng checkboxes
			XSL.setState(false);
			SL.setState(false);
			MSL.setState(false);
			FA.setState(false);
			XFA.setState(false);
			
			if (source == XSL) {
				message.setText("Speed set to x-slow");
				XSL.setState(true);
				Objdelay = 70;
			}
			if (source == SL) {
				message.setText("Speed set to slow");
				SL.setState(true);
				Objdelay = 25;
			}
			if (source == MSL) {
				message.setText("Speed set to medium");
				MSL.setState(true);
				Objdelay = 15;
			}
			if (source == FA) {
				message.setText("Speed set to fast");
				FA.setState(true);
				Objdelay = 5;
			}
			if (source == XFA) {
				message.setText("Speed set to x-fast");
				XFA.setState(true);
				Objdelay = 1;
			}
		}
		

		//ENVIRONMENT SELECTIONS
		if (source == MER || source == VEN || source == EAR || source == MOO || source == MAR || source == JUP ||source == SAT || source == URA || source == NEP || source == PLU) {
			//Clears all existing checkboxes
			MER.setState(false);
			VEN.setState(false);
			EAR.setState(false);
			MOO.setState(false);
			MAR.setState(false);
			JUP.setState(false);
			SAT.setState(false);
			URA.setState(false);
			NEP.setState(false);
			PLU.setState(false);
			
			if (source == MER) {
				g = mer;
				message.setText("Mercury "+g+" m/s^2");
				MER.setState(true);
			}
			if (source == VEN) {
				g = ven;
				message.setText("Venus "+g+" m/s^2");
				VEN.setState(true);
			}
			if (source == EAR) {
				g = ear;
				message.setText("Earth "+g+" m/s^2");
				EAR.setState(true);
			}
			if (source == MOO) {
				g = moo;
				message.setText("Moon "+g+" m/s^2");
				MOO.setState(true);
			}
			if (source == MAR) {
				g = mar;
				message.setText("Mars "+g+" m/s^2");
				MAR.setState(true);
			}
			if (source == JUP) {
				g = jup;
				message.setText("Jupiter "+g+" m/s^2");
				JUP.setState(true);
			}
			if (source == SAT) {
				g = sat;
				message.setText("Saturn "+g+" m/s^2");
				SAT.setState(true);
			}
			if (source == URA) {
				g = ura;
				message.setText("Uranus "+g+" m/s^2");
				URA.setState(true);
			}
			if (source == NEP) {
				g = nep;
				message.setText("Neptune "+g+" m/s^2");
				NEP.setState(true);
			}
			if (source == PLU) {
				g = plu;
				message.setText("Pluto "+g+" m/s^2");
				PLU.setState(true);
			}		
		}		
	}
	
	public boolean CheckObjResize(int x) {
		//Variables
		ok = true;  //global variable, therefore needs to be resized
		int TS, half;
		int i=0;						 		// index for vector of rectangles.
		int newXMax; int newXMin; int newYMax; int newYMin;
		
		TS = x; 								// get the value
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
		return ok;
	}	

	public int getSeconds() {
		long current = System.currentTimeMillis();
		return (int)((current - this.milsec)/1000);
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
		public void updateSize(int NS) {
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
			// Triangle for calculating point C1 and C2
			xt = l*Math.cos(rad);
			yt = l*Math.sin(rad);
			
			//start point for projectile-little triangle
			cxt = (l+20)*Math.cos(rad);		
			cyt = (l+20)*Math.sin(rad);
			
			// Changing degrees into radians
			rad = (deg*2*Math.PI)/360;
			
			// Sub triangle Calculations to find Point A1 and A2
			x1 = (w/2)*Math.cos(rad);
			y1 = (w/2)*Math.sin(rad);
			// A1 and A2 points for Cannon
			a1.x = (int)((sheet.getWidth()-(CBbase/2)) - y1);
			a1.y = (int)((sheet.getHeight()-(CBbase/2)) + x1);
			a2.x = (int)((sheet.getWidth()-(CBbase/2)) + y1);
			a2.y = (int)((sheet.getHeight()-(CBbase/2)) - x1);
			
			// C1 and C2 points for Cannon
			c1.x = (int)(((sheet.getWidth()-(CBbase/2))- xt) - y1);
			c1.y = (int)(((sheet.getHeight()-(CBbase/2))- yt) + x1);
			c2.x = (int)(((sheet.getWidth()-(CBbase/2))- xt) + y1);
			c2.y = (int)(((sheet.getHeight()-(CBbase/2))- yt) - x1);
			
			Cannon.reset();
			Cannon.addPoint(a1.x,a1.y);
			Cannon.addPoint(a2.x,a2.y);
			Cannon.addPoint(c2.x,c2.y);
			Cannon.addPoint(c1.x,c1.y);
			
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
			g.setColor(Color.white);
			g.fillOval(xVal-(SObj-1)/2,	yVal-(SObj-1)/2,	SObj,	SObj);
			g.setColor(Color.black);
			g.drawOval(xVal-(SObj-1)/2,	yVal-(SObj-1)/2,	SObj-1,	SObj-1);

			// Projectile
			if (projectileExists) {
				g.setColor(Color.black);
				g.fillOval(projectile.GetXValue()-((20)/2), projectile.GetYValue()-((20)/2), 21, 21);
			}
			
			// Painting all of the vector Rectangles
			for(int i = 0; i < Walls.size(); i++) {
				t = Walls.elementAt(i);
				g.fillRect(t.x, t.y, t.width, t.height);
			}
			
			// Polygon
			g.setColor(Color.gray);
			g.fillPolygon(Cannon);
			g.setColor(Color.gray);
			g.drawPolygon(Cannon);
			
			// Cannon Circle
			g.setColor(Color.black);
			g.fillOval(sheet.getWidth()-(CBbase), sheet.getHeight()-(CBbase), CBbase, CBbase);
			g.setColor(Color.red);
			g.drawOval(sheet.getWidth()-(CBbase), sheet.getHeight()-(CBbase), CBbase-1, CBbase-1);
			
			
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
			Rectangle b = new Rectangle(GetObject());
			// If the ball hits the cannon, give point to the ball and reset it.
			if (Cannon.intersects(b)) {
				bScore += 1;
				ballS.setText("Ball: "+bScore);
				message.setText("Ball Scores!");
				yVal = (SObj-1)/2 + 2;
				xVal = (SObj-1)/2 + 2;
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
		
		public void Collision() {
			int i = 0;
			Rectangle b = new Rectangle(Obj.GetObject());
			Rectangle p = new Rectangle(projectile.GetObject());
			Rectangle t = new Rectangle();
			
			// If the projectile hits a rectangle, it destroys it
			while(i < Walls.size()) {
				t = Obj.getOne(i);
				if(p.intersects(t)) {
					Obj.removeOne(i);
					projectileExists = false;
					message.setText("BOOM!!!");
				}
				i++;
			}
			
			// If the projectile hits the ball, gives point to the player
			if(p.intersects(b)) {
				pScore += 1;
				playerS.setText("Player: "+pScore);
				message.setText("Player Scores!");
				Obj.SetXValue(GetRandomNumber(50, sheet.getWidth()-50));
				Obj.SetYValue(GetRandomNumber(50, sheet.getHeight()-50));
				System.out.print(xVal);
				System.out.print(yVal);
				projectileExists = false;	
			}
			
			// If the projectile hits the cannon, gives point to the ball
			if(Cannon.intersects(p)) {
				bScore += 1;
				ballS.setText("Ball: "+bScore);
				message.setText("Ball Scores!");
				projectileExists = false;
			}
			
			// If the projectile hits the ground, destroys the projectile
			if(projectile.GetYValue() >= sheet.getHeight()) {
				projectileExists = false;
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