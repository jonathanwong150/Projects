BIN_DIR = bin
CXX = g++
CPPFLAGS = -Wall -g

all: $(BIN_DIR)/.dirstamp interpreter

interpreter: Interpreter.cpp $(BIN_DIR)/ProgramState.o $(BIN_DIR)/LetStatement.o $(BIN_DIR)/AddStatement.o $(BIN_DIR)/SubStatement.o $(BIN_DIR)/MultStatement.o $(BIN_DIR)/DivStatement.o $(BIN_DIR)/PrintStatement.o $(BIN_DIR)/PrintAllStatement.o $(BIN_DIR)/GoToStatement.o $(BIN_DIR)/GoSubStatement.o $(BIN_DIR)/IfStatement.o $(BIN_DIR)/ReturnStatement.o $(BIN_DIR)/EndStatement.o $(BIN_DIR)/PeriodStatement.o
	$(CXX) $(CPPFLAGS) $^ -o $@

$(BIN_DIR)/ProgramState.o: ProgramState.cpp ProgramState.h
	$(CXX) $(CPPFLAGS) -c $< -o $@ 

$(BIN_DIR)/LetStatement.o: LetStatement.cpp LetStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@ 

$(BIN_DIR)/AddStatement.o: AddStatement.cpp AddStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@ 

$(BIN_DIR)/SubStatement.o: SubStatement.cpp SubStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@ 

$(BIN_DIR)/MultStatement.o: MultStatement.cpp MultStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@ 

$(BIN_DIR)/DivStatement.o: DivStatement.cpp DivStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@ 

$(BIN_DIR)/PrintStatement.o: PrintStatement.cpp PrintStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@ 

$(BIN_DIR)/PrintAllStatement.o: PrintAllStatement.cpp PrintAllStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@ 

$(BIN_DIR)/GoToStatement.o: GoToStatement.cpp GoToStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@ 

$(BIN_DIR)/GoSubStatement.o: GoSubStatement.cpp GoSubStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/ReturnStatement.o: ReturnStatement.cpp ReturnStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/IfStatement.o: IfStatement.cpp IfStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/EndStatement.o: EndStatement.cpp EndStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/PeriodStatement.o: PeriodStatement.cpp PeriodStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(BIN_DIR)

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp
