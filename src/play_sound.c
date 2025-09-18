#include "play_sound.h"

#include <unistd.h>

sfSound *sound;

int load_sound(void) {
  soundBuffer = sfSoundBuffer_createFromMemory(soundWavData, SOUND_WAVDATA_LEN);
  if (!soundBuffer) {
    return -1;
  }
  return 0;
}

int play_sound(void) {
  sfTime duration = sfSoundBuffer_getDuration(soundBuffer);

  sound = sfSound_create();
  sfSound_setBuffer(sound, soundBuffer);
  sfSound_setLoop(sound, sfFalse);

  for (int i = 0; i < 3; i++) {
    sfSound_play(sound);
    usleep(duration.microseconds + (duration.microseconds >> 1));
    sfSound_stop(sound);
  }

  return 0;
}

void free_sound(void) {
  sfSound_destroy(sound);
  sfSoundBuffer_destroy(soundBuffer);
}
