RUN_FILE = e.txt
OUTPUT = output.txt
PWD = "/Users/RedDragon/Dropbox/College/CS 1622 Compilers/project3b"
JARPATH = "/Users/RedDragon/Dropbox/College/CS 1622 Compilers/project3b/lib"

all: build run

build: build_tools build_class

it: build_class run

build_tools:
	bin/jflex BestLexer.flex
	java -jar $(JARPATH)/java-cup-11a.jar -interface -parser BestParser BestParser.cup
build_class:
	javac -classpath $(JARPATH)/java-cup-11a.jar:$(PWD)/ Main.java
run:
	java -classpath $(JARPATH)/java-cup-11a.jar:$(PWD)/ Main $(RUN_FILE)
save:
	java -classpath $(JARPATH)/java-cup-11a.jar:$(PWD)/ Main $(RUN_FILE) > $(OUTPUT)