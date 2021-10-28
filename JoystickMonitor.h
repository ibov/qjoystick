/* The qjoystick class is rewritten based on
 * the lib: https://github.com/drewnoakes/joystick
 * New functions added:
 *   - Auto reconnect to joystick after unplugging / plugging
 *   - Emit signals including:
 *          + button / axis values
 *          + disconnected state
 *
 * Author: N.D.Quan - 27/10/2021
 */


#ifndef JOYSTICKMONITOR_H
#define JOYSTICKMONITOR_H

#include <QtCore/QObject>
#include "qjoystick.h"


//====================================================
//================ JoystickMonitor CLASS ==============
//====================================================
class JoystickMonitor : public QObject
{
    Q_OBJECT
public:
    explicit JoystickMonitor(QObject *parent = 0);
    ~JoystickMonitor();

private slots:
    void onDisconnectedEvent(bool value);
    void onButtonEvent(unsigned char number, short value);
    void onAxisEvent(unsigned char number, short value);

private:
    Joystick* joystick;
};


#endif // JOYSTICKMONITOR_H
