#include "user.h"

void user::progress(quint16 id){
	quint16 prev{ id };

	while (exercise[id].id != exercise[prev].id) prev--;

}
