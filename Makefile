CC=gcc
BIN = test
BIN_PATH = ./

SDS_PATH = ./sds
SDS_FILE = $(wildcard $(SDS_PATH)/*.c)
SDS_OBJS = $(patsubst %.c,%.o,$(SDS_FILE))

SRC_PATH = ./
SRC_FILE = $(wildcard $(SRC_PATH)/*.c)
SRC_OBJS = $(patsubst %.c,%.o,$(SRC_FILE))

INC_PATH = -I$(SDS_PATH) -I$(SRC_PATH)
CFLAGS = -g -O0 -Wall $(INC_PATH)

$(BIN):sds $(SRC_OBJS) 
	$(CC) -o $(BIN_PATH)/$@ $(SDS_OBJS) $(SRC_OBJS) $(CFLAGS)
	@echo "compile $(BIN) success!";

sds:$(SDS_OBJS)
	@echo "compile sds success!";

clean:
	$(RM) $(SDS_PATH)/*.o $(SRC_PATH)/*.o $(BIN_PATH)/$(BIN)
