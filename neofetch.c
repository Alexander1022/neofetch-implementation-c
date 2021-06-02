#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/sysinfo.h> 

#if defined(_WIN32)
    #define PLATFORM_NAME "Windows NT x32" 

#elif defined(_WIN64)
    #define PLATFORM_NAME "Windows NT x64" 

#elif defined(__CYGWIN__) && !defined(_WIN32)
    #define PLATFORM_NAME "Windows NT" 

#elif defined(__ANDROID__)
    #define PLATFORM_NAME "Android" 

#elif defined(__linux__)
    #define PLATFORM_NAME "Linux" 

#elif defined(__unix__) || !defined(__APPLE__) && defined(__MACH__)
    #if defined(BSD)
        #define PLATFORM_NAME "BSD" 
    #endif

#elif defined(__hpux)
    #define PLATFORM_NAME "HP-UX" 

#elif defined(_AIX)
    #define PLATFORM_NAME "AIX" 

#elif defined(__APPLE__) && defined(__MACH__) 
    #if TARGET_IPHONE_SIMULATOR == 1
        #define PLATFORM_NAME "iOS" 

    #elif TARGET_OS_IPHONE == 1
        #define PLATFORM_NAME "iOS" 

    #elif TARGET_OS_MAC == 1
        #define PLATFORM_NAME "OSX" 
    #endif

#elif defined(__sun) && defined(__SVR4)
    #define PLATFORM_NAME "Solaris"

#else
    #define PLATFORM_NAME NULL
#endif

char *get_platform_name() 
{
    if(PLATFORM_NAME != NULL)
    {
        return PLATFORM_NAME;
    }

    else
    {
        return "Unknown";
    }
}

void getUptime(struct sysinfo sysInfo)
{
    int days = sysInfo.uptime / 86400;
    int hours = (sysInfo.uptime / 3600) - (days * 24);
    int mins = (sysInfo.uptime / 60) - (days * 1440) - (hours * 60);
    
    if(hours > 1)
    {
        printf("Uptime: %d hours, %d minutes\n", hours, mins);
    }
    
    else
    {
        printf("Uptime: %d hour, %d minutes\n", hours, mins);
    }   
}

void getMemory(struct sysinfo sysInfo)
{
    unsigned long totalRAM = sysInfo.totalram / 1000000000;
    unsigned long freeRAM = sysInfo.freeram / 1000000000;

    printf("Free memory : %lu/%lu", freeRAM, totalRAM);
}

int main()
{
    struct sysinfo sysInfo;

    printf("------------------\n");
    printf("OS : %s\n", get_platform_name());
    getUptime(sysInfo);
    getMemory(sysInfo);
    return 0;
}