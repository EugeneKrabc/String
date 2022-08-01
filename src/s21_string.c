#include "s21_string.h"

void *s21_memchr(const void *str, int c, S21_SIZE_T n) {
    const char *tmp = (const char*) str;
    unsigned char chr = (unsigned char) c;
    char *buf = S21_NULL;

    for (S21_SIZE_T i = 0; i < n; i++) {
        if (tmp[i] == chr) {
            buf = (void *)(&tmp[i]);
            break;
        }
    }
    return buf;
}

int s21_memcmp(const void *str1, const void *str2, S21_SIZE_T n) {
    int res = 0;
    for (S21_SIZE_T i = 0; i < n && !res; i++) {
        if (*((char *)str1 + i) != *((char *)str2 + i))
            res = *((char *)str1 + i) - *((char *)str2 + i);
    }
    return res;
}

void *s21_memcpy(void *dest, const void *src, S21_SIZE_T n) {
    const char *src_new = (const char*)src;
    char *dest_new = (char*)dest;
    for (S21_SIZE_T i = 0; i < n; src_new++, dest_new++, i++) {
        *dest_new = *src_new;
    }
    return dest;
}

void *s21_memmove(void *dest, const void *src, S21_SIZE_T n) {
    char* chdest = dest;
    const char* chsrc = src;
    if (chdest <= chsrc || chdest >= chsrc + n) {
        while (n--)
            *chdest++ = *chsrc++;
    } else {
        chdest = chdest + n - 1;
        chsrc = chsrc + n - 1;
        while (n--)
            *chdest-- = *chsrc--;
    }
    return dest;
}

void *s21_memset(void *str, int c, S21_SIZE_T n) {
    unsigned char chr = (unsigned char)c;
    char *tmp = str;
    for (S21_SIZE_T i = 0; i < n; i++) {
        tmp[i] = chr;
    }
    return str;
}

char *s21_strcat(char *dest, const char *src) {
    char *tmp = dest;
    while (*tmp)
        tmp++;
    while (*src) {
        *tmp = *src;
        tmp++;
        src++;
    }
    *tmp = *src;
    return (dest);
}

char *s21_strncat(char *dest, const char *src, S21_SIZE_T n) {
    char *tmp = dest;
    while (*tmp)
        tmp++;
    for (S21_SIZE_T i = 0; i < n; i++, tmp++, src++) {
        *tmp = *src;
    }
    *tmp = '\0';
    return (dest);
}

char *s21_strchr(const char *str, int c) {
    const char *tmp = str;
    unsigned char chr = (unsigned char)c;
    while (*tmp) {
        if (*tmp == chr)
            break;
        tmp++;
    }
    if (*tmp == '\0' && c != 0) {
        tmp = S21_NULL;
    }
    return ((char *) tmp);
}

int s21_strcmp(const char *str1, const char *str2) {
    while (*str1 && *str1 == *str2) {
        str1++;
        str2++;
    }
    return (*str1 - *str2);
}

int s21_strncmp(const char *str1, const char *str2, S21_SIZE_T n) {
    for (S21_SIZE_T i = 0; *str1 == *str2 && i < n - 1; i++) {
        str1++;
        str2++;
    }
    return n == 0 ? 0 : (*str1 - *str2);
}

char *s21_strcpy(char *dest, const char *src) {
    char *tmp = dest;
    while (*src) {
        *tmp = *src;
        tmp++;
        src++;
    }
    *tmp = *src;
    return (dest);
}

char *s21_strncpy(char *dest, const char *src, S21_SIZE_T n) {
    char *tmp = dest;
    for (S21_SIZE_T i = 0; i < n; i++, tmp++, src++) {
        if (*src) {
            *tmp = *src;
        } else {
            *tmp = 0;
        }
    }
    return (dest);
}

S21_SIZE_T s21_strcspn(const char *str1, const char *str2) {
    S21_SIZE_T count = 0;
    int flag = 1;
    for (; *str1; str1++) {
        if (flag) {
            count++;
            const char *tmp = str2;
            for (; *tmp; tmp++) {
                if (*str1 == *tmp) {
                    flag = 0;
                    count--;
                    break;
                }
            }
        }
    }
    return(count);
}

