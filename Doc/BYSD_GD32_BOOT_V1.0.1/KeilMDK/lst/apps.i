#line 1 "..\\Source\\apps\\apps.c"
#line 1 "..\\Source\\apps\\apps.h"







#line 1 "..\\Source\\main\\includes.h"







#line 1 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdio.h"
 
 
 





 






 













#line 38 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdio.h"


  
  typedef unsigned int size_t;    








 
 

 
  typedef struct __va_list __va_list;





   




 




typedef struct __fpos_t_struct {
    unsigned __int64 __pos;
    



 
    struct {
        unsigned int __state1, __state2;
    } __mbstate;
} fpos_t;
   


 


   

 

typedef struct __FILE FILE;
   






 

extern FILE __stdin, __stdout, __stderr;
extern FILE *__aeabi_stdin, *__aeabi_stdout, *__aeabi_stderr;

#line 129 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdio.h"
    

    

    





     



   


 


   


 

   



 

   


 




   


 





    


 






extern __declspec(__nothrow) int remove(const char *  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int rename(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   








 
extern __declspec(__nothrow) FILE *tmpfile(void);
   




 
extern __declspec(__nothrow) char *tmpnam(char *  );
   











 

extern __declspec(__nothrow) int fclose(FILE *  ) __attribute__((__nonnull__(1)));
   







 
extern __declspec(__nothrow) int fflush(FILE *  );
   







 
extern __declspec(__nothrow) FILE *fopen(const char * __restrict  ,
                           const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   








































 
extern __declspec(__nothrow) FILE *freopen(const char * __restrict  ,
                    const char * __restrict  ,
                    FILE * __restrict  ) __attribute__((__nonnull__(2,3)));
   








 
extern __declspec(__nothrow) void setbuf(FILE * __restrict  ,
                    char * __restrict  ) __attribute__((__nonnull__(1)));
   




 
extern __declspec(__nothrow) int setvbuf(FILE * __restrict  ,
                   char * __restrict  ,
                   int  , size_t  ) __attribute__((__nonnull__(1)));
   















 
#pragma __printf_args
extern __declspec(__nothrow) int fprintf(FILE * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   


















 
#pragma __printf_args
extern __declspec(__nothrow) int _fprintf(FILE * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 
#pragma __printf_args
extern __declspec(__nothrow) int printf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   




 
#pragma __printf_args
extern __declspec(__nothrow) int _printf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   



 
#pragma __printf_args
extern __declspec(__nothrow) int sprintf(char * __restrict  , const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   






 
#pragma __printf_args
extern __declspec(__nothrow) int _sprintf(char * __restrict  , const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 

#pragma __printf_args
extern __declspec(__nothrow) int snprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(3)));
   















 

#pragma __printf_args
extern __declspec(__nothrow) int _snprintf(char * __restrict  , size_t  ,
                      const char * __restrict  , ...) __attribute__((__nonnull__(3)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int fscanf(FILE * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   






























 
#pragma __scanf_args
extern __declspec(__nothrow) int _fscanf(FILE * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int scanf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   






 
#pragma __scanf_args
extern __declspec(__nothrow) int _scanf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int sscanf(const char * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   








 
#pragma __scanf_args
extern __declspec(__nothrow) int _sscanf(const char * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 

 
extern __declspec(__nothrow) int vfscanf(FILE * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int vscanf(const char * __restrict  , __va_list) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) int vsscanf(const char * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));

extern __declspec(__nothrow) int _vfscanf(FILE * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int _vscanf(const char * __restrict  , __va_list) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) int _vsscanf(const char * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));

extern __declspec(__nothrow) int vprintf(const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int _vprintf(const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) int vfprintf(FILE * __restrict  ,
                    const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int vsprintf(char * __restrict  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   






 

extern __declspec(__nothrow) int vsnprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(3)));
   







 

extern __declspec(__nothrow) int _vsprintf(char * __restrict  ,
                      const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   



 
extern __declspec(__nothrow) int _vfprintf(FILE * __restrict  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   



 
extern __declspec(__nothrow) int _vsnprintf(char * __restrict  , size_t  ,
                      const char * __restrict  , __va_list  ) __attribute__((__nonnull__(3)));
   



 
extern __declspec(__nothrow) int fgetc(FILE *  ) __attribute__((__nonnull__(1)));
   







 
extern __declspec(__nothrow) char *fgets(char * __restrict  , int  ,
                    FILE * __restrict  ) __attribute__((__nonnull__(1,3)));
   










 
extern __declspec(__nothrow) int fputc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   







 
extern __declspec(__nothrow) int fputs(const char * __restrict  , FILE * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) int getc(FILE *  ) __attribute__((__nonnull__(1)));
   







 




    extern __declspec(__nothrow) int (getchar)(void);

   





 
extern __declspec(__nothrow) char *gets(char *  ) __attribute__((__nonnull__(1)));
   









 
extern __declspec(__nothrow) int putc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   





 




    extern __declspec(__nothrow) int (putchar)(int  );

   



 
extern __declspec(__nothrow) int puts(const char *  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int ungetc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   






















 

extern __declspec(__nothrow) size_t fread(void * __restrict  ,
                    size_t  , size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,4)));
   











 

extern __declspec(__nothrow) size_t __fread_bytes_avail(void * __restrict  ,
                    size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,3)));
   











 

extern __declspec(__nothrow) size_t fwrite(const void * __restrict  ,
                    size_t  , size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,4)));
   







 

extern __declspec(__nothrow) int fgetpos(FILE * __restrict  , fpos_t * __restrict  ) __attribute__((__nonnull__(1,2)));
   








 
extern __declspec(__nothrow) int fseek(FILE *  , long int  , int  ) __attribute__((__nonnull__(1)));
   














 
extern __declspec(__nothrow) int fsetpos(FILE * __restrict  , const fpos_t * __restrict  ) __attribute__((__nonnull__(1,2)));
   










 
extern __declspec(__nothrow) long int ftell(FILE *  ) __attribute__((__nonnull__(1)));
   











 
extern __declspec(__nothrow) void rewind(FILE *  ) __attribute__((__nonnull__(1)));
   





 

extern __declspec(__nothrow) void clearerr(FILE *  ) __attribute__((__nonnull__(1)));
   




 

extern __declspec(__nothrow) int feof(FILE *  ) __attribute__((__nonnull__(1)));
   


 
extern __declspec(__nothrow) int ferror(FILE *  ) __attribute__((__nonnull__(1)));
   


 
extern __declspec(__nothrow) void perror(const char *  );
   









 

extern __declspec(__nothrow) int _fisatty(FILE *   ) __attribute__((__nonnull__(1)));
    
 

extern __declspec(__nothrow) void __use_no_semihosting_swi(void);
extern __declspec(__nothrow) void __use_no_semihosting(void);
    





 











#line 948 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdio.h"



 

#line 9 "..\\Source\\main\\includes.h"
#line 1 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdlib.h"
 
 
 




 
 



 













  


 








#line 46 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdlib.h"


  
  typedef unsigned int size_t;










    



    typedef unsigned short wchar_t;  
#line 75 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdlib.h"

typedef struct div_t { int quot, rem; } div_t;
    
typedef struct ldiv_t { long int quot, rem; } ldiv_t;
    

typedef struct lldiv_t { __int64 quot, rem; } lldiv_t;
    


#line 96 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdlib.h"
   



 

   




 
#line 115 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdlib.h"
   


 
extern __declspec(__nothrow) int __aeabi_MB_CUR_MAX(void);

   




 

   




 




extern __declspec(__nothrow) double atof(const char *  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) int atoi(const char *  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) long int atol(const char *  ) __attribute__((__nonnull__(1)));
   



 

extern __declspec(__nothrow) __int64 atoll(const char *  ) __attribute__((__nonnull__(1)));
   



 


extern __declspec(__nothrow) double strtod(const char * __restrict  , char ** __restrict  ) __attribute__((__nonnull__(1)));
   

















 

extern __declspec(__nothrow) float strtof(const char * __restrict  , char ** __restrict  ) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) long double strtold(const char * __restrict  , char ** __restrict  ) __attribute__((__nonnull__(1)));
   

 

extern __declspec(__nothrow) long int strtol(const char * __restrict  ,
                        char ** __restrict  , int  ) __attribute__((__nonnull__(1)));
   



























 
extern __declspec(__nothrow) unsigned long int strtoul(const char * __restrict  ,
                                       char ** __restrict  , int  ) __attribute__((__nonnull__(1)));
   


























 

 
extern __declspec(__nothrow) __int64 strtoll(const char * __restrict  ,
                               char ** __restrict  , int  ) __attribute__((__nonnull__(1)));
   




 
extern __declspec(__nothrow) unsigned __int64 strtoull(const char * __restrict  ,
                                         char ** __restrict  , int  ) __attribute__((__nonnull__(1)));
   



 

extern __declspec(__nothrow) int rand(void);
   







 
extern __declspec(__nothrow) void srand(unsigned int  );
   






 

struct _rand_state { int __x[57]; };
extern __declspec(__nothrow) int _rand_r(struct _rand_state *);
extern __declspec(__nothrow) void _srand_r(struct _rand_state *, unsigned int);
struct _ANSI_rand_state { int __x[1]; };
extern __declspec(__nothrow) int _ANSI_rand_r(struct _ANSI_rand_state *);
extern __declspec(__nothrow) void _ANSI_srand_r(struct _ANSI_rand_state *, unsigned int);
   


 

extern __declspec(__nothrow) void *calloc(size_t  , size_t  );
   



 
extern __declspec(__nothrow) void free(void *  );
   





 
extern __declspec(__nothrow) void *malloc(size_t  );
   



 
extern __declspec(__nothrow) void *realloc(void *  , size_t  );
   













 

extern __declspec(__nothrow) int posix_memalign(void **  , size_t  , size_t  );
   









 

typedef int (*__heapprt)(void *, char const *, ...);
extern __declspec(__nothrow) void __heapstats(int (*  )(void *  ,
                                           char const *  , ...),
                        void *  ) __attribute__((__nonnull__(1)));
   










 
extern __declspec(__nothrow) int __heapvalid(int (*  )(void *  ,
                                           char const *  , ...),
                       void *  , int  ) __attribute__((__nonnull__(1)));
   














 
extern __declspec(__nothrow) __declspec(__noreturn) void abort(void);
   







 

extern __declspec(__nothrow) int atexit(void (*  )(void)) __attribute__((__nonnull__(1)));
   




 
#line 415 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdlib.h"


extern __declspec(__nothrow) __declspec(__noreturn) void exit(int  );
   












 

extern __declspec(__nothrow) __declspec(__noreturn) void _Exit(int  );
   







      

extern __declspec(__nothrow) char *getenv(const char *  ) __attribute__((__nonnull__(1)));
   









 

extern __declspec(__nothrow) int  system(const char *  );
   









 

extern  void *bsearch(const void *  , const void *  ,
              size_t  , size_t  ,
              int (*  )(const void *, const void *)) __attribute__((__nonnull__(1,2,5)));
   












 
#line 503 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdlib.h"


extern  void qsort(void *  , size_t  , size_t  ,
           int (*  )(const void *, const void *)) __attribute__((__nonnull__(1,4)));
   









 

#line 532 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdlib.h"

extern __declspec(__nothrow) __pure int abs(int  );
   



 

extern __declspec(__nothrow) __pure div_t div(int  , int  );
   









 
extern __declspec(__nothrow) __pure long int labs(long int  );
   



 




extern __declspec(__nothrow) __pure ldiv_t ldiv(long int  , long int  );
   











 







extern __declspec(__nothrow) __pure __int64 llabs(__int64  );
   



 




extern __declspec(__nothrow) __pure lldiv_t lldiv(__int64  , __int64  );
   











 
#line 613 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdlib.h"



 
typedef struct __sdiv32by16 { int quot, rem; } __sdiv32by16;
typedef struct __udiv32by16 { unsigned int quot, rem; } __udiv32by16;
    
typedef struct __sdiv64by32 { int rem, quot; } __sdiv64by32;

__value_in_regs extern __declspec(__nothrow) __pure __sdiv32by16 __rt_sdiv32by16(
     int  ,
     short int  );
   

 
__value_in_regs extern __declspec(__nothrow) __pure __udiv32by16 __rt_udiv32by16(
     unsigned int  ,
     unsigned short  );
   

 
__value_in_regs extern __declspec(__nothrow) __pure __sdiv64by32 __rt_sdiv64by32(
     int  , unsigned int  ,
     int  );
   

 



 
extern __declspec(__nothrow) unsigned int __fp_status(unsigned int  , unsigned int  );
   







 























 
extern __declspec(__nothrow) int mblen(const char *  , size_t  );
   












 
extern __declspec(__nothrow) int mbtowc(wchar_t * __restrict  ,
                   const char * __restrict  , size_t  );
   















 
extern __declspec(__nothrow) int wctomb(char *  , wchar_t  );
   













 





 
extern __declspec(__nothrow) size_t mbstowcs(wchar_t * __restrict  ,
                      const char * __restrict  , size_t  ) __attribute__((__nonnull__(2)));
   














 
extern __declspec(__nothrow) size_t wcstombs(char * __restrict  ,
                      const wchar_t * __restrict  , size_t  ) __attribute__((__nonnull__(2)));
   














 

extern __declspec(__nothrow) void __use_realtime_heap(void);
extern __declspec(__nothrow) void __use_realtime_division(void);
extern __declspec(__nothrow) void __use_two_region_memory(void);
extern __declspec(__nothrow) void __use_no_heap(void);
extern __declspec(__nothrow) void __use_no_heap_region(void);

extern __declspec(__nothrow) char const *__C_library_version_string(void);
extern __declspec(__nothrow) int __C_library_version_number(void);











#line 867 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdlib.h"


 

#line 10 "..\\Source\\main\\includes.h"
#line 1 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\string.h"
 
 
 
 




 








 












#line 38 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\string.h"


  
  typedef unsigned int size_t;








extern __declspec(__nothrow) void *memcpy(void * __restrict  ,
                    const void * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) void *memmove(void *  ,
                    const void *  , size_t  ) __attribute__((__nonnull__(1,2)));
   







 
extern __declspec(__nothrow) char *strcpy(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) char *strncpy(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   





 

extern __declspec(__nothrow) char *strcat(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) char *strncat(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 






 

extern __declspec(__nothrow) int memcmp(const void *  , const void *  , size_t  ) __attribute__((__nonnull__(1,2)));
   





 
extern __declspec(__nothrow) int strcmp(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) int strncmp(const char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int strcasecmp(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   





 
extern __declspec(__nothrow) int strncasecmp(const char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int strcoll(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   







 

extern __declspec(__nothrow) size_t strxfrm(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(2)));
   













 


#line 185 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\string.h"
extern __declspec(__nothrow) void *memchr(const void *  , int  , size_t  ) __attribute__((__nonnull__(1)));

   





 

#line 201 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strchr(const char *  , int  ) __attribute__((__nonnull__(1)));

   




 

extern __declspec(__nothrow) size_t strcspn(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   




 

#line 224 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strpbrk(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));

   




 

#line 239 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strrchr(const char *  , int  ) __attribute__((__nonnull__(1)));

   





 

extern __declspec(__nothrow) size_t strspn(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   



 

#line 262 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strstr(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));

   





 

extern __declspec(__nothrow) char *strtok(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(2)));
extern __declspec(__nothrow) char *_strtok_r(char *  , const char *  , char **  ) __attribute__((__nonnull__(2,3)));

extern __declspec(__nothrow) char *strtok_r(char *  , const char *  , char **  ) __attribute__((__nonnull__(2,3)));

   

































 

extern __declspec(__nothrow) void *memset(void *  , int  , size_t  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) char *strerror(int  );
   





 
extern __declspec(__nothrow) size_t strlen(const char *  ) __attribute__((__nonnull__(1)));
   



 

extern __declspec(__nothrow) size_t strlcpy(char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   
















 

extern __declspec(__nothrow) size_t strlcat(char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






















 

extern __declspec(__nothrow) void _membitcpybl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpybb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpyhl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpyhb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpywl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpywb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovebl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovebb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovehl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovehb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovewl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovewb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
    














































 







#line 494 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\string.h"



 

#line 11 "..\\Source\\main\\includes.h"



#line 1 "..\\Source\\main\\../os/lfos.h"







#line 1 "..\\Source\\main\\../os/lfos_cfg.h"















typedef unsigned char INT8U;
typedef unsigned short INT16U;
typedef unsigned int INT32U;

typedef char INT8S;
typedef short INT16S;
typedef int INT32S;



typedef unsigned int OS_STK;














#line 9 "..\\Source\\main\\../os/lfos.h"



typedef struct tagLFOS_SEM
{
	void *pName;	
	INT8U sem_cnt;	
	INT32U timeout;
}LFOS_SEM;

typedef struct tagLFOSThread
{
	OS_STK *sp;				
	OS_STK *bottom;			
	OS_STK *sp_init_ptr;	
	INT32U stack_freed;		

	INT8U status;			
	INT32U dly_tick;		
	INT32U use_cpu_tick;	
	LFOS_SEM *pSem;			

}LFOSThread;


extern void cpu_int_en(void);
extern void cpu_int_dis(void);
extern void start_thread(void);
extern void context_sw(void);
extern void context_sw_int(void);
extern void lfos_thread_stack_init(OS_STK **sp,void *thread_proc);

extern LFOSThread *pCurThread;
extern LFOSThread *pHighThread;




extern LFOSThread *lfos_get_thread_ptr(INT8U thread_id);
extern OS_STK *lfos_get_sys_thread_stk_ptr(void);



extern void lfos_tick(void);
extern void lfos_enter_int(void);
extern void lfos_exit_int(void);



extern void lfos_init(void);
extern int lfos_create_thread(INT8U thread_id,void (*thread_proc)(void),
								OS_STK *sp,OS_STK *bottom);
extern void lfos_start(void);
extern void lfos_sleep(unsigned int t);
extern INT32U lfos_stack_used(unsigned char thread_id);
extern INT32U lfos_stack_freed(unsigned char thread_id);
extern INT16U lfos_get_version(void);



extern int lfos_create_sem(LFOS_SEM *pSem,void *pName,INT8U cnt);
extern int lfos_sem_pend(LFOS_SEM *pSem,INT32U timeout);
extern int lfos_sem_post(LFOS_SEM *pSem);



extern int lfos_create_mem(INT8U mem_lib_id,void *ptr,INT32U block_size,INT32U block_cnt);
extern void *lfos_mem_malloc(INT8U mem_lib_id);
extern int lfos_mem_free(INT8U mem_lib_id,void *ptr);
extern unsigned int lfos_mem_get_block_size(INT8U mem_lib_id);







#line 15 "..\\Source\\main\\includes.h"

#line 17 "..\\Source\\main\\includes.h"

#line 1 "..\\Source\\main\\../drivers/drivers.h"








#line 1 "..\\Source\\main\\includes.h"
#line 10 "..\\Source\\main\\../drivers/drivers.h"

#line 1 "..\\Source\\main\\../drivers/./RTT/SEGGER_RTT_Conf.h"
































































 













 
























 





























 
#line 203 "..\\Source\\main\\../drivers/./RTT/SEGGER_RTT_Conf.h"




 
#line 230 "..\\Source\\main\\../drivers/./RTT/SEGGER_RTT_Conf.h"




 
#line 244 "..\\Source\\main\\../drivers/./RTT/SEGGER_RTT_Conf.h"




 
#line 258 "..\\Source\\main\\../drivers/./RTT/SEGGER_RTT_Conf.h"




 
#line 285 "..\\Source\\main\\../drivers/./RTT/SEGGER_RTT_Conf.h"










 
#line 318 "..\\Source\\main\\../drivers/./RTT/SEGGER_RTT_Conf.h"




 









 
#line 12 "..\\Source\\main\\../drivers/drivers.h"
#line 1 "..\\Source\\main\\../drivers/./RTT/SEGGER_RTT.h"
































































 




#line 71 "..\\Source\\main\\../drivers/./RTT/SEGGER_RTT.h"






 






 





typedef struct {
  const     char*    sName;         
            char*    pBuffer;       
            unsigned SizeOfBuffer;  
            unsigned WrOff;         
  volatile  unsigned RdOff;         
            unsigned Flags;         
} SEGGER_RTT_BUFFER_UP;





typedef struct {
  const     char*    sName;         
            char*    pBuffer;       
            unsigned SizeOfBuffer;  
  volatile  unsigned WrOff;         
            unsigned RdOff;         
            unsigned Flags;         
} SEGGER_RTT_BUFFER_DOWN;






typedef struct {
  char                    acID[16];                                 
  int                     MaxNumUpBuffers;                          
  int                     MaxNumDownBuffers;                        
  SEGGER_RTT_BUFFER_UP    aUp[(3)];       
  SEGGER_RTT_BUFFER_DOWN  aDown[(3)];   
} SEGGER_RTT_CB;






 
extern SEGGER_RTT_CB _SEGGER_RTT;






 



int          SEGGER_RTT_AllocDownBuffer         (const char* sName, void* pBuffer, unsigned BufferSize, unsigned Flags);
int          SEGGER_RTT_AllocUpBuffer           (const char* sName, void* pBuffer, unsigned BufferSize, unsigned Flags);
int          SEGGER_RTT_ConfigUpBuffer          (unsigned BufferIndex, const char* sName, void* pBuffer, unsigned BufferSize, unsigned Flags);
int          SEGGER_RTT_ConfigDownBuffer        (unsigned BufferIndex, const char* sName, void* pBuffer, unsigned BufferSize, unsigned Flags);
int          SEGGER_RTT_GetKey                  (void);
unsigned     SEGGER_RTT_HasData                 (unsigned BufferIndex);
int          SEGGER_RTT_HasKey                  (void);
void         SEGGER_RTT_Init                    (void);
unsigned     SEGGER_RTT_Read                    (unsigned BufferIndex,       void* pBuffer, unsigned BufferSize);
unsigned     SEGGER_RTT_ReadNoLock              (unsigned BufferIndex,       void* pData,   unsigned BufferSize);
int          SEGGER_RTT_SetNameDownBuffer       (unsigned BufferIndex, const char* sName);
int          SEGGER_RTT_SetNameUpBuffer         (unsigned BufferIndex, const char* sName);
int          SEGGER_RTT_SetFlagsDownBuffer      (unsigned BufferIndex, unsigned Flags);
int          SEGGER_RTT_SetFlagsUpBuffer        (unsigned BufferIndex, unsigned Flags);
int          SEGGER_RTT_WaitKey                 (void);
unsigned     SEGGER_RTT_Write                   (unsigned BufferIndex, const void* pBuffer, unsigned NumBytes);
unsigned     SEGGER_RTT_WriteNoLock             (unsigned BufferIndex, const void* pBuffer, unsigned NumBytes);
unsigned     SEGGER_RTT_WriteSkipNoLock         (unsigned BufferIndex, const void* pBuffer, unsigned NumBytes);
unsigned     SEGGER_RTT_WriteString             (unsigned BufferIndex, const char* s);
void         SEGGER_RTT_WriteWithOverwriteNoLock(unsigned BufferIndex, const void* pBuffer, unsigned NumBytes);
unsigned     SEGGER_RTT_PutChar                 (unsigned BufferIndex, char c);
unsigned     SEGGER_RTT_PutCharSkip             (unsigned BufferIndex, char c);
unsigned     SEGGER_RTT_PutCharSkipNoLock       (unsigned BufferIndex, char c);










 
int     SEGGER_RTT_SetTerminal        (char TerminalId);
int     SEGGER_RTT_TerminalOut        (char TerminalId, const char* s);






 
int SEGGER_RTT_printf(unsigned BufferIndex, const char * sFormat, ...);









 
















#line 220 "..\\Source\\main\\../drivers/./RTT/SEGGER_RTT.h"

#line 229 "..\\Source\\main\\../drivers/./RTT/SEGGER_RTT.h"

#line 238 "..\\Source\\main\\../drivers/./RTT/SEGGER_RTT.h"

#line 247 "..\\Source\\main\\../drivers/./RTT/SEGGER_RTT.h"




 
#line 13 "..\\Source\\main\\../drivers/drivers.h"

#line 1 "..\\Source\\main\\../drivers/./DBG/DBG.h"
















#line 27 "..\\Source\\main\\../drivers/./DBG/DBG.h"









typedef void (*DBGUsartInit)(unsigned long bps,char cParity);
typedef unsigned int (*DBGUsartSend_unlock)(void *buf,unsigned int len);
typedef unsigned int (*DBGUsartRead)(void *buf,unsigned int ulBufSize,unsigned int ulTimeoutMs);














 
extern int DBG_Init(unsigned char num,
				DBGUsartInit pDBGUsartInitFunc,
				unsigned long bps,char cParity,
				DBGUsartSend_unlock pDBGUsartSend_unlock,
				DBGUsartRead pDBGUsartRead
				);

extern unsigned int ReadDBGUsart(unsigned char DBG_PortNum,void *buf,
					   				   unsigned int ulBufSize,unsigned int ulTimeoutMs);

extern void DBG_ChangeParam(unsigned char num,unsigned long bps,char cParity);


extern void Set_DBG_Level(int iLevel);

extern int Get_DBG_Level(void);

extern int DBG_Print(int iLevel,void *str,...);

extern void DBG_PrintBuf(int iLevel,void *tip,void *str,unsigned int length);

extern unsigned char DBG_SendChar(unsigned char ch);

extern void DBG_SendData(void *pdat,unsigned int len);










#line 15 "..\\Source\\main\\../drivers/drivers.h"


#line 1 "..\\Source\\main\\../drivers/./stlib/misc.h"




















 

 







 
#line 1 "..\\Source\\device\\stm32f10x.h"







































 



 



 
    






  


 
  


 


         
        
         
        

        
         
         



















 










 









            
#line 122 "..\\Source\\device\\stm32f10x.h"





 






 
#line 143 "..\\Source\\device\\stm32f10x.h"



 



 



 
#line 162 "..\\Source\\device\\stm32f10x.h"




 
typedef enum IRQn
{
 
  NonMaskableInt_IRQn         = -14,     
  MemoryManagement_IRQn       = -12,     
  BusFault_IRQn               = -11,     
  UsageFault_IRQn             = -10,     
  SVCall_IRQn                 = -5,      
  DebugMonitor_IRQn           = -4,      
  PendSV_IRQn                 = -2,      
  SysTick_IRQn                = -1,      

 
  WWDG_IRQn                   = 0,       
  PVD_IRQn                    = 1,       
  TAMPER_IRQn                 = 2,       
  RTC_IRQn                    = 3,       
  FLASH_IRQn                  = 4,       
  RCC_IRQn                    = 5,       
  EXTI0_IRQn                  = 6,       
  EXTI1_IRQn                  = 7,       
  EXTI2_IRQn                  = 8,       
  EXTI3_IRQn                  = 9,       
  EXTI4_IRQn                  = 10,      
  DMA1_Channel1_IRQn          = 11,      
  DMA1_Channel2_IRQn          = 12,      
  DMA1_Channel3_IRQn          = 13,      
  DMA1_Channel4_IRQn          = 14,      
  DMA1_Channel5_IRQn          = 15,      
  DMA1_Channel6_IRQn          = 16,      
  DMA1_Channel7_IRQn          = 17,      

#line 221 "..\\Source\\device\\stm32f10x.h"

#line 242 "..\\Source\\device\\stm32f10x.h"

#line 270 "..\\Source\\device\\stm32f10x.h"

#line 296 "..\\Source\\device\\stm32f10x.h"


  ADC1_2_IRQn                 = 18,      
  USB_HP_CAN1_TX_IRQn         = 19,      
  USB_LP_CAN1_RX0_IRQn        = 20,      
  CAN1_RX1_IRQn               = 21,      
  CAN1_SCE_IRQn               = 22,      
  EXTI9_5_IRQn                = 23,      
  TIM1_BRK_IRQn               = 24,      
  TIM1_UP_IRQn                = 25,      
  TIM1_TRG_COM_IRQn           = 26,      
  TIM1_CC_IRQn                = 27,      
  TIM2_IRQn                   = 28,      
  TIM3_IRQn                   = 29,      
  TIM4_IRQn                   = 30,      
  I2C1_EV_IRQn                = 31,      
  I2C1_ER_IRQn                = 32,      
  I2C2_EV_IRQn                = 33,      
  I2C2_ER_IRQn                = 34,      
  SPI1_IRQn                   = 35,      
  SPI2_IRQn                   = 36,      
  USART1_IRQn                 = 37,      
  USART2_IRQn                 = 38,      
  USART3_IRQn                 = 39,      
  EXTI15_10_IRQn              = 40,      
  RTCAlarm_IRQn               = 41,      
  USBWakeUp_IRQn              = 42,      
  TIM8_BRK_IRQn               = 43,      
  TIM8_UP_IRQn                = 44,      
  TIM8_TRG_COM_IRQn           = 45,      
  TIM8_CC_IRQn                = 46,      
  ADC3_IRQn                   = 47,      
  FSMC_IRQn                   = 48,      
  SDIO_IRQn                   = 49,      
  TIM5_IRQn                   = 50,      
  SPI3_IRQn                   = 51,      
  UART4_IRQn                  = 52,      
  UART5_IRQn                  = 53,      
  TIM6_IRQn                   = 54,      
  TIM7_IRQn                   = 55,      
  DMA2_Channel1_IRQn          = 56,      
  DMA2_Channel2_IRQn          = 57,      
  DMA2_Channel3_IRQn          = 58,      
  DMA2_Channel4_5_IRQn        = 59       


#line 381 "..\\Source\\device\\stm32f10x.h"

#line 426 "..\\Source\\device\\stm32f10x.h"

#line 472 "..\\Source\\device\\stm32f10x.h"
} IRQn_Type;



 

#line 1 "..\\Source\\device\\core_cm3.h"
 




















 





































 

 
 
 
 
 
 
 
 








 











#line 1 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdint.h"
 
 





 










#line 26 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdint.h"







 

     

     
typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;
typedef   signed       __int64 int64_t;

     
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned       __int64 uint64_t;

     

     
     
typedef   signed          char int_least8_t;
typedef   signed short     int int_least16_t;
typedef   signed           int int_least32_t;
typedef   signed       __int64 int_least64_t;

     
typedef unsigned          char uint_least8_t;
typedef unsigned short     int uint_least16_t;
typedef unsigned           int uint_least32_t;
typedef unsigned       __int64 uint_least64_t;

     

     
typedef   signed           int int_fast8_t;
typedef   signed           int int_fast16_t;
typedef   signed           int int_fast32_t;
typedef   signed       __int64 int_fast64_t;

     
typedef unsigned           int uint_fast8_t;
typedef unsigned           int uint_fast16_t;
typedef unsigned           int uint_fast32_t;
typedef unsigned       __int64 uint_fast64_t;

     
typedef   signed           int intptr_t;
typedef unsigned           int uintptr_t;

     
typedef   signed       __int64 intmax_t;
typedef unsigned       __int64 uintmax_t;




     

     





     





     





     

     





     





     





     

     





     





     





     

     


     


     


     

     


     


     


     

     



     



     


     
    
 



#line 197 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdint.h"

     







     










     











#line 261 "D:\\Keil\\ARM\\ARMCC\\bin\\..\\include\\stdint.h"



 



#line 91 "..\\Source\\device\\core_cm3.h"

















 

#line 117 "..\\Source\\device\\core_cm3.h"





 


 





 
typedef struct
{
  volatile uint32_t ISER[8];                       
       uint32_t RESERVED0[24];                                   
  volatile uint32_t ICER[8];                       
       uint32_t RSERVED1[24];                                    
  volatile uint32_t ISPR[8];                       
       uint32_t RESERVED2[24];                                   
  volatile uint32_t ICPR[8];                       
       uint32_t RESERVED3[24];                                   
  volatile uint32_t IABR[8];                       
       uint32_t RESERVED4[56];                                   
  volatile uint8_t  IP[240];                       
       uint32_t RESERVED5[644];                                  
  volatile  uint32_t STIR;                          
}  NVIC_Type;                                               
   





 
typedef struct
{
  volatile const  uint32_t CPUID;                         
  volatile uint32_t ICSR;                          
  volatile uint32_t VTOR;                          
  volatile uint32_t AIRCR;                         
  volatile uint32_t SCR;                           
  volatile uint32_t CCR;                           
  volatile uint8_t  SHP[12];                       
  volatile uint32_t SHCSR;                         
  volatile uint32_t CFSR;                          
  volatile uint32_t HFSR;                          
  volatile uint32_t DFSR;                          
  volatile uint32_t MMFAR;                         
  volatile uint32_t BFAR;                          
  volatile uint32_t AFSR;                          
  volatile const  uint32_t PFR[2];                        
  volatile const  uint32_t DFR;                           
  volatile const  uint32_t ADR;                           
  volatile const  uint32_t MMFR[4];                       
  volatile const  uint32_t ISAR[5];                       
} SCB_Type;                                                

 












 






























 






 





















 









 


















 
































                                     









 









 









 














   





 
typedef struct
{
  volatile uint32_t CTRL;                          
  volatile uint32_t LOAD;                          
  volatile uint32_t VAL;                           
  volatile const  uint32_t CALIB;                         
} SysTick_Type;

 












 



 



 








   





 
typedef struct
{
  volatile  union  
  {
    volatile  uint8_t    u8;                        
    volatile  uint16_t   u16;                       
    volatile  uint32_t   u32;                       
  }  PORT [32];                                
       uint32_t RESERVED0[864];                                 
  volatile uint32_t TER;                           
       uint32_t RESERVED1[15];                                  
  volatile uint32_t TPR;                           
       uint32_t RESERVED2[15];                                  
  volatile uint32_t TCR;                           
       uint32_t RESERVED3[29];                                  
  volatile uint32_t IWR;                           
  volatile uint32_t IRR;                           
  volatile uint32_t IMCR;                          
       uint32_t RESERVED4[43];                                  
  volatile uint32_t LAR;                           
  volatile uint32_t LSR;                           
       uint32_t RESERVED5[6];                                   
  volatile const  uint32_t PID4;                          
  volatile const  uint32_t PID5;                          
  volatile const  uint32_t PID6;                          
  volatile const  uint32_t PID7;                          
  volatile const  uint32_t PID0;                          
  volatile const  uint32_t PID1;                          
  volatile const  uint32_t PID2;                          
  volatile const  uint32_t PID3;                          
  volatile const  uint32_t CID0;                          
  volatile const  uint32_t CID1;                          
  volatile const  uint32_t CID2;                          
  volatile const  uint32_t CID3;                          
} ITM_Type;                                                

 



 
























 



 



 



 








   





 
typedef struct
{
       uint32_t RESERVED0;
  volatile const  uint32_t ICTR;                          



       uint32_t RESERVED1;

} InterruptType_Type;

 



 








   


#line 614 "..\\Source\\device\\core_cm3.h"





 
typedef struct
{
  volatile uint32_t DHCSR;                         
  volatile  uint32_t DCRSR;                         
  volatile uint32_t DCRDR;                         
  volatile uint32_t DEMCR;                         
} CoreDebug_Type;

 




































 






 






































   


 
#line 721 "..\\Source\\device\\core_cm3.h"

#line 728 "..\\Source\\device\\core_cm3.h"






   




 





#line 758 "..\\Source\\device\\core_cm3.h"


 


 




#line 783 "..\\Source\\device\\core_cm3.h"


 
 
 
 








 
extern uint32_t __get_PSP(void);








 
extern void __set_PSP(uint32_t topOfProcStack);








 
extern uint32_t __get_MSP(void);








 
extern void __set_MSP(uint32_t topOfMainStack);








 
extern uint32_t __REV16(uint16_t value);








 
extern int32_t __REVSH(int16_t value);


#line 933 "..\\Source\\device\\core_cm3.h"





 








 
static __inline uint32_t  __get_BASEPRI(void)
{
  register uint32_t __regBasePri         __asm("basepri");
  return(__regBasePri);
}







 
static __inline void __set_BASEPRI(uint32_t basePri)
{
  register uint32_t __regBasePri         __asm("basepri");
  __regBasePri = (basePri & 0xff);
}







 
static __inline uint32_t __get_PRIMASK(void)
{
  register uint32_t __regPriMask         __asm("primask");
  return(__regPriMask);
}







 
static __inline void __set_PRIMASK(uint32_t priMask)
{
  register uint32_t __regPriMask         __asm("primask");
  __regPriMask = (priMask);
}







 
static __inline uint32_t __get_FAULTMASK(void)
{
  register uint32_t __regFaultMask       __asm("faultmask");
  return(__regFaultMask);
}







 
static __inline void __set_FAULTMASK(uint32_t faultMask)
{
  register uint32_t __regFaultMask       __asm("faultmask");
  __regFaultMask = (faultMask & 1);
}







 
static __inline uint32_t __get_CONTROL(void)
{
  register uint32_t __regControl         __asm("control");
  return(__regControl);
}







 
static __inline void __set_CONTROL(uint32_t control)
{
  register uint32_t __regControl         __asm("control");
  __regControl = control;
}





#line 1445 "..\\Source\\device\\core_cm3.h"







 
 

 











 
static __inline void NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
  uint32_t reg_value;
  uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);                          
  
  reg_value  =  ((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR;                                                    
  reg_value &= ~((0xFFFFul << 16) | (7ul << 8));              
  reg_value  =  (reg_value                       |
                (0x5FA << 16) | 
                (PriorityGroupTmp << 8));                                      
  ((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR =  reg_value;
}








 
static __inline uint32_t NVIC_GetPriorityGrouping(void)
{
  return ((((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR & (7ul << 8)) >> 8);    
}








 
static __inline void NVIC_EnableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000) + 0x0100))->ISER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}








 
static __inline void NVIC_DisableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000) + 0x0100))->ICER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}









 
static __inline uint32_t NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  return((uint32_t) ((((NVIC_Type *) ((0xE000E000) + 0x0100))->ISPR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0));  
}








 
static __inline void NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000) + 0x0100))->ISPR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}








 
static __inline void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000) + 0x0100))->ICPR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}









 
static __inline uint32_t NVIC_GetActive(IRQn_Type IRQn)
{
  return((uint32_t)((((NVIC_Type *) ((0xE000E000) + 0x0100))->IABR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0));  
}












 
static __inline void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if(IRQn < 0) {
    ((SCB_Type *) ((0xE000E000) + 0x0D00))->SHP[((uint32_t)(IRQn) & 0xF)-4] = ((priority << (8 - 4)) & 0xff); }  
  else {
    ((NVIC_Type *) ((0xE000E000) + 0x0100))->IP[(uint32_t)(IRQn)] = ((priority << (8 - 4)) & 0xff);    }         
}















 
static __inline uint32_t NVIC_GetPriority(IRQn_Type IRQn)
{

  if(IRQn < 0) {
    return((uint32_t)(((SCB_Type *) ((0xE000E000) + 0x0D00))->SHP[((uint32_t)(IRQn) & 0xF)-4] >> (8 - 4)));  }  
  else {
    return((uint32_t)(((NVIC_Type *) ((0xE000E000) + 0x0100))->IP[(uint32_t)(IRQn)]           >> (8 - 4)));  }  
}
















 
static __inline uint32_t NVIC_EncodePriority (uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);           
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7 - PriorityGroupTmp) > 4) ? 4 : 7 - PriorityGroupTmp;
  SubPriorityBits     = ((PriorityGroupTmp + 4) < 7) ? 0 : PriorityGroupTmp - 7 + 4;
 
  return (
           ((PreemptPriority & ((1 << (PreemptPriorityBits)) - 1)) << SubPriorityBits) |
           ((SubPriority     & ((1 << (SubPriorityBits    )) - 1)))
         );
}
















 
static __inline void NVIC_DecodePriority (uint32_t Priority, uint32_t PriorityGroup, uint32_t* pPreemptPriority, uint32_t* pSubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);           
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7 - PriorityGroupTmp) > 4) ? 4 : 7 - PriorityGroupTmp;
  SubPriorityBits     = ((PriorityGroupTmp + 4) < 7) ? 0 : PriorityGroupTmp - 7 + 4;
  
  *pPreemptPriority = (Priority >> SubPriorityBits) & ((1 << (PreemptPriorityBits)) - 1);
  *pSubPriority     = (Priority                   ) & ((1 << (SubPriorityBits    )) - 1);
}



 












 
static __inline uint32_t SysTick_Config(uint32_t ticks)
{ 
  if (ticks > (0xFFFFFFul << 0))  return (1);             
                                                               
  ((SysTick_Type *) ((0xE000E000) + 0x0010))->LOAD  = (ticks & (0xFFFFFFul << 0)) - 1;       
  NVIC_SetPriority (SysTick_IRQn, (1<<4) - 1);   
  ((SysTick_Type *) ((0xE000E000) + 0x0010))->VAL   = 0;                                           
  ((SysTick_Type *) ((0xE000E000) + 0x0010))->CTRL  = (1ul << 2) | 
                   (1ul << 1)   | 
                   (1ul << 0);                     
  return (0);                                                   
}






 





 
static __inline void NVIC_SystemReset(void)
{
  ((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR  = ((0x5FA << 16)      | 
                 (((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR & (7ul << 8)) | 
                 (1ul << 2));                    
  __dsb(0);                                                                    
  while(1);                                                     
}

   



 






 
 

extern volatile int ITM_RxBuffer;                     












 
static __inline uint32_t ITM_SendChar (uint32_t ch)
{
  if ((((CoreDebug_Type *) (0xE000EDF0))->DEMCR & (1ul << 24))  &&       
      (((ITM_Type *) (0xE0000000))->TCR & (1ul << 0))                  &&       
      (((ITM_Type *) (0xE0000000))->TER & (1ul << 0)        )                    )      
  {
    while (((ITM_Type *) (0xE0000000))->PORT[0].u32 == 0);
    ((ITM_Type *) (0xE0000000))->PORT[0].u8 = (uint8_t) ch;
  }  
  return (ch);
}










 
static __inline int ITM_ReceiveChar (void) {
  int ch = -1;                                

  if (ITM_RxBuffer != 0x5AA55AA5) {
    ch = ITM_RxBuffer;
    ITM_RxBuffer = 0x5AA55AA5;        
  }
  
  return (ch); 
}









 
static __inline int ITM_CheckChar (void) {

  if (ITM_RxBuffer == 0x5AA55AA5) {
    return (0);                                  
  } else {
    return (1);                                  
  }
}

   






   



 
#line 479 "..\\Source\\device\\stm32f10x.h"
#line 1 "..\\Source\\device\\system_stm32f10x.h"



















 



 



   
  


 









 



 




 

extern uint32_t SystemCoreClock;           



 



 



 



 



 



 
  
extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);


 









 
  


   
 
#line 480 "..\\Source\\device\\stm32f10x.h"
#line 481 "..\\Source\\device\\stm32f10x.h"



   

 
typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;   
typedef const int16_t sc16;   
typedef const int8_t sc8;    

typedef volatile int32_t  vs32;
typedef volatile int16_t  vs16;
typedef volatile int8_t   vs8;

typedef volatile const int32_t vsc32;   
typedef volatile const int16_t vsc16;   
typedef volatile const int8_t vsc8;    

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;   
typedef const uint16_t uc16;   
typedef const uint8_t uc8;    

typedef volatile uint32_t  vu32;
typedef volatile uint16_t vu16;
typedef volatile uint8_t  vu8;

typedef volatile const uint32_t vuc32;   
typedef volatile const uint16_t vuc16;   
typedef volatile const uint8_t vuc8;    

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;


typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

 





 



    



 

typedef struct
{
  volatile uint32_t SR;
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t SMPR1;
  volatile uint32_t SMPR2;
  volatile uint32_t JOFR1;
  volatile uint32_t JOFR2;
  volatile uint32_t JOFR3;
  volatile uint32_t JOFR4;
  volatile uint32_t HTR;
  volatile uint32_t LTR;
  volatile uint32_t SQR1;
  volatile uint32_t SQR2;
  volatile uint32_t SQR3;
  volatile uint32_t JSQR;
  volatile uint32_t JDR1;
  volatile uint32_t JDR2;
  volatile uint32_t JDR3;
  volatile uint32_t JDR4;
  volatile uint32_t DR;
} ADC_TypeDef;



 

typedef struct
{
  uint32_t  RESERVED0;
  volatile uint16_t DR1;
  uint16_t  RESERVED1;
  volatile uint16_t DR2;
  uint16_t  RESERVED2;
  volatile uint16_t DR3;
  uint16_t  RESERVED3;
  volatile uint16_t DR4;
  uint16_t  RESERVED4;
  volatile uint16_t DR5;
  uint16_t  RESERVED5;
  volatile uint16_t DR6;
  uint16_t  RESERVED6;
  volatile uint16_t DR7;
  uint16_t  RESERVED7;
  volatile uint16_t DR8;
  uint16_t  RESERVED8;
  volatile uint16_t DR9;
  uint16_t  RESERVED9;
  volatile uint16_t DR10;
  uint16_t  RESERVED10; 
  volatile uint16_t RTCCR;
  uint16_t  RESERVED11;
  volatile uint16_t CR;
  uint16_t  RESERVED12;
  volatile uint16_t CSR;
  uint16_t  RESERVED13[5];
  volatile uint16_t DR11;
  uint16_t  RESERVED14;
  volatile uint16_t DR12;
  uint16_t  RESERVED15;
  volatile uint16_t DR13;
  uint16_t  RESERVED16;
  volatile uint16_t DR14;
  uint16_t  RESERVED17;
  volatile uint16_t DR15;
  uint16_t  RESERVED18;
  volatile uint16_t DR16;
  uint16_t  RESERVED19;
  volatile uint16_t DR17;
  uint16_t  RESERVED20;
  volatile uint16_t DR18;
  uint16_t  RESERVED21;
  volatile uint16_t DR19;
  uint16_t  RESERVED22;
  volatile uint16_t DR20;
  uint16_t  RESERVED23;
  volatile uint16_t DR21;
  uint16_t  RESERVED24;
  volatile uint16_t DR22;
  uint16_t  RESERVED25;
  volatile uint16_t DR23;
  uint16_t  RESERVED26;
  volatile uint16_t DR24;
  uint16_t  RESERVED27;
  volatile uint16_t DR25;
  uint16_t  RESERVED28;
  volatile uint16_t DR26;
  uint16_t  RESERVED29;
  volatile uint16_t DR27;
  uint16_t  RESERVED30;
  volatile uint16_t DR28;
  uint16_t  RESERVED31;
  volatile uint16_t DR29;
  uint16_t  RESERVED32;
  volatile uint16_t DR30;
  uint16_t  RESERVED33; 
  volatile uint16_t DR31;
  uint16_t  RESERVED34;
  volatile uint16_t DR32;
  uint16_t  RESERVED35;
  volatile uint16_t DR33;
  uint16_t  RESERVED36;
  volatile uint16_t DR34;
  uint16_t  RESERVED37;
  volatile uint16_t DR35;
  uint16_t  RESERVED38;
  volatile uint16_t DR36;
  uint16_t  RESERVED39;
  volatile uint16_t DR37;
  uint16_t  RESERVED40;
  volatile uint16_t DR38;
  uint16_t  RESERVED41;
  volatile uint16_t DR39;
  uint16_t  RESERVED42;
  volatile uint16_t DR40;
  uint16_t  RESERVED43;
  volatile uint16_t DR41;
  uint16_t  RESERVED44;
  volatile uint16_t DR42;
  uint16_t  RESERVED45;    
} BKP_TypeDef;
  


 

typedef struct
{
  volatile uint32_t TIR;
  volatile uint32_t TDTR;
  volatile uint32_t TDLR;
  volatile uint32_t TDHR;
} CAN_TxMailBox_TypeDef;



 
  
typedef struct
{
  volatile uint32_t RIR;
  volatile uint32_t RDTR;
  volatile uint32_t RDLR;
  volatile uint32_t RDHR;
} CAN_FIFOMailBox_TypeDef;



 
  
typedef struct
{
  volatile uint32_t FR1;
  volatile uint32_t FR2;
} CAN_FilterRegister_TypeDef;



 
  
typedef struct
{
  volatile uint32_t MCR;
  volatile uint32_t MSR;
  volatile uint32_t TSR;
  volatile uint32_t RF0R;
  volatile uint32_t RF1R;
  volatile uint32_t IER;
  volatile uint32_t ESR;
  volatile uint32_t BTR;
  uint32_t  RESERVED0[88];
  CAN_TxMailBox_TypeDef sTxMailBox[3];
  CAN_FIFOMailBox_TypeDef sFIFOMailBox[2];
  uint32_t  RESERVED1[12];
  volatile uint32_t FMR;
  volatile uint32_t FM1R;
  uint32_t  RESERVED2;
  volatile uint32_t FS1R;
  uint32_t  RESERVED3;
  volatile uint32_t FFA1R;
  uint32_t  RESERVED4;
  volatile uint32_t FA1R;
  uint32_t  RESERVED5[8];

  CAN_FilterRegister_TypeDef sFilterRegister[14];



} CAN_TypeDef;



 
typedef struct
{
  volatile uint32_t CFGR;
  volatile uint32_t OAR;
  volatile uint32_t PRES;
  volatile uint32_t ESR;
  volatile uint32_t CSR;
  volatile uint32_t TXD;
  volatile uint32_t RXD;  
} CEC_TypeDef;



 

typedef struct
{
  volatile uint32_t DR;
  volatile uint8_t  IDR;
  uint8_t   RESERVED0;
  uint16_t  RESERVED1;
  volatile uint32_t CR;
} CRC_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t SWTRIGR;
  volatile uint32_t DHR12R1;
  volatile uint32_t DHR12L1;
  volatile uint32_t DHR8R1;
  volatile uint32_t DHR12R2;
  volatile uint32_t DHR12L2;
  volatile uint32_t DHR8R2;
  volatile uint32_t DHR12RD;
  volatile uint32_t DHR12LD;
  volatile uint32_t DHR8RD;
  volatile uint32_t DOR1;
  volatile uint32_t DOR2;



} DAC_TypeDef;



 

typedef struct
{
  volatile uint32_t IDCODE;
  volatile uint32_t CR;	
}DBGMCU_TypeDef;



 

typedef struct
{
  volatile uint32_t CCR;
  volatile uint32_t CNDTR;
  volatile uint32_t CPAR;
  volatile uint32_t CMAR;
} DMA_Channel_TypeDef;

typedef struct
{
  volatile uint32_t ISR;
  volatile uint32_t IFCR;
} DMA_TypeDef;



 

typedef struct
{
  volatile uint32_t MACCR;
  volatile uint32_t MACFFR;
  volatile uint32_t MACHTHR;
  volatile uint32_t MACHTLR;
  volatile uint32_t MACMIIAR;
  volatile uint32_t MACMIIDR;
  volatile uint32_t MACFCR;
  volatile uint32_t MACVLANTR;              
       uint32_t RESERVED0[2];
  volatile uint32_t MACRWUFFR;              
  volatile uint32_t MACPMTCSR;
       uint32_t RESERVED1[2];
  volatile uint32_t MACSR;                  
  volatile uint32_t MACIMR;
  volatile uint32_t MACA0HR;
  volatile uint32_t MACA0LR;
  volatile uint32_t MACA1HR;
  volatile uint32_t MACA1LR;
  volatile uint32_t MACA2HR;
  volatile uint32_t MACA2LR;
  volatile uint32_t MACA3HR;
  volatile uint32_t MACA3LR;                
       uint32_t RESERVED2[40];
  volatile uint32_t MMCCR;                  
  volatile uint32_t MMCRIR;
  volatile uint32_t MMCTIR;
  volatile uint32_t MMCRIMR;
  volatile uint32_t MMCTIMR;                
       uint32_t RESERVED3[14];
  volatile uint32_t MMCTGFSCCR;             
  volatile uint32_t MMCTGFMSCCR;
       uint32_t RESERVED4[5];
  volatile uint32_t MMCTGFCR;
       uint32_t RESERVED5[10];
  volatile uint32_t MMCRFCECR;
  volatile uint32_t MMCRFAECR;
       uint32_t RESERVED6[10];
  volatile uint32_t MMCRGUFCR;
       uint32_t RESERVED7[334];
  volatile uint32_t PTPTSCR;
  volatile uint32_t PTPSSIR;
  volatile uint32_t PTPTSHR;
  volatile uint32_t PTPTSLR;
  volatile uint32_t PTPTSHUR;
  volatile uint32_t PTPTSLUR;
  volatile uint32_t PTPTSAR;
  volatile uint32_t PTPTTHR;
  volatile uint32_t PTPTTLR;
       uint32_t RESERVED8[567];
  volatile uint32_t DMABMR;
  volatile uint32_t DMATPDR;
  volatile uint32_t DMARPDR;
  volatile uint32_t DMARDLAR;
  volatile uint32_t DMATDLAR;
  volatile uint32_t DMASR;
  volatile uint32_t DMAOMR;
  volatile uint32_t DMAIER;
  volatile uint32_t DMAMFBOCR;
       uint32_t RESERVED9[9];
  volatile uint32_t DMACHTDR;
  volatile uint32_t DMACHRDR;
  volatile uint32_t DMACHTBAR;
  volatile uint32_t DMACHRBAR;
} ETH_TypeDef;



 

typedef struct
{
  volatile uint32_t IMR;
  volatile uint32_t EMR;
  volatile uint32_t RTSR;
  volatile uint32_t FTSR;
  volatile uint32_t SWIER;
  volatile uint32_t PR;
} EXTI_TypeDef;



 

typedef struct
{
  volatile uint32_t ACR;
  volatile uint32_t KEYR;
  volatile uint32_t OPTKEYR;
  volatile uint32_t SR;
  volatile uint32_t CR;
  volatile uint32_t AR;
  volatile uint32_t RESERVED;
  volatile uint32_t OBR;
  volatile uint32_t WRPR;
#line 920 "..\\Source\\device\\stm32f10x.h"
} FLASH_TypeDef;



 
  
typedef struct
{
  volatile uint16_t RDP;
  volatile uint16_t USER;
  volatile uint16_t Data0;
  volatile uint16_t Data1;
  volatile uint16_t WRP0;
  volatile uint16_t WRP1;
  volatile uint16_t WRP2;
  volatile uint16_t WRP3;
} OB_TypeDef;



 

typedef struct
{
  volatile uint32_t BTCR[8];   
} FSMC_Bank1_TypeDef; 



 
  
typedef struct
{
  volatile uint32_t BWTR[7];
} FSMC_Bank1E_TypeDef;



 
  
typedef struct
{
  volatile uint32_t PCR2;
  volatile uint32_t SR2;
  volatile uint32_t PMEM2;
  volatile uint32_t PATT2;
  uint32_t  RESERVED0;   
  volatile uint32_t ECCR2; 
} FSMC_Bank2_TypeDef;  



 
  
typedef struct
{
  volatile uint32_t PCR3;
  volatile uint32_t SR3;
  volatile uint32_t PMEM3;
  volatile uint32_t PATT3;
  uint32_t  RESERVED0;   
  volatile uint32_t ECCR3; 
} FSMC_Bank3_TypeDef; 



 
  
typedef struct
{
  volatile uint32_t PCR4;
  volatile uint32_t SR4;
  volatile uint32_t PMEM4;
  volatile uint32_t PATT4;
  volatile uint32_t PIO4; 
} FSMC_Bank4_TypeDef; 



 

typedef struct
{
  volatile uint32_t CRL;
  volatile uint32_t CRH;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint32_t BSRR;
  volatile uint32_t BRR;
  volatile uint32_t LCKR;
} GPIO_TypeDef;



 

typedef struct
{
  volatile uint32_t EVCR;
  volatile uint32_t MAPR;
  volatile uint32_t EXTICR[4];
  uint32_t RESERVED0;
  volatile uint32_t MAPR2;  
} AFIO_TypeDef;


 

typedef struct
{
  volatile uint16_t CR1;
  uint16_t  RESERVED0;
  volatile uint16_t CR2;
  uint16_t  RESERVED1;
  volatile uint16_t OAR1;
  uint16_t  RESERVED2;
  volatile uint16_t OAR2;
  uint16_t  RESERVED3;
  volatile uint16_t DR;
  uint16_t  RESERVED4;
  volatile uint16_t SR1;
  uint16_t  RESERVED5;
  volatile uint16_t SR2;
  uint16_t  RESERVED6;
  volatile uint16_t CCR;
  uint16_t  RESERVED7;
  volatile uint16_t TRISE;
  uint16_t  RESERVED8;
} I2C_TypeDef;



 

typedef struct
{
  volatile uint32_t KR;
  volatile uint32_t PR;
  volatile uint32_t RLR;
  volatile uint32_t SR;
} IWDG_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t CSR;
} PWR_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t CFGR;
  volatile uint32_t CIR;
  volatile uint32_t APB2RSTR;
  volatile uint32_t APB1RSTR;
  volatile uint32_t AHBENR;
  volatile uint32_t APB2ENR;
  volatile uint32_t APB1ENR;
  volatile uint32_t BDCR;
  volatile uint32_t CSR;










} RCC_TypeDef;



 

