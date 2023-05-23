import java.awt.*;
import java.awt.event.*;

public class menu implements ActionListener, WindowListener, ItemListener {
// screen dimensions
	private int sw = 650;
	private int sh = 480;
// create frame object
	private Frame EditorFrame;
// create TextArea for typing
	private TextArea EditArea;
// the menu bar
	private MenuBar MMB;
// Menu's will be added to the MenuBar as well as become sub menu's within a menu
	private Menu FILE, TEXT;		// Main items on menu bar
	private Menu NEW, SIZE, FONT;	// Sub menu items under menu items
// The MenuItems trigger events, they are the terminals of a Menu
	private MenuItem FOLDER, DOCUMENT;	// terminal items in New menu
	private MenuItem QUIT;				// Menu Item
// Another terminal of the menu structure is a CheckboxMenuItem which can have a *check* displayed
	private CheckboxMenuItem S10, S14, S18;	// Checkbox Menu Items for Size
	private CheckboxMenuItem TNR, CO;		// Checkbox Menu Items for Font
// Font has three parameters: the type, style and size
	private int FontType = Font.PLAIN;
	private String FontStyle = "TimesNewRoman";
	private int FontSize = 14;
	
	public static void main(String[] args) {
		new menu();
	}	
	// constructor
	public menu() {
		EditArea = new TextArea("",sw-10,sh-10,TextArea.SCROLLBARS_BOTH);
	// Set up the Frame object
		EditorFrame = new Frame("Editor");				// Frame for Application
		EditorFrame.setLayout(new BorderLayout(0,0));	// Frame BorderLayout
		EditorFrame.setBackground(Color.lightGray);		// Frame Background Color
		EditorFrame.setForeground(Color.black);			// Frame Foreground Color
		EditorFrame.add("Center",EditArea);				// Add the TextArea
	// Specify the Menu structure, it is sequential so add it in the order left to right and top to bottom
		MMB = new MenuBar();							// Create Menu bar
		FILE = new Menu("FILE");						// Create first Menu entry for Menu bar
		NEW = new Menu("NEW");							// Create first Menu entry for File Menu
	// add MenuItem Folder with short cut key to Menu entery New
		FOLDER = NEW.add(new MenuItem("Folder",new MenuShortcut(KeyEvent.VK_F)));
	// add MenuItem Document with short cut key to Menu entry New
		DOCUMENT = NEW.add(new MenuItem("Document",new MenuShortcut(KeyEvent.VK_D)));
	// add and finish the first MenuBar entry FILE
		FILE.add(NEW);									// add Menu New to File Menu
		FILE.addSeparator();							// add separator to File Menu
	// add MenuItem Quit with short cut key to File Menu
		QUIT = FILE.add(new MenuItem("Quit",new MenuShortcut(KeyEvent.VK_Q)));
	// Specify the second Menu entry
		TEXT = new Menu("TEXT");						// Create second Menu entry for Menu bar
		SIZE = new Menu("Size");						// Create first Menu entry for Text Menu
		FONT = new Menu("Font");						// Create second Menu Entry for Text Menu
	// Create the Font Size CheckboxMenuItems and add to SIZE Menu
		SIZE.add(S10 = new CheckboxMenuItem("10"));		// CheckboxMenuItem size 10
		SIZE.add(S14 = new CheckboxMenuItem("14"));		// CheckboxMenuItem size 14
		SIZE.add(S18 = new CheckboxMenuItem("18"));		// CheckboxMenuItem size 18
	// Set Size 14 active, *check*
		S14.setState(true);								// init Checkbox selection to 14
	// add SIZE Menu to the TEXT Menu
		TEXT.add(SIZE);									// add Size Menu to Text Menu
	// Create the Font Style CheckboxMenuItems and add to FONT Menu
		FONT.add(TNR = new CheckboxMenuItem("TimesNewRoman"));
		FONT.add(CO = new CheckboxMenuItem("Courier"));
	// Set Font Times New Roman active, *check*
		TNR.setState(true);								// init Checkbox selection to TimesNewRoman
	// Add Font Menu to the TEXT Menu
		TEXT.add(FONT);									// add Font Menu to Text Menu
	// Add the FILE and TEXT Menu's to the Menu Bar
		MMB.add(FILE);									// add File to Menu bar
		MMB.add(TEXT);									// add Text to Menu bar
	// Turn on the Listener for the MenuItem's and the MenuShortCut's
		DOCUMENT.addActionListener(this);				// add listener for File menu
		FOLDER.addActionListener(this);				// add listener for File menu
		QUIT.addActionListener(this);				// add listener for File menu
	// Turn on the Listener for the CheckboxMenuItem's
		S10.addItemListener(this);					// add listener for font size
		S14.addItemListener(this);					// add listener for font size
		S18.addItemListener(this);					// add listener for font size
		TNR.addItemListener(this);					// add listener for font size
		CO.addItemListener(this);					// add listener for font size
	// Add the MenuBar to the Frame
		EditorFrame.setMenuBar(MMB);				// add menu bar to Frame
	// Turn on the WindowListener, size, and validate the Frame
		EditorFrame.addWindowListener(this);		// add window listener
		EditorFrame.setSize(sw,sh);					// set Frame size
		EditorFrame.setResizable(true);
		EditorFrame.setVisible(true);
		EditorFrame.validate();
	// Set the Font based on the current settings
		setTheFont();
	}
	
