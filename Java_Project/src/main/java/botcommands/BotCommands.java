package botcommands;

import database.CommandDAO;
import database.JDBCConnection;
import net.dv8tion.jda.api.JDA;
import net.dv8tion.jda.api.entities.Member;
import net.dv8tion.jda.api.entities.Message;
import net.dv8tion.jda.api.events.ExceptionEvent;
import net.dv8tion.jda.api.events.guild.GuildJoinEvent;
import net.dv8tion.jda.api.events.interaction.command.SlashCommandInteractionEvent;
import net.dv8tion.jda.api.events.message.MessageReceivedEvent;
import net.dv8tion.jda.api.hooks.ListenerAdapter;
import org.jetbrains.annotations.NotNull;

import java.sql.SQLException;

public class BotCommands extends ListenerAdapter{

    CommandDAO commandDAO = new CommandDAO(JDBCConnection.getInstance().getConnection());

    public BotCommands() throws SQLException, ClassNotFoundException {
    }


    @Override
    public void onSlashCommandInteraction(@NotNull SlashCommandInteractionEvent event) {

        if (event.getName().equals("ping")) {
            long time = System.currentTimeMillis();
            event.reply("Pong!").setEphemeral(true) // reply or acknowledge
                    .flatMap(v ->
                            event.getHook().editOriginalFormat("Pong: %d ms", System.currentTimeMillis() - time) // then edit original
                    ).queue(); // Queue both reply and edit
        }else
        if (event.getName().equals("help")) {
            event.reply("sent").queue();
            Member member = event.getMember();
            if (member != null) {
                   String sir = String.valueOf(commandDAO.getAll());
                member.getUser().openPrivateChannel().
                        queue(privateChannel -> {
                            // event.reply("Pong!").setEphemeral(true).queue();
                            privateChannel.sendMessage( sir)
                                    .queue();
                        });
            }
        }
        else
            if (event.getName().equals(commandDAO.getByNume(event.getName()))) {
                 event.reply("sent").queue();
                 Member member = event.getMember();

                   String mesaj= commandDAO.getDescription(event.getName());
                    if (member != null) {
                        member.getUser().openPrivateChannel().
                                queue(privateChannel -> {
                                    // event.reply("Pong!").setEphemeral(true).queue();
                                    privateChannel.sendMessage(mesaj)
                                            .queue();
                                });
                    }

        } } }
         /*   else
                if (event.getName().equals("menger")){
                    event.reply("sent").queue();
                    Member member = event.getMember();
                    if (member != null) {
                        member.getUser().openPrivateChannel().
                                queue(privateChannel -> {
                                    // event.reply("Pong!").setEphemeral(true).queue();
                                    privateChannel.sendMessage("Teorema lui Menger  -  Fie G un grafic finit nedirecționat și s și t două vârfuri distincte. Numărul minim de muchii de eliminat pentru a deconecta s și t este egal cu numărul maxim de căi disjuncte de margine ale G care conectează s și t ."
                                            + "  https://profs.info.uaic.ro/~olariu/curent/AG/files/agr5.pdf ")
                                            .queue();
                                      });
                    }
                }

    }
}

/*

    try {
                    CommandDAO commandDAO = new CommandDAO(JDBCConnection.getInstance().getConnection());
                   String mesaj= commandDAO.getDescription(event.getName() );
                    if (member != null) {
                        member.getUser().openPrivateChannel().
                                queue(privateChannel -> {
                                    // event.reply("Pong!").setEphemeral(true).queue();
                                    privateChannel.sendMessage(mesaj)
                                            .queue();
                                });
                    }
                } catch (SQLException e) {
                    e.printStackTrace();
                } catch (ClassNotFoundException e) {
                    e.printStackTrace();
                }

           */
