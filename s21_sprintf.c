#include "s21_string.h"

s21_size_t s21_strlen(const char *str) {
    s21_size_t len = 0;

    if (str !=NULL) {
        for (int i = 0; str[i]; i++) {
            len++;
        }
    }
    return len;
}
void *s21_memset(void *str, int c, s21_size_t n) {
    unsigned char *b = (unsigned char *)str;
    for (s21_size_t i = 0; i < n; i += 1) {
        b[i] = c;
    }
    return str;
}
char *s21_strcat(char *dest, const char *src) {
    int destLen = s21_strlen(dest);
    int srcLen = s21_strlen(src);

    for (int i = 0; i <= srcLen; i += 1) dest[destLen + i] = src[i];

    return dest;
}

char *s21_strchr(const char *str, int c) {
    int Length = s21_strlen(str) + 1;
    char *answer = S21_NULL;

    for (int i = 0; i < Length && answer == S21_NULL; i += 1)
        if (str[i] == c) answer = (char *)str;

    return answer;
}
//------------------------------------------------------------------------

int s21_sprintf(char *buf, const char *format, ...) {
    va_list p_args;
    va_start(p_args, format);

    s21_copy_to_buf(buf, format, p_args);

    va_end(p_args);
    return s21_strlen(buf);
}

void s21_copy_to_buf(char *buf, const char *string, va_list p_args) {
    int i[2] = {0, 0};

    for (; i[0] < (int)s21_strlen(string); i[0]++, i[1]++) {
        if (string[i[0]] == '%' && string[i[0] + 1] != '%') {
            s21_format_processing(string, i, buf, p_args);
        } else if (string[i[0]] == '%' && string[i[0] + 1] == '%') {
            buf[i[1]] = string[i[0]];
        } else {
            buf[i[1]] = string[i[0]];
        }
    }

    buf[i[1]] = '\0';
}

void s21_format_processing(const char *format, int *i, char *buf, va_list p_args) {
    format_t params;

    params.minus = 0;
    params.plus = 0;
    params.space = 0;
    params.zero = 0;
    params.length = ' ';
    params.width = 0;
    params.isprec = 0;
    params.prec = 0;
    params.spec = '\0';
    params.hash = 0;

    for (; i[0] < (int)s21_strlen(format) &&
           s21_strchr("cdifsugGeExXonp", format[i[0]]) == NULL;
           i[0]++) {
        switch (format[i[0]]) {
            case '0':
                if (!params.isprec && !params.zero && !params.width) {
                    params.zero = 1;
                }
                break;
            case '+':
                params.plus = 1;
                break;
            case '-':
                params.minus = 1;
                break;
            case ' ':
                params.space = 1;
                break;
            case 'l':
                params.length = 'l';
                break;
            case 'h':
                params.length = 'h';
                break;
            case 'L':
                params.length = 'L';
                break;
            case '.':
                params.isprec = 1;
                break;
            case '#':
                params.hash = 1;
                break;
        }

        if (params.isprec && format[i[0]] == '-')
            params.prec = 0;
        else if (params.isprec && format[i[0]] == '*')
            params.prec = va_arg(p_args, int);
        else if (params.isprec && (format[i[0]] > 47 && format[i[0]] < 58)) {
            params.prec = params.prec * 10 + format[i[0]] - 48;

        } else if (format[i[0]] > 47 && format[i[0]] < 58) {
            params.width = params.width * 10 + format[i[0]] - 48;

        } else if (format[i[0]] == '*')
            params.width = va_arg(p_args, int);
    }

    params.spec = format[i[0]];

    s21_format_and_buff(i, buf, p_args, params);
}

