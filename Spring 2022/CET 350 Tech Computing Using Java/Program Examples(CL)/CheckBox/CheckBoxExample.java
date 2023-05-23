import java.awt.*;
import java.awt.event.*;

public class CheckBoxExample extends Frame implements ItemListener, WindowListener {
	private static final long serialVersionUID = 1L;
	
	private Checkbox CheckBox1, CheckBox2, CheckBox3, CheckBox4;
	private Checkbox RadioButton1, RadioButton2, RadioButton3, RadioButton4;
	
	private CheckboxGroup RadioButtonGroup;
	private Label CheckBoxOut, RadioButtonOut;
	
	public static void main(String[] args) {
		new CheckBoxExample();
	}
	
	// Constructor
	public CheckBoxExample() { 
		// Labels
		RadioButtonOut 	= new Label();
		CheckBoxOut 	= new Label();
		
		// CheckboxGroup
		RadioButtonGroup = new CheckboxGroup();
		
		// Checkboxes (Radio)
		RadioButton1 = new Checkbox("Radio Button 1", RadioButtonGroup, true);
		RadioButton2 = new Checkbox("Radio Button 2", RadioButtonGroup, false);
		RadioButton3 = new Checkbox("Radio Button 3", RadioButtonGroup, false);
		RadioButton4 = new Checkbox("Radio Button 4", RadioButtonGroup, false);
		
		// Checkboxes
		CheckBox1 = new Checkbox("Check Box 1", false);
		CheckBox2 = new Checkbox("Check Box 2", false);
		CheckBox3 = new Checkbox("Check Box 3", false);
		CheckBox4 = new Checkbox("Check Box 4", false);
		
		// Frame layout
		setLayout(new GridLayout(0,2));
		
		// Size and Location of Frame
		setBounds(100,100,300,150);
		
		// Make visible and validate
		setVisible(true);
		validate();
		
		// Add Checkboxes to the Frame
		add(RadioButton1);
		add(CheckBox1);
		add(RadioButton2);
		add(CheckBox2);
		add(RadioButton3);
		add(CheckBox3);
		add(RadioButton4);
		add(CheckBox4);
		add(RadioButtonOut);
		add(CheckBoxOut);
		
		// Set the text of the Radio Button Label to the active Checkbox
		RadioButtonOut.setText(RadioButtonGroup.getSelectedCheckbox().getLabel());
		
		// Add the Listeners
		RadioButton1.addItemListener(this);
		RadioButton2.addItemListener(this);
		RadioButton3.addItemListener(this);
		RadioButton4.addItemListener(this);
		CheckBox1.addItemListener(this);
		CheckBox2.addItemListener(this);
		CheckBox3.addItemListener(this);
		CheckBox4.addItemListener(this);
		addWindowListener(this);
	}
	
	public void stop() {
		RadioButton1.removeItemListener(this);
		RadioButton2.removeItemListener(this);
		RadioButton3.removeItemListener(this);
		RadioButton4.removeItemListener(this);
		CheckBox1.removeItemListener(this);
		CheckBox2.removeItemListener(this);
		CheckBox3.removeItemListener(this);
		CheckBox4.removeItemListener(this);
		dispose();
	}
	
	public void itemStateChanged(ItemEvent e) {
		// Get the source and cast it to the Checkbox so we can get information from the Checkbox
		Checkbox cb = (Checkbox)e.getSource();
		
		// Check if it is a Checkbox used in the group
		if(cb == RadioButton1 || cb == RadioButton2 || cb == RadioButton3 || cb == RadioButton4)
			//Change the Radio Button Label to display the active Checkbox
			RadioButtonOut.setText(RadioButtonGroup.getSelectedCheckbox().getLabel());
			
		if(cb == CheckBox1)
			CheckBoxOut.setText("CB1 "+cb.getState());
		if(cb == CheckBox2)
			CheckBoxOut.setText("CB2 "+cb.getState());
		if(cb == CheckBox3)
			CheckBoxOut.setText("CB3 "+cb.getState());
		if(cb == CheckBox4)
			CheckBoxOut.setText("CB4 "+cb.getState());
		}
		
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