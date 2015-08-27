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
        foreach(int key, studies.keys())
        {
            std::cout  << "Study name:" << studies[key].toStdString() << "\t|\tdb key: "<< key << std::endl;
        }
    }
    else
    {
        QStringList studyFilterList, patientFilterList, datasetFilterList;
        foreach(QString filter, m_args.filter)
        {
            QString lvl = filter.split(":")[0];

            if(lvl == "study")
                studyFilterList << filter.split(":")[1];
            else if(lvl == "patient")
                patientFilterList << filter.split(":")[1];
            else if(lvl == "dataset")
                datasetFilterList << filter.split(":")[1];
        }

        if(studyFilterList.isEmpty())
            studyFilterList << "";
        if(patientFilterList.isEmpty())
            patientFilterList << "";
        if(datasetFilterList.isEmpty())
            datasetFilterList << "";

        foreach(QString studyfilter, studyFilterList)
        {
            QMap<int, QString> studiesMap;
            studiesMap.unite(findStudyList(studyfilter));
            foreach(int study, studiesMap.keys())
            {
                std::cout  << "Study name:" << studiesMap[study].toStdString() << "\t|\tdb key: "<< study << std::endl;
                QMap<int, QString> patientsMap;
                foreach(QString patientFilter, patientFilterList)
                {
                    patientsMap.unite(findSubjectList(studiesMap[study], patientFilter));
                    foreach(int patient, patientsMap.keys())
                    {
                        std::cout  << "\tPatient name:" << patientsMap[patient].toStdString() << "\t|\tdb key: "<< patient << std::endl;
                        QMap<int, QString> datasetMap;
                        foreach(QString datasetFilter, datasetFilterList)
                        {
                            datasetMap.unite(findExamList(study, patient));
                            foreach(int exam, datasetMap.keys())
                            {
                                std::cout  << "\t\tDataset name:" << datasetMap[exam].toStdString() << "\t|\tdb key: "<< exam << std::endl;
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
