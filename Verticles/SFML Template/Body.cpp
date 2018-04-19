#include "Body.h"

b2Vec2 Body::m_getPosition()
{
	return b2Vec2(m_body->GetPosition().x, m_body->GetPosition().y);
}

float Body::m_fGetRotation()
{
	return m_body->GetAngle();
}

float Body::m_fGetRadius()
{
	return m_fRadius;
}

b2Vec2 Body::getSize()
{
	return m_size;
}

void Body::onCollisionEnter(Body * otherBody)
{
}

void Body::onCollisionExit(Body * otherBody)
{
}



/*!	Sets the friction, density and restitution of this dynamic body. Must be called before
setting up the dynamic body.*/
void Body::m_setAttributes(float fDensity, float fFriction, float fRestitution)
{
	m_fDensity = fDensity;
	m_fFriction = fFriction;
	m_fRestitution = fRestitution;
}

/*! The function that sets up the fixture, shape and body of this class. It should be called from one of the
more shape specific setupBodyAs* functions.*/
void Body::m_setupBody(b2BodyType bodyType, const b2Shape* shape, b2Vec2 position, float fRotation, b2World * world, void * self, bool isSensor)
{
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;

	bodyDef.type = bodyType;

	bodyDef.position.Set(position.x, position.y);

	bodyDef.angle = fRotation * DEG2RAD; //Set body rotation to fRotation in radians.
	
	m_body = world->CreateBody(&bodyDef);
	m_body->SetUserData(self);

	fixtureDef.shape = shape;

	m_bIsSensor = isSensor;

	if (isSensor)
	{
		fixtureDef.isSensor = true;
	}
	else
	{
		fixtureDef.density = m_fDensity;
		fixtureDef.friction = m_fFriction;
		fixtureDef.restitution = m_fRestitution;
	}

	m_body->CreateFixture(&fixtureDef);

	
}

/*! Sets up this body as a box.*/
void Body::m_setupBodyAsBox(b2BodyType bodyType, b2Vec2 position, b2Vec2 size, float fRotation, b2World * world, void * self, bool isSensor)
{
	b2PolygonShape boxShape = b2PolygonShape();
	boxShape.SetAsBox(size.x * 0.5f, size.y * 0.5f);
	boxShape.m_radius = 0.05f;
	m_size = size;

	m_setupBody(bodyType, &boxShape, position, fRotation, world, self, isSensor);
}

/*! Sets up this body as a circle.*/
void Body::m_setupBodyAsCircle(b2BodyType bodyType, b2Vec2 position, float fRadius, b2World * world, void * self, bool isSensor)
{
	b2CircleShape circleShape = b2CircleShape();
	circleShape.m_radius = fRadius;
	m_fRadius = fRadius;
	

	m_setupBody(bodyType, &circleShape, position, 0.0f, world, self, isSensor);
}

void Body::m_setTag(std::string tag)
{
	m_tag = tag;
}


