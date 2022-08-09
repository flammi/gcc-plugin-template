CXX ?= g++

# Flags for the C++ compiler: enable C++11 and all the warnings, -fno-rtti is required for GCC plugins
CXXFLAGS = -std=c++11 -Wall -fno-rtti 
# Workaround for an issue of -std=c++11 and the current GCC headers
CXXFLAGS += -Wno-literal-suffix

# Determine the plugin-dir and add it to the flags
PLUGINDIR=$(shell $(CXX) -print-file-name=plugin)
CXXFLAGS += -I$(PLUGINDIR)/include -g

# top level goal: build our plugin as a shared library
all: dummy_plugin.so

.PHONY: clean test
clean: 
	rm -f dummy_plugin.so dummy_plugin.o

dummy_plugin.o : dummy_plugin.cc
	$(CXX) $(CXXFLAGS) -fPIC -c -o $@ $<

dummy_plugin.so: dummy_plugin.o
	$(CXX) $(LDFLAGS) -shared -o $@ $<
