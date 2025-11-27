EXEC_EXT = out
RUN = ./

SRC_DIR = ./src
OBJ_DIR = obj
BIN_DIR = bin

CLIENT = $(BIN_DIR)/client.$(EXEC_EXT)
SERVER = $(BIN_DIR)/server.$(EXEC_EXT)

build-client: $(CLIENT)
build-server: $(SERVER)

# directory rules
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# build executables
$(BIN_DIR)/server.$(EXEC_EXT): $(OBJ_DIR)/server.o $(OBJ_DIR)/logs.o $(OBJ_DIR)/sockets.o $(OBJ_DIR)/commands.o | $(BIN_DIR)
	gcc $^ -o $@

$(BIN_DIR)/client.$(EXEC_EXT): $(OBJ_DIR)/client.o $(OBJ_DIR)/logs.o  | $(BIN_DIR)
	gcc $^ -o $@

# compile sources
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	gcc -c $< -o $@

# run rules
client: build-client
	$(RUN)$(CLIENT)

server: build-server
	$(RUN)$(SERVER)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)