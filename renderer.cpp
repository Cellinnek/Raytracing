internal void 
render_background() {
	u32* pixel = (u32*)render_state.memory;
	for (int y = 0; y < render_state.height; y++) {
		for (int x = 0; x < render_state.width; x++) {
			*pixel++ = 0xff00ff * x + 0x00ff00 * y;
		}
	}
}

internal void 
clear_screen(u32 color) {
	u32* pixel = (u32*)render_state.memory;
	for (int y = 0; y < render_state.height; y++) {
		for (int x = 0; x < render_state.width; x++) {
			*pixel++ = color;
		}
	}
}

internal void
draw_rect_in_pixels(int x0, int y0, int x1, int y1, u32 color) {

	x0 = clamp(0, x0, render_state.width);
	x1 = clamp(0, x1, render_state.width);
	y0 = clamp(0, y0, render_state.height);
	y1 = clamp(0, y1, render_state.height);

	for (int y = y0; y < y1; y++) {
		u32* pixel = (u32*)render_state.memory + x0 + y * render_state.width;
		for (int x = x0; x < x1; x++) {
			*pixel++ = color;
		}
	}
}

void
draw_rect(int x0, int y0, int x1, int y1, u32 color) {
	for (int y = y0; y < y1; y++) {
		/*if (x1 + (y) * render_state.width < gh*gw) {*/
			u32* pixel = (u32*)render_state.memory + x0 + y * render_state.width;
			for (int x = x0; x < x1; x++) {
				*pixel++ = color;
			/*}*/
		}
	}
}

