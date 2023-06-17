#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include <QMap>
#include <QString>
#include <QFileInfo>
#include <QTreeWidgetItem>
#include <Eigen/Core>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class modelInfo;

// 这里必须继承QObject不然无法使用信号槽
class modelManager : public QObject{
    Q_OBJECT
public:
    modelManager();
    ~modelManager();

    int praseConfFile(QString sConfPath);
    int initModel(QString sModelPath);
    int checkRedundancy(QString sModelName);
    int setModelName(modelInfo& model, QString sNewName);
    int setModelName(QString sModelName, QString sNewName);
    // int setSubModelName(QString sModelName);
    // int rotateSubModel(QString sSubModelName, Eigen::Matrix3d rotation);
    int rotateModelVertex(QString sModelName, Eigen::Matrix3d rotation);
    int rotateModelNormal(QString sModelName, Eigen::Matrix3d rotation);
    int setModelActive(QString sModelName);
    // int setSubModelActive(QString sSubModelName);
    int setActiveOrDeAactive(QString sModelName, bool bIsAcitve);
    int setActiveOrDeAactive(QStringList sNameList, bool bIsAcitve);
    int addModel2Map(modelInfo& model, QString sModelName);
    // int clearSubModel();

    // 这两个接下来还要思考怎么封装，现在就先这样
    int readFile(QString sFilePath, modelInfo& model);
    int readConfigFile(QString sFilePath, modelInfo& model);
    int readModelFromFile(QString sModelPath, modelInfo& model);
    Eigen::MatrixX3d trans2Eigen(std::vector<Eigen::Matrix<double, 1, 3>> input);

    // 给外界一个查找modelInfo的接口
    int getModelInfoFromMap(QString sTargetName, modelInfo& model);
    int isModelExist(QString sModelName);
    QMap<QString, modelInfo> mModelInfoMap;
signals:
    void logOutputSig(QString);
    void setTreeNodeSig();
    void addNodeSig(QString, QTreeWidgetItem*);

public slots:
    int clearModel(QString sModelName);
};

class modelInfo{
public:
    modelInfo();
    ~modelInfo();

    int clear();
    int turnActive();
    int turnDeActive();
    int isActive();

    int setModelName(QString sNewName);
    QString getModelName();

    bool bActive;
    QString sModelName;
    QString sModelPath;
    QTreeWidgetItem* iTreeWidgetItem;

    // QMap<QString, subModel> mSubModelInfo;
    
    Eigen::MatrixX3d eModelVertex;
    Eigen::MatrixX3d eModelNormal;
};

// 暂时不用
// class subModel{
// public:
//     subModel();
//     ~subModel();

//     int clear();
//     bool bActive;
//     QString sSubModelName;
//     QString sParent;
//     Eigen::MatrixX3d eModelVertex;
//     Eigen::MatrixX3d eModelNormal;
// };
#endif