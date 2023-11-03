#include <QCoreApplication>
#include "include/MyLib.h"


int main(int argc, char *argv[])
{
    MyLib myLib = MyLib("../sample/deps/omp");
    char *file = "../deps/text.txt";
    myLib.regist("nano", "/bin/nano", ".txt");
    myLib.open(".txt", file);
    return 0;
}
