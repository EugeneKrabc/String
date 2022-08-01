#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
    int i = 0 , j = 0;
    t_format info;
    va_start(info.arg, format);
    while (format[i]) {
        if (format[i] == '%') {
            init_struct(&info);
            i = check_flags(&info, format, i + 1, str, &j);
        } else {
            str[j++] = format[i++];
        }
    }
    str[j] = 0;
    va_end(info.arg);
    return j;
}

void init_struct(t_format *info) {
    info->zero = 0;
    info->precision = 0;
    info->minus = 0;
    info->padding = 0;
    info->plus = 0;
    info->point = 0;
    info->sign = 0;
    info->space = 0;
    info->width = 0;
    info->nmb_len = 0;
    info->is_negative = 0;
    info->l = 0;
    info->h = 0;
    info->upper_case = 0;
    info->hexadecimal = 0;
    info->octavian = 0;
    info->scientific = 0;
    info->ptr_val = 0;
    info->get_ptr = 0;
    info->sharp = 0;
    info->L = 0;
}

int check_flags(t_format *info, const char *format, int i, char *str, int *j) {
    char tmp_buf[10] = "";
    int buf_i;
    while (!is_specifier(format[i]) && format[i]) {
        if (format[i] == '-') {
            info->minus = 1;
            i++;
        }
        if (format[i] == '+') {
            info->plus = 1;
            i++;
        }
        if (format[i] == ' ') {
            info->space = 1;
            i++;
        }
        if (format[i] == '0') {
            info->zero = 1;
            i++;
        }
        if (format[i] == '*') {
            info->width = va_arg(info->arg, int);
            i++;
            if (info->width < 0) {
                info->minus = 1;
                info->width *= -1;
            }
        }
        if (format[i] >= '0' && format[i] <= '9') {
            buf_i = 0;
            while (format[i] >= '0' && format[i] <= '9' && buf_i < 9) {
                tmp_buf[buf_i++] = format[i++];
            }
            tmp_buf[buf_i] = 0;
            info->width = s21_atoi(tmp_buf);
        }
        if (format[i] == '.') {
            info->point = 1;
            i++;
            if (format[i] == '*') {
                info->precision = va_arg(info->arg, int);
                i++;
            } else {
                if (format[i] >= '0' && format[i] <='9') {
                    buf_i = 0;
                    while (format[i] >= '0' && format[i] <= '9' && buf_i < 9) {
                        tmp_buf[buf_i++] = format[i++];
                    }
                    tmp_buf[buf_i] = 0;
                    info->precision = s21_atoi(tmp_buf);
                }
            }
        }
        if (format[i] == 'h') {
            info->h = format[i];
            i++;
        }
        if (format[i] == 'l') {
            info->l = format[i];
            i++;
        }
        if (format[i] == '#')
            info->sharp = format[i++];
        if (format[i] == 'L')
            info->L = format[i++];
    }
    handle_specifier(info, str, j, format[i]);
    return (i + 1);
}

int is_specifier(char c) {
    int result = 0;
    if (c == 'd' || c == 'i' || c == 'f' || c == 'u' || c == 's'
        || c == 'c' || c == 'x' || c == 'X' || c == 'e' || c == 'E'
        || c == 'o' || c == 'p' || c == 'n' || c == '%' || c == 'g' || c == 'G')
        result = 1;
    return result;
}

