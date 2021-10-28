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

#include "JoystickMonitor.h"
#include <QDebug>
#include <QObject>


JoystickMonitor::JoystickMonitor(QObject *parent)
    : QObject(parent)    
{
    joystick = new Joystick("/dev/input/js0");
    connect(joystick, &Joystick::onButtonChange,this,&JoystickMonitor::onButtonEvent);
    connect(joystick, &Joystick::onAxisChange,this,&JoystickMonitor::onAxisEvent);
    connect(joystick, &Joystick::onDisconnected,this,&JoystickMonitor::onDisconnectedEvent);
    joystick->start();

}

void JoystickMonitor::onButtonEvent(unsigned char number, short value)
{
    qDebug() << "Button " << number << ":" << value;
}

void JoystickMonitor::onAxisEvent(unsigned char number, short value)
{
    qDebug() << "Axis " << number << ":" << value;
}

void JoystickMonitor::onDisconnectedEvent(bool value)
{
    qDebug() << "Joystick is disconnected: " << value;
}


JoystickMonitor::~JoystickMonitor()
{
    delete joystick;
}


