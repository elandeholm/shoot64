typedef struct bytemap_t
{
	unsigned int w, h;
	int x, y;
	size_t size;
	struct palette_t *p;
	unsigned char data[1];
};

struct bytemap_t *bytemap_new(int w, int h, int id);
void bytemap_delete(struct bytemap_t *bm);
void bytemap_clear(struct bytemap_t *bm);
void bytemap_goto(struct bytemap_t, int x, int y);
void bytemap_palette(struct bytemap_t *bm, struct palette_t *p);
void bytemap_cdraw(struct bytemap *dest, struct bytemap_t *src,
									unsigned int object_id, unsigned int collmask, struct collision_t *c);
void bytemap_draw(struct bytemap_t *dest, struct bytemap_t *src);
void bytemap_render(struct bytemap_t *bm, struct gltexture_t *glt);

