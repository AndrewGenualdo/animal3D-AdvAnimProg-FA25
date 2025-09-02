/*
	Copyright 2011-2025 Daniel S. Buckstein

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

/*
	animal3D SDK: Minimal 3D Animation Framework
	By Daniel S. Buckstein
	
	a3_KeyframeAnimationController.c
	Implementation of keyframe animation controller.
*/

#include "../a3_KeyframeAnimationController.h"

#include <string.h>


// macros to help with names
#define A3_CLIPCTRL_DEFAULTNAME		("unnamed clip ctrl")
#define A3_CLIPCTRL_SEARCHNAME		((ctrlName && *ctrlName) ? ctrlName : A3_CLIPCTRL_DEFAULTNAME)


//-----------------------------------------------------------------------------

// initialize clip controller
a3i32 a3clipControllerInit(a3_ClipController* clipCtrl_out, const a3byte ctrlName[a3keyframeAnimation_nameLenMax], const a3_ClipPool* clipPool, const a3ui32 clipIndex_pool, const a3i32 playback_step, const a3f64 playback_stepPerSec)
{
	a3i32 const ret = a3clipControllerSetClip(clipCtrl_out, clipPool, clipIndex_pool, playback_step, playback_stepPerSec);
	if (ret >= 0)
	{
		strncpy(clipCtrl_out->name, A3_CLIPCTRL_SEARCHNAME, a3keyframeAnimation_nameLenMax);
		return ret;
	}
	return -1;
}

// update clip controller
a3i32 a3clipControllerUpdate(a3_ClipController* clipCtrl, a3f64 dt)
{
	if (clipCtrl && clipCtrl->clipPool)
	{
//-----------------------------------------------------------------------------
//****TO-DO-ANIM-PROJECT-1: IMPLEMENT ME
//-----------------------------------------------------------------------------

		/*for (int i = 0; i < clipCtrl->clipPool->keyframeCount; i++) {
			a3_Keyframe* keyframe = &clipCtrl->clipPool->keyframe[i];
			//a3f64 u = (keyframe. - t0) / keyframe->duration_sec;
			//a3f64 u = (t - t0) / (t1 - t0); 
			//t0 = start of keyframe relative to clip (which is on 0.0 -> 1.0)
			//t1 = end of keyframe relative to clip (which is on 0.0 -> 1.0)
			a3f64 u = (keyframe->)
		}*/


		//1. time step: add dt
		clipCtrl->clipTime_sec += dt;
		clipCtrl->keyframeTime_sec += dt;

		//2. resolve keyframe
		a3f64 t = clipCtrl->keyframeTime_sec; //time through current keyframe
		a3f64 t1 = clipCtrl->clipPool->keyframe[clipCtrl->keyframeIndex].duration_sec; //keyframe duration
		a3f64 t0 = t1 - t; //start of keyframe

		//	a. paused: dt = 0
		if (dt == 0.0f) return; //#1 : if time isn't passing, why bother doing anything?

		//	b. forward: dt > 0
		if (dt > 0) {
			while (t >= t1) {//		ii. steps(s) taken
				t -= t1;
				clipCtrl->keyframeIndex++;
				if (clipCtrl->keyframeIndex > clipCtrl->clipPool->keyframeCount) return; //			iii. clip exited
				t1 = clipCtrl->keyframe[clipCtrl->keyframeIndex].duration_sec;
				t0 = t1 - t;
			}
		} else { //	c. reverse: dt < 0
			while (t < t0) { //		ii. step(s) taken
				clipCtrl->keyframeIndex--;
				if (clipCtrl->keyframeIndex < 0) return; //			iii. clip exited
				t1 = clipCtrl->keyframe[clipCtrl->keyframeIndex].duration_sec;
				t += t1;
				t0 = t1 - t;
			}
		}

		//3. normalized keyframe/clip time: relative time/duration
		a3f64 u = 


		//		i. stop
		//		ii. step(s) taken
		//		iii. clip exited
		//	c. reverse: dt < 0
		//		i. stop
		//		ii. steps(s) taken
		//		iii. clip exited
		//3. normalized keyframe/clip time: relative time/duration

		
		
		

		while (t >= t1) {
			t -= t1;
			clipCtrl->keyframeIndex++;

		}

		
		//while (!(t >= t0 && t < t1)) {
			//??? I get the general idea but wtf is he talking about with this loop
		//}

		//#1 not moving (dt = 0.0)
		//moving forward
		// - #2 forward stay in keyframe 
		// - #3 forward jump to future keyframe (t >= t1)
		// - #4 forward end of clip
		//moving backward
		// - #5 backward stay in keyframe
		// - #6 backward jump to previous keyframe (t < t0)
		// - #7 backward beginning of clip

		/*a3f64 t = 0.5f + dt; //seconds through current keyframe?
		a3f64 t1 = clipCtrl->keyframe[clipCtrl->keyframeIndex].duration_sec; //keyframe duration
		while (t >= t1) {
			t -= t1;
			clipCtrl->keyframeIndex++;
			if (clipCtrl->keyframeIndex > clipCtrl->clipPool->keyframeCount) clipCtrl->keyframeIndex = 0;
			t1 = clipCtrl->keyframe[clipCtrl->keyframeIndex].duration_sec;
		}
		a3i32 keyIndex = clipCtrl->keyframeIndex;*/



		/*clipCtrl->clipTime_sec += dt;

		for (int i = 0; i < clipCtrl->clipPool->clipCount; i++) {
			a3_Clip* clip = &clipCtrl->clipPool->clip[i];
			
		}

		

		for (int i = 0; i < clipCtrl->clipPool->sampleCount; i++) {
			a3_Sample* sample = &clipCtrl->clipPool->sample[i];
		}*/

		/*a3i32 a = a3clipGetIndexInPool(clipCtrl->clipPool, "teapot_morph");
		a3_Keyframe* keyframe = NULL;
		a3_Sample* sample1 = NULL;
		a3_Sample* sample2 = NULL;
		a3f64 playbackStepPerSec = 100.0;
		a3i32 b = a3keyframeInit(keyframe, sample1, sample2, playbackStepPerSec);*/
		//a3_ClipPool* clipPool = NULL;
		//a3i32 c = a3clipPoolCreate(clipPool, 100, 100, 100);
		//a3_ClipController* clipController;
		//a3i32 d = a3clipControllerInit(clipController, "test", clipPool, );

//-----------------------------------------------------------------------------
//****END-TO-DO-PROJECT-1
//-----------------------------------------------------------------------------
	}
	return -1;
}


//-----------------------------------------------------------------------------
