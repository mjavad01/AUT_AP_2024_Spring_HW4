#ifndef USER_H
#define USER_H

#include <string>
#include"message.h"
#include"server.h"


class Server; // forward declaration

class User {
public:
    User(std::string username, std::string private_key, Server* server);

    std::string get_username() const;

    bool send_text_message(std::string text, std::string receiver);
    bool send_voice_message(std::string receiver);

private:
    std::string username;
    std::string private_key;
    Server* const server;
};

#endif // USER_H
