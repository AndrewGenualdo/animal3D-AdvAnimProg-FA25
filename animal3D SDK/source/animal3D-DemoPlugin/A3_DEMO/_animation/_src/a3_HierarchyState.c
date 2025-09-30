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
	
	a3_HierarchyState.c
	Implementation of transform hierarchy state.
*/

#include "../a3_HierarchyState.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


//-----------------------------------------------------------------------------

// initialize pose set given an initialized hierarchy and key pose count
a3i32 a3hierarchyPoseGroupCreate(a3_HierarchyPoseGroup *poseGroup_out, const a3_Hierarchy *hierarchy, const a3ui32 poseCount)
{
	// validate params and initialization states
	//	(output is not yet initialized, hierarchy is initialized)
	if (poseGroup_out && hierarchy && !poseGroup_out->hierarchy && hierarchy->nodes)
	{
		// determine memory requirements
		a3ui32 const nodeCount = hierarchy->numNodes;
		a3ui32 const hposeCount = poseCount, hposeSpace = sizeof(a3_HierarchyPose) * hposeCount;
		a3ui32 const sposeCount = hposeCount * nodeCount, sposeSpace = sizeof(a3_SpatialPose) * sposeCount;
		a3ui32 const channelSpace = sizeof(a3_SpatialPoseChannel) * nodeCount;
		a3ui32 const orderSpace = sizeof(a3_SpatialPoseEulerOrder) * nodeCount;
		a3ui32 const memreq = hposeSpace + sposeSpace + channelSpace + orderSpace;
		a3index i;

		// allocate everything (one malloc)
		poseGroup_out->hpose = (a3_HierarchyPose*)malloc(memreq);
		poseGroup_out->hpose->hpose_base = poseGroup_out->pose = (a3_SpatialPose*)(poseGroup_out->hpose + hposeCount);
		poseGroup_out->channel = (a3_SpatialPoseChannel*)(poseGroup_out->pose + sposeCount);
		poseGroup_out->order = (a3_SpatialPoseEulerOrder*)(poseGroup_out->channel + nodeCount);

		// set pointers
		for (i = 1; i < hposeCount; ++i)
		{
			poseGroup_out->hpose[i].hpose_base = poseGroup_out->hpose[i - 1].hpose_base + nodeCount;
			poseGroup_out->hpose[i].hpose_index = i * nodeCount;
		}

		// reset all data
		a3hierarchyPoseReset(poseGroup_out->hpose, sposeCount);
		memset(poseGroup_out->channel, a3poseChannel_none, channelSpace);
		memset(poseGroup_out->order, a3poseEulerOrder_xyz, orderSpace);
		poseGroup_out->hierarchy = hierarchy;
		poseGroup_out->hposeCount = hposeCount;
		poseGroup_out->poseCount = sposeCount;

		// done
		return 1;
	}
	return -1;
}

// release pose set
a3i32 a3hierarchyPoseGroupRelease(a3_HierarchyPoseGroup *poseGroup)
{
	// validate param exists and is initialized
	if (poseGroup && poseGroup->hierarchy)
	{
		// release everything (one free)
		free(poseGroup->hpose);

		// reset pointers
		poseGroup->hierarchy = 0;
		poseGroup->hpose = 0;
		poseGroup->pose = 0;
		poseGroup->channel = 0;
		poseGroup->order = 0;

		// done
		return 1;
	}
	return -1;
}

// load binary
a3i32 a3hierarchyPoseGroupLoadBinary(a3_HierarchyPoseGroup* poseGroup, a3_FileStream const* fileStream)
{
	FILE* fp;
	a3ui32 ret = 0;
	a3ui32 dataSize = 0;
	if (poseGroup && fileStream)
	{
		if (poseGroup->hierarchy && !poseGroup->pose)
		{
			fp = fileStream->stream;
			if (fp)
			{
//-----------------------------------------------------------------------------
//****TO-DO-ANIM-OPTIONAL: IMPLEMENT ME
//-----------------------------------------------------------------------------
				
				//fread
				// -> create posegroup function

//-----------------------------------------------------------------------------
//****END-TO-DO-OPTIONAL
//-----------------------------------------------------------------------------
			}
			return ret;
		}
	}
	return -1;
}

