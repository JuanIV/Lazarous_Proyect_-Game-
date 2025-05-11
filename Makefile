CC = gcc
CFLAGS = -g -Wall -pedantic -ansi -I$(INCDIR)
SRCDIR = ./src
INCDIR = ./include
LIBDIR = ./lib
OBJDIR = ./obj
EXEDIR = ./exe
LDFLAGS = -L$(LIBDIR) -lscreen  
files = $(OBJDIR)/command.o $(OBJDIR)/set.o $(OBJDIR)/character.o $(OBJDIR)/space.o $(OBJDIR)/player.o $(OBJDIR)/inventory.o $(OBJDIR)/object.o $(OBJDIR)/class.o $(OBJDIR)/link.o $(OBJDIR)/game.o $(OBJDIR)/game_actions.o $(OBJDIR)/graphic_engine.o $(OBJDIR)/game_management.o $(OBJDIR)/game_rules.o $(OBJDIR)/game_loop.o 
vpath %.h $(INCDIR)
vpath %.c $(SRCDIR)
vpath %.o $(OBJDIR)
set_test_files = $(OBJDIR)/set_test.o $(OBJDIR)/set.o 
space_test_files = $(OBJDIR)/space_test.o $(OBJDIR)/space.o $(OBJDIR)/set.o $(OBJDIR)/link.o
character_test_files = $(OBJDIR)/character_test.o $(OBJDIR)/character.o
link_test_files = $(OBJDIR)/link_test.o $(OBJDIR)/link.o
inventory_test_files = $(OBJDIR)/inventory_test.o $(OBJDIR)/inventory.o $(OBJDIR)/set.o
player_test_files = $(OBJDIR)/player_test.o $(OBJDIR)/player.o $(OBJDIR)/inventory.o $(OBJDIR)/set.o
object_test_files = $(OBJDIR)/object_test.o $(OBJDIR)/object.o 
class_test_files = $(OBJDIR)/class_test.o $(OBJDIR)/class.o 
.PHONY: prepare project run_tests $(tests) clean run runv
all : project tests
tests: set_test character_test space_test link_test inventory_test player_test object_test


# *************** GAME ***************

project : prepare $(files)
	$(CC) $(CFLAGS) $(files) -o $(EXEDIR)/$@ $(LDFLAGS)


# ************** TESTS ***************

set_test : prepare $(set_test_files)
	$(CC) $(CFLAGS) $(set_test_files) -o $(EXEDIR)/$@ $(LDFLAGS)

character_test : prepare $(character_test_files)
	$(CC) $(CFLAGS) $(character_test_files) -o $(EXEDIR)/$@ $(LDFLAGS)

space_test : prepare $(space_test_files)
	$(CC) $(CFLAGS) $(space_test_files) -o $(EXEDIR)/$@ $(LDFLAGS)

link_test : prepare $(link_test_files)
	$(CC) $(CFLAGS) $(link_test_files) -o $(EXEDIR)/$@ $(LDFLAGS)

inventory_test : prepare $(inventory_test_files)
	$(CC) $(CFLAGS) $(inventory_test_files) -o $(EXEDIR)/$@ $(LDFLAGS)

player_test : prepare $(player_test_files)
	$(CC) $(CFLAGS) $(player_test_files) -o $(EXEDIR)/$@ $(LDFLAGS)

object_test : prepare $(object_test_files)
	$(CC) $(CFLAGS) $(object_test_files) -o $(EXEDIR)/$@ $(LDFLAGS)

class_test : prepare $(class_test_files)
	$(CC) $(CFLAGS) $(object_test_files) -o $(EXEDIR)/$@ $(LDFLAGS)

# ************** FOLDERS *************

prepare :
	@mkdir -p $(EXEDIR) $(OBJDIR)

# .o:

