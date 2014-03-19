RUN_FILE = test5.txt
OUTPUT = output.txt
PWD = /Users/RedDragon/Dropbox/College/CS\ 1622\ Compilers/Project2
JARPATH = /Users/RedDragon/Dropbox/College/CS\ 1622\ Compilers/Project2/lib

all: build run

build: build_tools build_class

build_tools:
	bin/jflex BestLexer.flex
	java -jar $(JARPATH)/java-cup-11a.jar -interface -parser BestParser BestParser.cup
build_class:
	javac -classpath $(JARPATH)/java-cup-11a.jar:$(PWD)/ Apocalypse.java
run:
	java -classpath $(JARPATH)/java-cup-11a.jar:$(PWD)/ Apocalypse $(RUN_FILE)
save:
	java -classpath $(JARPATH)/java-cup-11a.jar:$(PWD)/ Apocalypse $(RUN_FILE) > $(OUTPUT)