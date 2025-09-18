#include <inttypes.h>
#include "./sound.gen.h"
#include <SFML/Audio/Sound.h>
#include <SFML/Audio.h>

int load_sound(void);

int play_sound(void); 

void free_sound(void);

static struct sfSoundBuffer* soundBuffer;
