#define COLOR_INDEX_TO_RGBA(p, i) (p)->rgba[(i)]
#define RGBA_COMPOSE(rgba, r, g, b, a) \
	(rgba)->r = r, (rgba)->g = g, (rgba)->b = b, (rgba)->a = a
#define RGBA_DECOMPOSE(rgba, r, g, b, a) \
	(r) = (rgba)->r, (g) = (rgba)->g, (b) = (rgba)->b, (a) = (rgba)->a
#define COLOR_RGBA_TO_R(rgba) (rgba)->r
#define COLOR_RGBA_TO_G(rgba) (rgba)->g
#define COLOR_RGBA_TO_B(rgba) (rgba)->b
#define COLOR_RGBA_TO_A(rgba) (rgba)->a

struct rgba_t
{
	unsigned char r, g, b, a;
};

struct palette_t
{
	int n;
	struct rgba_t rgbad[1];
};

struct palette_t *color_palette_new(int n, const char *descr);
void color_palette_delete(struct palette_t *p);
struct palette_t *color_palette_set(int i, struct rgba_t *rgba);
struct palette_t *color_palette_get(int i, struct rgba_t *rgba);
struct palette_t *color_c64_palette();

#ifdef SHOOT64_DEBUG
void color_debug(struct palette_t *p);
#endif

