#include "telegram_bot.hpp"

int main()
{
    std::cout << "Bem-vindo ao Telegram Bot!" << std::endl;
    telegram_bot tgbot("7132288406:AAGr8jjVtgQbD1VptDYure0pTn98EcohxBQ", "835554428");

    //tgbot.send_text_message("Olá Vinícius!!");
    tgbot.send_photo_message("../wallhaven-2y9x5m.jpg");

    return 0;
}