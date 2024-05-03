#include <qimage.h>
#include <QDateTime>
#include "approach.h"

struct exercise{
	quint16 id;

	QVector<approach> approach;

	exercise(quint16);
};

