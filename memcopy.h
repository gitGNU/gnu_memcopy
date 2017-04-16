//===================== Copyright © 2017, Jared Ryan Bills =====================//
//    This program is free software: you can redistribute it and/or modify	//
//    it under the terms of the GNU Lesser General Public License as published	//
//    by the Free Software Foundation, either version 3 of the License, or	//
//    (at your option) any later version.					//
//										//
//    This program is distributed in the hope that it will be useful,		//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of		//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the		//
//    GNU Lesser General Public License for more details.			//
//										//
//    You should have received a copy of the GNU Lesser General Public License	//
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.	//
//==============================================================================//
//										//
// Purpose: Contains a reimplementation of the ever-used memcpy (renamed	//
//	memcopy here). Includes memcopy derivatives for various bus sizes.	//
//										//
//==============================================================================//

#ifndef MEMCOPY_H
#define MEMCOPY_H

#include "datatypes.h"
#include <stddef.h>
#include <assert.h>

inline void * memcopy8(void *, void *, const size_t);
inline void * memcopy16(void *, void *, const size_t);
inline void * memcopy32(void *, void *, const size_t);
inline void * memcopy64(void *, void *, const size_t);

//Title:		memcopy
//Purpose:		Copies memory from one portion of memory to another of a_byteLen size,
//			keeping bus size in mind.
//Parameters:	a_dest - Destination Address to copy to
//			a_src - Source Address to copy from
//			a_byteLen - Number of bytes to copy
//Return:		Address of destination buffer/structure (legacy compatibility).
//TODO:			Address in-built CPU features for faster memory vector operations.
//			Address memory alignment
inline void * memcopy(void * a_dest, void * a_src, const size_t a_byteLen) {
	if (a_byteLen & 0x7)
		memcopy64(a_dest, a_src, a_byteLen);
	else if (a_byteLen & 0x3) {
		void * dest = a_dest;
		void * src = a_src;
		size_t len = a_byteLen;
		if (len > 8) {
			register size_t offset = len & ~(uint64)(0x7);
			memcopy64(dest, src, offset);
			dest = (void *)((size_t)(a_dest) + offset);
			src = (void *)((size_t)(a_src) + offset);
			len = a_byteLen & 0x7;
		}
		memcopy32(dest, src, len);
	}
	else if (a_byteLen & 0x1) {
		void * dest = a_dest;
		void * src = a_src;
		size_t len = a_byteLen;
		if (len > 8) {
			register size_t offset = len & ~(size_t)(0x7);
			memcopy64(dest, src, offset);
			dest = (void *)((size_t)(a_dest) + offset);
			src = (void *)((size_t)(a_src) + offset);
			len = a_byteLen & 0x7;
		}
		if (len > 4) {
			register size_t offset = len & ~(size_t)(0x3);
			memcopy32(dest, src, offset);
			dest = (void *)((size_t)(a_dest) + offset);
			src = (void *)((size_t)(a_src) + offset);
			len = a_byteLen & 0x3;
		}
		memcopy16(dest, src, len);
	}
	else {
		void * dest = a_dest;
		void * src = a_src;
		size_t len = a_byteLen;
		if (len > 8) {
			register size_t offset = len & ~(size_t)(0x7);
			memcopy64(dest, src, offset);
			dest = (void *)((size_t)(a_dest) + offset);
			src = (void *)((size_t)(a_src) + offset);
			len = a_byteLen & 0x7;
		}
		if (len > 4) {
			register size_t offset = len & ~(size_t)(0x3);
			memcopy32(dest, src, offset);
			dest = (void *)((size_t)(a_dest) + offset);
			src = (void *)((size_t)(a_src) + offset);
			len = a_byteLen & 0x3;
		}
		if (len > 2) {
			register size_t offset = len & ~(size_t)(0x1);
			memcopy16(dest, src, offset);
			dest = (void *)((size_t)(a_dest) + offset);
			src = (void *)((size_t)(a_src) + offset);
			len = a_byteLen & 0x1;
		}
		memcopy8(dest, src, len);
	}
	return a_dest;
}
//Title:		memcopy8
//Purpose:		Copies memory from one portion of memory to another of a_byteLen size,
//			one bytes at a time, but does not transfer tailing memory if less
//			than 8 bits wide.
//Parameters:	a_dest - Destination Address to copy to
//			a_src - Source Address to copy from
//			a_byteLen - Number of bytes to copy
//Return:		Address of destination buffer/structure (legacy compatibility).
//TODO:			Address in-built CPU features for faster memory vector operations.
//			Address memory alignment
inline void * memcopy8(void * a_dest, void * a_src, const size_t a_byteLen) {
	for (uintptr c = 0; c < a_byteLen; ++c)
		*((uint8 *)(a_dest)+c) = *((uint8 *)(a_src)+c);
	return a_dest;
}
//Title:		memcopy16
//Purpose:		Copies memory from one portion of memory to another of a_byteLen size,
//			two bytes at a time, but does not transfer tailing memory if less
//			than 16 bits wide.
//Parameters:	a_dest - Destination Address to copy to
//			a_src - Source Address to copy from
//			a_byteLen - Number of bytes to copy
//Return:		Address of destination buffer/structure (legacy compatibility).
//TODO:			Address in-built CPU features for faster memory vector operations.
//			Address memory alignment
inline void * memcopy16(void * a_dest, void * a_src, const size_t a_byteLen) {
	assert(!(a_byteLen & 0x1));
	for (uintptr c = 0; c < a_byteLen; c += 2)
		*((uint16 *)(a_dest)+c) = *((uint16 *)(a_src)+c);
	return a_dest;
}
//Title:		memcopy32
//Purpose:		Copies memory from one portion of memory to another of a_byteLen size,
//			four bytes at a time, but does not transfer tailing memory if less
//			than 32 bits wide.
//Parameters:	a_dest - Destination Address to copy to
//			a_src - Source Address to copy from
//			a_byteLen - Number of bytes to copy
//Return:		Address of destination buffer/structure (legacy compatibility).
//TODO:			Address in-built CPU features for faster memory vector operations.
//			Address memory alignment
inline void * memcopy32(void * a_dest, void * a_src, const size_t a_byteLen) {
	assert(!(a_byteLen & 0x3));
	for (uintptr c = 0; c < a_byteLen; c += 4)
		*((uint32 *)(a_dest)+c) = *((uint32 *)(a_src)+c);
	return a_dest;
}
//Title:		memcopy64
//Purpose:		Copies memory from one portion of memory to another of a_byteLen size,
//			eight bytes at a time, but does not transfer tailing memory if less
//			than 64 bits wide.
//Parameters:	a_dest - Destination Address to copy to
//			a_src - Source Address to copy from
//			a_byteLen - Number of bytes to copy
//Return:		Address of destination buffer/structure (legacy compatibility).
//TODO:			Address in-built CPU features for faster memory vector operations.
//			Address memory alignment
inline void * memcopy64(void * a_dest, void * a_src, const size_t a_byteLen) {
	assert(!(a_byteLen & 0x7));
	for (uintptr c = 0; c < a_byteLen; c += 8)
		*((uint64 *)(a_dest)+c) = *((uint64 *)(a_src)+c);
	return a_dest;
}

#endif