typedef struct
{
  volatile uint16_t CRH;
  uint16_t  RESERVED0;
  volatile uint16_t CRL;
  uint16_t  RESERVED1;
  volatile uint16_t PRLH;
  uint16_t  RESERVED2;
  volatile uint16_t PRLL;
  uint16_t  RESERVED3;
  volatile uint16_t DIVH;
  uint16_t  RESERVED4;
  volatile uint16_t DIVL;
  uint16_t  RESERVED5;
  volatile uint16_t CNTH;
  uint16_t  RESERVED6;
  volatile uint16_t CNTL;
  uint16_t  RESERVED7;
  volatile uint16_t ALRH;
  uint16_t  RESERVED8;
  volatile uint16_t ALRL;
  uint16_t  RESERVED9;
} RTC_TypeDef;



 

typedef struct
{
  volatile uint32_t POWER;
  volatile uint32_t CLKCR;
  volatile uint32_t ARG;
  volatile uint32_t CMD;
  volatile const uint32_t RESPCMD;
  volatile const uint32_t RESP1;
  volatile const uint32_t RESP2;
  volatile const uint32_t RESP3;
  volatile const uint32_t RESP4;
  volatile uint32_t DTIMER;
  volatile uint32_t DLEN;
  volatile uint32_t DCTRL;
  volatile const uint32_t DCOUNT;
  volatile const uint32_t STA;
  volatile uint32_t ICR;
  volatile uint32_t MASK;
  uint32_t  RESERVED0[2];
  volatile const uint32_t FIFOCNT;
  uint32_t  RESERVED1[13];
  volatile uint32_t FIFO;
} SDIO_TypeDef;



 

