#include "s21_string.h"


int s21_sscanf(char *str, const char *format, ...) {
    int i = 0;
    t_format_scan info;
    info.read_fail = 0;
    info.ret_value = 0;
    va_start(info.arg, format);
    while (format[i]) {
        if (format[i] == '%') {
            init_struct_scan(&info);
            i = check_flags_scan(&info, format, i + 1, &str);
            if (info.read_fail) {
                if (*str == 0)
                    info.ret_value = -1;
                break;
            }
        }
    }
    int ret = info.ret_value;
    va_end(info.arg);
    return ret;
}

void init_struct_scan(t_format_scan *info) {
    info->width = 0;
    info->l = 0;
    info->h = 0;
    info->hexadecimal = 0;
    info->scientific = 0;
    info->star = 0;
    info->octavian = 0;
}

int check_flags_scan(t_format_scan *info, const char *format, int i, char **str) {
    while (!is_specifier_scan(format[i]) && format[i]) {
        if (format[i] == '*') {
            info->star = 1;;
            i++;
        }
        if (format[i] == 'h') {
            info->h = format[i];
            i++;
        }
        if (format[i] == 'l') {
            info->l = format[i];
            i++;
        }
    }
    handle_specifier_scan(info, str, format[i]);
    return (i + 1);
}

int is_specifier_scan(char c) {
    int result = 0;
    if (c == 'd' || c == 'i' || c == 'f' || c == 'u' || c == 's'
        || c == 'c' || c == 'x' || c == 'X' || c == 'e' || c == 'E'
        || c == 'o' || c == 'p' || c == 'n' || c == 'g' || c == 'G')
        result = 1;
    return result;
}

void handle_specifier_scan(t_format_scan *info, char **str, char spec) {
    char *fake = S21_NULL;
    long long fake_nmb;
    switch (spec) {
        case 'o':
            info->octavian = 1;
            if (!info->star)
                info->ret_value += read_unsigned(str, va_arg(info->arg, unsigned*), info);
            else
                read_unsigned(str, (unsigned*)&fake_nmb, info);
            break;
        case 'i':
            skip_spaces(str);
            if (**str == '0' && (*(*str + 1) == 'x' || *(*str + 1) == 'X')) {
                info->hexadecimal = 1;
                if (!info->star)
                    info->ret_value += read_unsigned(str, va_arg(info->arg, unsigned*), info);
                else
                    read_unsigned(str, (unsigned*)&fake_nmb, info);
            } else if (**str == '0') {
                info->octavian = 1;
                if (!info->star)
                    info->ret_value += read_unsigned(str, va_arg(info->arg, unsigned*), info);
                else
                    read_unsigned(str, (unsigned*)&fake_nmb, info);
            } else {
                if (!info->star)
                    info->ret_value += read_int(str, va_arg(info->arg, int*), info);
                else
                    read_int(str, (int*)&fake_nmb, info);
            }
            break;
        case 'd':
            if (info->l) {
                info->ret_value += read_long(str, va_arg(info->arg, long*), info);
            } else if (info->h) {
                info->ret_value += read_short(str, (short*)va_arg(info->arg, int*), info);
            } else {
                if (!info->star)
                    info->ret_value += read_int(str, va_arg(info->arg, int*), info);
                else
                    read_int(str, (int*)&fake_nmb, info);
            }
            break;
        case 'u':
            if (info->l) {
                info->ret_value += read_unsigned_long(str, va_arg(info->arg, unsigned long*), info);
            } else if (info->h) {
                info->ret_value += read_unsigned_short(str, (unsigned short*)va_arg(info->arg, int*), info);
            } else {
                if (!info->star)
                    info->ret_value += read_unsigned(str, va_arg(info->arg, unsigned*), info);
                else
                    read_unsigned(str, (unsigned*)&fake_nmb, info);
            }
            break;
        case 'x':
            info->hexadecimal = 1;
            if (!info->star)
                info->ret_value += read_unsigned(str, va_arg(info->arg, unsigned*), info);
            else
                read_unsigned(str, (unsigned*)&fake_nmb, info);
            break;
        case 'X':
            info->hexadecimal = 1;
            if (!info->star)
                info->ret_value += read_unsigned(str, va_arg(info->arg, unsigned*), info);
            else
                read_unsigned(str, (unsigned*)&fake_nmb, info);
            break;
        case 'p':
            info->hexadecimal = 1;
            if (!info->star)
                info->ret_value += read_ptr(str, (unsigned long*)va_arg(info->arg, void**), info);
            else
                read_ptr(str, (unsigned long*)&fake_nmb, info);
            break;
        case 'c':
            if (!info->star)
                info->ret_value += read_char(str, va_arg(info->arg, char *), info);
            else
                read_char(str, (char*)&fake_nmb, info);
            break;
        case 's':
            if (!info->star)
                info->ret_value += read_string(str, va_arg(info->arg, char *), info);
            else
                read_string(str, fake, info);
            break;
        case 'g':
        case 'G':
        case 'e':
        case 'E':
        case 'f':
            info->ret_value += read_float(str, info);
            break;
    }
}