S21_SIZE_T s21_strlen(const char *str) {
    S21_SIZE_T lenght = 0;
    while (*str) {
        str++;
        lenght++;
    }
    return (lenght);
}

char *s21_strpbrk(const char *str1, const char *str2) {
    char *return_value = S21_NULL;
    for (; *str1; str1++) {
        if (!return_value) {
            const char *tmp = str2;
            for (; *tmp; tmp++) {
                if (*tmp == *str1) {
                    return_value = (char*)str1;
                    break;
                }
            }
        }
    }
    return return_value;
}

char *s21_strrchr(const char *str, int c) {
    char *return_value = S21_NULL;
    for (; *str; str++) {
        if (*str == c) {
            return_value = (char*) str;
        }
    }
    if (*str == 0 && c == 0)
        return_value = (char*)str;
    return (return_value);
}

S21_SIZE_T s21_strspn(const char *str1, const char *str2) {
    S21_SIZE_T lenght = 0;
    int flag = 1;
    for (; *str1; str1++) {
        if (flag) {
            const char *tmp = str2;
            for (; *tmp; tmp++) {
                if (*str1 == *tmp) {
                    lenght++;
                    flag = 1;
                    break;
                } else {
                    flag = 0;
                }
            }
        } else {
            break;
        }
    }
    return lenght;
}

char *s21_strstr(const char *haystack, const char *needle) {
    char *tmp_needle = (char*) needle;
    char *value_return = S21_NULL;
    if (!*needle) {
        value_return = (char *)haystack;
    } else {
        for (; *haystack; haystack++) {
            if (*haystack != *tmp_needle) {
                continue;
            }
            char *tmp_haystack = (char*) haystack;
            while (*tmp_needle) {
                if (*tmp_haystack == *tmp_needle) {
                    tmp_needle++;
                    tmp_haystack++;
                } else {
                    tmp_needle = (char*) needle;
                    break;
                }
                if (!*tmp_needle) {
                    value_return = (char *) haystack;
                    break;
                }
            }
        }
    }
    return value_return;
}

char *s21_strtok(char *str, const char *delim) {
    static char *next = S21_NULL;
    if (str) {
      next = str;
    }
    if (next && *next == 0) {
      return S21_NULL;
    }
    char* c = next;
    if (c) {
        while (s21_strchr(delim, *c))
            c++;
    }
    if (c && *c == 0) {
      return S21_NULL;
    }
    char* word = c;
    if (c) {
        while (s21_strchr(delim, *c) == 0)
        c++;
    }
    if (c && *c == 0) {
      next = c;
      return word;
    }
    if (c) {
        *c = 0;
        next = c + 1;
    }
    return word;
}

void *s21_to_upper(const char *str) {
    char *str_up = S21_NULL;
    if (str != S21_NULL) {
        int size = s21_strlen(str) + 1;
        str_up = malloc(size * sizeof(char));
        int i;
        for (i = 0; str[i]; i++) {
            if (str[i] >= 97 && str[i] <= 122) {
                str_up[i] = str[i] - 32;
            } else {
                str_up[i] = str[i];
            }
        }
        str_up[i] = '\0';
    }
    return str_up;
}

void *s21_to_lower(const char *str) {
    char *str_low = S21_NULL;
    if (str != S21_NULL) {
        int size = s21_strlen(str) + 1;
        int i;
        str_low = malloc(size * sizeof(char));
        for (i = 0; str[i]; i++) {
            if (str[i] <= 90 && str[i] >= 65) {
                str_low[i] = str[i] + 32;
            } else {
                str_low[i] = str[i];
            }
        }
        str_low[i] = '\0';
    }
    return str_low;
}

void *s21_insert(const char *src, const char *str, S21_SIZE_T start_index) {
    char *new_str = NULL;
    if (src && str && s21_strlen(src) >= start_index) {
        new_str = (char *)malloc((s21_strlen(src) + s21_strlen(str) + 1) *
                                 sizeof(char));
        if (new_str) {
            s21_strncpy(new_str, src, start_index);
            *(new_str + start_index) = '\0';
            s21_strcat(new_str, str);
            s21_strcat(new_str, src + start_index);
        }
    }
    return (void *)new_str;
}

