#pragma once

#include <ntifs.h>

#pragma pack(push, 1)

typedef struct _GATE_DESCRIPTOR
{
	USHORT Offset;
	ULONG  Access;
	USHORT Selector;
	ULONG  ExtendedOffset;
	ULONG  Reserved;
} GATE_DESCRIPTOR;

typedef struct _SEGMENT_DESCRIPTOR
{
	ULONG_PTR LimitLow       : 16;
	ULONG_PTR BaseLow        : 16;
	ULONG_PTR BaseMid        : 8;
	ULONG_PTR AttributesLow  : 8;
	ULONG_PTR LimitHigh      : 4;
	ULONG_PTR AttributesHigh : 4;
	ULONG_PTR BaseHigh       : 8;
} SEGMENT_DESCRIPTOR;

//SEGMENT_DESCRIPTOR.Attributes (-Gap)...
typedef union
{
	USHORT UCHARs;
	struct FIELDS
	{
		USHORT type:4;                  /* 0;  Bit 40-43 */
		USHORT s  : 1;                 	/* 4;  Bit 44    */
		USHORT dpl: 2;               	/* 5;  Bit 45-46 */
		USHORT p  : 1;                 	/* 7;  Bit 47    */
		// gap!    
		USHORT avl: 1;               	/* 8;  Bit 52 */
		USHORT l  : 1;                 	/* 9;  Bit 53 */
		USHORT db : 1;                	/* 10; Bit 54 */
		USHORT g  : 1;                 	/* 11; Bit 55 */
		USHORT Gap: 4;
	};
} SEGMENT_ATTRIBUTES;

typedef struct _SEGMENT_SELECTOR
{
	ULONG_PTR selector;
	ULONG     limit;
	ULONG_PTR base;
	ULONG_PTR rights;
	USHORT    attributes;
} SEGMENT_SELECTOR;

typedef struct _GDT
{
	USHORT limit;
	ULONG_PTR base;
} GDT;

#pragma pack(pop)

typedef struct _GUEST_STATE
{
    void* VMXON;
	void* VMCS;
    void* hvStack;
    //
    ULONG_PTR CR0;
    ULONG_PTR CR3;
    ULONG_PTR CR4;
    //
    ULONG_PTR RFLAGS;
    //
    ULONG_PTR Cs;
    ULONG_PTR Ds;
    ULONG_PTR Es;
    ULONG_PTR Ss;
    ULONG_PTR Fs;
    ULONG_PTR Gs;
	ULONG_PTR Ldtr;
	ULONG_PTR Tr;
    //
    GDT Gdtr;
    GDT Idtr;
    //
    ULONG_PTR S_CS;
    ULONG_PTR SEIP;
    ULONG_PTR SESP;
    //
} GUEST_STATE;

#define SEG_CODE				0x10
#define SEG_DATA				0x18

#define NORMAL					0x10

#define BTS(b)					(1i64 << b)
#define CR4_VMXE				BTS(13)

#define FEATURE_CONTROL_LOCKED			BTS(0)
#define FEATURE_CONTROL_VMXON_ENABLED	BTS(2)

#define	MAX_HV_CALLBACK			VMX_EXIT_XSETBV+2

//------------------------------------------------------------------
// ****************** DEFINE PUSHAQ order of regs ******************
//------------------------------------------------------------------

enum RegSetx86
{
	RDI = 0,
	RSI,
	RBP,
	RSP,
	RBX,
	RDX,
	RCX,
	RAX,
	REG_X86_COUNT
};

enum RegSetx64
{
	R15 = REG_X86_COUNT,
	R14,
	R13,
	R12,
	R11,
	R10,
	R9,
	R8,
	REG_X64_COUNT
};

#define REG_COUNT REG_X64_COUNT

enum RegFastCallX64Volatile
{
	VOLATILE_REG_RCX = 0,
	VOLATILE_REG_RDX,
	VOLATILE_REG_R8,
	VOLATILE_REG_R9,
	VOLATILE_REG_COUNT
};
