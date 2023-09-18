# QMAKE:=/Users/{user}/Qt/6.5.2/macos/bin/qmake

# If you're in Linux / Windows change APPICATIONS to the applications folder
APPLICATIONS:=Applications

CC:=gcc
CFLAGS:= -g -Wall -Werror -Wextra -std=c11
BUILD := ./build/
OBJ_DIR:=$(BUILD)objects
APP:=$(BUILD)Calculator.app
TEST_FLAGS:=-lcheck -lpthread -pthread -lm
TESTS:=test

SOURCES += \
    ./Calculator/QCustomPlotLib/qcustomplot.cpp \
    ./Calculator/calculation.c \
    ./Calculator/creditmodel.cpp \
    ./Calculator/depositmodel.cpp \
    ./Calculator/main.cpp \
    ./Calculator/mainwindow.cpp \
    ./Calculator/parsing.c \
    ./Calculator/plotgraphic.cpp \
    ./Calculator/queue.c \
    ./Calculator/stack.c \
    ./Calculator/validator.c

HEADERS += \
    ./Calculator/QCustomPlotLib/qcustomplot.h \
    ./Calculator/creditmodel.h \
    ./Calculator/defines.h \
    ./Calculator/depositmodel.h \
    ./Calculator/mainwindow.h \
    ./Calculator/plotgraphic.h \
    ./Calculator/queue_stack.h \
    ./Calculator/Calculator.h \
    ./Calculator/validator.h

SOURCE := Calculator/%.c
SRC := Calculator/*.c

ifeq ($(shell uname -s),Linux)
	TEST_FLAGS+=-lsubunit -lgcov
endif

all: build

build: $(BUILD)Calculator.pro
	cd $(BUILD)
# $(QMAKE) -o $(BUILD)Makefile $(BUILD)Calculator.pro -spec macx-clang CONFIG+=debug CONFIG+=qml_debug
	qmake -o $(BUILD)Makefile $(BUILD)Calculator.pro -spec macx-clang CONFIG+=debug CONFIG+=qml_debug
	make -C $(BUILD)

./$(BUILD)Calculator.pro:
	cp Calculator.pro $(BUILD)

./$(BUILD)%.o: $(SOURCE)
	$(CC) $(CFLAGS) -c $< -o $@

install: build
	@mkdir $(HOME)/$(APPLICATIONS)/Calculator/ 2>/dev/null
	cp -rf $(APP) $(HOME)/$(APPLICATIONS)/Calculator/
	make clean_wo_app

uninstall:
	rm -rf $(HOME)/$(APPLICATIONS)/Calculator

clean:
	rm -rf *.info ./$(BUILD)*.o ./$(BUILD)*.gcda ./$(BUILD)*.gcno ./$(BUILD)$(TESTS) ./$(BUILD)*.app ./$(BUILD)*.pro ./$(BUILD).qmake.stash ./$(BUILD)Makefile ./$(BUILD)*.cpp ./$(BUILD)moc* ./$(BUILD)ui_mainwindow.h report *.tar

clean_wo_app: # clean without rm app
	rm -rf *.info ./$(BUILD)*.o ./$(BUILD)*.gcda ./$(BUILD)*.gcno ./$(BUILD)$(TESTS) ./$(BUILD)*.pro ./$(BUILD).qmake.stash ./$(BUILD)Makefile ./$(BUILD)moc* ./$(BUILD)*.cpp ./$(BUILD)ui_mainwindow.h report

dvi:
	open -a 'google chrome' doc.html

dist:
	tar -czvf Calculator.tar $(HOME)/$(APPLICATIONS)/Calculator/ doc.html
# gzip $(HOME)/$(APPLICATIONS)/Calculator/ ../Calculator.tar

./$(BUILD)$(TESTS).o: $(TESTS).c 
	$(CC) $(CFLAGS) -c $< -o $@

test: $(BUILD)queue.o $(BUILD)stack.o $(BUILD)validator.o $(BUILD)parsing.o $(BUILD)calculation.o $(BUILD)$(TESTS).o
	$(CC) $^ -o $(BUILD)$(TESTS) --coverage $(TEST_FLAGS) -I./ -L./
	./$(BUILD)$(TESTS)

rebuild: clean all

gcov_report: CFLAGS += --coverage
gcov_report: report

report: clean $(TESTS)
	lcov -t "Calculator" -o Calculator.info -c -d $(BUILD)
	genhtml -o report Calculator.info
	open -a 'google chrome' ./report/index.html

leaks: clean $(TESTS)
ifeq ($(shell uname -s),Linux)
	valgrind -s --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(BUILD)$(TESTS)
else
	leaks --atExit -- $(BUILD)$(TESTS)
endif

