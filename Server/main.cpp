#include <QApplication>
#include "MyServer.h"
#include "DatabaseConn.h"

int main(int argc, char** argv)

{
    QApplication app(argc, argv);

    //if (!createConnection(""))
        //return -1;

    MyServer server(2323);

    server.show();

    return app.exec();

}
