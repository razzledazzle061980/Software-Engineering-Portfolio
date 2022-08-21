import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class SlideShow extends JFrame {

	//Declare Variables
	private JPanel slidePane;
	private JPanel textPane;
	private JPanel buttonPane;
	private CardLayout card;
	private CardLayout cardText;
	private JButton btnPrev;
	private JButton btnNext;
	private JLabel lblSlide;
	private JLabel lblTextArea;

	/**
	 * Create the application.
	 */
	public SlideShow() throws HeadlessException {
		initComponent();
	}
	
	
	/**
	 * Initialize the contents of the frame.
	 */
	private void initComponent() {
		/* 	Initialize variables to empty objects
			Below I changed the background color, so
			it is easier to read the details of destinations
		 */
		card = new CardLayout();
		cardText = new CardLayout();
		slidePane = new JPanel();
		textPane = new JPanel();
		
		textPane.setBackground(Color.lightGray);
		textPane.setBounds(5, 470, 790, 50);
		textPane.setVisible(true);
		buttonPane = new JPanel();
		btnPrev = new JButton();
		btnNext = new JButton();
		lblSlide = new JLabel();
		lblTextArea = new JLabel();

		/*	Setup frame attributes
			Change the text on the title to
			reflect the destinations are those
			associated with Detox and Wellness
		 */
		setSize(800, 600);
		setLocationRelativeTo(null);
		setTitle("Top 5 Detox/Wellness Destinations");
		getContentPane().setLayout(new BorderLayout(10, 50));
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		//Setting the layouts for the panels
		slidePane.setLayout(card);
		textPane.setLayout(cardText);

		//logic to add each of the slides and text
		for (int i = 1; i <= 5; i++) {
			lblSlide = new JLabel();
			lblTextArea = new JLabel();
			lblSlide.setText(getResizeIcon(i));
			lblTextArea.setText(getTextDescription(i));
			slidePane.add(lblSlide, "card" + i);
			textPane.add(lblTextArea, "cardText" + i);

		}

		getContentPane().add(slidePane, BorderLayout.CENTER);
		getContentPane().add(textPane, BorderLayout.SOUTH);
		getContentPane().add(buttonPane, BorderLayout.SOUTH);

		buttonPane.setLayout(new FlowLayout(FlowLayout.CENTER, 20, 10));

		// Previous button parameters
		btnPrev.setText("Previous");
		btnPrev.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				goPrevious();
			}
		});
		buttonPane.add(btnPrev);

		// Next button parameters
		btnNext.setText("Next");
		btnNext.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				goNext();
			}
		});
		buttonPane.add(btnNext);


	}

	/**
	 * Previous Button Functionality
	 */
	private void goPrevious() {
		card.previous(slidePane);
		cardText.previous(textPane);
	}

	/**
	 * Next Button Functionality
	 */
	private void goNext() {
		card.next(slidePane);
		cardText.next(textPane);
	}

	/**
	 * Method to get the images - the changes made to this
	 * section was to add the custom images incorporated into the application
	 *
	 * Changed the width of the images to 790 and then added a 5 pixel left
	 * margin to the body so to create a uniform border.  This was done because
	 * the original file had the text offset on the x by 5 which gave it a border
	 * like effect, so I continued that effect with adding a border to the images
	 */
	private String getResizeIcon(int i) {
		String image = "";
		if (i==1){
			image = "<html><body style='margin-left: 5px'><img width='790' height='500' src='" + getClass().getResource("resources/Amanpuri_Resort_Thailand.png") + "'</body></html>";
		} else if (i==2){
			image = "<html><body style='margin-left: 5px'><img width='790' height='500' src='" + getClass().getResource("resources/Ananda_In_The_Himalayas .png") + "'</body></html>";
		} else if (i==3){
			image = "<html><body style='margin-left: 5px'><img width='790' height='500' src='" + getClass().getResource("resources/Chiva_Som_Nong_Kae_Thailand.png") + "'</body></html>";
		} else if (i==4){
			image = "<html><body style='margin-left: 5px'><img width='790' height='500' src='" + getClass().getResource("resources/Injidup_Spa_Retreat_Australia.png") + "'</body></html>";
		} else if (i==5){
			image = "<html><body style='margin-left: 5px'><img width='790' height='500' src='" + getClass().getResource("resources/The_Lodge_At_Chaa_Creek_Belize.png") + "'</body></html>";
		}
		return image;
	}
	
	/**
	 * Method to get the text values
	 *
	 * The first destination had the font size of 5 which applied to each subsequent
	 * destination so as to keep test and the layout common throughout the application
	 *
	 * Added a 5 pixel margin to the left in the body of each set of text to push it away
	 * from the bounding box of the container.
	 */
	private String getTextDescription(int i) {
		String text = ""; 
		if (i==1){
			text = "<html><body style='margin-left: 5px' ><font size='5'>#1 Top Destination - Amanpuri Resort Pansea Beach Thailand</font><br>Experience a secluded getaway in the coconut grove amidst abundant nature and fresh air.</body></html>";
		} else if (i==2){
			text = "<html><body style='margin-left: 5px' ><font size='5'>#2 Top Destination - Ananda_In_The_Himalayas Narendranagar India</font><br>Large spacious rooms and a beautiful view of the Palace, gardens and the valley below.</body></html>";
		} else if (i==3){
			text = "<html><body style='margin-left: 5px' ><font size='5'>#3 Top Destination - Chiva-Som Resort Nong KaeThailand</font><br>One of the top destinations of 2021 and offers a getaway you will soon not forget.</body></html>";
		} else if (i==4){
			text = "<html><body style='margin-left: 5px' ><font size='5'>#4 Top Destination - Injidup Spa Retreat Australia</font><br>Located on a secluded beach, relaxation full of pampering that includes massages, body treatments and gourmet meals.</body></html>";
		} else if (i==5){
			text = "<html><body style='margin-left: 5px' ><font size='5'>#5 Top Destination - The Lodge At Chaa Creek San Ignacio Belize</font><br>Located at the foothill of a mountain, trek through the jungle or visit Mayan ruins</body></html>";
		}
		return text;
	}
	
	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {

			@Override
			public void run() {
				SlideShow ss = new SlideShow();
				ss.setVisible(true);
			}
		});
	}
}