void handle_specifier(t_format *info, char *str, int *j, char spec) {
    long double long_dbl_nmb;
    double dbl_nmb;
    switch (spec) {
        case 'c':
            if (info->l)
                add_wchar(str, j, info);
            else
                add_char(str, j, info);
            break;
        case 'd':
        case 'i':
            if (info->l)
                add_long(str, j, info);
            else if (info->h)
                add_short(str, j, info);
            else
                add_int(str, j, info);
            break;
        case 'u':
            if (info->l)
                add_unsigned_long(str, j, info);
            else if (info->h)
                add_unsigned_short(str, j, info);
            else
                add_unsigned(str, j, info);
            break;
        case 'x':
            info->hexadecimal = 1;
            if (info->l)
                add_unsigned_long(str, j, info);
            else if (info->h)
                add_unsigned_short(str, j, info);
            else
                add_unsigned(str, j, info);
            break;
        case 'X':
            info->hexadecimal = 1;
            info->upper_case = 1;
            if (info->l)
                add_unsigned_long(str, j, info);
            else if (info->h)
                add_unsigned_short(str, j, info);
            else
                add_unsigned(str, j, info);
            break;
        case 'o':
            info->octavian = 1;
            if (info->l)
                add_unsigned_long(str, j, info);
            else if (info->h)
                add_unsigned_short(str, j, info);
            else
                add_unsigned(str, j, info);
            break;
        case 'p':
            info->hexadecimal = 1;
            info->sharp = 1;
            info->ptr_val = (long unsigned)va_arg(info->arg, void *);
            info->get_ptr = 1;
            add_unsigned_long(str, j, info);
            break;
        case 's':
            if (info->l)
                add_Wstring(str, j, info);
            else
                add_string(str, j, info);
            break;
        case 'g':
            if (info->L) {
                long_dbl_nmb = va_arg(info->arg, long double);
                choose_presentation(info, long_dbl_nmb, str, j);
            } else {
                dbl_nmb = va_arg(info->arg, double);
                choose_presentation(info, dbl_nmb, str, j);
            }
            break;
        case 'G':
            info->upper_case = 1;
            if (info->L) {
                long_dbl_nmb = va_arg(info->arg, long double);
                choose_presentation(info, long_dbl_nmb, str, j);
            } else {
                dbl_nmb = va_arg(info->arg, double);
                choose_presentation(info, dbl_nmb, str, j);
            }
            break;
        case 'f':
            if (info->L)
                add_long_float(str, j, info);
            else
                add_double(str, j, info);
            break;
        case 'e':
            info->scientific = 1;
            if (info->L)
                add_long_float(str, j, info);
            else
                add_double(str, j, info);
            break;
        case 'E':
            info->scientific = 1;
            info->upper_case = 1;
            if (info->L)
                add_long_float(str, j, info);
            else
                add_double(str, j, info);
            break;
        case 'n':
            *va_arg(info->arg, int *) = *j;
            break;
        case '%':
            str[(*j)++] = '%';
            break;
    }
}

void choose_presentation(t_format *info, long double nmb, char *str, int *j) {
    char tmp_sci[50] = "";
    if (nmb < 0) {
        nmb *= -1;
        info->is_negative = 1;
    }
    int exp = ftoa_scientific(nmb, tmp_sci, info);
    if (exp >= -4 && exp < info->precision) {
        char tmp_fl[50] = "";
        ftoa(nmb, tmp_fl, info);
        if (tmp_fl[0] == '0' && info->precision)
            info->precision += 2;
        make_precision_for_g(tmp_fl, info);
        trunctacte_zeroes(tmp_fl, info);
        info->nmb_len = s21_strlen(tmp_fl);
        add_flags(str, j, info, tmp_fl, 0);
    } else {
        if (!info->precision && info->point)
            info->precision = 1;
        info->scientific = 1;
        info->nmb_len = s21_strlen(tmp_sci);
        char expo_part[5];
        s21_strcpy(expo_part, &tmp_sci[info->nmb_len - 4]);
        make_precision_for_g(tmp_sci, info);
        trunctacte_zeroes(tmp_sci, info);
        s21_strcat(tmp_sci, expo_part);
        info->nmb_len = s21_strlen(tmp_sci);
        add_flags(str, j, info, tmp_sci, 0);
    }
}

void make_precision_for_g(char *tmp, t_format *info) {
    int curr_nmb = 0;
    for (int i = 0; tmp[i]; i++) {
        if (tmp[i] != '.')
            curr_nmb++;
        if (curr_nmb == info->precision && tmp[i] != '.' && info->precision != 1) {
            if (tmp[i + 1] == '.' && tmp[i + 2] >= '5')
                increase_rank(tmp, i);
            else if (tmp[i + 1] >= '5')
                increase_rank(tmp, i);
        }
        if (curr_nmb > info->precision || (curr_nmb == info->precision && tmp[i] == '.' && !info->sharp)) {
            tmp[i] = 0;
            break;
        }
    }
}

