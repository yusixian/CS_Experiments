package util;

import dao.Impl.UserDaoImpl;
import dao.UserDao;
import dao.entity.User;

import java.util.ArrayList;
import java.util.List;

/*
 * 项目名: Exp
 * 文件名: CheckUtil
 * 创建者: cos
 * 创建时间:2021/12/19 20:54
 * 描述: 格式检查类
 */
public class CheckerUtil {
    /**
     * 检查用户基本信息是否过长或过短
     * @param un 用户名
     * @param pw 密码
     * @return errorMessage 错误提示语句 为空则无错误
     */
    public static String userInfoCheck(String un, String pw) {
        String errorMessage = null;
        //用户名是不是符合要求
        if (un.length() == 0) {
            errorMessage = "用户名为空";
        } else if (un.length() > 15) {
            errorMessage = "用户名过长";
        }

        //密码是不是符合要求
        if (pw.length() == 0) {
            errorMessage = "密码为空";
        } else if (pw.length() > 15) {
            errorMessage = "密码过长";
        }
        return errorMessage;
    }
    /**
     * 注册界面检查：普通用户注册信息，检查合法性
     * @param un 用户名
     * @param pw 密码
     * @return errorMessage 错误提示语句
     */
    public static String userSignUpCheck(String un, String pw) {
        String errorMessage = userInfoCheck(un, pw); // 检查基本信息合法性
        // 检查该用户是否已被注册
        UserDao userDao = new UserDaoImpl();
        try {
            User sameUser = userDao.findSingleUser(un);
            if (sameUser != null) {
                errorMessage = "该用户名已被注册";
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return errorMessage;
    }
}