void s21_format_and_buff(int *i, char *buf, va_list p_args, format_t params) {
    // %[flags][width][.prec][length]specifier

    switch (params.spec) {
        case 'c':
            if (params.length == 'l')
                s21_lc_to_buf(va_arg(p_args, wchar_t), params, buf, i);
            else if (params.length == 'h')
                s21_lc_to_buf(va_arg(p_args, wint_t), params, buf, i);
            else
                s21_c_to_buf(va_arg(p_args, int), params, buf, i);
            break;
        case 'd':
        case 'i':
            if (params.length == 'l')
                s21_d_to_buf(va_arg(p_args, long int), params, buf, i, 10);
            else if (params.length == 'h')
        s21_d_to_buf((short)va_arg(p_args, int), params, buf, i, 10);
            else if (params.length == 'L')
        s21_d_to_buf(va_arg(p_args, long long), params, buf, i, 10);
            else
            s21_d_to_buf(va_arg(p_args, int), params, buf, i, 10);
            break;
        case 'f':
            if (params.length == 'L')
                s21_f_to_buf(va_arg(p_args, long double), params, buf, i);
            else
            s21_f_to_buf(va_arg(p_args, double), params, buf, i);
            break;
        case 's':
            s21_s_to_buf(p_args, params, buf, i);
            break;
        case 'u':
            s21_u_to_buf(va_arg(p_args, uint64_t), params, buf, i, 10);
            break;
        case 'g':
        case 'G':
            if (params.length == 'L')
                s21_gG_to_buf(va_arg(p_args, long double), params, buf, i);
            else
            s21_gG_to_buf(va_arg(p_args, double), params, buf, i);
            break;
        case 'e':
        case 'E':
            if (params.length == 'L')
                s21_parse_man(params, buf, va_arg(p_args, long double), i);
            else
            s21_parse_man(params, buf, va_arg(p_args, double), i);
            break;
        case 'x':
        case 'X':
            s21_xX_to_buf(params, buf, va_arg(p_args, int64_t), i);
            break;
        case 'n':
            i[1]--;
            break;
        case 'o':
            s21_o_to_buf(params, buf, va_arg(p_args, int64_t), i);
            break;
        case 'p':
            s21_p_to_buf(params, buf, va_arg(p_args, uint64_t), i);
            break;
    }

    if (params.spec == 'G' || params.spec == 'E') s21_uppcase(buf);
}

void s21_c_to_buf(const char c, format_t params, char *buf, int *i) {
    if (params.width && !params.minus) {
        for (int j = 0; j < params.width - 1; j++) {
            buf[i[1]] = ' ';
            i[1]++;
        }
        buf[i[1]] = c;
    } else if (params.width && params.minus) {
        buf[i[1]] = c;
        i[1]++;
        for (int j = 0; j < params.width - 1; j++) {
            buf[i[1]] = ' ';
            i[1]++;
        }
        i[1]--;
    } else {
        buf[i[1]] = c;
    }
}

void s21_d_to_buf(int64_t d, format_t params, char *buf, int *i, int base) {
    int m = 0;

    if ((d < 0) && (d != 0)) {
        d = -d;
        m = 1;
    }

    char temp[BUFF_SIZE] = {'\0'};
    int j = 0;

    if (d == 0) {
        temp[0] = '0';
        j++;
    } else {
        while (d != 0) {
            // temp[j] = d%10 + 48;
            temp[j] = "0123456789abcdef"[d % base];
            j++;
            d /= base;
        }
    }

    int len = (int)s21_strlen(temp);

    while (len < params.prec) {
        temp[j++] = '0';
        params.prec--;
    }

    if (params.space && !m) temp[j] = ' ';
    if (params.plus && !m) temp[j] = '+';
    if (params.hash && !(params.spec == 'x' || params.spec == 'X')) temp[j] = '0';
    if (m) temp[j] = '-';

    if (params.spec == 'X') s21_uppcase(temp);

    s21_format_flag(temp, params, buf, i, 0);
}

void s21_format_flag(char *temp, format_t params, char *buf, int *i, int mode) {
    int base_w = (int)s21_strlen(temp);

    if ((params.hash && (params.spec == 'x' || params.spec == 'X')) ||
        params.spec == 'p') {
        if (!s21_check_zeroes(temp) || params.spec == 'p') {
            // params.prec += 2;
            // params.width -= 1;
            if (params.width) params.width -= 2;
        }
    } else if (params.width && params.hash &&
               (params.spec == 'x' || params.spec == 'X' || params.spec == 'p'))
        params.width -= 2;

    if (params.width && !params.minus) {
        for (int j = 0; j < params.width - mode - base_w; j++) {
            if (!params.zero)
                buf[i[1]++] = ' ';
            else
                buf[i[1]++] = '0';
        }
        if ((params.hash && (params.spec == 'x' || params.spec == 'X')) ||
            params.spec == 'p') {
            if (!s21_check_zeroes(temp) || params.spec == 'p') {
                buf[i[1]++] = '0';
                if (params.spec == 'X')
                    buf[i[1]++] = 'X';
                else
                    buf[i[1]++] = 'x';
            }
        }
        for (int j = 0; j < base_w; j++) buf[i[1]++] = temp[base_w - 1 - j];
        i[1]--;
    } else if (params.width && params.minus) {
        if ((params.hash && (params.spec == 'x' || params.spec == 'X')) ||
            params.spec == 'p') {
            if (!s21_check_zeroes(temp) || params.spec == 'p') {
                buf[i[1]++] = '0';
                if (params.spec == 'X')
                    buf[i[1]++] = 'X';
                else
                    buf[i[1]++] = 'x';
            }
        }
        for (int j = 0; j < base_w; j++) buf[i[1]++] = temp[base_w - 1 - j];
        for (int j = 0; j < params.width - mode - base_w; j++) buf[i[1]++] = ' ';
        i[1]--;
    } else {
        if ((params.hash && (params.spec == 'x' || params.spec == 'X')) ||
            params.spec == 'p') {
            if (!s21_check_zeroes(temp) || params.spec == 'p') {
                buf[i[1]++] = '0';
                if (params.spec == 'X')
                    buf[i[1]++] = 'X';
                else
                    buf[i[1]++] = 'x';
            }
        }
        for (int j = 0; j < base_w; j++) buf[i[1]++] = temp[base_w - 1 - j];
        i[1]--;
    }
}

