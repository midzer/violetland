#include <iostream>
#include <sys/stat.h>
#include <cstdlib>

#include "FileUtility.h"





/**
 * All paths on windows are relative to the application's executable path.
 * 
 * @param argvZero The application's executable path is normally given as first
 *     argument of `argv' to `main'. The content of this value is expected to be
 *     given as argument
 * 
 * @return Initialized FileUtility instance for Windows
 */
violet::FileUtility* violet::FileUtility::ofWindows(char const* argvZero) {
	std::filesystem::path const executable = argvZero;
	std::filesystem::path const directoryOfExecutable = executable.parent_path();
	
	return new FileUtility(directoryOfExecutable, directoryOfExecutable);
}





/**
 * On UNIX the path of game resources are system defined on build tyem and user
 * content will reside in `.config/violetland' relative to the user's home
 * directory.
 *
 * @return Initialized FileUtility instance for UNIX
 */
#if defined(__linux__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__EMSCRIPTEN__)
violet::FileUtility* violet::FileUtility::ofUnix() {
	
	/* Application binary
	 */
#ifndef INSTALL_PREFIX
#define INSTALL_PREFIX "/usr/local";
#endif //INSTALL_PREFIX
	std::filesystem::path application = INSTALL_PREFIX;
	application /= "bin";
	
	
	/* Application resources
	 */
    std::filesystem::path resources;
#ifndef DATA_INSTALL_DIR
    resources = application / "../share/violetland";
#else //DATA_INSTALL_DIR
	resources = DATA_INSTALL_DIR;
#endif //DATA_INSTALL_DIR
	
	
	/* User data
	 */
	std::filesystem::path user = getenv("HOME");
	user /= ".config";
	mkdir(user.string().c_str(), S_IRWXU | S_IRGRP | S_IROTH);
	user /= "violetland";
	mkdir(user.string().c_str(), S_IRWXU | S_IRGRP | S_IROTH);
	
	
	return new FileUtility(resources, user);
}
#endif





void violet::FileUtility::traceResPath() {
	std::cout << "Path to resources is set to:" << std::endl;
	std::cout << '\t' << m_resPath << std::endl;
	std::cout << "To change the path use -r <path> key" << std::endl;
}





/**
 * Will create a FileUtility instance depending on the defined OS environment
 * 
 * @param argv[0] of main
 * @return Initialized FileUtility instance for actual OS environment
 */
violet::FileUtility* violet::FileUtility::ofOs(char const* argvZero) {
	
	/* Windows
	 */
#if defined(_WIN32)
	return FileUtility::ofWindows(argvZero);
#elif defined(__linux__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__EMSCRIPTEN__)
	return FileUtility::ofUnix();
#else
	#error Missing environment specification
#endif
}





/**
 * Constructor
 * 
 * @param resources Path to game resources (common to all users)
 * @param user Path to user resources
 */
violet::FileUtility::FileUtility(
			const std::filesystem::path& resources,
			const std::filesystem::path& user
		) :	m_resPath(resources),
			m_usrPath(user) {
	
	traceResPath();
}



/**
 * Changes game resource path
 * 
 * @param path New path to game resources
 */
void violet::FileUtility::setResourcePath(std::filesystem::path const& path) {
	m_resPath = path;
	traceResPath();
}



unsigned int violet::FileUtility::getFilesCountFromDir(std::filesystem::path dir)  {
	unsigned int count = 0;
	std::filesystem::directory_iterator dir_it(dir);

	while (dir_it != std::filesystem::directory_iterator()) {
		if (std::filesystem::is_regular_file(*dir_it))
			++count;
		++dir_it;
	}
	return count;
}

std::vector<std::string> violet::FileUtility::getFilesFromDir(std::filesystem::path dir) {
	std::vector<std::string> files;
	std::filesystem::directory_iterator dir_it(dir);

	while (dir_it != std::filesystem::directory_iterator()) {
		if (std::filesystem::is_regular_file(*dir_it)) {
			files.push_back(dir_it->path().filename().string());
		}
		++dir_it;
	}
	return files;
}

std::vector<std::string> violet::FileUtility::getSubDirsFromDir(std::filesystem::path dir) {
	std::vector<std::string> subDirs;
	std::filesystem::directory_iterator dir_it(dir);

	while (dir_it != std::filesystem::directory_iterator()) {
		if (std::filesystem::is_directory(*dir_it))
			if (dir_it->path().filename().string()[0] != '.')
				subDirs.push_back(dir_it->path().filename().string());
		++dir_it;
	}
	return subDirs;
}

unsigned int violet::FileUtility::getSubDirsCountFromDir(std::filesystem::path dir) {
	std::filesystem::directory_iterator dir_it(dir);
	unsigned int count = 0;

	while (dir_it != std::filesystem::directory_iterator()) {
		if (std::filesystem::is_directory(*dir_it))
			if (dir_it->path().filename().string()[0] != '.')
				++count;
		++dir_it;
	}
	return count;
}



std::filesystem::path violet::FileUtility::getFullPath(PathType type, std::string resource) const {
	std::filesystem::path path(m_resPath);
	std::filesystem::path usrPath(m_usrPath);

	switch (type) {
	case FileUtility::image:
		path /= "images";
		return path /= resource;
	case FileUtility::anima:
		path /= "images";
		path /= "anima";
		return path /= resource;
	case FileUtility::sound:
		path /= "sounds";
		return path /= resource;
	case FileUtility::music:
		path /= "music";
		return path /= resource;
	case FileUtility::monsters:
		path /= "monsters";
		return path /= resource;
	case FileUtility::weapon:
		path /= "weapon";
		return path /= resource;
	case FileUtility::user:
		return usrPath /= resource;
	default:
		return path /= resource;
	}
}
