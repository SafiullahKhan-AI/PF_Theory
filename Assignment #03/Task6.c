#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define DATA_FILE "members.dat"
#define NAME_MAX 100
#define BATCH_MAX 32
#define MEM_MAX 8
#define DATE_MAX 11
#define INTEREST_MAX 8
#define INIT_CPC 8

typedef struct {
    int id;
    char name[NAME_MAX];
    char batch[BATCH_MAX];
    char membership[MEM_MAX];
    char reg_date[DATE_MAX];
    char dob[DATE_MAX];
    char interest[INTEREST_MAX];
} Student;

static Student *students = NULL;
static size_t studentCounter = 0;
static size_t studentCap = 0;

static void trim(char *s)
{
    if (!s)
        return;
    size_t n = strlen(s);

    while (n > 0 && (s[n-1] == '\n' || s[n-1] == '\r' || s[n-1] == ' ' || s[n-1] == '\t')){
        s[n-1] = '\0';
        n--;
    }
}

static char *read_line(const char *prompt){
    if (prompt)
        printf("%s", prompt);

    fflush(stdout);
    size_t cap = 128;
    size_t len = 0;
    char *buf = malloc(cap);
    if (!buf){
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    int c;
    while ((c = fgetc(stdin)) != EOF && c != '\n'){
        if (len + 1 >= cap){
            cap *= 2;
            char *tmp = realloc(buf, cap);
            if (!tmp){
                free(buf);
                perror("realloc");
                exit(EXIT_FAILURE);
            }
            buf = tmp;
        }
        buf[len++] = (char)c;
    }
    if (c == EOF && len == 0){
        free(buf);
        return NULL;
    }
    buf[len] = '\0';
    trim(buf);
    return buf;
}

static void ensure_capacity(size_t min){
    if (studentCap >= min)
        return;
    size_t n = studentCap ? studentCap : INIT_CPC;
    while (n < min)
        n <<= 1;
    Student *tmp = realloc(students, n * sizeof(Student));
    if (!tmp){
        perror("realloc");
        exit(EXIT_FAILURE);
    }
    students = tmp;
    studentCap = n;
}

int loadDatabase(const char *filename){
    FILE *f = fopen(filename, "rb");
    if (!f){
        if (errno == ENOENT){
            studentCounter = 0;
            return 0;
        }
        return -1;
    }
    if (fseek(f, 0, SEEK_END) != 0){
        fclose(f);
        return -1;
    }
    long sz = ftell(f);
    if (sz < 0){
        fclose(f);
        return -1;
    }
    rewind(f);
    size_t estimated = (size_t)(sz / sizeof(Student) + 4);
    ensure_capacity(estimated);
    studentCounter = 0;
    Student tmp;
    while(fread(&tmp, sizeof(Student), 1, f) == 1){
        ensure_capacity(studentCounter + 1);
        students[studentCounter++] = tmp;
    }
    if (ferror(f)){
        fclose(f);
        return -1;
    }
    fclose(f);
    return 0;
}

int saveDatabase(const char *filename){
    char tmpname[512];
    snprintf(tmpname, sizeof(tmpname), "%s.tmp", filename);
    FILE *f = fopen(tmpname, "wb");
    if(!f)
        return -1;
    for(size_t i = 0; i < studentCounter; ++i){
        if(fwrite(&students[i], sizeof(Student), 1, f) != 1){
            fclose(f);
            remove(tmpname);
            return -1;
        }
    }
    if(fflush(f) != 0){
        fclose(f);
        remove(tmpname);
        return -1;
    }
    if (fclose(f) != 0){
        remove(tmpname);
        return -1;
    }
    if(remove(filename) != 0 && errno != ENOENT){
    }
    if (rename(tmpname, filename) != 0){
        remove(tmpname);
        return -1;
    }
    return 0;
}

static long findStudentIndexByID(int id){
    for (size_t i = 0; i < studentCounter; ++i){
        if (students[i].id == id)
            return (long)i;
    }
    return -1;
}

int addStudent(const Student *s, const char *filename){
    if (!s)
        return -1;
    if (findStudentIndexByID(s->id) != -1)
        return -1;
    FILE *f = fopen(filename, "ab");
    if (!f)
        return -1;
    if (fwrite(s, sizeof(Student), 1, f) != 1){
        fclose(f);
        return -1;
    }
    if (fclose(f) != 0)
        return -1;
    ensure_capacity(studentCounter + 1);
    students[studentCounter++] = *s;
    return 0;
}

static int validBatch(const char *b){
    if (!b)
        return 0;
    if (strcmp(b, "CS") == 0)
        return 1;
    if (strcmp(b, "SE") == 0)
        return 1;
    if (strcmp(b, "Cyber Security") == 0)
        return 1;
    if (strcmp(b, "AI") == 0)
        return 1;
    return 0;
}

static int validMembership(const char *m){
    if (!m)
        return 0;
    if (strcmp(m, "IEEE") == 0)
        return 1;
    if (strcmp(m, "ACM") == 0)
        return 1;
    return 0;
}

static int validInterest(const char *s){
    if (!s)
        return 0;
    if (strcmp(s, "IEEE") == 0)
        return 1;
    if (strcmp(s, "ACM") == 0)
        return 1;
    if (strcmp(s, "Both") == 0)
        return 1;
    return 0;
}

static int validDate(const char *d){
    if (!d)
        return 0;
    if (strlen(d) != 10)
        return 0;
    for (int i = 0; i < 10; ++i)
    {
        if (i == 4 || i == 7)
        {
            if (d[i] != '-')
                return 0;
        }
        else
        {
            if (d[i] < '0' || d[i] > '9')
                return 0;
        }
    }
    return 1;
}

int updateStudent(int studentID){
    long idx = findStudentIndexByID(studentID);
    if (idx == -1)
        return -1;
    Student *s = &students[idx];
    char *in;
    printf("Current record:\n");
    printf("%d %s %s %s %s %s %s\n", s->id, s->name, s->batch, s->membership, s->reg_date, s->dob, s->interest);
    in = read_line("New batch (blank to keep): ");
    if (!in)
        return -1;
    if (strlen(in) > 0){
        if (!validBatch(in))
        {
            free(in);
            return -1;
        }
        strncpy(s->batch, in, BATCH_MAX - 1);
        s->batch[BATCH_MAX - 1] = '\0';
    }
    free(in);
    in = read_line("New membership (blank to keep): ");
    if (!in)
        return -1;
    if (strlen(in) > 0){
        if (!validMembership(in)){
            free(in);
            return -1;
        }
        strncpy(s->membership, in, MEM_MAX - 1);
        s->membership[MEM_MAX - 1] = '\0';
    }
    free(in);
    if (saveDatabase(DATA_FILE) != 0)
        return -1;
    return 0;
}

int deleteStudent(int studentID){
    long idx = findStudentIndexByID(studentID);
    if (idx == -1)
        return -1;
    for (size_t i = (size_t)idx; i + 1 < studentCounter; ++i)
        students[i] = students[i + 1];
    studentCounter--;
    if (studentCap > INIT_CPC && studentCounter * 4 < studentCap){
        size_t nc = studentCap / 2;
        if (nc < INIT_CPC)
            nc = INIT_CPC;
        Student *tmp = realloc(students, nc * sizeof(Student));
        if (tmp)
        {
            students = tmp;
            studentCap = nc;
        }
    }
    if (saveDatabase(DATA_FILE) != 0)
        return -1;
    return 0;
}

void displayAllStudents(void){
    if (studentCounter == 0){
        printf("No students\n");
        return;
    }
    for (size_t i = 0; i < studentCounter; ++i){
        Student *s = &students[i];
        printf("ID:%d Name:%s Batch:%s Membership:%s Reg:%s DOB:%s Interest:%s\n", s->id, s->name, s->batch, s->membership, s->reg_date, s->dob, s->interest);
    }
}

void generateBatchReport(const char *batchFilter, const char *membershipFilter){
    int found = 0;
    for (size_t i = 0; i < studentCounter; ++i){
        int batchMatch = (!batchFilter || strlen(batchFilter) == 0) ? 1 : (strcmp(students[i].batch, batchFilter) == 0);
        int memMatch = 1;
        if (membershipFilter && strlen(membershipFilter) > 0){
            if (strcmp(membershipFilter, "Both") == 0)
                memMatch = (strcmp(students[i].interest, "Both") == 0);
            else
                memMatch = (strcmp(students[i].membership, membershipFilter) == 0) || (strcmp(students[i].interest, "Both") == 0);
        }
        if (batchMatch && memMatch){
            if (!found)
                printf("Report: batch='%s' membership='%s'\n", batchFilter ? batchFilter : "", membershipFilter ? membershipFilter : "");
            Student *s = &students[i];
            printf("%d %s %s %s %s %s %s\n", s->id, s->name, s->batch, s->membership, s->reg_date, s->dob, s->interest);
            found = 1;
        }
    }
    if (!found)
        printf("No matching records\n");
}

static void read_string(const char *prompt, char *out, size_t outlen){
    char *tmp = read_line(prompt);
    if (!tmp){
        out[0] = '\0';
        return;
    }
    strncpy(out, tmp, outlen - 1);
    out[outlen - 1] = '\0';
    free(tmp);
}

void registerStudentInteractive(void){
    Student s;
    char *tmp;
    char buf[64];
    printf("Enter ID: ");
    if (scanf("%d", &s.id) != 1){
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
        return;
    }
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
    if (findStudentIndexByID(s.id) != -1)
        return;
    tmp = read_line("Full Name: ");
    if (!tmp)
        return;
    strncpy(s.name, tmp, NAME_MAX - 1);
    s.name[NAME_MAX - 1] = '\0';
    free(tmp);
    tmp = read_line("Batch (CS/SE/Cyber Security/AI): ");
    if (!tmp)
        return;
    if (!validBatch(tmp)){
        free(tmp);
        return;
    }

    strncpy(s.batch, tmp, BATCH_MAX - 1);
    s.batch[BATCH_MAX - 1] = '\0';
    free(tmp);
    tmp = read_line("Membership (IEEE/ACM): ");
    if (!tmp)
        return;
    if (!validMembership(tmp)){
        free(tmp);
        return;
    }
    strncpy(s.membership, tmp, MEM_MAX - 1);
    s.membership[MEM_MAX - 1] = '\0';
    free(tmp);
    tmp = read_line("Registration Date (YYYY-MM-DD): ");
    if (!tmp)
        return;
    if (!validDate(tmp)){
        free(tmp);
        return;
    }
    strncpy(s.reg_date, tmp, DATE_MAX - 1);
    s.reg_date[DATE_MAX - 1] = '\0';
    free(tmp);
    tmp = read_line("DOB (YYYY-MM-DD): ");
    if (!tmp)
        return;
    if (!validDate(tmp)){
        free(tmp);
        return;
    }
    strncpy(s.dob, tmp, DATE_MAX - 1);
    s.dob[DATE_MAX - 1] = '\0';
    free(tmp);
    tmp = read_line("Interest (IEEE/ACM/Both): ");
    if (!tmp)
        return;
    if (!validInterest(tmp)){
        free(tmp);
        return;
    }
    strncpy(s.interest, tmp, INTEREST_MAX - 1);
    s.interest[INTEREST_MAX - 1] = '\0';
    free(tmp);
    if (addStudent(&s, DATA_FILE) != 0)
        return;
    if (saveDatabase(DATA_FILE) != 0)
        return;
    printf("Registered\n");
}

void printMenu(void){
    printf("\n=== FAST Membership System ===\n");
    printf("1 Register new student\n");
    printf("2 Update existing student\n");
    printf("3 Delete a student\n");
    printf("4 View all registrations\n");
    printf("5 Generate batch-wise report\n");
    printf("6 Exit\n");
    printf("Enter choice: ");
}

int main(void){
    ensure_capacity(INIT_CPC);
    loadDatabase(DATA_FILE);
    int choice = 0;
    while (1){
        printMenu();
        if(scanf("%d", &choice) != 1){
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;
            continue;
        }

        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
        if (choice == 1){
            registerStudentInteractive();
        }
        else if (choice == 2){
            int id;
            printf("Enter ID to update: ");
            if (scanf("%d", &id) != 1){
                while ((c = getchar()) != '\n' && c != EOF)
                    ;
                continue;
            }
            while((c = getchar()) != '\n' && c != EOF)
                ;
            updateStudent(id);
        }
        else if (choice == 3){
            int id;
            printf("Enter ID to delete: ");
            if (scanf("%d", &id) != 1){
                while ((c = getchar()) != '\n' && c != EOF)
                    ;
                continue;
            }
            while ((c = getchar()) != '\n' && c != EOF)
                ;
            deleteStudent(id);
        }
        else if (choice == 4){
            displayAllStudents();
        }
        else if (choice == 5){
            char *b = read_line("Enter batch (blank for any): ");
            char *m = read_line("Enter membership filter (IEEE/ACM/Both or blank): ");
            generateBatchReport(b, m);
            free(b);
            free(m);
        }
        else if (choice == 6){
            saveDatabase(DATA_FILE);
            break;
        }
    }
    free(students);
    return 0;
}
