#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>

#define SHA1HashSize 20


#define SHA1CircularShift(bits,word) \
	(((word) << (bits)) | ((word) >> (32-(bits))))

typedef struct SHA1Context
{
	uint32_t Intermediate_Hash[SHA1HashSize/4]; /* Message Digest */
	uint32_t Length_Low; /* Message length in bits */
	uint32_t Length_High; /* Message length in bits */
	/* Index into message block array */
	int Message_Block_Index;
	uint8_t Message_Block[64]; /* 512-bit message blocks */
	int Computed; /* Is the digest computed? */
	int Corrupted; /* Is the message digest corrupted? */
} SHA1Context;

extern void SHA1Input( SHA1Context *context,uint8_t *message_array,unsigned length);
extern void SHA1Result( SHA1Context *context,uint8_t* Message_Digest);
extern void SHA1Reset(SHA1Context *context);
