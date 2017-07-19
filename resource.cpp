#include "resource.h"
#include <QDir>
#include <QTextCodec>
#include <QFileInfoList>
#include <QFileInfo>
#include <QCoreApplication>

Resource::Resource(QString Name)
{
	ResourceName = Name;
    SelfPath          = "/"+Name;
	SelfMapPath       = "/maps";
	SelfPlayerMdlPath = "/player";
	SelfMapMdlPath    = "/map";
	SelfWeaponMdlPath = "/models";
	SelfWeaponImgPath = "/gfx/vgui/clsImages";
	SelfBkgPath       = "/resource";
	SelfAmbiencePath  = "/sound/ambience";
	SelfBotsaddPath   = "/shrikebot/config";
    //ResPaths.push_back(SelfMapPath);
    //ResPaths.push_back(SelfPlayerMdlPath);
    //ResPaths.push_back(SelfMapMdlPath);
	ResPaths.push_back(SelfWeaponMdlPath);
	ResPaths.push_back(SelfWeaponImgPath);
    //ResPaths.push_back(SelfBkgPath);
    ResPaths.push_back(SelfBotsaddPath);
    ResPaths.push_back(SelfAmbiencePath);

	NamesVec.push_back(WeaponMdlNames);
	NamesVec.push_back(WeaponImgNames);
	NamesVec.push_back(MapMdlNames);
	NamesVec.push_back(MapNames);
	NamesVec.push_back(BkgImgNames);
	NamesVec.push_back(AmbienceNames);

	//PathNamesMap[SelfMapPath]       = MapNames;
	//PathNamesMap[SelfMapMdlPath]    = MapMdlNames;
	PathNamesMap[SelfWeaponMdlPath] = WeaponMdlNames;
	PathNamesMap[SelfWeaponImgPath] = WeaponImgNames;
	//PathNamesMap[SelfBkgPath]       = BkgImgNames;
	PathNamesMap[SelfBotsaddPath]   = BotsaddFilesNames;
	PathNamesMap[SelfAmbiencePath]  = AmbienceNames;
}

void Resource::GetOneDirFileNames(QString Path,vector<QString>& Names)
{
    QString absolutePath = QCoreApplication::applicationDirPath();
	QDir dir(absolutePath+Path);
	const QFileInfoList list = dir.entryInfoList();
    QFileInfoList::const_iterator iter = list.begin()+2;
	while(iter!=list.end())
	{
        QString fileName = (*iter).fileName();
        Names.push_back(fileName);
        iter++;
	}
}


bool Resource::GetSelfResNames()
{
    GetOneDirFileNames(SelfPath+SelfWeaponMdlPath,WeaponMdlNames);
    GetOneDirFileNames(SelfPath+SelfWeaponImgPath,WeaponImgNames);
	//GetOneDirFileNames(SelfMapMdlPath,MapMdlNames);
	//GetOneDirFileNames(SelfMapPath,MapNames);
	//GetOneDirFileNames(SelfBkgPath,BkgImgNames);
    GetOneDirFileNames(SelfPath+SelfBotsaddPath,BotsaddFilesNames);
    GetOneDirFileNames(SelfPath+SelfAmbiencePath,AmbienceNames);

    PathNamesMap[SelfWeaponMdlPath] = WeaponMdlNames;
	PathNamesMap[SelfWeaponImgPath] = WeaponImgNames;
	//PathNamesMap[SelfBkgPath]       = BkgImgNames;
	PathNamesMap[SelfBotsaddPath]   = BotsaddFilesNames;
	PathNamesMap[SelfAmbiencePath]  = AmbienceNames;
	return true;
}
/*vector<QString> Resource::GetOneDirDirNames(QString Path)
{

}*/

bool Resource::copyFileToPath(QString sourceDir ,QString toDir, bool coverFileIfExist)  
{  
    toDir.replace("\\","/");  
    if (sourceDir == toDir){  
        return true;  
    }  
    if (!QFile::exists(sourceDir)){  
        return false;  
    }  
    QDir *createfile     = new QDir;  
    bool exist = createfile->exists(toDir);  
    if (exist){  
        if(coverFileIfExist){  
            createfile->remove(toDir);  
        }  
    }//end if  
  
    if(!QFile::copy(sourceDir, toDir))  
    {  
        return false;  
    }  
    return true;  
}  

