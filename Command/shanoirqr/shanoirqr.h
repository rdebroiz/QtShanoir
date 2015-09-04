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
    QString displayLevel;
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

    void print(QMap<int, QString> const& map);
    void print(QString const& study, QMap<int, QString> const& map);
    void print(QString const& study, QString const& subject, QMap<int, QString> const& map);
    void print(QString const& study, QString const& subject, QString const& exam, QMap<int, QString> const& map);

    QMap<int, QString> querryStudy();
    QMap<int, QString> querrySubject(QString const& study);
    QMap<int, QString> querryExam(const int study, int subject);
    QMap<int, QString> querryDataset(int const study, int const  subject, int const exam);

    QStringList m_studyFilters;
    QStringList m_subjectFilters;
    QStringList m_examFilters;
    QStringList m_datasetFilters;
};
