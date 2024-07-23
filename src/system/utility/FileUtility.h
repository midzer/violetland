#ifndef VIOLET_FILEUTILITY_H_
#define VIOLET_FILEUTILITY_H_

#include <filesystem>
#include <string>
#include <vector>



namespace violet {

class FileUtility {
private:
	std::filesystem::path m_resPath;
	std::filesystem::path m_usrPath;
	
	static FileUtility* ofWindows(char const* argvZero);
	static FileUtility* ofUnix();
	
	void traceResPath();
	
	
public:
	enum PathType {
		common = 0,
		image,
		anima,
		sound,
		music,
		monsters,
		weapon,
		user
	};
	
	
	static FileUtility* ofOs(char const* argvZero);
	
	
	static unsigned int getFilesCountFromDir(std::filesystem::path dir);
	static unsigned int getSubDirsCountFromDir(std::filesystem::path dir);
	static std::vector<std::string> getFilesFromDir(std::filesystem::path dir);
	static std::vector<std::string> getSubDirsFromDir(std::filesystem::path dir);
	
	
	FileUtility(	std::filesystem::path const& resources,
			std::filesystem::path const& user);

	void setResourcePath(std::filesystem::path const& path);
	std::filesystem::path getFullPath(PathType type, std::string resource) const;
};
}

#endif /* VIOLET_FILEUTILITY_H_ */
