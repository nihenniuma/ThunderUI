#include "modelManagerOld.h"

ModelManager::ModelManager()
{
    // 没啥要初始化的，直接默认
}

ModelManager::~ModelManager()
{
    // 没存指针之类的东西直接默认析构
}

int ModelManager::initModel(QString sModelPath)
{
    int nret;
    QFileInfo modelFileInfo(sModelPath);
    modelInfo* model = new modelInfo();
    nret = readModelFromFile(sModelPath, *model);
    if(nret == -1){
        return -1;
    }

    QString modelName = modelFileInfo.baseName();
    nret = addModel2Map(*model, modelName);
    if(nret == -1){
        return -1;
    }
    model->iTreeWidgetItem = new QTreeWidgetItem();

    // 不需要设置名称，因为在上面加入Map的时候我们就应该要设置名称（会有重复情况）
    // nret = setModelName(*model, modelName);
    // if(nret == -1){
    //     return -1;
    // }

    // 下面有个位置的函数执行不下去
    nret = setModelActive(modelName);
    // std::cout << "nret ： " << nret << std::endl;
    if(nret == -1){
        return -1;
    }
    emit addNodeSig(modelName, model->iTreeWidgetItem);
    // std::cout << modelName.toStdString() << std::endl;
    // 将新的模型数据更新到Map里
    // 先检查数据的冗余情况
    nret = checkRedundancy(modelName);
    if(nret == -1){
        // 数据冗余，不能按照这个名字更新
        return -1;
    }
    mModelInfoMap[modelName] = *model;
    return 0;
}

// 查看该模型名称在Map中是否已存在，如果已存在同样的名字会覆盖原来的数据
int ModelManager::checkRedundancy(QString sModelName)
{
    // 存在冗余情况
    if(mModelInfoMap.find(sModelName) != mModelInfoMap.end()){
        return -1;
    }
    return 0;
}

int ModelManager::setModelName(modelInfo &model, QString sNewName)
{
    int ret = model.setModelName(sNewName);
    if(ret == -1){
        // 还没改好
    }
    return ret;
}

int ModelManager::setModelName(QString sModelName, QString sNewName)
{
    if(mModelInfoMap.find(sModelName) == mModelInfoMap.end()){
        return -1;
    }
    return setModelName(mModelInfoMap[sModelName], sNewName);
}

// int ModelManager::setSubModelName(QString sModelName)
// {
//     return 0;
// }

// int ModelManager::rotateSubModel(QString sSubModelName, Eigen::Matrix3d rotation)
// {
//     return 0;
// }

int ModelManager::rotateModelVertex(QString sModelName, Eigen::Matrix3d rotation)
{
    if(mModelInfoMap.find(sModelName) == mModelInfoMap.end()){
        return -1;
    }
    modelInfo* modelPtr = &mModelInfoMap[sModelName];
    modelPtr->eModelVertex = modelPtr->eModelVertex * rotation;
    return 0;
}

int ModelManager::rotateModelNormal(QString sModelName, Eigen::Matrix3d rotation)
{
    if(mModelInfoMap.find(sModelName) == mModelInfoMap.end()){
        return -1;
    }
    modelInfo* modelPtr = &mModelInfoMap[sModelName];
    modelPtr->eModelNormal = modelPtr->eModelNormal * rotation;
    return 0;
}

int ModelManager::setModelActive(QString sModelName)
{
    return setActiveOrDeAactive(sModelName, true);
}

// int ModelManager::setSubModelActive(QString sSubModelName)
// {
//     return 0;
// }

int ModelManager::setActiveOrDeAactive(QString sModelName, bool bIsAcitve)
{
    if(mModelInfoMap.find(sModelName) == mModelInfoMap.end()){
        return -1;
    }
    // std::cout << "??" << std::endl;
    modelInfo* modelPtr = &mModelInfoMap[sModelName];
    return bIsAcitve ? modelPtr->turnActive() : modelPtr->turnDeActive();
}

int ModelManager::setActiveOrDeAactive(QStringList sNameList, bool bIsAcitve)
{
    auto iter = sNameList.begin();
    int nret;
    for(; iter != sNameList.end(); iter++){
        QString modelName = *iter;
        nret = setActiveOrDeAactive(modelName, bIsAcitve);
        if(nret == -1){
            return -1;
        }
    }
    return 0;
}

