#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <map>
#include <string>
#include "message.h" 
#include"user.h"

class User; // forward declaration

class Server {
public:
    Server();

    std::vector<User> get_users() const;
    std::map<std::string, std::string> get_public_keys() const;
    std::vector<Message*> get_messages() const;

    User create_user(std::string username);
    bool create_message(Message* msg, std::string signature);

    std::vector<Message*> get_all_messages_from(std::string username);
    std::vector<Message*> get_all_messages_to(std::string username);
    std::vector<Message*> get_chat(std::string user1, std::string user2);

    static void sort_msgs(std::vector<Message*>& msgs);

private:
    std::vector<User> users;
    std::map<std::string, std::string> public_keys;
    std::vector<Message*> messages;
};

#endif // SERVER_H