void trunctacte_zeroes(char *buff, t_format *info) {
    int point_flag = 0;
    int only_zeroes_flag = 1;
    int numbers = 0;
    char *tmp = S21_NULL;
    while (*buff) {
        if (*buff != '.')
            numbers++;
        if (point_flag && *buff == '0' && (numbers >= info->precision || info->scientific) && !info->sharp) {
            tmp = buff;
            while (*tmp) {
                if (*tmp != '0') {
                    only_zeroes_flag = 0;
                    break;
                }
                tmp++;
            }
            if (only_zeroes_flag) {
                *buff = 0;
                return;
            }
        }
        if (*buff == '.')
            point_flag = 1;
        buff++;
    }
}

void increase_rank(char *tmp, int index) {
    if (index >= 0) {
        if (tmp[index] == '.') {
            increase_rank(tmp, index - 2);
        } else {
            tmp[index]++;
            if (tmp[index] == 58) {
                increase_rank(tmp, index - 1);
                tmp[index] = '0';
            }
        }
    }
}

void add_char(char *str, int *j, t_format *info) {
    if (info->width) {
        if (info->minus) {
            str[(*j)++] = (char)va_arg(info->arg, int);
            add_spaces_or_zeros(info->width - 1, ' ', str, j);
        } else {
            add_spaces_or_zeros(info->width - 1, ' ', str, j);
            str[(*j)++] = (char)va_arg(info->arg, int);
        }
    } else {
        str[(*j)++] = (char)va_arg(info->arg, int);
    }
}

void add_wchar(char *str, int *j, t_format *info) {
    if (info->width) {
        if (info->minus) {
            str[(*j)++] = (wchar_t)va_arg(info->arg, wchar_t);
            add_spaces_or_zeros(info->width - 1, ' ', str, j);
        } else {
            add_spaces_or_zeros(info->width - 1, ' ', str, j);
            str[(*j)++] = (wchar_t)va_arg(info->arg, wchar_t);
        }
    } else {
        str[(*j)++] = (wchar_t)va_arg(info->arg, wchar_t);
    }
}

void add_string(char *str, int *j, t_format *info) {
    char *ptr;
    ptr = va_arg(info->arg, char *);
    int str_len;
    if (ptr != S21_NULL)
        str_len = s21_strlen(ptr);
    else
        str_len = s21_strlen("(null)");
    if (info->point && !info->precision)
        str_len = 0;
    if (info->width) {
        if (info->minus) {
            if (info->precision && info->precision < str_len)
                str_len = info->precision;
            add_string_to_buff(str, j, str_len, ptr);
            add_spaces_or_zeros(info->width - str_len, ' ', str, j);
        } else {
            if (info->precision && info->precision < str_len)
                str_len = info->precision;
            add_spaces_or_zeros(info->width - str_len, ' ', str, j);
            add_string_to_buff(str, j, str_len, ptr);
        }
    } else {
        if (info->precision && info->precision < str_len)
                str_len = info->precision;
        add_string_to_buff(str, j, str_len, ptr);
    }
}

void add_Wstring(char *str, int *j, t_format *info) {
    wchar_t *ptr;
    ptr = va_arg(info->arg, wchar_t *);
    int str_len;
    char buff[1000];
    int i = 0;
    while (*ptr && ptr) {
        buff[i++] = (char)(*ptr);
        ptr++;
    }
    buff[i] = 0;
    str_len = s21_strlen(buff);
    if (info->point && !info->precision)
        str_len = 0;
    if (info->width) {
        if (info->minus) {
            if (info->precision && info->precision < str_len)
                str_len = info->precision;
            add_string_to_buff(str, j, str_len, buff);
            add_spaces_or_zeros(info->width - str_len, ' ', str, j);
        } else {
            if (info->precision && info->precision < str_len)
                str_len = info->precision;
            add_spaces_or_zeros(info->width - str_len, ' ', str, j);
            add_string_to_buff(str, j, str_len, buff);
        }
    } else {
        if (info->precision && info->precision < str_len)
                str_len = info->precision;
        add_string_to_buff(str, j, str_len, buff);
    }
}

