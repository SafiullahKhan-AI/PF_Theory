#include <stdio.h>

int main() {
    int age;
    char eyesightexam, writtentest, drivingtest, medicalcertificate;
    printf("DRIVING LICENSE FORM\n");
    printf("Enter your age: ");
    scanf("%d", &age);
    if (age <= 0) {
        printf("Invalid Age\n");
        return 1;
    }

    if (age < 18) {
        printf("Ineligible, You must be 18 or older.\n");
        return 1;
    }
    printf("Have you passed the eyesight test? (Press P for pass and F for fail): ");
    scanf(" %c", &eyesightexam);
    if (eyesightexam == 'F' || eyesightexam == 'f') {
        printf("Need prescription for glasses\n");
        return 1;
    }
    printf("Have you passed the written test? (Press P for pass and F for fail): ");
    scanf(" %c", &writtentest);
    if (writtentest == 'F' || writtentest == 'f') {
        printf("GIVE A RETAKE\n");
        return 1;
    }
    printf("Have you passed the driving test? (Press P for pass and F for fail): ");
    scanf(" %c", &drivingtest);
    if (drivingtest == 'F' || drivingtest == 'f') {
        printf("Ineligible because you did not passed the driving test.\n");
        return 1;
    }
    if (age < 60) {
        printf("You are eligible for the license\n");
    } else {
        printf("Do you have a medical fitness certificate? (Press Y for yes and N for no): ");
        scanf(" %c", &medicalcertificate);
        if (medicalcertificate == 'N' || medicalcertificate == 'n') {
            printf("You are not eligible for the license\n");
            return 1;
        } else {
            printf("Eligible!!\n");
        }
    }

    return 0;
}

