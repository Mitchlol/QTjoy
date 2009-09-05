#ifndef ARGS_H_
#define ARGS_H_

#include <libplayerc++/playerc++.h>
#include <iostream>
#include <unistd.h>

static std::string gHostname(PlayerCc::PLAYER_HOSTNAME);
static uint32_t gPort(PlayerCc::PLAYER_PORTNUM);
static uint32_t gIndex(0);
static uint32_t gDebug(0);
static uint32_t gFrequency(10); // Hz
static uint32_t gDataMode(PLAYER_DATAMODE_PUSH);
static bool gUseLaser(false);

void
print_usage(int argc, char** argv);

int
parse_args(int argc, char** argv);

#endif /* ARGS_H_ */
