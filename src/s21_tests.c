#include <check.h>
#include <stdio.h>
#include <string.h>
#include "s21_string.h"

int r1, r2;

START_TEST(test_s21_memchr) {
    char str1[] = "Hello world!", str2[] = "";
    ck_assert_ptr_eq(s21_memchr(str1, 'w', 13), memchr(str1, 'w', 13));
    ck_assert_ptr_eq(s21_memchr(str1, ' ', 13), memchr(str1, ' ', 13));
    ck_assert_ptr_eq(s21_memchr(str1, 111, 13), memchr(str1, 111, 13));
    ck_assert_ptr_eq(s21_memchr(str2, ' ', 1), memchr(str2, ' ', 1));
}
END_TEST

START_TEST(test_s21_memcmp) {
    char str1[] = "abcdefghj", str2[] = "abcdefghj", str3[] = "abcdefghjz",
         str4[] = "", str5[] = "\n";
    ck_assert_int_eq(s21_memcmp(str1, str2, 10), memcmp(str1, str2, 10));
    ck_assert_int_eq(s21_memcmp(str1, str3, 10), memcmp(str1, str3, 10));
    ck_assert_int_eq(s21_memcmp(str1, str4, 1), memcmp(str1, str4, 1));
    ck_assert_int_eq(s21_memcmp(str5, str4, 1), memcmp(str5, str4, 1));
}
END_TEST

START_TEST(test_s21_memcpy) {
    char str1[] = "abcd", str2[] = "efgh", str3[] = "efghi", str4[] = "",
         str5[] = "abcd", str6[] = "efgh", str7[] = "efghi", str8[] = "";

    s21_memcpy(str1, str2, 4);
    memcpy(str5, str6, 4);
    ck_assert_pstr_eq(str1, str5);

    s21_memcpy(str1, str3, 4);
    memcpy(str5, str7, 4);
    ck_assert_pstr_eq(str1, str5);

    s21_memcpy(str3, str1, 1);
    memcpy(str7, str5, 1);
    ck_assert_pstr_eq(str3, str7);

    s21_memcpy(str1, str4, 1);
    memcpy(str5, str8, 1);
    ck_assert_pstr_eq(str1, str5);
}
END_TEST

START_TEST(test_s21_memmove) {
    char str1[] = "abcd", str2[] = "efgh", str3[] = "iuytr", str4[] = "";
    char str5[] = "abcd", str6[] = "efgh", str7[] = "iuytr", str8[] = "";
    ck_assert_pstr_eq(s21_memmove(str1, str2, 5), memmove(str5, str6, 5));
    ck_assert_pstr_eq(s21_memmove(str1, str3, 4), memmove(str5, str7, 4));
    ck_assert_pstr_eq(s21_memmove(str3, str4, 1), memmove(str7, str8, 1));
    ck_assert_pstr_eq(s21_memmove(str1, str2, 5), memmove(str5, str6, 5));
    ck_assert_pstr_eq(s21_memmove(str1, str2, 5), memmove(str5, str6, 5));
    ck_assert_pstr_eq(s21_memmove(str1, str2, 5), memmove(str5, str6, 5));
}
END_TEST

START_TEST(test_s21_memset) {
    char str1[9] = "abcdefgh", str2[1] = "", str3[9] = "abcdefgh", str4[1] = "";

    s21_memset(str1, 'i', 8);
    memset(str3, 'i', 8);
    ck_assert_pstr_eq(str1, str3);

    s21_memset(str1, 'i', 5);
    memset(str3, 'i', 5);
    ck_assert_pstr_eq(str1, str3);

    s21_memset(str1, ' ', 5);
    memset(str3, ' ', 5);
    ck_assert_pstr_eq(str1, str3);

    s21_memset(str1, ' ', 8);
    memset(str3, ' ', 8);
    ck_assert_pstr_eq(str1, str3);

    s21_memset(str2, ' ', 1);
    memset(str4, ' ', 1);
    ck_assert_pstr_eq(str1, str3);

    s21_memset(str2, 'i', 1);
    memset(str4, 'i', 1);
    ck_assert_pstr_eq(str1, str3);
}
END_TEST

START_TEST(test_s21_strcat) {
    char str1[32] = "Hello world", str2[] = "qwe", str3[] = " \n\0",
         str4[] = "\0", str5[] = "abcde\0", str6[32] = "",
         str7[32] = "Hello world", str8[] = "qwe", str9[] = " \n\0",
         str10[] = "\0", str11[] = "abcde\0", str12[32] = "";

    s21_strcat(str1, str3);
    strcat(str7, str9);
    ck_assert_pstr_eq(str1, str7);

    s21_strcat(str2, str4);
    strcat(str8, str10);
    ck_assert_pstr_eq(str2, str8);

    s21_strcat(str5, str4);
    strcat(str11, str10);
    ck_assert_pstr_eq(str5, str11);

    s21_strcat(str3, str4);
    strcat(str9, str10);
    ck_assert_pstr_eq(str3, str9);

    s21_strcat(str6, str2);
    strcat(str12, str8);
    ck_assert_pstr_eq(str6, str12);
}
END_TEST

START_TEST(test_s21_strncat) {
    char str1[32] = "Hello world", str2[] = "qwe", str3[] = " \n\0",
         str4[] = "\0", str6[32] = "", str7[32] = "Hello world", str8[] = "qwe",
         str9[] = " \n\0", str10[] = "\0", str12[32] = "";

    s21_strncat(str1, str3, 4);
    strncat(str7, str9, 4);
    ck_assert_pstr_eq(str1, str7);

    s21_strncat(str2, str4, 3);
    strncat(str8, str10, 3);
    ck_assert_pstr_eq(str2, str8);

    s21_strncat(str6, str2, 4);
    strncat(str12, str8, 4);
    ck_assert_pstr_eq(str6, str12);
}
END_TEST

START_TEST(test_s21_strchr) {
    char str1[] = "Hello world!", str2[] = "";
    ck_assert_pstr_eq(s21_strchr(str2, 33), strchr(str2, 33));
    ck_assert_pstr_eq(s21_strchr(str1, 'w'), strchr(str1, 'w'));
    ck_assert_pstr_eq(s21_strchr(str1, 108), strchr(str1, 108));
    ck_assert_pstr_eq(s21_strchr(str1, ' '), strchr(str1, ' '));
    ck_assert_pstr_eq(s21_strchr(str1, 'a'), strchr(str1, 'a'));
}
END_TEST

START_TEST(test_s21_strcmp) {
    char str1[] = "abcd", str2[] = "abcd", str4[] = "efghi", str5[] = "";
    ck_assert_int_eq(s21_strcmp(str1, str2), strcmp(str1, str2));
    ck_assert_int_eq(s21_strcmp(str4, str1), strcmp(str4, str1));
    ck_assert_int_eq(s21_strcmp(str5, str1), strcmp(str5, str1));
    ck_assert_int_eq(s21_strcmp(str1, str5), strcmp(str1, str5));
}
END_TEST

