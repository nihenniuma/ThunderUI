#include "logSys.h"

QString sDefaultLogPath = "";

LogSys::LogSys() : m_pLogTextOutput(nullptr){}
LogSys::~LogSys(){}

int LogSys::initLogSys(QTextBrowser* logTextOutput)
{
    m_pLogTextOutput = logTextOutput;
    return 0;
}

int LogSys::saveLog(QString path){
    return 0;
}

int LogSys::saveLog(){
    std::cout << "saveLog" << std::endl;
    return 0;
}

int LogSys::clearLog()
{
    if(m_pLogTextOutput == nullptr) return -1;
    m_pLogTextOutput->clear(); 
    return 0;
}

int LogSys::outputLog(QString msg){
    if(m_pLogTextOutput == nullptr) return -1;
    QString output = QDateTime::currentDateTime().toString("yyyy-mm-dd") + ' ' + \
                    QDateTime::currentDateTime().toString("HH:mm:ss") + ' ' + msg + '\n';
    m_pLogTextOutput->insertPlainText(output);
    return 0;
}

