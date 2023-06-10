#define INITGUID

#include <iostream>
#include <string>
#include <filesystem>
#include <sstream>
#include <locale>
#include <codecvt>
#include <direct.h>
#include <shlobj.h>
#include <knownfolders.h>

using namespace std;
using convert_type = codecvt_utf8<wchar_t>;
namespace fs = filesystem;

class extractor
{
    private:
        wchar_t* localAppdataPath;
        wchar_t* desktopPath;
        wstringstream preparedPath;
        wstringstream preparedDesktopPath;
    public:
        extractor();
        ~extractor();
        void loadAppdataPath();
        void loadDesktopPath();
        void createDestinationFolder(string path);
        void copyFilesToDestination(string fromPath, string toPath);
        wstringstream preparePath();
        wstringstream prepareDesktopPath();
        string getPreparedPathString();
        string getDesktopPathString();
};

extractor::extractor(){
    localAppdataPath = 0;
    desktopPath = 0;
    loadAppdataPath(); loadDesktopPath();
    preparedPath = preparePath();
    preparedDesktopPath = prepareDesktopPath();
}

extractor::~extractor(){

}

void extractor::loadAppdataPath(){
    if(SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &localAppdataPath) == S_OK){
        cout << "\nSuccesfully obtained user AppData\\Local\\ path." << endl;
    } else {
        cout << "\nERROR: Unable to obtain user AppData\\Local\\ path." << endl;
        exit(1);
    }
}

void extractor::loadDesktopPath(){
    if(SHGetKnownFolderPath(FOLDERID_Desktop, 0, NULL, &desktopPath) == S_OK){
        cout << "\nSuccesfully obtained user Desktop\\ path." << endl;
    } else {
        cout << "\nERROR: Unable to obtain user Desktop\\ path." << endl;
        exit(1);
    }
}


wstringstream extractor::preparePath(){
    wstringstream path; 
    path << localAppdataPath << "\\Packages\\Microsoft.Windows.ContentDeliveryManager_cw5n1h2txyewy\\LocalState\\Assets";
    return path;
}

wstringstream extractor::prepareDesktopPath(){
    wstringstream path; 
    path << desktopPath << "\\LockScreenImgs";
    return path;
}

string extractor::getPreparedPathString(){
    wstring path = preparedPath.str();
    wstring_convert<convert_type, wchar_t> converter;
    string converted_path = converter.to_bytes(path);
    return converted_path;
}


string extractor::getDesktopPathString(){
    wstring path = preparedDesktopPath.str();
    wstring_convert<convert_type, wchar_t> converter;
    string converted_path = converter.to_bytes(path);
    return converted_path;
}


void extractor::createDestinationFolder(string path){
    if(mkdir(path.c_str()) == 0){
        cout << "NEW FOLDER CREATED \"LockScreenImgs\" on your Desktop!." << endl;
    } else {
        cout << "ERROR: Folder unable to be created." << endl;
    }
}


void extractor::copyFilesToDestination(string fromPath, string toPath){
    cout << fromPath << endl;
    for (const auto & entry : fs::directory_iterator(fromPath)){
        if(entry.file_size() > 1000000){
            cout << entry.path().string() << endl;
            cout << getDesktopPathString() << endl;
            fs::copy_file(entry.path().string(), toPath);
            // STUCK :)
        }
    }
}