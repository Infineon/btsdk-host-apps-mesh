#include "mainwindow.h"
#include <QApplication>

bool g_bUseBsa = false;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#ifdef BSA
    g_bUseBsa = true;
#endif

    MainWindow w;
    w.show();
#if defined( MESH_AUTOMATION_ENABLED ) && (MESH_AUTOMATION_ENABLED == TRUE)
    #include "SocketHelper.h"
    SocketHelper *socket = SocketHelper::GetInstance();
    socket->SetOpenPort(12012);
    socket->CreateThread(&socket);
#endif
    return a.exec();
}
