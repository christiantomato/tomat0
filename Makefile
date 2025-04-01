#the executable (.out extension is convention for binary files)
exec = tomat0.out
#listing our sources (in the source folder with extension .c)
sources = $(wildcard src/*.c)
#object files created by compiler, linked together to create exectuable
objects = $(sources: .c = .o)
#for debugging, commented out for now because the dysm file is making me go insane and we don't need it right now
#flags = -g


#how to create the exectuable
$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

#how to create the object files
#recreates the object files when change detected
%.o: %.c include/%.h 
	gcc -c $(flags) $< -o $@

#make it accessible globally on system
#(sudo make install)
install:
	make
	cp ./tomat0.out /usr/local/bin/tomat0

#clean command to recompile (remove .out ext and object files)
clean:
	-rm *.out
	-rm *.o 
	-rm src/*.o
	-rm -rf *.dSYM
