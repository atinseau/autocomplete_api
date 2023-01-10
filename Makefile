PROJECT_NAME = autocomplete_api
MAKEFILE_PARAMS = -j --no-print-directory

build:
	@mkdir -p build
	@cd build && cmake .. && make $(MAKEFILE_PARAMS)

all:
	@cd build && make $(MAKEFILE_PARAMS)

clean:
	rm -rf build

fclean: clean

serve: all
	@cd build && ./$(PROJECT_NAME)

seeder: all
	@cd build && ./seeder/$(PROJECT_NAME)_seeder $(filter-out $@,$(MAKECMDGOALS))

test: all
	@cd build && ./tests/$(PROJECT_NAME)_test


# ignore all arguments after seeder
%:
	@:

.PHONY: build all clean fclean migrations test

.DEFAULT_GOAL := all