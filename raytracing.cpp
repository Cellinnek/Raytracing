#include <vector>
#include <math.h>
#include <thread>
#include <stdlib.h> 
#define PI 3.14159265

double render_distance = 2000;
//double huj = 1000;
double cx = 0;
double cy = 0;
double cz = 0;
int s = 5;
int w = gw / s;
int h = gh / s;
double ls = 5;
int moves = 5;
int moves2 = 5;
double cube_x = -100;
double cube_y = 60;
double cube_z = 200;
double cube_size = 500;
double cube2_size = 75;
double angle = 26.5;
float angle_change_z = 0;
float angle_change_y = 0;

class Ray {
public:
	double a, b, e, x, y, z, s_r_z_angle, s_r_y_angle, r_z_angle, r_y_angle, hx, hy, hz; 
	u32 color;
	bool move() {
		x += sin((b) * PI / 180) * cos((a)*PI / 180) * ls;
		y += sin((a) * PI / 180) * ls;
		z += cos((b) * PI / 180) * cos((a)*PI / 180) * ls;

		if (sqrt((x-cx) * (x - cx) + (y - cy) * (y - cy) + (z- cz) * (z-cz)) > render_distance) {
			x = cx;
			y = cy;
			z = cz;
			a = (r_y_angle + angle_change_y);
			b = (r_z_angle + angle_change_z);
			return false;
		}
		return true;
		
	}
	void set(/*double a, double b, double c,*/ double d, double e) {
		//x = a;
		//y = b;
		//z = c;
		r_z_angle = d;
		r_y_angle = e;
		s_r_z_angle = d;
		s_r_y_angle = e;

	}
	void reset() {
		r_z_angle = s_r_z_angle;
		r_y_angle = s_r_y_angle;
		x = cx;
		y = cy;
		z = cz;
		/*hx = 0; hy = 0; hz = 0; hx2 = 0; hz2 = 0; hy2 = 0;*/
		a = (r_y_angle + angle_change_y);
		b = (r_z_angle + angle_change_z);
	}
	void hit() {
		
		hx = x;
		hy = y;
		hz = z;
	}
};

class Cube {
public:
	double ax, bx, ay, by, az, bz;
	void set(double a, double b, double c, double d, double e, double f) {
		ax = a;
		bx = b;
		ay = c;
		by = d;
		az = e;
		bz = f;
	}
	void move(double xs, double ys, double zs) {
		ax += xs;
		bx += xs;
		ay += ys;
		by += ys;
		az += zs;
		bz += zs;
	}
};
class Sphere {
public:
	double x, y, z, r;
	
	void set(double a, double b, double c, double d) {
		x = a;
		y = b;
		z = c;
		r = d;
	}
};


std::vector<Ray> ray(w* h);
Cube cube1;
Cube cube2;

internal void
InitRays() {
	cube1.set(cube_y, (cube_y + cube_size)-480, cube_x, (cube_x + cube_size), cube_z, (cube_z + cube_size));
	cube2.set(cube_y+50, (cube_y + cube2_size)+50 , cube_x+50, (cube_x + cube2_size)+50, cube_z+150, (cube_z + cube2_size)+150);
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			ray[y * w + x].set(
				//0,
				//0,
				//0,
				(((double)x - w / 2) / w) * 2 * angle, // x i z || xz = ls*cos(konta yegoweho) || x = xz*cos(tego konta) z = xz*sin(tego konta)
				(((double)y - h / 2) / h) * 2 * angle); // y i xz || y = ls*sin(tego konta)
		}
	}
}

