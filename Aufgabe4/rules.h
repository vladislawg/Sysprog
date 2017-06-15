#include <stdint.h>
#include <stdlib.h>

#include "thread.h"
#include "field.h"

enum field_type {FISH, SHARK, WATER};

void calculate_shark_generation(thread_args* args);

void calculate_fish_generation(thread_args* args);