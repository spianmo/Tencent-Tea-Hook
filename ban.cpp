#ifdef _WIN32

#include <tchar.h>
#include <Windows.h>

#else
#include <sys/sysinfo.h>
#include <unistd.h>
#endif

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include "ban.h"

#ifdef _WIN32
#define OS "Windows 32-bit"
#elif _WIN64
#define OS "Windows 64-bit"
#elif __APPLE__ || __MACH__
#define OS "Mac OSX"
#elif __linux__
#define OS "Linux"
#elif __FreeBSD__
#define OS "FreeBSD"
#elif __unix || __unix__
#define OS "Unix"
#else
#define OS "Other"
#endif

struct mem_s {
    uint64_t available, total;
};

static const char *mem_units[] = {"B", "K", "M", "G", "T"};

static void get_hostname(char *, size_t);

static void get_cores(int32_t *);

static void get_mem(struct mem_s *);

static void get_time(char *, size_t);

static void humanize_mem(uint64_t, char *, size_t);

static char *render(const char *, const char *, const char *);

void
bant(const char *name, const char *tpl, char *banner, size_t length) {
    assert(name != NULL);
    assert(tpl != NULL);
    assert(banner != NULL);

    /* Render binary name. */
    char *result = render(tpl, "@NAME@", name);

    /* Render hostname. */
    char *tmp = result;
    char hostname[128] = {'\0'};
    get_hostname(hostname, 128);
    result = render(result, "@HOSTNAME@", hostname);
    free(tmp);

    /* Render operating system. */
    tmp = result;
    result = render(result, "@OS@", OS);
    free(tmp);

    /* Render number of cores. */
    tmp = result;
    int32_t c = 0;
    get_cores(&c);
    char cores[4] = {'\0'};
    snprintf(cores, 4, "%d", c);
    result = render(result, "@CORES@", cores);
    free(tmp);

    /* Render available and total memory. */
    tmp = result;
    struct mem_s m = {.available=0, .total=0};
    get_mem(&m);
    char available[32] = {'\0'};
    humanize_mem(m.available, available, 32);
    char total[32] = {'\0'};
    humanize_mem(m.total, total, 32);
    char mem[64] = {'\0'};
    snprintf(mem, 64, "%s/%s", available, total);
    result = render(result, "@MEM@", mem);
    free(tmp);

    /* Render current time. */
    tmp = result;
    char now[32] = {'\0'};
    get_time(now, 32);
    result = render(result, "@TIME@", now);
    free(tmp);

    /* Dump result in output string. */
    strncpy(banner, result, length);
    free(result);
}

static void
get_hostname(char *hostname, size_t length) {
    assert(hostname != NULL);

#ifdef WIN32
    DWORD size = length;
    GetComputerName(hostname, &size);
#else
    gethostname(hostname, length);
#endif
}

static void
get_cores(int32_t *cores) {
    assert(cores != NULL);

#ifdef WIN32
    SYSTEM_INFO info = {.dwNumberOfProcessors=0};
    GetSystemInfo(&info);
    *cores = info.dwNumberOfProcessors;
#else
    *cores = sysconf(_SC_NPROCESSORS_ONLN);
#endif
}

static void
get_mem(struct mem_s *mem) {
    assert(mem != NULL);

#ifdef WIN32
    MEMORYSTATUS status = {.dwTotalPhys=0, .dwAvailPhys=0};
    GlobalMemoryStatus(&status);
    mem->available = status.dwAvailPhys;
    mem->total = status.dwTotalPhys;
#else
    struct sysinfo info;
    sysinfo(&info);
    mem->available = info.freeram * info.mem_unit;
    mem->total = info.totalram * info.mem_unit;
#endif
}

static void
get_time(char *now, size_t length) {
    assert(now != NULL);

    time_t rawtime;
    time(&rawtime);

    struct tm *timeinfo;
    timeinfo = localtime(&rawtime);

    strftime(now, length, "%FT%T%z", timeinfo);
}

static void
humanize_mem(uint64_t bytes, char *mem, size_t length) {
    assert(mem != NULL);

    int32_t i = 0;
    double d = bytes;

    if (d > 1024.0) {
        for (; bytes / 1024 > 0 && i < 4; ++i, bytes /= 1024) {
            d = bytes / 1024.0;
        }
    }

    snprintf(mem, length, "%.02lf%s", d, mem_units[i]);
}

static char *
render(const char *tpl, const char *p, const char *v) {
    assert(tpl != NULL);

    int32_t idx = 0, cnt = 0;
    size_t plen = strlen(p);
    size_t vlen = strlen(v);

    for (; tpl[idx]; ++idx) {
        if (strstr(tpl + idx, p) == tpl + idx) {
            ++cnt;
            idx += plen - 1;
        }
    }

    char *result = (char *) calloc(idx + cnt * (vlen - plen) + 1, sizeof(char));

    idx = 0;
    while (*tpl) {
        if (strstr(tpl, p) == tpl) {
            strcpy(result + idx, v);
            idx += vlen;
            tpl += plen;
        } else {
            result[idx++] = *tpl++;
        }
    }

    return result;
}