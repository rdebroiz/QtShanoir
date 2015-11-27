#include <shanoirqr.h>

#include <iostream>

#include <dao.h>

#include <utility>
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
        std::vector<std::pair<QString,QString>> freeLabelList;
        std::vector<MatchingType> matchingTypeVector;

        for(QString filter : m_args.filter)
        {
            QString keyCharacter=":";


            QString lvl = filter.split(keyCharacter)[0];

            if(lvl == "study")
                studyFilterList << filter.split(keyCharacter)[1];
            else if(lvl == "patient")
                patientFilterList << filter.split(keyCharacter)[1];
            else if(lvl == "exam")
                examFilterList << filter.split(keyCharacter)[1];
            else if(lvl == "dataset")
                datasetFilterList << filter.split(keyCharacter)[1];
            else {

                if(filter.contains(":"))
                {
                  keyCharacter=":";
                  matchingTypeVector.push_back(contains);
                }
                else if(filter.contains("="))
                {
                    keyCharacter="=";
                    matchingTypeVector.push_back(equals);
                }
                else if(filter.contains("!"))
                {
                    keyCharacter="!";
                    matchingTypeVector.push_back(notcontains);
                }

                freeLabelList.push_back(std::make_pair(filter.split(keyCharacter)[0],filter.split(keyCharacter)[1]));

            }

        }

        if(studyFilterList.isEmpty())
            studyFilterList << "";
        if(patientFilterList.isEmpty())
            patientFilterList << "";
        if(examFilterList.isEmpty())
            examFilterList << "";
       if(datasetFilterList.isEmpty() && (freeLabelList.size()==0))
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
                                            downloadFile(QString::number(dataset), m_args.download);
                                        }
                                    }
                                }
                                if(freeLabelList.size()!=0)
                                {
                                    auto keys=findDatasetListFilterFromField(study,patient,exam,freeLabelList,matchingTypeVector);
                                    for(int dataset : keys)
                                    {
                                        QtShanoirDataset dataSetForData=getShanoirDataSet(study,patient,exam,dataset);
                                        std::cout << "\t\t Data set: key: "<<dataset<<" matching: "<<std::endl;

                                        for(unsigned int index=0;index<freeLabelList.size();++index)
                                        {
                                            // display all values of the matching field (only once)
                                            if(std::find_if(freeLabelList.begin(),freeLabelList.begin()+index,[&](std::pair<QString,QString> a){return(a.first==freeLabelList[index].first);})==(freeLabelList.begin()+index))
                                                std::cout<<"\t\t\t "<<freeLabelList[index].first.toStdString()<<":"<<dataSetForData.getField(freeLabelList[index].first).toStdString()<<std::endl;
                                        }
                                        if(!m_args.download.isEmpty())
                                        {
                                            downloadFile(QString::number(dataset), m_args.download);
                                        }
                                    }

                                }
                            }
                        }
                    }
                }
            }
        }

        /*
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
                                           //findProcessedDatasetList(study, patient, exam,dataset)
                                        std::cout  << "\t\tDataset name:" << datasetMap[dataset].toStdString() << "\t|\tdb key: "<< dataset << std::endl;
                                        if(!m_args.download.isEmpty())
                                        {
                                            downloadFile(QString::number(dataset), m_args.download);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }*/
    }

    emit finished();

}
void shanoirqr::setArgs(arguments const& args)
{
    m_args = args;
}
