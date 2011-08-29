#include "InputsManager.h"

namespace bloup
{

InputsManager::InputsManager():
    m_repeat(false)
{
}

void InputsManager::keyPressInput(QKeyEvent *event)
{
    if (!m_repeat && event->isAutoRepeat())
        return;
    qWarning("%s", event->text().toStdString().c_str());
    m_events.push_back(Input(Input::keyPressed,
                             event->text().toStdString(),
                             event->key()));
}

void InputsManager::keyReleaseInput(QKeyEvent *event)
{
    if (!m_repeat && event->isAutoRepeat())
        return;
    m_events.push_back(Input(Input::keyReleased,
                             event->text().toStdString(),
                             event->key()));
}

void InputsManager::leaveInput(QEvent *event)
{
    m_events.push_back(Input(Input::leave));
}

void InputsManager::setEnableRepeat(bool enable)
{
    m_repeat = enable;
}

bool InputsManager::isEmpty() const
{
    return m_events.empty();
}


Input InputsManager::getInput()
{
    if (isEmpty())
        return Input(Input::invalid);
    Input res = m_events.front();
    m_events.erase(m_events.begin());
    return res;
}

} // namespace bloup