START_TEST(test_s21_strncmp) {
    char str1[] = "abcd", str2[] = "abcd", str3[] = "efgh", str4[] = "efghi",
         str5[] = "";
    ck_assert_int_eq(s21_strncmp(str1, str2, 5), strncmp(str1, str2, 5));
    ck_assert_int_eq(s21_strncmp(str1, str3, 5), strncmp(str1, str3, 5));
    ck_assert_int_eq(s21_strncmp(str1, str3, 4), strncmp(str1, str3, 4));
    ck_assert_int_eq(s21_strncmp(str1, str4, 5), strncmp(str1, str4, 5));
    ck_assert_int_eq(s21_strncmp(str4, str1, 4), strncmp(str4, str1, 4));
    ck_assert_int_eq(s21_strncmp(str5, str1, 1), strncmp(str5, str1, 1));
    ck_assert_int_eq(s21_strncmp(str1, str5, 1), strncmp(str1, str5, 1));
}
END_TEST

START_TEST(test_s21_strcpy) {
    char str1[] = "Hello", str2[] = "World", str3[] = "", str4[32] = "",
         str5[] = "Hello", str6[] = "World", str7[] = "", str8[32] = "";

    s21_strcpy(str1, str2);
    strcpy(str5, str6);
    ck_assert_str_eq(str1, str5);

    s21_strcpy(str2, str1);
    strcpy(str6, str5);
    ck_assert_str_eq(str2, str6);

    s21_strcpy(str1, str3);
    strcpy(str5, str7);
    ck_assert_str_eq(str1, str5);

    s21_strcpy(str4, str1);
    strcpy(str8, str5);
    ck_assert_str_eq(str4, str8);

    s21_strcpy(str4, str3);
    strcpy(str8, str7);
    ck_assert_str_eq(str4, str8);
}
END_TEST

START_TEST(test_s21_strncpy) {
    char str1[] = "kjzxnvkjbsdfjhkbbds", str2[] = "jsdjsdfkjdsfjh", str3[] = "",
         str4[] = "kjzxnvkjbsdfjhkbbds", str5[] = "jsdjsdfkjdsfjh", str6[] = "";

    s21_strncpy(str1, str2, 5);
    strncpy(str4, str5, 5);
    ck_assert_str_eq(str1, str4);

    s21_strncpy(str1, str2, 20);
    strncpy(str4, str5, 20);
    ck_assert_str_eq(str1, str4);

    s21_strncpy(str1, str2, 15);
    strncpy(str4, str5, 15);
    ck_assert_str_eq(str1, str4);

    s21_strncpy(str2, str1, 8);
    strncpy(str5, str4, 8);
    ck_assert_str_eq(str1, str4);

    s21_strncpy(str2, str1, 15);
    strncpy(str5, str4, 15);
    ck_assert_str_eq(str1, str4);

    s21_strncpy(str1, str3, 8);
    strncpy(str4, str6, 8);
    ck_assert_str_eq(str1, str4);
}
END_TEST

START_TEST(test_s21_strcspn) {
    char str1[] = "jkflkfgdkhslkhgsdk", str2[] = "gd", str3[] = "";
    ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
    ck_assert_int_eq(s21_strcspn(str2, str1), strcspn(str2, str1));
    ck_assert_int_eq(s21_strcspn(str1, str3), strcspn(str1, str3));
    ck_assert_int_eq(s21_strcspn(str2, str3), strcspn(str2, str3));
    ck_assert_int_eq(s21_strcspn(str3, str1), strcspn(str3, str1));
    ck_assert_int_eq(s21_strcspn(str3, str2), strcspn(str3, str2));
}
END_TEST

START_TEST(test_s21_strerror) {
    for (int j = 0, err = -1; j < 3; j++) {
        char *errtest1 = s21_strerror(err);
        char *errtest2 = strerror(err);
        S21_SIZE_T i = 0, len1 = s21_strlen(errtest1),
                   len2 = s21_strlen(errtest2);
        while (i < len1 || i < len2) {
            ck_assert_str_eq(errtest1 + i, errtest2 + i);
            i++;
        }
        err += 1;
    }
}
END_TEST

START_TEST(test_s21_strlen) {
    char str1[] = "Hello world!", str2[] = "", str3[] = "!@IU@!*&$@1KWljD",
         str4[] = "Hello world!\n", str5[] = "123456";
    ck_assert_int_eq(s21_strlen(str1), strlen(str1));
    ck_assert_int_eq(s21_strlen(str2), strlen(str2));
    ck_assert_int_eq(s21_strlen(str3), strlen(str3));
    ck_assert_int_eq(s21_strlen(str4), strlen(str4));
    ck_assert_int_eq(s21_strlen(str5), strlen(str5));
}
END_TEST

START_TEST(test_s21_strpbrk) {
    char str1[] = "abcdefghijklmnop", str2[] = "pkh", str3[] = "";
    ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
    ck_assert_ptr_eq(s21_strpbrk(str2, str1), strpbrk(str2, str1));
    ck_assert_ptr_eq(s21_strpbrk(str1, str3), strpbrk(str1, str3));
    ck_assert_ptr_eq(s21_strpbrk(str2, str3), strpbrk(str2, str3));
    ck_assert_ptr_eq(s21_strpbrk(str3, str1), strpbrk(str3, str1));
    ck_assert_ptr_eq(s21_strpbrk(str3, str2), strpbrk(str3, str2));
}
END_TEST

START_TEST(test_s21_strrchr) {
    char str1[] = ";odsagjnpasdun 1242149215", str2[] = "";
    ck_assert_pstr_eq(s21_strrchr(str1, 'a'), strrchr(str1, 'a'));
    ck_assert_pstr_eq(s21_strrchr(str1, 100), strrchr(str1, 100));
    ck_assert_pstr_eq(s21_strrchr(str1, '/'), strrchr(str1, '/'));
    ck_assert_pstr_eq(s21_strrchr(str1, 98), strrchr(str1, 98));
    ck_assert_pstr_eq(s21_strrchr(str2, 'a'), strrchr(str2, 'a'));
    ck_assert_pstr_eq(s21_strrchr(str2, ' '), strrchr(str2, ' '));
    ck_assert_pstr_eq(s21_strrchr(str2, 56), strrchr(str2, 56));
}
END_TEST

START_TEST(test_s21_strspn) {
    char str1[] = "a;iuhgilsdugiaudhgiu2", str2[] = "gsdsgk", str3[] = "i2u",
         str4[] = "";
    ck_assert_int_eq(s21_strspn(str1, str2), strspn(str1, str2));
    ck_assert_int_eq(s21_strspn(str1, str3), strspn(str1, str3));
    ck_assert_int_eq(s21_strspn(str2, str1), strspn(str2, str1));
    ck_assert_int_eq(s21_strspn(str3, str1), strspn(str3, str1));
    ck_assert_int_eq(s21_strspn(str2, str3), strspn(str2, str3));
    ck_assert_int_eq(s21_strspn(str2, str4), strspn(str2, str4));
    ck_assert_int_eq(s21_strspn(str4, str1), strspn(str4, str1));
}
END_TEST

START_TEST(test_s21_strstr) {
    char str1[] = "abcdefghijklm", str2[] = "hij", str3[] = "", str4[] = "edc";
    ck_assert_pstr_eq(s21_strstr(str1, str2), strstr(str1, str2));
    ck_assert_pstr_eq(s21_strstr(str1, str4), strstr(str1, str4));
    ck_assert_pstr_eq(s21_strstr(str2, str1), strstr(str2, str1));
    ck_assert_pstr_eq(s21_strstr(str2, str4), strstr(str2, str4));
    ck_assert_pstr_eq(s21_strstr(str3, str1), strstr(str3, str1));
    ck_assert_pstr_eq(s21_strstr(str3, str2), strstr(str3, str2));
    ck_assert_pstr_eq(s21_strstr(str3, str4), strstr(str3, str4));
}
END_TEST

