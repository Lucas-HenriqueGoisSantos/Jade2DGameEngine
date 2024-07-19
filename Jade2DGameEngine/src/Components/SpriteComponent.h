#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H


struct SpriteComponent {

	int width;
	int height;

	SpriteComponent( int width, int height ) {
		
		this->width = width;
		this->height = height;
	}
};

#endif