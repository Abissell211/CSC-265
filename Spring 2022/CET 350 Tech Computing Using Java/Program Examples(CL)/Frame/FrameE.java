// Frame Example
import java.awt.*;

public class FrameE extends Frame {
	FrameE(){
		Frame f = new Frame();
		f.setSize(400,300);
		f.setTitle("TEST FRAME");
		f.setLayout(null);
		f.setVisible(true);
	}
	
	public static void main(String args[]) {
		FrameE awt_obj = new FrameE();
	}
}