#include <vector>
#include <math.h>z
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



//internal void
//RayCube(u32 color, int ax, int bx, int ay, int by, int az, int bz) {
//	Ray ray;
//	float s = 1;
//	float w = (render_state.width) / s / 2;
//	float h = (render_state.height) / s / 2;
//	for (float y = -h; y <= h; y += s) {
//		for (float x = -w; x <= w; x += s) {
//			ray.set(y, x, 0, 0 + (y / (h)), 0 + (x / (w)), 1);
//			for (float n = 0; n <= 1200; n++) {
//				ray.move();
//				if (ray.x >= ax && ray.x <= bx && ray.y >= ay && ray.y <= by && ray.z >= az && ray.z <= bz && !(ray.x >= ax + 25 && ray.x <= bx - 25 && ray.y >= ay + 25 && ray.y <= by - 25 && ray.z >= az && ray.z <= bz)) {
//					draw_rect((y + h) * s, (x + w) * s, (y + h) * s + 2 * s, (x + w) * s + 2 * s, color);
//					break;
//				}
//			}
//		}
//	}
//}


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






int s = 4;
int w = gw / s;
int h = gh / s;
int moves = 300;
int ls = 4;
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

internal void
RayTrace(u32 color) {
	for (float y = 0; y < render_state.height/s; y ++) {
		for (float x = 0; x < render_state.width/s; x ++) {
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


//internal void
//draw_rect(int x0, int y0, int x1, int y1, u32 color) {
//	for (int y = y0; y < y1; y++) {
//		u32* pixel = (u32*)render_state.memory + x0 + y * render_state.width;
//		for (int x = x0; x < x1; x++) {
//			*pixel++ = color;
//		}
//	}
//}