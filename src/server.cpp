#include "server.h"
#include "crypto.h"
// #include "user.h"





Server::Server() {}

std::vector<User> Server::get_users() const {
    return users;
}

std::map<std::string, std::string> Server::get_public_keys() const {
    return public_keys;
}

std::vector<Message*> Server::get_messages() const {
    return messages;
}

User Server::create_user(std::string username) {
    if (public_keys.find(username) != public_keys.end()) {
        throw std::logic_error("Username already exists");
    }
    std::string public_key{}, private_key{};
    crypto::generate_key(public_key, private_key);
    public_keys[username] = public_key;
    users.emplace_back(username, private_key, this);
    return users.back();
}

bool Server::create_message(Message* msg, std::string signature) {

    
    std::string sender_username = msg->get_sender();

    std::string message_data;
    if (msg->get_type() == "text") {
        message_data = msg->get_text();
    } else {
        std::vector<unsigned char> voiceData =  msg->get_voice();
        message_data =  std::string(voiceData.begin(), voiceData.end());
    }
    if (public_keys.find(msg->get_receiver()) != public_keys.end()) {
    if (crypto::verifySignature(public_keys[sender_username], message_data, signature)) {
        messages.push_back(msg);
        return true;
    }
    }
    return false;
}

std::vector<Message*> Server::get_all_messages_from(const std::string username) {
    std::vector<Message*> result;
    std::copy_if(messages.begin(), messages.end(), std::back_inserter(result),
                 [&username](Message* m) { return m->get_sender() == username; });
    return result;
}

std::vector<Message*> Server::get_all_messages_to(const std::string username) {
    std::vector<Message*> result;
    std::copy_if(messages.begin(), messages.end(), std::back_inserter(result),
                 [&username](Message* m) { return m->get_receiver() == username; });
    return result;
}

std::vector<Message*> Server::get_chat(const std::string user1, const std::string user2) {
    std::vector<Message*> result;
    std::copy_if(messages.begin(), messages.end(), std::back_inserter(result),
                 [&user1, &user2](Message* m) {
                     return (m->get_sender() == user1 && m->get_receiver() == user2) ||
                            (m->get_sender() == user2 && m->get_receiver() == user1);
                 });
    return result;
}

void Server::sort_msgs(std::vector<Message *> &msgs){
    std::sort(msgs.begin(), msgs.end(), [](Message* a, Message* b) { return a->get_time() < b->get_time(); });
}