int read_char(char **buff, char *target, t_format_scan *info) {
    int res = 0;
    if (**buff) {
        *target = **buff;
        res = 1;
        (*buff)++;
    } else {
        info->read_fail = 1;
        res = -1;
    }
    return res;
}

int read_string(char **buff, char *target, t_format_scan *info) {
    int res = 0;
    skip_spaces(buff);
    if (**buff == 0) {
        res = -1;
    } else {
        while (**buff != '\n' && **buff != ' ' && **buff != '\t' && **buff != 0) {
            !info->star ? (*target = **buff) : 0;
            target++;
            (*buff)++;
            res = 1;
        }
        if (!info->star)
            *target = 0;
    }
    if (res == 0 || res == -1)
        info->read_fail = 1;
    return res;
}

int read_unsigned(char **buff, unsigned *target, t_format_scan *info) {
    int check = 0;
    int res = 0;
    skip_spaces(buff);
    if (info->octavian) {
        if (**buff == '0')
            res = 1;
        check_valid_oct(buff, &res, &check, target);
        if (check) {
            *target = **buff - '0';
            (*buff)++;
        }
        for (; **buff != ' ' && **buff != '\t' && **buff != '\n' && **buff && check; (*buff)++) {
            if ((**buff >= '0' && **buff <= '8'))
                *target = *target * 8 + **buff - '0';
            else
                check = 0;
        }
    } else if (info->hexadecimal) {
        if (**buff == '0')
            res = 1;
        check_valid_hex(buff, &res, &check, target);
        if (check) {
            if (**buff >= 'A' && **buff <= 'F')
                *target = **buff - 55;
            else if (**buff >= 'a' && **buff <= 'f')
                *target = **buff - 87;
            else
                *target = **buff - '0';
            (*buff)++;
        }
        for (; **buff != ' ' && **buff != '\t' && **buff != '\n' && **buff && check; (*buff)++) {
            if ((**buff >= '0' && **buff <= '9') || (**buff >= 'A' && **buff <= 'F') ||
            (**buff >= 'a' && **buff <= 'f')) {
                if (**buff >= 'A' && **buff <= 'F')
                    *target = *target * 16 + **buff - 55;
                else if (**buff >= 'a' && **buff <= 'f')
                    *target = *target * 16 + **buff - 87;
                else
                    *target = *target * 16 + **buff - '0';
            } else {
                check = 0;
            }
        }
    } else {
        if (**buff == '0')
            res = 1;
        check_valid_unsigned(buff, &res, &check, target);
        if (check) {
            *target = **buff - '0';
            (*buff)++;
        }
        for (; **buff != ' ' && **buff != '\t' && **buff != '\n' && **buff && check; (*buff)++) {
            if (**buff >= '0' && **buff <= '9')
                *target = *target * 10 + **buff - '0';
            else
                check = 0;
        }
    }
    skip_spaces(buff);
    if (!res)
        info->read_fail = 1;
    return res;
}

int read_int(char **buff, int *target, t_format_scan *info) {
    int check = 0;
    int res = 0;
    int neg = 0;
    skip_spaces(buff);
    if (**buff == '0')
        res = 1;
    check_valid_int(buff, &res, &check, target, &neg, info);
    if (check) {
        *target = **buff - '0';
        (*buff)++;
        for (; **buff != ' ' && **buff != '\t' && **buff != '\n' && **buff; (*buff)++) {
            if (**buff >= '0' && **buff <= '9')
                *target = *target * 10 + **buff - '0';
            else
                break;
        }
    }
    neg ? (*target *= -1) : 0;
    skip_spaces(buff);
    if (!res)
        info->read_fail = 1;
    return res;
}

