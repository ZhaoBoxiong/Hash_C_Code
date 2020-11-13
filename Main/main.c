#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "../MD5/MD5.h"
#include "../SHA1/SHA1.h"
#include "../SHA256/SHA256.h"
typedef enum
{
	HASH_NONE,
	HASH_MD5,
	HASH_SHA1,
	HASH_SHA256
}HASH_Type_T;

int main(int argc, char **argv)
{
	char Md5Str[3]="MD5";
	char SHA1Str[4]="SHA1";
	char SHA256Str[6]="SHA256";

	HASH_Type_T HashType; 

	if ((argv[1][5]) == '6')
	{
		printf("SHA256 Selected \n");
		HashType = HASH_SHA256;
	}
	else if ((argv[1][0]) == 'M')
	{
		printf("MD5 Selected \n");
		HashType = HASH_MD5;
	}
	else if ((argv[1][3]) == '1')
	{
		printf("SHA1 Selected \n");
		HashType = HASH_SHA1;
	}
	else
	{
		printf("Wrong Option \n");
		HashType = HASH_NONE;
	}

	if (HashType == HASH_MD5)
	{
		struct stat st;
	    unsigned char digest[16] = {0};
	    MD5_CTX context;
	    int i = 0;

	    MD5Init(&context);

	    if(-1 == stat(argv[2], &st))
	    {
	        /* 文件不存在则计算参数字符串的MD5 */
	        MD5Update(&context, argv[2], strlen(argv[2]));
	    }
	    else
	    {
	        /* 计算文件MD5 */
	        FILE *fp = fopen(argv[2], "rb");
	        char *data = NULL;
	        int ret = 0;

	        if(!fp)
	        {
	            perror("fopen");
	            exit(-1);
	        }

	        data = malloc(st.st_size);
	        if(!data)
	        {
	            perror("malloc");
	            exit(-1);
	        }
	        ret = fread(data, 1, st.st_size, fp);
	        if(ret != st.st_size)
	        {
	            perror("fread");
	            exit(-1);
	        } 
	        MD5Update(&context, data, st.st_size);
	        fclose(fp);
	        free(data);
	    }
	    MD5Final(&context, digest);

	    /* 打印MD5值 */
	    printf("md5: ");
	    for(i = 0; i < 16; i++)
	    {
	        printf("%02x", digest[i]);
	    }
	    printf("\n");
	    return 0;
	}
	else if (HashType == HASH_SHA1)
	{
		uint8_t SHA1_Message_Digest[20]={0};
		struct stat st;
		int i = 0;
		SHA1Context sha;
		SHA1Reset(&sha);
		if(-1 == stat(argv[2], &st))
	    {
	        /* 文件不存在则计算参数字符串的SHA1 */
	        SHA1Input(&sha, argv[2], strlen(argv[2]));
	    }
	    else
	    {
	    		        /* 计算文件SHA1 */
	        FILE *fp = fopen(argv[2], "rb");
	        char *data = NULL;
	        int ret = 0;


	        if(!fp)
	        {
	            perror("fopen");
	            exit(-1);
	        }

	        data = malloc(st.st_size);
	        if(!data)
	        {
	            perror("malloc");
	            exit(-1);
	        }
	        ret = fread(data, 1, st.st_size, fp);
	        if(ret != st.st_size)
	        {
	            perror("fread");
	            exit(-1);
	        }
			SHA1Input(&sha, data, st.st_size);
	    	fclose(fp);
	    	free(data);
	    }
	    SHA1Result(&sha, SHA1_Message_Digest);

	    	    /* 打印MD5值 */
	    printf("SHA1: ");
	    for(i = 0; i < 20; i++)
	    {
	        printf("%02x", SHA1_Message_Digest[i]);
	    }
	    printf("\n");

	}
	else if (HashType == HASH_SHA256)
	{
		long SHA256_Result[8] = {0};
		struct stat st;
		if(-1 == stat(argv[2], &st))
	    {
	        StrSHA256(argv[2], strlen(argv[2]), SHA256_Result);
	        printf("%08X%08X%08X%08X%08X%08X%08X%08X", SHA256_Result[0], SHA256_Result[1], SHA256_Result[2], SHA256_Result[3], SHA256_Result[4], SHA256_Result[5], SHA256_Result[6], SHA256_Result[7]);
	    }
	    else
	    {
	    	FILE *fp = fopen(argv[2], "rb");
	        char *data = NULL;
	        int ret = 0;

	        if(!fp)
	        {
	            perror("fopen");
	            exit(-1);
	        }

	        data = malloc(st.st_size);
	        if(!data)
	        {
	            perror("malloc");
	            exit(-1);
	        }
	        ret = fread(data, 1, st.st_size, fp);
	        if(ret != st.st_size)
	        {
	            perror("fread");
	            exit(-1);
	        }

	        FileSHA256(argv[2], SHA256_Result);
	        printf("%08X%08X%08X%08X%08X%08X%08X%08X", SHA256_Result[0], SHA256_Result[1], SHA256_Result[2], SHA256_Result[3], SHA256_Result[4], SHA256_Result[5], SHA256_Result[6], SHA256_Result[7]);

	    }

		
	}

	



}