/* This qjoystick class is rewritten based on
 * the lib: https://github.com/drewnoakes/joystick
 * New functions added:
 *   - Auto reconnect to joystick after unplugging / plugging
 *   - Emit signals including:
 *          + button / axis values
 *          + disconnected state
 *
 * Author: N.D.Quan - 27/10/2021
 */


#ifndef QJOYSTICK_H
#define QJOYSTICK_H

#include <QtCore/QObject>
#include <QtCore/QThread>
#include <string>
#include <iostream>

//====================================================
//================ JOYSTICK_EVENT CLASS ==============
//====================================================
#define JS_EVENT_BUTTON 0x01 // button pressed/released
#define JS_EVENT_AXIS   0x02 // joystick moved
#define JS_EVENT_INIT   0x80 // initial state of device

class JoystickEvent
{
public:
  static const short MIN_AXES_VALUE = -32768;
  static const short MAX_AXES_VALUE = 32767;
  unsigned int time;
  short value;
  unsigned char type;
  unsigned char number;

  bool isButton()
  {
    return (type & JS_EVENT_BUTTON) != 0;
  }

  bool isAxis()
  {
    return (type & JS_EVENT_AXIS) != 0;
  }

  bool isInitialState()
  {
    return (type & JS_EVENT_INIT) != 0;
  }

};

//====================================================
//================ JOYSTICK CLASS ====================
//====================================================
class Joystick : public QThread
{
Q_OBJECT
private:
    void openPath(std::string devicePath, bool blocking=false);
    int _fd;
    std::string m_devicePath;

public:
    ~Joystick();
    Joystick();
    Joystick(int joystickNumber);
    Joystick(std::string devicePath);
    Joystick(Joystick const&) = delete;
    Joystick(std::string devicePath, bool blocking);
    bool isFound();
    bool isDisconnected();
    bool sample(JoystickEvent* event);
    void run();

signals:
    void onButtonChange(unsigned char number, short value);
    void onAxisChange(unsigned char number, short value);
    void onDisconnected(bool value);

};

#endif // QJOYSTICK_H