int read_long(char **buff, long *target, t_format_scan *info) {
    int check = 0;
    int res = 0;
    int neg = 0;
    skip_spaces(buff);
    if (**buff == '0')
        res = 1;
    check_valid_int(buff, &res, &check, (int*)target, &neg, info);
    if (check) {
        *target = **buff - '0';
        (*buff)++;
        for (; **buff != ' ' && **buff != '\t' && **buff != '\n' && **buff; (*buff)++) {
            if (**buff >= '0' && **buff <= '9')
                *target = *target * 10 + **buff - '0';
            else
                break;
        }
    }
    neg ? (*target *= -1) : 0;
    skip_spaces(buff);
    if (!res)
        info->read_fail = 1;
    return res;
}

int read_unsigned_long(char **buff, unsigned long *target, t_format_scan *info) {
    int check = 0;
    int res = 0;
    skip_spaces(buff);
    if (**buff == '0')
        res = 1;
    check_valid_unsigned_long(buff, &res, &check, target);
    if (check) {
        *target = **buff - '0';
        (*buff)++;
    }
    for (; **buff != ' ' && **buff != '\t' && **buff != '\n' && **buff && check; (*buff)++) {
        if (**buff >= '0' && **buff <= '9')
            *target = *target * 10 + **buff - '0';
        else
            check = 0;
    }
    skip_spaces(buff);
    if (!res)
        info->read_fail = 1;
    return res;
}

int read_short(char **buff, short *target, t_format_scan *info) {
    int check = 0;
    int res = 0;
    int neg = 0;
    skip_spaces(buff);
    if (**buff == '0')
        res = 1;
    check_valid_int(buff, &res, &check, (int*)target, &neg, info);
    if (check) {
        *target = **buff - '0';
        (*buff)++;
        for (; **buff != ' ' && **buff != '\t' && **buff != '\n' && **buff; (*buff)++) {
            if (**buff >= '0' && **buff <= '9')
                *target = *target * 10 + **buff - '0';
            else
                break;
        }
    }
    neg ? (*target *= -1) : 0;
    skip_spaces(buff);
    if (!res)
        info->read_fail = 1;
    return res;
}

int read_unsigned_short(char **buff, unsigned short *target, t_format_scan *info) {
    int check = 0;
    int res = 0;
    int neg = 0;
    skip_spaces(buff);
    if (**buff == '0')
        res = 1;
    check_valid_uns_short(buff, &res, &check, target);
    if (check) {
        *target = **buff - '0';
        (*buff)++;
        for (; **buff != ' ' && **buff != '\t' && **buff != '\n' && **buff; (*buff)++) {
            if (**buff >= '0' && **buff <= '9')
                *target = *target * 10 + **buff - '0';
            else
                break;
        }
    }
    neg ? (*target *= -1) : 0;
    skip_spaces(buff);
    if (!res)
        info->read_fail = 1;
    return res;
}

int read_ptr(char **buff, unsigned long *target, t_format_scan *info) {
    int check = 0;
    int res = 0;
    skip_spaces(buff);
    if (**buff == '0')
        res = 1;
    check_valid_ptr(buff, &res, &check, target);
    if (check) {
        if (**buff >= 'A' && **buff <= 'F')
            *target = **buff - 55;
        else if (**buff >= 'a' && **buff <= 'f')
            *target = **buff - 87;
        else
            *target = **buff - '0';
        (*buff)++;
    }
    for (; **buff != ' ' && **buff != '\t' && **buff != '\n' &&
    **buff && check; (*buff)++) {
        if ((**buff >= '0' && **buff <= '9') || (**buff >= 'A' && **buff <= 'F')
        || (**buff >= 'a' && **buff <= 'f')) {
            if (**buff >= 'A' && **buff <= 'F')
                *target = *target * 16 + **buff - 55;
            else if (**buff >= 'a' && **buff <= 'f')
                *target = *target * 16 + **buff - 87;
            else
                *target = *target * 16 + **buff - '0';
        } else {
            check = 0;
        }
    }
    skip_spaces(buff);
    if (!res)
        info->read_fail = 1;
    return res;
}

int read_float(char **buff, t_format_scan *info) {
    int res = 0;
    skip_spaces(buff);
    if (**buff == 0) {
        res = -1;
    } else if ((**buff >= '0' && **buff <= '9') ||
                **buff == '-' || **buff == '+') {
        double value  = s21_atof(buff, info);
        double exp;
        if ((exp = scientific_presentation(buff)))
            value *= pow(10, exp);
        if (!info->star) {
            *va_arg(info->arg, double *) = value;
            res = 1;
        } else {
            res = 0;
        }
    }
    if ((res == 0 && !info->star) || res == -1)
        info->read_fail = 1;
    return res;
}

