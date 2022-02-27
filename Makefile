BAZEL = $(shell which bazel)
BAZEL_OPTIONS = --cxxopt='-std=gnu++17' \
				--cxxopt='-Wall' \
				--cxxopt='-Werror' \
				--cxxopt='-Wno-terminate'

.PHONY: build
build:
	$(BAZEL) build ${BAZEL_OPTIONS} //src:*
	$(BAZEL) build ${BAZEL_OPTIONS} //test:*

.PHONY: clean
clean:
	$(BAZEL) clean

.PHONY: run
run:
	$(BAZEL) run ${BAZEL_OPTIONS} //src:main

.PHONY: apply-format
apply-format:
	$(CURDIR)/apply-format.sh

.PHONY: test
test:
	$(BAZEL) test ${BAZEL_OPTIONS} //test:*
