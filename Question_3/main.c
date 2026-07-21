#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

struct Employee {
    int id;
    char name[20];
    float salary;
};

int main() {
    int fd;
    struct Employee emp;

    // Step 1: Create and Open a file
    fd = open("employee.dat", O_CREAT | O_RDWR, 0666);

    // Step 2: Write employee records
   //First employee
    emp.id = 101;
    sprintf(emp.name, "Alice");
    emp.salary = 50000;
    write(fd, &emp, sizeof(emp));
    // Second employee
    emp.id = 102;
    sprintf(emp.name, "Bob");
    emp.salary = 60000;
    write(fd, &emp, sizeof(emp));
   //Third employee
    emp.id = 103;
    sprintf(emp.name,"Jhon");
    emp.salary = 80000;
    write(fd, &emp, sizeof(emp)); 
    //step 3: Update second employee
    emp.id = 102;
     sprintf(emp.name, "Bob");
    emp.salary = 65000;

    lseek(fd, sizeof(struct Employee), SEEK_SET);
    write(fd, &emp, sizeof(emp));

    // Step 4: Read second employee
    lseek(fd, sizeof(struct Employee), SEEK_SET);
    read(fd, &emp, sizeof(emp));

    printf("ID = %d\n", emp.id);
    printf("Name = %s\n", emp.name);
    printf("Salary = %.2f\n", emp.salary);

    // Step 5: Close file
    close(fd);

    return 0;
}
