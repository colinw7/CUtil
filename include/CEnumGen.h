#undef CENUM_START
#undef CENUM_END
#undef CENUM_ITEM
#undef CENUM_VALUE

#define CENUM_START(E) \
CEnum<E> enum_map; \
\
template<typename T> \
void CEnum<T>::init() {

#define CENUM_END(E) \
}

#define CENUM_ITEM(E,S,N) add(E,S);
#define CENUM_VALUE(E,S,N,V) CENUM_ITEM(E,S,N)
