#ifndef AUDIO_DRIVER_H
#define AUDIO_DRIVER_H
#include <memory>
#include <vector>

typedef std::unique_ptr<std::vector<bool>> uptr_dv_t;

uptr_dv_t audio_driver();

#endif
