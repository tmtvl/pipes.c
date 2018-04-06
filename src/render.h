#ifndef RENDER_H_
#define RENDER_H_
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include "pipe.h"

enum COLOR_ERRS {
    ERR_CURSES_ERR = -1,
    ERR_TOO_MANY_COLORS = -2,
    ERR_CANNOT_CHANGE_COLOR = -3,
    ERR_NO_COLOR = -4,
    ERR_OUT_OF_MEMORY = -5,
    ERR_QUERY_UNSUPPORTED = -6
};

struct palette {
    uint32_t *colors;
    size_t num_colors;
};

struct color_backup {
    size_t num_colors;
    char **escape_codes;
};

typedef void (*anim_function)(unsigned int width, unsigned int height,
        void *data);

int init_color_palette(uint32_t *colors, size_t num_colors,
        struct palette *palette, struct color_backup *backup);

void init_colors(void);
void animate(int fps, anim_function renderer,
        unsigned int *width, unsigned int *height,
        volatile sig_atomic_t *interrupted, void *data);
void render_pipe(struct pipe *p, char **trans, char **pipe_chars,
        int old_state, int new_state);

void palette_destroy(struct palette *palette);
int create_color_backup(size_t num_colors, struct color_backup *backup);
void restore_colors(struct color_backup *backup);
void free_colors(struct color_backup *backup);

#endif //RENDER_H_
