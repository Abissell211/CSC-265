//Andrew Bissell, Daniel Nash
//GROUP 1 
//Tech Computing Using Java CET-350
//Chat Program
//bis3683@calu.edu, nas8662@calu.edu
package Chat;

import java.io.*;
import java.awt.*;
import java.awt.event.*;
import java.net.Socket;
import java.net.ServerSocket;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.SocketTimeoutException;


public class Chat implements Runnable, ActionListener, WindowListener {
	private static final long serialVersionUID = 10L;
	protected final static boolean auto_flush = true;		// enhances readability of printwriter
	BufferedReader br;										// input
	PrintWriter pw;											// output
	
	//Window initializations
	final int WIN_WIDTH = 600;
	final int WIN_HEIGHT = 400;
	private Insets I;
	
	
	//Buttons
	Button ChangePortButton = new Button("Change Port");
	Button SendButton 		= new Button("   Send   ");
	Button ServerButton 	= new Button("Start Server");
	Button ClientButton 	= new Button("  Connect  ");
	Button DisconnectButton = new Button("Disconnect");
	Button ChangeHostButton = new Button("Change Host");
	
	Label PortLabel = new Label("Port: ");
	Label HostLabel = new Label("Host: ");
	
	TextField ChatText = new TextField("", 10);
	TextField PortText = new TextField("", 10);
	TextField HostText = new TextField("", 10);
	
	Frame DispFrame;
	
	Thread theThread;
	
	TextArea DialogScreen = new TextArea("", 10, 80);
	TextArea MessageScreen = new TextArea("", 3, 80);
	
	Socket client;
	Socket server;
	
	ServerSocket listen_socket;		// socket for listening for connections
	
	int DEFAULT_PORT = 44004;
	int port = DEFAULT_PORT;
	int service = 0;				// the state of the machine- initial=0, server=1, client=2
	int timeout = 1000;
	boolean more = true;			// controls main loop
	String host = "";				// host name
	String input = "";				// input from either host or user.
		
	public static void main(String[] args) {
//		String timeOutString = "-1";
//		int timeOutInt = -1;
//		
//		//get user input as string
//		try {
//			timeOutString = new BufferedReader(new InputStreamReader(System.in)).readLine();
//		} catch (IOException e) {}
//		
//		
//		//parse answer or reassign
//		try {
//			timeOutInt = Integer.parseInt(timeOutString);
//		} catch (NumberFormatException e) {
//			timeOutInt = 1000;
//		} 
		
		new Chat();
	}
	
	
	Chat() {
		//timeout = passedTimeOut;		//sets the wait to the global
		implementLayout();
		
		PortText.setText(String.valueOf(port));		//set initial port value
		
		//add listeners
		ChangePortButton.addActionListener(this);;
		ChatText.addActionListener(this);
		SendButton.addActionListener(this);
		ServerButton.addActionListener(this);
		ClientButton.addActionListener(this);
		DisconnectButton.addActionListener(this);
		ChangeHostButton.addActionListener(this);
		
		service = 0;		//initialize
		more = true;		//continues the main loop
	}
	