void add_string_to_buff(char *str, int *j, int str_len, char *ptr) {
    if (ptr != S21_NULL)
        s21_strncpy(&str[(*j)], ptr, str_len);
    else
        s21_strncpy(&str[(*j)], "(null)", str_len);
    (*j) += str_len;
}

void add_int(char *str, int *j, t_format *info) {
    char tmp[30] = "";
    int nmb = (int)va_arg(info->arg, int);
    if (nmb < 0) {
        info->is_negative = 1;
        nmb *= -1;
    }
    if (nmb < 0)
        s21_strcat(tmp, "2147483648");
    else
        itoa_unsigned(nmb, tmp, 10, 0, info);
    info->nmb_len = s21_strlen(tmp);
    add_flags(str, j, info, tmp, 1);
}

void add_flags(char *str, int *j, t_format *info, char *tmp, int flag_is_int) {
    int field_len = info->nmb_len;
    if (info->is_negative)
        field_len++;
    int nmb_zero_to_print = 0;
    if (info->precision && info->precision < info->nmb_len && flag_is_int)
        info->precision = info->nmb_len;
    if (info->precision && info->precision > info->nmb_len && flag_is_int)
        nmb_zero_to_print = info->precision - info->nmb_len;
    if (info->sharp) {
        if (info->hexadecimal) {
            field_len += 2;
        } else if (info->octavian) {
            field_len += 2;
            nmb_zero_to_print -= 1;
        }
    }
    if (info->width) {
        if (info->minus) {
            if (info->plus && !info->is_negative)
                add_flag_modifier(str, j, &field_len, '+', 1);
            else if (info->space && !info->is_negative)
                add_flag_modifier(str, j, &field_len, ' ', 1);
            if (info->is_negative && !info->zero)
                add_flag_modifier(str, j, &field_len, '-', 0);
            check_sharp_modifier(str, j, info);
            for (int i = 0; i < nmb_zero_to_print; i++)
                add_flag_modifier(str, j, &field_len, '0', 0);
            s21_strcpy(&str[(*j)], tmp);
            (*j) += info->nmb_len;
            add_spaces_or_zeros(info->width - field_len - nmb_zero_to_print, ' ', str, j);
        } else {
            if ((info->plus || info->space) && !info->is_negative)
                field_len++;
            if (info->plus && !info->is_negative && info->zero)
                add_flag_modifier(str, j, &field_len, '+', 0);
            else if (info->space && !info->is_negative && info->zero)
                add_flag_modifier(str, j, &field_len, ' ', 0);
            else if (info->is_negative && info->zero)
                add_flag_modifier(str, j, &field_len, '-', 0);
            if (info->zero) {
                check_sharp_modifier(str, j, info);
                add_spaces_or_zeros(info->width - field_len - nmb_zero_to_print, '0', str, j);
           } else {
                add_spaces_or_zeros(info->width - field_len - nmb_zero_to_print, ' ', str, j);
           }
            if (info->plus && !info->is_negative && !info->zero)
                add_flag_modifier(str, j, &field_len, '+', 0);
            else if (info->space && !info->is_negative && !info->zero)
                add_flag_modifier(str, j, &field_len, ' ', 0);
            else if (info->is_negative && !info->zero)
                add_flag_modifier(str, j, &field_len, '-', 0);
            if (!info->zero)
                check_sharp_modifier(str, j, info);
            add_spaces_or_zeros(nmb_zero_to_print, '0', str, j);
            s21_strcpy(&str[(*j)], tmp);
            (*j) += info->nmb_len;
        }
    } else {
        if (info->plus && !info->is_negative)
            add_flag_modifier(str, j, &field_len, '+', 1);
        else if (info->space && !info->is_negative)
            add_flag_modifier(str, j, &field_len, ' ', 1);
        if (info->is_negative)
            add_flag_modifier(str, j, &field_len, '-', 0);
        check_sharp_modifier(str, j, info);
        for (int i = 0; i < nmb_zero_to_print; i++)
            add_flag_modifier(str, j, &field_len, '0', 0);
        s21_strcpy(&str[(*j)], tmp);
        (*j) += info->nmb_len;
    }
}

