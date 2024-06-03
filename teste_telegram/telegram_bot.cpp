#include "telegram_bot.hpp"

telegram_bot::telegram_bot(const std::string &token) 
    : token(token)
{
    this->url = this->url + token;

    this->server_link = read_file_server();

    std::thread bot_listenning(&telegram_bot::listen_commands, this);

    bot_listenning.join();
}
 
telegram_bot::telegram_bot(const std::string &token, const std::string& chat_id) 
    : token(token), chat_id(chat_id)
{
    this->url = this->url + token;
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
                chatId = response["result"]["chat"]["id"];
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

bool telegram_bot::fileExists(const std::string& filename) const
{
    std::ifstream file(filename);
    return file.good();
}

void telegram_bot::send_photo_message(const std::string& photo_path)
{
    if (this->chat_id.empty())
    {
        std::cerr << "Nenhum usuário está cadastrado" << std::endl;
    } 
    else
    {
        if (!fileExists(photo_path)) 
        {
            std::cerr << "Erro: Arquivo " << photo_path << " não existe." << std::endl;
            return;
        }
        std::string sm = "/sendPhoto";
        // cpr::Multipart multipart
        // {
        //     {"chat_id", this->chat_id},
        //     {"photo", cpr::File{photo_path}}
        // };

        cpr::Response r = cpr::Get(cpr::Url{this->url + sm}, cpr::Multipart {{"chat_id", this->chat_id}, {"photo", cpr::File{photo_path}}});

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

void telegram_bot::listen_commands()
{
    std::string gp = "/getUpdates";
    while (true)
    {
        cpr::Response r = cpr::Get(cpr::Url{this->url + gp});

        if (r.status_code == 200)
        {
            try
            {
                nlohmann::json response = nlohmann::json::parse(r.text);
                if (response["ok"].get<bool>()) 
                {
                    if (response["result"].contains("message"))
                    {
                        std::string command = response["result"]["message"]["text"];

                        this->command_handler(command, response);
                    }
                }
                else 
                {
                    std::cerr << "Erro na resposta do Telegram: " << response.dump(4) << std::endl;
                }
            }
            catch(const nlohmann::json::parse_error& e)
            {
                std::cerr << "Ero ao parsear JSON: " << e.what() << '\n';
            }
            
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void telegram_bot::command_handler(std::string command, nlohmann::json response)
{
    if (command.compare("/start") == 0)
    {
        this->chat_id = response["result"]["chat"]["id"];
        this->send_text_message("Bem-vindo ao PiMetis! Você sera cadastrado no sistema de babá eletrônica.");
    }

    if (command.compare("/espiar") == 0)
    {
        std::time_t time = std::time({});
        char buff[std::size("dd/mm/yyyy hh:mm:ss")];
        std::strftime(std::data(buff), std::size(buff),
                      "%D %T", std::localtime(&time));;

        std::string buffTime(buff);
        std::string mensagem = "Espiando às " + buffTime + "\n";
        this->send_text_message("Espiando às ");
    }

    if (command.compare("/sair") == 0)
    {
        this->send_text_message("Obrigado por usar o PiMetis! Você será removido no sistema de babá eletrônica.");
        this->chat_id = "";
    }
}