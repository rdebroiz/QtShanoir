#include <shanoirqr.h>

#include <iostream>
#include <limits>
#include <iomanip>

#include <dao.h>


shanoirqr::shanoirqr(QObject *parent): QObject(parent)
{

}
shanoirqr::~shanoirqr()
{

}
void shanoirqr::start()
{
    GlobalData::settings.setLogin(m_args.login);
    GlobalData::settings.setPassword(m_args.password);
    GlobalData::settings.setHost(m_args.host);
    GlobalData::settings.setPort(m_args.port);
    GlobalData::settings.setTrustore(m_args.truststore);

    authentification();

    for(QString const& filter : m_args.filter)
    {
        QString lvl = filter.split(":")[0];

        if(lvl == "study")
            m_studyFilters << filter.split(":")[1];
        else if(lvl == "subject")
            m_subjectFilters << filter.split(":")[1];
        else if(lvl == "exam")
            m_examFilters << filter.split(":")[1];
        else if(lvl == "dataset")
            m_datasetFilters << filter.split(":")[1];
        else
        {
            std::cout << "warning: "<< lvl.toStdString() << std::endl
                      << "level from -q <level:filer> must be in [study, subject, exam, dataset]"
                      << std::endl;
            emit finished();
            return;
        }
    }

    if(m_args.displayLevel == "study")
    {
        std::cout << std::setw(15) << std::left <<  "Study Name"
                  << " : " << "key" << std::endl;
        std::cout << "---------------------------------------------------------------------------------------------------" << std::endl;
        print(querryStudy());
    }
    else if(m_args.displayLevel == "subject")
    {
        std::cout << std::setw(15) << std::left <<  "Study name"
                  << std::setw(15) <<  std::left << "Subject name"
                  << " : " << "key" << std::endl;
        std::cout << "---------------------------------------------------------------------------------------------------" << std::endl;
        QStringList studies = querryStudy().values();
        std::sort(studies.begin(), studies.end());
        for(QString const& study : studies)
        {
            print(study, querrySubject(study));
        }

    }
    else if(m_args.displayLevel == "exam")
    {
        std::cout << std::setw(15) << std::left <<  "Study name"
                  << std::setw(15) << std::left << "Subject name"
                  << std::setw(15) << std::left << "Exam name"
                  << " : " << "key" << std::endl;
        std::cout << "---------------------------------------------------------------------------------------------------" << std::endl;
        QMap<int, QString> studiesMap = querryStudy();
        QStringList studies = studiesMap.values();
        std::sort(studies.begin(), studies.end());
        for(QString const& study : studies)
        {
            QMap<int, QString> subjectsMap = querrySubject(study);
            QStringList subjects = subjectsMap.values();
            std::sort(subjects.begin(), subjects.end());
            for(QString const& subject : subjects)
            {
                print(study, subject, querryExam(studiesMap.key(study), subjectsMap.key(subject)));
            }

        }
    }
    else if(m_args.displayLevel == "dataset")
    {

        std::cout << std::setw(15) << std::left <<  "Study name"
                  << std::setw(15) << std::left << "Subject name"
                  << std::setw(15) << std::left << "Exam name"
                  << std::setw(42) << std::left << "Dataset name"
                  << " : " << "key" << std::endl;
        std::cout << "---------------------------------------------------------------------------------------------------" << std::endl;
        QMap<int, QString> studiesMap = querryStudy();
        QStringList studies = studiesMap.values();
        std::sort(studies.begin(), studies.end());
        for(QString const& study : studies)
        {
            QMap<int, QString> subjectsMap = querrySubject(study);
            QStringList subjects = subjectsMap.values();
            std::sort(subjects.begin(), subjects.end());
            for(QString const& subject : subjects)
            {
                QMap<int, QString> examsMap = querryExam(studiesMap.key(study), subjectsMap.key(subject));
                QStringList exams = examsMap.values();
                std::sort(exams.begin(), exams.end());
                for(QString const& exam : exams)
                {
                    print(study, subject, exam, querryDataset(studiesMap.key(study), subjectsMap.key(subject), examsMap.key(exam)));
                }
            }
        }
    }
    else
    {
        std::cout << "-l / --level argument must be in [study, subject, exam, dataset]";
        emit finished();
    }

//        if(studyFilterList.isEmpty())
//            studyFilterList << "";
//        if(subjectFilterList.isEmpty())
//            subjectFilterList << "";
//        if(examFilterList.isEmpty())
//            examFilterList << "";
//        if(datasetFilterList.isEmpty())
//            datasetFilterList << "";

    emit finished();
}

QMap<int, QString> shanoirqr::querryExam(int const study, int const  subject)
{
    return findExamList(study, subject);
}

QMap<int, QString> shanoirqr::querryDataset(int const study, int const  subject, int const exam)
{
    return findDatasetList(study, subject, exam);
}

QMap<int, QString> shanoirqr::querryStudy()
{
    QMap<int, QString> findResponse = findStudyList("");

    for(QString const& filter : m_studyFilters)
    {
        QMap<int, QString> nestedFindResponse = findStudyList(filter);
        for(int const & key : findResponse.keys())
            if(!nestedFindResponse.contains(key))
                findResponse.remove(key);
    }

    return findResponse;
}

QMap<int, QString> shanoirqr::querrySubject(QString const& study)
{
    QMap<int, QString> findResponse;

    findResponse.unite(findSubjectList(study, ""));
    for(QString const& filter : m_subjectFilters)
    {
        QMap<int, QString> nestedFindResponse = findSubjectList(study, filter);
        for(int const & key : findResponse.keys())
            if(!nestedFindResponse.contains(key))
                findResponse.remove(key);
    }
    return findResponse;
}

void shanoirqr::print(const QMap<int, QString> &map)
{
    QStringList values = map.values();
    std::sort(values.begin(), values.end());
    for(QString const& val : values)
    {
        std::cout << std::setw(15) <<  std::left << val.toStdString()
                  << " : " << map.key(val) << std::endl;
    }

}

void shanoirqr::print(QString const& study, const QMap<int, QString> &map)
{
    QStringList values = map.values();
    std::sort(values.begin(), values.end());
    for(QString const& val : values)
    {
        std::cout << std::setw(15) <<  std::left << study.toStdString()
                  << std::setw(15) <<  std::left << val.toStdString()
                  << " : " << map.key(val) << std::endl;
    }

}

void shanoirqr::print(QString const& study, QString const& subject, const QMap<int, QString> &map)
{
    QStringList values = map.values();
    std::sort(values.begin(), values.end());
    for(QString const& val : values)
    {
        std::cout << std::setw(15) <<  std::left << study.toStdString()
                  << std::setw(15) <<  std::left << subject.toStdString()
                  << std::setw(15) <<  std::left << val.toStdString()
                  << " : " << map.key(val) << std::endl;
    }

}

void shanoirqr::print(QString const& study, QString const& subject, QString const& exam, const QMap<int, QString> &map)
{
    QStringList values = map.values();
    std::sort(values.begin(), values.end());
    for(QString const& val : values)
    {
        std::cout << std::setw(15) <<  std::left << study.toStdString()
                  << std::setw(15) <<  std::left << subject.toStdString()
                  << std::setw(15) <<  std::left << exam.toStdString()
                  << std::setw(42) <<  std::left << val.toStdString()
                  << " : " << map.key(val) << std::endl;
    }

}


void shanoirqr::setArgs(arguments const& args)
{
    m_args = args;
}
