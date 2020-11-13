
SubDir :=$(CURDIR)/Main
SubDir +=$(CURDIR)/MD5
SubDir +=$(CURDIR)/SHA1
SubDir +=$(CURDIR)/SHA256

ObjDir :=$(CURDIR)/O_files

SRC_PATH=$(CURDIR)

DIRS =$(shell ls -l | grep ^d | awk '{print $$9}')
# Find all folders in the current dir

SubDirToMak = $(filter-out O_files,$(DIRS))

# filter-out O_files folder


export HomeDir=$(CURDIR)

all: clean $(SubDirToMak) Buildexe

$(SubDirToMak):ECHO
	make -C $(CURDIR)/$@ -f SubDir.mak
ECHO:
	@echo Folders to build is $(SubDirToMak)

Buildexe:
	make -C $(ObjDir) -f makeexe.mak

clean:
	rm -f $(ObjDir)/*.o
	rm -f $(ObjDir)/*.exe

Show:
	@echo $(DIRS)
	@echo $(SRC_PATH)
	@echo $(SubDirToMak)