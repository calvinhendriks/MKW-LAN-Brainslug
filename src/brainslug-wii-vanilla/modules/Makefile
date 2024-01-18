###############################################################################
# Makefile
#  by Alex Chadwick
#
# A makefile script for generation of all brainslug modules
###############################################################################

MODULES += rmc-local-net

###############################################################################
# Parameters

# Used to suppress command echo.
Q      ?= @
LOG    ?= @echo $@

###############################################################################
# Rule to make everything.
PHONY += all
all: $(addsuffix _module,$(MODULES))

%_module:
	$Q$(MAKE) BSLUGDIR=$(BSLUGDIR) -C $*

###############################################################################
# Release rule

PHONY += release
release: $(addsuffix _module_release,$(MODULES))

%_module_release: %_module
	$(LOG)
	$Qcp $*/bin/$*.mod $(RELEASE_DIR)/$*.mod
	
###############################################################################
# Install rule

# Rule to install bslug.
PHONY += install
install : $(addsuffix _module_install,$(MODULES))
	
%_module_install: $(BSLUGDIR)/modules
	$(LOG)
	$Qcp -r $* $(BSLUGDIR)/modules
	
$(BSLUGDIR)/modules:
	-$Qmkdir $(BSLUGDIR)/modules

# Rule to install bslug.
PHONY += uninstall
uninstall : 
	$(LOG)
	-$Qrm -rf $(BSLUGDIR)/modules

###############################################################################
# Clean rule

# Rule to clean files.
PHONY += clean
clean: $(addsuffix _module_clean,$(MODULES))
	
%_module_clean:
	$Q$(MAKE) -C $* clean

###############################################################################
# Phony targets

.PHONY : $(PHONY)