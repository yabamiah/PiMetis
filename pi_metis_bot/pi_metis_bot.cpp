#include "pi_metis_bot.hpp"

telegram_bot::telegram_bot(const std::string &token) 
    : token(token), image_path("/home/yaba/Sandbox/PiMetis/teste_ia/person.jpg")
{
    this->url = this->url + token;

    this->server_link = read_file_server();

    std::thread bot_listenning(&telegram_bot::listen_commands, this);

    bot_listenning.detach();
}
 
telegram_bot::telegram_bot(const std::string &token, const std::string& chat_id) 
    : token(token), chat_id(chat_id), image_path("/home/yaba/Sandbox/PiMetis/teste_ia/person.jpg")
{
    this->url = this->url + token;
    
    std::thread bot_listenning(&telegram_bot::listen_commands, this);

    bot_listenning.detach();
}

telegram_bot::~telegram_bot()
{
}

void telegram_bot::set_chatId(const std::string& chat_id)
{
    this->chat_id = chat_id;
}

std::string telegram_bot::get_updates() const
{
    std::string gp = "/getUpdates", chatId;
    
    cpr::Response r = cpr::Get(cpr::Url{this->url + gp});

    if (r.status_code == 200)
    {
        try 
        {
            nlohmann::json response = nlohmann::json::parse(r.text);

            if (response["ok"].get<bool>())
            {
                 for (const auto& update : response["result"]) {
                    if (update.contains("message")) {
                        int64_t chatIdNumber = update["message"]["chat"]["id"].get<int64_t>();
                        chatId = std::to_string(chatIdNumber);
                        std::cout << "Chat ID: " << chatId << std::endl;
                    }
                }
            } 
            else
            {
                std::cerr << "Erro na resposta do Telegram: " << response.dump(4) << std::endl;
            }
        } catch (const nlohmann::json::parse_error& e) 
        {
            std::cerr << "Erro ao parsear JSON: " << e.what() << std::endl;
        }
    } 
    else
    {
        std::cerr << "Falha na requisição: " << r.status_code << std::endl;
    }

    return chatId;
}

void telegram_bot::send_text_message(const std::string& text_message)
{
    if (this->chat_id.empty())
    {
        std::cerr << "Nenhum usuário está cadastrado" << std::endl;
    } 
    else
    {
        std::string sm = "/sendMessage";

        cpr::Response r = cpr::Get(cpr::Url{this->url + sm}, 
                                   cpr::Parameters{{"chat_id", this->chat_id},
                                                   {"text", text_message}}); 

        if (r.status_code == 200)
        {
            std::cout << "Mensagem enviado com sucesso!" << std::endl;
        }
        else
        {
            std::cout << "Falha ao enviar mensagem: " << r.status_code << std::endl;
            std::cout << r.text << std::endl;
        }
    }
}

void telegram_bot::send_warning()
{
    std::string message = "Uma pessoa foi detectado às " + this->get_time() + " segue uma foto tirada no instante.\n";
    this->send_text_message(message);

    if (fileExists(this->image_path))
    {
        this->send_photo_message();
    }
}

bool telegram_bot::fileExists(const std::string& filename) const
{
    std::ifstream file(filename);
    return file.good();
}

void telegram_bot::send_photo_message()
{
    if (this->chat_id.empty())
    {
        std::cerr << "Nenhum usuário está cadastrado" << std::endl;
    } 
    else
    {
        if (!fileExists(this->image_path)) 
        {
            std::cerr << "Erro: Arquivo " << this->image_path << " não existe." << std::endl;
            return;
        }
        std::string sm = "/sendPhoto";

        cpr::Response r = cpr::Get(cpr::Url{this->url + sm}, cpr::Multipart {{"chat_id", this->chat_id}, {"photo", cpr::File{this->image_path}}});

        if (r.status_code == 200) 
        {
            try 
            {
                nlohmann::json response = nlohmann::json::parse(r.text);
                if (response["ok"].get<bool>())
                {
                    std::cout << "Foto enviada com sucesso!" << std::endl;
                }
                else
                {
                    std::cerr << "Erro na reposta do Telegram: " << response.dump(4) << std::endl;
                }
            } catch (const nlohmann::json::parse_error& e)
            {
                std::cerr << "Erro ao parsear JSON: " << e.what() << std::endl;
            }
        }
        else
        {
            std::cout << "Falha ao enviar mensagem: " << r.status_code << std::endl;
            std::cout << r.text << std::endl;
        }
    }
}