	public void implementLayout() {
		
		//declarations and implementations
		DispFrame = new Frame("Chat");		
		Panel northArea = new Panel();
		Panel centerArea = new Panel();
		Panel southArea = new Panel();
		GridBagLayout gblDispCenter = new GridBagLayout();
		GridBagLayout gblDispSouth = new GridBagLayout();
		GridBagLayout gblDispNorth = new GridBagLayout();
		GridBagConstraints c = new GridBagConstraints();
		
		//set the main layout
		DispFrame.setLayout(new BorderLayout(0,0));
		
		//add Panels corresponding to the different areas
		DispFrame.add(BorderLayout.NORTH, northArea);
		DispFrame.add(BorderLayout.SOUTH, southArea);
		DispFrame.add(BorderLayout.CENTER, centerArea);
		
		//apply layout managers to different areas
		northArea.setLayout(gblDispNorth);
		southArea.setLayout(gblDispSouth);
		centerArea.setLayout(gblDispCenter);
		
		DispFrame.setSize(WIN_WIDTH, WIN_HEIGHT);
		
		//Set colors of the different areas
		DispFrame.setBackground(Color.WHITE);
		DispFrame.setForeground(Color.BLACK);
		
		//GridBagLayout initialization
		//	Top GridBagLayout
		double colWeightNorth[] = {1};
		double rowWeightNorth[] = {1};
		int colWidthNorth[] = {1};
		int rowHeightNorth[] = {1};
		gblDispNorth.columnWeights = colWeightNorth;
		gblDispNorth.rowWeights = rowWeightNorth;
		gblDispNorth.columnWidths = colWidthNorth;
		gblDispNorth.rowHeights = rowHeightNorth;
		//	Center GridBagLayout
		double colWeightCenter[] = {1,1,1,1,1,1,1};
		double rowWeightCenter[] = {1,1,1,1};
		int colWidthCenter[] = {1,1,1,1,1,1,1};
		int rowHeightCenter[] = {1,1,1,1};
		gblDispCenter.columnWeights = colWeightCenter;
		gblDispCenter.rowWeights = rowWeightCenter;
		gblDispCenter.columnWidths = colWidthCenter;
		gblDispCenter.rowHeights = rowHeightCenter;
		//	Bottom GridBagLayout
		double colWeightSouth[] = {1};
		double rowWeightSouth[] = {1};
		int colWidthSouth[] = {1};
		int rowHeightSouth[] = {1};
		gblDispSouth.columnWeights = colWeightSouth;
		gblDispSouth.rowWeights = rowWeightSouth;
		gblDispSouth.columnWidths = colWidthSouth;
		gblDispSouth.rowHeights = rowHeightSouth;
		

		//Intialize Constraints- used across all three sheets
		c.anchor = GridBagConstraints.CENTER;			//places component into the center of the cell
		c.weightx = 1;  								//specifies resizing behavior
		c.weighty = 1;  								//specifies resizing behavior
		c.gridheight = 1;  								//# of cells in a col
		c.gridwidth = 1;    							//# of cells in a row
		c.fill = GridBagConstraints.HORIZONTAL;  		//fills the component horizontally and vertically for resizing
		
		//Components-Top sheet
		c.gridx = 0;
		c.gridy = 0;
		gblDispNorth.setConstraints(DialogScreen, c);
		northArea.add(DialogScreen);
		
		//Components-Center sheet
		//	ROW 0
		c.gridx = 0;
		c.gridy = 0;
		c.gridwidth = 6;
		gblDispCenter.setConstraints(ChatText, c);
		centerArea.add(ChatText);
		
		c.gridwidth = 1;
		c.gridx = 6;
		gblDispCenter.setConstraints(SendButton, c);
		centerArea.add(SendButton);
		
		//	ROW 1
		c.gridx = 2;
		c.gridy = 1;
		gblDispCenter.setConstraints(HostLabel, c);
		centerArea.add(HostLabel);
		
		c.gridx = 3;
		gblDispCenter.setConstraints(HostText, c);
		centerArea.add(HostText);
		
		c.gridx = 5;
		gblDispCenter.setConstraints(ChangeHostButton, c);
		centerArea.add(ChangeHostButton);
		
		c.gridx = 6;
		gblDispCenter.setConstraints(ServerButton, c);
		centerArea.add(ServerButton);
		
		//	ROW 2
		c.gridx = 2;
		c.gridy = 2;
		gblDispCenter.setConstraints(PortLabel, c);
		centerArea.add(PortLabel);
		
		c.gridx = 3;
		gblDispCenter.setConstraints(PortText, c);
		centerArea.add(PortText);
		
		c.gridx = 5;
		gblDispCenter.setConstraints(ChangePortButton, c);
		centerArea.add(ChangePortButton);
		
		c.gridx = 6;
		gblDispCenter.setConstraints(ClientButton, c);
		centerArea.add(ClientButton);
		
		//	ROW 3
		c.gridx =  6;
		c.gridy = 3;
		gblDispCenter.setConstraints(DisconnectButton, c);
		centerArea.add(DisconnectButton);
		
		//Components-Bottom Sheet
		c.gridx = 0;
		c.gridy = 0;
		gblDispSouth.setConstraints(MessageScreen, c);
		southArea.add(MessageScreen);
		
		//set enable/disable
		MessageScreen.setEditable(false);
		ChatText.setEditable(false);
		DialogScreen.setEditable(false);
		
		PortText.setText(String.valueOf(port));
		HostText.setText("");
		
		ClientButton.setEnabled(false);
		
		
		//add the listeners to the frame
		DispFrame.setVisible(true);
		DispFrame.addWindowListener(this);
	}
	
