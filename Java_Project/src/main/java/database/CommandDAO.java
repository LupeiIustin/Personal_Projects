package database;




import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class CommandDAO implements DAO<Command>{
    private final Connection connection;

    public CommandDAO(Connection connection)
    {
        this.connection = connection;
    }
    
    public String getDescription(String name)
    {
        ResultSet results;
        String toReturn = null;
        try(PreparedStatement prepared = connection.prepareStatement("SELECT description FROM commands WHERE name=?"))
        {
            prepared.setString(1,name);
            results = prepared.executeQuery();
            while(results.next())
            {
              //  int id = results.getInt(1);
               // String name1 = results.getString(2);
                String description = results.getString(1);


                toReturn = description;
            }
            results.close();
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }

        return toReturn;
    }

    @Override
    public String getNameById(int id)
    {
        ResultSet results;
     //   Command toReturn = null;
        String name1= null;
        try(PreparedStatement prepared = connection.prepareStatement("SELECT name FROM commands WHERE id=?"))
        {
            prepared.setInt(1,id);
            results = prepared.executeQuery();
            while(results.next())
            {
               // int id1 = results.getInt(1);
                String name = results.getString(1);
               // String description = results.getString(3);
                name1 = name;


              //  toReturn = new Command(id1,name,description);
            }
            results.close();
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }

        return name1;
    }

    @Override
    public String getByNume(String name) {
        ResultSet results;

        String name1= null;
        try(PreparedStatement prepared = connection.prepareStatement("SELECT name FROM commands WHERE name=?"))
        {
            prepared.setString(1,name);
            results = prepared.executeQuery();
            while(results.next())
            {
                String name2 = results.getString(1);
                name1 = name2;

            }
            results.close();
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }

        return name1;
    }

    @Override
    public int getCount() {
        ResultSet results;
       // Command toReturn = null;
       int count = 0;
        try(PreparedStatement prepared = connection.prepareStatement("SELECT count(name) FROM commands"))
        {
          //  prepared.setInt(1,count);
            results = prepared.executeQuery();
            while(results.next())
            {
                 count = results.getInt(1);
                // String name = results.getString(1);
                // String description = results.getString(3);
                // description1 = name;
                // toReturn = new Command(id1,name,description);
            }
            results.close();
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }

        return count;
    }

    @Override
    public List<Command> getByName(String name)
    {
        ResultSet results;
        List<Command> toReturn = new ArrayList<>();
        try(PreparedStatement prepared = connection.prepareStatement("SELECT * FROM commands WHERE name=?"))
        {
            prepared.setString(1,name);
            results = prepared.executeQuery();
            while(results.next())
            {
                String createBy = results.getString(1);
                int id = results.getInt(2);
                String name1 = results.getString(3);
                String description = results.getString(4);


                toReturn.add(new Command(createBy,id,name,description));
            }
            results.close();
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }

        return toReturn;
    }

    @Override
    public List<String> getAll()
    {
        ResultSet results;
        List<String> toReturn = new ArrayList<>();
        try(PreparedStatement prepared = connection.prepareStatement("SELECT * FROM commands"))
        {
            results = prepared.executeQuery();
            while(results.next())
            {   String createdBy = results.getString(1);
                int id = results.getInt(2);
                String name = results.getString(3);
                String description = results.getString(4);

                toReturn.add("/" + name);
            }
            results.close();
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }

        return toReturn;
    }

    @Override
    public void insert(Command newCommand)
    {
        try (PreparedStatement prepared = connection.prepareStatement("INSERT INTO commands VALUES( ?, ?, ?, ?)")) {
            prepared.setString(1,newCommand.getCreatedBy());
            prepared.setInt(2, newCommand.getId());
            prepared.setString(3, newCommand.getName());
            prepared.setString(4, newCommand.getDescription());

            prepared.executeUpdate();
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }

    }

    @Override
    public void update(int id,Command newCommand)
    {
        try(PreparedStatement prepared = connection.prepareStatement("UPDATE commands SET id=?, name=?, description=? " +
                "WHERE id= ?"))
        {
            prepared.setInt(1, id);
            prepared.setString(2, newCommand.getName());
            prepared.setString(3, newCommand.getDescription());

            int rowsUpdated = prepared.executeUpdate();
            if(rowsUpdated == 0)
            {
                System.out.println("No rows updated!");
            }
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }

    }

    @Override
    public void delete(int id)
    {
        try(PreparedStatement prepared = connection.prepareStatement("DELETE from commands WHERE id= ?"))
        {
            prepared.setInt(1, id);

            int rowsUpdated = prepared.executeUpdate();
            if(rowsUpdated == 0)
            {
                System.out.println("No rows updated!");
            }
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }
    }
}
