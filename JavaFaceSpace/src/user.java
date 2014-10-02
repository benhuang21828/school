import java.util.ArrayList;

public class user {
	private String name;
	private String status;
	private ArrayList<user> friends = new ArrayList<user>();
	
	public void setName(String newname){
		name = newname;
	}
	public String getName(){
		return name;
	}
	public void setStatus(String newstatus){
		status = newstatus;
	}
	public void addFriend(user newfriend){
		friends.add(newfriend);
	}
	public ArrayList<user> showFriends(){
		return friends;
	}
	public String getStatus(){
		return status;
		
	}
}