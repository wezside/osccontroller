LiveOSC OpenFrameworks Controller
=================================

OSC Controller class to use with LiveOSC + Ableton + OpenFrameworks

Requirements
------------

* OpenFrameworks 0.8.x
* ofxOsc
* Ableton Live 9 with Max for Live
* LiveOSC
* Need a virtual midi port set
	* loopMidi for Windows 
* Port 9000 open on firewall
* Setup Midi device in Ableton using virtual Midi port + Remote switch
* JSONXX library 
	* add .h files to your compiler CFLAGS - see config.make
	* Remove the jsonxx_test.cc file when using Make to compile as this will conflict with OF
* ableton.json is only needed for use with setGroupXX()