/*
 *
 * STD_TYPES.h
 *
 */ 


#ifndef STD_TYPES_H_
#define STD_TYPES_H_

typedef unsigned char	   u8;
typedef unsigned short int u16;
typedef unsigned 		   u32;
typedef unsigned long long u64;

typedef signed char		   s8;
typedef signed short int   s16;
typedef signed long  int   s32;

typedef float 			   f32;
typedef double			   f64;

#ifndef NULL
#define NULL	((void*)0)
#endif

typedef enum {
	false =0,
	true
}enuBOOL;

typedef enum
{
	NO_ERR = 0,
	ERR = 1,
}Err_t;



#endif /* STD_TYPES_H_ */
