#ifndef MYLISTVIEWITEM_H
#define MYLISTVIEWITEM_H

#include <qlistview.h>
#include <qpainter.h>

class QString;
class QColor;

class MyListViewItem : public QListViewItem {
	public:
		MyListViewItem(QListView *parent,int dataIndex ,QString &str,const QColor &col, bool active, bool warn);
		MyListViewItem(QListViewItem *item, int dataIndex ,QString &str,const QColor &col, bool active, bool warn);
		QString	key ( int column, bool ascending ) const;
		QColor &color() { return m_color; }
		void setColor(const QColor &col) { m_color = col; listView()->repaintItem(this); }

		bool active() { return m_active; }
		void setActive(bool a) { m_active = a; listView()->repaintItem(this); }
		int getDataIndex() { return m_dataIndex; }
		
protected:
		virtual void paintCell( QPainter * p, const QColorGroup & cg, int column, int width, int align );
		virtual int width ( const QFontMetrics & fm, const QListView * lv, int c ) const;
		
		void drawColorColumn(QPainter * p, const QColorGroup & cg, int column, int width, int align );
		void drawActiveColumn(QPainter * p, const QColorGroup & cg, int column, int width, int align );	
		
		int m_dataIndex;
		QColor m_color;
		bool m_active;

};


#endif
