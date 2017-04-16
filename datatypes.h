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
// Purpose: Contains various useful data type definitions to simplify working	//
//	with memory.								//
//										//
//==============================================================================//

#ifndef DATATYPES_H
#define DATATYPES_H

#include <stdint.h>
#ifdef __cplusplus
#include <vector.h>
#endif

#define P64_TO_P(p64)					((void *)(p64))
#define P32_TO_P(p32)					P64_TO_P(p32)
#define P16_TO_P(p16)					P64_TO_P(p16)
#define P_TO_P64(p)					((uint64)(p))
#define P_TO_P32(p)					((uint32)(p))
#define P_TO_P16(p)					((uint16)(p))

typedef uint8_t						uint8;
typedef uint16_t					uint16;
typedef uint32_t					uint32;
typedef uint64_t					uint64;
typedef int8_t						int8;
typedef int16_t						int16;
typedef int32_t						int32;
typedef int64_t						int64;
typedef float						float32;
typedef double						float32_64;
typedef long double					float64;
#ifdef __cplusplus
typedef Vector<int64, 2>				Vector2D;
typedef Vector<int64, 3>				Vector3D;
typedef Vector<int64, 4>				Vector4D;
typedef Vector<float32, 2>				Vector2D_fl32;
typedef Vector<float32, 3>				Vector3D_fl32;
typedef Vector<float32, 4>				Vector4D_fl32;
typedef Vector<float64, 2>				Vector2D_fl64;
typedef Vector<float64, 3>				Vector3D_fl64;
typedef Vector<float64, 4>				Vector4D_fl64;
#else
typedef struct {int64 ix, iy;}				Vector2D;
typedef struct {int64 ix, iy, iz;}			Vector3D;
typedef struct {int64 ix, iy, iz, it;}			Vector4D;
typedef struct {float32 flx32, fly32;}			Vector2D_fl32;
typedef struct {float32 flx32, fly32, flz32;}		Vector3D_fl32;
typedef struct {float32 flx32, fly32, flz32, flt32;}	Vector4D_fl32;
typedef struct {float64 flx64, fly64;}			Vector2D_fl64;
typedef struct {float64 flx64, fly64, flz64;}		Vector3D_fl64;
typedef struct {float64 flx64, fly64, flz64, flt64;}	Vector4D_fl641;
#endif

//Title:	var64
//Purpose:	Generic 64-bit variable, with all appropriate primitive containers
//		suitable to be used (useful for loose type safety)
typedef union {
	uint64	pointer64;
	uint64	var64;
	int64	int64;
	float64	float64;
	uint32	pointer32[2];
	uint32	var32[2];
	int32	int32[2];
	float32	float32[2];
	uint16	pointer16[4];
	uint16	var16[4];
	int16	int16[4];
	uint8	var8[8];
	int8	int8[8];
	char	char8[8];
} var64;

//Title:	var32
//Purpose:	Generic 32-bit variable, with all appropriate primitive containers
//		suitable to be used (useful for loose type safety)
typedef union {
	uint32	pointer32;
	uint32	var32;
	int32	int32;
	float32	float32;
	uint16	pointer16[2];
	uint16	var16[2];
	int16	int16[2];
	uint8	var8[4];
	int8	int8[4];
	char	char8[4];
} var32;

//Title:	var16
//Purpose:	Generic 16-bit variable, with all appropriate primitive containers
//		suitable to be used (useful for loose type safety)
typedef union {
	uint16	pointer16;
	uint16	var16;
	int16	int16;
	uint8	var8[2];
	int8	int8[2];
	char	char8[2];
} var16;

//Title:	var8
//Purpose:	Generic 8-bit variable, with all appropriate primitive containers
//		suitable to be used (useful for loose type safety)
typedef union {
	uint8	var8;
	int8	int8;
	char	char8;
} var8;

#endif
