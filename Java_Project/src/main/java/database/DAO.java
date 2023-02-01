package database;


import java.util.List;

public interface   DAO<T> {
    String getNameById(int id);
    String getByNume(String nume);
    int getCount();

    List<T> getByName(String name);

    List<String> getAll();

    void insert(T newObject);

   // void insertFromDiscord(Command newCommand) throws SQLException, ClassNotFoundException;

    void update(int id, T object);

    void delete(int id);
}
