#include <qimage.h>
#include <QDateTime>

struct exercise{
	quint16 id;
	quint16 approach_count;
	quint16 max_weight;
	quint16 repetitions;

	exercise(quint16, quint16, quint16, quint16);
	double multi();
};

