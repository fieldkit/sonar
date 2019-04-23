BUILD ?= $(abspath build)

all: cmake
	$(MAKE) -C $(BUILD)

cmake: gitdeps
	mkdir -p $(BUILD)
	cd $(BUILD) && cmake ../

gitdeps:
	simple-deps --config firmware/module/dependencies.sd
	simple-deps --config firmware/test/dependencies.sd

clean:
	rm -rf $(BUILD)

veryclean: clean
	rm -rf gitdeps
