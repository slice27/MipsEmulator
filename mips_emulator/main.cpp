#include "MipsCpu.h"

uint32_t instructions[] = {
    0x27bdffd8, // 0x4000d0     addiu	sp,sp,-40
    0xafbf0024, // 0x4000d4     sw	ra,36(sp)
    0xafbe0020, // 0x4000d8     sw	s8,32(sp)
    0x03a0f025, // 0x4000dc     move	s8,sp
    0xafc40028, // 0x4000e0     sw	a0,40(s8)
    0xafc5002c, // 0x4000e4     sw	a1,44(s8)
    0x24020002, // 0x4000e8     li	v0,2
    0xafc20018, // 0x4000ec     sw	v0,24(s8)
    0x8fc40018, // 0x4000f0     lw	a0,24(s8)
    0x0c100047, // 0x4000f4     jal	40011c <square(int)>
    0x00000000, // 0x4000f8     nop
    0xafc20018, // 0x4000fc     sw	v0,24(s8)
    0x8fc20018, // 0x400104     lw	v0,24(s8)
    0x03c0e825, // 0x400100     move	sp,s8
    0x8fbf0024, // 0x400108     lw	ra,36(sp)
    0x8fbe0020, // 0x40010c     lw	s8,32(sp)
    0x27bd0028, // 0x400110     addiu	sp,sp,40
    0x03e00008, // 0x400114     jr	ra
    0x00000000, // 0x400118     nop
    //square(int):
    0x27bdfff8, // 0x40011c     addiu	sp,sp,-8
    0xafbe0004, // 0x400120     sw	s8,4(sp)
    0x03a0f025, // 0x400124     move	s8,sp
    0xafc40008, // 0x400128     sw	a0,8(s8)
    0x8fc30008, // 0x40012c     lw	v1,8(s8)
    0x8fc20008, // 0x400130     lw	v0,8(s8)
    0x00000000, // 0x400134     nop
    0x00620018, // 0x400138     mult	v1,v0
    0x00001012, // 0x40013c     mflo	v0
    0x03c0e825, // 0x400140     move	sp,s8
    0x8fbe0004, // 0x400144     lw	s8,4(sp)
    0x27bd0008, // 0x400148     addiu	sp,sp,8
    0x03e00008, // 0x40014c     jr	ra
    0x00000000, // 0x400150     nop
};
        
int main(int argc, char **argv)
{
    int size = sizeof(instructions) / sizeof(instructions[0]);

    MipsCpu cpu;
    cpu.LoadProgram(instructions, size);
    cpu.Run();
	return 0;
}
