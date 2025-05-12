#include "Contact.hpp"

Contact::Contact() {}
Contact::~Contact() {}

void Contact::setFirstName(const std::string &value)      { _firstName = value; }
void Contact::setLastName(const std::string &value)       { _lastName = value; }
void Contact::setNickName(const std::string &value)       { _nickName = value; }
void Contact::setPhoneNumber(const std::string &value)    { _phoneNumber = value; }
void Contact::setDarkestSecret(const std::string &value)  { _darkestSecret = value; }

const std::string &Contact::getFirstName() const  { return _firstName; }
const std::string &Contact::getLastName()  const  { return _lastName; }
const std::string &Contact::getNickName()  const  { return _nickName; }
const std::string &Contact::getPhoneNumber() const{ return _phoneNumber; }
const std::string &Contact::getDarkestSecret()const{ return _darkestSecret; }

bool Contact::isEmpty() const {
    return _firstName.empty();
}