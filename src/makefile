QMAKE:=/Users/awesic/Qt/6.5.2/macos/bin/qmake
APPLICATIONS:=Applications

CC:=gcc
CFLAGS:=-g -Wall -Werror -Wextra -std=c11 --coverage
BUILD := ./build/
OBJ_DIR:=$(BUILD)objects
APP:=$(BUILD)SmartCalc.app
TEST_FLAGS:=-lcheck -lpthread -pthread -lm
TESTS:=test

SOURCES += \
    ./SmartCalc/QCustomPlotLib/qcustomplot.cpp \
    ./SmartCalc/calculation.c \
    ./SmartCalc/creditmodel.cpp \
    ./SmartCalc/depositmodel.cpp \
    ./SmartCalc/main.cpp \
    ./SmartCalc/mainwindow.cpp \
    ./SmartCalc/parsing.c \
    ./SmartCalc/plotgraphic.cpp \
    ./SmartCalc/queue.c \
    ./SmartCalc/stack.c \
    ./SmartCalc/validator.c

HEADERS += \
    ./SmartCalc/QCustomPlotLib/qcustomplot.h \
    ./SmartCalc/creditmodel.h \
    ./SmartCalc/defines.h \
    ./SmartCalc/depositmodel.h \
    ./SmartCalc/mainwindow.h \
    ./SmartCalc/plotgraphic.h \
    ./SmartCalc/queue_stack.h \
    ./SmartCalc/smartcalc.h \
    ./SmartCalc/validator.h

SOURCE := SmartCalc/%.c
SRC := SmartCalc/*.c

ifeq ($(shell uname -s),Linux)
	TEST_FLAGS+=-lsubunit -lgcov
endif

all: build

build: $(BUILD)SmartCalc.pro
	cd $(BUILD)
	$(QMAKE) -o $(BUILD)Makefile $(BUILD)SmartCalc.pro -spec macx-clang CONFIG+=debug CONFIG+=qml_debug
	make -C $(BUILD)

./$(BUILD)SmartCalc.pro:
	cp SmartCalc.pro $(BUILD)

./$(BUILD)%.o: $(SOURCE)
	$(CC) $(CFLAGS) -c $< -o $@

install: build
	@mkdir $(HOME)/$(APPLICATIONS)/SmartCalc/ 2>/dev/null
	cp -rf $(APP) $(HOME)/$(APPLICATIONS)/SmartCalc/
	make clean_wo_app

uninstall:
	rm -rf $(HOME)/$(APPLICATIONS)/SmartCalc

clean:
	rm -rf *.info ./$(BUILD)*.o ./$(BUILD)*.gcda ./$(BUILD)*.gcno ./$(BUILD)$(TESTS) ./$(BUILD)*.app ./$(BUILD)*.pro ./$(BUILD).qmake.stash ./$(BUILD)Makefile ./$(BUILD)*.cpp ./$(BUILD)ui_mainwindow.h report *.tar

clean_wo_app:
	rm -rf *.info ./$(BUILD)*.o ./$(BUILD)*.gcda ./$(BUILD)*.gcno ./$(BUILD)$(TESTS) ./$(BUILD)*.pro ./$(BUILD).qmake.stash ./$(BUILD)Makefile ./$(BUILD)*.cpp ./$(BUILD)ui_mainwindow.h report

dvi:
	open -a 'google chrome' doc.html

dist:
	tar -czvf SmartCalc.tar $(HOME)/$(APPLICATIONS)/SmartCalc/
	# gzip $(HOME)/$(APPLICATIONS)/SmartCalc/ ../SmartCalc.tar

./$(BUILD)$(TESTS).o: $(TESTS).c 
	$(CC) $(CFLAGS) -c $< -o $@

test: $(BUILD)queue.o $(BUILD)stack.o $(BUILD)validator.o $(BUILD)parsing.o $(BUILD)calculation.o $(BUILD)$(TESTS).o
	$(CC) $^ -o $(BUILD)$(TESTS) --coverage $(TEST_FLAGS) -I./ -L./
	./$(BUILD)$(TESTS)

rebuild: clean all

gcov_report: clean $(TESTS)
	lcov -t "smartcalc" -o smartcalc.info -c -d $(BUILD)
	genhtml -o report smartcalc.info
	open -a 'google chrome' ./report/index.html

style:
	clang-format -style=google -i $(TESTS).c $(SRC)
	# python3 ./cpplint.py --extension=c $(TESTS).c $(SRC)
	# cppcheck --enable=all --inconclusive --suppress=missingIncludeSystem $(TESTS).c $(SRC)

leaks: clean $(TESTS)
ifeq ($(shell uname -s),Linux)
	valgrind -s --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(BUILD)$(TESTS)
else
	leaks --atExit -- $(BUILD)$(TESTS)
endif

