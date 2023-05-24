#define FMT_HEADER_ONLY
#include <dpp/dpp.h>
#include <dpp/colors.h>
#include <iostream>
#include <fstream>
#include <string>
#include "include/json.hpp"
#include "include/fmt/include/fmt/color.h"

using json = nlohmann::json;

int main() {
    std::string botToken;
    std::ifstream myBotToken("ids/token.txt");
    if(myBotToken.is_open()){
        myBotToken >> botToken;
    }

    std::string guildToken;
    std::ifstream myGuildToken("ids/snowflake.txt");
    if(myGuildToken.is_open()){
        myGuildToken >> guildToken;
    }

    std::ifstream myJson("data/bank.json");
    json bankJson = json::parse(myJson);
    json tabOne = bankJson["BankTabs"]["One"];
    json tabTwo = bankJson["BankTabs"]["Two"];

    const std::string BOT_TOKEN = botToken;
    uint64_t intents = dpp::i_default_intents | dpp::i_message_content;
    dpp::cluster bot(BOT_TOKEN, intents);

    bot.on_log(dpp::utility::cout_logger());

    bot.on_message_create([&bot, tabOne, tabTwo](const dpp::message_create_t& event) {
         if (event.msg.content == "!bank") {
            // First Bank tab.
            dpp::embed embed = dpp::embed().set_color(dpp::colors::cinnabar);     
            embed.set_title("Bank Tab One");

            for (auto it = tabOne.begin(); it != tabOne.end(); ++it){
                std::string formattedValue = fmt::format("```ansi\n\u001b[0;31m{}\n```",static_cast<std::string>(it.value()));
                embed.add_field(it.key(), formattedValue, true);
            }

            // Second Bank Tab.
            dpp::embed embed2 = dpp::embed().set_color(dpp::colors::jazzberry_jam);
            embed2.set_title("Bank Tab Two");

            for (auto it = tabTwo.begin(); it != tabTwo.end(); ++it){
                std::string formattedValue = fmt::format("```ansi\n\u001b[0;34m{}\n```",static_cast<std::string>(it.value()));
                embed2.add_field(it.key(), formattedValue, true);
            }

            dpp::message msg(event.msg.channel_id, embed);
            dpp::message msg2(event.msg.channel_id, embed2);
            bot.message_create(msg);
            bot.message_create(msg2);
        }
    });

    bot.on_ready([&bot, guildToken](const dpp::ready_t& event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            bot.guild_command_create(dpp::slashcommand("test", "Test!", bot.me.id), guildToken);
        }
    });

    bot.start(dpp::st_wait);
}