void s21_f_to_buf(long double f, format_t params, char *buf, int *i) {
    int m = 0;

    if (f < 0. && f != 0.) {
        f = -f;
        m = 1;
    }
    int count = 0;
    long double man = 0, ipartd = 0;
    long long ipart = 0;
    char temp[BUFF_SIZE] = {'\0'};

    man += modfl(f, &ipartd);
    if (params.spec == 'e' || params.spec == 'E')
        ipart = round(ipartd);
    else
        ipart = ipartd;

    long long del = 0;

    if (params.prec) {  //&& params.spec != 'e' && params.spec != 'E'
        if (params.spec == 'e' || params.spec == 'E')
            del = pow(10, params.prec - 1);
        else
            del = pow(10, params.prec);
        man = roundl(man * del) / del;
    } else {
        del = pow(10, 6);
        man = roundl(man * del) / del;
    }

    if (!params.prec && params.isprec) man = roundl(man);

    int j = 0;
    if (!(!params.prec && params.isprec) || (params.spec != 'f' && !params.prec))
        temp[j++] = '.';

    if (ipart == 0) temp[j++] = '0';

    while (ipart != 0) {
        temp[j] = (long int)ipart % 10 + '0';
        j++;
        ipart /= 10;
    }

    if (params.space && !m) temp[j] = ' ';
    if (params.plus && !m) temp[j] = '+';
    if (m) temp[j] = '-';

    if (params.spec == 'f' && !params.prec)
        count = 6;
    else if (params.prec == 0 && params.isprec)
        count = 1;
    else if (params.prec)
        count = params.prec;

    s21_format_flag(temp, params, buf, i, count);

    i[1]++;

    if (!(!params.prec && params.isprec)) {
        long long mani = man * pow(10, count) + 0.05;
        char temp1[BUFF_SIZE] = {'\0'};

        int k = 0;
        for (; k < count; k++) {
            temp1[k] = mani % 10 + '0';
            mani /= 10;
        }
        k--;
        for (; k >= 0; k--) {
            buf[i[1]++] = temp1[k];
        }
    }

    i[1]--;
}

void s21_s_to_buf(va_list p_args, format_t params, char *buf, int *i) {
    int j = 0;
    char temp[BUFF_SIZE] = {'\0'};

    if (params.length == 'l') {
        const wchar_t *wstr = va_arg(p_args, wchar_t *);
        if (wstr != NULL) {
            j = wcstombs(temp, wstr, BUFF_SIZE);

            if (params.width && !params.minus) {
                for (int k = 0; k < params.width - j; k++) {
                    buf[i[1]++] = ' ';
                }
            }
            j = 0;
            while (temp[j] != '\0' && (!params.isprec || j < params.prec)) {
                buf[i[1]++] = temp[j++];
            }
            if (params.width && params.minus) {
                for (int k = 0; k < params.width - j; k++) {
                    buf[i[1]++] = ' ';
                }
            }
            i[1]--;
        } else {
            s21_strcat(buf, "(null)");
            i[1] += 5;
        }
    } else {
        char *str = va_arg(p_args, char *);
        if (str != NULL) {
            j = s21_strlen(str);
            if (params.width && !params.minus) {
                for (int k = 0; k < params.width - j; k++) {
                    buf[i[1]++] = ' ';
                }
            }
            j = 0;
            while (*str != '\0' && (!params.isprec || j < params.prec)) {
                buf[i[1]++] = *str;
                str++;
                j++;
            }

            if (params.width && params.minus) {
                for (int k = 0; k < params.width - j; k++) {
                    buf[i[1]++] = ' ';
                }
            }
            i[1]--;
        } else {
            s21_strcat(buf, "(null)");
            i[1] += 5;
        }
    }
}

void s21_lc_to_buf(wchar_t c1, format_t params, char *buf, int *i) {
    char tmp[10] = {0};
    tmp[0] = c1;

    if (params.width && !params.minus) {
        for (int j = 0; j < params.width - 1; j++) {
            buf[i[1]] = ' ';
            i[1]++;
        }

        buf[i[1]] = '\0';
        i[1] = s21_strlen(s21_strcat(buf, tmp)) - 1;

    } else if (params.width && params.minus) {
        i[1] = s21_strlen(s21_strcat(buf, tmp));
        for (int j = 0; j < params.width - 1; j++) {
            buf[i[1]] = ' ';
            i[1]++;
        }
        i[1]--;
    } else {
        i[1] = s21_strlen(s21_strcat(buf, tmp));
    }
}

