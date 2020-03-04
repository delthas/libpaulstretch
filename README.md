# libpaulstretch [![builds.sr.ht status](https://builds.sr.ht/~delthas/libpaulstretch.svg)](https://builds.sr.ht/~delthas/libpaulstretch)

A tiny & portable C11 implementation of the [Paulstretch](https://github.com/paulnasca/paulstretch_cpp) extreme audio stretching algorithm.

Paulstretch is originally a GUI program developed by Nasca Octavian Paul. This library was rewritten from scratch to offer the same audio stretching capabilities, in a lightweight C library.

## Building

Depends on FFTW3.

```
meson build/
ninja -C build/
```

## Usage

See [`include/paulstretch.h`](include/paulstretch.h) and [`example/simple.c`](examples/simple.c) for an example.

The general idea is:
```c
double stretch_factor = 10.0;
double buffer_duration = 0.25;
size_t window_size = buffer_duration * 44100;
paulstretch ps = paulstretch_create(stretch_factor, window_size);

float *in = malloc(window_size * sizeof(float));
while(true) {
  // read <window_size> float audio samples into in ...
  paulstretch_write(ps, in);
  float *out;
  while(paulstretch_read(ps, &out)) {
    // use the <window_size> stretched audio samples from out ...
  }
}

free(in);
paulstretch_destroy(ps);
```

## Features

The original Paulstretch GUI program has several additional features: onset detection, custom harmonics, pitch shift, frequency shift, octave mixer, ...

This library focuses on the core of the algorithm: sound stretching, without onset detection, much like the Paulstretch plugin for Audacity.

## License

MIT