	// SetTheFont determines what size and type is active and sets the Font accordingly
	public void setTheFont() {
		FontSize = 10;
		if(S10.getState() == true)
			FontSize = 10;
		if(S14.getState() == true)
			FontSize = 14;
		if(S18.getState() == true)
			FontSize = 18;
		FontStyle = "TimesNewRoman";
		if(TNR.getState() == true)
			FontStyle = "TimesNewRoman";
		if(CO.getState() == true)
			FontStyle = "Courier";
		FontType = Font.PLAIN;
		EditArea.setFont(new Font(FontStyle,FontType,FontSize));
	}
	
	// itemStateChanged changes the *check* to the selected CheckboxMenuItem and updates the Font
	public void itemStateChanged(ItemEvent e) {
		CheckboxMenuItem checkbox = (CheckboxMenuItem) e.getSource();
		if(checkbox == S10 || checkbox == S14 || checkbox == S18) {
			S10.setState(false);
			S14.setState(false);
			S18.setState(false);
			checkbox.setState(true);
		}
		if(checkbox == TNR || checkbox == CO) {
			TNR.setState(false);
			CO.setState(false);
			checkbox.setState(true);
		}
		setTheFont();
	}
	// actionperformed processes the MenuItem's and MenuShortCut keys
	public void actionPerformed(ActionEvent e) {
		Object source = e.getSource();
		if(source == FOLDER)
			EditArea.append("\nFolder\n");
		if(source == DOCUMENT)
			EditArea.append("\nDOCUMENT\n");
		if(source == QUIT)
			stop();
	}
	
	// stop removes the Listeners and shuts down the program
	public void stop() {
		DOCUMENT.removeActionListener(this);		// remove listener for File menu
		FOLDER.removeActionListener(this);			// remove listener for File menu
		QUIT.removeActionListener(this);			// remove listener for File menu
		S10.removeItemListener(this);				// remove listener for font size
		S14.removeItemListener(this);				// remove listener for font size
		S18.removeItemListener(this);				// remove listener for font size
		TNR.removeItemListener(this);				// remove listener for font size
		CO.removeItemListener(this);				// remove listener for font size
		EditorFrame.removeWindowListener(this);
		EditorFrame.dispose();
	}
	
	// WidowEvents
	public void windowClosing(WindowEvent e) {
		stop();
	}
	public void windowClosed(WindowEvent e) {}
	public void windowOpened(WindowEvent e) {}
	public void windowActivated(WindowEvent e) {}
	public void windowDeactivated(WindowEvent e) {}
	public void windowIconified(WindowEvent e) {}
	public void windowDeiconified(WindowEvent e) {}
}