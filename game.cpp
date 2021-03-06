#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

float speed = 200;

internal void
simulate_game(Input* input, float dt) {
	if (is_down(BUTTON_RIGHT)) {
		cx += cos((angle_change_z)*PI / 180) * speed * dt;
		cz -= sin((angle_change_z)*PI / 180) * speed * dt;
	}
	if (is_down(BUTTON_LEFT)) {
		cx -= cos((angle_change_z)*PI / 180) * speed * dt;
		cz += sin((angle_change_z)*PI / 180) * speed * dt;
	}
	if (is_down(BUTTON_UP)) {
		cx += sin((angle_change_z)*PI / 180) * speed * dt;
		cz += cos((angle_change_z)*PI / 180) * speed * dt;
	}
	if (is_down(BUTTON_DOWN)) {
		cx -= sin((angle_change_z)*PI / 180) * speed * dt;
		cz -= cos((angle_change_z)*PI / 180) * speed * dt;
	}
	if (is_down(BUTTON_SPACE)) cy += speed * dt;
	if (is_down(BUTTON_SHIFT)) cy -= speed * dt;
	if (is_down(BUTTON_A)) angle_change_z -= 30 * dt;
	if (is_down(BUTTON_D)) angle_change_z += 30 * dt;
	if (is_down(BUTTON_W)) angle_change_y += 30 * dt;
	if (is_down(BUTTON_S)) angle_change_y -= 30 * dt;
	
	MultiRayTracing();

}