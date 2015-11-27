#include <docopt.h>
#include <shanoirqr.h>

#include <QCoreApplication>
#include <QString>
#include <QTimer>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QSettings>
#include <QDebug>

#include <iostream>

void shMessageHandler(QtMsgType type, const char *msg)
{
    QString txt;
    switch (type) {
    case QtDebugMsg:
        txt = QString("Debug: %1").arg(msg);
        break;
    case QtWarningMsg:
        txt = QString("Warning: %1").arg(msg);
    break;
    case QtCriticalMsg:
        txt = QString("Critical: %1").arg(msg);
    break;
    case QtFatalMsg:
        txt = QString("Fatal: %1").arg(msg);
        abort();
    }
    QFile outFile("shanoirqr.log");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << endl;
}

static const char USAGE[] =
R"(shanoirqr

    Usage:
      shanoirqr (-i <ini_file> | <login> <password> <host> [--port <port_number>] [--truststore <things>]) [-q <level:filter>]... [-d <path>]
      shanoirqr (-h | --help)
      shanoirqr --version

    Options:
      -h --help            Show this screen.
      --port port_number   Port used to be connected to the shanoir server [default: 0]
      --truststore things  Truststore thing [default: ""]
      -i                   ini configuration file for all connection stuff. [default: ""]
      -q level:filter      Query to send to shanoir, must look likes [level:filter], level beeing in [study, patient, exam, dataset]
      -d path              Downlaod dataset found to path [default: ""]
      --version            Show version.
)";

int main(int argc, const char** argv)
{

    QCoreApplication app(argc, const_cast<char **>(argv));
    qInstallMsgHandler(shMessageHandler);

    std::map<std::string, docopt::value> args
        = docopt::docopt(USAGE,
                         { argv + 1, argv + argc },
                         true,               // show help if requested
                         "shanoirqr 1.a");  // version string

    for(auto const& arg : args)
    {
        std::cout << arg.first << ": " << arg.second << std::endl;
    }
    std::cout << std::endl << std::endl;

    arguments a;

    if(! args["<ini_file>"].asString().empty())
    {
        QString settings_filename = QString::fromUtf8(args["<ini_file>"].asString().c_str());
        QSettings settings(settings_filename, QSettings::IniFormat);

        settings.beginGroup("Users");
        a.login = settings.value("login", "").toString();
        a.password = settings.value("password", "").toString();
        settings.endGroup();

        settings.beginGroup("Server");
        a.host = settings.value("host", "").toString();
        a.port = settings.value("port", "").toInt();
        settings.endGroup();

        settings.beginGroup("Security");
        a.truststore = settings.value("truststore", "").toString();
        settings.endGroup();
    }
    else
    {
        a.login = QString::fromUtf8(args["<login>"].asString().c_str());
        a.password = QString::fromUtf8(args["<password>"].asString().c_str());
        a.host = QString::fromUtf8(args["<host>"].asString().c_str());
        a.login = atoi(args["<port>"].asString().c_str());
        a.truststore = QString::fromUtf8(args["<truststore>"].asString().c_str());
    }

    if(args["-q"].isStringList())
    {
        for(auto const& querry : args["-q"].asStringList())
        {
            a.filter << QString::fromUtf8(querry.c_str());
        }
    }
    if(args["-d"].isString())
        a.download = QString::fromUtf8(args["-d"].asString().c_str());

    qDebug() << "login: " << a.login;
    qDebug() << "password: " << a.password;
    qDebug() << "host: " << a.host;
    qDebug() << "port: " << a.port;
    qDebug() << "truststore: " << a.truststore;

    shanoirqr *task = new shanoirqr(&app);
    task->setArgs(a);

    QObject::connect(task, SIGNAL(finished()), &app, SLOT(quit()));
    QTimer::singleShot(0, task, SLOT(start()));

    app.exec();
}
