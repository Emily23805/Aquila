#ifndef _AQUILA_FB_H
#define _AQUILA_FB_H

#include <stdint.h>

/* Framebuffer API */
#define FBIOGET_VSCREENINFO	0x4600
#define FBIOPUT_VSCREENINFO	0x4601
#define FBIOGET_FSCREENINFO	0x4602

struct fb_fix_screeninfo {
	char id[16];			/* identification string eg "TT Builtin" */
	unsigned long smem_start;	/* Start of frame buffer mem */
					/* (physical address) */
	uint32_t smem_len;			/* Length of frame buffer mem */
	uint32_t type;			/* see FB_TYPE_*		*/
	uint32_t type_aux;			/* Interleave for interleaved Planes */
	uint32_t visual;			/* see FB_VISUAL_*		*/
	uint16_t xpanstep;			/* zero if no hardware panning  */
	uint16_t ypanstep;			/* zero if no hardware panning  */
	uint16_t ywrapstep;		/* zero if no hardware ywrap    */
	uint32_t line_length;		/* length of a line in bytes    */
	unsigned long mmio_start;	/* Start of Memory Mapped I/O   */
					/* (physical address) */
	uint32_t mmio_len;			/* Length of Memory Mapped I/O  */
	uint32_t accel;			/* Indicate to driver which	*/
					/*  specific chip/card we have	*/
	uint16_t capabilities;		/* see FB_CAP_*			*/
	uint16_t reserved[2];		/* Reserved for future compatibility */
};

struct fb_bitfield {
    uint32_t offset;    /* beginning of bitfield    */
    uint32_t length;    /* length of bitfield       */
    uint32_t msb_right; /* != 0 : Most significant bit is right */
};

struct fb_var_screeninfo {
    uint32_t xres;          /* visible resolution       */
    uint32_t yres;
    uint32_t xres_virtual;  /* virtual resolution       */
    uint32_t yres_virtual;
    uint32_t xoffset;       /* offset from virtual to visible */
    uint32_t yoffset;       /* resolution           */

    uint32_t bits_per_pixel;    /* guess what           */
    uint32_t grayscale;     /* 0 = color, 1 = grayscale, >1 = FOURCC          */
    struct fb_bitfield red;     /* bitfield in fb mem if true color, */
    struct fb_bitfield green;   /* else only length is significant */
    struct fb_bitfield blue;
    struct fb_bitfield transp;  /* transparency         */

    uint32_t nonstd;            /* != 0 Non standard pixel format */

    uint32_t activate;          /* see FB_ACTIVATE_*        */

    uint32_t height;            /* height of picture in mm    */
    uint32_t width;         /* width of picture in mm     */

    uint32_t accel_flags;       /* (OBSOLETE) see fb_info.flags */

    /* Timing: All values in pixclocks, except pixclock (of course) */
    uint32_t pixclock;          /* pixel clock in ps (pico seconds) */
    uint32_t left_margin;       /* time from sync to picture    */
    uint32_t right_margin;      /* time from picture to sync    */
    uint32_t upper_margin;      /* time from sync to picture    */
    uint32_t lower_margin;
    uint32_t hsync_len;     /* length of horizontal sync    */
    uint32_t vsync_len;     /* length of vertical sync  */
    uint32_t sync;          /* see FB_SYNC_*        */
    uint32_t vmode;         /* see FB_VMODE_*       */
    uint32_t rotate;            /* angle we rotate counter clockwise */
    uint32_t colorspace;        /* colorspace for FOURCC-based modes */
    uint32_t reserved[4];       /* Reserved for future compatibility */
};

#define _RGBA(r, g, b, a) (((r) << 3*8) | ((g) << 2*8) | ((b) << 1*8) | ((a) << 0*8))
#define _RGB(r, g, b) (((r) << 3*8) | ((g) << 2*8) | ((b) << 1*8))
#define _ALPHA(c, a) (((c) & (~0xFF)) | ((a) & 0xFF))

struct aquilafb {
    struct fb_fix_screeninfo fix_screeninfo;
    struct fb_var_screeninfo var_screeninfo;
    int fd;
    void *mmap;
    unsigned xres, yres, pitch, bpp;
};

struct aquilafb_image {
    unsigned xres, yres, pitch, bpp;
    void *buf;
};

int aquilafb_init(struct aquilafb *fb, char *path);
void aquilafb_wallpaper(struct aquilafb *fb, char *backbuf, struct aquilafb_image *img);
void aquilafb_render(struct aquilafb *fb, void *backbuf);

#endif