typedef struct
{
  volatile uint16_t CR1;
  uint16_t  RESERVED0;
  volatile uint16_t CR2;
  uint16_t  RESERVED1;
  volatile uint16_t SR;
  uint16_t  RESERVED2;
  volatile uint16_t DR;
  uint16_t  RESERVED3;
  volatile uint16_t CRCPR;
  uint16_t  RESERVED4;
  volatile uint16_t RXCRCR;
  uint16_t  RESERVED5;
  volatile uint16_t TXCRCR;
  uint16_t  RESERVED6;
  volatile uint16_t I2SCFGR;
  uint16_t  RESERVED7;
  volatile uint16_t I2SPR;
  uint16_t  RESERVED8;  
} SPI_TypeDef;



 

typedef struct
{
  volatile uint16_t CR1;
  uint16_t  RESERVED0;
  volatile uint16_t CR2;
  uint16_t  RESERVED1;
  volatile uint16_t SMCR;
  uint16_t  RESERVED2;
  volatile uint16_t DIER;
  uint16_t  RESERVED3;
  volatile uint16_t SR;
  uint16_t  RESERVED4;
  volatile uint16_t EGR;
  uint16_t  RESERVED5;
  volatile uint16_t CCMR1;
  uint16_t  RESERVED6;
  volatile uint16_t CCMR2;
  uint16_t  RESERVED7;
  volatile uint16_t CCER;
  uint16_t  RESERVED8;
  volatile uint16_t CNT;
  uint16_t  RESERVED9;
  volatile uint16_t PSC;
  uint16_t  RESERVED10;
  volatile uint16_t ARR;
  uint16_t  RESERVED11;
  volatile uint16_t RCR;
  uint16_t  RESERVED12;
  volatile uint16_t CCR1;
  uint16_t  RESERVED13;
  volatile uint16_t CCR2;
  uint16_t  RESERVED14;
  volatile uint16_t CCR3;
  uint16_t  RESERVED15;
  volatile uint16_t CCR4;
  uint16_t  RESERVED16;
  volatile uint16_t BDTR;
  uint16_t  RESERVED17;
  volatile uint16_t DCR;
  uint16_t  RESERVED18;
  volatile uint16_t DMAR;
  uint16_t  RESERVED19;
} TIM_TypeDef;



 
 
