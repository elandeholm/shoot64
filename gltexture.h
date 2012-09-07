#define BGRA_COMPOSE(b, g, r, a) (((b) << 24) | ((g) << 16) | ((r) << 8) | (a))

typedef unsigned int bgra_t;

struct gltexture_t
{
	unsigned int w, h;
	size_t size;
	bgra_t data[0];
}

struct gltexture_t *gltexture_new(int w, int h);
void gltexture_delete(struct gltexture_t *glt);
void gltexture_clear(struct gltexture_t *glt);

