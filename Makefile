build:
	cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=1 
	cmake --build build

test_unit: build
	cd build && ctest

test_e2e: build
	python3 -m unittest test/e2e/e2e.py

test: test_unit test_e2e

.PHONY: build test_unit test_e2e test
