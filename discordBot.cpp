#include <dpp/dpp.h>
#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp"

int main() {
    using json = nlohmann::json;
    std::string botToken;
    std::ifstream myBotToken("token.txt");
    std::ifstream myJson("bank.json");
    json bank_json = json::parse(myJson);
    if(myBotToken.is_open()){
        myBotToken >> botToken;
    }

    // Just testing to see how nlohmann works - TODO
    std::cout << bank_json["Bank"]["BankTabs"]["One"].dump(1) << std::endl;

    const std::string BOT_TOKEN = botToken;
    uint64_t intents = dpp::i_default_intents | dpp::i_message_content;
    dpp::cluster bot(BOT_TOKEN, intents);

    bot.on_log(dpp::utility::cout_logger());

    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
        if (event.command.get_command_name() == "ping") {
            event.reply("Pong!");
        }
    });

	    bot.on_message_create([&bot](const dpp::message_create_t &event) {
        if (event.msg.content == "!file") {
            // create a message
            dpp::message msg(event.msg.channel_id, "uploading_image");
 
            // attach the image to the message
            msg.add_file("cheese.jpg", dpp::utility::read_file("/home/linuxdev/Documents/cheese.jpg"));
 
            dpp::embed embed;
            embed.set_image("attachment://cheese.jpg"); // reference to the attached file
            msg.add_embed(embed);
 
            // send the message
            bot.message_create(msg);
        }
    });

    bot.on_ready([&bot](const dpp::ready_t& event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            bot.global_command_create(dpp::slashcommand("ping", "Ping pong!", bot.me.id));
        }
    });

    bot.start(dpp::st_wait);
}