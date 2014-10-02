import java.awt.*;
import acm.graphics.*;
public class Display extends GCanvas{
	
	public GLabel UserName;
	public GLabel UserStatus;
	public GLabel CurrentUser;
	public GLabel FriendList = new GLabel("Friends List:",300,60);
	public GLabel list = new GLabel("",50,300);
	
	public void init(){
	GRect abcd = new GRect(0,0,500,500);
		abcd.setFilled(true);
		abcd.setFillColor(Color.white);
		add(abcd);
	
	}	
	public void showUserName(){	
		if(FaceSpace.CurrentUser.getName() == null){
			UserName = new GLabel(" ",50,60);
		}
		else{ UserName = new GLabel(FaceSpace.CurrentUser.getName(),50,60);	}
		UserName.setFont("Dialog-12");
		UserName.setColor(Color.BLUE);
		add(UserName);
	}
		
	public void showUserStatus(){
		if(FaceSpace.CurrentUser.getStatus().equals(null)){
			UserStatus = new GLabel("Status: ",50,360);
		}
		else{	UserStatus = new GLabel("Status: "+FaceSpace.CurrentUser.getStatus(),50,360);	}
		UserStatus.setFont("Dialog-12");
		UserStatus.setColor(Color.BLACK);
		add(UserStatus);
	}	
	
	public void showCurrentUser(){
		if(FaceSpace.CurrentUser.getName().equals(null)){
			CurrentUser = new GLabel("Displaying ..." + "None",300,400);
		}
		else{ CurrentUser = new GLabel("Displaying..."+ FaceSpace.CurrentUser.getName(),300,400); }
		CurrentUser.setFont("Dialog-12");
		CurrentUser.setColor(Color.BLACK);
		add(CurrentUser);
	}
	
	public void DisplayFriendList(){
		FriendList.setFont("Dialog-12");
		FriendList.setColor(Color.BLACK);
		add(FriendList);
		
		if(FaceSpace.CurrentUser.getName() != null){
			ShowFriendsList();
		}
	}
	
	public void ShowFriendsList(){
		int LabelLocation = 60;
		if(FaceSpace.CurrentUser.showFriends().size() != 0){
			for(int i=0; i<FaceSpace.CurrentUser.showFriends().size();i++){
				
				if(FaceSpace.CurrentUser.showFriends().get(i).getName().equals(0)){
					list.setFont("Dialog-12");
					list.setColor(Color.BLACK);
					list = new GLabel(FaceSpace.CurrentUser.showFriends().get(i).getName(),300,LabelLocation);
					add(list);
					System.out.println(FaceSpace.CurrentUser.showFriends().get(i).getName());
				}
				else{
					list.setFont("Dialog-12");
					list.setColor(Color.BLACK);
					list =new GLabel(" ", LabelLocation, 300);
					add(list);
					System.out.println(FaceSpace.CurrentUser.showFriends().get(i).getName());
				}
				LabelLocation = LabelLocation + 15;
			}
		}
	}

	
}