// save binary
a3i32 a3hierarchyPoseGroupSaveBinary(a3_HierarchyPoseGroup const* poseGroup, a3_FileStream const* fileStream)
{
	FILE* fp;
	a3ui32 ret = 0;
	if (poseGroup && fileStream)
	{
		if (poseGroup->hierarchy && poseGroup->pose)
		{
			fp = fileStream->stream;
			if (fp)
			{
//-----------------------------------------------------------------------------
//****TO-DO-ANIM-OPTIONAL: IMPLEMENT ME
//-----------------------------------------------------------------------------
				
				//fwrite
				// -> 

//-----------------------------------------------------------------------------
//****END-TO-DO-OPTIONAL
//-----------------------------------------------------------------------------
			}
			return ret;
		}
	}
	return -1;
}





//-----------------------------------------------------------------------------

// initialize hierarchy state given an initialized hierarchy
a3i32 a3hierarchyStateCreate(a3_HierarchyState *state_out, const a3_Hierarchy *hierarchy)
{
	// validate params and initialization states
	//	(output is not yet initialized, hierarchy is initialized)
	if (state_out && hierarchy && !state_out->hierarchy && hierarchy->nodes)
	{
		// determine memory requirements
		a3ui32 const nodeCount = hierarchy->numNodes;
		a3ui32 const hposeCount = sizeof(state_out->hpose) / sizeof(a3_HierarchyPose);
		a3ui32 const sposeCount = hposeCount * nodeCount;
		a3ui32 const memreq = sizeof(a3_SpatialPose) * sposeCount;
		a3index i;

		// allocate everything (one malloc)
		state_out->hpose->hpose_base = (a3_SpatialPose*)malloc(memreq);

		// set pointers
		state_out->hierarchy = hierarchy;
		for (i = 1; i < hposeCount; ++i)
		{
			state_out->hpose[i].hpose_base = state_out->hpose[i - 1].hpose_base + nodeCount;
			state_out->hpose[i].hpose_index = i * nodeCount;
		}

		// reset all data
		a3hierarchyPoseReset(state_out->hpose, sposeCount);

		// done
		return 1;
	}
	return -1;
}

// release hierarchy state
a3i32 a3hierarchyStateRelease(a3_HierarchyState *state)
{
	// validate param exists and is initialized
	if (state && state->hierarchy)
	{
		a3ui32 const hposeCount = sizeof(state->hpose) / sizeof(a3_HierarchyPose);
		a3ui32 i;

		// release everything (one free)
		free(state->hpose->hpose_base);

		// reset pointers
		state->hierarchy = 0;
		for (i = 0; i < hposeCount; ++i)
		{
			state->hpose[i].hpose_base = 0;
			state->hpose[i].hpose_index = 0;
		}

		// done
		return 1;
	}
	return -1;
}


//-----------------------------------------------------------------------------

// update inverse local-space matrices
a3i32 a3hierarchyStateUpdateLocalInverse(const a3_HierarchyState* state)
{
	if (state && state->hierarchy)
	{
		a3index i = 0;
//-----------------------------------------------------------------------------
//****TO-DO-ANIM-PROJECT-2: IMPLEMENT ME
//-----------------------------------------------------------------------------
		
		for (i = 0; i < state->hierarchy->numNodes; ++i)
		{
			a3real4x4TransformInverse(state->localSpaceInv->hpose_base[i].transformMat.m,
				state->localSpace->hpose_base[i].transformMat.m);
		}

//-----------------------------------------------------------------------------
//****END-TO-DO-PROJECT-2
//-----------------------------------------------------------------------------
		return i;
	}
	return -1;
}

