#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_
#include <ctype.h>
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <wchar.h>
#include <stdarg.h> // Подключаем заголовочный файл для работы с переменным числом аргументов


#define BUFF_SIZE 512

typedef long unsigned int s21_size_t;
typedef long unsigned s21_size_t;
#define S21_NULL ((void *)0)




void *s21_memchr(const void *str, int c, s21_size_t n); //done
int s21_memcmp(const void *str1, const void *str2, s21_size_t n); //done
void *s21_memcpy(void *dest, const void *src, s21_size_t n); //done
void *s21_memset(void *str, int c, s21_size_t n); //done
char *s21_strcat(char *dest, const char *src); //done
char *s21_strncat(char *dest, const char *src, s21_size_t n);//done
char *s21_strchr(const char *str, int c);//done
int s21_strcmp(const char *str1, const char *str2);//done
char *s21_strcpy(char *dest, const char *src); //done
s21_size_t s21_strspn(const char *str1, const char *str2);//done
char *s21_strerror(int errnum);//done
s21_size_t s21_strlen(const char *str); //done
char *s21_strpbrk(const char *str1, const char *str2);//done
char *s21_strrchr(const char *str, int c);//done
char *s21_strstr(const char *haystack, const char *needle);//done
char *s21_strtok(char *str, const char *delim);//done

typedef struct format_struct {
    int minus;
    int plus;
    int space;
    char length;
    int width;
    int zero;
    int prec;
    int isprec;
    char spec;
    int hash;
} format_t;

typedef enum token_length {
    NONE_LENGTH,
    LENGTH_SHORT,
    LENGTH_LONG,
    LENGTH_LONG_LONG,
    LENGTH_DOUBLE,
    LENGTH_LONG_DOUBLE
} token_length;

int s21_sprintf(char *str, const char *format, ...);
void s21_copy_to_buf(char *buf, const char *string, va_list p_args);
void s21_format_processing(const char *format, int *i, char *buf, va_list p_args);
void s21_format_and_buff(int *i, char *buf, va_list p_args, format_t params);
void s21_c_to_buf(const char c, format_t params, char *buf, int *i);
void s21_d_to_buf(int64_t d, format_t params, char *buf, int *i, int base);
void s21_format_flag(char *temp, format_t params, char *buf, int *i, int mode);
void s21_f_to_buf(long double f, format_t params, char *buf, int *i);
void s21_s_to_buf(va_list p_args, format_t params, char *buf, int *i);
void s21_lc_to_buf(wchar_t c1, format_t params, char *buf, int *i);
void s21_u_to_buf(uint64_t d, format_t params, char *buf, int *i, int base);
void s21_gG_to_buf(long double f, format_t params, char *buf, int *i);
void s21_remove_trailing_zeroes(char *buf, int *i);
void s21_prepend_mantiss(char *buf, int pow, char sign, int *i);
void s21_uppcase(char *str);
void s21_parse_man(format_t params, char *buf, long double val, int *i);
void s21_o_to_buf(format_t params, char *buf, int64_t val, int *i);
void s21_xX_to_buf(format_t params, char *buf, int64_t val, int *i);
int s21_check_zeroes(char *buf);
void s21_p_to_buf(format_t params, char *buf, int64_t val, int *i);

typedef struct token {
    void *address;
    token_width width;
    unsigned int width_status;
    token_length token_length;
    char buff[1024];
    char spec;
} token;

/* СТРУКТУРА:
 * флаг(плюс/минус)
 * ширина - width (число перед спецификатором)
 * точность - precision (точка)
 * длина - length ()
 * спецификатор(буква после ширины)
 */
int s21_sscanf(const char *str, const char *format, ...);
int space_check(char c);
int register_check(char c);
int check_EOF_string(const char *str_carriage);
void skip_chars_in_buffer(char **src_carriage, int *fail, token *t);
token token_parse(char **format, va_list *ap);
void format_parse_width(char **format, token *t);
void format_parse_length(char **format, token *t);
void format_parse_specifier(char **format, token *t);
void write_tokens_to_memory(char **str_carriage, token *t, int token_carriage,
                            int *result);
int parse_number_from_format(char **format);
void write_chars_to_buff(char **str_carriage, const char *c, char *buff,
                         int16_t width, int start_ind);
void write_char_to_memory(char **str_carriage, int *result, token *t);
void write_int_to_memory(char **str_carriage, int *fail_flag, int *res,
                         token *t);
void write_float_to_memory(char **str_carriage, int *result, token *t);
void write_string_to_memory(char **str_carriage, const int *fail_flag,
                            int *result, token *t);
void write_unspec_int_to_memory(char **str_carriage, int *fail_flag,
                                int *result, token *t);
void write_unsigned_to_memory(char **str_carriage, int *fail_flag, int *result,
                              token *t);
void write_8_16_to_memory(char **str_carriage, int *fail_flag, int *result,
                          token *t, int base);
void skip_spaces_in_str(char **str_carriage);
void unsigned_type_converter(token *t, unsigned long long int result,
                             int sign);
void int_type_converter(token *t, long long int result, int sign);
void float_type_converter(token *t, long double result);

/*format −  это С-строка, содержащая один или несколько следующих элементов:
 * -пробельный символ,
 * -непробельный символ
 * и спецификаторы формата.

Спецификатор формата для печатающих функций следует прототипу:
 %[флаги][ширина][.точность][длина]спецификатор.

 Спецификатор формата для сканирующих функций следует прототипу:
 %[*][ширина][длина]спецификатор.
*/


#endif  