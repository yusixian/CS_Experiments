package config;

import java.io.FileInputStream;
import java.util.Properties;

public class Config {
    private  static Properties p = null;
    static {
        try {
            p = new Properties();
            p.load(new FileInputStream("config/mysql.properties"));

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    public static String getValue(String key) {
        return p.get(key).toString();
    }
}
