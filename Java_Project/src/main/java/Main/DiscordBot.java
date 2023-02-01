package Main;

import botlisteners.BotListeners;
import database.Command;
import database.CommandDAO;
import database.DAO;
import database.JDBCConnection;
import net.dv8tion.jda.api.JDA;
import net.dv8tion.jda.api.JDABuilder;
import net.dv8tion.jda.api.entities.Activity;
import botcommands.BotCommands;
import org.apache.ibatis.jdbc.ScriptRunner;

import javax.security.auth.login.LoginException;
import java.beans.IntrospectionException;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.Reader;
import java.sql.SQLException;

public class DiscordBot  {


    public static JDA bot;
    public static void main(String[] args) throws LoginException, IntrospectionException, SQLException, ClassNotFoundException {

         bot = (JDA) JDABuilder.createDefault("OTgwMDUyMjYwMzAwMTQ4Nzc2.GelgPf.2viin61Z1KLGi5iaCdYvDwF0_wUowQWc04CBsU")
              //  .enableIntents(GatewayIntent.GUILD_MEMBERS)
               // .disableCache(CacheFlag.MEMBER_OVERRIDES)
                .setActivity(Activity.watching("Captcha"))
                .addEventListeners(new BotCommands())
                .addEventListeners(new BotListeners())
              // .addEventListeners(new GuildMemberJoin())
              //.enableIntents(GatewayIntent.GUILD_MEMBERS)
                .build();

        try {
            ScriptRunner scriptRunner = new ScriptRunner(JDBCConnection.getInstance().getConnection());
            Reader reader = new BufferedReader(new FileReader("C:\\Users\\User\\Desktop\\Lupei_Iustin-Programare-Avansata\\Proiect\\commands.sql"));

            scriptRunner.runScript(reader);

            DAO<Command> commandManager = new CommandDAO(JDBCConnection.getInstance().getConnection());

           // InformationTool importer = new InformationTool("C:\\Users\\User\\Desktop\\DBTest\\commands.csv");
            //   importer.AddInformation(1);

        } catch (SQLException | ClassNotFoundException |  IOException exception) {
            exception.printStackTrace();
        }

        CommandDAO commandDAO = new CommandDAO(JDBCConnection.getInstance().getConnection());
        System.out.println("------commandDAO.getDescription--------");
        System.out.println(commandDAO.getDescription("dijkstra" ));
        System.out.println("------commandDAO.getByNume--------");
        System.out.println(commandDAO.getByNume("dijkstra"));
        System.out.println("------commandDAO.getAll--------");
        System.out.println(commandDAO.getAll());
        System.out.println("----commandDAO.getCount-----");
        System.out.println("avem " + commandDAO.getCount() +" comenzi");
        System.out.println("----commandDAO.getById-----");


        for (int i = 1; i <= commandDAO.getCount(); i++) {
            bot.upsertCommand(commandDAO.getNameById(i), "algorithm").queue();
            System.out.println("/" + commandDAO.getNameById(i));

        }



       // Guild guild = bot.getGuildById(980164824157806755L);
/*
        Commands commands = new Commands("dijkstra","algorithm");
        bot.upsertCommand("ping", "test your ping").queue();
        bot.upsertCommand("dijkstra", "algorithm").queue();
        bot.upsertCommand("menger", "algorithm").queue();
        bot.upsertCommand("help", "commands").queue();

        Command command= new Command(1, "mama","ce bun esti");
        CommandDAO commandDAO = new CommandDAO(JDBCConnection.getInstance().getConnection());
        commandDAO.insert(command);

      */

        //commandDAO.getById(2);



    }
}
