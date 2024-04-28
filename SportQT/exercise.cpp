#include "exercise.h"

exercise::exercise(QString img_path, QString desc, QVector<QString> type, QString type2)
	: img_path(img_path), desc(desc), type(type), type2(type2) {
	time = QDateTime::currentDateTime();
}
