#include "logSys.h"

QString sDefaultLogPath = "";

LogSys::LogSys() : pLogTextOutput(nullptr){}
LogSys::~LogSys(){}

int LogSys::initLogSys(QTextBrowser* logTextOutput)
{
    pLogTextOutput = logTextOutput;
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
    if(pLogTextOutput == nullptr) return -1;
    pLogTextOutput->clear(); 
    return 0;
}

int LogSys::outputLog(QString msg){
    if(pLogTextOutput == nullptr) return -1;
    QString output = QDateTime::currentDateTime().toString("yyyy-mm-dd") + ' ' + \
                    QDateTime::currentDateTime().toString("HH:mm:ss") + ' ' + msg + '\n';
    pLogTextOutput->insertPlainText(output);
    return 0;
}

