include Makefile.inc

all: mmtk

mmtk:
	@(cd ./mexsrc; $(MAKE))

clean:
	@(cd ./mexsrc; $(MAKE) clean)

gendoc:
	@( $(DOCGEN) $(DOCFILE) )
	@( cd $(DOC)/latex; $(MAKE) )

help:
	@echo '-----'
	@echo 'Makefile for the MMTK.'
	@echo ' '
	@echo 'Options are:'
	@echo '- all: builds he library, the tests, and examples.'
	@echo ' '
	@echo '- gendoc: generates the documentation for the library.'
	@echo ' '
	@echo '- clean: cleans ALL the generated files.'
	@echo '-----'
