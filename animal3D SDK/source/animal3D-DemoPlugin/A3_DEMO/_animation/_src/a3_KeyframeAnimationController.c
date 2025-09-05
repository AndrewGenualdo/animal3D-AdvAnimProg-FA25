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

		//1. time step: add dt
		clipCtrl->clipTime_sec += dt;
		clipCtrl->keyframeTime_sec += dt;

		//2. resolve keyframe
		a3f64 t = clipCtrl->keyframeTime_sec; //time through current keyframe
		a3f64 t1 = clipCtrl->clipPool->keyframe[clipCtrl->keyframeIndex].duration_sec; //keyframe duration
		a3f64 t0 = t1 - t; //start of keyframe


		//	a. paused: dt = 0
		if (dt == 0.0f) return -1; //#1 : if time isn't passing, why bother doing anything?

		//	b. forward: dt > 0
		if (dt > 0) {
			while (t >= t1) {//		ii. steps(s) taken
				clipCtrl->keyframeIndex++;
				if (clipCtrl->keyframeIndex > clipCtrl->clipPool->keyframeCount)  //			iii. clip exited
				{
					t -= t1;
					clipCtrl->keyframeTime_sec = t;
					clipCtrl->clipTime_sec = t;
					clipCtrl->keyframeIndex = 0;
					t1 = clipCtrl->keyframe[clipCtrl->keyframeIndex].duration_sec;
					t0 = t1 - t;
					a3f64 u = t / t1;
					clipCtrl->keyframeParam = u;
				}
				else {
					t -= t1;
					t1 = clipCtrl->keyframe[clipCtrl->keyframeIndex].duration_sec;
					t0 = t1 - t;
				}
				
			}
		//	c. reverse: dt < 0
		} else { 
			while (t < t0) { //		ii. step(s) taken
				clipCtrl->keyframeIndex--;
				if (clipCtrl->keyframeIndex < 0)  //			iii. clip exited
				{
					for (a3ui32 i = 0; i < clipCtrl->clipPool->keyframeCount; i++) clipCtrl->clipTime_sec += clipCtrl->keyframe[i].duration_sec;
					clipCtrl->keyframeIndex = clipCtrl->clipPool->keyframeCount - 1;
					t1 = clipCtrl->keyframe[clipCtrl->keyframeIndex].duration_sec;
					t += t1;
					clipCtrl->keyframeTime_sec = t;
					t0 = t1 - t;
					a3f64 u = t / t1;
					clipCtrl->keyframeParam = u;
				}
				else {
					t1 = clipCtrl->keyframe[clipCtrl->keyframeIndex].duration_sec;
					t += t1;
					t0 = t1 - t;
				}
				
			}
		}

		//3. normalized keyframe/clip time: relative time/duration
		a3f64 u = t / t1;
		
		clipCtrl->keyframeParam = u;
		clipCtrl->keyframeTime_sec = t;


		//		i. stop
		//		ii. step(s) taken
		//		iii. clip exited
		//	c. reverse: dt < 0
		//		i. stop
		//		ii. steps(s) taken
		//		iii. clip exited
		//3. normalized keyframe/clip time: relative time/duration

//-----------------------------------------------------------------------------
//****END-TO-DO-PROJECT-1
//-----------------------------------------------------------------------------
	}
	return -1;
}


//-----------------------------------------------------------------------------
