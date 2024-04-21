#ifndef _LOCK_H_
#define _LOCK_H_

#define CODELEN 12

typedef enum
{
	LockState_Blank,
	LockState_Clear,
	LockState_Active,
	LockState_Solved
} LockState;

typedef struct {
	int code[CODELEN];
	int numberOfCodes;
	int currentCodeIndex;

	float angle;

	LockState lockstate;
} Lock;

void InitLock(Lock* lock);

void GenerateNewCodes(Lock* lock,  int numberOfCodes);

void SetLockAngle(float a);

void SetLockAngleChange(float a);

float ConvertNumberToAngle(int number);

void SetNumber(int number);

void DrawLock(Lock* lock);

void UpdateLock(Lock* lock);

#endif