package service;

import dao.Impl.OrderDaoImpl;
import dao.Impl.UserDaoImpl;
import dao.UserDao;
import dao.entity.Order;
import dao.entity.User;

import javax.jws.soap.SOAPBinding;
import java.util.Date;
import java.util.List;

public class UserService {
    public UserDaoImpl userDao;
    public UserService() {
        userDao = new UserDaoImpl();
    }
    public boolean isRegisterOK(String userName, String passWord) {
        User nowUser = userDao.findSingleUser(userName);
//        System.out.println(userName + ", " + passWord);
        if(nowUser != null)
            return false;
        User newUser = new User(userName, passWord);
        userDao.insert(newUser);
        return true;
    }
    public boolean isLoginOK(String userName, String passWord) {
        User nowUser = userDao.findSingleUser(userName);
//        System.out.println(userName + ", " + passWord);
        if(nowUser != null && nowUser.getPassWord().equals(passWord))
            return true;
        else return false;
    }
    public static void printAll(List<User> list) {
        System.out.println("-----------以下为所有用户-----------");
        for(int i = 0; i < list.size(); ++i) {
            System.out.println(list.get(i));
        }
    }

    public static void main(String []args) throws Exception  {
        UserService userService = new UserService();
        User user1 = new User(1, "test", "123456");
        System.out.println("-----------插入"+user1.toString()+"-----------");
        userService.userDao.insert(user1);
        User user2 = new User(2, "wang", "qwerty");
        System.out.println("-----------插入"+user2.toString()+"-----------");
        userService.userDao.insert(user2);
        List<User> list = userService.userDao.findAll();

        printAll(list);

//        System.out.println("-----------更新"+user1.toString()+"-----------");
//        user1.setPassWord("1234");
//        userDao.update(user1.getUserName(), user1);
//        System.out.println("----------------------");
//
//        list = userDao.findAll();
//        printAll(list);
    }
}
