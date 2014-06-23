#include <qstring.h>
#include <qdom.h>
#include "xmlutils.h"

QString XMLUtils::attributeValue(const QDomElement &root, const QString &tag, const QString &attr, unsigned int index)
{

	QString str;

	QDomElement el = XMLUtils::childWithTag(root, tag, index);

	if (el.isNull()) return QString::null;
	
	return el.attribute(attr);

}

QDomElement XMLUtils::childWithTag(const QDomElement &root, const QString &tag, unsigned int index)
{

	QDomNodeList list;
	QDomElement el;
	register unsigned int i, curpos;

	list = root.childNodes();
	curpos = 0;

	for (i = 0; i < list.count(); i++) {
		el = list.item(i).toElement();
		if (el.isNull()) continue;
		if (el.tagName() == tag) {
			if (curpos == index) return el;
			curpos++;
		}
	}

	QDomElement null;
	return null;
}


