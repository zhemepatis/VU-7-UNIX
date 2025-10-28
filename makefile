EXEC_EXT = out
RUN = ./

SRC_DIR = ./src
OBJ_DIR = obj
BIN_DIR = bin

TARGET = $(BIN_DIR)/main.$(EXEC_EXT)

# build rule
build: $(TARGET)

$(BIN_DIR)/main.$(EXEC_EXT): $(OBJ_DIR)/main.o $(OBJ_DIR)/commands.o | $(BIN_DIR)
	gcc $^ -o $@

$(BIN_DIR)/%.$(EXEC_EXT): $(OBJ_DIR)/%.o | $(BIN_DIR)
	gcc $^ -o $@

bin: 
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)
	gcc -c $^ -o $@

obj: 
	mkdir -p $@

# run rule
run: build
	$(RUN)$(TARGET)

# clean rule
clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)