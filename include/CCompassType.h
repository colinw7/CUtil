#ifndef CCOMPASS_H
#define CCOMPASS_H

enum class CCompassType {
  NONE  = 0,
  NORTH = (1<<0),
  SOUTH = (1<<1),
  EAST  = (1<<2),
  WEST  = (1<<3)
};

#endif
