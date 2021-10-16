#include <vector>
#include <math.h>
#include <thread>

int render_distance = 1000;
int huj = 90;

class Ray {
public:
	float x, y, z, xs, ys, zs, strx,stry,strz;
	void move() {
		x += xs;
		y += ys;
		z += zs;
		/*if (sqrt(sqrt((x-huj) * (x - huj) + (y - huj) * (y - huj)) * (sqrt((x - huj) * (x - huj) + (y - huj) * (y - huj))) + z * z) > render_distance) {
			x = strx;
			y = stry;
			z = strz;
		}*/
		if (z > render_distance) {
			x = strx;
			y = stry;
			z = strz;
		}
	}
	void set(float a, float b, float c, float d, float e, float f) {
		x = a;
		y = b;
		z = c;
		strx = a;
		stry = b;
		strz = c;
		xs = d;
		ys = e;
		zs = f;
	}
	void reset() {
		x = strx;
		y = stry;
		z = strz;
	}
};

class Cube {
public:
	float ax, bx, ay, by, az, bz;
	void set(float a, float b, float c, float d, float e, float f) {
		ax = a;
		bx = b;
		ay = c;
		by = d;
		az = e;
		bz = f;
	}
	void move(float xs, float ys, float zs) {
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
	float x, y, z, r;
	
	void set(float a,float b,float c,float d) {
		x = a;
		y = b;
		z = c;
		r = d;
	}
};

int s = 3;
int w = gw / s;
int h = gh / s;
int moves = 100;
int ls = 10;
Cube cube1;
std::vector<Ray> ray(w* h);



internal void
InitRays() {
	for (double y = 0; y < w; y ++) {
		for (double x = 0; x < h; x ++) {
			ray[y*w+x].set(y,
				x,
				0,
				(2*ls*(y-h/2) / h),
				(2 * ls*(x - w / 2) / w),
				ls);
		}
	}
}


bool
Colision(float y, float x) {
	if (ray[y * w + x].x >= cube1.ax && 
		ray[y * w + x].x <= cube1.bx && 
		ray[y * w + x].y >= cube1.ay && 
		ray[y * w + x].y <= cube1.by && 
		ray[y * w + x].z >= cube1.az && 
		ray[y * w + x].z <= cube1.bz) return true;
	else return false;
	
}

void
RayTrace(u32 color, float stry,float strx, float bruh) {
	for (float y = stry; y < render_state.height/s; y += bruh) {
		for (float x = strx; x < render_state.width/s; x += bruh) {
			for (int i = 0; i <= moves; i++) {
				ray[y * w + x].move();
				/*u32* pixel = (u32*)render_state.memory + (int)x + (int)y * render_state.width;*/
				if (Colision(y, x)) {
					draw_rect(x*s,y*s,x*s+s,y*s+s,color);
					/**pixel++ = color;*/
					ray[y * w + x].reset();
					break;
				}
				/*else draw_rect(x * s, y * s, x * s + s, y * s + s, 00000000);*/
				
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