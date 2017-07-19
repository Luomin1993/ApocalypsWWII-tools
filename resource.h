#ifndef RESOURCE_H
#define RESOURCE_H

#include <QObject>
#include <vector>
#include <map>

using namespace std;

class Resource
{
public:
    QString ResourceName;
    QString SelfPath;
    QString SelfPlayerMdlPath;
    QString SelfMapPath;
    QString SelfMapMdlPath;
    QString SelfWeaponMdlPath;
    QString SelfWeaponImgPath;
    QString SelfBkgPath;
    QString SelfAmbiencePath;
    QString SelfBotsaddPath;
    vector<QString> ResPaths;
    vector<vector<QString>> NamesVec;
    vector<QString> WeaponMdlNames;
    vector<QString> MapMdlNames;
    vector<QString> MapNames;
    vector<QString> AmbienceNames;
    vector<QString> WeaponImgNames;
    vector<QString> BkgImgNames;
    vector<QString> BotsaddFilesNames;
    map<QString,vector<QString>> PathNamesMap;
    //vector<QString> WeaponMdlNames;
    QString ResourcePath;
    Resource(QString Name);
    bool GetSelfResNames();
    void GetOneDirFileNames(QString Path,vector<QString>& Names);
    bool copyFileToPath(QString sourceDir ,QString toDir, bool coverFileIfExist);
    bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist);
    bool DelDir(const QString &path);
    bool CleanSelf(QString GameResPath);
    bool LoadSelf(QString GameResPath);
};

#endif // RESOURCE_H