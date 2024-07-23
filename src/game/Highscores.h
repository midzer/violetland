#ifndef VIOLET_HIGHSCORES_H_
#define VIOLET_HIGHSCORES_H_

#include <set>

#include <filesystem>
#include <boost/filesystem/fstream.hpp>

#include "../system/utility/FileUtility.h"
#include "../system/utility/Templates.h"
#include "lifeforms/Player.h"

namespace violet {

class HighscoresEntry {
public:
	HighscoresEntry(float Strength, float Agility, float Vitality, 
			unsigned Xp, std::string Name, unsigned Time);
	HighscoresEntry(violet::Player* player, std::string Name, 
			unsigned Time);
	const float Strength;
	const float Agility;
	const float Vitality;
	const unsigned Xp;
	const std::string Name;
	const unsigned Time;
	bool operator<(const HighscoresEntry& e) const {
		return Xp < e.Xp;
	}
};

class Highscores {
	static const size_t MAX_SIZE = 10;
private:
	std::set<HighscoresEntry> m_data;
	const FileUtility* m_fileUtility;
	const std::filesystem::path hsFile;
	const std::filesystem::path hsTempFile;
public:
	Highscores(FileUtility* fileUtility);
	void clear();
	void read();
	bool isHighscore(unsigned Time);
	bool add(HighscoresEntry entry);
	
	std::set<HighscoresEntry> const& getData() const {
		return m_data;
	}
};
}

#endif /* VIOLET_HIGHSCORES_H_ */