START_TEST(test_s21_strtok) {
    char arr1[100] = "My name is Root. Hello world!", *parr1 = arr1,
         arr2[100] = "My name is Root. Hello world!", *parr2 = arr2;

    s21_strtok(parr1, " .");
    strtok(parr2, " .");
    ck_assert_pstr_eq(parr1, parr2);

    parr1 = s21_strtok(NULL, " .");
    parr2 = strtok(NULL, " .");
    ck_assert_pstr_eq(parr1, parr2);

    parr1 = s21_strtok(parr1, "x");
    parr2 = strtok(parr2, "x");
    ck_assert_pstr_eq(parr1, parr2);
}
END_TEST

START_TEST(test_s21_sprintf) {
    char c[255] = {}, d[255] = {}, x1 = 't';
    wchar_t wch1 = 'W', wch2 = 'C';
    int n = 2100, n1 = 0, n2 = -21;
    short sh = 123, sh1 = -123;
    float f = 21.21, f1 = -21.21;
    long int lg = 12345678912345, lg1 = -12345678912345;
    s21_sprintf(c, "%% %p", &n);
    sprintf(d, "%% %p", &n);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%d %d %d %hd %hd %ld %ld %10ld", n, n1, n2, sh, sh1, lg,
                lg1, lg1);
    sprintf(d, "%d %d %d %hd %hd %ld %ld %10ld", n, n1, n2, sh, sh1, lg, lg1,
            lg1);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%10d %+3d %+010d %+-10d %+-10d % -10d %-10d %-10d", n,
                212121, 2121, n2, n, 21, 55, -55);
    sprintf(d, "%10d %+3d %+010d %+-10d %+-10d % -10d %-10d %-10d", n, 212121,
            2121, n2, n, 21, 55, -55);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%-10d %010d %010d %*d %2d", 21, n2, n, 10, n, n2);
    sprintf(d, "%-10d %010d %010d %*d %2d", 21, n2, n, 10, n, n2);
    ck_assert_str_eq(c, d);
    s21_sprintf(
        c, "[%.*d] [%3.10d] [%.d] [%-+.5d] [%-+10.5d] [%.10d] [%.10d] [%2.2d] [%.d] [% d] [%.0d]", 10,
        n, n2, 42, 21, 10, n, n2, -21, x1, 21, -42);
    sprintf(d, "[%.*d] [%3.10d] [%.d] [%-+.5d] [%-+10.5d] [%.10d] [%.10d] [%2.2d] [%.d] [% d] [%.0d]",
            10, n, n2, 42, 21, 10, n, n2, -21, x1, 21, -42);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%d %d %d %d %d %ld %ld", INT_MIN, INT_MAX, SHRT_MAX,
                SHRT_MIN, USHRT_MAX, LONG_MAX, LONG_MIN);
    sprintf(d, "%d %d %d %d %d %ld %ld", INT_MIN, INT_MAX, SHRT_MAX, SHRT_MIN,
            USHRT_MAX, LONG_MAX, LONG_MIN);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%c %10c %-10c %5lc %-5lc", '!', 'a', 'b', wch1, wch2);
    sprintf(d, "%c %10c %-10c %5lc %-5lc", '!', 'a', 'b', wch1, wch2);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%c %c %c", CHAR_MAX, CHAR_MIN, UCHAR_MAX);
    sprintf(d, "%c %c %c", CHAR_MAX, CHAR_MIN, UCHAR_MAX);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%s %10s %-10s %-3s %.s %.3s %.10s", "hello", "hello",
                "hello", "hello", "hello", "hello", "hello");
    sprintf(d, "%s %10s %-10s %-3s %.s %.3s %.10s", "hello", "hello", "hello",
            "hello", "hello", "hello", "hello");
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%ls %10ls %-10ls %-3ls %.ls %.3ls %.10ls", L"hello",
                L"hello", L"hello", L"hello", L"hello", L"hello", L"hello");
    sprintf(d, "%ls %10ls %-10ls %-3ls %.ls %.3ls %.10ls", L"hello", L"hello",
            L"hello", L"hello", L"hello", L"hello", L"hello");
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%u %lu", UINT_MAX, ULONG_MAX);
    sprintf(d, "%u %lu", UINT_MAX, ULONG_MAX);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "hello %n", &n);
    sprintf(d, "hello %n", &n1);
    ck_assert_msg(c, d, "error");
    s21_sprintf(c, "[%-10o] [%lo] [%lo] [%o] [%o] [%o] [%10o] [%#10o] [%0#10o]", 21, lg, lg1, n,
                0, n2, 0, 21, 42);
    sprintf(d, "[%-10o] [%lo] [%lo] [%o] [%o] [%o] [%10o] [%#10o] [%0#10o]", 21, lg, lg1, n, 0,
            n2, 0, 21, 42);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "[%#o] [%#o] [%#10o] [%0#10o] [%.10o] [%.0o] [%#5.10o]", n, n2, 0, 0, n, 0,
                123);
    sprintf(d, "[%#o] [%#o] [%#10o] [%0#10o] [%.10o] [%.0o] [%#5.10o]", n, n2, 0, 0, n, 0,
            123);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%x %x %x %10x %-10x %.10x %.0x %#5.10x", n, n1, n2, 0, 21,
                n, 0, 123);
    sprintf(d, "%x %x %x %10x %-10x %.10x %.0x %#5.10x", n, n1, n2, 0, 21, n, 0,
            123);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "[%#x] [%#x] [%#5x] [%#2x] [%-#5x] [%0#7x] [%0#10x] [%-10.5x] [%lx] [%lx]",
                n, n2, 21, 0, 42, 21, 0, -65, lg, lg1);
    sprintf(d, "[%#x] [%#x] [%#5x] [%#2x] [%-#5x] [%0#7x] [%0#10x] [%-10.5x] [%lx] [%lx]", n,
            n2, 21, 0, 42, 21, 0, -65, lg, lg1);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%X %X %X %10X %-10X %lX", n, n1, n2, 0, 21, lg1);
    sprintf(d, "%X %X %X %10X %-10X %lX", n, n1, n2, 0, 21, lg1);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%#X %#X %-#10X %#10X %#10X %0#10X %0#10X", n, n2, 21, 42, 0,
                4221, n1);
    sprintf(d, "%#X %#X %-#10X %#10X %#10X %0#10X %0#10X", n, n2, 21, 42, 0,
            4221, n1);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%+.1f %.2f %.3f %.4f %10.5f %10.5f %-10.3f %-10.2f", f, f1,
                21.21, -21.21, 42.42, -42.42, f, f1);
    sprintf(d, "%+.1f %.2f %.3f %.4f %10.5f %10.5f %-10.3f %-10.2f", f, f1,
            21.21, -21.21, 42.42, -42.42, f, f1);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "[% 10f] [% 10f] [%f] [%.0f] [%.0f] [%#.0f] [%.0f] [%f] [%010f]", f, f1, 21.,
                21.21, 0.0, 21.21, 21., 0.0, 21.21);
    sprintf(d, "[% 10f] [% 10f] [%f] [%.0f] [%.0f] [%#.0f] [%.0f] [%f] [%010f]", f, f1, 21.,
            21.21, 0.0, 21.21, 21., 0.0, 21.21);
    ck_assert_str_eq(c, d);
    ck_assert_int_eq(
        s21_sprintf(c, "% 10f % 10f %f %.0f %.0f %#.0f %.0f %f %010f", f, f1,
                    21., 21.21, 0.0, 21.21, 21., 0.0, 21.21),
        sprintf(d, "% 10f % 10f %f %.0f %.0f %#.0f %.0f %f %010f", f, f1, 21.,
                21.21, 0.0, 21.21, 21., 0.0, 21.21));
    ck_assert_int_eq(
        s21_sprintf(c,
                    "%#x %#x %#10x %#10x %-#10x %0#10x %0#10x %-10.5x %lx %lx",
                    n, n2, 21, 0, 42, 21, 0, -65, lg, lg1),
        sprintf(d, "%#x %#x %#10x %#10x %-#10x %0#10x %0#10x %-10.5x %lx %lx",
                n, n2, 21, 0, 42, 21, 0, -65, lg, lg1));
}
END_TEST

