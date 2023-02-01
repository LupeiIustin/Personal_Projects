package database;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class JDBCConnection {
    private static JDBCConnection jdbcConnection;

    private JDBCConnection(){}

    public static JDBCConnection getInstance()
    {
        if(jdbcConnection == null)
        {
            jdbcConnection = new JDBCConnection();
        }
        return jdbcConnection;
    }

    public Connection getConnection() throws SQLException, ClassNotFoundException {
        Connection connection;
        Class.forName("oracle.jdbc.driver.OracleDriver");
        connection = DriverManager.getConnection("jdbc:oracle:thin:@localhost:1521:XE","student","STUDENT");

        return connection;
    }
}
