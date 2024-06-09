#ifndef MESSAGE_H
#define MESSAGE_H

#include<string>
#include<ctime>
#include <iostream>
#include<vector>
#include<random>

class Message {
public:
    // Constructors
    Message(std::string type, std::string sender, std::string receiver);
    Message();

    virtual ~Message() {} //virtual destructor 


    // Getter functions
    std::string get_type() const;
    std::string get_sender() const;
    std::string get_receiver() const;
    std::string get_time() const;
    
    virtual std::string get_text() const;//for acsses get_text function in Message objs
    virtual std::vector<unsigned char> get_voice() const;


    // Print function for use in operator<< overloading
    virtual void print(std::ostream &os) const;

    // Overload operator<< to work with Message objects
    friend std::ostream& operator<<(std::ostream &os, const Message &msg);

private:
    std::string type;     // Type of the message ("text", "voice", ...)
    std::string sender;   // The username who sent this message
    std::string receiver; // The username to whom this message is intended
    std::string time;     // Creation time of the message in GMT
};


class TextMessage : public Message {
public:
    // Constructor
    TextMessage(std::string text, std::string sender, std::string receiver);

    // Member function for printing
    void print(std::ostream &os) const override;

    // Getter function for the text content
    std::string get_text()  const override;

private:
    std::string text;  // The text content of the message
};

class VoiceMessage : public Message {
public:
    // Constructor
    VoiceMessage(std::string sender, std::string receiver);

    // Member function for printing
    void print(std::ostream &os) const override;

    // Getter function for the voice data
    std::vector<unsigned char> get_voice() const override;

private:
    std::vector<unsigned char> voice; // Array of bytes to store the voice data
};



#endif //MESSAGE_H