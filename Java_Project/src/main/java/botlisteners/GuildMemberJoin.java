package botlisteners;

import net.dv8tion.jda.api.entities.MessageType;
import net.dv8tion.jda.api.entities.User;
import net.dv8tion.jda.api.events.guild.member.GuildMemberJoinEvent;
import net.dv8tion.jda.api.events.message.MessageReceivedEvent;
import net.dv8tion.jda.api.hooks.ListenerAdapter;
import org.jetbrains.annotations.NotNull;

public class GuildMemberJoin extends ListenerAdapter {
    @Override
    public void onGuildMemberJoin(@NotNull GuildMemberJoinEvent event) {
        System.out.println("----------------------------------");
                User user = event.getMember().getUser();
                user.openPrivateChannel().
                        queue(privateChannel -> {
                            // event.reply("Pong!").setEphemeral(true).queue();
                            privateChannel.sendMessage("  Bine ai venit " + user.getName()+", pentru a vedea comenzile " +
                                            "disponibile pentru a afla informatii despre diferiti  " +
                                            "algoritmi tasteaza /help pe canalul dedicat MinaKnowsEverythingAboutAlgorithms ! ")
                                    .queue();
                        });

            }
        }


