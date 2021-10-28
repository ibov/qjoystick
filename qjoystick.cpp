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

#include "qjoystick.h"

#include <QDebug>
#include <QObject>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <sstream>
#include "unistd.h"


//========================================================
//==================== JOYSTICK CLASS ====================
//========================================================
Joystick::Joystick()
{
    m_devicePath = "/dev/input/js0";
    openPath(m_devicePath);
}

Joystick::Joystick(int joystickNumber)
{
  std::stringstream sstm;
  sstm << "/dev/input/js" << joystickNumber;
  openPath(sstm.str());
}

Joystick::Joystick(std::string devicePath)
{
  m_devicePath = devicePath;
  openPath(devicePath);
}

Joystick::Joystick(std::string devicePath, bool blocking)
{
  m_devicePath = devicePath;
  openPath(devicePath, blocking);
}

void Joystick::openPath(std::string devicePath, bool blocking)
{
  // Open the device using either blocking or non-blocking
  _fd = open(devicePath.c_str(), blocking ? O_RDONLY : O_RDONLY | O_NONBLOCK);
}

bool Joystick::sample(JoystickEvent* event)
{
  int bytes = read(_fd, event, sizeof(*event));

  if (bytes == -1)
    return false;
  return bytes == sizeof(*event);
}

bool Joystick::isFound()
{
  return _fd >= 0;
}

bool Joystick::isDisconnected()
{
    struct stat info;

    if(stat(m_devicePath.c_str(), &info ) != 0)
    {
        return true;
    }
    else
        return false;
}

Joystick::~Joystick()
{
  close(_fd);
}

void Joystick::run()
{
    while (true)
    {
      //QThread::msleep(100);

      // Attempt to sample an event from the joystick
      JoystickEvent event;
      bool check;
      check =sample(&event);
      if (check)
      {
        if (event.isButton())
        {
           //qDebug() << "Button " << event.number << ":" << event.value;
            emit onButtonChange(event.number,event.value);
        }
        else if (event.isAxis())
        {
          //qDebug() << "Axis " << event.number<< ":" << event.value;
            emit onAxisChange(event.number,event.value);
        }
      }
      //qDebug() << _fd << check << isDisconnected();
      if (not check && isDisconnected())
      {
          //qDebug() << "Joystick is disconnected";
          close(_fd);
          openPath(m_devicePath,false);
          emit onDisconnected(true);
          QThread::msleep(500);
      }
      else if (!isFound())
      {
          openPath(m_devicePath,false);
          emit onDisconnected(false);
          QThread::msleep(500);
      }
    }
}

