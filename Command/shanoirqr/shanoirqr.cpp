#include <shanoirqr.h>

#include <iostream>

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

    if(m_args.filter.isEmpty())
    {
        QMap<int, QString> studies = findStudyList("");
        for(int key : studies.keys())
        {
            std::cout  << "Study name:" << studies[key].toStdString() << "\t|\tdb key: "<< key << std::endl;
        }
    }
    else
    {
        QStringList studyFilterList, patientFilterList, examFilterList, datasetFilterList;
        for(QString filter : m_args.filter)
        {
            QString lvl = filter.split(":")[0];

            if(lvl == "study")
                studyFilterList << filter.split(":")[1];
            else if(lvl == "patient")
                patientFilterList << filter.split(":")[1];
            else if(lvl == "exam")
                examFilterList << filter.split(":")[1];
            else if(lvl == "dataset")
                datasetFilterList << filter.split(":")[1];
        }

        if(studyFilterList.isEmpty())
            studyFilterList << "";
        if(patientFilterList.isEmpty())
            patientFilterList << "";
        if(examFilterList.isEmpty())
            examFilterList << "";
        if(datasetFilterList.isEmpty())
            datasetFilterList << "";

        for(QString studyfilter : studyFilterList)
        {
            QMap<int, QString> studiesMap;
            studiesMap.unite(findStudyList(studyfilter));
            for(int study : studiesMap.keys())
            {
                std::cout  << "Study name:" << studiesMap[study].toStdString() << "\t|\tdb key: "<< study << std::endl;
                QMap<int, QString> patientsMap;
                for(QString patientFilter : patientFilterList)
                {
                    patientsMap.unite(findSubjectList(studiesMap[study], patientFilter));
                    for(int patient : patientsMap.keys())
                    {
                        std::cout  << "\tPatient name:" << patientsMap[patient].toStdString() << "\t|\tdb key: "<< patient << std::endl;
                        QMap<int, QString> examMap;
                        for(QString examFilter : examFilterList)
                        {
                            examMap.unite(findExamListf(study, patient, examFilter));
                            for(int exam : examMap.keys())
                            {
                                std::cout  << "\t\tExam name:" << examMap[exam].toStdString() << "\t|\tdb key: "<< exam << std::endl;
                                QMap<int, QString> datasetMap;
                                for(QString datasetFilter : datasetFilterList)
                                {
                                    datasetMap.unite(findDatasetListf(study, patient, exam, datasetFilter));
                                    for(int dataset : datasetMap.keys())
                                    {
                                        std::cout  << "\t\tDataset name:" << datasetMap[dataset].toStdString() << "\t|\tdb key: "<< dataset << std::endl;
                                        if(!m_args.download.isEmpty())
                                        {
                                            downloadFile(datasetMap[dataset], m_args.download);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    emit finished();

}
void shanoirqr::setArgs(arguments const& args)
{
    m_args = args;
}
