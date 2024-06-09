#include "user.h"
#include "crypto.h"


User::User(std::string username, std::string private_key, Server* server)
    : username(username), private_key(private_key), server(server) {}


std::string User::get_username() const {
    return username;
}



bool User::send_text_message(std::string text, std::string receiver) {
    
    TextMessage* msg = new TextMessage(text, username, receiver);

    std::string signature = crypto::signMessage(private_key, msg->get_text());
    bool result = server->create_message(msg, signature);
    if (!result) {
        delete msg; // clean up memory 
    }
    return result;
    }


bool User::send_voice_message(const std::string receiver) {

    VoiceMessage* msg = new VoiceMessage(username, receiver);
    
    std::vector<unsigned char> voiceData =  msg->get_voice();

    std::string signature = crypto::signMessage(private_key, (std::string(voiceData.begin(), voiceData.end())));
    bool result = server->create_message(msg, signature);
    if (!result) {
        delete msg; // clean memory 
    }
    return result;
}
