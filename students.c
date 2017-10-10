/*
 * This is the file in which you will implement the functionality required by
 * the assignment.  Make sure to add your name and @oregonstate.edu email
 * address below:
 *
 * Name: Ethan Shields
 * Email: shieldse@oregonstate.edu
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "students.h"

void quick_sort(struct student*, int, int);
int partition(struct student*, int, int);
void swap(struct student*, struct student*);

/*
 * This function should initialize a single student struct with name, ID, and
 * GPA data.
 *
 * Params:
 *   student - a pointer to the student struct to be initialized.  The memory
 *     for this student will already be allocated before the function is
 *     called.  You simply need to fill its values.  When the function returns,
 *     the fields of this student struct should contain the corresponding
 *     values passed in the other arguments.  Note that this function must
 *     allocate space for the name field and copy the value from name into the
 *     newly-allocated name field.  Make sure that if any of the fields of
 *     student already have memory on the heap allocated to them, you free that
 *     memory before overwriting it with new values.
 *   name - a string containing the student's name.  Note that you'll have to
 *     make a copy of this string to store in the student struct instead of
 *     storing this string directly.
 *   id - an integer ID for the student
 *   gpa - the student's GPA
 */
void init_student(struct student* student, char* name, int id, float gpa) {
    int length = strlen(name) + 1;
    char* n = malloc(length * sizeof(char));
    strcpy(n, name);

    free_student(student);

    student->name = n;
    student->id = id;
    student->gpa = gpa;
}

/*
 * This function should free the memory allocated by init_student() for a
 * single student.
 *
 * Params:
 *   student - a pointer to the student whose memory should be freed.  Note
 *     that only memory stored *within* this struct should be freed.  The
 *     struct itself should not be freed.
 */
void free_student(struct student* student) {
    if (student->name) {
        free_student(student);
        student->name = NULL;
    }
}


/*
 * This function should make a deep copy of a single student.  A deep copy is
 * a copy where pointer fields don't simply have their values (i.e. the memory
 * addresses they point to) copied, but the pointers are dereferenced and
 * copies made of the values themselves.  In other words, for each pointer
 * field in the object being copied, new memory is allocated for a copy of that
 * field to be created, and a pointer to this newly-allocated memory is stored
 * in the copied object.
 *
 * Params:
 *   student - a pointer to the student to be deep copied
 *
 * Return:
 *   Should return a pointer to a deep copy of student.  Memory for this copy
 *   should be allocated by this function.  This memory will have to be freed
 *   using a combination of free_student() and free().
 */
struct student* deep_copy_student(struct student* student) {
    struct student* s = malloc(sizeof(struct student));

    s->name = student->name;
    s->id = student->id;
    s->gpa = student->gpa;

    return s;
}


/*
 * This function should allocate space for an array of student structs and
 * initialize their fields using the provided information.  In particular, you
 * should create an array of student structs where the i'th student has the
 * i'th name, the i'th ID, and the i'th GPA from the arrays provided as
 * arguments.  You should use your init_student() function to perform the
 * initialization of each student in the new array.
 *
 * Params:
 *   num_students - the number of students to be stored in the newly allocated
 *     array
 *   names - an array of the names of the students to be stored in the newly
 *     allocated array of student structs.  This array will have length
 *     num_students.
 *   ids - an array of the IDs of the students to be stored in the newly
 *     allocated array of student structs.  This array will have length
 *     num_students.
 *   gpas - an array of the GPAs of the students to be stored in the newly
 *     allocated array of student structs.  This array will have length
 *     num_students.
 *
 * Return:
 *   Should return a pointer to the newly allocated and initialized array of
 *   student structs.  The i'th student in this array should have the i'th
 *   name, the i'th ID, and the i'th GPA from the arrays provided as arguments.
 */
struct student* create_student_array(int num_students, char** names, int* ids, float* gpas) {

    struct student* students = malloc(num_students * sizeof(struct student));

    for (size_t i = 0; i < num_students; i++) {
        init_student(students + i, names[i], ids[i], gpas[i]);
    }

    return students;
}


/*
 * This function should free all of the memory allocated to an array of
 * student structs, including the memory allocated to the array itself as
 * well as any memory allocated within the individual student structs.  You
 * should use free_student() to free the memory for each individual student.
 *
 * Params:
 *   students - a pointer to the array of student structs whose memory is to
 *     be freed
 *   num_students - the number of students in the array
 */