$(OBJDIR)/command.o: $(SRCDIR)/command.c $(INCDIR)/command.h $(INCDIR)/types.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/set.o: $(SRCDIR)/set.c $(INCDIR)/set.h $(INCDIR)/types.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/character.o: $(SRCDIR)/character.c $(INCDIR)/character.h $(INCDIR)/types.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/space.o: $(SRCDIR)/space.c $(INCDIR)/space.h $(INCDIR)/types.h $(INCDIR)/set.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/player.o: $(SRCDIR)/player.c $(INCDIR)/player.h $(INCDIR)/types.h $(INCDIR)/inventory.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/inventory.o: $(SRCDIR)/inventory.c $(INCDIR)/inventory.h $(INCDIR)/set.h $(INCDIR)/types.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/object.o: $(SRCDIR)/object.c $(INCDIR)/object.h $(INCDIR)/types.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/class.o: $(SRCDIR)/class.c $(INCDIR)/class.h $(INCDIR)/types.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/link.o: $(SRCDIR)/link.c $(INCDIR)/link.h $(INCDIR)/types.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/game.o: $(SRCDIR)/game.c $(INCDIR)/game.h $(INCDIR)/command.h $(INCDIR)/types.h $(INCDIR)/space.h $(INCDIR)/object.h $(INCDIR)/player.h $(INCDIR)/set.h $(INCDIR)/character.h $(INCDIR)/link.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/game_actions.o: $(SRCDIR)/game_actions.c $(INCDIR)/game_actions.h $(INCDIR)/command.h $(INCDIR)/types.h $(INCDIR)/game.h $(INCDIR)/space.h $(INCDIR)/character.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/graphic_engine.o: $(SRCDIR)/graphic_engine.c $(INCDIR)/graphic_engine.h $(INCDIR)/game.h $(INCDIR)/command.h $(INCDIR)/types.h $(INCDIR)/space.h $(INCDIR)/libscreen.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/game_management.o: $(SRCDIR)/game_management.c $(INCDIR)/game_management.h $(INCDIR)/game.h $(INCDIR)/command.h $(INCDIR)/types.h $(INCDIR)/space.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/game_loop.o: $(SRCDIR)/game_loop.c $(INCDIR)/command.h $(INCDIR)/types.h $(INCDIR)/game.h $(INCDIR)/space.h $(INCDIR)/game_actions.h $(INCDIR)/graphic_engine.h $(INCDIR)/game_management.h $(INCDIR)/game_rules.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/game_rules.o: $(SRCDIR)/game_rules.c $(INCDIR)/game_rules.h $(INCDIR)/game.h $(INCDIR)/command.h $(INCDIR)/types.h $(INCDIR)/space.h $(INCDIR)/object.h $(INCDIR)/player.h $(INCDIR)/set.h $(INCDIR)/character.h $(INCDIR)/link.h
	$(CC) $(CFLAGS) -c $< -o $@


# *************** TESTS ***************


# .o:

$(OBJDIR)/set_test.o: $(SRCDIR)/set_test.c $(INCDIR)/set_test.h $(INCDIR)/set.h $(INCDIR)/test.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/character_test.o: $(SRCDIR)/character_test.c $(INCDIR)/character_test.h $(INCDIR)/character.h $(INCDIR)/test.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/space_test.o: $(SRCDIR)/space_test.c $(INCDIR)/space_test.h $(INCDIR)/space.h $(INCDIR)/set.h $(INCDIR)/test.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/link_test.o: $(SRCDIR)/link_test.c $(INCDIR)/link_test.h $(INCDIR)/link.h $(INCDIR)/test.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/inventory_test.o: $(SRCDIR)/inventory_test.c $(INCDIR)/inventory_test.h $(INCDIR)/inventory.h $(INCDIR)/set.h $(INCDIR)/test.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/player_test.o: $(SRCDIR)/player_test.c $(INCDIR)/player_test.h $(INCDIR)/player.h $(INCDIR)/set.h $(INCDIR)/inventory.h 
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/object_test.o: $(SRCDIR)/object_test.c $(INCDIR)/object_test.h $(INCDIR)/object.h 
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/class_test.o: $(SRCDIR)/class_test.c $(INCDIR)/class_test.h $(INCDIR)/class.h 
	$(CC) $(CFLAGS) -c $< -o $@

run_set_test:
	./$(EXEDIR)/set_test

run_character_test:
	./$(EXEDIR)/character_test

run_space_test:
	./$(EXEDIR)/space_test

run_link_test:
	./$(EXEDIR)/link_test

run_inventory_test:
	./$(EXEDIR)/inventory_test

run_player_test:
	./$(EXEDIR)/player_test

run_object_test:
	./$(EXEDIR)/object_test

run_class_test:
	./$(EXEDIR)/class_test
run_tests:
	@echo "Running set_test"
	./$(EXEDIR)/set_test
	@echo "Running character_test"
	./$(EXEDIR)/character_test
	@echo "Running space_test"
	./$(EXEDIR)/space_test
	@echo "Running link_test"
	./$(EXEDIR)/link_test
	@echo "Running inventory_test"
	./$(EXEDIR)/inventory_test
	@echo "Running player_test"
	./$(EXEDIR)/player_test
	@echo "Running object_test"
	./$(EXEDIR)/object_test

# ****************************************

# *************** GAME RUN ***************

run :
	@echo "Running project"
	./$(EXEDIR)/project lab.dat

runv :
	@echo "Running Valgrind"
	valgrind --leak-check=full -s --track-origins=yes ./$(EXEDIR)/project lab.dat

runl :
	@echo "Running Log"
	./$(EXEDIR)/project lab.dat -l logFile

rund :
	@echo "Running Deterministic mode"
	./$(EXEDIR)/project lab.dat -d

runvd :
	@echo "Running Deterministic mode"
	valgrind --leak-check=full -s --track-origins=yes ./$(EXEDIR)/project lab.dat -d

runld :
	@echo "Running Deterministic mode with Log"
	./$(EXEDIR)/project lab.dat -l -d logFile

run_test:
	@echo "Running global test"
	./$(EXEDIR)/project lab.dat -l output <game1.cmd

run_test2:
	./$(EXEDIR)/project lab.dat -l output <game2.cmd

doxygen:
	@echo "Generating html documentation"
	doxygen Doxyfile
	xdg-open doc/html/index.html >/dev/null 2>&1

clean_doxygen : 
	rm -rf ./doc/html ./doc/latex

clean :
	rm -rf $(OBJDIR) $(EXEDIR)


