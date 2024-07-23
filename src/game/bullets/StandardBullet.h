#ifndef VIOLET_STANDARDBULLET_H_
#define VIOLET_STANDARDBULLET_H_

#include "GL/gl.h"
#include "Bullet.h"

namespace violet {

class StandardBullet: public Bullet {
private:
	float Alpha;
	float prevX, prevY;
	bool m_explosive;
public:
	StandardBullet(float x, float y, float dX, float dY, bool explosive);
	bool isExplosive();
	virtual void process(int deltaTime);
	virtual void draw();
	virtual bool checkHit(Object* objRef);
};

}

#endif /* VIOLET_STANDARDBULLET_H_ */
