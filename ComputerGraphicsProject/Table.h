#include "HeaderGL.h"
#include "Texture.h"

class Table{
private:
	int radius;
	int thickness;
	int height;
	GLUquadric *quadric;
	Texture *texture;
	void drawLeg();
	void drawSurface();
public:
	Table(int, int, std::string);
	void drawTable(int,int,int, bool);
	void drawTeapot(float, float, float);
	
};

