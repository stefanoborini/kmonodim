#ifndef PALETTE_H
#define PALETTE_H

#include <qintdict.h>
#include <qobject.h>

class QDomElement;
class Color;


class Palette : public QObject {
Q_OBJECT;
public:
	Palette(QObject *parent = NULL, const char *name = 0);
	
	inline unsigned int size() const { return m_colors.count(); }
	void resetChanged();
	unsigned int modifiedColors();

	void reportChanges();
	
	Color color( unsigned int index ) const;
	void setColor ( unsigned int index, const Color &col);

	bool changed(unsigned int index) const;
	
signals:
	void signalChanged();
	
protected:
	QIntDict<Color> m_colors;
	QMap<unsigned int,bool> m_changed;

};
	
#endif
