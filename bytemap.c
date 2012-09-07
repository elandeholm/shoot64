#include <string.h>
#include <stdlib.h>
#include "bytemap.h"
#include "collision.h"
#include "color.h"
#include "gltexture.h"

// bytemapped (8 bit indexed) graphics operations

struct bytemap_t *bytemap_new(int w, int h, int id)
{
	struct bytemap_t *bm;
	size_t size;

	size = w*h;	
	bm = malloc(size+sizeof(struct bytemap_t));
	bm->w = w;
	bm->h = h;
	bm->size = size;
	bytemap_clear(bm);
	bytemap_goto(bm, 0, 0);
	
	return bm;
}

void bytemap_clear(struct bytemap_t *bm)
{
	memset(bm->data, 0, bm->size);
}

void bytemap_goto(struct bytemap_t *bm, int x, int y)
{
	bm->x = x;
	bm->y = 0;
}

// draw with collision detection

void bytemap_cdraw(struct bytemap *dest, struct bytemap_t *src,
									unsigned int obj_id, struct collinfo_t *ci);
{
	unsigned char *sd, *dd, *cd;
	int sx, sy, dx, dy;
	int sw, sh, dw, dh;
	int syw, dyw;
	unsigned int cobj_id;
	unsigned int cobj_mask;

	sw = src->w;
	sh = src->h;
	dw = dest->w;
	dh = dest->h
	syw = 0;
	dyw = 0;

	if (ci) // collision detection ON
	{
		cobj_mask = ci->obj_mask;
		for(y = 0; y < sh; ++y)
		{
			sy = y + src->y;
			dy = y + dest->y;
			if ((sy >= 0) && (sy < sh) && // vertical clipping
					(dy >= 0) && (dy < dh))
			{
				sx = src->x;
				dx = dest->x;    
				sd = &src->data[syw+sx];
				dd = &dest->data[dyw+dx];
				cd = &ci->data[dyw+dx];
				for(x = 0; x < sw; ++x, ++sx, ++dx)
				{
					if ((sx >= 0) && (sx < sw) && // horizontal clipping
							(dx >= 0) && (dx < dw))
					{
						if ((pixel = *sd)) // color index non zero means overwrite
						{
							if (!(cobj_id = *cd))
							{
								*cd = obj_id;
							}
							else if (cobj_id & cobj_mask)
							{
								collision_add(obj_id, cobj_id);
							}
							*dd = pixel;
						}
					}
					++sd;
					++dd;
					++cd;
				}
			}
			syw += sw;
			dyw += dw;
		}
	}
	else // collision detection OFF
	{
		for(y = 0; y < sh; ++y)
		{
			sy = y + src->y;
			dy = y + dest->y;
			if ((sy >= 0) && (sy < sh) && // vertical clipping
					(dy >= 0) && (dy < dh))
			{
				sx = src->x;
				dx = dest->x;    
				sd = &src->data[syw+sx];
				dd = &dest->data[dyw+dx];
				for(x = 0; x < sw; ++x, ++sx, ++dx)
				{
					if ((sx >= 0) && (sx < sw) && // horizontal clipping
							(dx >= 0) && (dx < dw))
					{
						if ((pixel = *sd)) // color index non zero means overwrite
						{
							*dd = pixel;
						}
					}
					++sd;
					++dd;
				}
			}
			syw += sw;
			dyw += dw;
		}
	}	
}

// draw without collision detection

void bytemap_draw(struct bytemap_t *dest, struct bytemap_t *src)
{
	bytemap_cdraw(dest, src, 0, NULL);
}

// transfer bytemap to gl bgra texture

void bytemap_render(struct bytemap_t *bm, struct gltexture_t *glt)
{
	rgba_t rgba;
	bgra_t *bgrad;
	
	// sanity checks
	
	assert(bm->w == glt->w);
	assert(bm->h == glt->h);	
	
	bmw = bm->w;
	bmh = bm->h;

	bmyw = 0;

	for(y = 0; y < bmh; ++y)
	{
		bmd = &bm->data[bmyw];
		bgrad = &dest->data[bmyw];
		for(x = 0; x < bmw; ++x)
		{
			if ((pixel = *sd)) // color index non zero means overwrite
			{
				rgba = COLOR_INDEX_TO_RGBA(bm->palette, pixel);
				*bgrad = BGRA_COMPOSE(COLOR_RGBA_TO_B(rgba), COLOR_RGBA_TO_G(rgba),
															COLOR_RGBA_TO_R(rgba), COLOR_RGBA_TO_A(rgba));
			}
		}
		bmyw += bmw;
	}

}