bool Resource::copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist)  
{  
    QDir sourceDir(fromDir);  
    QDir targetDir(toDir);  
    if(!targetDir.exists()){    /**< 如果目标目录不存在，则进行创建 */  
        if(!targetDir.mkdir(targetDir.absolutePath()))  
            return false;  
    }  
  
    QFileInfoList fileInfoList = sourceDir.entryInfoList();  
    foreach(QFileInfo fileInfo, fileInfoList){  
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")  
            continue;  
  
        if(fileInfo.isDir()){    /**< 当为目录时，递归的进行copy */  
            if(!copyDirectoryFiles(fileInfo.filePath(),   
                targetDir.filePath(fileInfo.fileName()),  
                coverFileIfExist))  
                return false;  
        }  
        else{            /**< 当允许覆盖操作时，将旧文件进行删除操作 */  
            if(coverFileIfExist && targetDir.exists(fileInfo.fileName())){  
                targetDir.remove(fileInfo.fileName());   
            }  
  
            /// 进行文件copy  
            if(!QFile::copy(fileInfo.filePath(),   
                targetDir.filePath(fileInfo.fileName()))){  
                    return false;     
            }  
        }  
    }  
    return true;  
}  

/*bool Resource::LoadSelf(QString GameResPath)
{
	vector<vector<QString>>::const_iterator iter = NamesVec.begin();
	while(iter!=NamesVec.end())
	{
		vector<QString>::const_iterator iterThis = (*iter).begin();
		while(iterThis!=(*iter).end())
		{
			copyFileToPath(*iterThis,*(PathNamesMap.find(*iter)),true);
		}
	} 
	return true;
}*/

bool Resource::LoadSelf(QString GameResPath)
{
	//map<QString,vector<QString>>::const_iterator iter = PathNamesMap.begin();
	QString absolutePath = QCoreApplication::applicationDirPath();
	vector<QString>::const_iterator iter = ResPaths.begin();
	while(iter!=ResPaths.end())
	{
        //vector<QString> NamesVec = (*(PathNamesMap.find(*iter))).second;
        vector<QString> NamesVec = PathNamesMap[*iter];
        vector<QString>::const_iterator iterThis = NamesVec.begin();
		while(iterThis!=NamesVec.end())
		{
            QString rsPath = ResourceName+*iter+"/"+*iterThis;
            bool isSuc = copyFileToPath(absolutePath+"/"+rsPath,absolutePath+"/dod"+*iter+"/"+*iterThis,true);
			iterThis++;
		}
		iter++;
	}
    copyDirectoryFiles(absolutePath+"/"+ResourceName+SelfMapPath,absolutePath+"/dod/maps",true);
    copyDirectoryFiles(absolutePath+"/"+ResourceName+SelfMapMdlPath,absolutePath+"/dod/models/map",true);
    copyDirectoryFiles(absolutePath+"/"+ResourceName+SelfPlayerMdlPath,absolutePath+"/dod/models/player",true);
    copyDirectoryFiles(absolutePath+"/"+ResourceName+SelfBkgPath,absolutePath+"/dod/resource",true);
    copyFileToPath(absolutePath+"/"+ResourceName+"/media/gamestartup.mp3",absolutePath+"/dod/media/gamestartup.mp3",true);
	return true;
}

bool Resource::DelDir(const QString &path)  
{  
    if (path.isEmpty()){  
        return false;  
    }  
    QDir dir(path);  
    if(!dir.exists()){  
        return true;  
    }  
    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot); //设置过滤  
    QFileInfoList fileList = dir.entryInfoList(); // 获取所有的文件信息  
    foreach (QFileInfo file, fileList){ //遍历文件信息  
        if (file.isFile()){ // 是文件，删除  
            file.dir().remove(file.fileName());  
        }else{ // 递归删除  
            DelDir(file.absoluteFilePath());  
        }  
    }  
    return dir.rmpath(dir.absolutePath()); // 删除文件夹  
}  


bool Resource::CleanSelf(QString GameResPath)
{
	QString absolutePath = QCoreApplication::applicationDirPath();
	vector<QString>::const_iterator iter = ResPaths.begin();
	while(iter!=ResPaths.end())
	{
        //vector<QString> NamesVec = (*(PathNamesMap.find(*iter))).second;
        vector<QString> NamesVec = PathNamesMap[*iter];
        vector<QString>::const_iterator iterThis = NamesVec.begin();
		while(iterThis!=NamesVec.end())
		{
            QString rsPath = 'dod'+*iter+"/"+*iterThis;
            QFile::remove(absolutePath+"/"+rsPath);
			iterThis++;
		}
		iter++;
	}
	DelDir(absolutePath+"/dod/maps");
	DelDir(absolutePath+"/dod/models/map");
	DelDir(absolutePath+"/dod/models/player");
	DelDir(absolutePath+"/dod/resource");
	QFile::remove("dod/media/gamestartup.mp3"); 
	return true;
}