// update inverse object-space matrices
a3i32 a3hierarchyStateUpdateObjectInverse(const a3_HierarchyState* state)
{
	if (state && state->hierarchy)
	{
		a3index i = 0;
//-----------------------------------------------------------------------------
//****TO-DO-ANIM-PROJECT-2: IMPLEMENT ME
//-----------------------------------------------------------------------------
		
		for (i = 0; i < state->hierarchy->numNodes; ++i) 
		{
			a3real4x4TransformInverse(state->objectSpaceInv->hpose_base[i].transformMat.m,
				state->objectSpace->hpose_base[i].transformMat.m);
		}

//-----------------------------------------------------------------------------
//****END-TO-DO-PROJECT-2
//-----------------------------------------------------------------------------
		return i;
	}
	return -1;
}

// update inverse object-space bind-to-current matrices
a3i32 a3hierarchyStateUpdateObjectBindToCurrent(const a3_HierarchyState* state, const a3_HierarchyState* state_bind)
{
	if (state && state->hierarchy && state_bind && state_bind->hierarchy)
	{
		a3index i = 0;
//-----------------------------------------------------------------------------
//****TO-DO-ANIM-PROJECT-2: IMPLEMENT ME
//-----------------------------------------------------------------------------
		
		for (i = 0; i < state->hierarchy->numNodes; ++i)
		{
			a3real4x4Product(state->objectSpaceBindToCurrent->hpose_base[i].transformMat.m,
				state->objectSpace->hpose_base[i].transformMat.m,
				state_bind->objectSpaceInv->hpose_base[i].transformMat.m);
		}

//-----------------------------------------------------------------------------
//****END-TO-DO-PROJECT-2
//-----------------------------------------------------------------------------
		return i;
	}
	return -1;
}


//-----------------------------------------------------------------------------

