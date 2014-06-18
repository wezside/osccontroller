LiveOSC OpenFrameworks Controller
=================================

OSC Controller class to use with LiveOSC + Ableton + OpenFrameworks

Requirements
------------

* OpenFrameworks 0.8.x
* ofxOsc addon
* Ableton Live 9 with Max for Live
* LiveOSC
* Port 9000 open on firewall
* Setup Midi device in Ableton using virtual Midi port + Remote switch
* JSONXX library 
	* add .h files to your compiler CFLAGS - see config.make
	* Remove the jsonxx_test.cc file when using Make to compile as this will conflict with OF
* ableton.json is only needed for use with setGroupXX()

The map file ableton.json is currently a carbon copy of your Live Session set-up in Ableton. Your setup must make use of groups if you want to use this file. It is possible to not use groups by sioply not using this config mapping file. OSCController includes a liveOSCAPI() method for makinbg liveOSC API calls directly.