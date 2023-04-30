CC = g++
AR = ar
RM = rm

CDEBUG = -g
LDEBUG = -g

INC_DIR = ../include
OBJ_DIR = ../minObj
LIB_DIR = ../lib

all: dirs $(LIB_DIR)/libCUtilMin.a

dirs:
	@if [ ! -e ../obj ]; then mkdir ../obj; fi
	@if [ ! -e ../lib ]; then mkdir ../lib; fi
	@if [ ! -e ../bin ]; then mkdir ../bin; fi

SRC = \
CUtil.cpp \
CWindow.cpp \
CEvent.cpp \
CEnv.cpp \
CEnvMatch.cpp \
CInterval.cpp \
CEncode64.cpp \
CEncode85.cpp \
CBrush.cpp \

OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRC))

CPPFLAGS = \
-std=c++17 \
-I. \
-I$(INC_DIR) \
-I../../CFile/include \
-I../../CMath/include \
-I../../CGlob/include \
-I../../CStrUtil/include \

clean:
	$(RM) -f $(OBJ_DIR)/*.o
	$(RM) -f $(LIB_DIR)/libCUtilMin.a

$(OBJS): $(OBJ_DIR)/%.o: %.cpp
	$(CC) -c $< -o $(OBJ_DIR)/$*.o $(CPPFLAGS)

.SUFFIXES: .cpp

$(LIB_DIR)/libCUtilMin.a: $(OBJS)
	$(AR) crv $(LIB_DIR)/libCUtilMin.a $(OBJS)
