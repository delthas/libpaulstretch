#ifndef PAULSTRETCH_H
#define PAULSTRETCH_H

#include <stdbool.h>
#include <unistd.h>

/*
 * A pointer to an opaque Paulstretch instance.
 */
typedef struct paulstretch *paulstretch;

/*
 * Initialize a Paulstretch instance.
 *
 * stretch_factor is the stretching factor for the audio.
 * A stretch factor of 10 on 1 second of audio would produce approximately 10 seconds of audio.
 * stretch_factor must be greater than or equal to 1.0.
 *
 * window_size is the size (in samples) of the window used for stretching the audio.
 * In internally corresponds to the size of the FFT run on parts of the song.
 * It is also the size of all buffers (in samples) read and written to this Paulstretch instance.
 * A window size corresponding to 0.25 seconds works best for most music.
 * Larger values can also be used to "smear" a sound into a texture.
 * window_size should be greater than or equal to 128.
 *
 * Call paulstretch_destroy to free the instance after use.
 */
paulstretch paulstretch_create(double stretch_factor, size_t window_size);

/*
 * Frees this Paulstretch instance.
 *
 * This must be called exactly once per instance.
 */
void paulstretch_destroy(paulstretch ps);

/*
 * Writes input audio samples into the Paulstretch instance.
 *
 * samples is an array of <window_size> samples.
 * Each sample is a float with native endianness.
 * After each call to this function, you must call paulstretch_read repeateadly until it returns false.
 */
void paulstretch_write(paulstretch ps, float *samples);

/*
 * Reads stretched audio samples from the Paulstretch instance.
 *
 * samples is an pointer to an "out" array of samples
 * If samples are available, samples will be set to the address of an array of <window_size> stretched audio samples.
 * Each sample is a float with native endianness.
 * The array set in samples is valid until the next call to any paulstretch function on this instance.
 *
 * This function returns true when samples are available and samples was set, otherwise false.
 */
bool paulstretch_read(paulstretch ps, float **samples);

#endif
