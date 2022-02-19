build:
	cmake -B build
	cmake --build build

test: build
	cd build && ctest

.PHONY: build test
