#include <stdbool.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <float.h>


#define HEIGHT 50
#define WIDTH 50
#define PPM_SCALAR 25
#define SAMPLE_SIZE 100
#define BIAS 10.0
typedef float Layer[HEIGHT][WIDTH];

void layer_save_as_ppm(Layer layer, const char *file_path) 
{
		float min = FLT_MAX;
		float max = FLT_MIN;
		for (int y = 0; y < HEIGHT-1; y++) {
				for (int x = 0; x < WIDTH-1; x++) {
						if (layer[y][x] < min) min = layer[y][x];
						if (layer[y][x] > max) max = layer[y][x];
				}
		}
		FILE *f = fopen(file_path, "wb");
		if (f == NULL){
				fprintf(stderr, "ERROR: could not open file %s: %m\n", file_path);
				exit(1);
		}

 		fprintf(f, "P6\n%d %d 255\n", WIDTH * PPM_SCALAR, HEIGHT * PPM_SCALAR);
		
		for (int y = 0; y < HEIGHT * PPM_SCALAR; y++) {
				for (int x = 0; x < WIDTH * PPM_SCALAR; x++) {
						float s = (layer[y / PPM_SCALAR][x / PPM_SCALAR] - min) / (max - min);

						char pixel[3] = {
								(char) floorf(255*(1.0f - s)),
								(char) floorf(255*s),
								0
						};

						fwrite(pixel, sizeof(pixel), 1, f);
				}
		}	

		fclose(f);
}

void layer_save_as_bin(Layer layer, const char *file_path)
{
		FILE *f = fopen(file_path, "wb");
		if (f == NULL) {
				fprintf(stderr, "ERROR: could not open file as %s: %m", file_path);
				exit(1);
		}

		fwrite(layer, sizeof(Layer), 1, f); // size of the type not the parameter.


		fclose(f);

}

//void layer_load_load_bin(Layer layer, const char *file_path)
//{
//		assert(0 && "TODO: layer_save_as_bin is not implemented yet!");
//}
//
static int clampi(int x, int min, int max) 
{
		if (x < min) x = min;
		if (x > max) x = max;
		return x;
}

void layer_fill_rect(Layer layer, int x, int y, int w, int h, float value)
{
		assert(w > 0);
		assert(h > 0);
		int x0 = clampi(x, 0, WIDTH-1);
		int y0 = clampi(y, 0, HEIGHT-1);
		int x1 = clampi(x0 + w - 1, 0, WIDTH-1);
		int y1 = clampi(y0 + h - 1, 0, HEIGHT-1);

		for (int xi = x0; xi <= x1; xi++)
		{
				for (int yi = y0; yi <= y1; yi++)
				{
						layer[xi][yi] = value;
				}
		}
}

void layer_fill_circle(Layer layer, int cx, int cy, int r, float value) 
{
	assert(r > 0);
	int x0 = clampi(cx - r, 0, WIDTH-1);
	int y0 = clampi(cy - r, 0, HEIGHT-1);
	int x1 = clampi(cx + r, 0, WIDTH-1);
	int y1 = clampi(cy + r, 0, HEIGHT-1);

	for (int y = y0; y < y1; y++) {
			for (int x = x0; x < x1; x++) {
					int dx = x - cx;
					int dy = y - cy;
					if (dx*dx + dy*dy <= r*r) {
							layer[y][x] = value;
					}
			}
	}
}

float fit_forward(Layer inputs, Layer weights)
{
		float output = 0.0f;

		for (int y = 0; y < HEIGHT; y++)
		{
				for (int x = 0; x < WIDTH; x++)
				{
						output += inputs[y][x] * weights[y][x];
				}
		}
		return output;
}

void excite_weights(Layer inputs, Layer weights)
{
		for (int y = 0; y < HEIGHT; y++){
				for (int x = 0; x < WIDTH; x++) 
				{
						weights[y][x] += inputs[y][x];
				}
		}
}

void supress_weights(Layer inputs, Layer weights)
{
		for (int y = 0; y < HEIGHT; y++){
				for (int x = 0; x < WIDTH; x++) 
				{
						weights[y][x] -= inputs[y][x];
				}
		}
}

int rand_range(int low, int high)
{
		assert(low < high);
		return rand() % (high - low) + low;
}

void layer_random_rect(Layer layer) 
{

		layer_fill_rect(layer, 0, 0, WIDTH, HEIGHT, 0.0f);
		int x = rand_range(0, WIDTH);
		int y = rand_range(0, HEIGHT);
		
		int w = WIDTH-x;
		if (w < 2) w = 2;
		w = rand_range(1, w);

		int h = HEIGHT-y;
		if (h < 2) h = 2;
		h = rand_range(1, h);

		layer_fill_rect(layer, x, y, w, h, 1.0f);
}

void layer_random_circle(Layer layer)
{
		layer_fill_rect(layer, 0, 0, WIDTH, HEIGHT, 0.0f);
		int cx = rand_range(0, WIDTH);
		int cy = rand_range(0, HEIGHT);
		int r = INT_MAX;
		if (r > cx) r = cx;
		if (r > cy) r = cy;
		if (r > WIDTH - cx) r = WIDTH - cx;
		if (r > HEIGHT - cy) r = HEIGHT - cy;
		if (r < 2) r = 2;
		r = rand_range(1, r);
		layer_fill_circle(layer, cx, cy, r, 1.0f);
}

bool pass_train(Layer inputs, Layer weights)
{
	bool done = true;

	for (int i = 0; i < SAMPLE_SIZE; i++) {
			layer_random_rect(inputs);
			if (fit_forward(inputs, weights) > BIAS) 
			{
					supress_weights(inputs, weights);
					done = false;
			}

			layer_random_circle(inputs);
			if (fit_forward(inputs, weights) < BIAS) 
			{
					excite_weights(inputs, weights);
					done = false;
			}

	}
	return done;
}
static Layer inputs;
static Layer weights;
int main() {

	int epoch = 0;
	while (!pass_train(inputs, weights)){
			srand(69);
			printf("training on epoch: %d\n", epoch);
			if (epoch == 3000) {
					break;
			}
			epoch ++;
			continue;
	}
	layer_save_as_ppm(weights, "weights.ppm");
	return 0;
}
