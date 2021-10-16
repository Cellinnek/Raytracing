#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)



float player_pos_x = 40;
float player_pos_y = 40;
float player_pos_z = 100;
float size = 120;
float speed = 200;


internal void
simulate_game(Input* input, float dt) {
	cube1.set(player_pos_y, (player_pos_y + size), player_pos_x, (player_pos_x + size), player_pos_z, (player_pos_z + size));
	clear_screen(00000000);	
	
	MultiRayTracing();

	if (is_down(BUTTON_RIGHT)) player_pos_x -= speed * dt;
	if (is_down(BUTTON_LEFT)) player_pos_x += speed * dt;
	if (is_down(BUTTON_UP)) player_pos_z -= speed * dt;
	if (is_down(BUTTON_DOWN)) player_pos_z += speed * dt;
	if (is_down(BUTTON_SPACE)) player_pos_y -= speed * dt;
	if (is_down(BUTTON_SHIFT)) player_pos_y += speed * dt;
	/*float speed = 50.f; 
	if (is_down(BUTTON_UP)) player_pos_y += speed*dt;
	if (is_down(BUTTON_DOWN)) player_pos_y -= speed * dt;
	if (is_down(BUTTON_RIGHT)) player_pos_x += speed * dt;
	if (is_down(BUTTON_LEFT)) player_pos_x -= speed * dt;


	draw_rect(player_pos_x, player_pos_y, 1, 1, 0xff0000);
	draw_rect(30, 50, 5, 5, 0x222222);*/
}