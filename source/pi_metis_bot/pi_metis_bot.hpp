#ifndef PI_METIS_BOT_HPP
#define PI_METIS_BOT_HPP

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
        std::string link_server_path = "/home/yaba/Sandbox/PiMetis/source/servidor_link.txt";
        std::string image_path;
        std::string server_link;
        std::string token;
        std::string chat_id;

    public:
        telegram_bot( const std::string &token );
        telegram_bot( const std::string &token, const std::string& chat_id );
        ~telegram_bot();
    
        std::string get_updates() const;
        void set_chatId( const std::string& chat_id );
        void send_text_message( const std::string& text_message );
        void send_warning( const std::string& message_, const std::string& photo );
        void send_photo_message( const std::string& image_path_ );
        std::string read_file_server() const;
        bool fileExists( const std::string& filename ) const;

        void set_image( const std::string& image_path );
        std::string get_image() const;

    private:
        void listen_commands();
        void command_handler( std::string command, nlohmann::json response );
        std::string read_file_to_vector( const std::string& filename ) const;
        std::string get_time() const;
};

#endif // PI_METIS_BOT_HPP
