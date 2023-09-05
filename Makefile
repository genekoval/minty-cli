program := minty

project := $(program)-cli
summary := Command line client for Minty servers

STD := c++20

$(program).type := executable
$(program).libs := \
 $(program) \
 commline \
 conftools \
 crypto \
 date \
 fmt \
 fstore \
 http \
 netcore \
 pthread \
 ssl \
 timber \
 uuid++ \
 yaml-cpp \
 zipline

install := $(program)
targets := $(install)

files = \
 $(include) \
 $(src) \
 Makefile \
 VERSION

include mkbuild/base.mk

define defines.add
 $(addprefix -D, $(1))
endef

defines.debug := TIMBER_TIMER_ACTIVE
defines.release := TIMBER_MAX_LEVEL=info

ifeq ($(environment),$(environment.develop))
 CXXFLAGS += $(call defines.add,$(defines.debug))
else
 CXXFLAGS += $(call defines.add,$(defines.release))
endif

$(obj)/$(program)/main.o: CXXFLAGS +=\
 -DNAME='"$(program)"'\
 -DVERSION='"$(version)"'\
 -DDESCRIPTION='"$(summary)"'
