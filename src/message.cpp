#include "message.h"





// header implementation 

//  constructors
Message::Message(std::string type, std::string sender, std::string receiver)
    : type(type), sender(sender), receiver(receiver) {
    // docker container time is is gmt 
    std::time_t t = std::time(nullptr);
    time = std::ctime(&t);
    time.erase(time.find_last_not_of(" \n\r\t") + 1);

}

Message::Message() : type(""), sender(""), receiver("") {

    std::time_t t = std::time(nullptr);
    time = std::ctime(&t);
    time.erase(time.find_last_not_of(" \n\r\t") + 1);
}

// getting objects 
std::string Message::get_type() const { return type; }
std::string Message::get_sender() const { return sender; }
std::string Message::get_receiver() const { return receiver; }
std::string Message::get_time() const { return time; }
std::string Message::get_text() const {return {};}

std::vector<unsigned char> Message::get_voice() const
{
    return std::vector<unsigned char>();
}
// std::vector<unsigned char>get_voice() const {return {};}

// orint function 
void Message::print(std::ostream &os) const {
    os <<  sender << " -> " << receiver << "\n"
       << "message type: " << type << "\n"
       << "message time: " << time << "\n";
}

// operator <<
std::ostream& operator<<(std::ostream &os, const Message &msg) {
    msg.print(os);
    return os;
}

// ***********************************************************************************
// text message implementation

// Constructor
TextMessage::TextMessage(std::string text, std::string sender, std::string receiver)
    : Message("text", sender, receiver), text(text) {}


void TextMessage::print(std::ostream &os) const {
    Message::print(os);
    os << "text : " << text << "\n";
}

// Getter function for the text content
std::string TextMessage::get_text() const {return text;}

// ***********************************************************************************
// voice message implementation 

// Constructor
VoiceMessage::VoiceMessage(std::string sender, std::string receiver)
    : Message("voice", sender, receiver) {
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, 255);
        voice.resize(5);
        for (int i = 0; i < 5; ++i) {
            voice[i] = static_cast<unsigned char>(distrib(gen));
    }
        
    }

// print funtion 
void VoiceMessage::print(std::ostream &os) const {
    Message::print(os); 
    os << "voice: " ;
        for (auto byte : voice) {
        os << " " << static_cast<int>(byte);
    }
    os << std::endl;
}

// getting objects 
std::vector<unsigned char> VoiceMessage::get_voice() const {return voice;}