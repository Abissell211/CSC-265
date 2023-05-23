import java.awt.*;
import java.awt.event.*;

public class PanelMouse extends Frame implements WindowListener, MouseListener, MouseMotionListener {
	final int	WinLeft = 10;					// left side of frame
	final int	WinTop = 10;					// top of frame
	Point		FrameSize = new Point(640,400);	// initial frame size
	Panel		sheet = new Panel();
	List		list = new List(13);
	
	PanelMouse() {
		setLayout(new BorderLayout());			// layout border
		setBounds(WinLeft, WinTop, FrameSize.x, FrameSize.y);	// size and position of the frame
		setBackground(Color.lightGray);
		sheet.setLayout(new BorderLayout(0,0));	// sheet border layout
		sheet.setVisible(true);
		sheet.add("Center",list);				// add the list to the center of the Panel sheet
		add("Center",sheet);					// add sheet Panel to center of Application
		addWindowListener(this);
		list.addMouseListener(this);
		list.addMouseMotionListener(this);
		setVisible(true);						// make it visible
		validate();
	}
	
	public static void main(String[] args) {
		new PanelMouse();
	}
	
	public void Stop() {
		removeWindowListener(this);
		list.removeMouseListener(this);
		list.removeMouseMotionListener(this);
		dispose();
	}
//---------------Window Events---------------//	
	public void windowClosing(WindowEvent e){
		Stop();
	}
	public void windowClosed(WindowEvent e){}
	public void windowOpened(WindowEvent e){
		list.add("Window opened");
	}
	public void windowActivated(WindowEvent e){
		list.add("Window activated");
	}
	public void windowDeactivated(WindowEvent e){
		list.add("Window deactivated");
	}
	public void windowIconified(WindowEvent e){
		list.add("Window iconified");
	}
	public void windowDeiconified(WindowEvent e){
		list.add("Window deiconofied");
	}
//----------------Mouse Events----------------//	
	public void mousePressed(MouseEvent e){
		String button = "";
		if(e.getButton()==MouseEvent.BUTTON1)
			button = "Left";
		if(e.getButton()==MouseEvent.BUTTON2)
			button = "Center";
		if(e.getButton()==MouseEvent.BUTTON3)
			button = "Right";
		list.add(button+" mouse button "+e.getButton()+" pressed");
	}
	public void mouseReleased(MouseEvent e){
		list.add("Mouse button "+e.getButton()+" released");
	}
	public void mouseClicked(MouseEvent e){
		list.add("Mouse Clicked "+e.getClickCount()+" clicks");
	}
	public void mouseMoved(MouseEvent e){
		//list.add("Mouse Moved");
	}
	public void mouseDragged(MouseEvent e){
		list.add("Mouse Dragged");
	}
	public void mouseEntered(MouseEvent e){
		list.add("Mouse Entered");
	}
	public void mouseExited(MouseEvent e){
		list.add("Mouse Exited");
	}
}