int ModelManager::addModel2Map(modelInfo &model, QString sModelName)
{
    if(mModelInfoMap.find(sModelName) == mModelInfoMap.end()){
        mModelInfoMap.insert(sModelName, model);
    }else{
        int i = 1;
        while(mModelInfoMap.find(sModelName) != mModelInfoMap.end()){
            // 这里后面可以优化
            sModelName += '_';
            sModelName += QString(i);
            i++;
        }
    }
    return setModelName(model, sModelName);
}

int ModelManager::clearModel(QString sModelName)
{
    auto iter = mModelInfoMap.find(sModelName);
    if(iter == mModelInfoMap.end()){
        qDebug() << QString(
                    "There is no Model named %1!")
                    .arg(sModelName);
        return 0;
    }
    iter->clear();
    mModelInfoMap.erase(iter);
    qDebug() << QString(
                    "Model named %1 clear!")
                    .arg(sModelName);
    return 0;
}

// int ModelManager::clearSubModel()
// {
//     return 0;
// }

int ModelManager::readFile(QString sFilePath, modelInfo &model)
{
    // 先得到后缀名，判断是config文件还是stl
    QString suffix = sFilePath.mid(sFilePath.indexOf('.'));
    if(suffix.compare("conf", Qt::CaseInsensitive) == 0){
        readConfigFile(sFilePath, model);
    }else{
        readModelFromFile(sFilePath, model);
    }
    return 0;
}

int ModelManager::readConfigFile(QString sFilePath, modelInfo &model)
{
    return 0;
}

int ModelManager::readModelFromFile(QString sModelPath, modelInfo &model)
{
    QString log;
    std::string filePath = sModelPath.toStdString();
    int length = filePath.length();

    if (!(filePath[length-4]=='.' && filePath[length-3]=='s' && filePath[length-2]=='t' && filePath[length-1]=='l'))
    {
        log += "the file inputed isn't stl file!";
        qDebug() << log;
        return -1;
    }
    else
    {
        std::vector<Eigen::Matrix<double, 1, 3>> vertex;
        std::vector<Eigen::Matrix<double, 1, 3>> normal;
        std::ifstream in;
        in.open(filePath, std::ios::in);
        if (in.fail())
        {
            log += "file open failed!";
            qDebug() << log;
            return -1;
        }
        char buffer_f[5]; // the buffer_f used to distinguish binary stl to ASCII stl
        in.read(buffer_f, 5);
        if (buffer_f[0]=='s' && buffer_f[1]=='o' && buffer_f[2]=='l' && buffer_f[3]=='i' && buffer_f[4]=='d') // it's an ASCII file
        {
            std::string line;
            while (!in.eof())
            {
                Eigen::Matrix<double, 1, 3> temp;
                double x, y, z;
                std::getline(in, line); // facet normal x y z
                const char* c_line = line.c_str(); // transform string to const char* to put it in function sscanf()
                if(sscanf(c_line, " facet normal %lf %lf %lf", &x, &y, &z)==3)
                {
                    temp << x, y, z;
                    normal.push_back(temp);
                }
                else
                {
                    log += "error: read nromal vector";
                    qDebug() << log;
                    return -1;
                }

                std::getline(in, line); // outer loop

                for(int i : {0, 1, 2})
                {
                    std::getline(in, line); // vertex x y z
                    c_line = line.c_str(); 
                    Eigen::Matrix<double, 1, 3> vec;
                    if(sscanf(c_line, " vertex %lf %lf %lf", &x, &y, &z)==3)
                    {
                        vec << x, y, z;
                        vertex.push_back(vec);
                    }
                    else if(sscanf(c_line, " vertex %lf %lf %lf", &x, &y, &z)==0)
                    {
                        return -1;
                    }
                    else
                    {
                        log += "num of vertex less than 3, the rest vertexes of triangle is missing!";
                        qDebug() << log;
                        return -1;
                    }
                }

                std::getline(in, line); // endloop
                std::getline(in, line); // endfacet
            }
            in.close();
            log += "ASCII stl file has been loaded successfully!";
        }
        else
        {
            in.close(); // this ifstream was opened in the mode of std::ios::in, we should open it in binary
            in.open(filePath, std::ios::in | std::ios::binary);
            if (in.fail())
            {
                log += "binary stl file open failed!";
                qDebug() << log;
                return -1;
            }
            char head_c[80];
            int num = in.readsome(head_c, 80); // binary stl file has 80 bytes in the front of the file
            if (num != 80)
            {
                log +="binary stl file error occurs: less than 80 bytes!";
                qDebug() << log;
                return -1;
            }
            float buffer_f;
            int buffer_i;
            char info[2];
            in.read((char*)&buffer_i, 4); // the first 4 bytes is an unsigned int so do not use atoi
                                          // int num_facets = atoi(buffer_f); 4 bytes int store how many facets are (atoi for char to int)
            double x, y, z;
            while(!in.eof())
            {
                // normal vector
                Eigen::Matrix<double, 1, 3> temp;
                in.read((char*)&buffer_f, 4);
                x = buffer_f;
                in.read((char*)&buffer_f, 4);
                y = buffer_f;
                in.read((char*)&buffer_f, 4);
                z = buffer_f; // three float(4 bytes per float) store normal vector of this facet
                temp << x, y, z;
                normal.push_back(temp);

                // vertex1
                Eigen::Matrix<double, 1, 3> vec_1;
                in.read((char*)&buffer_f, 4);
                x = buffer_f; // three float(4 bytes per float) store coordinates of one vertex
                in.read((char*)&buffer_f, 4);
                y = buffer_f;
                in.read((char*)&buffer_f, 4);
                z = buffer_f;
                vec_1 << x, y, z;
                vertex.push_back(vec_1);

                // vertex2
                Eigen::Matrix<double, 1, 3> vec_2;
                in.read((char*)&buffer_f, 4);
                x = buffer_f; // three float(4 bytes per float) store coordinates of one vertex
                in.read((char*)&buffer_f, 4);
                y = buffer_f;
                in.read((char*)&buffer_f, 4);
                z = buffer_f;
                vec_2 << x, y, z;
                vertex.push_back(vec_2);

                //vertex3
                Eigen::Matrix<double, 1, 3> vec_3;
                in.read((char*)&buffer_f, 4);
                x = buffer_f; // three float(4 bytes per float) store coordinates of one vertex
                in.read((char*)&buffer_f, 4);
                y = buffer_f;
                in.read((char*)&buffer_f, 4);
                z = buffer_f;
                vec_3 << x, y, z;
                vertex.push_back(vec_3);

                in.read(info, 2); // two bytes store facet's info
            }
            in.close();

            log += "binary stl file has been loaded successfully!";
            log += "file path: ";
            log += QString::fromStdString(filePath);
        }
        
        // 最后把所有数据传给model
        model.eModelVertex = trans2Eigen(vertex);
        model.eModelNormal = trans2Eigen(normal);
    }
    qDebug() << log;
    return 0;
}

