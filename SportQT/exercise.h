#include <qimage.h>
#include <QDateTime>
#include "approach.h"

struct exercise{
	quint16 id;

	QString img_path;
	QString desc;
	QVector<QString> type; //мышцs
	QString type2; //упор
	QDateTime time;

	QVector<approach> approach;

	exercise(QString, QString, QVector<QString>, QString);
};

