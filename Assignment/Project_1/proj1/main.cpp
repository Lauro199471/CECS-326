#include "mainwindow.h"
#include <QApplication>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int main(int argc, char *argv[])
{
    /*myStruct mainStruct;
    for(int i = 0;i<21;i=i+1)
    {
        deallocatedIndex[i] = 255;
    }*/

    srand(time(0));

    //init_INT_ARRAY(&mainStruct);
    //init_CHARPTR_ARRAY(&mainStruct);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