int scientific_presentation(char **buff) {
    int exp = 0;
    if ((**buff == 'e' || **buff == 'E') && (*(*buff + 1) == '+' || *(*buff + 1) == '-')
    && *(*buff + 2) >= '0' && *(*buff + 2) <= '9'
    && *(*buff + 3) >= '0' && *(*buff + 3) <= '9') {
        exp = (*(*buff + 2) - '0') * 10 + (*(*buff + 3) - '0');
        if (*(*buff + 1) == '-')
            exp *= -1;
        *buff += 4;
    }
    return exp;
}

double s21_atof(char **buff, t_format_scan *info) {
    if (info->width)
     {;}
    double value = 0, scale = 1;
    int afterpoint = 0, negative = 0;
    if (**buff == '-') {
        negative = 1;
        (*buff)++;
    } else if (**buff == '+') {
        (*buff)++;
    }
    while ((**buff >= '0' && **buff <= '9') || **buff == '.') {
        if (afterpoint) {
            scale = scale / 10;
            value = value + (**buff - '0') * scale;
        } else if (**buff == '.') {
            afterpoint = 1;
        } else {
            value = value * 10.0 + (**buff - '0');
        }
        (*buff)++;
    }
    if (negative)
        value *= -1;
    return value;
}

void skip_zeros_long(char **buff, long long *target) {
    while (**buff == '0') {
        (*buff)++;
        *target = 0;
    }
}

void skip_zeros_int(char **buff, int *target) {
    while (**buff == '0') {
        (*buff)++;
        *target = 0;
    }
}

void skip_zeros_short(char **buff, short *target) {
    while (**buff == '0') {
        (*buff)++;
        *target = 0;
    }
}

void skip_spaces(char **buff) {
    while (**buff == ' ' || **buff == '\t' || **buff == '\n')
        (*buff)++;
}

void check_valid_hex(char **buff, int *res, int *check, unsigned *target) {
    if (**buff == '0' && (*(*buff + 1) == 'x' || *(*buff + 1) == 'X')) {
            *buff = *buff + 2;
            skip_zeros_int(buff, (int*)target);
    }
    skip_zeros_int(buff, (int*)target);
    if ((**buff > '0' && **buff <= '9') || (**buff >= 'A' && **buff <= 'F')
    || (**buff >= 'a' && **buff <= 'f')) {
        *check = 1;
        *res = 1;
    }
}

void check_valid_unsigned(char **buff, int *res, int *check, unsigned *target) {
    skip_zeros_int(buff, (int*)target);
    if (**buff > '0' && **buff <= '9') {
        *check = 1;
        *res = 1;
    }
}

void check_valid_unsigned_long(char **buff, int *res, int *check, unsigned long *target) {
    skip_zeros_long(buff, (long long*)target);
    if (**buff > '0' && **buff <= '9') {
        *check = 1;
        *res = 1;
    }
}

void check_valid_uns_short(char **buff, int *res, int *check, unsigned short *target) {
    skip_zeros_short(buff, (short*)target);
    if (**buff > '0' && **buff <= '9') {
        *check = 1;
        *res = 1;
    }
}

void check_valid_int(char **buff, int *res, int *check, int *target, int *neg, t_format_scan *info) {
    if (**buff == '-') {
        (*buff)++;
        if (info->l)
            skip_zeros_long(buff, (long long*)target);
        else if (info->h)
            skip_zeros_short(buff, (short*)target);
        else
            skip_zeros_int(buff, (int*)target);
        if (**buff > '0' && **buff <= '9') {
            *check = 1;
            *res = 1;
            *neg = 1;
        }
    } else {
        if (info->l)
            skip_zeros_long(buff, (long long*)target);
        else if (info->h)
            skip_zeros_short(buff, (short*)target);
        else
            skip_zeros_int(buff, (int*)target);
        if (**buff > '0' && **buff <= '9') {
            *check = 1;
            *res = 1;
        }
    }
}

void check_valid_oct(char **buff, int *res, int *check, unsigned *target) {
    skip_zeros_int(buff, (int*)target);
    if (**buff > '0' && **buff <= '8') {
        *check = 1;
        *res = 1;
    }
}

void check_valid_ptr(char **buff, int *res, int *check, unsigned long *target) {
    if (**buff == '0' && (*(*buff + 1) == 'x' || *(*buff + 1) == 'X')) {
            *buff = *buff + 2;
            skip_zeros_long(buff, (long long*)target);
    }
    skip_zeros_long(buff, (long long*)target);
    if ((**buff > '0' && **buff <= '9') || (**buff >= 'A' && **buff <= 'F')
    || (**buff >= 'a' && **buff <= 'f')) {
        *check = 1;
        *res = 1;
    }
}