typedef struct
{
  volatile uint16_t SR;
  uint16_t  RESERVED0;
  volatile uint16_t DR;
  uint16_t  RESERVED1;
  volatile uint16_t BRR;
  uint16_t  RESERVED2;
  volatile uint16_t CR1;
  uint16_t  RESERVED3;
  volatile uint16_t CR2;
  uint16_t  RESERVED4;
  volatile uint16_t CR3;
  uint16_t  RESERVED5;
  volatile uint16_t GTPR;
  uint16_t  RESERVED6;
} USART_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t CFR;
  volatile uint32_t SR;
} WWDG_TypeDef;



 
  


 











 




#line 1312 "..\\Source\\device\\stm32f10x.h"

#line 1335 "..\\Source\\device\\stm32f10x.h"



#line 1354 "..\\Source\\device\\stm32f10x.h"




















 
  


   

#line 1454 "..\\Source\\device\\stm32f10x.h"



 



 
  
  

 
    
 
 
 

 
 
 
 
 

 



 



 


 
 
 
 
 

 











 
#line 1515 "..\\Source\\device\\stm32f10x.h"




 





 
 
 
 
 

 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 





 



 






 
 
 
 
 

 
#line 1691 "..\\Source\\device\\stm32f10x.h"

#line 1698 "..\\Source\\device\\stm32f10x.h"

 
 








 








 






