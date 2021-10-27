#include <vector>
#include <math.h>
#include <thread>
#define PI 3.14159265

double render_distance = 2000;
double huj = 200;
global_variable double cx=0, cy=0, cz=0;
double s = 4;
int w = gw / s;
int h = gh / s;
int moves = 200;
double ls = 10;
double cube_x = 40;
double cube_y = 40;
double cube_z = 100;
double cube_size = 120;
double angle = 20;
int angle_change_z = 0;
int angle_change_x = 0;

class Ray {
public:
	double x, y, z, r_z_angle, r_x_angle;
	void move() {
		x += sin((r_z_angle + angle_change_z) * PI / 180) * ls;
		y += sin((r_x_angle + angle_change_x) * PI / 180) * ls;
		z += cos((r_z_angle + angle_change_z) * PI / 180) * ls;
		if (sqrt(sqrt((x-huj) * (x - huj) + (y - huj) * (y - huj)) * (sqrt((x - huj) * (x - huj) + (y - huj) * (y - huj))) + z * z) > render_distance) {
			x = cx;
			y = cy;
			z = cz;
		}
		//if (z-cz > render_distance) {
		//	x = cx;
		//	y = cy;
		//	z = cz;
		//}
	}
	void set(double a, double b, double c, double d, double e) {
		x = a;
		y = b;
		z = c;
		r_z_angle = d;
		r_x_angle = e;
	}
	void reset() {
		x = cx;
		y = cy;
		z = cz;
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


internal void
InitRays() {
	cube1.set(cube_y, (cube_y + cube_size), cube_x, (cube_x + cube_size), cube_z, (cube_z + cube_size));
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			ray[y * w + x].set(
				0,
				0,
				0,
				(((double)x - w / 2) / w) * 2 * angle,
				(((double)y - h / 2) / h) * 2 * angle);
		}
	}
}

bool
Colision(double yp, double xp) {
	double x = ray[yp * w + xp].x;
	double y = ray[yp * w + xp].y;
	double z = ray[yp * w + xp].z;

	if( x >= cube1.ax &&
		x <= cube1.bx &&
		y >= cube1.ay &&
		y <= cube1.by &&
		z >= cube1.az &&
		z <= cube1.bz) return true;
	if (
		sqrt(
			(x*x + y*y)
			+z*z) < 50) return true;
	return false;
	
}

void
RayTrace(u32 color, double stry, double strx, double bruh) {
	for (double y = stry; y < render_state.height/s; y += bruh) {
		for (double x = strx; x < render_state.width/s; x += bruh) {
			for (int i = 0; i <= moves; i++) {
				ray[y * w + x].move();
				if (Colision(y, x)) {
					draw_rect(x*s,y*s,x*s+s,y*s+s,color);
					ray[y * w + x].reset();
					break;
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