void *s21_trim(const char *src, const char *trim_chars) {
    char *src_new = S21_NULL;
    if (src != S21_NULL && trim_chars != S21_NULL) {
        int size = s21_strlen(src) + 1;
        src_new = malloc(size * sizeof(char));
        int i = 0, k = size - 2, flag = 1, l;
        while (src[i] && flag) {
            flag = 0;
            for (int j = 0; trim_chars[j]; j++) {
                if (src[i] == trim_chars[j]) {
                    flag = 1;
                    i++;
                    break;
                }
            }
        }
        flag = 1;
        while (k >=0 && flag) {
            flag = 0;
            for (int j = 0; trim_chars[j]; j++) {
                if (src[k] == trim_chars[j]) {
                    flag = 1;
                    k--;
                    break;
                }
            }
        }
        k = k - i;
        for (l = 0; l <= k; i++, l++)
            src_new[l] = src[i];
        src_new[l] = '\0';
    }
    return src_new;
}

char *s21_strerror(int nmb) {
    static char unknown[27];
    s21_sprintf(unknown, "Unknown error: %d", nmb);
    #define ERRSTR(v, s) do {    \
        if (nmb == (v))          \
            return (s);          \
    } while (0);
    ERRSTR(0, "Undefined error: 0");
    ERRSTR(EPERM, "Operation not permitted");
    ERRSTR(ENOENT, "No such file or directory");
    ERRSTR(ESRCH, "No such process");
    ERRSTR(EINTR, "Interrupted system call");
    ERRSTR(EIO, "Input/output error");
    ERRSTR(ENXIO, "Device not configured");
    ERRSTR(E2BIG, "Argument list too long");
    ERRSTR(ENOEXEC, "Exec format error");
    ERRSTR(EBADF, "Bad file descriptor");
    ERRSTR(ECHILD, "No child processes");
    ERRSTR(EDEADLK, "Resource deadlock avoided");
    ERRSTR(ENOMEM, "Cannot allocate memory");
    ERRSTR(EACCES, "Permission denied");
    ERRSTR(EFAULT, "Bad address");
    ERRSTR(ENOTBLK, "Block device required");
    ERRSTR(EBUSY, "Resource busy");
    ERRSTR(EEXIST, "File exists");
    ERRSTR(EXDEV, "Cross-device link");
    ERRSTR(ENODEV, "Operation not supported by device");
    ERRSTR(ENOTDIR, "Not a directory");
    ERRSTR(EISDIR, "Is a directory");
    ERRSTR(EINVAL, "Invalid argument");
    ERRSTR(ENFILE, "Too many open files in system");
    ERRSTR(EMFILE, "Too many open files");
    ERRSTR(ENOTTY, "Inappropriate ioctl for device");
    ERRSTR(ETXTBSY, "Text file busy");
    ERRSTR(EFBIG, "File too large");
    ERRSTR(ENOSPC, "No space left on device");
    ERRSTR(ESPIPE, "Illegal seek");
    ERRSTR(EROFS, "Read-only file system");
    ERRSTR(EMLINK, "Too many links");
    ERRSTR(EPIPE, "Broken pipe");
    ERRSTR(EDOM, "Numerical argument out of domain");
    ERRSTR(ERANGE, "Result too large");
    ERRSTR(EAGAIN, "Resource temporarily unavailable");
    ERRSTR(EINPROGRESS, "Operation now in progress");
    ERRSTR(EALREADY, "Operation already in progress");
    ERRSTR(ENOTSOCK, "Socket operation on non-socket");
    ERRSTR(EDESTADDRREQ, "Destination address required");
    ERRSTR(EMSGSIZE, "Message too long");
    ERRSTR(EPROTOTYPE, "Protocol wrong type for socket");
    ERRSTR(ENOPROTOOPT, "Protocol not available");
    ERRSTR(EPROTONOSUPPORT, "Protocol not supported");
    ERRSTR(ESOCKTNOSUPPORT, "Socket type not supported");
    ERRSTR(EOPNOTSUPP, "Operation not supported");
    ERRSTR(EPFNOSUPPORT, "Protocol family not supported");
    ERRSTR(EAFNOSUPPORT, "Address family not supported by protocol family");
    ERRSTR(EADDRINUSE, "Address already in use");
    ERRSTR(EADDRNOTAVAIL, "Can't assign requested address");
    ERRSTR(ENETDOWN, "Network is down");
    ERRSTR(ENETUNREACH, "Network is unreachable");
    ERRSTR(ENETRESET, "Network dropped connection on reset");
    ERRSTR(ECONNABORTED, "Software caused connection abort");
    ERRSTR(ECONNRESET, "Connection reset by peer");
    ERRSTR(ENOBUFS, "No buffer space available");
    ERRSTR(EISCONN, "Socket is already connected");
    ERRSTR(ENOTCONN, "Socket is not connected");
    ERRSTR(ESHUTDOWN, "Can't send after socket shutdown");
    ERRSTR(ETOOMANYREFS, "Too many references: can't splice");
    ERRSTR(ETIMEDOUT, "Operation timed out");
    ERRSTR(ECONNREFUSED, "Connection refused");
    ERRSTR(ELOOP, "Too many levels of symbolic links");
    ERRSTR(ENAMETOOLONG, "File name too long");
    ERRSTR(EHOSTDOWN, "Host is down");
    ERRSTR(EHOSTUNREACH, "No route to host");
    ERRSTR(ENOTEMPTY, "Directory not empty");
    ERRSTR(EPROCLIM, "Too many processes");
    ERRSTR(EUSERS, "Too many users");
    ERRSTR(EDQUOT, "Disc quota exceeded");
    ERRSTR(ESTALE, "Stale NFS file handle");
    ERRSTR(EREMOTE, "Too many levels of remote in path");
    ERRSTR(EBADRPC, "RPC struct is bad");
    ERRSTR(ERPCMISMATCH, "RPC version wrong");
    ERRSTR(EPROGUNAVAIL, "RPC prog. not avail");
    ERRSTR(EPROGMISMATCH, "Program version wrong");
    ERRSTR(EPROCUNAVAIL, "Bad procedure for program");
    ERRSTR(ENOLCK, "No locks available");
    ERRSTR(ENOSYS, "Function not implemented");
    ERRSTR(EFTYPE, "Inappropriate file type or format");
    #ifdef EAUTH
        ERRSTR(EAUTH, "Authentication error");
    #endif
    #ifdef ENEEDAUTH
        ERRSTR(ENEEDAUTH, "Need authenticator");
    #endif
        ERRSTR(EIDRM, "Device power is off");
        ERRSTR(ENOMSG, "Device error");
    #ifdef EOVERFLOW
        ERRSTR(EOVERFLOW, "Value too large to be stored in data type");
    #endif
        ERRSTR(ECANCELED, "Bad executable (or shared library)");
        ERRSTR(EILSEQ, "Bad CPU type in executable");
    #ifdef ENOATTR
        ERRSTR(ENOATTR, "Shared library version mismatch");
    #endif
    #ifdef EDOOFUS
        ERRSTR(EDOOFUS, "Malformed Mach-o file");
    #endif
    #ifdef EBADMSG
        ERRSTR(EBADMSG, "Operation canceled");
    #endif
    #ifdef EMULTIHOP
        ERRSTR(EMULTIHOP, "Identifier removed");
    #endif
    #ifdef ENOLINK
        ERRSTR(ENOLINK, "No message of desired type");
    #endif
    #ifdef EPROTO
        ERRSTR(EPROTO, "Illegal byte sequence");
    #endif
    ERRSTR(93, "Attribute not found");
    ERRSTR(94, "Bad message");
    ERRSTR(95, "EMULTIHOP (Reserved)");
    ERRSTR(96, "No message available on STREAM");
    ERRSTR(97, "ENOLINK (Reserved)");
    ERRSTR(98, "No STREAM resources");
    ERRSTR(99, "Not a STREAM");
    ERRSTR(100, "Protocol error");
    ERRSTR(101, "STREAM ioctl timeout");
    ERRSTR(102, "Operation not supported on socket");
    ERRSTR(103, "Policy not found");
    ERRSTR(104, "State not recoverable");
    ERRSTR(105, "Previous owner died");
    ERRSTR(106, "Interface output queue is full");
    return unknown;
}