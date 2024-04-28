#include <qimage.h>
#include "approach.h"

struct exercise{
	quint16 id;

	QImage img;
	QString desc;
	QVector<QString> type; //мышцs
	QString type2; //упор

	QVector<approach> approach;
};

