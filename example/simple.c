#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "paulstretch.h"

int main(int argc, char *argv[]) {
  if(argc != 3) {
    fprintf(stderr, "usage: %s <input.raw> <output.raw>\n", argv[0]);
    return 1;
  }
  
  int exit_code = 0;
  
  // stretch the audio ten times
  double stretch_factor = 10.0;
  
  // a good default buffer_duration for most music is 0.25 seconds
  double buffer_duration = 0.25;
  // multiply by the sample rate to get the buffer size in samples
  size_t window_size = buffer_duration * 44100;
  
  paulstretch ps = paulstretch_create(stretch_factor, window_size);
  
  // we'll write input data window_size samples at a time
  float *in = malloc(window_size * sizeof(float));
  
  // for this example we use raw files because using audio codecs is not relevant
  // to generate the input file: `ffmpeg -i input.file -f f32le -c:a pcm_f32le input.raw`
  // ^ (actually this strangely messes up the volume, i used audacity instead (export as raw)
  // to generate the output file: `ffmpeg -i output.raw -c:a <codec> output.file`
  
  FILE *input_file = fopen(argv[1], "rb");
  if(!input_file) {
    exit_code = 1;
    perror("fopen input file for reading");
    goto error_paulstretch;
  }
  
  FILE *output_file = fopen(argv[2], "wb");
  if(!output_file) {
    exit_code = 1;
    perror("fopen output file for writing");
    goto error_sample;
  }

  while(true) {
    // read input data into the input buffer
    if(fread(in, sizeof(float), window_size, input_file) != window_size) {
      break;
    }
    // write this input data (window_size samples) to paulstretch
    paulstretch_write(ps, in);
  
    // this pointer will be set to the output data, an array of window_size samples
    float *out;
    // while output stretched audio samples are available:
    // get the stretched audio data from paulstretch, writing the array address into out
    while(paulstretch_read(ps, &out)) {
      // write the stretched audio to the output file
      if(fwrite(out, sizeof(float), window_size, output_file) != window_size) {
        exit_code = 1;
        perror("fwrite to output file");
        goto error_stretched;
      }
    }
  }
  
error_stretched:
  fclose(output_file);
error_sample:
  fclose(input_file);
error_paulstretch:
  free(in);
  paulstretch_destroy(ps);
  
  return exit_code;
}
