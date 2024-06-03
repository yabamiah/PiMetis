#ifndef TELEGRAM_BOT_HPP
#define TELEGRAM_BOT_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>
#include <ctime>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

class telegram_bot
{
    private:
        std::string url = "https://api.telegram.org/bot";
        std::string link_server_path = "../servidor_link.txt";
        std::string server_link;
        std::string token;
        std::string chat_id;

    public:
        telegram_bot(const std::string &token);
        telegram_bot(const std::string &token, const std::string& chat_id);
        ~telegram_bot();
    
        std::string get_updates() const;
        void set_chatId(const std::string& chat_id);
        void send_text_message(const std::string& text_message);
        void send_photo_message(const std::string& photo_path);
        std::string read_file_server() const;
        bool fileExists(const std::string& filename) const;

        void listen_commands();
        void command_handler(std::string command, nlohmann::json response);
        std::string read_file_to_vector(const std::string& filename) const;
    
};

#endif // TELEGRAM_BOT_HPP