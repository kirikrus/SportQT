#include "user.h"

QVector<double> user::progress(quint16 id){
	QVector<double> out;

	for (quint16 i{ 0 };i<exercise.size();i++)
		if (exercise[i].id == id)
			out.push_back(exercise[i].multi());

	return out;
}
