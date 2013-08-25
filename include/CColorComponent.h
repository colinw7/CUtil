#ifndef CCOLOR_COMPONENT_H
#define CCOLOR_COMPONENT_H

enum CColorComponent {
  CCOLOR_COMPONENT_NONE =0,
  CCOLOR_COMPONENT_RED  =(1<<0),
  CCOLOR_COMPONENT_GREEN=(1<<1),
  CCOLOR_COMPONENT_BLUE =(1<<2),
  CCOLOR_COMPONENT_ALPHA=(1<<3)
};

#endif