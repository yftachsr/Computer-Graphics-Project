#include "Objects.h"

void Objects::drawObjects() {
	Table b = Table(10, 2, "woodenTexture.jpg");
	b.drawTable(20, 0, 20, true);
	Refrigerator r = Refrigerator(-45, 1, -30);
	r.draw();
	//drawCarrpet();
}