	public void stop() {
		try {	// make sure all sockets, bufferedreaders, and printwriters are closed
			if(client != null) {
				client.close();
			}
			if(server != null) {
				server.close();
			}
			if(br != null) {
				br.close();
			}
			if(pw != null) {
				pw.close();
			}
		} catch (IOException e) {}
		
		if (theThread != null) {
			theThread.setPriority(Thread.MIN_PRIORITY);
		}
		
		// Remove all listeners
		ChangePortButton.removeActionListener(this);
		ChatText.removeActionListener(this);
		SendButton.removeActionListener(this);
		ServerButton.removeActionListener(this);
		ClientButton.removeActionListener(this);
		DisconnectButton.removeActionListener(this);
		ChangeHostButton.removeActionListener(this);
		
		// remove window listener and dispose
		DispFrame.removeWindowListener(this);
		DispFrame.dispose();
		System.exit(0);
	}
	
	public void start() {
		if(theThread == null) {
			theThread = new Thread(this);
			theThread.start();
		}
	}
	
	public void close() {
		try {
			if(server != null) {	// does the server socket exist?
				if(pw != null) {
					pw.print("");	//send null to other device
				}
				server.close(); 	// close the socket
				server = null;		// null the socket
			}
			if (client != null) {
				if (pw != null) {
					pw.print("");
				}
				client.close();
				client = null;
			}
			if (listen_socket != null) {
				if (pw != null) {
					pw.print("");
				}
				listen_socket.close();
				listen_socket = null;
			}
			
		} catch(IOException e) {
			MessageScreen.append(e.toString() + "\n");
		}
		
		// reset the buttons
		ChangePortButton.setEnabled(true);
		SendButton.setEnabled(true);
		ServerButton.setEnabled(true);
		ClientButton.setEnabled(false);
		DisconnectButton.setEnabled(true);
		ChangeHostButton.setEnabled(true);
		
		// reset the textfield, service state and thread
		DispFrame.setTitle("Chat");
		ChatText.setText("");
		ChatText.setEditable(false);
		HostText.setText("");
		host = "";
		PortText.setText(String.valueOf(DEFAULT_PORT));
		port = DEFAULT_PORT;
		service = 0;					
		theThread = null;
	}
	
	public void Message_Display(String message) {
		if(service == 1) {	// checks if the machine state is server (1)
			if (!message.equals("")) {
				MessageScreen.append("Server: " + message + "\n"); // If so appends the Server to the status message TextArea
			}
			
		}
		
		if(service == 2) {	// checks if the machine state is client (2)
			if (!message.equals("")) {
				MessageScreen.append("Client: " + message + "\n"); // If so appends the Client to the status message TextArea
			}			
		}
		
		ChatText.requestFocus(); // sets the focus back to the Chat TextField so the user can just type their message
	}
	
	
	public void run() {
		theThread.setPriority(Thread.MAX_PRIORITY);
		
		while(more) {
			try {
				input = br.readLine();	//take the data from the bufferedreader and put it into the input sting
				
				if(input == null) {		// if the input is empty invert more
					more = !more;
					if (server != null) {
						//server is active for this instance of program
						MessageScreen.append("Server Disconnected\n");
						//DispFrame.setTitle("Chat");
					} else if (client != null) {
						//client is active for this instance of program
						MessageScreen.append("Client Disconnected\n");
						//DispFrame.setTitle("Chat");
					}
				} else {
					DialogScreen.append("in: " + input + "\n");
				}
				
			} catch(IOException e) {
				//MessageScreen.append(e.getMessage() + "-->in the thread loop catch statement<--" +"\n");
			}
		}
		
		close();
	}
	
