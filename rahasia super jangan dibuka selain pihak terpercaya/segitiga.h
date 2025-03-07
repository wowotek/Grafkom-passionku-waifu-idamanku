class segitiga {
private:
	const float m2p = 20; //meter to pixel
	const float p2m = 1 / m2p; //pixel to meter
	const float PI = 3.14;
public:
	b2Body* add3angle(int x, int y, float w, float h, bool dyn = true);
	void draw3angle(b2Vec2* points, b2Vec2 center, float angle);
	b2World* world;
	segitiga(b2World* world2) {
		world = world2;
	};
};

b2Body* segitiga::add3angle(int x, int y, float w, float h, bool dyn) { //add bodydef
	//create dynamic body
	b2BodyDef bodyDef;
	if (dyn == true) {
		bodyDef.type = b2_dynamicBody;
	}
	bodyDef.position.Set(x * p2m, y * p2m);
	b2Body* body = world->CreateBody(&bodyDef);

	//attach polygon using fixture def
	b2Vec2 vertices[3];
	vertices[0].Set(-w/2 * p2m, h/2 * p2m);
	vertices[1].Set(w/2 * p2m, h/2 * p2m);
	vertices[2].Set(0, -h/2 * p2m);
	int32 count = 3;

	b2PolygonShape segitiga;
	segitiga.Set(vertices, count);


	b2FixtureDef fixtureDef;
	fixtureDef.shape = &segitiga;
	fixtureDef.density = 0.5f;
	fixtureDef.friction = 0.1f;
	fixtureDef.restitution = 0.15f;
	body->CreateFixture(&fixtureDef);

	return body;
}

void segitiga::draw3angle(b2Vec2* points, b2Vec2 center, float angle) {
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(center.x * m2p, center.y * m2p, 0);
	glRotatef(angle * 180.0 / PI, 0, 0, 1);
	glBegin(GL_POLYGON);

	glVertex2f(points[0].x * m2p, points[0].y * m2p-3.5);
	glVertex2f(points[1].x * m2p, points[1].y * m2p-3.5);
	glVertex2f(points[2].x * m2p, points[2].y * m2p);

	glEnd();
	glPopMatrix();
	glFlush();
}