// load HTR file, read and store complete pose group and hierarchy
a3i32 a3hierarchyPoseGroupLoadHTR(a3_HierarchyPoseGroup* poseGroup_out, a3_Hierarchy* hierarchy_out, const a3byte* resourceFilePath)
{
	if (poseGroup_out && !poseGroup_out->hierarchy && hierarchy_out && !hierarchy_out->nodes && resourceFilePath && *resourceFilePath)
	{
//-----------------------------------------------------------------------------
//****TO-DO-ANIM-PROJECT-2: IMPLEMENT ME
//-----------------------------------------------------------------------------

		//written by Andrew Genualdo
		enum Section { NONE, HEADER, SEGMENTS, BASEPOS, FRAME, END} section = NONE;

		
		//buffer for each line
		char line[512]; 

		//remember which node we're on
		char currentNodeName[256] = "";

		//make sure it opens right
		FILE* file = fopen(resourceFilePath, "r");
		if (file == NULL) return EXIT_FAILURE;

		//header data
		/*a3i32 numSegments = 0;
		a3i32 numFrames = 0;
		a3i32 dataFrameRate = 0;
		a3f32 scaleFactor = 1.0;*/
		a3i32 numSegments = 0, numFrames = 0, dataFrameRate = 0;
		a3f32 scaleFactor = 1.0;


		a3ui32 counter = 0;
		

		//read line by line
		while (fgets(line, sizeof(line), file))
		{
			
			if (line[0] == '#') continue;
			if (line[0] == '[') //update which section we are in
			{ 
				counter = 0;
				if (strncmp(line, "[Header]", 8) == 0) section = HEADER;
				else if (strncmp(line, "[SegmentNames&Hierarchy]", 24) == 0) section = SEGMENTS;
				else if (strncmp(line, "[BasePosition]", 14) == 0) section = BASEPOS;
				else if (strncmp(line, "[EndOfFile]", 11) == 0) section = END;
				else //this is the only one with variable header names
				{
					//extract node name
					if (sscanf(line, "[%255[^]]]", currentNodeName) != 1)
					{
						printf("Failed to parse frame header: '%s'\n", line);
						return EXIT_FAILURE;
					}
					printf("Arrived at node: '%s'\n", currentNodeName);
					section = FRAME;
				}
				continue;
			}
			
			switch (section) 
			{
			case HEADER: 
			{
				//extract relevant data from HEADER section
				switch (counter)
				{
				case 3: if (sscanf(line, "NumSegments %d", &numSegments) != 1) return EXIT_FAILURE; break;
				case 4: if (sscanf(line, "NumFrames %d", &numFrames) != 1) return EXIT_FAILURE; break;
				case 5: if (sscanf(line, "DataFrameRate %d", &dataFrameRate) != 1) return EXIT_FAILURE; break;
				case 11: if (sscanf(line, "ScaleFactor %f", &scaleFactor) != 1) return EXIT_FAILURE; break;
				}
				break;
			}
			case SEGMENTS: 
			{
				if (counter == 0) //first segment only
				{ 
					if (a3hierarchyCreate(hierarchy_out, numSegments, NULL) != numSegments) 
					{
						printf("failed to make hierarchy");
						return EXIT_FAILURE;
					}
				}

				//strip newline
				line[strcspn(line, "\r\n")] = 0;

				//scan line for child and parent
				a3byte child[a3node_nameSize], parent[a3node_nameSize];
				if (sscanf(line, "%s %s", child, parent) != 2) 
				{
					printf("Failed on node: '%s'\n", line);
					return EXIT_FAILURE;
				}

				//get parent index
				a3i32 parentIndex;
				if (strcmp(parent, "GLOBAL") == 0) parentIndex = -1;
				else parentIndex = a3hierarchyGetNodeIndex(hierarchy_out, parent);

				//get parent from hierarchy
				if (parentIndex == -1 && strcmp(parent, "GLOBAL") != 0) 
				{
					printf("Parent not found: '%s'\n", parent);
					return EXIT_FAILURE;
				}

				//set new child node with parentIndex
				if (a3hierarchySetNode(hierarchy_out, counter, parentIndex, child) == -1) 
				{
					printf("Failed to set node: '%s'\n", child);
					return EXIT_FAILURE;
				}

				printf("added node '%s' | '%s'\n", child, parent);
				break;
			}
			case BASEPOS: {
				if (counter == 0) //first line only
				{ 
					a3hierarchyPoseGroupCreate(poseGroup_out, hierarchy_out, hierarchy_out->numNodes);
				}
				char name[256];
				a3f32 tx, ty, tz, rx, ry, rz, boneLength;

				//load data from line
				if (sscanf(line, "%s %f %f %f %f %f %f %f", name, &tx, &ty, &tz, &rx, &ry, &rz, &boneLength) != 8)
				{
					printf("Failed to parse base position: '%s'\n", line);
					return EXIT_FAILURE;
				}

				//get node index
				a3i32 nodeIndex = a3hierarchyGetNodeIndex(hierarchy_out, name);
				if (nodeIndex == -1) 
				{
					printf("Node '%s' not found in hierarchy\n", name);
					return EXIT_FAILURE;
				}

				//get allocated pose in poseGroup
				a3_SpatialPose* pose = &poseGroup_out->pose[nodeIndex];
				a3spatialPoseReset(pose);
				a3spatialPoseSetTranslation(pose, tx, ty, tz);
				a3spatialPoseSetRotation(pose, rx, ry, rz);
				//set bone length??? I don't know where to put this
				break;
			}
			case FRAME: {
				if (counter == 0) // first line of first FRAME section
				{
					poseGroup_out->poseCount = hierarchy_out->numNodes * numFrames;
					poseGroup_out->pose = (a3_SpatialPose*)malloc(sizeof(a3_SpatialPose) * poseGroup_out->poseCount);
					if (!poseGroup_out->pose)
					{
						printf("Failed to allocate pose array for frames.\n");
						return EXIT_FAILURE;
					}

					// Optionally reset the hpose pointer
					poseGroup_out->hpose[0].hpose_base = poseGroup_out->pose;
					poseGroup_out->hpose[0].hpose_index = 0;
				}

				a3i32 nodeIndex = a3hierarchyGetNodeIndex(hierarchy_out, currentNodeName);
				if (nodeIndex == -1) 
				{
					printf("Node '%s' not found in hierarchy\n", currentNodeName);
					return EXIT_FAILURE;
				}

				a3i32 frameIndex;
				a3f32 tx, ty, tz, rx, ry, rz, boneScale;

				if (sscanf(line, "%d %f %f %f %f %f %f %f", &frameIndex, &tx, &ty, &tz, &rx, &ry, &rz, &boneScale) != 8)
				{
					printf("Failed to parse frame line: '%s'\n", line);
					return EXIT_FAILURE;
				}

				//get allocated pose in poseGroup
				a3_SpatialPose* pose = &poseGroup_out->pose[nodeIndex + frameIndex * hierarchy_out->numNodes];
				a3spatialPoseReset(pose);
				a3spatialPoseSetTranslation(pose, tx, ty, tz);
				a3spatialPoseSetRotation(pose, rx, ry, rz);

				break;
			}
			}
			counter++;
		}

		// Close the file
		fclose(file);
		printf("loaded file: %s\n", resourceFilePath);
		printf("segments: %d\n", numSegments);
		printf("frames: %d\n", numFrames);
		printf("rate: %d\n", dataFrameRate);
		printf("scale: %f\n", scaleFactor);
		return 0;
		

//-----------------------------------------------------------------------------
//****END-TO-DO-PROJECT-2
//-----------------------------------------------------------------------------
	}
	return -1;
}

