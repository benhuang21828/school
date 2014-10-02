/*
THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
A TUTOR OR CODE WRITTEN BY OTHER STUDENTS. Benjamin Huang.& David Seibert
*/
import java.io.*;
import java.awt.event.*;
import java.awt.*;

import javax.swing.*;
import javax.swing.filechooser.FileFilter;
//import javax.swing.filechooser.FileNameExtensionFilter;

import java.util.*;
import acm.graphics.*;
import acm.program.*;



public class FaceSpace extends Program{
	
	public Display canvas;
	private JTextField x;
	private JTextField a;
	private JTextField b;
	private JTextField c;
	private String name;
	private String status;
	private String newFriend;
	private ArrayList<user> users = new ArrayList<user>();
	public static user CurrentUser = new user();
	
	public void init(){
		resize(621,541);
		canvas = new Display();
		x = new JTextField(13);
		add(x,NORTH);
		add(new JButton("Add"), NORTH);
		add(new JButton("Delete"), NORTH);
		add(new JButton("Look Up"), NORTH);
		
		
		a = new JTextField(13);
		add(a,WEST);
		add(new JButton("Change Status"), WEST);
		
	
		b = new JTextField(13);
		add(b,WEST);
		add(new JButton("Add Friend"), WEST);
		
		c = new JTextField(13);
		add(c,WEST);
		add(new JButton("Number Of Hops"), WEST);
		
		add(canvas);
		canvas.init();
		canvas.showCurrentUser();
		canvas.showUserName();
		canvas.showUserStatus();
		canvas.DisplayFriendList();
		addActionListeners();
}
	
	
	public void actionPerformed(ActionEvent e){
		newFriend = b.getText();
		name = x.getText();
		status = a.getText();
		String connect = c.getText();
		
		if(e.getActionCommand().equals("Add")){
				user newuser = new user();
				newuser.setName(name);
				users.add(newuser);
				CurrentUser = newuser;
			
		}

		
		if(e.getActionCommand().equals("Delete")){
			
		}
		if(e.getActionCommand().equals("Look Up")){
			for (int i = 0; i<users.size(); i++){
				user finduser = users.get(i);
				String foundname = finduser.getName();
				if (name == foundname){
					name = finduser.getName();
					CurrentUser = finduser;
				}
				canvas.init();
				canvas.showCurrentUser();
				canvas.showUserName();
				canvas.showUserStatus();
				canvas.DisplayFriendList();
				canvas.
				
				/*
				 * canvas.printUser(currentUser)
				 */
			}	
		}
		if(e.getActionCommand().equals("Change Status")){
			CurrentUser.setStatus(status);
			canvas.init();
			canvas.showCurrentUser();
			canvas.showUserName();
			canvas.showUserStatus();
			canvas.DisplayFriendList();
		}
		if(e.getActionCommand().equals("Add Friend")){
		    boolean stored = false;
		    boolean alreadyfriend = false;
		    user brandnewfriend = new user();
		    if(newFriend != CurrentUser.getName()){
				for(int i = 0; i<users.size();i++){
					user existing = users.get(i);
					String newuser = existing.getName();
					if(newuser == newFriend){
						stored = true;
						brandnewfriend = existing;
					}
				}
		    }
			if(stored==true){
				for(int i=0;i<CurrentUser.showFriends().size();i++){
					user sfriend = CurrentUser.showFriends().get(i);
					if (sfriend.getName() == newFriend){
						alreadyfriend=true;
						return;
						CurrentUser.addFriend(newFriend);
					}
				}
			}
			if (alreadyfriend == false){
				CurrentUser.addFriend(brandnewfriend);
				brandnewfriend.addFriend(CurrentUser);
			}
			boolean alreadyfriend = false;
			if(newFriend != CurrentUser.getName()){
				for (int i = 0; i<users.size(); i++){
					user stored = users.get(i);
					String newuser = stored.getName();
					if(newuser == newFriend){
						user brandnewfriend = stored;
						for(int j=0; j<CurrentUser.showFriends().size(); j++){
							user sfriend = CurrentUser.showFriends().get(j);
							if (sfriend.getName() == newFriend){
								alreadyfriend = true;
							}
							
						}
						if (alreadyfriend == false){
							CurrentUser.addFriend(brandnewfriend);
							brandnewfriend.addFriend(CurrentUser);
							System.out.print(brandnewfriend.getName());
						}
					}
				}
			}
			canvas.init();
			canvas.showCurrentUser();
			canvas.showUserName();
			canvas.showUserStatus();
			canvas.DisplayFriendList();
		}

	public static void main(String[] args){
		new FaceSpace().start(args);
	}
	}	
		
