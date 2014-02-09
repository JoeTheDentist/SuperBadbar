
#include "SfmlKeyConvertor.h"


std::string SfmlKeyConvertor::sfmlkeyToStdstring (sf::Key::Code key)
{
    std::string plop;
    plop += char (key);
    return plop;
}

sf::Key::Code SfmlKeyConvertor::stdstringToSfmlkey (std::string str)
{
    for (int i = 0; i <= int (sf::Key::Count); i++)
    {
        if (str == SfmlKeyConvertor::sfmlkeyToStdstring (sf::Key::Code (i) ) )
        {
            return (sf::Key::Code (i) );
        }
    }
    return sf::Key::Count;
}
