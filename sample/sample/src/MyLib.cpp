#include "../include/MyLib.h"
#include <cerrno>
#include <cstddef>
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <QtDBus/QDBusError>
#include <QtDBus/QDBusReply>
#include <QtDBus/QDBusInterface>
MyLib::MyLib(char *path) : _pathToLib(path) {}
void MyLib::regist(char *name, char *path, char *type) {
  pid_t chield;
  if ((chield = fork()) == 0) {
    char *argVec[] = {_pathToLib};
    execve(_pathToLib, argVec, NULL);
    std::cout << "chield: " << errno << "\n";
  } else {
    sleep(3);
    if (!connection.isConnected()) {
        qWarning("Cannot connect to the D-Bus session bus.\n"
                 "To start it, run:\n"
                 "\teval `dbus-launch --auto-syntax`\n");
        wait(&chield);
        return ;
    }

    QDBusInterface iface(SERVICE_NAME, "/");
    if (iface.isValid()) {
        QDBusReply<QString> reply = iface.call("regist", QString(name), QString(path), QString(type));
        if (reply.isValid()) {
            std::cout << "Reply was: " << qPrintable(reply.value()) << std::endl;
            wait(&chield);
            return ;
        }

        qWarning("Call failed: %s\n", qPrintable(reply.error().message()));
        wait(&chield);
        return ;
    }

    qWarning("%s\n", qPrintable(connection.lastError().message()));
    wait(&chield);
  }
}
void MyLib::open(char *type, char *file) {
  pid_t chield;
  if ((chield = fork()) == 0) {
    char *argVec[] = {_pathToLib};
    execve(_pathToLib, argVec, NULL);
    std::cout << "chield: " << errno << "\n";
  } else {
    sleep(3);
    if (!connection.isConnected()) {
        qWarning("Cannot connect to the D-Bus session bus.\n"
                 "To start it, run:\n"
                 "\teval `dbus-launch --auto-syntax`\n");
        wait(&chield);
        return ;
    }

    QDBusInterface iface(SERVICE_NAME, "/");
    if (iface.isValid()) {
        QDBusReply<QString> reply = iface.call("regist", QString(type), QString(file));
        if (reply.isValid()) {
            std::cout << "Reply was: " << qPrintable(reply.value()) << std::endl;
            wait(&chield);
            return ;
        }

        qWarning("Call failed: %s\n", qPrintable(reply.error().message()));
        wait(&chield);
        return ;
    }

    qWarning("%s\n", qPrintable(connection.lastError().message()));
    wait(&chield);
  }
}
