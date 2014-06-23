class QString;
class QDomElement;

namespace XMLUtils {

	QString attributeValue(const QDomElement &root, const QString &tag, const QString &attr, unsigned int index = 0);
	QDomElement childWithTag(const QDomElement &root, const QString &tag, unsigned int index = 0);

};