#line 1734 "..\\Source\\device\\stm32f10x.h"

 











 











 













 






#line 1850 "..\\Source\\device\\stm32f10x.h"




#line 1870 "..\\Source\\device\\stm32f10x.h"

 





#line 1883 "..\\Source\\device\\stm32f10x.h"

 
#line 1902 "..\\Source\\device\\stm32f10x.h"

#line 1911 "..\\Source\\device\\stm32f10x.h"

 
#line 1919 "..\\Source\\device\\stm32f10x.h"



















#line 1944 "..\\Source\\device\\stm32f10x.h"












 













#line 1976 "..\\Source\\device\\stm32f10x.h"





#line 1990 "..\\Source\\device\\stm32f10x.h"

#line 1997 "..\\Source\\device\\stm32f10x.h"

#line 2007 "..\\Source\\device\\stm32f10x.h"











 


















#line 2043 "..\\Source\\device\\stm32f10x.h"

 
#line 2051 "..\\Source\\device\\stm32f10x.h"



















#line 2076 "..\\Source\\device\\stm32f10x.h"












 













#line 2108 "..\\Source\\device\\stm32f10x.h"





#line 2122 "..\\Source\\device\\stm32f10x.h"

#line 2129 "..\\Source\\device\\stm32f10x.h"

#line 2139 "..\\Source\\device\\stm32f10x.h"











 








 








   
#line 2178 "..\\Source\\device\\stm32f10x.h"

#line 2273 "..\\Source\\device\\stm32f10x.h"

#line 2300 "..\\Source\\device\\stm32f10x.h"
 
 
 
 
 
 

 




































































 




































































 
#line 2462 "..\\Source\\device\\stm32f10x.h"

 
#line 2480 "..\\Source\\device\\stm32f10x.h"

 
#line 2498 "..\\Source\\device\\stm32f10x.h"

#line 2515 "..\\Source\\device\\stm32f10x.h"

 
#line 2533 "..\\Source\\device\\stm32f10x.h"

 
#line 2552 "..\\Source\\device\\stm32f10x.h"

 

 






 
#line 2579 "..\\Source\\device\\stm32f10x.h"






 








 









 








 








 









 










 




#line 2654 "..\\Source\\device\\stm32f10x.h"

 










#line 2685 "..\\Source\\device\\stm32f10x.h"

 





 
#line 2700 "..\\Source\\device\\stm32f10x.h"

 
#line 2709 "..\\Source\\device\\stm32f10x.h"

   
#line 2718 "..\\Source\\device\\stm32f10x.h"

 
#line 2727 "..\\Source\\device\\stm32f10x.h"

 





 
#line 2742 "..\\Source\\device\\stm32f10x.h"

 
#line 2751 "..\\Source\\device\\stm32f10x.h"

   
#line 2760 "..\\Source\\device\\stm32f10x.h"

 
#line 2769 "..\\Source\\device\\stm32f10x.h"

 





 
#line 2784 "..\\Source\\device\\stm32f10x.h"

 
#line 2793 "..\\Source\\device\\stm32f10x.h"

   
#line 2802 "..\\Source\\device\\stm32f10x.h"

 
#line 2811 "..\\Source\\device\\stm32f10x.h"

 





 
#line 2826 "..\\Source\\device\\stm32f10x.h"

 
#line 2835 "..\\Source\\device\\stm32f10x.h"

   
#line 2844 "..\\Source\\device\\stm32f10x.h"

 
#line 2853 "..\\Source\\device\\stm32f10x.h"

#line 2862 "..\\Source\\device\\stm32f10x.h"

#line 2871 "..\\Source\\device\\stm32f10x.h"

#line 2881 "..\\Source\\device\\stm32f10x.h"

 
 
 
 
 

 





 


 


 




 
 
 
 
 

 
#line 2945 "..\\Source\\device\\stm32f10x.h"

 
#line 2980 "..\\Source\\device\\stm32f10x.h"

 
#line 3015 "..\\Source\\device\\stm32f10x.h"

 
#line 3050 "..\\Source\\device\\stm32f10x.h"

 
#line 3085 "..\\Source\\device\\stm32f10x.h"

 





 





 





 





 





 





 





 





 






 
#line 3152 "..\\Source\\device\\stm32f10x.h"

 



 









 
#line 3176 "..\\Source\\device\\stm32f10x.h"




 




 
#line 3192 "..\\Source\\device\\stm32f10x.h"

 





 
#line 3214 "..\\Source\\device\\stm32f10x.h"

 
 





 
#line 3229 "..\\Source\\device\\stm32f10x.h"
 
#line 3236 "..\\Source\\device\\stm32f10x.h"

 




 






 


 


 


 
 
 
 
 

 
#line 3285 "..\\Source\\device\\stm32f10x.h"

 
#line 3307 "..\\Source\\device\\stm32f10x.h"

 
#line 3329 "..\\Source\\device\\stm32f10x.h"

 
#line 3351 "..\\Source\\device\\stm32f10x.h"

 
#line 3373 "..\\Source\\device\\stm32f10x.h"

 
#line 3395 "..\\Source\\device\\stm32f10x.h"

 
 
 
 
 

 
#line 3431 "..\\Source\\device\\stm32f10x.h"

 
#line 3461 "..\\Source\\device\\stm32f10x.h"

 
#line 3471 "..\\Source\\device\\stm32f10x.h"















 
#line 3495 "..\\Source\\device\\stm32f10x.h"















 
#line 3519 "..\\Source\\device\\stm32f10x.h"















 
#line 3543 "..\\Source\\device\\stm32f10x.h"















 
#line 3567 "..\\Source\\device\\stm32f10x.h"















 
#line 3591 "..\\Source\\device\\stm32f10x.h"















 
#line 3615 "..\\Source\\device\\stm32f10x.h"















 


 


 


 


 


 


 


 


 


 



 


 


 



 


 


 


 



 


 


 


 


 
 
 
 
 

 






 
#line 3716 "..\\Source\\device\\stm32f10x.h"

#line 3725 "..\\Source\\device\\stm32f10x.h"















  
 
#line 3748 "..\\Source\\device\\stm32f10x.h"


















 








































 


















































 


 


 


 


 


 


 
#line 3883 "..\\Source\\device\\stm32f10x.h"

#line 3890 "..\\Source\\device\\stm32f10x.h"

#line 3897 "..\\Source\\device\\stm32f10x.h"

#line 3904 "..\\Source\\device\\stm32f10x.h"







 
#line 3918 "..\\Source\\device\\stm32f10x.h"

#line 3925 "..\\Source\\device\\stm32f10x.h"

#line 3932 "..\\Source\\device\\stm32f10x.h"

#line 3939 "..\\Source\\device\\stm32f10x.h"

#line 3946 "..\\Source\\device\\stm32f10x.h"

#line 3953 "..\\Source\\device\\stm32f10x.h"

 
#line 3961 "..\\Source\\device\\stm32f10x.h"

#line 3968 "..\\Source\\device\\stm32f10x.h"

#line 3975 "..\\Source\\device\\stm32f10x.h"

#line 3982 "..\\Source\\device\\stm32f10x.h"

#line 3989 "..\\Source\\device\\stm32f10x.h"

#line 3996 "..\\Source\\device\\stm32f10x.h"

 
#line 4004 "..\\Source\\device\\stm32f10x.h"

#line 4011 "..\\Source\\device\\stm32f10x.h"

#line 4018 "..\\Source\\device\\stm32f10x.h"

#line 4025 "..\\Source\\device\\stm32f10x.h"





 


 


 


 


 



 
 
 
 
 

 









































 



 


 


 


 


 


 


 



 



 



 


 


 



 
 
 
 
 
 





 






 


 
#line 4167 "..\\Source\\device\\stm32f10x.h"

 
#line 4177 "..\\Source\\device\\stm32f10x.h"

 


 


 
 
 
 
 

 
















 









#line 4225 "..\\Source\\device\\stm32f10x.h"

 

























 
#line 4268 "..\\Source\\device\\stm32f10x.h"

 
#line 4282 "..\\Source\\device\\stm32f10x.h"

 
#line 4292 "..\\Source\\device\\stm32f10x.h"

 




























 





















 




























 





















 
#line 4411 "..\\Source\\device\\stm32f10x.h"

 


 


 


 


 


 


 


 


 
#line 4446 "..\\Source\\device\\stm32f10x.h"





#line 4457 "..\\Source\\device\\stm32f10x.h"

 
#line 4465 "..\\Source\\device\\stm32f10x.h"

#line 4472 "..\\Source\\device\\stm32f10x.h"

 


 
 
 
 
 

 




 
#line 4494 "..\\Source\\device\\stm32f10x.h"

 


 


 


 


 


 


 


 


 
 
 
 
 

 


 





 


 



 
 
 
 
 

 
#line 4556 "..\\Source\\device\\stm32f10x.h"



 
#line 4568 "..\\Source\\device\\stm32f10x.h"







 


 
 
 
 
 

 











#line 4606 "..\\Source\\device\\stm32f10x.h"

 











#line 4629 "..\\Source\\device\\stm32f10x.h"

 











#line 4652 "..\\Source\\device\\stm32f10x.h"

 











#line 4675 "..\\Source\\device\\stm32f10x.h"

 








































 








































 








































 








































 


































 


































 


































 


































 



























 



























 



























 
#line 5072 "..\\Source\\device\\stm32f10x.h"

 
#line 5081 "..\\Source\\device\\stm32f10x.h"

 
#line 5090 "..\\Source\\device\\stm32f10x.h"

 
#line 5101 "..\\Source\\device\\stm32f10x.h"

#line 5111 "..\\Source\\device\\stm32f10x.h"

#line 5121 "..\\Source\\device\\stm32f10x.h"

#line 5131 "..\\Source\\device\\stm32f10x.h"

 
#line 5142 "..\\Source\\device\\stm32f10x.h"

#line 5152 "..\\Source\\device\\stm32f10x.h"

#line 5162 "..\\Source\\device\\stm32f10x.h"

#line 5172 "..\\Source\\device\\stm32f10x.h"

 
#line 5183 "..\\Source\\device\\stm32f10x.h"

#line 5193 "..\\Source\\device\\stm32f10x.h"

#line 5203 "..\\Source\\device\\stm32f10x.h"

#line 5213 "..\\Source\\device\\stm32f10x.h"

 
#line 5224 "..\\Source\\device\\stm32f10x.h"

#line 5234 "..\\Source\\device\\stm32f10x.h"

#line 5244 "..\\Source\\device\\stm32f10x.h"

#line 5254 "..\\Source\\device\\stm32f10x.h"

 
#line 5265 "..\\Source\\device\\stm32f10x.h"

#line 5275 "..\\Source\\device\\stm32f10x.h"

#line 5285 "..\\Source\\device\\stm32f10x.h"

#line 5295 "..\\Source\\device\\stm32f10x.h"

 
#line 5306 "..\\Source\\device\\stm32f10x.h"

#line 5316 "..\\Source\\device\\stm32f10x.h"

#line 5326 "..\\Source\\device\\stm32f10x.h"

#line 5336 "..\\Source\\device\\stm32f10x.h"

 
#line 5347 "..\\Source\\device\\stm32f10x.h"

#line 5357 "..\\Source\\device\\stm32f10x.h"

#line 5367 "..\\Source\\device\\stm32f10x.h"

#line 5377 "..\\Source\\device\\stm32f10x.h"

 


 


 
 
 
 
 

 




 












 


 






#line 5425 "..\\Source\\device\\stm32f10x.h"

 


 


 


 


 


 


 


 


 
















 


 
#line 5495 "..\\Source\\device\\stm32f10x.h"

 
#line 5510 "..\\Source\\device\\stm32f10x.h"

 
#line 5536 "..\\Source\\device\\stm32f10x.h"

 


 


 
 
 
 
 

 
 























 























 























 























 























 























 























 























 
 
#line 5757 "..\\Source\\device\\stm32f10x.h"

 
#line 5769 "..\\Source\\device\\stm32f10x.h"

 






 
#line 5786 "..\\Source\\device\\stm32f10x.h"



     


 
 


 


 


 


 


 


 


 


 

 


 


 


 


 


 


 


 


 

 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 

 


 


 


 


 


 


 


 


 

 


#line 5930 "..\\Source\\device\\stm32f10x.h"



 


