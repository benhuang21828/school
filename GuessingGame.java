package hw1;
//THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING CODE WRITTEN BY OTHER STUDENTS. BENJAMIN HUANG.

import java.sql.Array;
import java.util.ArrayList;
import java.util.Random;
import javax.swing.JOptionPane;

public class GuessingGame {

	// fill in code here
	// define data members
	private int guess;
	private int totalgues;
	private ArrayList<Integer> numbs;
	

	public GuessingGame ( ) {
		// fill in code here
		// initialization
		totalgues = 0;
		numbs = new ArrayList<Integer>();
		for(int i = 0; i < 10000; i++){
			numbs.add(i);
		}
		
	}

	public int myGuessIs() {
		// fill in code here
		
		int NumbsSize = numbs.size();
		boolean xsize;
		if(NumbsSize > 0 ){
			xsize = true;
		}
		else{
			xsize = false;
		}
		if(xsize == true){
			int z = (int)(Math.random()*NumbsSize);
			guess = numbs.get(z);
			totalgues++;
			numbs.remove(z);
			return guess;
		}
		else{
			return -1;
		}
	}
	
	public int totalNumGuesses() {
		// fill in code here
		// this should return the total number of guesses taken
		return totalgues;

	}
 
	public void updateMyGuess(int nmatches) {
		// fill in code here
		// update the guess based on the number of matching digits claimed by the user
		for(int i = 0; i < numbs.size(); i++){
			if(numbofmatches(nmatches, numbs.get(i)) >= 1) {
				System.out.println(numbs.get(i));
				numbs.remove(i);
				i = i -1;
			}
		}
	}
	
	public int numbofmatches(int y, int x){
		int one = guess/1000;
		int two = (guess%1000)/100;
		int three = (guess%100)/10; 
		int four = (guess%10);
		int oneDashone = x/1000;
		int twoDashone = (x%1000)/100;
		int threeDashone = (x%100)/10; 
		int fourDashone = (x%10); 
		int DaNumbsOfMatches = 0;
		if(one == oneDashone){
			DaNumbsOfMatches ++;
		}
		if(two == twoDashone){
			DaNumbsOfMatches ++;
		}
		if(three == threeDashone){
			DaNumbsOfMatches ++;
		}
		if(four == fourDashone){
			DaNumbsOfMatches ++;
		}
		int Jim = 0;
		if(y == 0 && DaNumbsOfMatches > 0){
			Jim++;
		}
		else if(y > DaNumbsOfMatches){
			Jim++;
		}
		return Jim;
		
		
		
	}
	
	// fill in code here (optional)
	// feel free to add more methods as needed
	
	// you shouldn't need to change the main function
	public static void main(String[] args) {

		GuessingGame gamer = new GuessingGame( );
  
		JOptionPane.showMessageDialog(null, "Think of a number between 1000 and 9999.\n Click OK when you are ready...", "Let's play a game", JOptionPane.INFORMATION_MESSAGE);
		int numMatches = 0;
		int myguess = 0;
		
		do {
			myguess = gamer.myGuessIs();
			if (myguess == -1) {
				JOptionPane.showMessageDialog(null, "I don't think your number exists.\n I could be wrong though...", "Mistake", JOptionPane.INFORMATION_MESSAGE);
				System.exit(0);
			}
			String userInput = JOptionPane.showInputDialog("I guess your number is " + myguess + ". How many digits did I guess correctly?");
			// quit if the user input nothing (such as pressed ESC)
			if (userInput == null)
				System.exit(0);
			// parse user input, pop up a warning message if the input is invalid
			try {
				numMatches = Integer.parseInt(userInput.trim());
			}
			catch(Exception exception) {
				JOptionPane.showMessageDialog(null, "Your input is invalid. Please enter a number between 0 and 4", "Warning", JOptionPane.WARNING_MESSAGE);
				numMatches = 0;
			}
			// the number of matches must be between 0 and 4
			if (numMatches < 0 || numMatches > 4) {
				JOptionPane.showMessageDialog(null, "Your input is invalid. Please enter a number between 0 and 4", "Warning", JOptionPane.WARNING_MESSAGE);
				numMatches = 0;
			}
			if (numMatches == 4)
				break;
			// update based on user input
			gamer.updateMyGuess(numMatches);
			
		} while (true);
		
		// the game ends when the user says all 4 digits are correct
		System.out.println("Aha, I got it, your number is " + myguess + ".");
		System.out.println("I did it in " + gamer.totalNumGuesses() + " turns.");
	}
}
