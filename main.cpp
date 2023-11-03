#include <QCoreApplication>
#include <QLocale>
#include <QTranslator>
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusError>
#include "include/FileReader.h"
#include "include/FileWriter.h"
#include <cerrno>
#include <cstddef>
#include <dirent.h>
#include <iostream>
#include <map>
#include <string.h>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <utility>

#define SERVICE_NAME "ru.mishenko.maksim.dbus"

std::string resPath;

class DBusListner : public QObject
{
    Q_OBJECT
public slots:
    void regist(const QString &name,const QString &path,const QString &type);
    void execute(const QString &type,const QString &path);

    void prepair(const std::string &dirName);
};

void DBusListner::prepair(const std::string &dirName){
    auto pDir = opendir(dirName.c_str());
    if (pDir == NULL && errno == 2) {
        mkdir(dirName.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    } else {
        closedir(pDir);
    }
}

void DBusListner::regist(const QString &name,const QString &path,const QString &type){
    FileReader *reader = new FileReader(resPath + "/types");
    auto typesMap = reader->readMultiMap();
    delete reader;
    reader = new FileReader(resPath + "/progs");
    auto programs = reader->readSimpleMap();
    delete reader;
    if (typesMap.count(type.toStdString())) {
        if (typesMap[type.toStdString()].count(name.toStdString()) == 0) {
            typesMap[type.toStdString()].insert(name.toStdString());
        }
    } else {
        typesMap.insert(std::pair(type.toStdString(), std::set{name.toStdString()}));
    }
    programs[name.toStdString()] = path.toStdString();
    FileWriter *writer = new FileWriter(resPath + "/types");
    writer->writeMultiMap(typesMap);
    delete writer;
    writer = new FileWriter(resPath + "/progs");
    writer->writeSimpleMap(programs);
    delete writer;
}

void DBusListner::execute(const QString &type,const QString &file){
    FileReader *reader = new FileReader(resPath + "/types");
    auto typesMap = reader->readMultiMap();
    delete reader;
    reader = new FileReader(resPath + "/progs");
    auto programs = reader->readSimpleMap();
    delete reader;
    if (typesMap.count(type.toStdString())) {
        auto progs = typesMap[type.toStdString()];
        auto name = *(progs.begin());
        if (progs.size() > 1) {
            for (auto selectProg = progs.cbegin(); selectProg != progs.cend();
                 ++selectProg) {
                char answer;
                std::cout << "open with " << *selectProg << " (y/n): ";
                std::cin >> answer;
                if (answer == 'y') {
                    name = *selectProg;
                    break;
                }
            }
        }
        auto path = programs[name];
        char *pPath = new char[path.length() + 1];
        strcpy(pPath, path.c_str());
        char *argVec[3] = {pPath, const_cast<char*>(file.toStdString().c_str()), NULL};
        execve(argVec[0], argVec, NULL);
        std::cout << errno;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    auto path = std::string(argv[0]);
    auto listner = DBusListner();
    path.erase(path.begin() + path.find_last_of("/"), path.end());
    resPath = path + "/resources";
    listner.prepair(resPath);

    auto connection = QDBusConnection::sessionBus();

    if (!connection.isConnected()) {
        qWarning("Cannot connect to the D-Bus session bus.\n"
                 "To start it, run:\n"
                 "\teval `dbus-launch --auto-syntax`\n");
        return 1;
    }

    if (!connection.registerService(SERVICE_NAME)) {
        qWarning("%s\n", qPrintable(connection.lastError().message()));
        exit(1);
    }

    connection.registerObject("/", &listner, QDBusConnection::ExportAllSlots);

    return a.exec();
}