#line 5942 "..\\Source\\device\\stm32f10x.h"



 


#line 5954 "..\\Source\\device\\stm32f10x.h"



 


#line 5966 "..\\Source\\device\\stm32f10x.h"



 


#line 5978 "..\\Source\\device\\stm32f10x.h"



 


#line 5990 "..\\Source\\device\\stm32f10x.h"



 


#line 6002 "..\\Source\\device\\stm32f10x.h"



 


#line 6014 "..\\Source\\device\\stm32f10x.h"



 

 


#line 6028 "..\\Source\\device\\stm32f10x.h"



 


#line 6040 "..\\Source\\device\\stm32f10x.h"



 


#line 6052 "..\\Source\\device\\stm32f10x.h"



 


#line 6064 "..\\Source\\device\\stm32f10x.h"



 


#line 6076 "..\\Source\\device\\stm32f10x.h"



 


#line 6088 "..\\Source\\device\\stm32f10x.h"



 


#line 6100 "..\\Source\\device\\stm32f10x.h"



 


#line 6112 "..\\Source\\device\\stm32f10x.h"



 


#line 6124 "..\\Source\\device\\stm32f10x.h"



 


#line 6136 "..\\Source\\device\\stm32f10x.h"



 


#line 6148 "..\\Source\\device\\stm32f10x.h"



 


#line 6160 "..\\Source\\device\\stm32f10x.h"



 


#line 6172 "..\\Source\\device\\stm32f10x.h"



 


#line 6184 "..\\Source\\device\\stm32f10x.h"



 


#line 6196 "..\\Source\\device\\stm32f10x.h"



 


#line 6208 "..\\Source\\device\\stm32f10x.h"



 
 
 
 
 

 
 
#line 6228 "..\\Source\\device\\stm32f10x.h"

 
#line 6239 "..\\Source\\device\\stm32f10x.h"

 
#line 6257 "..\\Source\\device\\stm32f10x.h"











 





 





 
#line 6295 "..\\Source\\device\\stm32f10x.h"

 












 
#line 6316 "..\\Source\\device\\stm32f10x.h"

 
 






 




 





 





 






 




 





 





 






   




 





 





 





 




 





 





 





 




 





 





 
 


 
#line 6456 "..\\Source\\device\\stm32f10x.h"

 
#line 6473 "..\\Source\\device\\stm32f10x.h"

 
#line 6490 "..\\Source\\device\\stm32f10x.h"

 
#line 6507 "..\\Source\\device\\stm32f10x.h"

 
#line 6541 "..\\Source\\device\\stm32f10x.h"

 
#line 6575 "..\\Source\\device\\stm32f10x.h"

 
#line 6609 "..\\Source\\device\\stm32f10x.h"

 
#line 6643 "..\\Source\\device\\stm32f10x.h"

 
#line 6677 "..\\Source\\device\\stm32f10x.h"

 
#line 6711 "..\\Source\\device\\stm32f10x.h"

 
#line 6745 "..\\Source\\device\\stm32f10x.h"

 
#line 6779 "..\\Source\\device\\stm32f10x.h"

 
#line 6813 "..\\Source\\device\\stm32f10x.h"

 
#line 6847 "..\\Source\\device\\stm32f10x.h"

 
#line 6881 "..\\Source\\device\\stm32f10x.h"

 
#line 6915 "..\\Source\\device\\stm32f10x.h"

 
#line 6949 "..\\Source\\device\\stm32f10x.h"

 
#line 6983 "..\\Source\\device\\stm32f10x.h"

 
#line 7017 "..\\Source\\device\\stm32f10x.h"

 
#line 7051 "..\\Source\\device\\stm32f10x.h"

 
#line 7085 "..\\Source\\device\\stm32f10x.h"

 
#line 7119 "..\\Source\\device\\stm32f10x.h"

 
#line 7153 "..\\Source\\device\\stm32f10x.h"

 
#line 7187 "..\\Source\\device\\stm32f10x.h"

 
#line 7221 "..\\Source\\device\\stm32f10x.h"

 
#line 7255 "..\\Source\\device\\stm32f10x.h"

 
#line 7289 "..\\Source\\device\\stm32f10x.h"

 
#line 7323 "..\\Source\\device\\stm32f10x.h"

 
#line 7357 "..\\Source\\device\\stm32f10x.h"

 
#line 7391 "..\\Source\\device\\stm32f10x.h"

 
#line 7425 "..\\Source\\device\\stm32f10x.h"

 
#line 7459 "..\\Source\\device\\stm32f10x.h"

 
 
 
 
 

 









#line 7486 "..\\Source\\device\\stm32f10x.h"

 
#line 7494 "..\\Source\\device\\stm32f10x.h"

 
#line 7504 "..\\Source\\device\\stm32f10x.h"

 


 


 


 


 





















 




 
 
 
 
 

 
#line 7565 "..\\Source\\device\\stm32f10x.h"

 
#line 7574 "..\\Source\\device\\stm32f10x.h"







 



#line 7595 "..\\Source\\device\\stm32f10x.h"



 



 


 
#line 7620 "..\\Source\\device\\stm32f10x.h"

 
#line 7630 "..\\Source\\device\\stm32f10x.h"

 




 


 
 
 
 
 

 
#line 7656 "..\\Source\\device\\stm32f10x.h"

 


 



 
#line 7680 "..\\Source\\device\\stm32f10x.h"

 
#line 7689 "..\\Source\\device\\stm32f10x.h"







 
#line 7709 "..\\Source\\device\\stm32f10x.h"

 
#line 7720 "..\\Source\\device\\stm32f10x.h"



 
 
 
 
 

 


#line 7749 "..\\Source\\device\\stm32f10x.h"

 









#line 7783 "..\\Source\\device\\stm32f10x.h"

 
 
 
 
 

 









 


 


 





 
#line 7823 "..\\Source\\device\\stm32f10x.h"

 


 









 


 

 



 



 



 



 



 



 



 



#line 8287 "..\\Source\\device\\stm32f10x.h"



 

 

  

#line 1 "..\\Source\\main\\stm32f10x_conf.h"



















 

 



 
 
#line 53 "..\\Source\\main\\stm32f10x_conf.h"

 
 

 
 

 
#line 76 "..\\Source\\main\\stm32f10x_conf.h"



 
#line 8298 "..\\Source\\device\\stm32f10x.h"




 

















 









 

  

 

 
#line 33 "..\\Source\\main\\../drivers/./stlib/misc.h"



 



 



 



 

typedef struct
{
  uint8_t NVIC_IRQChannel;                    


 

  uint8_t NVIC_IRQChannelPreemptionPriority;  

 

  uint8_t NVIC_IRQChannelSubPriority;         

 

  FunctionalState NVIC_IRQChannelCmd;         

    
} NVIC_InitTypeDef;
 


 



 
























 



 



 



 







 



 

#line 133 "..\\Source\\main\\../drivers/./stlib/misc.h"


 



 

#line 151 "..\\Source\\main\\../drivers/./stlib/misc.h"















 



 







 



 



 



 



 

void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup);
void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct);
void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset);
void NVIC_SystemLPConfig(uint8_t LowPowerMode, FunctionalState NewState);
void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource);









 



 



 

 
#line 18 "..\\Source\\main\\../drivers/drivers.h"
#line 1 "..\\Source\\main\\../drivers/./stlib/stm32f10x_rcc.h"




















 

 







 
#line 33 "..\\Source\\main\\../drivers/./stlib/stm32f10x_rcc.h"



 



 



 

typedef struct
{
  uint32_t SYSCLK_Frequency;   
  uint32_t HCLK_Frequency;     
  uint32_t PCLK1_Frequency;    
  uint32_t PCLK2_Frequency;    
  uint32_t ADCCLK_Frequency;   
}RCC_ClocksTypeDef;



 



 



 









  



 



#line 94 "..\\Source\\main\\../drivers/./stlib/stm32f10x_rcc.h"



  



 
#line 126 "..\\Source\\main\\../drivers/./stlib/stm32f10x_rcc.h"

#line 141 "..\\Source\\main\\../drivers/./stlib/stm32f10x_rcc.h"


 



 
#line 175 "..\\Source\\main\\../drivers/./stlib/stm32f10x_rcc.h"


 




 
#line 196 "..\\Source\\main\\../drivers/./stlib/stm32f10x_rcc.h"


 

#line 283 "..\\Source\\main\\../drivers/./stlib/stm32f10x_rcc.h"




 

#line 295 "..\\Source\\main\\../drivers/./stlib/stm32f10x_rcc.h"


 



 

#line 317 "..\\Source\\main\\../drivers/./stlib/stm32f10x_rcc.h"


  



 

#line 333 "..\\Source\\main\\../drivers/./stlib/stm32f10x_rcc.h"


 



 

#line 347 "..\\Source\\main\\../drivers/./stlib/stm32f10x_rcc.h"

#line 364 "..\\Source\\main\\../drivers/./stlib/stm32f10x_rcc.h"




 




 








 
#line 396 "..\\Source\\main\\../drivers/./stlib/stm32f10x_rcc.h"


#line 423 "..\\Source\\main\\../drivers/./stlib/stm32f10x_rcc.h"
  



 

#line 435 "..\\Source\\main\\../drivers/./stlib/stm32f10x_rcc.h"


 



 








 



 

#line 462 "..\\Source\\main\\../drivers/./stlib/stm32f10x_rcc.h"


 



 







#line 489 "..\\Source\\main\\../drivers/./stlib/stm32f10x_rcc.h"


 



 

#line 518 "..\\Source\\main\\../drivers/./stlib/stm32f10x_rcc.h"




  



 

#line 553 "..\\Source\\main\\../drivers/./stlib/stm32f10x_rcc.h"
 




 



 







#line 586 "..\\Source\\main\\../drivers/./stlib/stm32f10x_rcc.h"



 



 

#line 606 "..\\Source\\main\\../drivers/./stlib/stm32f10x_rcc.h"

#line 625 "..\\Source\\main\\../drivers/./stlib/stm32f10x_rcc.h"




 



 



 



 



 

void RCC_DeInit(void);
void RCC_HSEConfig(uint32_t RCC_HSE);
ErrorStatus RCC_WaitForHSEStartUp(void);
void RCC_AdjustHSICalibrationValue(uint8_t HSICalibrationValue);
void RCC_HSICmd(FunctionalState NewState);
void RCC_PLLConfig(uint32_t RCC_PLLSource, uint32_t RCC_PLLMul);
void RCC_PLLCmd(FunctionalState NewState);





#line 666 "..\\Source\\main\\../drivers/./stlib/stm32f10x_rcc.h"

void RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSource);
uint8_t RCC_GetSYSCLKSource(void);
void RCC_HCLKConfig(uint32_t RCC_SYSCLK);
void RCC_PCLK1Config(uint32_t RCC_HCLK);
void RCC_PCLK2Config(uint32_t RCC_HCLK);
void RCC_ITConfig(uint8_t RCC_IT, FunctionalState NewState);


 void RCC_USBCLKConfig(uint32_t RCC_USBCLKSource);




void RCC_ADCCLKConfig(uint32_t RCC_PCLK2);






void RCC_LSEConfig(uint8_t RCC_LSE);
void RCC_LSICmd(FunctionalState NewState);
void RCC_RTCCLKConfig(uint32_t RCC_RTCCLKSource);
void RCC_RTCCLKCmd(FunctionalState NewState);
void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks);
void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState);
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);





void RCC_APB2PeriphResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);
void RCC_BackupResetCmd(FunctionalState NewState);
void RCC_ClockSecuritySystemCmd(FunctionalState NewState);
void RCC_MCOConfig(uint8_t RCC_MCO);
FlagStatus RCC_GetFlagStatus(uint8_t RCC_FLAG);
void RCC_ClearFlag(void);
ITStatus RCC_GetITStatus(uint8_t RCC_IT);
void RCC_ClearITPendingBit(uint8_t RCC_IT);








 



 



  

 
#line 19 "..\\Source\\main\\../drivers/drivers.h"
#line 1 "..\\Source\\main\\../drivers/./stlib/stm32f10x_gpio.h"




















 

 







 
#line 33 "..\\Source\\main\\../drivers/./stlib/stm32f10x_gpio.h"



 



 



 

#line 53 "..\\Source\\main\\../drivers/./stlib/stm32f10x_gpio.h"
                                     


 

typedef enum
{ 
  GPIO_Speed_10MHz = 1,
  GPIO_Speed_2MHz, 
  GPIO_Speed_50MHz
}GPIOSpeed_TypeDef;





 

typedef enum
{ GPIO_Mode_AIN = 0x0,
  GPIO_Mode_IN_FLOATING = 0x04,
  GPIO_Mode_IPD = 0x28,
  GPIO_Mode_IPU = 0x48,
  GPIO_Mode_Out_OD = 0x14,
  GPIO_Mode_Out_PP = 0x10,
  GPIO_Mode_AF_OD = 0x1C,
  GPIO_Mode_AF_PP = 0x18
}GPIOMode_TypeDef;








 

typedef struct
{
  uint16_t GPIO_Pin;             
 

  GPIOSpeed_TypeDef GPIO_Speed;  
 

  GPIOMode_TypeDef GPIO_Mode;    
 
}GPIO_InitTypeDef;




 

typedef enum
{ Bit_RESET = 0,
  Bit_SET
}BitAction;





 



 



 

#line 144 "..\\Source\\main\\../drivers/./stlib/stm32f10x_gpio.h"



#line 163 "..\\Source\\main\\../drivers/./stlib/stm32f10x_gpio.h"



 



 

#line 204 "..\\Source\\main\\../drivers/./stlib/stm32f10x_gpio.h"







#line 217 "..\\Source\\main\\../drivers/./stlib/stm32f10x_gpio.h"






#line 245 "..\\Source\\main\\../drivers/./stlib/stm32f10x_gpio.h"
                              


  



 

#line 266 "..\\Source\\main\\../drivers/./stlib/stm32f10x_gpio.h"

#line 274 "..\\Source\\main\\../drivers/./stlib/stm32f10x_gpio.h"



 



 

#line 299 "..\\Source\\main\\../drivers/./stlib/stm32f10x_gpio.h"

#line 316 "..\\Source\\main\\../drivers/./stlib/stm32f10x_gpio.h"



 



  








                                                 


 



 



 



 

void GPIO_DeInit(GPIO_TypeDef* GPIOx);
void GPIO_AFIODeInit(void);
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct);
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx);
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx);
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal);
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal);
void GPIO_PinLockConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_EventOutputConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource);
void GPIO_EventOutputCmd(FunctionalState NewState);
void GPIO_PinRemapConfig(uint32_t GPIO_Remap, FunctionalState NewState);
void GPIO_EXTILineConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource);
void GPIO_ETH_MediaInterfaceConfig(uint32_t GPIO_ETH_MediaInterface);








 



 



 

 
#line 20 "..\\Source\\main\\../drivers/drivers.h"
#line 1 "..\\Source\\main\\../drivers/./stlib/stm32f10x_flash.h"




















 

 







 
#line 33 "..\\Source\\main\\../drivers/./stlib/stm32f10x_flash.h"



 



 



 



 

