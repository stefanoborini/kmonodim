#ifndef COLOR_H
#define COLOR_H

#include <qcolor.h>

class Color : public QColor {
public:
	Color();
	Color(int r, int g, int b, bool active = true);
	Color(const QColor &col, bool active = true);
	Color(const QString &name, bool active = true);

	inline bool active() const { return m_active; }
	inline void setActive(bool a) { m_active = a; }
	inline void setColor(const QColor &col) { QColor::operator=(col); }
	
	bool operator==( const Color &c ) const;
	bool operator!=( const Color &c ) const;
	Color &operator=(const Color &col);

	static const Color null;

protected:
	bool m_active;

};

#endif
