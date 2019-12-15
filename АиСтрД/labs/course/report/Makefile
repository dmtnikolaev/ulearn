#
# Makefile
#
# Run `make` to:
#    1. Run Pandoc.
#    2. Convert all Markdown files to single out/TARGET.pdf (set TARGET below).
#       Source files will be sorted before concatenation.
#
# Run `make clean` to clean up project (delete output file).
#

# Name of output document.
TARGET = doc

RM = /bin/rm
PANDOC = /bin/pandoc

# Output directory.
OUT_DIR = out

# Markdown file(s) will be converted.
SOURCE_DOCS = $(wildcard *.md)
SOURCE_DOCS := $(filter-out README.md,$(SOURCE_DOCS))
SOURCE_DOCS := $(filter-out $(exclude),$(SOURCE_DOCS))
SOURCE_DOCS := $(sort $(SOURCE_DOCS))

# Pandoc metadata file (configure appearance of PDF).
STYLE_FILE = style.yaml

# Full path to output PDF file.
EXPORTED_PDF = $(OUT_DIR)/$(TARGET).pdf

# Basic Pandoc options (see `pandoc -h` and https://pandoc.org/MANUAL.html).
PANDOC_OPTIONS = \
	--standalone \
	--toc \
	--listings \
	--pdf-engine=xelatex \
	--metadata-file=$(STYLE_FILE) \
	--resource-path=.\
	--template=eisvogel.tex \
	--from markdown+multiline_tables+grid_tables+raw_tex+definition_lists \

# Add filters to Pandoc if necessary.
#PANDOC_OPTIONS += --filter=pantable

# Rule for MD -> PDF.
#
$(TARGET):
	$(PANDOC) \
		$(PANDOC_OPTIONS) \
		-o $(EXPORTED_PDF) \
		$(SOURCE_DOCS)

# Targets.
#
.PHONY: all clean

all: $(TARGET)

clean:
	$(RM) $(EXPORTED_PDF)