	public void actionPerformed(ActionEvent e) {	// All the connections to the network sockets happen here
		Object source = e.getSource();
		String data = "";
		Integer portWrapper; 
		
		// Disconnect Button
		if (source == DisconnectButton) {
			//disconnectAll();
			MessageScreen.append("Disconnected.\n");
			pw.print("");
			if (theThread != null) {
				theThread.interrupt();
			}
			
			close();  		//set to initial state
		}
		
		if (source == ChangeHostButton) {
			data = HostText.getText();
			
			if (data.equals("")) {
				ClientButton.setEnabled(false);
			} else {
				ClientButton.setEnabled(true);
				host = data;
			}
		}
		
		if (source == ChangePortButton || source == PortText) {
			// Get the text from the Port TextField
			data = PortText.getText();
			
			// Set the port variable to this new int port value
			try {
				portWrapper = Integer.parseInt(data);
				port = portWrapper.intValue();
				
				if (port <= 0) {
					MessageScreen.append("Invalid port, reset to 44004\n");
					port = 44004;
					PortText.setText("44004");
				}
				
			} catch (NumberFormatException er) {
				port = 44004;
				MessageScreen.append("Invalid port, reset to 44004\n");
				PortText.setText("44004");
			}
			
			//Allow connection at this point
			ClientButton.setEnabled(true);
		}
		


		
		
		// Client Button
		if (source == ClientButton) {
			// Status Message
			MessageScreen.append("Client: timeout time set to " + (timeout) + "mS\n");
			
			try {
				ServerButton.setEnabled(false);	
				ClientButton.setEnabled(false);	
				
				// Check if the Server exists and close and clear it if it does
				if(server != null) {	
					server.close();
					server = null;
				}
				
				server = new Socket();		//socket TO the server
				
				// Status message
				MessageScreen.append("Client: Connecting to " + host + ":" + port + "\n");
				
				server.setSoTimeout(timeout);	// client timeout < server timeout
				
				try {
					server.connect(new InetSocketAddress(host, port)); // Send a connection request to the server
					
					// update Frame
					DispFrame.setTitle("Client: connected to " + server.getInetAddress() + " at port " + server.getPort());
					MessageScreen.append("Client: connected to " + server.getInetAddress() + " at port " + server.getPort() + "\n");
					try {
						br = new BufferedReader(new InputStreamReader (server.getInputStream()));	// listen for server socket input
						pw = new PrintWriter(server.getOutputStream(), auto_flush);					// print out to server
						service = 2;		//client mode
						ChatText.setEditable(true);
						more = true;		//main thread loop- continue
						start();  //main thread- start
					} catch (SocketTimeoutException s) {
						MessageScreen.append(s.toString() + "\n");
						close();
					}
				} catch (IOException er) {
					MessageScreen.append(er.toString() + "\n");
					close();
				}	
			} catch (IOException er) {
				MessageScreen.append(er.toString() + "\n");
				close();
			}
		}
		
		
		
		if (source == SendButton) {
			// Chat TextField or Send button will get the text form the Chat TextField
			data = ChatText.getText();
			
			DialogScreen.append("out: " + data + "\n");		// Append the message to the DialogScreen TextArea
			pw.println(data);							// Send the message out through the Socket's PrintWriter
			
			// Clear the Chat TextField
			ChatText.setText("");
		}
		
		if (source == ServerButton) {
			// Send a message to the status message TextArea
			MessageScreen.append("");

			try {
				ServerButton.setEnabled(false);	// Disable Server Button
				ClientButton.setEnabled(false);	// Disable Client Button
				// Check if the ServerSocket exists and close and clear it if it does
				if(listen_socket != null) {	
					listen_socket.close();
					listen_socket = null;
				}
				
				//send message to the status message Text Area
				MessageScreen.append("Server: Attempting to open socket\n");
				
				listen_socket = new ServerSocket(port);	// Set the ServerSocket port
				
				//send message to the status message Text Area
				MessageScreen.append("Server: listening on port " + PortText.getText() + "\n");
				
				listen_socket.setSoTimeout(10*timeout); // Set the timeout for the server to wait for a connection, this should be longer than the client request timer
				
				// Send a message to the status message TextArea
				MessageScreen.append("Server: timeout" + (10*timeout) + "mS.\n");
				  
				if(client != null) {					// Check if the client Socket exists and close and clear it if it does
					client.close();
					client = null;
				}
				
				try {
					// send an updated status message to the stauts message TextArea
					MessageScreen.append("Waiting for a request on " + PortText.getText() + "\n");
				
					// Listen for a Socket request
					client = listen_socket.accept();	
					
					// Set the title of the Frame to indicate it is a server
					DispFrame.setTitle("Server: connection from " + client.getInetAddress() + "\n");
					MessageScreen.append("Server: connection from " + client.getInetAddress() + "\n");	// Send an updated status message to the status message TextArea that a connection has been made from

				
					try {
						br = new BufferedReader(new InputStreamReader (client.getInputStream()));	// Create the BufferedReader
						pw = new PrintWriter(client.getOutputStream(), auto_flush);					// Create the PrintWriter
	
					
					// Change the state, service, to the server mode service = 1;
					service = 1;
					
					// Enable the Chat TextField
					ChatText.setEditable(true);
					
					// Set the run while loop flag, more, to true
					more = true;
					
					// start the Thread with start();
					start();
					} catch(IOException er) {
						MessageScreen.append(er.toString() + "\n");
						close();
					}
				} catch (SocketTimeoutException s) {
					MessageScreen.append(s.toString() + "\n");
					close();
				}	
			} catch(IOException er) {
				MessageScreen.append(er.toString() + "\n");
				close();
			}
		}
		
		
		ChatText.requestFocus();
	}
	
	
	public void disconnectAll() {
		// Send a status message to the status display TextArea
		MessageScreen.append("Disconnected.\n");
		
		//reset values
		ChatText.setText("");
		ChatText.setEditable(false);
		port = 44004;
		PortText.setText(String.valueOf(port));
		HostText.setText("");
		
		try {	// make sure all sockets, bufferedreaders, and printwriters are closed
			if(client != null) {
				client.close();
			}
			if(server != null) {
				server.close();
			}
			if(br != null) {
				br.close();
			}
			if(pw != null) {
				pw.close();
			}
		} catch (IOException e) {}
		if (theThread != null) {
			theThread.interrupt();
		}
	}
	public void windowClosing(WindowEvent e) {
		stop();
	}
	public void windowClosed(WindowEvent e) {
		ChatText.requestFocus(); // Set the focus to the Chat TextField for the user to enter a message to send
	}
	public void windowOpened(WindowEvent e) {
		ChatText.requestFocus(); // Set the focus to the Chat TextField for the user to enter a message to send
	}
	public void windowIconified(WindowEvent e) {
		ChatText.requestFocus(); // Set the focus to the Chat TextField for the user to enter a message to send
	}
	public void windowDeiconified(WindowEvent e) {
		ChatText.requestFocus(); // Set the focus to the Chat TextField for the user to enter a message to send
	}
	public void windowActivated(WindowEvent e) {
		ChatText.requestFocus(); // Set the focus to the Chat TextField for the user to enter a message to send
	}
	public void windowDeactivated(WindowEvent e) {
		ChatText.requestFocus(); // Set the focus to the Chat TextField for the user to enter a message to send
	}
}