typedef enum
{ 
  FLASH_BUSY = 1,
  FLASH_ERROR_PG,
  FLASH_ERROR_WRP,
  FLASH_COMPLETE,
  FLASH_TIMEOUT
}FLASH_Status;



 



 



 

#line 77 "..\\Source\\main\\../drivers/./stlib/stm32f10x_flash.h"


 



 







 



 







 



 

 
#line 118 "..\\Source\\main\\../drivers/./stlib/stm32f10x_flash.h"

 
#line 144 "..\\Source\\main\\../drivers/./stlib/stm32f10x_flash.h"

 
#line 211 "..\\Source\\main\\../drivers/./stlib/stm32f10x_flash.h"











 



 







 



 







 



 





#line 270 "..\\Source\\main\\../drivers/./stlib/stm32f10x_flash.h"


 


 
#line 291 "..\\Source\\main\\../drivers/./stlib/stm32f10x_flash.h"






 



 
#line 333 "..\\Source\\main\\../drivers/./stlib/stm32f10x_flash.h"





 
#line 346 "..\\Source\\main\\../drivers/./stlib/stm32f10x_flash.h"



 



 



 



 



 

 
void FLASH_SetLatency(uint32_t FLASH_Latency);
void FLASH_HalfCycleAccessCmd(uint32_t FLASH_HalfCycleAccess);
void FLASH_PrefetchBufferCmd(uint32_t FLASH_PrefetchBuffer);
void FLASH_Unlock(void);
void FLASH_Lock(void);
FLASH_Status FLASH_ErasePage(uint32_t Page_Address);
FLASH_Status FLASH_EraseAllPages(void);
FLASH_Status FLASH_EraseOptionBytes(void);
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data);
FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data);
FLASH_Status FLASH_ProgramOptionByteData(uint32_t Address, uint8_t Data);
FLASH_Status FLASH_EnableWriteProtection(uint32_t FLASH_Pages);
FLASH_Status FLASH_ReadOutProtection(FunctionalState NewState);
FLASH_Status FLASH_UserOptionByteConfig(uint16_t OB_IWDG, uint16_t OB_STOP, uint16_t OB_STDBY);
uint32_t FLASH_GetUserOptionByte(void);
uint32_t FLASH_GetWriteProtectionOptionByte(void);
FlagStatus FLASH_GetReadOutProtectionStatus(void);
FlagStatus FLASH_GetPrefetchBufferStatus(void);
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState);
FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG);
void FLASH_ClearFlag(uint32_t FLASH_FLAG);
FLASH_Status FLASH_GetStatus(void);
FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout);

 
void FLASH_UnlockBank1(void);
void FLASH_LockBank1(void);
FLASH_Status FLASH_EraseAllBank1Pages(void);
FLASH_Status FLASH_GetBank1Status(void);
FLASH_Status FLASH_WaitForLastBank1Operation(uint32_t Timeout);

#line 408 "..\\Source\\main\\../drivers/./stlib/stm32f10x_flash.h"








 



 



 

 
#line 21 "..\\Source\\main\\../drivers/drivers.h"




#line 1 "..\\Source\\main\\../drivers/./Stm32Flash/Stm32Flash.h"


















extern void Stm32FlashWriteTest(void);

extern void Stm32FlashReadTest(void);

extern void stm32_flash_disp(unsigned long ulStartAddr,unsigned long ulEndAddr);


extern int IAP_ProgramInit(unsigned int StartAddress,unsigned int EndAddress);

extern int IAP_ProgramWrite(void *pdat,unsigned int ulDatLen);


extern int Stm32FlashWritePage(uint32_t StartAddress,void *pdat);


extern void stm32_flash_write(unsigned long addr,void *buf,unsigned int len);
extern void stm32_flash_read1(unsigned long addr,unsigned int wantToReadBytes,void *buf,unsigned int bufsize);
extern void stm32_flash_erase_sector(unsigned long sector_id);










#line 26 "..\\Source\\main\\../drivers/drivers.h"


#line 1 "..\\Source\\main\\../drivers/./HardwareCfg/HardwareCfg.h"













































extern void gpio_init(void);

extern void delayms_by_timer(unsigned int ms);


extern void bsp_init(void);









#line 29 "..\\Source\\main\\../drivers/drivers.h"








#line 19 "..\\Source\\main\\includes.h"
	
#line 1 "..\\Source\\main\\../apps/apps.h"
#line 27 "..\\Source\\main\\../apps/apps.h"

#line 21 "..\\Source\\main\\includes.h"

	
	
	
	
	
	
	


#line 9 "..\\Source\\apps\\apps.h"

#line 11 "..\\Source\\apps\\apps.h"

#line 1 "..\\Source\\apps\\./crc32/crc32.h"









extern unsigned int calc_crc32(unsigned int PartialCrc,void *pbuf,unsigned int Length);
















#line 13 "..\\Source\\apps\\apps.h"


#line 1 "..\\Source\\apps\\./update/update.h"















extern void monitor_xmodem(void *buf,unsigned int len);

extern void check_usart_update(void);

extern void check_remote_update(void);

extern void enter_update_mode(void);

extern char is_update_mode(void);

extern void delayms(unsigned long t);

extern unsigned char is_driver_file_by_usart(void);









#line 16 "..\\Source\\apps\\apps.h"












#line 2 "..\\Source\\apps\\apps.c"



#line 1 "..\\Source\\apps\\./crc32/crc32.c"

unsigned int crc32_table[256] = {0};

#line 72 "..\\Source\\apps\\./crc32/crc32.c"

void init_crc32_tabel(void)
{
	unsigned int i = 0;
	unsigned int k = 0;
	unsigned int Val = 0;

	for (i = 0; i < 256; i++)
	{
	    Val = i;
	    for (k = 0; k < 8; k++)
	    {
	        if (Val & 1)
	        {
	            Val = 0xedb88320L ^ (Val >> 1);
	        }
	        else
			{
	            Val = Val >> 1;
			}
	    }
	    crc32_table[i] = Val;
	}
}


unsigned int calc_crc32(unsigned int PartialCrc,void *pbuf,unsigned int Length)
{
    unsigned int crc = 0xffffffffL;
    unsigned int i = 0;
    unsigned char *Buffer = (unsigned char *)pbuf;
	static unsigned char s_init_crc32_tab_flag = 0;

	if (s_init_crc32_tab_flag == 0)
	{
		init_crc32_tabel();
		s_init_crc32_tab_flag = 1;
	}

	if ((pbuf == 0) || (Length == 0))
	{
		return 0;
	}

    crc = PartialCrc ^ 0xffffffffL;

    for (i = 0; i < Length; i++)
    {
        
        crc = crc32_table[(crc ^ Buffer[i]) & 0xff] ^ (crc >> 8);
    }

    return (crc ^ 0xffffffffL);
}




#line 6 "..\\Source\\apps\\apps.c"


#line 1 "..\\Source\\apps\\./update/update.c"
#line 2 "..\\Source\\apps\\./update/update.c"



const  char ver_info[]  __attribute__ ((at((0x08000000 + 0x1000)))) = 
"<" "BYSD" ">" "<" "BYSD_GD32_BOOT_V1.0.1" ">" "<" "Mar 26 2023" ">" "<" "21:17:12" ">"; 



typedef void (*EntryFunc)(void);


unsigned char XOR_Check(INT8U *pdat,INT32U len)
{
	unsigned int i = 0;
	unsigned char temp = pdat[0];

	if (len == 1) return pdat[0];
	
	for (i = 1; i < len; i++)
	{
		temp ^= pdat[i];
	}
	return temp;
}

void stm32_flash_read(unsigned long addr,unsigned int wantToReadBytes,void *buf,unsigned int bufsize)
{
	unsigned long temp = 0;
	unsigned int rb = 0;
	unsigned char *ptr = (unsigned char *)buf;

	if (wantToReadBytes > bufsize)
	{
		wantToReadBytes = bufsize;
	}
	
	while (1)
	{
		temp = *(unsigned long *)addr;
		addr += 4;
		if (rb < wantToReadBytes)
		{
			if ((wantToReadBytes - rb) >= 4)
			{
				memcpy(ptr+rb,&temp,4);
			}
			else
			{
				memcpy(ptr+rb,&temp,wantToReadBytes - rb);
			}
			rb += 4;
		}
		else
		{
			break;
		}
	}
}




int export_bin_file(char is_intel,unsigned int readlen)
{
	unsigned int offset = 0;
	unsigned int slen = 0;
	
	static unsigned char  pbuf[2048] = {0};
	
	unsigned int ulTotalBytes = readlen * 1024;
	unsigned int addr = 0;
	

	if (readlen == 0) return 1;

	

	if (is_intel)
	{
		addr = 20 * 1024;
	}
	else
	{
		addr = 0;
	}

	
	memcpy(pbuf,"BINFILE",strlen("BINFILE"));
	offset = strlen("BINFILE");

	while (ulTotalBytes)
	{
		if (ulTotalBytes > 1024)
		{
			slen = 1024;
		}
		else
		{
			slen = ulTotalBytes;
		}

		pbuf[offset + 0] = slen >> 8;
		pbuf[offset + 1] = slen;

		if (is_intel)
		{
			stm32_flash_read(addr,slen,pbuf + offset + 2,1024);
		}
		else
		{
			
		}
		
		pbuf[offset + 2 + slen] = XOR_Check(pbuf,slen + offset + 2);
		DBG_SendData(pbuf,offset + 2 + slen + 1);
		
		delayms_by_timer(400);

		addr += slen;
		ulTotalBytes -= slen;

#line 136 "..\\Source\\apps\\./update/update.c"
	}
	

	DBG_Print(0,"%s","Import OK.\r\n");
	return 0;
}



void JumpToApp(void)
{
	uint32_t JumpAddress = 0;
	uint32_t SpAddress = 0;
	EntryFunc func;

	
	cpu_int_dis();
	

	JumpAddress = *(volatile uint32_t*) ((0x08000000 + (16 * 1024)) + 4);
	SpAddress = *(volatile uint32_t*)(0x08000000 + (16 * 1024));

	DBG_Print(0,"\r\nJump to Driver(Reset:%08X SP:%08X)...\r\n",JumpAddress,SpAddress);
	delayms(500);	

	func = (EntryFunc)JumpAddress;

  	((SysTick_Type *) ((0xE000E000) + 0x0010))->CTRL  &= ~((1ul << 0));    
	((SysTick_Type *) ((0xE000E000) + 0x0010))->LOAD = 0;
	((SysTick_Type *) ((0xE000E000) + 0x0010))->VAL = 0;

	
	((SCB_Type *) ((0xE000E000) + 0x0D00))->VTOR = (0x08000000 + (16 * 1024));

	__set_MSP(SpAddress);
	func();
}

static const unsigned short crc16tab[256]= {
    0x0000,0x1021,0x2042,0x3063,0x4084,0x50a5,0x60c6,0x70e7,
    0x8108,0x9129,0xa14a,0xb16b,0xc18c,0xd1ad,0xe1ce,0xf1ef,
    0x1231,0x0210,0x3273,0x2252,0x52b5,0x4294,0x72f7,0x62d6,
    0x9339,0x8318,0xb37b,0xa35a,0xd3bd,0xc39c,0xf3ff,0xe3de,
    0x2462,0x3443,0x0420,0x1401,0x64e6,0x74c7,0x44a4,0x5485,
    0xa56a,0xb54b,0x8528,0x9509,0xe5ee,0xf5cf,0xc5ac,0xd58d,
    0x3653,0x2672,0x1611,0x0630,0x76d7,0x66f6,0x5695,0x46b4,
    0xb75b,0xa77a,0x9719,0x8738,0xf7df,0xe7fe,0xd79d,0xc7bc,
    0x48c4,0x58e5,0x6886,0x78a7,0x0840,0x1861,0x2802,0x3823,
    0xc9cc,0xd9ed,0xe98e,0xf9af,0x8948,0x9969,0xa90a,0xb92b,
    0x5af5,0x4ad4,0x7ab7,0x6a96,0x1a71,0x0a50,0x3a33,0x2a12,
    0xdbfd,0xcbdc,0xfbbf,0xeb9e,0x9b79,0x8b58,0xbb3b,0xab1a,
    0x6ca6,0x7c87,0x4ce4,0x5cc5,0x2c22,0x3c03,0x0c60,0x1c41,
    0xedae,0xfd8f,0xcdec,0xddcd,0xad2a,0xbd0b,0x8d68,0x9d49,
    0x7e97,0x6eb6,0x5ed5,0x4ef4,0x3e13,0x2e32,0x1e51,0x0e70,
    0xff9f,0xefbe,0xdfdd,0xcffc,0xbf1b,0xaf3a,0x9f59,0x8f78,
    0x9188,0x81a9,0xb1ca,0xa1eb,0xd10c,0xc12d,0xf14e,0xe16f,
    0x1080,0x00a1,0x30c2,0x20e3,0x5004,0x4025,0x7046,0x6067,
    0x83b9,0x9398,0xa3fb,0xb3da,0xc33d,0xd31c,0xe37f,0xf35e,
    0x02b1,0x1290,0x22f3,0x32d2,0x4235,0x5214,0x6277,0x7256,
    0xb5ea,0xa5cb,0x95a8,0x8589,0xf56e,0xe54f,0xd52c,0xc50d,
    0x34e2,0x24c3,0x14a0,0x0481,0x7466,0x6447,0x5424,0x4405,
    0xa7db,0xb7fa,0x8799,0x97b8,0xe75f,0xf77e,0xc71d,0xd73c,
    0x26d3,0x36f2,0x0691,0x16b0,0x6657,0x7676,0x4615,0x5634,
    0xd94c,0xc96d,0xf90e,0xe92f,0x99c8,0x89e9,0xb98a,0xa9ab,
    0x5844,0x4865,0x7806,0x6827,0x18c0,0x08e1,0x3882,0x28a3,
    0xcb7d,0xdb5c,0xeb3f,0xfb1e,0x8bf9,0x9bd8,0xabbb,0xbb9a,
    0x4a75,0x5a54,0x6a37,0x7a16,0x0af1,0x1ad0,0x2ab3,0x3a92,
    0xfd2e,0xed0f,0xdd6c,0xcd4d,0xbdaa,0xad8b,0x9de8,0x8dc9,
    0x7c26,0x6c07,0x5c64,0x4c45,0x3ca2,0x2c83,0x1ce0,0x0cc1,
    0xef1f,0xff3e,0xcf5d,0xdf7c,0xaf9b,0xbfba,0x8fd9,0x9ff8,
    0x6e17,0x7e36,0x4e55,0x5e74,0x2e93,0x3eb2,0x0ed1,0x1ef0
};

unsigned short CheckCRC16(void *pdat,unsigned int len)
{
	unsigned char *buf = (unsigned char *)pdat;
    unsigned int counter = 0;
    unsigned short crc = 0;

    for ( counter = 0; counter < len; counter++)
    {
        crc = (crc<<8) ^ crc16tab[((crc>>8) ^ *(unsigned char *)buf++)&0x00FF];
    }
    return crc;
}


