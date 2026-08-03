#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int escape = 1;
int get_user_choice(void);
void does_database_exist(void);
void if_overflow(void);

typedef struct date {
    int day, month, year, hour, minute;
} date;

date take_the_date(void);

typedef struct entry {
    long double amount;
    char comment[128];
} entry;

entry take_new_entry(date d, int i);

void append_to_database(date d, char *c, entry e);

typedef struct sort {
    int day, month, year, hour, minute;
    char line[256];
} record;

int compare_the_records(const void *a, const void *b);
void sort_the_database(void);

void how(void);
void credits(void);

int main(void) {
    printf("\n_________________________________________________________");
    printf("\n                                                         ");
    printf("\n                    Yazarkasa v0.1.0                     ");
    printf("\n                                                         ");
    printf("\n    Please select among available options below (1-3):   ");
    printf("\n                                                         ");
    printf("\n                     1) New Entry                        ");
    printf("\n                     2) Calculations                     ");
    printf("\n                     3) Exit                             ");
    printf("\n_________________________________________________________\n\n");

    do {
        int user_choice = get_user_choice();
        does_database_exist();
        switch (user_choice) {
            case 1: {
                printf("\n_________________________________________________________");
                printf("\n                                                         ");
                printf("\n                        New Entry                        ");
                printf("\n                                                         ");
                printf("\n          Please select the type of the entry:           ");
                printf("\n                                                         ");
                printf("\n                     1) Incoming T.                      ");
                printf("\n                     2) Outgoing T.                      ");
                printf("\n                     3) Exit                             ");
                printf("\n_________________________________________________________\n\n");
                
                do {
                    int user_choice = get_user_choice();
                    does_database_exist();
                    switch (user_choice) {
                        case 1: {
                            printf("\n_________________________________________________________");
                            printf("\n                                                         ");
                            printf("\n                  Incoming Transaction                   ");
                            printf("\n                                                         ");
                            printf("\n       Please select the type of the transaction:        ");
                            printf("\n                                                         ");
                            printf("\n                        1) Cash                          ");
                            printf("\n                        2) Debit                         ");
                            printf("\n                        3) Credit                        ");
                            printf("\n_________________________________________________________\n\n");

                            do {
                                int user_choice = get_user_choice();
                                does_database_exist();
                                switch (user_choice) {
                                    case 1: {
                                        date d = take_the_date();
                                        entry in_cash = take_new_entry(d, 1);
                                        append_to_database(d, "CASH  :", in_cash);
                                        sort_the_database();
                                        credits();
                                        break;
                                    }
                                    case 2: {
                                        date d = take_the_date();
                                        entry in_debit = take_new_entry(d, 1);
                                        append_to_database(d, "DEBIT :", in_debit);
                                        sort_the_database();
                                        credits();
                                        break;
                                    }
                                    case 3: {
                                        date d = take_the_date();
                                        entry in_credit = take_new_entry(d, 1);
                                        append_to_database(d, "CREDIT:", in_credit);
                                        sort_the_database();
                                        credits();
                                        break;
                                    }
                                    default: how();
                                }
                            } while (escape);
                            break;
                        }
                        case 2: {
                            printf("\n_________________________________________________________");
                            printf("\n                                                         ");
                            printf("\n                  Outgoing Transaction                   ");
                            printf("\n                                                         ");
                            printf("\n       Please select the type of the transaction:        ");
                            printf("\n                                                         ");
                            printf("\n                        1) Cash                          ");
                            printf("\n                        2) Debit                         ");
                            printf("\n                        3) Credit                        ");
                            printf("\n_________________________________________________________\n\n");

                            do {
                                int user_choice = get_user_choice();
                                does_database_exist();
                                switch (user_choice) {
                                    case 1: {
                                        date d = take_the_date();
                                        entry out_cash = take_new_entry(d, 2);
                                        append_to_database(d, "CASH  :", out_cash);
                                        sort_the_database();
                                        credits();
                                        break;
                                    }
                                    case 2: {
                                        date d = take_the_date();
                                        entry out_debit = take_new_entry(d, 2);
                                        append_to_database(d, "DEBIT :", out_debit);
                                        sort_the_database();
                                        credits();
                                        break;
                                    }
                                    case 3: {
                                        date d = take_the_date();
                                        entry out_credit = take_new_entry(d, 2);
                                        append_to_database(d, "CREDIT:", out_credit);
                                        sort_the_database();
                                        credits();
                                        break;
                                    }
                                    default: how();
                                }
                            } while (escape);
                            break;
                        }
                        case 3: {
                            credits();
                            break;
                        }
                        default: how();
                    }   
                } while (escape);
                break;
            }
            case 2: {
                printf("\n_________________________________________________________");
                printf("\n                                                         ");
                printf("\n                      Calculations                       ");
                printf("\n                                                         ");
                printf("\n          Please select the type of the entry:           ");
                printf("\n                                                         ");
                printf("\n                     1) xxxxxxxxxxx                      ");
                printf("\n                     2) xxxxxxxxxxx                      ");
                printf("\n                     3) xxxxxxxxxxx                      ");
                printf("\n_________________________________________________________\n\n");

                do {
                    int user_choice = get_user_choice();
                    does_database_exist();
                    credits();
                } while (escape);
                break;
            }
            case 3: {
                credits();
                break;
            }
            default: how();
        }
    } while (escape);

    return 0;
}

