#ifndef INPUTSSMANAGER_H
#define INPUTSMANAGER_H

#include <events/Input.h>
#include <QKeyEvent>
#include <list>

namespace bloup
{

/*!
  * @class InputsManager
  * @brief Handles events
  */
class InputsManager
{
public:
    /*!
      * @brief Constructor
      */
    InputsManager();

    /*!
      * @brief Handle key press (this is for internal use)
      * @param event
      */
    void keyPressInput(QKeyEvent *event);

    /*!
      * @brief Handle key release (this is for internal use)
      * @param event
      */
    void keyReleaseInput(QKeyEvent *event);

    /*!
      * @brief Handle leave event (this is for internal use)
      * @param event
      */
    void leaveInput(QEvent *event);

    /*!
      * @brief Enable / disable autorepeat
      * @param enable
      */
    void setEnableRepeat(bool enable);

    /*!
      * @brief Returns true if the list of events is empty
      * @return true if the list of events is empty
      */
    bool isEmpty() const;

    /*!
      * @brief Returns the next event on the list
      * @return The event, or an invalid event if there's no more
      */
    Input getInput();

private:
    std::list<Input> m_events;
    bool m_repeat;
};

} // namespace bloup

#endif // EVENTSMANAGER_H
