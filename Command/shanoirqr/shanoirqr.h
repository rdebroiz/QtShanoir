#include <QObject>

#include <QString>
#include <QStringList>

struct arguments
{
    QString login;
    QString password;
    QString host;
    int port;
    QString truststore;
    QString querryLevl;
    QStringList filter;
};

class shanoirqr: public QObject
{
    Q_OBJECT

public:
    shanoirqr(QObject *parent = NULL);
    virtual ~shanoirqr();

    void setArgs(arguments const& args);

public slots:
    void start();

signals:
    void finished();

private:
    arguments m_args;
};