std::string telegram_bot::read_file_to_vector(const std::string& filename) const
{
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open())
    {
        throw std::runtime_error("Não foi possível abrir o arquivo.");
    }

    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::string buffer;

    if (!file.read(buffer.data(), size)) 
    {
        throw std::runtime_error("Erro ao ler o arquivo.");
    }

    return buffer;
}

std::string telegram_bot::read_file_server() const
{
    std::string server_link;
    std::fstream(this->link_server_path, std::ios::in) >> server_link;

    return server_link;
}

void telegram_bot::listen_commands() {
    std::string gp = "/getUpdates";
    int lastUpdateId = 0;

    while (true) {
        cpr::Response r = cpr::Get(cpr::Url{this->url + gp}, cpr::Parameters{{"offset", std::to_string(lastUpdateId + 1)}});

        if (r.status_code == 200) {
            try {
                nlohmann::json response = nlohmann::json::parse(r.text);
                if (response["ok"].get<bool>()) {
                    for (const auto& update : response["result"]) {
                        if (update.contains("update_id")) {
                            lastUpdateId = update["update_id"].get<int>();
                        }
                        if (update.contains("message")) {
                            std::string command = update["message"]["text"].get<std::string>();
                            this->command_handler(command, update);
                        }
                    }
                } else {
                    std::cerr << "Erro na resposta do Telegram: " << response.dump(4) << std::endl;
                }
            } catch (const nlohmann::json::parse_error& e) {
                std::cerr << "Erro ao parsear JSON: " << e.what() << std::endl;
            } catch (const nlohmann::json::type_error& e) {
                std::cerr << "Erro de tipo ao acessar JSON: " << e.what() << std::endl;
            }
        } else {
            std::cerr << "Falha na requisição: " << r.status_code << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}


void telegram_bot::command_handler(std::string command, nlohmann::json response)
{
    if (command.compare("/start") == 0)
    {
        for (const auto& update : response["result"]) {
                    if (update.contains("chat")) {
                        int64_t chatIdNumber = update["message"]["chat"]["id"].get<int64_t>();
                        this->chat_id = std::to_string(chatIdNumber);
                    }
        }

        this->send_text_message("Bem-vindo ao PiMetis! Você sera cadastrado no sistema de babá eletrônica.");
    }

    if (command.compare("/espiar") == 0)
    {
        // std::time_t time = std::time({});
        // char buff[std::size("dd/mm/yyyy hh:mm:ss")];
        // std::strftime(std::data(buff), std::size(buff),
        //               "%D %T", std::localtime(&time));

        // std::string buffTime(buff);
        std::string mensagem = "Espiando às " + this->get_time() + "\n";
        this->send_text_message(mensagem);
        if (fileExists(this->image_path))
        {
            this->send_photo_message();
        }
    }

    if (command.compare("/sair") == 0)
    {
        this->send_text_message("Obrigado por usar o PiMetis! Você será removido no sistema de babá eletrônica.");
        this->chat_id = "";
    }
}

void telegram_bot::set_image( const std::string& image_path )
{
    this->image_path = image_path;
}

std::string telegram_bot::get_image() const
{
    return this->image_path;
}

std::string telegram_bot::get_time() const
{
    std::time_t time = std::time({});
    char buff[std::size("dd/mm/yyyy hh:mm:ss")];
    std::strftime(std::data(buff), std::size(buff),
                    "%D %T", std::localtime(&time));

    std::string buffTime(buff);

    return buffTime;
}