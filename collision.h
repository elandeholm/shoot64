#define COLLISION_MAX_OBJECTS 64

struct collision_t
{
	unsigned int obj1;
	unsigned int obj2;
};

struct collisionmap_t
{
	unsigned int w, h;
	size_t size;
	int ncollisions;
	struct collision_t collisions[COLLISION_MAX_OBJECTS];
	unsigned int data[1];
};

struct collision_t *collision_new(int width, int height);
void collision_clear(struct collision_t *c);
void collision_delete(struct collision_t *c);
void collision_add(unsigned int obj1_id, unsigned int obj2_id);

