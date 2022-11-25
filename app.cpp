#include "src/render.cuh"
#include "src/io.cuh"
#include "src/intersection.cuh"
#include "src/bvh.cuh"
#include "src/random.cuh"

#include <iostream>
#include <string>
#include <cstdio>

int main(int argc, char* argv[]) {
  int width = 1024;
  int height = 1024;
  int spp = 1;

  std::string obj_infile{ "data/fireplace_room.obj" };
  std::string ppm_outfile{ "output.ppm" };
  if (argc > 1) {
	int which = 0;
	for (int i = 1; i < argc; i++) {
	  if (strcmp(argv[i], "-f") == 0)
		which = 1;
	  else if (strcmp(argv[i], "-x") == 0)
		which = 2;
	  else if (strcmp(argv[i], "-y") == 0)
		which = 3;
	  else if (strcmp(argv[i], "-s") == 0)
		which = 4;
	  else if (strcmp(argv[i], "-h") == 0) {
		return 0;
	  } else if (which) {
		switch (which) {
		case 1:
		  obj_infile = argv[i];
		  break;
		case 2:
		  width = atoi(argv[i]);
		  break;
		case 3:
		  height = atoi(argv[i]);
		  break;
		case 4:
		  spp = atoi(argv[i]);
		  break;
		}
		which = 0;
	  }
	}
  }

  printf("Loading file %s.\n", obj_infile.c_str());
  printf("Rendering with width %d, height %d, spp %d\n", width, height, spp);

  float vfov = 0.79f;
  float aspect = (float)width / (float)height;

  Vec3 look_from{ 5.03f, 0.91f, -2.20f };
  Vec3 look_at{ -0.21f, 0.83f, -0.34f };
  // Vec3 look_from(0.f, 1.0f, 3.5f);
  // Vec3 look_at(0.f, 1.0f, -1.f);

  Vec3 view_up{ 0.f, 1.f, 0.f };

  Scene s;
  load_obj(obj_infile, &s);
  s.cam = Camera(vfov, aspect, look_from, look_at, view_up);

  RenderParams params = { spp };

  Image im(width, height);

  render(params, s, im);

  write_ppm(ppm_outfile, im);

  return 0;
}