Eigen::MatrixX3d ModelManager::trans2Eigen(std::vector<Eigen::Matrix<double, 1, 3>> input)
{
    int rows = input.size();
    Eigen::MatrixX3d temp(rows, 3);
    for(int i = 0; i < input.size(); i++){
        for(int j : {0, 1, 2}){
            temp(i, j) = input[i][j];
        }
    }
    return temp;
}

int ModelManager::getModelInfoFromMap(QString sTargetName, modelInfo& model)
{
    if (mModelInfoMap.find(sTargetName) == mModelInfoMap.end()){
        return -1;
    }
    model = mModelInfoMap[sTargetName];
    return 0;
}

int ModelManager::isModelExist(QString sModelName)
{
    if(mModelInfoMap.find(sModelName) == mModelInfoMap.end()){
        return -1;
    }
    return 0;
}

modelInfo::modelInfo()
    : bActive(true),
    iTreeWidgetItem(nullptr)
{
}

modelInfo::~modelInfo()
{
}

int modelInfo::clear()
{
    // 这里本来是调用最下层subModel的clear的
    return 0;
}

int modelInfo::turnActive()
{
    bActive = true;
    return bActive == true ? 0 : -1;
}

int modelInfo::turnDeActive()
{
    bActive = false;
    return bActive == false ? 0 : -1;
}

int modelInfo::isActive()
{
    return bActive == true ? 0 : -1;
}

int modelInfo::setModelName(QString sNewName)
{
    sModelName = sNewName;
    return 0;
}

QString modelInfo::getModelName()
{
    return sModelName;
}

// subModel::subModel()
// {
// }

// subModel::~subModel()
// {
// }

// int subModel::clear()
// {
//     return 0;
// }