int get_user_choice(void) {
    int user_choice;
    char buffer[32];
    char *endPtr;

    while (1) {
        printf("Your selection: ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) continue;
        if (strchr(buffer, '\n') == NULL) {
            if_overflow();
            continue;
        }
        user_choice = strtol(buffer, &endPtr, 10);
        if (endPtr != buffer && user_choice >= 1 && user_choice <= 3) {
            return user_choice;
        }
        printf("\nIt can't be that hard to enter a valid selection...\n\n");
    }
}

void does_database_exist(void) {
    FILE *database = fopen("yazarkasa.csv", "r");

    if (database) {
        fclose(database);
    } else {
        printf("\n>>> WARNING!");
        printf("\nIt seems the database has been vaporized somehow.");
        printf("\nOr it's just that this is your first time initializing one.");
        printf("\nIf you previously had a database,");
        printf("\nI'm afraid that one seems to be lost.");
        FILE *database = fopen("yazarkasa.csv", "w");
        if (database == NULL) {
            printf("\n\n>>> WEIRD!\nI wonder how can a write even fail but it sure seems it can and it did.");
            return;
        }
        fprintf(database, "DATE & TIME\t        TYPE\tAMOUNT\t    COMMENT\n");
        fclose(database);
        printf("\nEither way, I created a new database.");
        printf("\nNow please press enter to continue...");
        getchar();
    }
}

void if_overflow(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    printf("\nIs it really that hard to not overflow the buffer?");
    printf("\nMind you, I really hate dealing with overflows...\n\n");
}

date take_the_date(void) {
    date d;
    int is_feb_29;
    int day;
    char buffer[32];
    char *endPtr;

    while (1) {
        printf("Year   : ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) continue;
        if (strchr(buffer, '\n') == NULL) {
            if_overflow();
            continue;
        }
        d.year = strtol(buffer, &endPtr, 10);
        if (endPtr != buffer && d.year >= 1 && d.year <= 9999) break;
        printf("\nDoes that abomination really look like a valid year to you?\n\n");
    }

    if (d.year % 4 == 0) {
            if (d.year % 100 != 0) {
                if (d.year % 400 == 0) {
                    is_feb_29 = 1;
                } else is_feb_29 = 1;
            } else is_feb_29 = 0;
        } else is_feb_29 = 0;

    while (1) {
        printf("Month  : ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) continue;
        if (strchr(buffer, '\n') == NULL) {
            if_overflow();
            continue;
        }
        d.month = strtol(buffer, &endPtr, 10);
        if (endPtr != buffer && d.month >= 1 && d.month <= 12) break;
        printf("\nDoes that abomination really look like a valid month to you?\n\n");
    }

    if (d.month == 2) {
        if (is_feb_29 == 1) {
            day = 29;
        } else day = 28;
    } else if (d.month == 1 || d.month == 3 || d.month == 5 || d.month == 7 || d.month == 8 || d.month == 10 || d.month ==  12) {
        day = 31;
    } else day = 30;

    while (1) {
        printf("Day    : ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) continue;
        if (strchr(buffer, '\n') == NULL) {
            if_overflow();
            continue;
        }
        d.day = strtol(buffer, &endPtr, 10);
        if (endPtr != buffer && d.day >= 1 && d.day <= day) break;
        printf("\nDoes that abomination really look like a valid day to you?\n\n");
    }
    
    while (1) {
        printf("Hour   : ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) continue;
        if (strchr(buffer, '\n') == NULL) {
            if_overflow();
            continue;
        }
        d.hour = strtol(buffer, &endPtr, 10);
        if (endPtr != buffer && d.hour >= 0 && d.hour <= 23) break;
        printf("\nDoes that abomination really look like a valid hour to you?\n\n");
    }

    while (1) {
        printf("Minute : ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) continue;
        if (strchr(buffer, '\n') == NULL) {
            if_overflow();
            continue;
        }
        d.minute = strtol(buffer, &endPtr, 10);
        if (endPtr != buffer && d.minute >= 0 && d.minute <= 59) break;
        printf("\nDoes that abomination really look like a valid minute to you?\n\n");
    }

    return d;
}

entry take_new_entry(date d, int i) {
    entry e;
    char buffer[16];
    char *endPtr;

    while (1) {
        printf("Amount : ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) continue;
        if (strchr(buffer, '\n') == NULL) {
            if_overflow();
            continue;
        }
        for (char *comma = buffer; *comma; comma++) {
            if (*comma == ',') *comma = '.';
        }
        e.amount = strtold(buffer, &endPtr);
        if (endPtr != buffer && i == 1 && e.amount != 0) {
            if (e.amount < 0) e.amount *= -1;
            break;
        } else if (endPtr != buffer && i != 1 && e.amount != 0) {
            if (e.amount > 0) e.amount *= -1;
            break;
        }
        printf("\nDoes that abomination really look valid to you?\n\n");
    }

    while (1) {
        printf("Comment: ");
        if (fgets(e.comment, sizeof(e.comment), stdin) == NULL) continue;
        if (strchr(e.comment, '\n') == NULL) {
            if_overflow();
            continue;
        }
        char *newline = strchr(e.comment, '\n');
        *newline = '\0';
        break;
    }
    
    return e;
}

void append_to_database(date d, char *c, entry e) {
    FILE *database;
    database = fopen("yazarkasa.csv", "a");
    if (database == NULL) {
        printf("\n\n>>> WEIRD!\nI wonder how can a write even fail but it sure seems it can and it did.");
        return;
    }
    fprintf(database, "%02d/%02d/%04d - %02d:%02d\t%s\t%+.2Lf TL\t%s\n", d.day, d.month, d.year, d.hour, d.minute, c, e.amount, e.comment);
    fclose(database);
}

int compare_the_records(const void *a, const void *b) {
    const record *r1 = a;
    const record *r2 = b;

    if (r1->year != r2->year) return r1->year - r2->year;
    if (r1->month != r2->month) return r1->month - r2->month;
    if (r1->day != r2->day) return r1->day - r2->day;
    if (r1->hour != r2->hour) return r1->hour - r2->hour;
    return r1->minute - r2->minute;
}

void sort_the_database(void) {
    FILE *database;
    database = fopen("yazarkasa.csv", "r");
    
    if (database == NULL) {
        printf("\n\n>>> WEIRD!\nThings have taken a weird route...");
        return;
    }
    
    record r[512];
    int count = 0;
    
    char discard[256];
    if (fgets(discard, sizeof(discard), database) == NULL) {
        printf("\n\nSomehow the database is empty.");
        fclose(database);
        return;
    }

    while (count < 512 && fgets(r[count].line, sizeof(r[count].line), database) != NULL) {
        int failsafe = sscanf(r[count].line, 
                              "%02d/%02d/%04d - %02d:%02d", 
                              &r[count].day, 
                              &r[count].month, 
                              &r[count].year, 
                              &r[count].hour, 
                              &r[count].minute);
        
        if (failsafe != 5) {
            continue;
        }
        count++;
    }
    
    fclose(database);
    qsort(r, count, sizeof(record), compare_the_records);
    database = fopen("yazarkasa.csv", "w");
    if (database == NULL) {
        printf("\n\n>>> WEIRD!\nI wonder how can a write even fail but it sure seems it can and it did.");
        return;
    }
    fprintf(database, "DATE & TIME\t        TYPE\tAMOUNT\t    COMMENT\n");
    for (int i = 0; i < count; i++) fputs(r[i].line, database);
    fclose(database);
}

void how(void) {
    printf("\n\nI've no idea what have you possibly done with that keyboard of yours");
    printf("\nto get this message but I must admit that I'm quite impressed :D ");
    getchar();
    escape = 0;
}

void credits(void) {
    printf("\n_________________________________________________________");
    printf("\n                                                         ");
    printf("\n                            #                            ");
    printf("\n                          #                              ");
    printf("\n                        #                                ");
    printf("\n                      #                                  ");
    printf("\n            #       #               #                    ");
    printf("\n            #     #               # #                    ");
    printf("\n            #   #               #   #   #                ");
    printf("\n            # #               #     # #                  ");
    printf("\n            #       #       #       #       #            ");
    printf("\n            # #       #           # #     #              ");
    printf("\n            #   #       #       #   #   #                ");
    printf("\n            #     #       #   #     # #                  ");
    printf("\n            #       #       #       #                    ");
    printf("\n                      #     #                            ");
    printf("\n                        #   #                            ");
    printf("\n                          # #                            ");
    printf("\n                            #                            ");
    printf("\n_________________________________________________________\n\n");
    printf("Have a great day!\nPlease press enter to exit the program...");
    getchar();
    escape = 0;
}