#ifndef ACCESSOR_H
#define ACCESSOR_H

#define ACCESSOR_DCL_GET(n,T,v) \
const T &get##n() const;

#define ACCESSOR_IMPL_GET(n,T,v) \
const T &get##n() const { return v##_; }

#define ACCESSOR_DCL_SET(n,T,v) \
void set##n(const T &v);

#define ACCESSOR_IMPL_SET(n,T,v) \
void set##n(const T &v) { v##_ = v; }

#define ACCESSOR_DCL_MODIFY(n,T,v) \
T &modify##n();

#define ACCESSOR_IMPL_MODIFY(n,T,v) \
T &modify##n() { return v##_; }

#define ACCESSOR_DCL(n,T,v) \
ACCESSOR_DCL_GET(n,T,v) \
ACCESSOR_DCL_SET(n,T,v) \
ACCESSOR_DCL_MODIFY(n,T,v)

#define ACCESSOR_IMPL(n,T,v) \
ACCESSOR_IMPL_GET(n,T,v) \
ACCESSOR_IMPL_SET(n,T,v) \
ACCESSOR_IMPL_MODIFY(n,T,v)

#define ACCESSOR(n,T,v) \
ACCESSOR_IMPL(n,T,v)

#define ACCESSOR_DCL_GET_IMPL_SET(n,T,v) \
ACCESSOR_DCL_GET(n,T,v) \
ACCESSOR_IMPL_SET(n,T,v)

#define ACCESSOR_IMPL_GET_DCL_SET(n,T,v) \
ACCESSOR_IMPL_GET(n,T,v) \
ACCESSOR_DCL_SET(n,T,v)

//-----------------

#define PACCESSOR_GET(n,T,v) \
T *get##n() const { return v##_; }

#define PACCESSOR_SET(n,T,v) \
void set##n(T *v) { v##_ = v; }

#define PACCESSOR_MODIFY(n,T,v) \
T *modify##n() { return v##_; }

#define PACCESSOR(n,T,v) \
PACCESSOR_GET(n,T,v) \
PACCESSOR_SET(n,T,v) \
PACCESSOR_MODIFY(n,T,v) \

#endif
