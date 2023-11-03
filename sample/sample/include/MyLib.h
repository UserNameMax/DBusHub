#include <QtDBus/QDBusConnection>

#define SERVICE_NAME "ru.mishenko.maksim.dbus"

class MyLib {
private:
  char *_pathToLib;
  QDBusConnection connection = QDBusConnection::sessionBus();

public:
  MyLib(char *path);
  void regist(char *name, char *path, char *type);
  void open(char *type, char *file);
};