void check_sharp_modifier(char *str, int *j, t_format *info) {
    if (info->sharp && info->hexadecimal) {
        if (info->upper_case) {
            s21_strcpy(&str[(*j)], "0X");
            *j += 2;
        } else {
            s21_strcpy(&str[(*j)], "0x");
            *j += 2;
        }
    } else if (info->sharp && info->octavian) {
        s21_strcpy(&str[(*j)], "0");
        *j += 1;
    }
}

void add_flag_modifier(char *str, int *j, int *field_len, char sign, int inc_field_flag) {
    str[(*j)] = sign;
    (*j)++;
    if (inc_field_flag)
        (*field_len)++;
}

void add_spaces_or_zeros(int number_of_spaces, char c, char *str, int *j) {
    for (int i = 0; i < number_of_spaces; i++) {
        str[(*j)] = c;
        (*j)++;
    }
}

void add_short(char *str, int *j, t_format *info) {
    char tmp[30] = "";
    short nmb = (short)va_arg(info->arg, int);
    if (nmb < 0) {
        info->is_negative = 1;
        nmb *= -1;
    }
    itoa_unsigned(nmb, tmp, 10, 0, info);
    info->nmb_len = s21_strlen(tmp);
    add_flags(str, j, info, tmp, 1);
}

void add_long(char *str, int *j, t_format *info) {
    char tmp[30] = "";
    long long nmb = va_arg(info->arg, long long);
    if (nmb < 0) {
        info->is_negative = 1;
        nmb *= -1;
    }
    itoa_unsigned(nmb, tmp, 10, 0, info);
    info->nmb_len = s21_strlen(tmp);
    add_flags(str, j, info, tmp, 1);
}

void add_unsigned(char *str, int *j, t_format *info) {
    char tmp[30] = "";
    unsigned int nmb = (unsigned)va_arg(info->arg, unsigned);
    if (info->hexadecimal) {
        if (info->upper_case)
            itoa_unsigned(nmb, tmp, 16, 1, info);
        else
            itoa_unsigned(nmb, tmp, 16, 0, info);
    } else if (info->octavian) {
        itoa_unsigned(nmb, tmp, 8, 0, info);
    } else {
        itoa_unsigned(nmb, tmp, 10, 0, info);
    }
    info->nmb_len = s21_strlen(tmp);
    add_flags(str, j, info, tmp, 1);
}

void add_unsigned_short(char *str, int *j, t_format *info) {
    char tmp[30] = "";
    unsigned short nmb = (unsigned short)va_arg(info->arg, int);
    if (info->hexadecimal) {
        if (info->upper_case)
            itoa_unsigned(nmb, tmp, 16, 1, info);
        else
            itoa_unsigned(nmb, tmp, 16, 0, info);
    } else if (info->octavian) {
        itoa_unsigned(nmb, tmp, 8, 0, info);
    } else {
        itoa_unsigned(nmb, tmp, 10, 0, info);
    }
    info->nmb_len = s21_strlen(tmp);
    add_flags(str, j, info, tmp, 1);
}

void add_unsigned_long(char *str, int *j, t_format *info) {
    char tmp[30] = "";
    unsigned long nmb;
    if (info->ptr_val || info->get_ptr)
        nmb = info->ptr_val;
    else
        nmb = (unsigned long)va_arg(info->arg, long int);
    if (info->hexadecimal) {
        if (info->upper_case)
            itoa_unsigned(nmb, tmp, 16, 1, info);
        else
            itoa_unsigned(nmb, tmp, 16, 0, info);
    } else if (info->octavian) {
        itoa_unsigned(nmb, tmp, 8, 0, info);
    } else {
        itoa_unsigned(nmb, tmp, 10, 0, info);
    }
    info->nmb_len = s21_strlen(tmp);
    add_flags(str, j, info, tmp, 1);
}

void add_double(char *str, int *j, t_format *info) {
    char tmp[50] = "";
    double nmb = va_arg(info->arg, double);
    if (nmb < 0) {
        info->is_negative = 1;
        nmb *= -1;
    }
    if (info->scientific)
        ftoa_scientific(nmb, tmp, info);
    else
        ftoa(nmb, tmp, info);
    info->nmb_len = s21_strlen(tmp);
    add_flags(str, j, info, tmp, 0);
}

