#include <CUtil.h>
#include <CStrUtil.h>

std::string
CUtil::
toString(CAngleType angle_type)
{
  if      (angle_type == CANGLE_TYPE_DEGREES)
    return "degrees";
  else if (angle_type == CANGLE_TYPE_RADIANS)
    return "radians";
  else
    return "??";
}

CAngleType
CUtil::
toAngleType(const std::string &str)
{
  if      (CStrUtil::casecmp(str, "degrees") == 0)
    return CANGLE_TYPE_DEGREES;
  else if (CStrUtil::casecmp(str, "radians") == 0)
    return CANGLE_TYPE_RADIANS;
  else
    return CANGLE_TYPE_NONE;
}

void
CUtil::
breakpoint()
{
}

void
CUtil::
decodeMask(unsigned int full_mask, unsigned int *shift, unsigned int *mask)
{
  *shift = 0;

  while (! (full_mask & 0x0001)) {
    full_mask >>= 1;

    (*shift)++;
  }

  *mask = full_mask;
}

void
CUtil::
decodeMask(unsigned short full_mask, unsigned short *shift, unsigned short *mask)
{
  *shift = 0;

  while (! (full_mask & 0x0001)) {
    full_mask >>= 1;

    (*shift)++;
  }

  *mask = full_mask;
}