START_TEST(s21_sprintf_test1) {
    char str1[1000];
    char str2[1000];

    void *p = 0x0;
    unsigned int n1 = 0, n2 = 0;
    r1 =
        sprintf(str1, "%p%d%o%s%c%i%e%f%f%g%u%x%G%X%%%n%s", p, 25, 342, "aboba",
                'a', 123, 25.34, 4325.23434, 0.0000000123, 2.12345, 12345u,
                8342, 0.0000456, 1235, &n1, "hello my friend");
    r2 =
        s21_sprintf(str2, "%p%d%o%s%c%i%e%f%f%g%u%x%G%X%%%n%s", p, 25, 342, "aboba",
                'a', 123, 25.34, 4325.23434, 0.0000000123, 2.12345, 12345u,
                8342, 0.0000456, 1235, &n2, "hello my friend");
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(n1, n2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test2) {
    char str1[1000];
    char str2[1000];
    r1 = sprintf(str1, "%+-25.3d%25.15o%#10.f%015d", 252, 243, 256.34, 15);
    r2 =
        s21_sprintf(str2, "%+-25.3d%25.15o%#10.f%015d", 252, 243, 256.34, 15);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test3) {
    char str1[100];
    char str2[100];
    r1 = sprintf(str1, "%#+34.10g%#.10x%#15.1o%25.10s", 25.3456, 1234, 4567,
                     "HELLOMYDEARFRIEND");
    r2 = s21_sprintf(str2, "%#+34.10g%#.10x%#15.1o%25.10s", 25.3456, 1234,
                         4567, "HELLOMYDEARFRIEND");
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test4) {
    char str1[100];
    char str2[100];
    void *p = (void *)43252342;
    r1 = sprintf(str1, "%#24.f%-15.20i%20p%020u", 43253242.4342, 4567899, p,
                     43252342u);
    r2 = s21_sprintf(str2, "%#24.f%-15.20i%20p%020u", 43253242.4342,
                         4567899, p, 43252342u);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
    char str3[50];
    char str4[100];
    int r3 = sprintf(str3, "%*.0f", 25, 25432.34345);
    int r4 = s21_sprintf(str4, "%*.0f", 25, 25432.34345);
    ck_assert_str_eq(str3, str4);
    ck_assert_int_eq(r3, r4);
}
END_TEST

START_TEST(s21_sprintf_test_d) {
    char str1[1000];
    char str2[1000];
    short h = 34;
    r1 = sprintf(
        str1, "%-25.10d%-30.2d%10.12d%11d%*d%*.*d%+-25.*d%+10.2ld%-11.*hd", 253,
        335, 1234, 34, 10, 25, 5, 15, 345, 5, 666, 456789l, 5, h);
    r2 = s21_sprintf(
        str2, "%-25.10d%-30.2d%10.12d%11d%*d%*.*d%+-25.*d%+10.2ld%-11.*hd", 253,
        335, 1234, 34, 10, 25, 5, 15, 345, 5, 666, 456789l, 5, h);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_i) {
    char str1[1000];
    char str2[1000];
    short h = 34;
    long l = 2353423523424;
    r1 =
        sprintf(str1, "%+50.i%-10.20i%10.i%012i%*.*i%-10.*i%+10.1li%*.25hi",
                34567, 225, 5230, 125, 10, 5, 456, 10, 377, l, 12, h);
    r2 =
        s21_sprintf(str2, "%+50.i%-10.20i%10.i%012i%*.*i%-10.*i%+10.1li%*.25hi",
                    34567, 225, 5230, 125, 10, 5, 456, 10, 377, l, 12, h);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_c) {
    char str1[1000];
    char str2[1000];
    wchar_t c1 = 'T', c2 = 'Z';
    r1 = sprintf(str1, "%10c%-10c%25c%-30c%25c%*c%2c%*c%lc%-50lc", 'a', 'e',
                     'f', 'R', 'Q', 10, 'P', 'L', 20, 'x', c1, c2);
    r2 = s21_sprintf(str2, "%10c%-10c%25c%-30c%25c%*c%2c%*c%lc%-50lc", 'a',
                         'e', 'f', 'R', 'Q', 10, 'P', 'L', 20, 'x', c1, c2);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_e) {
    char str1[1000];
    char str2[1000];
    r1 =
        sprintf(str1, "%+-20e%010.*e%-*.10Le%#025.7e%*.*e%*.9e%#010.*e%25.15e",
                2543.43254, 10, 1012.34567, 15, (long double)-0.00456, 45678.342532, 10, 15,
                11111.22, 16, -3245.3425342, 10, -0.00123, 235423424.43252);
    r2 = s21_sprintf(
        str2, "%+-20e%010.*e%-*.10Le%#025.7e%*.*e%*.9e%#010.*e%25.15e",
        2543.43254, 10, 1012.34567, 15, (long double)-0.00456, 45678.342532, 10, 15,
        11111.22, 16, -3245.3425342, 10, -0.00123, 235423424.43252);    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_E) {
    char str1[1000];
    char str2[1000];
    r1 = sprintf(str1, "%+-25.4E%25.*E%-*.10LE%#02.E%*.*E%*.15E%*E%12.10E",
                     3456.4325, 8, 23452.43242, 5, (long double)-0.05267, 25.432523432, 10,
                     2, 53242.4242, 10, 456789.43242, 25, 1111122222.34567899,
                     2345678.23453242);
    r2 = s21_sprintf(
        str2, "%+-25.4E%25.*E%-*.10LE%#02.E%*.*E%*.15E%*E%12.10E", 3456.4325, 8,
        23452.43242, 5, (long double)-0.05267, 25.432523432, 10, 2, 53242.4242, 10,
        456789.43242, 25, 1111122222.34567899, 2345678.23453242);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_f) {
    char str1[1000];
    char str2[1000];
    r1 = sprintf(
        str1,
        "%+-10.3f%+10.2f%15.10Lf%+*.6f%*.10f%-10.*f%25.*f%25.f%#+10.f%*.*f",
        2546.4324, 3452.4325, (long double)5678.43256, 25, 456789.243242, 10,
        3456789123.43245, 2, 12345.6788, 1, 34.4325432, 4325678.43242,
        34567.2345432, 10, 2, 34567.43244);
    r2 = s21_sprintf(
        str2,
        "%+-10.3f%+10.2f%15.10Lf%+*.6f%*.10f%-10.*f%25.*f%25.f%#+10.f%*.*f",
        2546.4324, 3452.4325, (long double)5678.43256, 25, 456789.243242, 10,
        3456789123.43245, 2, 12345.6788, 1, 34.4325432, 4325678.43242,
        34567.2345432, 10, 2, 34567.43244);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_o) {
    char str1[1000];
    char str2[1000];
    unsigned short h = 253;
    unsigned long l = 4325234324242l;
    r1 =
        sprintf(str1, "%-25.10o%-10o%#-30.2o%#*.10o%#*.*o%25.*o%#.10ho%*lo",
                12345, 6532, 43522, 10, 64342, 15, 2, 343, 6, 678, h, 10, l);
    r2 = s21_sprintf(
        str2, "%-25.10o%-10o%#-30.2o%#*.10o%#*.*o%25.*o%#.10ho%*lo", 12345,
        6532, 43522, 10, 64342, 15, 2, 343, 6, 678, h, 10, l);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_x) {
    char str1[1000];
    char str2[1000];
    unsigned short h = 345;
    unsigned long l = 52342353242l;
    r1 =
        sprintf(str1,
                "%x%-25x%#10x%#-10x%#10.5x%-25.34x%#-10.2x%*.*x%#*.10x%20.*"
                "x%#10.*x%*.5hx%10.25lx",
                235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15, 3452, 8,
                23452, 10, 34254, 3, 33334, 10, h, l);
    r2 =
        s21_sprintf(str2,
                    "%x%-25x%#10x%#-10x%#10.5x%-25.34x%#-10.2x%*.*x%#*.10x%"
                    "20.*x%#10.*x%*.5hx%10.25lx",
                    235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15, 3452,
                    8, 23452, 10, 34254, 3, 33334, 10, h, l);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_X) {
    char str1[1000];
    char str2[1000];
    unsigned short h = 234;
    unsigned long l = 4325243132l;
    r1 =
        sprintf(str1,
                "%hX%-10X%15X%#-15X%#20.3X%-30.12X%#-12.3X%*.*X%#*.15X%21.*X%"
                "#12.*X%*.8hx%14.12lX",
                (unsigned short)235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15, 3452, 8,
                23452, 10, 34254, 3, 33334, 10, h, l);
    r2 = s21_sprintf(str2,
                         "%hX%-10X%15X%#-15X%#20.3X%-30.12X%#-12.3X%*.*X%#*.15X%"
                         "21.*X%#12.*X%*.8hx%14.12lX",
                         (unsigned short)235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15,
                         3452, 8, 23452, 10, 34254, 3, 33334, 10, h, l);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_u) {
    char str1[1000];
    char str2[1000];
    unsigned short h = 115;
    unsigned long l = 123325242342l;
    r1 =
        sprintf(str1, "%u%15u%-20u%010u%-15.10u%20.*u%*.*u%*.10u%-20.12lu%19hu",
                4321u, 34567u, 2342u, 12346u, 234542u, 10, 234523u, 10, 5,
                2345u, 20, 2432u, l, h);
    r2 = s21_sprintf(
        str2, "%u%15u%-20u%010u%-15.10u%20.*u%*.*u%*.10u%-20.12lu%19hu", 4321u,
        34567u, 2342u, 12346u, 234542u, 10, 234523u, 10, 5, 2345u, 20, 2432u, l,
        h);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_s) {
    char str1[1000];
    char str2[1000];
    wchar_t s[10] = {'h', 'e', 'l', 'l', 'o'};
    r1 = sprintf(str1, "%s%23s%-15s%10.s%15.2s%16.*s%*.*s%*s%15ls%15.3ls",
                     "aboba", "helloworld", "ABOBA", "ABOBBAAA", "AAABOBA", 10,
                     "QWERTY", 15, 4, "AAAAABOOOOOBAAA", 10, "ABOBAAAAA", s, s);
    r2 =
        s21_sprintf(str2, "%s%23s%-15s%10.s%15.2s%16.*s%*.*s%*s%15ls%15.3ls",
                    "aboba", "helloworld", "ABOBA", "ABOBBAAA", "AAABOBA", 10,
                    "QWERTY", 15, 4, "AAAAABOOOOOBAAA", 10, "ABOBAAAAA", s, s);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_p) {
    char str1[1000];
    char str2[1000];
    void *p1 = (void *)0x123456789;
    void *p2 = (void *)4325234;
    void *p3 = (void *)0x123f324b;
    void *p4 = (void *)432520;
    r1 = sprintf(str1, "%p%20p%-15p%10p%-15p%*p%10p%*p", p1, p2, p3, p4, p2,
                     10, p3, p1, 10, p4);
    r2 = s21_sprintf(str2, "%p%20p%-15p%10p%-15p%*p%10p%*p", p1, p2, p3, p4,
                         p2, 10, p3, p1, 10, p4);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_percent) {
    char str1[1000];
    char str2[1000];
    r1 = sprintf(str1, "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
    r2 = s21_sprintf(str2, "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_g) {
    char str1[1000];
    char str2[1000];
    r1 = sprintf(
        str1, "%g%23g%-10g%015g%#10.5g%0#15.10Lg%+10.6g%#*.g%-10.*g%+#25.8g",
        2345.4325674, 23445.2378, 1234.23424862, 3456.3674765, 0.000015688, (long double)-324234.2384,
        2345.423764, 5, 23456.4357, 9, 234567.4367297, 0.00000834);
    r2 = s21_sprintf(
        str2, "%g%23g%-10g%015g%#10.5g%0#15.10Lg%+10.6g%#*.g%-10.*g%+#25.8g",
        2345.4325674, 23445.2378, 1234.23424862, 3456.3674765, 0.000015688, (long double)-324234.2384,
        2345.423764, 5, 23456.4357, 9, 234567.4367297, 0.00000834);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_G) {
    char str1[1000];
    char str2[1000];
    r1 = sprintf(
        str1,
        "%G%25G%#-15G%017G%#05.2G%#010.16LG%+#8.6G%*.8G%#-10.*G%+#12.16G%*.*G",
        43242.432567, 123432.43658, 0000.7865, -34252.432667, 1234.56,
        (long double)111.43253448768665, 4324.4395, 25, -3213.43567, 16,
        -43.432423534768, 111.243253646, 25, 5, 0.0000003567);
    r2 = s21_sprintf(
        str2,
        "%G%25G%#-15G%017G%#05.2G%#010.16LG%+#8.6G%*.8G%#-10.*G%+#12.16G%*.*G",
        43242.432567, 123432.43658, 0000.7865, -34252.432667, 1234.56,
        (long double)111.43253448768665, 4324.4395, 25, -3213.43567, 16,
        -43.432423534768, 111.243253646, 25, 5, 0.0000003567);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(test_s21_to_upper) {
    char *res = s21_to_upper("test");
    ck_assert_str_eq(res, "TEST");
    if (res)
        free(res);

    res = s21_to_upper(" t e s t");
    ck_assert_str_eq(res, " T E S T");
    if (res)
        free(res);

    res = s21_to_upper("test001");
    ck_assert_str_eq(res, "TEST001");
    if (res)
        free(res);

    res = s21_to_upper("!test!");
    ck_assert_str_eq(res, "!TEST!");
    if (res)
        free(res);

    res = s21_to_upper(" ");
    ck_assert_str_eq(res, " ");
    if (res)
        free(res);

    res = s21_to_upper("!*_*!");
    ck_assert_str_eq(res, "!*_*!");
    if (res)
        free(res);
}
END_TEST

START_TEST(test_s21_to_lower) {
    char *res = s21_to_lower("TEST");
    ck_assert_str_eq(res, "test");
    if (res)
        free(res);

    res = s21_to_lower(" T E S T");
    ck_assert_str_eq(res, " t e s t");
    if (res)
        free(res);

    res = s21_to_lower("TEST001");
    ck_assert_str_eq(res, "test001");
    if (res)
        free(res);

    res = s21_to_lower("!TEST!");
    ck_assert_str_eq(res, "!test!");
    if (res)
        free(res);

    res = s21_to_lower(" ");
    ck_assert_str_eq(res, " ");
    if (res)
        free(res);

    res = s21_to_lower("!*_*!");
    ck_assert_str_eq(res, "!*_*!");
    if (res)
        free(res);
}
END_TEST

START_TEST(test_s21_insert) {
    char *str1 = "Test";
    char *str2 = "quest";
    char *res = NULL;

    res = s21_insert(str1, str2, 2);
    ck_assert_str_eq(res, "Tequestst");
    if (res)
        free(res);

    str1 = "The test";
    str2 = " perfect";
    res = s21_insert(str1, str2, 3);
    ck_assert_str_eq(res, "The perfect test");
    if (res)
        free(res);

    str1 = "Insert in";
    str2 = " end";
    res = s21_insert(str1, str2, 9);
    ck_assert_str_eq(res, "Insert in end");
    if (res)
        free(res);

    str1 = " with insert";
    str2 = "Start";
    res = s21_insert(str1, str2, 0);
    ck_assert_str_eq(res, "Start with insert");
    if (res)
        free(res);

    str1 = "Newspace";
    str2 = " ";
    res = s21_insert(str1, str2, 3);
    ck_assert_str_eq(res, "New space");
    if (res)
        free(res);

    str1 = "";
    str2 = " ";
    res = s21_insert(str1, str2, 0);
    ck_assert_str_eq(res, " ");
    if (res)
        free(res);
}
END_TEST

START_TEST(test_s21_trim) {
    char *res = s21_trim("testc", "c");
    ck_assert_str_eq(res, "test");
    if (res)
        free(res);

    res = s21_trim(" test ", " ");
    ck_assert_str_eq(res, "test");
    if (res)
        free(res);

    res = s21_trim(" ", " ");
    ck_assert_str_eq(res, "");
    if (res)
        free(res);

    res = s21_trim("*te*st*", "*");
    ck_assert_str_eq(res, "te*st");
    if (res)
        free(res);

    res = s21_trim(" te st001", " ");
    ck_assert_str_eq(res, "te st001");
    if (res)
        free(res);

    res = s21_trim(" /*()", ")(/ *");
    ck_assert_str_eq(res, "");
    if (res)
        free(res);
}
END_TEST

char *empty_str = "";

START_TEST(sscanf_test_c) {
char c1, c2;
char *str1 = " abc ";
r1 = sscanf(str1, "%*c%*c%c", &c1);
r2 = s21_sscanf(str1, "%*c%*c%c", &c2);
ck_assert_int_eq(r1, r2);
ck_assert_int_eq(c1, c2);
r1 = sscanf(empty_str, "%c", &c1);
r2 = s21_sscanf(empty_str, "%c", &c2);
ck_assert_int_eq(r1, r2);
ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_test_d) {
int nmb1 = 111, nmb2 = 111;
char *str2 = "  123   -123   567  32368  ";
char wrong_str2[] = " abc 123 ";
r1 = sscanf(str2, "%*d%d%*d%*d", &nmb1);
r2 = s21_sscanf(str2, "%*d%d%*d%*d", &nmb2);
ck_assert_int_eq(nmb1, nmb2);
ck_assert_int_eq(r1, r2);

r1 = sscanf(empty_str, "%d", &nmb1);
r2 = s21_sscanf(empty_str, "%d", &nmb2);
ck_assert_int_eq(nmb1, nmb2);
ck_assert_int_eq(r1, r2);

r1 = sscanf(wrong_str2, "%d", &nmb1);
r2 = s21_sscanf(wrong_str2, "%d", &nmb2);
ck_assert_int_eq(nmb1, nmb2);
ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_test_i) {
int nmbX1 = 1, nmbX2 = 1, nmbO1 = 1, nmbO2 = 1;
int nmbD1 = 1, nmbD2 = 1;
char *str3 = "  0x3F5  0600 -12345 987";
char *wrong_str3 = "  0000xFF5  ";
r1 = sscanf(str3, "%i%i%i%*i", &nmbX1, &nmbO1, &nmbD1);
r2 = s21_sscanf(str3, "%i%i%i%*i", &nmbX2, &nmbO2, &nmbD2);
ck_assert_int_eq(nmbX1, nmbX2);
ck_assert_int_eq(nmbO1, nmbO2);
ck_assert_int_eq(nmbD1, nmbD2);
ck_assert_int_eq(r1, r2);

r1 = sscanf(empty_str, "%i", &nmbD1);
r2 = s21_sscanf(empty_str, "%i", &nmbD2);
ck_assert_int_eq(nmbD1, nmbD2);
ck_assert_int_eq(r1, r2);

r1 = sscanf(wrong_str3, "%i", &nmbX1);
r2 = s21_sscanf(wrong_str3, "%i", &nmbX2);
ck_assert_uint_eq(nmbX1, nmbX2);
ck_assert_int_eq(r1, r2);
unsigned int octnmb1 = 1, octnmb2 = 2;
r1 = sscanf(str3, "%*x%o", &octnmb1);
r2 = s21_sscanf(str3, "%*x%o", &octnmb2);
ck_assert_uint_eq(octnmb1, octnmb2);
ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_test_u) {
unsigned u1 = 1, u2 = 2;
char *str4 = " 0    3147483647";
char *wrong_str4 = "  Verter_Hi123456";
r1 = sscanf(str4, "%*u%u", &u1);
r2 = s21_sscanf(str4, "%*u%u", &u2);
ck_assert_uint_eq(u1, u2);
ck_assert_int_eq(r1, r2);

r1 = sscanf(empty_str, "%u", &u1);
r2 = s21_sscanf(empty_str, "%u", &u2);
ck_assert_int_eq(u1, u2);
ck_assert_int_eq(r1, r2);

r1 = sscanf(wrong_str4, "%u", &u1);
r2 = s21_sscanf(wrong_str4, "%u", &u2);
ck_assert_uint_eq(u1, u2);
ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_test_x) {
unsigned u1 = 1, u2 = 2, u3 = 3, u4 = 4;
char *str4 = " 123123  3147487 123 123";
r1 = sscanf(str4, "%*x%x%X%*X", &u1, &u3);
r2 = s21_sscanf(str4, "%*x%x%X%*X", &u2, &u4);
ck_assert_uint_eq(u1, u2);
ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_test_double) {
double fl1 = 1, fl2 = 2;
double dbl1 = 1, dbl2 = 2;
char *str5 = "  -876.214235  2145.93560734567  324.21427 ";
char *wrong_str5 = "  Verter_Kek35634.34";
r1 = sscanf(str5, "%lf%lf%*f", &fl1, &dbl1);
r2 = s21_sscanf(str5, "%lf%lf%*f", &fl2, &dbl2);
ck_assert_msg(dbl1 == dbl2, "Float test 1 fail");
ck_assert_msg(fl1 == fl2, "Float test 2 fail");
ck_assert_int_eq(r1, r2);

r1 = sscanf(empty_str, "%lf", &dbl1);
r2 = s21_sscanf(empty_str, "%lf", &dbl2);
ck_assert_msg(dbl1 == dbl2, "Float test 3 fail");
ck_assert_int_eq(r1, r2);

r1 = sscanf(wrong_str5, "%lf", &dbl1);
r2 = s21_sscanf(wrong_str5, "%lf", &dbl2);
ck_assert_msg(dbl1 == dbl2, "Float test 4 fail");
ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_test_EeGg) {
double e1, e2, g1, g2;
char *str6_l = "  0.000000000123e+04  543214221.0e-11 0.0";
char *str6_u = "  0.08762147E+03  1446567457.024E-11 0E+02";
char *wrong_str6 = "  Verter?35634E+02";
r1 = sscanf(str6_l, "%le%lg%*E", &e1, &g1);
r2 = s21_sscanf(str6_l, "%le%lg%*E", &e2, &g2);
ck_assert_msg(e1 == e2, "Float test 5 fail");
ck_assert_msg(g1 == g2, "Float test 6 fail");
ck_assert_int_eq(r1, r2);
r1 = sscanf(str6_u, "%lE%lG%*e", &e1, &g1);
r2 = s21_sscanf(str6_u, "%lE%lG%*e", &e2, &g2);
ck_assert_int_eq(e1, e2);
ck_assert_int_eq(g1,  g2);
ck_assert_int_eq(r1, r2);

r1 = sscanf(empty_str, "%le", &e1);
r2 = s21_sscanf(empty_str, "%le", &e2);
ck_assert_int_eq(e1, e2);
ck_assert_int_eq(r1, r2);

r1 = sscanf(wrong_str6, "%lg", &g1);
r2 = s21_sscanf(wrong_str6, "%lg", &g2);
ck_assert_int_eq(g1,  g2);
ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_test_s) {
    char str_var1[30] = "", str_var2[30] = "";
    r1 = sscanf(" this is random string", "%*s%*s%10s%*s", str_var1);
    r2 = s21_sscanf(" this is random string", "%*s%*s%s%*s", str_var2);
    ck_assert_str_eq(str_var1, str_var2);
    ck_assert_int_eq(r1, r2);
    r1 = sscanf("\0", "%10s", str_var1);
    r2 = s21_sscanf("\0", "%s", str_var2);
    ck_assert_str_eq(str_var1, str_var2);
    ck_assert_int_eq(r1, r2);
}

START_TEST(sscanf_test_ld) {
long nm1 = 111, nm2 = 111;
char *str5 = "  123   -5123123123   567  588  ";
char wrong_str5[] = " abc 123 ";
r1 = sscanf(str5, "%*d%ld%*d%*d", &nm1);
r2 = s21_sscanf(str5, "%*d%ld%*d%*d", &nm2);
ck_assert_int_eq(nm1, nm2);
ck_assert_int_eq(r1, r2);
r1 = sscanf(empty_str, "%ld", &nm1);
r2 = s21_sscanf(empty_str, "%ld", &nm2);
ck_assert_int_eq(nm1, nm2);
ck_assert_int_eq(r1, r2);
r1 = sscanf(wrong_str5, "%ld", &nm1);
r2 = s21_sscanf(wrong_str5, "%ld", &nm2);
ck_assert_int_eq(nm1, nm2);
ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_test_hd) {
short nh1 = 111, nh2 = 111;
char *str6 = "  123   -5123123123   567  588  ";
char wrong_str6[] = " abc 123 ";
r1 = sscanf(str6, "%*d%hd%*d%*d", &nh1);
r2 = s21_sscanf(str6, "%*d%hd%*d%*d", &nh2);
ck_assert_int_eq(nh1, nh2);
ck_assert_int_eq(r1, r2);
r1 = sscanf(empty_str, "%hd", &nh1);
r2 = s21_sscanf(empty_str, "%hd", &nh2);
ck_assert_int_eq(nh1, nh2);
ck_assert_int_eq(r1, r2);
r1 = sscanf(wrong_str6, "%hd", &nh1);
r2 = s21_sscanf(wrong_str6, "%hd", &nh2);
ck_assert_int_eq(nh1, nh2);
ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_test_lu) {
unsigned long nu1 = 111, nu2 = 111;
char *str7 = "  123   5123123123   567  588  ";
char wrong_str7[] = " abc 123 ";
r1 = sscanf(str7, "%*d%lu%*d%*d", &nu1);
r2 = s21_sscanf(str7, "%*d%lu%*d%*d", &nu2);
ck_assert_int_eq(nu1, nu2);
ck_assert_int_eq(r1, r2);
r1 = sscanf(empty_str, "%lu", &nu1);
r2 = s21_sscanf(empty_str, "%lu", &nu2);
ck_assert_int_eq(nu1, nu2);
ck_assert_int_eq(r1, r2);
r1 = sscanf(wrong_str7, "%lu", &nu1);
r2 = s21_sscanf(wrong_str7, "%lu", &nu2);
ck_assert_int_eq(nu1, nu2);
ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_test_hu) {
unsigned short nuh1 = 111, nuh2 = 111;
char *str5 = "  123   15000   567  588  ";
char wrong_str5[] = " abc 123 ";
r1 = sscanf(str5, "%*d%hu%*d%*d", &nuh1);
r2 = s21_sscanf(str5, "%*d%hu%*d%*d", &nuh2);
ck_assert_int_eq(nuh1, nuh2);
ck_assert_int_eq(r1, r2);
r1 = sscanf(empty_str, "%hu", &nuh1);
r2 = s21_sscanf(empty_str, "%hu", &nuh2);
ck_assert_int_eq(nuh1, nuh2);
ck_assert_int_eq(r1, r2);
r1 = sscanf(wrong_str5, "%hu", &nuh1);
r2 = s21_sscanf(wrong_str5, "%hu", &nuh2);
ck_assert_int_eq(nuh1, nuh2);
ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_test_ptr) {
unsigned long p1 = 111, p2 = 111;
unsigned long *ptr1 = &p1, *ptr11 = &p1, *ptr2 = &p2, *ptr22 = &p2;
char *str8 = "  123   5123123123   0x567  588  ";
char wrong_str8[] = " abc 123 ";
r1 = sscanf(str8, "%*d%p%p%*p", &ptr1, &ptr11);
r2 = s21_sscanf(str8, "%*d%p%p%*p", &ptr2, &ptr22);
ck_assert_ptr_eq(ptr1, ptr2);
ck_assert_ptr_eq(ptr11, ptr22);
ck_assert_int_eq(r1, r2);
r1 = sscanf(empty_str, "%p", &ptr1);
r2 = s21_sscanf(empty_str, "%p", &ptr2);
ck_assert_ptr_eq(ptr1, ptr2);
ck_assert_int_eq(r1, r2);
r1 = sscanf(wrong_str8, "%p", &ptr1);
r2 = s21_sscanf(wrong_str8, "%p", &ptr2);
ck_assert_ptr_eq(ptr1, ptr2);
ck_assert_int_eq(r1, r2);
}
END_TEST

int main() {
    Suite *suite = suite_create("S21_Debuger");
    SRunner *srunner = srunner_create(suite);

    TCase *s21_memchrCase = tcase_create("s21_memchrCase");
    suite_add_tcase(suite, s21_memchrCase);
    tcase_add_test(s21_memchrCase, test_s21_memchr);

    TCase *s21_memcmpCase = tcase_create("s21_memcmpCase");
    suite_add_tcase(suite, s21_memcmpCase);
    tcase_add_test(s21_memcmpCase, test_s21_memcmp);

    TCase *s21_memcpyCase = tcase_create("s21_memcpyCase");
    suite_add_tcase(suite, s21_memcpyCase);
    tcase_add_test(s21_memcpyCase, test_s21_memcpy);

    TCase *s21_memmoveCase = tcase_create("s21_memmoveCase");
    suite_add_tcase(suite, s21_memmoveCase);
    tcase_add_test(s21_memmoveCase, test_s21_memmove);

    TCase *s21_memsetCase = tcase_create("s21_memsetCase");
    suite_add_tcase(suite, s21_memsetCase);
    tcase_add_test(s21_memsetCase, test_s21_memset);

    TCase *s21_strcatCase = tcase_create("s21_strcatCase");
    suite_add_tcase(suite, s21_strcatCase);
    tcase_add_test(s21_strcatCase, test_s21_strcat);

    TCase *s21_strncatCase = tcase_create("s21_strncatCase");
    suite_add_tcase(suite, s21_strncatCase);
    tcase_add_test(s21_strncatCase, test_s21_strncat);

    TCase *s21_strchrCase = tcase_create("s21_strchrCase");
    suite_add_tcase(suite, s21_strchrCase);
    tcase_add_test(s21_strchrCase, test_s21_strchr);

    TCase *s21_strcmpCase = tcase_create("s21_strcmpCase");
    suite_add_tcase(suite, s21_strcmpCase);
    tcase_add_test(s21_strcmpCase, test_s21_strcmp);

    TCase *s21_strncmpCase = tcase_create("s21_strncmpCase");
    suite_add_tcase(suite, s21_strncmpCase);
    tcase_add_test(s21_strncmpCase, test_s21_strncmp);

    TCase *s21_strcpyCase = tcase_create("s21_strcpyCase");
    suite_add_tcase(suite, s21_strcpyCase);
    tcase_add_test(s21_strcpyCase, test_s21_strcpy);

    TCase *s21_strncpyCase = tcase_create("s21_strncpyCase");
    suite_add_tcase(suite, s21_strncpyCase);
    tcase_add_test(s21_strncpyCase, test_s21_strncpy);

    TCase *s21_strcspnCase = tcase_create("s21_strcspnCase");
    suite_add_tcase(suite, s21_strcspnCase);
    tcase_add_test(s21_strcspnCase, test_s21_strcspn);

    TCase *s21_strerrorCase = tcase_create("s21_strerrorCase");
    suite_add_tcase(suite, s21_strerrorCase);
    tcase_add_test(s21_strerrorCase, test_s21_strerror);

    TCase *s21_strlenCase = tcase_create("s21_strlenCase");
    suite_add_tcase(suite, s21_strlenCase);
    tcase_add_test(s21_strlenCase, test_s21_strlen);

    TCase *s21_strpbrkCase = tcase_create("s21_strpbrkCase");
    suite_add_tcase(suite, s21_strpbrkCase);
    tcase_add_test(s21_strpbrkCase, test_s21_strpbrk);

    TCase *s21_strrchrCase = tcase_create("s21_strrchrCase");
    suite_add_tcase(suite, s21_strrchrCase);
    tcase_add_test(s21_strrchrCase, test_s21_strrchr);

    TCase *s21_strspnCase = tcase_create("s21_strspnCase");
    suite_add_tcase(suite, s21_strspnCase);
    tcase_add_test(s21_strspnCase, test_s21_strspn);

    TCase *s21_strstrCase = tcase_create("s21_strstrCase");
    suite_add_tcase(suite, s21_strstrCase);
    tcase_add_test(s21_strstrCase, test_s21_strstr);

    TCase *s21_strtokCase = tcase_create("s21_strtokCase");
    suite_add_tcase(suite, s21_strtokCase);
    tcase_add_test(s21_strtokCase, test_s21_strtok);

    TCase *s21_to_upperCase = tcase_create("s21_to_upperCase");
    suite_add_tcase(suite, s21_to_upperCase);
    tcase_add_test(s21_to_upperCase, test_s21_to_upper);

    TCase *s21_to_lowerCase = tcase_create("s21_to_lowerCase");
    suite_add_tcase(suite, s21_to_lowerCase);
    tcase_add_test(s21_to_lowerCase, test_s21_to_lower);

    TCase *s21_insertCase = tcase_create("s21_insertCase");
    suite_add_tcase(suite, s21_insertCase);
    tcase_add_test(s21_insertCase, test_s21_insert);

    TCase *s21_trimCase = tcase_create("s21_trimCase");
    suite_add_tcase(suite, s21_trimCase);
    tcase_add_test(s21_trimCase, test_s21_trim);

    TCase *s21_sprintfCase1 = tcase_create("s21_sprintfCase1");
    suite_add_tcase(suite, s21_sprintfCase1);
    tcase_add_test(s21_sprintfCase1, test_s21_sprintf);

    TCase *s21_sprintfCase2 = tcase_create("s21_sprintfCase2");
    suite_add_tcase(suite, s21_sprintfCase2);
    tcase_add_test(s21_sprintfCase2, s21_sprintf_test1);
    tcase_add_test(s21_sprintfCase2, s21_sprintf_test2);
    tcase_add_test(s21_sprintfCase2, s21_sprintf_test3);
    tcase_add_test(s21_sprintfCase2, s21_sprintf_test4);
    tcase_add_test(s21_sprintfCase2, s21_sprintf_test_d);
    tcase_add_test(s21_sprintfCase2, s21_sprintf_test_i);
    tcase_add_test(s21_sprintfCase2, s21_sprintf_test_c);
    tcase_add_test(s21_sprintfCase2, s21_sprintf_test_e);
    tcase_add_test(s21_sprintfCase2, s21_sprintf_test_E);
    tcase_add_test(s21_sprintfCase2, s21_sprintf_test_f);
    tcase_add_test(s21_sprintfCase2, s21_sprintf_test_o);
    tcase_add_test(s21_sprintfCase2, s21_sprintf_test_x);
    tcase_add_test(s21_sprintfCase2, s21_sprintf_test_X);
    tcase_add_test(s21_sprintfCase2, s21_sprintf_test_u);
    tcase_add_test(s21_sprintfCase2, s21_sprintf_test_s);
    tcase_add_test(s21_sprintfCase2, s21_sprintf_test_p);
    tcase_add_test(s21_sprintfCase2, s21_sprintf_test_percent);
    tcase_add_test(s21_sprintfCase2, s21_sprintf_test_g);
    tcase_add_test(s21_sprintfCase2, s21_sprintf_test_G);

    TCase *tc1_1 = tcase_create("s21_sprintfCase2");
    suite_add_tcase(suite, tc1_1);
    tcase_add_test(tc1_1, sscanf_test_c);
    tcase_add_test(tc1_1, sscanf_test_d);
    tcase_add_test(tc1_1, sscanf_test_i);
    tcase_add_test(tc1_1, sscanf_test_u);
    tcase_add_test(tc1_1, sscanf_test_double);
    tcase_add_test(tc1_1, sscanf_test_EeGg);
    tcase_add_test(tc1_1, sscanf_test_s);
    tcase_add_test(tc1_1, sscanf_test_ld);
    tcase_add_test(tc1_1, sscanf_test_hd);
    tcase_add_test(tc1_1, sscanf_test_lu);
    tcase_add_test(tc1_1, sscanf_test_hu);
    tcase_add_test(tc1_1, sscanf_test_ptr);
    tcase_add_test(tc1_1, sscanf_test_x);

    srunner_run_all(srunner, CK_VERBOSE);
    int number_failed = srunner_ntests_failed(srunner);
    srunner_free(srunner);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
