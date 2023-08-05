#ifndef LOG_SYS_H
#define LOG_SYS_H

#include "TreeWidget/treeWidgetManager.h"

#include <QString>
#include <QObject>
#include <QTimer>
#include <QDateTime>
#include <iostream>
#include <QTextBrowser>

// 打印日志输出的系统,暂时没写
class LogSys : public QObject{
    Q_OBJECT
public:
    LogSys();
    ~LogSys();

    int initLogSys(QTextBrowser* logTextOutput);

    static QString sDefaultLogPath;
    QString sDirPath;
    QTextBrowser* m_pLogTextOutput;

    // 拿这两个指针是为了bind LogSys的日志打印接口和这两个指针里的信息输出的接口弄成信号槽
    TreeWidgetManager* m_pTreeWidgetMgr;

public slots:
    int saveLog(QString path);
    int saveLog();
    int outputLog(QString msg);
    int clearLog();
};

#endif