void s21_u_to_buf(uint64_t d, format_t params, char *buf, int *i, int base) {
    if (params.length == 'l')
        d = (uint64_t)d;
    else if (params.length == 'h')
        d = (uint16_t)d;
    else if (params.length == ' ')
        d = (uint32_t)d;

    char temp[BUFF_SIZE] = {'\0'};
    int j = 0;

    if (d == 0) {
        temp[0] = '0';
        j++;
    } else {
        while (d != 0) {
            temp[j] = "0123456789abcdef"[d % base];
            j++;
            d /= base;
        }
    }

    int len = (int)s21_strlen(temp);

    while (len < params.prec) {
        temp[j++] = '0';
        params.prec--;
    }

    if (params.space) temp[j] = ' ';
    if (params.plus) temp[j] = '+';

    s21_format_flag(temp, params, buf, i, 0);
}

void s21_gG_to_buf(long double f, format_t params, char *buf, int *i) {
    if (params.prec == 0 && params.isprec) params.prec = 1;
    long double m_val = f + 0.000000001;
    int pow = 0;
    if ((int)f - f) {
        while ((int)m_val == 0) {
            pow++;
            m_val *= 10;
        }
    }
    if (pow > 4) {
        params.width -= 3;
        params.prec = 0;
        s21_f_to_buf(m_val, params, buf, i);
    } else {
        params.prec = 10;
        s21_f_to_buf(f, params, buf, i);
    }
    if (pow > 4) {
        s21_prepend_mantiss(buf, pow, '-', i);
    }
    s21_remove_trailing_zeroes(buf, i);
}

void s21_remove_trailing_zeroes(char *buf, int *i) {
    for (; buf[i[1]] == '0' || buf[i[1]] == '.'; i[1]--) {
        if (buf[i[1]] == '.') {
            buf[i[1]] = '\0';
            break;
        } else
            buf[i[1]] = '\0';
    }
}

void s21_prepend_mantiss(char *buf, int pow, char sign, int *i) {
    buf[i[1]] = 'e';
    buf[i[1] + 1] = sign;
    buf[i[1] + 3] = pow % 10 + '0';
    pow /= 10;
    buf[i[1] + 2] = pow % 10 + '0';
    // buf[i[1] + 4] = '\0';
    i[1] += 3;
}

void s21_uppcase(char *str) {
    while (*str) {
        if (*str >= 'a' && *str <= 'z') *str = *str - 'a' + 'A';
        str++;
    }
}

void s21_parse_man(format_t params, char *buf, long double val, int *i) {
    // val += 0.000000001;
    int pow = 0;
    char sign = (int)val == 0 ? '-' : '+';

    if ((int)val - val) {
        while ((int)val == 0) {
            pow++;
            val *= 10;
        }
    } else {
        sign = '+';
    }
    while ((int)val / 10 != 0) {
        pow++;
        val /= 10;
    }

    if (!params.isprec) params.prec = 6;

    if (params.prec == 0) {
        params.width -= 3;
        s21_f_to_buf(round(val), params, buf, i);
        s21_prepend_mantiss(buf, pow, sign, i);
    } else {
        params.width -= 3;
        params.prec += 1;
        s21_f_to_buf(val, params, buf, i);
        s21_prepend_mantiss(buf, pow, sign, i);
    }
}

void s21_o_to_buf(format_t params, char *buf, int64_t val, int *i) {
    s21_d_to_buf(val, params, buf, i, 8);
}

void s21_xX_to_buf(format_t params, char *buf, int64_t val, int *i) {
    s21_d_to_buf(val, params, buf, i, 16);
}

int s21_check_zeroes(char *buf) {
    for (int i = 0; buf[i]; i++)
        if (buf[i] != '0') return 0;
    return 1;
}

void s21_p_to_buf(format_t params, char *buf, int64_t val, int *i) {
    if (val)
        s21_d_to_buf(val, params, buf, i, 16);
    else {
        s21_memset(buf, 0, 1);
        s21_strcat(buf, "(nil)");
        i[1] += 6;
    }
}

 int main(){
    char buf[BUFF_SIZE];
     int a = 10, b = 20, c;
     char *ws = "Helloooooo";
     c = a + b;
     s21_sprintf(buf, "Sum of %d and %d is %d, %s\n", a, b, c, ws);
     printf("%s", buf);

     return 0;

}