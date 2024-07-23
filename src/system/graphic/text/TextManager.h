#ifndef VIOLET_TEXTMANAGER_H_
#define VIOLET_TEXTMANAGER_H_

#include <filesystem>

#include "TextObject.h"



namespace violet {

class TextManager {
private:
	TTF_Font *m_font;
	int m_ident, m_height;
public:
	enum TextHAlignFlag {
		LEFT, CENTER, RIGHT
	};
	enum TextVAlignFlag {
		TOP, MIDDLE, BOTTOM
	};
	TextManager(std::filesystem::path fontPath, int fontSize);
	void draw(const std::string& textBuf, float x, float y, TextHAlignFlag halign,
			TextVAlignFlag valign);
	const int getHeight() const {
		return m_height;
	}
	const int getIndent() const {
		return m_ident;
	}
	TextObject* getObject(const std::string& textBuf, float x, float y,
			TextHAlignFlag halign, TextVAlignFlag valign) const;
	virtual ~TextManager();
};
}

#endif /* VIOLET_TEXTMANAGER_H_ */
