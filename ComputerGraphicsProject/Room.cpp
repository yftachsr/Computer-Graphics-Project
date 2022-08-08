#include "Room.h"

Room::Room(float gridSizeX, float gridSizeY, float squareSizeX, float squareSizeY) {
	
	floor = new Floor(gridSizeX, gridSizeY, squareSizeX, squareSizeY);
	
	sizeX = gridSizeX * squareSizeX;
	sizeY = gridSizeY * squareSizeY;

	for (int i = 0; i < NUM_OF_WALLS - 1; i++) {
		if (i % 2 == 0) 
			walls[i] = new Wall(sizeX, sizeY / 2.0f, "wallTexture.jpg");
		else
			walls[i] = new Wall(sizeY, sizeY / 2.0f, "wallTexture.jpg");
	}
	
	walls[NUM_OF_WALLS - 1] = new Wall(sizeX, sizeY, "t.jpg");
	
}

void Room::draw(Robot * bipbop) {

	floor->reflection(bipbop);
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
	for (int i = 0; i < NUM_OF_WALLS - 1; i++) {
		glPushMatrix();
		if(i%2 == 0)
			glTranslatef(0, 0, sizeY / 2.0f);
		else
			glTranslatef(0, 0, sizeX / 2.0f);
		
		walls[i]->draw();
		glPopMatrix();
		glRotated(90, 0, 1, 0);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, sizeY / 2.0f, -sizeY / 2);
	glRotated(90, 1, 0, 0);
	walls[NUM_OF_WALLS - 1]->draw();
	glPopMatrix();
}

Room::~Room() {

	delete floor;
	for (int i = 0; i < 5; i++)
		delete walls[i];
}