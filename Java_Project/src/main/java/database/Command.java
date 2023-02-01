package database;


import java.util.StringJoiner;

public class Command {
    private final String createdBy;
    private final int id;
    private final String name;
    private final String description;


    public Command(String createdBy, int id, String name, String description) {
        this.createdBy = createdBy;
        this.id = id;
        this.name = name;
        this.description = description;


    }

    public String getCreatedBy() {return createdBy;}

    public int getId() {
        return id +1;
    }

    public String getName() {
        return name;
    }

    public String getDescription() {
        return description;
    }

    @Override
    public String toString() {
        return new StringJoiner(", ", Command.class.getSimpleName() + "[", "]")
                .add("createdBy='" + createdBy + "'")
                .add("id=" + id)
                .add("name='" + name + "'")
                .add("description='" + description + "'")
                .toString();
    }
}