void destroy_student_array(struct student* students, int num_students) {
    for (size_t i = 0; i < num_students; i++) {
        free_student(students + i);
    }
}


/*
 * This function should print the name, ID, and GPA of each student in an
 * array, one student per line.
 *
 * Params:
 *   students - the array of students to be printed
 *   num_students - the number of students in the array
 */
void print_students(struct student* students, int num_students) {
    for (size_t i = 0; i < num_students; i++) {
        struct student s = students[i];

        printf("Name: %s\n", s.name);
        printf("ID: %i\n", s.id);
        printf("GPA: %f\n\n", s.gpa);
    }
}


/*
 * This function should return a pointer to the student in a given array with
 * the highest GPA.  The pointer returned should be an address within the
 * array itself.  You should not make a copy of the student being returned,
 * i.e. this function should not allocate any memory.
 *
 * Params:
 *   students - the array from which to find the student with the highest GPA
 *   num_students - the number of students in the array
 *
 * Return:
 *   Should return a pointer to the student in the array with the highest GPA.
 *   The pointer returned should be an address within the array itself.  You
 *   should not make a copy of the student being returned.
 */
struct student* find_max_gpa(struct student* students, int num_students) {
    float max_gpa = 0;
    int index = -1;

    for (size_t i = 0; i < num_students; i++) {
        float gpa = students[i].gpa;
        if (gpa > max_gpa) {
            max_gpa = gpa;
            index = i;
        }
    }

    return students + index;
}


/*
 * This function should return a pointer to the student in a given array with
 * the lowest GPA.  The pointer returned should be an address within the
 * array itself.  You should not make a copy of the student being returned,
 * i.e. this function should not allocate any memory.
 *
 * Params:
 *   students - the array from which to find the student with the lowest GPA
 *   num_students - the number of students in the array
 *
 * Return:
 *   Should return a pointer to the student in the array with the lowest GPA.
 *   The pointer returned should be an address within the array itself.  You
 *   should not make a copy of the student being returned.
 */
struct student* find_min_gpa(struct student* students, int num_students) {
    float min_gpa = 4;
    int index = -1;

    for (size_t i = 0; i < num_students; i++) {
        float gpa = students[i].gpa;
        if (gpa < min_gpa) {
            min_gpa = gpa;
            index = i;
        }
    }

    return students + index;
}


/*
 * This function should sort students by descending GPA (i.e. highest GPAs
 * at the beginning of the array).  You may implement any sorting algorithm
 * you want, with the following constraints:
 *   - You must sort in place, i.e. you can't allocate additional memory.
 *   - You may not use built-in sorting functions like qsort(), i.e. you must
 *     implement the sort yourself.
 *
 * Params:
 *   students - the array of students to be sorted; when the function returns,
 *     this array will be sorted by descending GPA
 *   num_students - the number of students in the array
 */
void sort_by_gpa(struct student* students, int num_students) {
    //quick_sort(students, 0, num_students - 1);
}

/**
 * Sorts the students array using the quick sort algorithm
 * @param students Array of students to be sorted
 * @param a        lower index
 * @param b        Upper index
 */
void quick_sort(struct student* students, int a, int b) {
    if (a < b) {
        int pi = partition(students, a, b);

        quick_sort(students, a, pi - 1);
        quick_sort(students, pi + 1, b);
    }
}

/**
 * Places last element in correct position
 * @param  students  Array of students
 * @param  a         lower index
 * @param  b         Upper index
 * @return           New index of partitioned element
 */
int partition(struct student* students, int a, int b) {
    float pivot = students[b].gpa;

    int i = a - 1;

    for (size_t j = a; j <= b - 1; j++) {
        if (students[j].gpa >= pivot) {
            i++;
            swap(students + i, students + j);
        }
    }

    swap(students + i + 1, students + b);

    return i + 1;
}

/**
 * Swaps two student structs in students array
 * @param a     Pointer to first struct
 * @param b     Pointer to second struct
 */
void swap(struct student* a, struct student* b) {
    struct student temp = *a;
    *a = *b;
    *b = temp;
}
