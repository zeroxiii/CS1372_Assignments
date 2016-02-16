###################################################################
#	Make file for Breakout.						  
#																  
#	NOTE: Do not change this file unless otherwise instructed.    
#																  
###################################################################

DIR = c:/gba_studio
include $(DIR)/system/master.mak



 ####################
# GBA ROM Image Name #
 ####################

PROGNAME=“breakout”



 #########################################
# Set a list of files you want to compile #
 #########################################
 
OFILES += main.o breakoutLib.o myLib.o text.o



 #########################################################
# Compile using Krawall (sound stuff, don't mess with it) #
 #########################################################
 
USE_KRAWALL=no
KRAWALL_IS_REGISTERED=no
KRAWALL_FILES=



 ######################################
# Standard Makefile targets start here #
 ######################################
all : $(PROGNAME).$(EXT) clean



 ##############################################
# Most Makefile targets are predefined for you,#
# such as vba, clean ... in the following file #
 ##############################################

include $(DIR)/system/standard-targets.mak



 #####################################
# Custom  Makefile targets start here #
 #####################################

gfx: makefile




