# `Makefile'
#
# Build stochastic library, run tests, etc.
#
# Targets:
#
###############################################################################

###############################################################################
# This opening `if' relocates us into a platform-specific build directory and
# re-runs make there.  The real build stuff is below the `else'...
ifndef source_dir

# Not yet jumped to build directory, so work out where it is and jump there
# now.

this_makefile:=$(lastword $(MAKEFILE_LIST))
build_root?=$(CURDIR)/build
platform?=$(shell uname -om | tr 'A-Z \-/\\.()' a-z\-_)
build_dir:=$(build_root)/$(platform)

.SUFFIXES:

MAKETARGET=$(MAKE) --no-print-directory -C $@ -f $(CURDIR)/$(this_makefile) \
    build_dir=$(build_dir) platform=$(platform) source_dir=$(CURDIR) \
    this_makefile:=$(this_makefile) $(filter-out clean,$(MAKECMDGOALS))

.PHONY: $(build_dir)
$(build_dir):
	+@[ -d $@ ] || mkdir -p $@
	+@$(MAKETARGET)

$(this_makefile): ;

%:: $(build_dir) ;

.PHONY: clean
clean:
	$(RM) -fr $(build_dir)
	if [ -d $(build_root) ] ; \
	then \
	rmdir --ignore-fail-on-non-empty $(build_root); \
	fi

else
# End of build directory stuff.
###############################################################################

CC:=g++
CXXFLAGS:=-g -Wall -fPIC
LDFLAGS:=-g -L.

slib:=libstochastic.a
dlib:=libstochastic.so
lib_srcs:=ApproximationAlgorithm.cpp Cauchy.cpp ChiSquare.cpp \
    DeltaDistribution.cpp Distribution.cpp EmpiricalDistribution.cpp \
    Exponential.cpp FileParser.cpp Gaussian.cpp GraphRV.cpp \
    InverseRV_Distribution.cpp MaxOfDistributions.cpp \
    MinOfDistributions.cpp MixtureModel.cpp MonteCarloAlgorithm.cpp \
    NodeRV.cpp PG_EM.cpp PiecewiseGaussian.cpp PiecewiseUniform.cpp \
    ProbabilisticDiscretization.cpp PU_DivideAndConquer.cpp \
    RandomVariable.cpp SumOfUniforms.cpp Uniform.cpp
lib_objs:=$(lib_srcs:%.cpp=%.o)

test:=main
test_srcs:=main.cpp Experiments.cpp Gnuplot.cpp
test_objs:=$(test_srcs:%.cpp=%.o)
test_libs:=$(slib)

vpath %.cpp $(addprefix $(source_dir)/,src src/algorithms src/distributions \
    src/graph src/intermediateResults src/utilities test_src)

.PHONY: all
all: $(dlib)
	$(source_dir)/perl/test.pl

.PHONY: test
test: $(test)
	$<

$(slib): $(lib_objs)
	ar cvr $@ $?

$(dlib): $(lib_objs)
	$(CC) -shared -Wl,-soname,$@ -o $@ $^

$(test): $(test_objs) $(test_libs)

endif
