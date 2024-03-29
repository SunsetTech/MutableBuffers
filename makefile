NAME := MutableBuffer.so
CC := gcc
CFLAGS := -g -std=c99 -D"COMPAT53_PREFIX=LUA_COMPAT" -c -ISource -I/usr/include/luajit-2.1 -fpic -MMD
LDFLAGS := -shared compat-5.3.o
BUILD := Build
SOURCE := Source
SOURCES := $(shell find $(SOURCE) -name '*.c')
OBJECTS := $(patsubst $(SOURCE)/%,$(BUILD)/%,$(SOURCES:.c=.o))

all: $(OBJECTS) $(NAME) seperate_headers

$(NAME): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(BUILD)/%.o: $(SOURCE)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	@echo Scrub a dub dub...
	@rm -rf Build
	@rm -f *.so*
	@echo There! All clean! ^-^

.PHONY: print
print:
	@echo $(SOURCE)
	@echo $(SOURCES)
	@echo $(BUILD)
	@echo $(OBJECTS)

.PHONY: seperate_headers
seperate_headers:
	-@rm -r Headers
	@rsync -avm --include='*.h' -f 'hide,! */' ./Source/* ./Headers

-include $(OBJECTS:.o=.d)
