RUN_FILE = e.txt
OUTPUT = output.txt
PWD = /Users/RedDragon/Desktop/project3
JARPATH = /Users/RedDragon/Desktop/project3/lib

all: build run

build: build_tools build_class

build_tools:
	bin/jflex BestLexer.flex
	java -jar $(JARPATH)/java-cup-11a.jar -interface -parser BestParser BestParser.cup
build_class:
	javac -classpath $(JARPATH)/java-cup-11a.jar:$(PWD)/ Main.java
run:
	java -classpath $(JARPATH)/java-cup-11a.jar:$(PWD)/ Main $(RUN_FILE)
save:
	java -classpath $(JARPATH)/java-cup-11a.jar:$(PWD)/ Main $(RUN_FILE) > $(OUTPUT)