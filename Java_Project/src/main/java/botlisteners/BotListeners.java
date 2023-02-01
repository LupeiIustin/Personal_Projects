package botlisteners;

import database.Command;
import database.CommandDAO;
import database.JDBCConnection;
import net.dv8tion.jda.api.entities.*;
import net.dv8tion.jda.api.events.GenericEvent;
import net.dv8tion.jda.api.events.channel.ChannelCreateEvent;
import net.dv8tion.jda.api.events.channel.ChannelDeleteEvent;
import net.dv8tion.jda.api.events.message.MessageReceivedEvent;
import net.dv8tion.jda.api.hooks.ListenerAdapter;
import org.jetbrains.annotations.NotNull;

import java.sql.SQLException;
import java.util.List;

public class BotListeners extends ListenerAdapter {


    @Override
    public void onMessageReceived(@NotNull MessageReceivedEvent event) {
        // TextChannel general = event.getGuild().getTextChannelById(980164824157806755L);// 980164824157806755
        TextChannel general = event.getTextChannel();
        Guild guild = event.getGuild();
        List<Role> roles = guild.getRolesByName("createCommand", true);
        Role role = guild.getRoleById(984518701325905960L);


        List<Member> members = guild.getMembersWithRoles(role);
        /*
        if (!event.getAuthor().isBot()){
            general.sendMessage(roles.toString() + "-----roles---------").queue();
            general.sendMessage(members.toString() + "-------members wiht roles-----").queue();
            general.sendMessage(role.toString() + "-----").queue();
         }

         */
        Member member1 = event.getMember();
        boolean isMember = false;
        for (Member m : members) {
            if(member1.equals(m)) {isMember= true;}
            }
        if(!event.getAuthor().isBot()) {
            if (isMember == true && !event.getAuthor().isBot()) {
                //general.sendMessage("te-am gasit").queue();
                boolean isMessage = event.getMessage() != null;

                if (!event.getAuthor().isBot() && isMessage) {
                    String id = event.getAuthor().getId();
                    String s1 = (event.getMessage().getContentRaw());
                    String words[] = s1.split(",");//splits the string based on string

                    int count = words.length;
                    if (words.length == 3) {
                        try {
                            CommandDAO commandDAO = new CommandDAO(JDBCConnection.getInstance().getConnection());
                            if (words[0].equals("create")) {

                                String createdBy = event.getAuthor().getName();
                                int id2 = commandDAO.getCount();
                                String name = words[1];
                                String description = words[2];
                                Command command = new Command(createdBy, id2, name, description);
                                commandDAO.insert(command);
                                general.sendMessage("comanda corecta, am inserat: " + createdBy + ", "+ words[1] + ", " + words[2]).queue();
                            } else {
                                general.sendMessage("comanda corecta este <create>").queue();
                            }
                        } catch (SQLException e) {
                            e.printStackTrace();
                        } catch (ClassNotFoundException e) {
                            e.printStackTrace();
                        }

                    } else {
                        general.sendMessage("comanda nu respecta formatul de 3 parametrii").queue();
                    }
                }
            } else {
                general.sendMessage("Nu ai permisiunea sa creezi o comanda noua").queue();
            }
        }


    }

    @Override
    public void onChannelDelete(@NotNull ChannelDeleteEvent event) {
        String channelName = event.getChannel().getName();
        TextChannel general = event.getGuild().getTextChannelById(980521479701688350L);
           // general.getManager().getChannel();
        if (general != null) {
            general.sendMessage("The channel: \"" + channelName + "\" was deleted").queue();
        }
    }

    @Override
    public void onChannelCreate(@NotNull ChannelCreateEvent event) {
        String channelName = event.getChannel().getName();
        TextChannel general = event.getGuild().getTextChannelById(980521479701688350L);

        if (general != null) {
            general.sendMessage("The channel: \"" + channelName + "\" was created").queue();
        }
    }

    @Override
    public void onGenericEvent(@NotNull GenericEvent event) {
        if (event instanceof MessageReceivedEvent) {

            MessageReceivedEvent messageReceivedEvent = (MessageReceivedEvent) event;
            if (messageReceivedEvent.getMessage().getType().equals(MessageType.GUILD_MEMBER_JOIN)) {
                User user = messageReceivedEvent.getMember().getUser();
                user.openPrivateChannel().
                        queue(privateChannel -> {
                            // event.reply("Pong!").setEphemeral(true).queue();
                            privateChannel.sendMessage("  Bine ai venit " + user.getName()+", pentru a vedea comenzile " +
                                            "disponibile pentru a afla informatii despre diferiti  " +
                                            "algoritmi tasteaza /help pe canalul dedicat MinaKnowsEverythingAboutAlgorithms ! ")
                                    .queue();
                        });
                //long authorID =messageReceivedEvent.getAuthor().getIdLong();
                //Member member = messageReceivedEvent.getMember(authorID);
            }
        }
    /*
    @Override
    public void onGuildJoin(GuildJoinEvent event)
    {
        JDA api = event.getJDA();
        System.out.println("sdfghjkuuuuu");
        /*User user = api.getUserById(userId); // Acquire a reference to the User instance through the id
        user.openPrivateChannel().queue((channel) ->
        {
            // Send a private message to the user
            channel.sendMessageFormat("I have joined a new guild: **%s**", event.getGuild().getName()).queue();
        });*/
    /*
    @Override
    public void onGuildMemberJoin(@NotNull GuildMemberJoinEvent event) {
        System.out.println("sdfghjkl;'");
         User user = event.getMember().getUser();
        user.openPrivateChannel().queue((channel) ->
        {
            // Send a private message to the user
            channel.sendMessageFormat("I have joined a new guild: **%s**", event.getGuild().getName()).queue();
        });
        user.openPrivateChannel().
                queue(privateChannel -> {
                    // event.reply("Pong!").setEphemeral(true).queue();
                    privateChannel.sendMessage("Dijkstra's algorithm is an algorithm for finding the shortest paths between nodes in a graph, which may represent, for example, road networks.")
                            .queue();});
    }

 /*   @Override
    public void onGuildJoin(GuildJoinEvent event) {
        JDA api = event.getJDA();
        User user = api.getSelfUser(); // Acquire a reference to the User instance through the id
        user.openPrivateChannel().queue((channel) ->
        {
            // Send a private message to the user
            channel.sendMessageFormat("I have joined a new guild: **%s**", event.getGuild().getName()).queue();
        });
    }
*/

    /*
    @Override
    public void onGenericGuild(@NotNull GenericGuildEvent event) {
        System.out.println("a intrat");
    }

 */
    }}

