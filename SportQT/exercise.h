#include <qimage.h>
#include "approach.h"

struct exercise{
	quint16 id;

	QImage img;
	QString desc;
	QVector<QString> type; //����s
	QString type2; //����

	QVector<approach> approach;
};

