#include <qimage.h>
#include <QDateTime>
#include "approach.h"

struct exercise{
	quint16 id;

	QString img_path;
	QString desc;
	QVector<QString> type; //����s
	QString type2; //����
	QDateTime time;

	QVector<approach> approach;

	exercise(QString, QString, QVector<QString>, QString);
};

