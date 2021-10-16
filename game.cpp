#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

float speed = 100;

internal void
simulate_game(Input* input, float dt) {
	
	clear_screen(00000000);	
	
	if (is_down(BUTTON_RIGHT)) cy += speed * dt;
	if (is_down(BUTTON_LEFT)) cy -= speed * dt;
	if (is_down(BUTTON_UP)) cz += speed * dt;
	if (is_down(BUTTON_DOWN)) cz -= speed * dt;
	if (is_down(BUTTON_SPACE)) cx += speed * dt;
	if (is_down(BUTTON_SHIFT)) cx -= speed * dt;

	MultiRayTracing();

}