void *_FindChar(void *pdat,unsigned int datlen,unsigned char ucObj)
{
	unsigned int i = 0;
	unsigned char *pSrc = (unsigned char *)pdat;

	if (datlen == 0) datlen = strlen((char *)pSrc);
	for (i = 0; i < datlen; i++)
	{
		if (*(pSrc+i) == ucObj) return (pSrc+i);
	}
	return 0;
}

unsigned char xor_check(void *ptr,unsigned int len)
{
	unsigned char *pdat = (unsigned char *)ptr;
	unsigned int i = 0;
	INT8U temp = 0;

	if ((ptr == 0) || (len == 0))
	{
		return 0;
	}
	temp = pdat[0];
	if (len == 1) return pdat[0];
	
	for (i = 1; i < len; i++)
	{
		temp ^= pdat[i];
	}
	return temp;
}















unsigned char pagebuf[((uint16_t)0x800) + 1] = {0};

unsigned char ucStatusFlag = 0;
unsigned char s_last_xmodem_bag_id = 0;



int CheckPackIsOk(void *pHead)
{
	INT16U calccrc = 0;
	INT16U realcrc = 0;
	INT8U *ptr = (INT8U *)pHead;
	INT8U num = 0;

	num = ptr[1];

	realcrc = (ptr[3 + 1024] << 8) + ptr[3 + 1024 + 1];
	calccrc = CheckCRC16(ptr + 3,1024);

	
	if (realcrc == calccrc)
	{
		if (num != (s_last_xmodem_bag_id+1))
		{
			return 0;
		}
		s_last_xmodem_bag_id = num;	
		return 1;
	}

	return 0;
}



typedef struct tagDate
{
	INT8U year;
	INT8U month;
	INT8U day;
	INT8U hour;
	INT8U min;
	INT8U sec;
}Date;


typedef enum tagUpdateStatus
{
	UPDATE_STATUS_NO = 0x12,			
	UPDATE_STATUS_START = 0x34,			
	UPDATE_STATUS_FILE_OK = 0x56,		
	UPDATE_STATUS_UPDATE_OK = 0x78,		
										
	UPDATE_STATUS_UPDATE_FALSE = 0x90,
}UpdateStatus;


typedef struct tagUpdateInfo
{
	UpdateStatus eUpdateStatus;						
	INT8U ucUpdateWay;						
	INT32U ulStartAddr;						
	INT32U ulEndAddr;						
	INT32U ulTotalBytes;					
	INT16U usTotalPackCnt;						
	Date stStartTime;				
	INT32U ulStartTime;				
	Date stEndTime;					
	INT32U ulEndTime;				
	INT32U ulTakeTimes;				
	INT8S szReportPhone[20];				
	INT8S szServerAddr[32];
	INT16U usServerPort;
	INT8S szUpdateFileName[32];
}UpdateInfo;

UpdateInfo stUpdateInfo;
unsigned char is_driver_file_flag = 0;	













 
char *GetSubString(char *str,char *pSubStr1,char *pSubStr2,char *pOutBuf,unsigned int outbuflen)
{
	char *pTemp1 = 0;
	char *pTemp2 = 0;
	unsigned int templen = 0;

	if ((str == 0) || (pSubStr1 == 0) || (pOutBuf == 0) || (outbuflen == 0))
	{
		return 0;
	}

	pTemp1 = strstr(str,pSubStr1);
	
	if (pTemp1 == 0) return 0;

	
	if (pSubStr2 && strlen(pSubStr2))
	{
		pTemp2 = strstr(pTemp1 + strlen((char *)pSubStr1),pSubStr2);
	}
	else
	{
		pTemp2 = str + strlen(str);
	}
	if (pTemp2)
	{
		templen = pTemp2 - (pTemp1 + strlen((char *)pSubStr1));
		templen = (outbuflen >= templen) ? templen : outbuflen;
		memset(pOutBuf,0,outbuflen);
		if (templen) memcpy(pOutBuf,pTemp1 + strlen((char *)pSubStr1),templen);

		return pTemp1;
	}
	return 0;
}


char is_app_ver_ok(void)
{
	INT32U addr = stUpdateInfo.ulStartAddr;
	char *ptr1 = 0;
	char *ptr2 = 0;

	char sv[64] = {0};		
	char manufacturer[16] = {0};	
	char old_drv_sv[64] = {0};		
	char tempbuf[16] = {0};

	
	
	memcpy(pagebuf,(unsigned char *)(addr + 0x1000),100);
	memcpy(pagebuf + 110,(unsigned char *)((0x08000000 + (16 * 1024)) + 0x1000),100);

	pagebuf[100] = 0;
	pagebuf[110 + 100] = 0;

	ptr1 = GetSubString((char *)pagebuf,"<",">",manufacturer,sizeof(manufacturer));
	if (ptr1 == 0)
	{
		return 0;
	}
	
	if (strcmp(manufacturer,"BYSD"))
	{
		return 0;
	}
	ptr2 = GetSubString(ptr1 + 1,"<",">",sv,sizeof(sv));
	if (ptr2 == 0)
	{
		return 0;
	}

	
	if (memcmp(sv,"BYSD_DRIVER",strlen("BYSD_DRIVER")) == 0)
	{
		
		memcpy(pagebuf,(unsigned char *)(addr + 40),100);
		
		if ((*(unsigned int *)pagebuf) == 0x11223344)
		{
			is_driver_file_flag = 1;
		}
		else
		{
			is_driver_file_flag = 0;
			DBG_Print(0,"the file is not driver file"
			"[driver file flag1 must:%08X this file flag1:%08X]\r\n",
			0x11223344,(*(unsigned int *)pagebuf));
		}
	}
	else
	{
		is_driver_file_flag = 0;
	}

	if (is_driver_file_flag)
	{
		ptr1 = GetSubString((char *)pagebuf + 110,"<",">",manufacturer,sizeof(manufacturer));
		if (ptr1 == 0)
		{
			return 1;
		}
		
		if (strcmp(manufacturer,"BYSD"))
		{
			return 1;
		}
		ptr2 = GetSubString(ptr1 + 1,"<",">",old_drv_sv,sizeof(old_drv_sv));
		if (ptr2 == 0)
		{
			return 1;
		}

		
		
		
		
		

		
		GetSubString(sv + strlen("BYSD_DRIVER"),"_","_",manufacturer,sizeof(manufacturer));
		GetSubString(old_drv_sv + strlen("BYSD_DRIVER"),"_","_",tempbuf,sizeof(tempbuf));
		if (strcmp(manufacturer,tempbuf))
		{
			DBG_Print(0,"drv cpu type is not match(old:%s new:%s)\r\n",old_drv_sv,sv);
			return 0;
		}

		
		GetSubString(sv + strlen("BYSD_DRIVER"),"_V",".",manufacturer,sizeof(manufacturer));
		GetSubString(old_drv_sv + strlen("BYSD_DRIVER"),"_V",".",tempbuf,sizeof(tempbuf));
		if (strcmp(manufacturer,tempbuf))
		{
			DBG_Print(0,"drv big version is not match(old:%s new:%s)\r\n",old_drv_sv,sv);
			return 0;
		}
	}
	return 1;
}

char is_update_file_ok(void)
{
	unsigned int rlen = 0;
	unsigned int tlen = stUpdateInfo.ulTotalBytes - 4;
	unsigned long addr = 0;
	unsigned char temp[4] = {0};
	unsigned int crc32 = 0;
	unsigned int read_crc32 = 0;

	if (stUpdateInfo.ulTotalBytes <= 4)
	{
		return 0;
	}

	if (is_app_ver_ok() == 0)
	{
		return 0;
	}

	addr = stUpdateInfo.ulStartAddr;

	while (tlen)
	{
		if (tlen > ((uint16_t)0x800))
		{
			rlen = ((uint16_t)0x800);
		}
		else
		{
			rlen = tlen;
		}

		memcpy(pagebuf,(unsigned char *)addr,rlen);

		crc32 = calc_crc32(crc32,pagebuf,rlen);		

		addr += rlen;
		tlen -= rlen;
	}

	memcpy(temp,(unsigned char *)addr,4);
	read_crc32 = (temp[0] << 24) + (temp[1] << 16) + (temp[2] << 8) + temp[3];
	if (crc32 != read_crc32)
	{
		DBG_Print(0,"crc32 check err.update false.(calc:%08X read:%08X)\r\n",
							crc32,read_crc32);
		return 0;
	}
	return 1;
}


char CarryApp(void)
{
	INT32U slen = 0;
	INT32U addr = stUpdateInfo.ulStartAddr;
	INT32U len = stUpdateInfo.ulTotalBytes;

#line 566 "..\\Source\\apps\\./update/update.c"

	enter_update_mode();

	if (is_driver_file_flag)
	{
		IAP_ProgramInit((0x08000000 + (16 * 1024)),(0x08000000 + 0x00060000));
	}
	else
	{
		IAP_ProgramInit(((0x08000000 + (16 * 1024)) + (48 * 1024)),(0x08000000 + 0x00060000));
	}

	DBG_Print(0,"carry app to cpu flash.(external flash start addr:%08X filesize:%uKB)\r\n",
	stUpdateInfo.ulStartAddr,(stUpdateInfo.ulTotalBytes + 1023) / 1024);
	
	while (len)
	{
		if (len >= ((uint16_t)0x800))
		{
			slen = ((uint16_t)0x800);
		}
		else
		{
			slen = len;
		}

		
		
		memcpy(pagebuf,(unsigned char *)addr,slen);
		
		
		
		
		
		IAP_ProgramWrite(pagebuf,((uint16_t)0x800));

		len -= slen;
		addr += slen;
	}
	return 1;
}

void check_remote_update(void)
{
	memcpy(&stUpdateInfo,(unsigned char *)(0x08000000 + (12 * 1024)),sizeof(stUpdateInfo));
	

	DBG_Print(3,"------------------------Update Info------------------------\r\n"
					 "Update Server:%s:%d DownloadFile:%s\r\n"
					 "Store Address In Flash:0x%08X ~ 0x%08X\r\n"
					 "TotalSize:%u TotalPackCnt:%u\r\n"
					 "Time:%02d/%02d/%02d %02d:%02d:%02d ~ %02d/%02d/%02d %02d:%02d:%02d\r\n"
					 "Take Times:%us status:%02X way:%d\r\n"
					 "-----------------------------------------------------------\r\n",
					stUpdateInfo.szServerAddr,stUpdateInfo.usServerPort,stUpdateInfo.szUpdateFileName,
					stUpdateInfo.ulStartAddr,stUpdateInfo.ulEndAddr,
					stUpdateInfo.ulTotalBytes,stUpdateInfo.usTotalPackCnt,
					stUpdateInfo.stStartTime.year,stUpdateInfo.stStartTime.month,
					stUpdateInfo.stStartTime.day,stUpdateInfo.stStartTime.hour,
					stUpdateInfo.stStartTime.min,stUpdateInfo.stStartTime.sec,
	
					stUpdateInfo.stEndTime.year,stUpdateInfo.stEndTime.month,
					stUpdateInfo.stEndTime.day,stUpdateInfo.stEndTime.hour,
					stUpdateInfo.stEndTime.min,stUpdateInfo.stEndTime.sec,
					stUpdateInfo.ulTakeTimes,stUpdateInfo.eUpdateStatus,
					stUpdateInfo.ucUpdateWay
					 );

	
	if (stUpdateInfo.eUpdateStatus == UPDATE_STATUS_FILE_OK)
	{
		
		if (is_update_file_ok())
		{
			CarryApp();
			stUpdateInfo.eUpdateStatus = UPDATE_STATUS_UPDATE_OK;
		}
		else
		{
			stUpdateInfo.eUpdateStatus = UPDATE_STATUS_UPDATE_FALSE;
		}


		stm32_flash_erase_sector((0x08000000 + (12 * 1024)) / 2048);
		stm32_flash_write((0x08000000 + (12 * 1024)),&stUpdateInfo,sizeof(stUpdateInfo));
		
#line 674 "..\\Source\\apps\\./update/update.c"
		JumpToApp();
	}
}



void monitor_xmodem(void *buf,unsigned int len)
{
	char *ptr = 0;
	char *headptr = 0;
	unsigned int rxlen = 0;
	static unsigned char last_bag = 0;
	static unsigned int idx = 0;
	static unsigned long swlen = 0;
	static unsigned char s_first_bag_flag = 1;

	if ((len == 0) || (buf == 0)) return ;
	ptr = (char *)buf;
	rxlen = len;
	if (rxlen >= (1 + 2 + 1024 + 2))
	{
		headptr = (char *)_FindChar(ptr,rxlen,0x02);
		if (headptr)
		{
			if (CheckPackIsOk(headptr))
			{
				if (s_first_bag_flag)
				{
					s_first_bag_flag = 0;
					
					if (
					(headptr[3 + 40 + 0] +
					(headptr[3 + 40 + 1] << 8) +
					(headptr[3 + 40 + 2] << 16) +
					(headptr[3 + 40 + 3] << 24)
					)
					== 0x11223344
					)
					{
						IAP_ProgramInit((0x08000000 + (16 * 1024)),(0x08000000 + 0x00060000));
					}
					else
					{
						IAP_ProgramInit(((0x08000000 + (16 * 1024)) + (48 * 1024)),(0x08000000 + 0x00060000));
					}
				}
				ucStatusFlag = 1;
				memcpy(pagebuf + idx * 1024,headptr + 3,1024);
				idx++;
				if (idx == (((uint16_t)0x800) / 1024))
				{
					idx = 0;
#line 736 "..\\Source\\apps\\./update/update.c"
					cpu_int_dis();
					IAP_ProgramWrite(pagebuf,((uint16_t)0x800));
					cpu_int_en();

					swlen += ((uint16_t)0x800);
					last_bag = 1;
				}
				else
				{
					last_bag = 0;
				}
				DBG_SendChar(0x06);
			}
			else
			{
				DBG_SendChar(0x15);
			}
		}
	}
	else if ((ptr[0] == 0x04) && (rxlen == 1))	
	{
		s_first_bag_flag = 1;
		if (last_bag == 0)
		{
#line 770 "..\\Source\\apps\\./update/update.c"
			cpu_int_dis();
			IAP_ProgramWrite(pagebuf,((uint16_t)0x800));
			cpu_int_en();



			swlen += ((uint16_t)0x800);	
		}

		JumpToApp();
	}
	else
	{
		
	}
}


void check_usart_update(void)
{

	JumpToApp();
#line 839 "..\\Source\\apps\\./update/update.c"
}

char s_update_mode = 0;

void enter_update_mode(void)
{
	s_update_mode = 1;
}

char is_update_mode(void)
{
	return s_update_mode;
}

void delayms(unsigned long t)
{
	volatile unsigned long i = 0;
	for (i = 0; i < t; i++);
}


#line 9 "..\\Source\\apps\\apps.c"





