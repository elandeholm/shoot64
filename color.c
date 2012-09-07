#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "color.h"

struct palette_t *color_c64_palette(int n, const char *descr)
{
	const char *ws;
	char *copy, *strp, *token;
	unsigned int code;
	struct palette_t *p;
	struct rgba_t *rgbad;
	size_t size;
	
	size = n*sizeof(struct rgba_t) + sizeof(struct palette_t);
	p = malloc(size);
	p->n = n;
	color_palette_clear(p);
	
	if (descr)
	{
		// parse a palette describing string in the format
		// used by color_c64_palette()

		// the parser is quite dumb since
		// it will silently and happily ignore invalid input
	
		copy = strdup(descr);
		
		strp = copy;
		ws = " \t\r\n";
		token = strtok(&strp, ws);
		if (token != NULL)
		{
			nc = atoi(token);
			for(token = strtok(NULL, ":"); token != NULL; token = strtok(NULL, ":"))
			{
				index = atoi(token);
				if (index >= 0 && index < n)
				{
					rgbad = &p->rgbad[index];
					token = strtok(NULL, ws);
					if (token != NULL)
					{
						// accept color codes on the formats
						// RRGGBB or RRGGBBAA
						code = strtol(token, NULL, 16);
						if (code < 0x1000000)
						{
							r = (code >> 16) & 0xff; g = (code >>  8) & 0xff;
							b = (code      ) & 0xff; a = 0;
						}
						else
						{
							r = (code >> 24) & 0xff; g = (code >> 16) & 0xff;
							b = (code     8) & 0xff; a = (code      ) & 0xff;						
						}
						RGBA_COMPOSE(rgbad, r, g, b, a);
					}
				}
			}
		}
		
		free(copy);
	}
	
	return p;
}

void color_palette_clear(struct palette_t *p)
{
	memset(&p->data, 0, n*sizeof(unsigned int));
}

struct palette_t *color_c64_palette()
{
	return color_palette_new(16,
	"  0:101010" // black
	"  1:ffffff" // white
	"  2:e04040" // red
	"  3:60ffff" // cyan (cat)
	"  4:e060e0" // purple (deep)
	"  5:40e040" // green
	"  6:4040e0" // blue
	"  7:ffff40" // yellow
	"  8:e0a040" // orange
	"  9:9c7448" // brown
	" 10:ffa0a0" // l red
	" 11:545454" // d gray
	" 12:888888" // m gray
	" 13:a0ffa0" // l green
	" 14:a0a0ff" // l blue
	" 15:c0c0c0" // l gray
	);
}

void color_debug(struct palette_t *p)
{
	int i;
	unsigned int r, g, b, a;
	struct rgba_t *rgba;
	
	fprintf(stderr, "color_debug: palette with %d colors\n", p->n);
	for(i = 0; i < p->n; ++i)
	{
		rgba = COLOR_INDEX_TO_RGBA(p, i);
		RGBA_DECOMPOSE(rgba, r, g, b, a);
		fprintf(stderr, "%03d : r%02x, g%02x, b%02x, a%02x\n", i, r, g, b, a);
	}
}

