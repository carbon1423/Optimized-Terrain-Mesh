#pragma once

#include "stb_perlin.h"

class HeightGen {
  public:
    int octaves;
    float lacunarity;
    float gain;
    float scale;

    HeightGen(int oct, float lac, float g, float s = 32.0f){
      octaves = oct;
      lacunarity = lac;
      gain = g;
      scale = s;
    }
    float get_height(int x, int z){
      float nx = (float)x / scale; 
      float nz = (float)z / scale;

      float frequency = 1.0f;
      float amp = 1.0f;
      float sum = 0.0f;
      for(int i = 0; i < octaves; i++){
        sum += stb_perlin_noise3_seed(x * frequency, 0, z * frequency, 0, 0, 0, 0) * amp;
        frequency *= lacunarity;
        amp *= gain;
      }
      return sum;
    }
};
