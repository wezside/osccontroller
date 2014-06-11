LiveOSC OpenFrameworks Controller
=================================

OSC Controller class to use with LiveOSC + Ableton + OpenFrameworks

Requirements
------------

* OpenFrameworks 0.8.x
* ofxOsc
* Ableton Live 9 with Max for Live
* LiveOSC
* Port 9000 open on firewall
* JSONXX library 
	* add .h files to your compiler CFLAGS - see config.make
	* Remove the jsonxx_test.cc file when using Make to compile as this will conflict with OF