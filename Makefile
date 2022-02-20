build:
	cmake -B build
	cmake --build build

test_unit: build
	cd build && ctest

test_e2e: build
	python3 -m unittest test/e2e/e2e.py

.PHONY: build test
