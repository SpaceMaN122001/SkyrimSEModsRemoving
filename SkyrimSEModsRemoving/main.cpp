#include <QtCore/QCoreApplication>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <iostream>
#include <string>
#include <QDirIterator>
using namespace std;

bool isFilePlayable(QString fileName);
bool isFolderPlayable(QString folderName);
void showModFiles(QString pathToGame);
bool isFoldersGameSkyrim(QString pathToGame);
void removeAllMods(QString pathToGame);
void removeAllModsFolders(QString pathToGame);
int getNumberOfNonOriginalGameFiles(QString pathToGame);

int main()
{
	setlocale(LC_ALL, "rus");

	int i = 0;
	QString pathToGame = QDir::currentPath();
	QFileInfo fileInfo = pathToGame;

	if (!isFoldersGameSkyrim(pathToGame)) { cout << "Программа находиться не в корне папки скайрима!(Переместите программу в корень папки скайрим, где находиться exe игры)" << endl; system("pause"); return -1; }

	if (getNumberOfNonOriginalGameFiles(pathToGame) == 0) { cout << "Моды не обнаружены!" << endl; system("pause"); return 0;}

	showModFiles(pathToGame);
	system("cls");

	cout << "Вы хотите удалить все моды? (Y - да, N - нет)" << endl;
	string question = "";
	cin >> question;

	if (question != "Y" && question != "N") exit(-1);
	if (question == "N") exit(0);
	if (question == "Y") {

		removeAllMods(pathToGame); 
		removeAllModsFolders(pathToGame + "\\" + "Data");
		removeAllModsFolders(pathToGame + "\\" + "Data" + "\\" + "ShaderCache");
		removeAllModsFolders(pathToGame + "\\" + "Data" + "\\" + "Video");
		removeAllModsFolders(pathToGame);
	}

	system("cls");
	cout << "Завершенно!" << endl;

	system("pause");
	return 0;
}

int getNumberOfNonOriginalGameFiles(QString pathToGame)
{
	QDirIterator it(pathToGame, QDirIterator::Subdirectories);
	int i = 0;

	while (it.hasNext()) {
		QFileInfo file = it.next();

		if (file.fileName() != ".." && file.fileName() != "." && file.suffix() != nullptr) {

			if (!isFilePlayable(file.fileName())) i++;
		}

		if (file.fileName() != ".." && file.fileName() != "." && file.suffix() == nullptr) {

			if (!isFolderPlayable(file.fileName())) i++;
		}
	}

	return i;
}

bool isFoldersGameSkyrim(QString pathToGame)
{
	QDir dir(pathToGame);
	QFileInfoList fileList = dir.entryInfoList();

	foreach(QFileInfo file, fileList)
	{
		if (file.fileName() != ".." && file.fileName() != "." && file.suffix() != nullptr) {

			if (file.fileName() == "SkyrimSE.exe" || file.fileName() == "SkyrimSELauncher.exe") return true;
		}
	}

	return false;
}

void showModFiles(QString pathToGame)
{
	QDirIterator it(pathToGame, QDirIterator::Subdirectories);

	while (it.hasNext()) {
		QFileInfo file = it.next();

		if (file.fileName() != ".." && file.fileName() != "." && file.suffix() != nullptr) {

			if (!isFilePlayable(file.fileName())) {

				cout << file.absoluteFilePath().toUtf8().constData() << endl;
			}
		}
		else if (file.fileName() != ".." && file.fileName() != "." && file.suffix() == nullptr) {

			if (!isFolderPlayable(file.fileName())) {

				cout << file.absoluteFilePath().toUtf8().constData() << endl;
			}
		}
	}
}

void removeAllMods(QString pathToGame)
{
	QDirIterator it(pathToGame, QDirIterator::Subdirectories);

	while (it.hasNext()) {
		QFileInfo file = it.next();

		if (file.fileName() != ".." && file.fileName() != "." && file.suffix() != nullptr) {

			if (!isFilePlayable(file.fileName())) {

				cout << file.absoluteFilePath().toUtf8().constData() << endl;
				
				QFile qFile(file.absoluteFilePath());
				qFile.open(QIODevice::ReadWrite);
				qFile.setPermissions(QFile::ReadOther | QFile::WriteOther);
				qFile.remove();
				qFile.close();
			}
		}
	}
}

void removeAllModsFolders(QString pathToGame)
{
	QDir dir(pathToGame);
	QFileInfoList fileList = dir.entryInfoList();

	foreach(QFileInfo file, fileList)
	{
		if (file.fileName() != ".." && file.fileName() != "." && file.suffix() == nullptr) {

			if (!isFolderPlayable(file.fileName())) {

				cout << file.absoluteFilePath().toUtf8().constData() << endl;
				QDir dir(file.absoluteFilePath());
				dir.removeRecursively();
			}
		}
	}
}

bool isFilePlayable(QString fileName)
{
	const int filesCount = 44;
	QString skyrimFilesArray[filesCount] =
	{
		"binkw64.dll",
		"gpu.txt",
		"high.ini",
		"installscript.vdf",
		"low.ini",
		"medium.ini",
		"Skyrim.ccc",
		"Skyrim_Default.ini",
		"SkyrimSE.cdx",
		"SkyrimSE.exe",
		"SkyrimSELauncher.exe",
		"steam_api64.cdx",
		"steam_api64.dll",
		"steam_emu.ini",
		"ultra.ini",
		"unins000.dat",
		"unins000.exe",
		"Dawnguard.esm",
		"Dragonborn.esm",
		"HearthFires.esm",
		"Skyrim - Animations.bsa",
		"Skyrim - Interface.bsa",
		"Skyrim - Meshes0.bsa",
		"Skyrim - Meshes1.bsa",
		"Skyrim - Misc.bsa",
		"Skyrim - Patch.bsa",
		"Skyrim - Shaders.bsa",
		"Skyrim - Sounds.bsa",
		"Skyrim - Textures0.bsa",
		"Skyrim - Textures1.bsa",
		"Skyrim - Textures2.bsa",
		"Skyrim - Textures3.bsa",
		"Skyrim - Textures4.bsa",
		"Skyrim - Textures5.bsa",
		"Skyrim - Textures6.bsa",
		"Skyrim - Textures7.bsa",
		"Skyrim - Textures8.bsa",
		"Skyrim - Voices_ru0.bsa",
		"Skyrim.esm",
		"Update.esm",
		"SkyrimSEModsRemoving.exe",
		"Qt5Cored.dll",
		"SkyrimPrefs.ini",
		"BGS_Logo.bik"
	};

	for (int i = 0; i < filesCount; i++) {

		if (fileName == skyrimFilesArray[i]) {

			return true;
		}
	}

	return false;
}

bool isFolderPlayable(QString folderName)
{
	const int foldersCount = 5;
	QString skyrimFoldersArray[foldersCount] =
	{
		"Data",
		"Creations",
		"Skyrim",
		"ShaderCache",
		"Video"
	};

	for (int i = 0; i < foldersCount; i++) {

		if (folderName == skyrimFoldersArray[i]) {

			return true;
		}
	}

	return false;
}
