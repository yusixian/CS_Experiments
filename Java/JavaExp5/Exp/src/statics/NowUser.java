package statics;


import dao.entity.User;

/*
 * 项目名: Exp_1.iml
 * 文件名: NowUser
 * 创建者: cos
 * 创建时间:2021/12/19 17:51
 * 描述: 全局用户类 当前用户
 */
public class NowUser {
    public static User nowUser;
    public static void initNowUser(User user) {
        nowUser = user;
    }
}
