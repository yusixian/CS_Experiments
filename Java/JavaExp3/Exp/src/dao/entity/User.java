package dao.entity;

public class User {
    private int id;
    private String userName;
    private String passWord;
    public User() {
        id = 0;
        userName = null;
        passWord = null;
    }
    public User(String userName, String passWord) {
        this.id = 0;
        this.userName = userName;
        this.passWord = passWord;
    }
    public User(int id, String userName, String passWord) {
        this.id = id;
        this.userName = userName;
        this.passWord = passWord;
    }

    public String getPassWord() {
        return passWord;
    }

    public void setPassWord(String passWord) {
        this.passWord = passWord;
    }

    public String getUserName() {
        return userName;
    }

    public void setUserName(String userName) {
        this.userName = userName;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    @Override
    public String toString() {
        return "User{" +
                "id=" + id +
                ", userName='" + userName + '\'' +
                ", passWord='" + passWord + '\'' +
                '}';
    }
}
