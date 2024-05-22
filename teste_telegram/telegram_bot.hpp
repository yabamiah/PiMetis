#ifndef TELEGRAM_BOT_HPP
#define TELEGRAM_BOT_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

class telegram_bot
{
    private:
        std::string url = "https://api.telegram.org/bot";
        std::string token;
        std::string chat_id;

    public:
        telegram_bot(const std::string &token);
        telegram_bot(const std::string &token, const std::string& chat_id);
        ~telegram_bot();
    
        std::string get_updates() const;
        void set_chatId(const std::string& chat_id);
        void send_text_message(const std::string& text_message);
        void send_photo_message(const std::string& image_buffer);

        // std::vector<char> read_file_to_vector(const std::string& filename) const;
    
};

#endif // TELEGRAM_BOT_HPP