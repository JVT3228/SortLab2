#pragma once

void processString(char* str, int len) {
    int count_e = 0;
    int group_count = 0;

    for (int i = 0; i < len; i++) {
        if (str[i] == 'å') {
            count_e++;
        }
        else {
            if (count_e == 5) {
                group_count++;
            }
            count_e = 0;
        }
    }

    if (count_e == 5) {
        group_count++;
    }

    count_e = 0;
    if (group_count > 1) {
        for (int i = 0; i < len; i++) {
            if (str[i] == 'å') {
                count_e++;
            }
            else {
                if (count_e == 5) {
                    str[i - 5] = 'Å';
                    for (int j = i - 4; j < i; j++) {
                        str[j] = ' ';
                    }
                }
                count_e = 0;
            }
        }
        if (count_e == 5) {
            str[len - 5] = 'Å';
            for (int j = len - 4; j < len; j++) {
                str[j] = ' ';
            }
        }

        int shift = 0;
        bool last_was_space = false;
        for (int i = 0; i < len; i++) {
            if (str[i] != ' ') {
                str[shift++] = str[i];
                last_was_space = false;
            }
            else if (!last_was_space) {
                str[shift++] = ' ';
                last_was_space = true;
            }
        }
        if (shift > 0 && str[shift - 1] == ' ') {
            shift--;
        }
        str[shift] = '\0';

        if (group_count > 1) {
            str[shift++] = '?';
            str[shift] = '\0';
        }
    }
}