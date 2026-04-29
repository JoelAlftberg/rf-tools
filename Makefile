.PHONY: default build clean run

default: build

build:
	mkdir -p build
	g++ -Wall -Werror source/main.cpp source/parser/parser.cpp lib/components/component_factory.cpp -Iinclude -Ilib -o build/rf-tools

clean:
	rm -rf build