# Farm-Window Alpha

### OSC MESSAGE


#### FROM SYNC MANAGER
##### SEND:
/sync/play/nowPlayingFile: (string) 	// filename

/sync/play/nowPlayingStart: (bool)		//  
 
/sync/play/nowPlayingStop: (bool)		// 

/sync/play/type: (int)					// photo or video

/sync/play/nowPlayingStartTime (int)	// start time in seconds


##### RECEIVE:



#### IN PLAYER WITH MACHINE_{machine_name} 

#### SEND:

/sync/start/machine: (string)			// kickstart signal

/sync/play/{machine_name}/currentFrame: (int)	// current frame number of machine


#### RECEIVE:
/sync/play/{machine_name}/frameJump: (int)	 // frames to be jumped

/sync/play/nowPlayingFile: (string) 	// filename

/sync/play/nowPlayingStart: (bool)		//  

/sync/play/nowPlayingStop: (bool)		// 

/sync/play/type: (int)					// photo or video

/sync/play/nowPlayingKickTime (int)	// start time in seconds
