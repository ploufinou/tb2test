#define TB_IMPL
#include "termbox.h"

#define WALL	'#'
#define	ME	'@'
#define	SPACE	' '

typedef struct {
	int x, y;
} pos_t;

int main() {
    struct tb_event ev;
    pos_t me = { 10, 10};
    int i;

    tb_init();
    tb_printf(0, 0, 0, 0, "Arrows to move, ESC to exit, Left mouse button to teleport");
    for (i = 0; i < tb_width(); i++) {
	    tb_set_cell(i, 1, WALL, TB_GREEN, 0);
	    tb_set_cell(i, tb_height() - 2, WALL, TB_GREEN, 0);
    }
    
    for (i = 1; i < tb_height() - 1; i++) {
	    tb_set_cell(0, i, WALL, TB_GREEN, 0);
	    tb_set_cell(tb_width() - 1, i, WALL, TB_GREEN, 0);
    }

    tb_hide_cursor();
    ev.key = 0;
    tb_set_input_mode(TB_INPUT_MOUSE);
    while (ev.key != TB_KEY_ESC) {
	    tb_set_cell(me.x, me.y, ME, TB_BLUE, 0);
	    tb_present(); /* draw */
	    tb_poll_event(&ev);
	    
	    tb_set_cell(me.x, me.y, SPACE, 0, 0);

	    if (ev.type == TB_EVENT_KEY) {
		    for (i = 0; i < tb_width(); i++) tb_set_cell(i, tb_height() - 1, SPACE, 0, 0); /* clear status line */
		    switch (ev.key) {
			    case TB_KEY_ARROW_UP: 
				    if (me.y > 2) me.y--;
				    break;
			    case TB_KEY_ARROW_DOWN: 
				    if (me.y < tb_height() - 3) me.y++; 
				    break;
			    case TB_KEY_ARROW_LEFT:
				    if (me.x > 1) me.x--; 
				    break;
			    case TB_KEY_ARROW_RIGHT: 
				    if (me.x < tb_width() - 2) me.x++; 
				    break;
		    }
	    }

	    if ((ev.type == TB_EVENT_MOUSE) && (ev.key == TB_KEY_MOUSE_LEFT))  {
		    if ((ev.x >= 1) && (ev.x <= tb_width() - 2) && (ev.y >= 2) && (ev.y <= tb_height() - 3)) {
			    me.x = ev.x;
			    me.y = ev.y;
		    } else {
			    tb_printf(0, tb_height() - 1, TB_RED, 0, "Invalid position!");
		    }
	    }
    }
    tb_shutdown();
    return 0;
}
