CC ?= gcc
TARGET=lib/libpublib.a

BUILD_PATH ?= .

CFLAGS = -g -O2 -Wall -fPIC $(MYCFLAGS)
# CFLAGS += -D_DEBUG -DDEBUG

ALLCFILE=config file_sys pubfunc thread_api zstring\
 buf thread_lock datalist

ALLOBJ=$(foreach v,$(ALLCFILE),obj/$(v).o)


.PHONY : install uninstall clean

$(TARGET): $(ALLOBJ) 
	ar crs $(TARGET) $(ALLOBJ)

#create build directory
predir:
	-@mkdir -p lib >/dev/null 2>&1
	-@mkdir -p obj >/dev/null 2>&1
	-@mkdir -p dep >/dev/null 2>&1


$(ALLOBJ) : obj/%.o : %.c dep/%.d
	@echo "** Compiling" $< " **"
	-@mkdir -p $(dir $@) >/dev/null 2>&1
	$(CC) -c $(CFLAGS) $< -o $@

dep/%.d : %.c
	-@mkdir -p $(dir $@) >/dev/null 2>&1
	@set -e;  rm -f $@;\
	$(CC) -MM $(CFLAGS) $< > $@.$$$$; \
	sed 's,\(.*\)\.o[ :]*,obj/\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

sinclude $(addprefix dep/,$(addsuffix .d,$(ALLCFILE)))


install:
	cp -d $(TARGET) /usr/local/lib/
	cp -d lib/libpbc.a /usr/local/lib/
	
uninstall:
	-$(RM) /usr/local/lib/libpublib.a
	-$(RM) /usr/local/lib/libpbc.a

clean:
	-$(RM) $(TARGET) obj/*.o dep/*
ifneq (,$(wildcard obj))
	-rmdir obj
endif
ifneq (,$(wildcard dep))
	-rmdir dep
endif