bool
Colision(double yp, double xp) {
	double x = ray[yp * w + xp].x;
	double y = ray[yp * w + xp].y;
	double z = ray[yp * w + xp].z;

	if(x >= cube1.ax &&
	x <= cube1.bx &&
	y >= cube1.ay &&
	y <= cube1.by &&
	z >= cube1.az &&
	z <= cube1.bz) {
		ray[yp * w + xp].hit();
		if (yp * w + xp - 1 > -1) {
			float c = atan2((ray[yp * w + xp].hx- ray[yp * w + xp-1].hx), ray[yp * w + xp - 1].hz - (ray[yp * w + xp].hz - ray[yp * w + xp - 1].hz));
			/*float d = atan2((ray[yp * w + xp].hy - ray[yp * w + xp - 1].hy), ray[yp * w + xp - 1].hx - (ray[yp * w + xp].hx - ray[yp * w + xp - 1].hz));*/
			ray[yp * w + xp].b = (2*c/PI*180)- ray[yp * w + xp].b;
			/*ray[yp * w + xp].a = (2 * d / PI * 180) - ray[yp * w + xp].a;*/

			
		}
			return false;
			
	}

	if (x >= cube2.ax &&
		x <= cube2.bx &&
		y >= cube2.ay &&
		y <= cube2.by &&
		z >= cube2.az &&
		z <= cube2.bz) {
		ray[yp * w + xp].color = 0x945094;
		return true;
	}
	
	if (sqrt((x * x + y * y) + (z - 500) * (z - 500)) < 50) {
		ray[yp * w + xp].color = 0x507065;
		return true;
	}
	if (y <= -200 && y >= -205 && (((int)(x + 2000) % 100 >= 50 || (int)(z + 2000) % 100 >= 50) && !((int)(x + 2000) % 100 >= 50 && (int)(z + 2000) % 100 >= 50))) {
		ray[yp * w + xp].color = 0xffffdf;
		return true;
	}
	return false;
	
	
}

//void
//RayTrace(u32 color, int stry, int strx, double bruh) {
//	for (int y = stry; y < render_state.height/s; y += bruh) {
//		for (int x = strx; x < render_state.width/s; x += bruh) {
//			for (int i = 0; i <= moves; i++) {
//				if (Colision(y, x)) {
//					draw_rect(x*s,y*s,x*s+s,y*s+s,color);
//					
//					ray[y * w + x].reset();
//					break;
//				}
//				ray[y * w + x].move();
//			}
//		}
//	}
//}

void
RayTrace(u32 color, int stry, int strx, int bruh) {
	for (int i = 0; i <= moves; i++) {
		for (int y = stry; y < render_state.height / s; y += bruh) {
			for (int x = strx; x < render_state.width / s; x += bruh) {
				for (int j = 0; j <= moves2; j++) {
					if (Colision(y, x)) {
						draw_rect(x * s, y * s, x * s + s, y * s + s, ray[y * w + x].color);
						ray[y * w + x].reset();
						break;
					}
					/*else draw_rect(x * s, y * s, x * s + s, y * s + s, 00000000);*/
					if (!ray[y * w + x].move()) draw_rect(x * s, y * s, x * s + s, y * s + s, 00000000);
				}
			}
		}
	}
}

internal void
MultiRayTracing() {
	std::thread ray0(RayTrace, 0xffffff, 0, 0, 4);
	std::thread ray1(RayTrace, 0xffffff, 0, 1, 4);
	std::thread ray2(RayTrace, 0xffffff, 0, 2, 4);
	std::thread ray3(RayTrace, 0xffffff, 0, 3, 4);
	std::thread ray4(RayTrace, 0xffffff, 1, 0, 4);
	std::thread ray5(RayTrace, 0xffffff, 1, 1, 4);
	std::thread ray6(RayTrace, 0xffffff, 1, 2, 4);
	std::thread ray7(RayTrace, 0xffffff, 1, 3, 4);
	std::thread ray8(RayTrace, 0xffffff, 2, 0, 4);
	std::thread ray9(RayTrace, 0xffffff, 2, 1, 4);
	std::thread ray10(RayTrace, 0xffffff, 2, 2, 4);
	std::thread ray11(RayTrace, 0xffffff, 2, 3, 4);
	std::thread ray12(RayTrace, 0xffffff, 3, 0, 4);
	std::thread ray13(RayTrace, 0xffffff, 3, 1, 4);
	std::thread ray14(RayTrace, 0xffffff, 3, 2, 4);
	std::thread ray15(RayTrace, 0xffffff, 3, 3, 4);

	ray0.join();
	ray1.join();
	ray2.join();
	ray3.join();
	ray4.join();
	ray5.join();
	ray6.join();
	ray7.join();
	ray8.join();
	ray9.join();
	ray10.join();
	ray11.join();
	ray12.join();
	ray13.join();
	ray14.join();
	ray15.join();
}