#ifndef VIOLET_LASERBULLET_H_
#define VIOLET_LASERBULLET_H_

#include "GL/gl.h"
#include "Bullet.h"

namespace violet {

class LaserBullet: public Bullet {
private:
	float Alpha;
	bool m_hit;
public:
	LaserBullet(float x, float y, float dX, float dY);
	virtual void process(int deltaTime);
	virtual void draw();
	virtual bool checkHit(Object* objRef);
};

}

#endif /* VIOLET_LASERBULLET_H_ */