void add_long_float(char *str, int *j, t_format *info) {
    char tmp[50] = "";
    long double nmb = va_arg(info->arg, long double);
    if (nmb < 0) {
        info->is_negative = 1;
        nmb *= -1;
    }
    if (info->scientific)
        ftoa_scientific(nmb, tmp, info);
    else
        ftoa(nmb, tmp, info);
    info->nmb_len = s21_strlen(tmp);
    add_flags(str, j, info, tmp, 0);
}

int itoa_unsigned(unsigned long n, char *tmp, int radix, int upper_case, t_format *info) {
    if (n == 0 && info->get_ptr == 0)
        info->sharp = 0;
    char a = 'a';
    if (upper_case)
        a = 'A';
    int i = 0;
    if (!(info->point && !info->precision && (info->octavian || info->hexadecimal)) ||
        (info->width && info->point && !info->precision)) {
        do {
            unsigned int remainder = n % radix;
            if (remainder > 9)
                tmp[i] = remainder + a - 10;
            else
                tmp[i] = remainder + '0';
            i++;
        } while ((n /= radix) > 0);
        tmp[i] = 0;
        reverse(tmp);
    }
    return i;
}

void ftoa(long double float_nmb, char *tmp, t_format *info) {
    if (info->precision < 0 || !info->point) {
        info->point = 1;
        info->precision = 6;
    }
    unsigned long int_part = 0;
    int_part = !info->precision ? (unsigned long int)round(float_nmb) : (unsigned long)float_nmb;
    long double float_part = float_nmb - int_part;
    int i = itoa_unsigned(int_part, tmp, 10, 0, info);
    if (info->precision || info->sharp)
        tmp[i++] = '.';
    tmp[i] = 0;
    int precision = info->precision;
    if (precision) {
        while (precision--)
            float_part *= 10;
        char float_buff[50] = {0};
        int float_len = itoa_unsigned((unsigned long)round(float_part), float_buff, 10, 0, info);
        while (float_len++ < info->precision)
            s21_strcat(tmp, "0");
        s21_strcat(tmp, float_buff);
    }
}

int ftoa_scientific(long double float_nmb, char *tmp, t_format *info) {
    if (info->precision < 0 || !info->point) {
        info->point = 1;
        info->precision = 6;
    }
    int exp = normalize(&float_nmb);
    unsigned long int_part = 0;
    int_part = !info->precision ? (unsigned long int)round(float_nmb) : (unsigned long)float_nmb;
    long double float_part = float_nmb - int_part;
    int i = itoa_unsigned(int_part, tmp, 10, 0, info);
    if (info->precision || info->sharp)
        tmp[i++] = '.';
    tmp[i] = 0;
    int precision = info->precision;
    if (precision) {
        while (precision--)
            float_part *= 10;
        char float_buff[30] = "";
        int float_len = itoa_unsigned((unsigned long)round(float_part), float_buff, 10, 0, info);
        while (float_len++ < info->precision)
            s21_strcat(tmp, "0");
        s21_strcat(tmp, float_buff);
    }
    char expo_buffer[30] = "";
    char e;
    if (info->upper_case)
        e = 'E';
    else
        e = 'e';
    s21_sprintf(expo_buffer, "%c%+.2d", e, exp);
    s21_strcat(tmp, expo_buffer);
    return exp;
}

int s21_atoi(char *str) {
    int result = 0;
    for (int i = 0; str[i]; i++) {
        result = result * 10 + str[i] - '0';
    }
    return result;
}

void reverse(char *tmp) {
    int i, j;
    for (i = 0, j = s21_strlen(tmp) - 1; i < j; i++, j--) {
        char c = tmp[i];
        tmp[i] = tmp[j];
        tmp[j] = c;
    }
}

int normalize(long double *val) {
    int exponent = 0;
    long double value = *val;
    if (value != 0) {
        while (value >= 10.0) {
            value /= 10.0;
            ++exponent;
        }

        while (value < 1.0) {
            value *= 10.0;
            --exponent;
        }
        *val = value;
    }
    return exponent;
}
