#ifndef INPUT_H
#define INPUT_H

#include <string>

namespace bloup
{

/*!
  * @class Input
  * @brief Represents a user output (from keyboard for now)
  */
class Input
{
public:
    enum type {keyPressed, keyReleased, leave, invalid};
public:
    /*!
      * @brief constructor
      * @param eventType
      * @param str event's name
      * @param key event's key
      */
    Input(type eventType = invalid, std::string str = "", int key = 0);

    type getType() const;

    std::string getString() const;

    int getKey() const;

private:
    type m_type;
    std::string m_string;
    int m_key;
};

} // namespace bloup

#endif // EVENT_H