// load BVH file, read and store complete pose group and hierarchy
a3i32 a3hierarchyPoseGroupLoadBVH(a3_HierarchyPoseGroup* poseGroup_out, a3_Hierarchy* hierarchy_out, const a3byte* resourceFilePath)
{
	if (poseGroup_out && !poseGroup_out->hierarchy && hierarchy_out && !hierarchy_out->nodes && resourceFilePath && *resourceFilePath)
	{
//-----------------------------------------------------------------------------
//****TO-DO-ANIM-OPTIONAL: IMPLEMENT ME
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
//****END-TO-DO-OPTIONAL
//-----------------------------------------------------------------------------
	}
	return -1;
}

// save HTR file, read and store complete pose group and hierarchy
a3i32 a3hierarchyPoseGroupSaveHTR(const a3_HierarchyPoseGroup* poseGroup_in, const a3_Hierarchy* hierarchy_in, const a3byte* resourceFilePath)
{
	if (poseGroup_in && poseGroup_in->hierarchy && hierarchy_in && hierarchy_in->nodes && resourceFilePath && *resourceFilePath)
	{
//-----------------------------------------------------------------------------
//****TO-DO-ANIM-OPTIONAL: IMPLEMENT ME
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
//****END-TO-DO-OPTIONAL
//-----------------------------------------------------------------------------
	}
	return -1;
}

// save BVH file, read and store complete pose group and hierarchy
a3i32 a3hierarchyPoseGroupSaveBVH(const a3_HierarchyPoseGroup* poseGroup_in, const a3_Hierarchy* hierarchy_in, const a3byte* resourceFilePath)
{
	if (poseGroup_in && poseGroup_in->hierarchy && hierarchy_in && hierarchy_in->nodes && resourceFilePath && *resourceFilePath)
	{
//-----------------------------------------------------------------------------
//****TO-DO-ANIM-OPTIONAL: IMPLEMENT ME
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
//****END-TO-DO-OPTIONAL
//-----------------------------------------------------------------------------
	}
	return -1;
}


//-----------------------------------------------------------------------------
