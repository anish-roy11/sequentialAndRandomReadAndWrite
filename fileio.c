
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>






// Function to concatenate two strings and return the concatenated value
char* concatenateStrings( char* str1,  char* str2) {
    // Calculate the length of the resulting string
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    // Allocate memory for the concatenated string, including space for the null terminator
    char* result = (char*)malloc(len1 + len2 + 1);

    // Check if memory allocation was successful
    if (result == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    // Copy the first string to the result
    strcpy(result, str1);

    // Concatenate the second string to the result
    strcat(result, str2);

    return result;
}


//i+_+j+_+Sequential_+thread+_+concurencyCount+.bin
char* createFilename( char *str1, char *str2, char *str3, char *str4, char *str5, char *str6, char *str7, char *str8, char *str9, char *str10,char *str11,char *str12)
{
    const char* string10 = "Hello, ";
    const char* string20 = "world!";

    char* filename = concatenateStrings(str1,str2 );
    filename = concatenateStrings(filename,str3 );
    filename = concatenateStrings(filename,str4 );
    filename = concatenateStrings(filename,str5 );
    filename = concatenateStrings(filename,str6 );
    filename = concatenateStrings(filename,str7 );
    filename = concatenateStrings(filename,str8 );
    filename = concatenateStrings(filename,str9 );
    filename = concatenateStrings(filename,str10 );
    filename = concatenateStrings(filename,str11 );
    filename = concatenateStrings(filename,str12 );
    return filename;

}


// Function to convert an integer to a string and return the string
char* intToString(int num)
{
    // Determine the number of digits in the integer
    int numDigits = snprintf(NULL, 0, "%d", num);

    // Allocate memory for the string, including space for the null terminator
    char* str = (char*)malloc(numDigits + 1);

    // Check if memory allocation was successful
    if (str == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    // Use sprintf to convert the integer to a string and store it in str
    snprintf(str, numDigits + 1, "%d", num);

    return str;
}



































int readFileRandomAccesswithRecordSizee(int recordSizeInKB, int fileSizeInKB, char *filenames)
{
    //printf("\n\n\n\n\n =======================================================================================");
    //printf("\n log entry: readFileRandomAccesswithRecordSizee");


    // Perform  benchmark
    clock_t start_time, end_time;
    double elapsed_time;
    start_time = clock();



    struct timeval start, end;
    double exec_time;
    start_time = clock();
    gettimeofday(&start, NULL);




    // Open the file for reading in binary mode
    FILE *file = fopen(filenames, "rb");
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    // Seed the random number generator
    //srand((unsigned int)time(NULL));
    srand(1024);

    // Define a buffer for record
    char *buffer = malloc(recordSizeInKB);

    // Number of records to read (1 MB file with 64KB records)
    int numRecords = fileSizeInKB / recordSizeInKB;

    int recordReadCount=0;

    // Read random records from the file with a random access pattern
    for (int i = 0; i < numRecords; i++)
    {
        // Seek to a random position in the file
        long position = (rand() % numRecords) * sizeof(buffer);
        fseek(file, position, SEEK_SET);


        // Read the record from the file
        size_t bytesRead = fread(buffer, 1, sizeof(buffer), file);
        recordReadCount++;

//        if (bytesRead != sizeof(buffer) && numRecords > 0)
//        {
//            perror("Error reading from file");
//            fclose(file);
//            return 1;
//        }

        // Process the record (you can replace this with your processing logic)
        // For demonstration, we print the first byte of each record
        //printf("Record %d: First Byte = %d\n", i + 1, buffer[0]);
    }

    // Close the file
    fclose(file);
    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    //elapsed_time = ((double)(end_time - start_time));
    //printf("\nFor read file random access, time elapsed: %lf seconds\n", elapsed_time);

    printf("\nTotal records read: %d\n", recordReadCount);



    gettimeofday(&end, NULL);
    exec_time = (double) (end.tv_sec - start.tv_sec) + (double) (end.tv_usec - start.tv_usec) / 1000000;

    // TO-DO transform execution time in throughput
    printf("\nExecution time: %lf seconds\n", exec_time);


    //printf("\n log exit: readFileRandomAccesswithRecordSizee");
    return 0;
}




































int readFileSequentialAccessWithRecordSizee(int recordSizeInKB, int fileSizeInKB, char *filenames)
{

    //printf("\n\n\n\n\n =======================================================================================");
    //printf("\nlog entry: readFileSequentialAccessWithRecordSizee");


    // Perform  benchmark
    clock_t start_time, end_time;
    double elapsed_time;
    start_time = clock();



    struct timeval start, end;
    double exec_time;
    start_time = clock();
    gettimeofday(&start, NULL);





    // Open the binary file for reading
    FILE *file = fopen(filenames, "rb");
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    // Define a buffer to read record
    char *buffer = malloc(recordSizeInKB);

    // Read and process each 64KB record
    size_t bytesRead;
    int recordCount = 0;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0)
    {
        recordCount++;
    }


    // Close the file
    fclose(file);
    end_time = clock();
    //elapsed_time = ((double)(end_time - start_time));
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("\nfilenames=%s read successfully", filenames);
    printf("\nTotal records read: %d\n", recordCount);


    //printf("\nFor read file sequential access, time elapsed: %lf seconds\n", elapsed_time);






    gettimeofday(&end, NULL);
    exec_time = (double) (end.tv_sec - start.tv_sec) + (double) (end.tv_usec - start.tv_usec) / 1000000;

    // TO-DO transform execution time in throughput
    //printf("\nExecution time: %lf seconds\n", exec_time);


    //printf("\nlog exit: readFileSequentialAccessWithRecordSizee");
    return 0;
}














































int writeFileRandomAccesswithRecordSizes(int recordSizeInKB, int fileSizeInKB, char *filenames)
{
    //printf("\n\n\n\n\n =======================================================================================");
//    printf("\n log entry: writeFileRandomAccesswithRecordSizes");


    printf("\nfilenames=%s", filenames);
    printf("\nrecordSizeInKB=%d", recordSizeInKB);
    printf("\nfileSizeInKB=%d", fileSizeInKB);

    // Perform  benchmark
    clock_t start_time, end_time;
    double elapsed_time;




    struct timeval start, end;
    double exec_time;
    start_time = clock();
    gettimeofday(&start, NULL);





    int noOfRecords=fileSizeInKB/recordSizeInKB;

    FILE *fp = fopen(filenames, "wb+");
    if (fp == NULL)
    {
        printf("Error opening output file\n");
        return 1;
    }

    // Allocate a buffer to store the binary data
    char *buffer = malloc(recordSizeInKB);
    if (buffer == NULL)
    {
        printf("Error allocating buffer\n");
        return 1;
    }

    // Generate random binary data
    for (int j = 0; j < recordSizeInKB; j++)
    {
        buffer[j] = rand() % 256;
    }


    // Write the binary data to the file in blocks
    for (int i = 0; i < noOfRecords; i++)
    {

        // Seek to the offset of the block to be written
        fseek(fp, i * recordSizeInKB, SEEK_SET);

        // Write the block to the file
        fwrite(buffer, 1, recordSizeInKB, fp);
    }

    if(noOfRecords == 0)
    {
        fseek(fp,  0, SEEK_SET);

        // Write the block to the file
        fwrite(buffer, 1, fileSizeInKB, fp);
    }

    // Close the output file
    fclose(fp);

    // Free the buffer
    free(buffer);



    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    //elapsed_time = ((double)(end_time - start_time));
    //printf("\nFor write file  random access, time elapsed: %lf seconds\n", elapsed_time);




    gettimeofday(&end, NULL);
    exec_time = (double) (end.tv_sec - start.tv_sec) + (double) (end.tv_usec - start.tv_usec) / 1000000;

    // TO-DO transform execution time in throughput
    //printf("\nExecution time: %lf seconds\n", exec_time);



    //printf("\n log exit: writeFileRandomAccesswithRecordSizes");

    return 0;
}












































































int writeFileSequentialAccessWithRecordSizes(int recordSizeInKB, int fileSizeInKB, char *filenames)
{
    //printf("\n\n\n\n\n =======================================================================================");
    //printf("\n log entry: writeFileSequentialAccessWithRecordSizes");


    printf("\nfilenames=%s", filenames);
    printf("\nrecordSizeInKB=%d", recordSizeInKB);
    printf("\nfileSizeInKB=%d", fileSizeInKB);

    // Perform  benchmark
    clock_t start_time, end_time;
    double elapsed_time;
    start_time = clock();


    struct timeval start, end;
    double exec_time;
    gettimeofday(&start, NULL);


    int blockSize = recordSizeInKB;
    int noOfRecords=fileSizeInKB/recordSizeInKB;

// Open the output file
    FILE *file = fopen(filenames, "wb");
    if (file == NULL)
    {
        printf("Error opening output file\n");
        return 1;
    }

    // Allocate a buffer to store the binary data
    char *buffer = malloc(recordSizeInKB);
    if (buffer == NULL)
    {
        printf("Error allocating buffer\n");
        return 1;
    }

// Generate random binary data
    for (int j = 0; j < recordSizeInKB; j++)
    {
        buffer[j] = rand() % 256;
    }

    // Write the binary data to the file in blocks
    for (int i = 0; i < noOfRecords; i++)
    {

        // Write the block to the file
        fwrite(buffer, 1, blockSize, file);
    }
    if(noOfRecords == 0)
    {
        fwrite(buffer, 1, fileSizeInKB, file);
    }

    // Close the output file
    fclose(file);

    // Free the buffer
    free(buffer);

    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    //elapsed_time = ((double)(end_time - start_time));

    gettimeofday(&end, NULL);
    exec_time = (double) (end.tv_sec - start.tv_sec) + (double) (end.tv_usec - start.tv_usec) / 1000000;
    //printf("\nExecution time: %lf seconds\n", exec_time);

//    printf("\nFor write file sequential access, time elapsed: %lf seconds\n", elapsed_time);

    return 0;

    //printf("\n log exit: writeFileSequentialAccessWithRecordSizes");
}





































void workWithFiles(int concurrencyCount)
{

//    char* count1String;
//    char* count2String;
//    char* fileExtension=".bin";
//    char* underscore = "_";
//    char* sequentialRead = "SequentialRead";
//    char* sequentialWrite = "sequentialWrite";
//    char* randomRead = "randomlRead";
//    char* randomWrite = "randomWrite";
//    char* concurrencyCountString = intToString(concurrencyCount);
//    char * filename;
//    char* recordNamearrayString[] = { "recordSize_64KB", "recordSize_01MB", "recordSize_16MB"};
//    char* fileNamearrayString[] = { "fileSize_4MB", "fileSize_1GB"};


    int recordSize64KB =  64 * 1024;
    int recordSize1MB =  1024 * 1024;
    int recordSize16MB =  16 * 1024 * 1024;

    int fileSize4MB = 4 * 1024 * 1024;
    int fileSize1GB =  1024 * 1024 * 1024 ;

    int recordSizearray[] = { recordSize64KB, recordSize1MB, recordSize16MB};
    int fileSizearray[] = { fileSize4MB, fileSize1GB};





//    int count1=0;
//    int count2=0;
//    for(int i=0; i < sizeof(fileSizearray) / sizeof(fileSizearray[0]); i++ )
//    {
//        count1++;
//        count1String = intToString(count1);
//        for(int j=0; j < sizeof(recordSizearray) / sizeof(recordSizearray[0]); j++ )
//        {
//
//            count2++;
//            count2String = intToString(count2);
//
//            filename = createFilename(count1String,underscore,count2String,underscore,
//                                      sequentialWrite,underscore,concurrencyCountString,underscore,
//                                      recordNamearrayString[j],underscore,fileNamearrayString[i],fileExtension);
//
//            writeFileSequentialAccessWithRecordSizes(recordSizearray[j], fileSizearray[i], filename);
//
//        }
//
//    }
//
//
//
//

    writeFileSequentialAccessWithRecordSizes(recordSizearray[0], fileSizearray[0], (char *) "1_SequentialWrite_recordSize64KB_fileSize4MB");
    writeFileSequentialAccessWithRecordSizes(recordSizearray[1], fileSizearray[0], (char *) "2_SequentialWrite_recordSize1MB_fileSize4MB");
    writeFileSequentialAccessWithRecordSizes(recordSizearray[2], fileSizearray[0], (char *) "3_SequentialWrite_recordSize16MB_fileSize4MB");
    writeFileSequentialAccessWithRecordSizes(recordSizearray[0], fileSizearray[1], (char *) "4_SequentialWrite_recordSize64KB_fileSize1GB");
    writeFileSequentialAccessWithRecordSizes(recordSizearray[1], fileSizearray[1], (char *) "5_SequentialWrite_recordSize1MB_fileSize1GB");
    writeFileSequentialAccessWithRecordSizes(recordSizearray[2], fileSizearray[1], (char *) "6_SequentialWrite_recordSize16MB_fileSize1GB");


    writeFileRandomAccesswithRecordSizes(recordSizearray[0], fileSizearray[0], (char *)  "101_RandomWrite_recordSize64KB_fileSize4MB");
    writeFileRandomAccesswithRecordSizes(recordSizearray[1], fileSizearray[0], (char *)  "102_RandomWrite_recordSize1MB_fileSize4MB");
    writeFileRandomAccesswithRecordSizes(recordSizearray[2], fileSizearray[0], (char *)  "103_RandomWrite_recordSize16MB_fileSize4MB");
    writeFileRandomAccesswithRecordSizes(recordSizearray[0], fileSizearray[1], (char *)  "104_RandomWrite_recordSize64KB_fileSize1GB");
    writeFileRandomAccesswithRecordSizes(recordSizearray[1], fileSizearray[1], (char *) "105_RandomWrite_recordSize1MB_fileSize1GB");
    writeFileRandomAccesswithRecordSizes(recordSizearray[2], fileSizearray[1], (char *) "106_RandomWrite_recordSize16MB_fileSize1GB");


    readFileSequentialAccessWithRecordSizee(recordSizearray[0], fileSizearray[0], (char *)  "1_SequentialWrite_recordSize64KB_fileSize4MB");
    readFileSequentialAccessWithRecordSizee(recordSizearray[1], fileSizearray[0], (char *)  "2_SequentialWrite_recordSize1MB_fileSize4MB");
    readFileSequentialAccessWithRecordSizee(recordSizearray[2], fileSizearray[0], (char *)  "3_SequentialWrite_recordSize16MB_fileSize4MB");
    readFileSequentialAccessWithRecordSizee(recordSizearray[0], fileSizearray[1], (char *)  "4_SequentialWrite_recordSize64KB_fileSize1GB");
    readFileSequentialAccessWithRecordSizee(recordSizearray[1], fileSizearray[1], (char *)  "5_SequentialWrite_recordSize1MB_fileSize1GB");
    readFileSequentialAccessWithRecordSizee(recordSizearray[2], fileSizearray[1], (char *)  "6_SequentialWrite_recordSize16MB_fileSize1GB");



    readFileRandomAccesswithRecordSizee(recordSizearray[0], fileSizearray[0], (char *)  "101_RandomWrite_recordSize64KB_fileSize4MB");
    readFileRandomAccesswithRecordSizee(recordSizearray[1], fileSizearray[0], (char *)  "102_RandomWrite_recordSize1MB_fileSize4MB");
    readFileRandomAccesswithRecordSizee(recordSizearray[2], fileSizearray[0], (char *)  "103_RandomWrite_recordSize16MB_fileSize4MB");
    readFileRandomAccesswithRecordSizee(recordSizearray[0], fileSizearray[1], (char *)  "104_RandomWrite_recordSize64KB_fileSize1GB");
    readFileRandomAccesswithRecordSizee(recordSizearray[1], fileSizearray[1], (char *) "105_RandomWrite_recordSize1MB_fileSize1GB");
    readFileRandomAccesswithRecordSizee(recordSizearray[2], fileSizearray[1], (char *) "106_RandomWrite_recordSize16MB_fileSize1GB");

}

//void workWithFiles3(int concurencyCount)
//{
//
//    printf("\nchild pid in workWithFiles3=%d",getpid());
//}



void sequentialWrite_recordSize64KB_fileSize4MB(int concurencyCount )
{
    printf("\n=========================================================================");
    printf("\nlog entry:sequentialWrite_recordSize64KB_fileSize4MB, concurrency count=%d",concurencyCount);

    // Perform  benchmark
    clock_t start_time, end_time;
    double elapsed_time;
    start_time = clock();


    struct timeval start, end;
    double exec_time;
    gettimeofday(&start, NULL);

    int recordSize64KB =  64 * 1024;
    int recordSize1MB =  1024 * 1024;
    int recordSize16MB =  16 * 1024 * 1024;

    int fileSize4MB = 4 * 1024 * 1024;
    int fileSize1GB =  1024 * 1024 * 1024 ;

    int recordSizearray[] = { recordSize64KB, recordSize1MB, recordSize16MB};
    int fileSizearray[] = { fileSize4MB, fileSize1GB};


    pid_t pids[concurencyCount];


    // Create the specified number of processes
    for (int j = 0; j < concurencyCount; j++)
    {
        pids[j] = fork();
        if (pids[j] == -1)
        {
            perror("fork() error");
            exit(EXIT_FAILURE);
        }

        else if (pids[j] == 0)
        {
            // Child process
            printf("\nchild pid=%d",getpid());
            pid_t pid = getpid();
            int pid_as_int = (int)pid;
            char* pid_as_String = intToString(pid_as_int);
            char* filename = concatenateStrings("1_SequentialWrite_recordSize64KB_fileSize4MB",pid_as_String );

            //writeFileSequentialAccessWithRecordSizes(recordSizearray[0]/concurencyCount, fileSizearray[0], (char *) "1_SequentialWrite_recordSize64KB_fileSize4MB");
            writeFileSequentialAccessWithRecordSizes(recordSizearray[0], fileSizearray[0]/concurencyCount, (char *) filename);
            exit(0);
        }


    }

    // Wait for all child processes to finish
    for (int j = 0; j < concurencyCount; j++)
    {
        wait(NULL);
    }


    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    //elapsed_time = ((double)(end_time - start_time));

    gettimeofday(&end, NULL);
    exec_time = (double) (end.tv_sec - start.tv_sec) + (double) (end.tv_usec - start.tv_usec) / 1000000;
    printf("\nExecution time: %lf seconds\n", exec_time);


}







void sequentialWrite_recordSize1MB_fileSize4MB(int concurencyCount)
{
    printf("\n=========================================================================");
    printf("\nlog entry:sequentialWrite_recordSize1MB_fileSize4MB, concurrency count=%d",concurencyCount);

    // Perform  benchmark
    clock_t start_time, end_time;
    double elapsed_time;
    start_time = clock();


    struct timeval start, end;
    double exec_time;
    gettimeofday(&start, NULL);

    int recordSize64KB =  64 * 1024;
    int recordSize1MB =  1024 * 1024;
    int recordSize16MB =  16 * 1024 * 1024;

    int fileSize4MB = 4 * 1024 * 1024;
    int fileSize1GB =  1024 * 1024 * 1024 ;

    int recordSizearray[] = { recordSize64KB, recordSize1MB, recordSize16MB};
    int fileSizearray[] = { fileSize4MB, fileSize1GB};


    pid_t pids[concurencyCount];


    // Create the specified number of processes
    for (int j = 0; j < concurencyCount; j++)
    {
        pids[j] = fork();
        if (pids[j] == -1)
        {
            perror("fork() error");
            exit(EXIT_FAILURE);
        }

        else if (pids[j] == 0)
        {
            // Child process
            printf("\nchild pid=%d",getpid());
            pid_t pid = getpid();
            int pid_as_int = (int)pid;
            char* pid_as_String = intToString(pid_as_int);
            char* filename = concatenateStrings("1_SequentialWrite_recordSize1MB_fileSize4MB",pid_as_String );

            //writeFileSequentialAccessWithRecordSizes(recordSizearray[0]/concurencyCount, fileSizearray[0], (char *) "1_SequentialWrite_recordSize64KB_fileSize4MB");
            writeFileSequentialAccessWithRecordSizes(recordSizearray[1], fileSizearray[0]/concurencyCount, (char *) filename);
            exit(0);
        }


    }

    // Wait for all child processes to finish
    for (int j = 0; j < concurencyCount; j++)
    {
        wait(NULL);
    }


    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    //elapsed_time = ((double)(end_time - start_time));

    gettimeofday(&end, NULL);
    exec_time = (double) (end.tv_sec - start.tv_sec) + (double) (end.tv_usec - start.tv_usec) / 1000000;
    printf("\nExecution time: %lf seconds\n", exec_time);


}

//@@@@@=======================

































void sequentialWrite_recordSize16MB_fileSize4MB(int concurencyCount)
{
    printf("\n=========================================================================");
    printf("\nlog entry:sequentialWrite_recordSize16MB_fileSize4MB, concurrency count=%d",concurencyCount);

    // Perform  benchmark
    clock_t start_time, end_time;
    double elapsed_time;
    start_time = clock();


    struct timeval start, end;
    double exec_time;
    gettimeofday(&start, NULL);

    int recordSize64KB =  64 * 1024;
    int recordSize1MB =  1024 * 1024;
    int recordSize16MB =  16 * 1024 * 1024;

    int fileSize4MB = 4 * 1024 * 1024;
    int fileSize1GB =  1024 * 1024 * 1024 ;

    int recordSizearray[] = { recordSize64KB, recordSize1MB, recordSize16MB};
    int fileSizearray[] = { fileSize4MB, fileSize1GB};


    pid_t pids[concurencyCount];


    // Create the specified number of processes
    for (int j = 0; j < concurencyCount; j++)
    {
        pids[j] = fork();
        if (pids[j] == -1)
        {
            perror("fork() error");
            exit(EXIT_FAILURE);
        }

        else if (pids[j] == 0)
        {
            // Child process
            printf("\nchild pid=%d",getpid());
            pid_t pid = getpid();
            int pid_as_int = (int)pid;
            char* pid_as_String = intToString(pid_as_int);
            char* filename = concatenateStrings("1_SequentialWrite_recordSize16MB_fileSize4MB",pid_as_String );

            //writeFileSequentialAccessWithRecordSizes(recordSizearray[0]/concurencyCount, fileSizearray[0], (char *) "1_SequentialWrite_recordSize64KB_fileSize4MB");
            writeFileSequentialAccessWithRecordSizes(recordSizearray[2], fileSizearray[0]/concurencyCount, (char *) filename);
            exit(0);
        }


    }

    // Wait for all child processes to finish
    for (int j = 0; j < concurencyCount; j++)
    {
        wait(NULL);
    }


    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    //elapsed_time = ((double)(end_time - start_time));

    gettimeofday(&end, NULL);
    exec_time = (double) (end.tv_sec - start.tv_sec) + (double) (end.tv_usec - start.tv_usec) / 1000000;
    printf("\nExecution time: %lf seconds\n", exec_time);


}

//@@@@@=======================

































void sequentialWrite_recordSize64KB_fileSize1GB(int concurencyCount)
{
    printf("\n=========================================================================");
    printf("\nlog entry:sequentialWrite_recordSize64KB_fileSize1GB, concurrency count=%d",concurencyCount);

    // Perform  benchmark
    clock_t start_time, end_time;
    double elapsed_time;
    start_time = clock();


    struct timeval start, end;
    double exec_time;
    gettimeofday(&start, NULL);

    int recordSize64KB =  64 * 1024;
    int recordSize1MB =  1024 * 1024;
    int recordSize16MB =  16 * 1024 * 1024;

    int fileSize4MB = 4 * 1024 * 1024;
    int fileSize1GB =  1024 * 1024 * 1024 ;

    int recordSizearray[] = { recordSize64KB, recordSize1MB, recordSize16MB};
    int fileSizearray[] = { fileSize4MB, fileSize1GB};


    pid_t pids[concurencyCount];


    // Create the specified number of processes
    for (int j = 0; j < concurencyCount; j++)
    {
        pids[j] = fork();
        if (pids[j] == -1)
        {
            perror("fork() error");
            exit(EXIT_FAILURE);
        }

        else if (pids[j] == 0)
        {
            // Child process
            printf("\nchild pid=%d",getpid());
            pid_t pid = getpid();
            int pid_as_int = (int)pid;
            char* pid_as_String = intToString(pid_as_int);
            char* filename = concatenateStrings("1_SequentialWrite_recordSize64KB_fileSize1GB",pid_as_String );

            //writeFileSequentialAccessWithRecordSizes(recordSizearray[0]/concurencyCount, fileSizearray[0], (char *) "1_SequentialWrite_recordSize64KB_fileSize4MB");
            writeFileSequentialAccessWithRecordSizes(recordSizearray[0], fileSizearray[1]/concurencyCount, (char *) filename);
            exit(0);
        }


    }

    // Wait for all child processes to finish
    for (int j = 0; j < concurencyCount; j++)
    {
        wait(NULL);
    }


    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    //elapsed_time = ((double)(end_time - start_time));

    gettimeofday(&end, NULL);
    exec_time = (double) (end.tv_sec - start.tv_sec) + (double) (end.tv_usec - start.tv_usec) / 1000000;
    printf("\nExecution time: %lf seconds\n", exec_time);


}

//@@@@@=======================

































void sequentialWrite_recordSize1MB_fileSize1GB(int concurencyCount)
{
    printf("\n=========================================================================");
    printf("\nlog entry:sequentialWrite_recordSize1MB_fileSize1GB, concurrency count=%d",concurencyCount);

    // Perform  benchmark
    clock_t start_time, end_time;
    double elapsed_time;
    start_time = clock();


    struct timeval start, end;
    double exec_time;
    gettimeofday(&start, NULL);

    int recordSize64KB =  64 * 1024;
    int recordSize1MB =  1024 * 1024;
    int recordSize16MB =  16 * 1024 * 1024;

    int fileSize4MB = 4 * 1024 * 1024;
    int fileSize1GB =  1024 * 1024 * 1024 ;

    int recordSizearray[] = { recordSize64KB, recordSize1MB, recordSize16MB};
    int fileSizearray[] = { fileSize4MB, fileSize1GB};


    pid_t pids[concurencyCount];


    // Create the specified number of processes
    for (int j = 0; j < concurencyCount; j++)
    {
        pids[j] = fork();
        if (pids[j] == -1)
        {
            perror("fork() error");
            exit(EXIT_FAILURE);
        }

        else if (pids[j] == 0)
        {
            // Child process
            printf("\nchild pid=%d",getpid());
            pid_t pid = getpid();
            int pid_as_int = (int)pid;
            char* pid_as_String = intToString(pid_as_int);
            char* filename = concatenateStrings("1_SequentialWrite_recordSize1MB_fileSize1GB",pid_as_String );

            //writeFileSequentialAccessWithRecordSizes(recordSizearray[0]/concurencyCount, fileSizearray[0], (char *) "1_SequentialWrite_recordSize64KB_fileSize4MB");
            writeFileSequentialAccessWithRecordSizes(recordSizearray[1], fileSizearray[1]/concurencyCount, (char *) filename);
            exit(0);
        }


    }

    // Wait for all child processes to finish
    for (int j = 0; j < concurencyCount; j++)
    {
        wait(NULL);
    }


    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    //elapsed_time = ((double)(end_time - start_time));

    gettimeofday(&end, NULL);
    exec_time = (double) (end.tv_sec - start.tv_sec) + (double) (end.tv_usec - start.tv_usec) / 1000000;
    printf("\nExecution time: %lf seconds\n", exec_time);


}

//@@@@@=======================

































void sequentialWrite_recordSize16MB_fileSize1GB(int concurencyCount)
{
    printf("\n=========================================================================");
    printf("\nlog entry:sequentialWrite_recordSize16MB_fileSize1GB, concurrency count=%d",concurencyCount);

    // Perform  benchmark
    clock_t start_time, end_time;
    double elapsed_time;
    start_time = clock();


    struct timeval start, end;
    double exec_time;
    gettimeofday(&start, NULL);

    int recordSize64KB =  64 * 1024;
    int recordSize1MB =  1024 * 1024;
    int recordSize16MB =  16 * 1024 * 1024;

    int fileSize4MB = 4 * 1024 * 1024;
    int fileSize1GB =  1024 * 1024 * 1024 ;

    int recordSizearray[] = { recordSize64KB, recordSize1MB, recordSize16MB};
    int fileSizearray[] = { fileSize4MB, fileSize1GB};


    pid_t pids[concurencyCount];


    // Create the specified number of processes
    for (int j = 0; j < concurencyCount; j++)
    {
        pids[j] = fork();
        if (pids[j] == -1)
        {
            perror("fork() error");
            exit(EXIT_FAILURE);
        }

        else if (pids[j] == 0)
        {
            // Child process
            printf("\nchild pid=%d",getpid());
            pid_t pid = getpid();
            int pid_as_int = (int)pid;
            char* pid_as_String = intToString(pid_as_int);
            char* filename = concatenateStrings("1_SequentialWrite_recordSize16MB_fileSize1GB",pid_as_String );

            //writeFileSequentialAccessWithRecordSizes(recordSizearray[0]/concurencyCount, fileSizearray[0], (char *) "1_SequentialWrite_recordSize64KB_fileSize4MB");
            writeFileSequentialAccessWithRecordSizes(recordSizearray[2], fileSizearray[1]/concurencyCount, (char *) filename);
            exit(0);
        }


    }

    // Wait for all child processes to finish
    for (int j = 0; j < concurencyCount; j++)
    {
        wait(NULL);
    }


    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    //elapsed_time = ((double)(end_time - start_time));

    gettimeofday(&end, NULL);
    exec_time = (double) (end.tv_sec - start.tv_sec) + (double) (end.tv_usec - start.tv_usec) / 1000000;
    printf("\nExecution time: %lf seconds\n", exec_time);


}

//@@@@@=======================

































void randomWrite_recordSize64KB_fileSize4MB(int concurencyCount)
{
    printf("\n=========================================================================");
    printf("\nlog entry:randomWrite_recordSize64KB_fileSize4MB, concurrency count=%d",concurencyCount);

    // Perform  benchmark
    clock_t start_time, end_time;
    double elapsed_time;
    start_time = clock();


    struct timeval start, end;
    double exec_time;
    gettimeofday(&start, NULL);

    int recordSize64KB =  64 * 1024;
    int recordSize1MB =  1024 * 1024;
    int recordSize16MB =  16 * 1024 * 1024;

    int fileSize4MB = 4 * 1024 * 1024;
    int fileSize1GB =  1024 * 1024 * 1024 ;

    int recordSizearray[] = { recordSize64KB, recordSize1MB, recordSize16MB};
    int fileSizearray[] = { fileSize4MB, fileSize1GB};


    pid_t pids[concurencyCount];


    // Create the specified number of processes
    for (int j = 0; j < concurencyCount; j++)
    {
        pids[j] = fork();
        if (pids[j] == -1)
        {
            perror("fork() error");
            exit(EXIT_FAILURE);
        }

        else if (pids[j] == 0)
        {
            // Child process
            printf("\nchild pid=%d",getpid());
            pid_t pid = getpid();
            int pid_as_int = (int)pid;
            char* pid_as_String = intToString(pid_as_int);
            char* filename = concatenateStrings("1_RandomWrite_recordSize64KB_fileSize4MB",pid_as_String );

            //writeFileRandomAccesswithRecordSizes(recordSizearray[0]/concurencyCount, fileSizearray[0], (char *) "1_SequentialWrite_recordSize64KB_fileSize4MB");
            writeFileRandomAccesswithRecordSizes(recordSizearray[0], fileSizearray[0]/concurencyCount, (char *) filename);
            exit(0);
        }


    }

    // Wait for all child processes to finish
    for (int j = 0; j < concurencyCount; j++)
    {
        wait(NULL);
    }


    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    //elapsed_time = ((double)(end_time - start_time));

    gettimeofday(&end, NULL);
    exec_time = (double) (end.tv_sec - start.tv_sec) + (double) (end.tv_usec - start.tv_usec) / 1000000;
    printf("\nExecution time: %lf seconds\n", exec_time);


}

//@@@@@=======================

































void randomWrite_recordSize1MB_fileSize4MB(int concurencyCount)
{
    printf("\n=========================================================================");
    printf("\nlog entry:randomWrite_recordSize1MB_fileSize4MB, concurrency count=%d",concurencyCount);

    // Perform  benchmark
    clock_t start_time, end_time;
    double elapsed_time;
    start_time = clock();


    struct timeval start, end;
    double exec_time;
    gettimeofday(&start, NULL);

    int recordSize64KB =  64 * 1024;
    int recordSize1MB =  1024 * 1024;
    int recordSize16MB =  16 * 1024 * 1024;

    int fileSize4MB = 4 * 1024 * 1024;
    int fileSize1GB =  1024 * 1024 * 1024 ;

    int recordSizearray[] = { recordSize64KB, recordSize1MB, recordSize16MB};
    int fileSizearray[] = { fileSize4MB, fileSize1GB};


    pid_t pids[concurencyCount];


    // Create the specified number of processes
    for (int j = 0; j < concurencyCount; j++)
    {
        pids[j] = fork();
        if (pids[j] == -1)
        {
            perror("fork() error");
            exit(EXIT_FAILURE);
        }

        else if (pids[j] == 0)
        {
            // Child process
            printf("\nchild pid=%d",getpid());
            pid_t pid = getpid();
            int pid_as_int = (int)pid;
            char* pid_as_String = intToString(pid_as_int);
            char* filename = concatenateStrings("1_RandomWrite_recordSize1MB_fileSize4MB",pid_as_String );

            //writeFileRandomAccesswithRecordSizes(recordSizearray[0]/concurencyCount, fileSizearray[0], (char *) "1_SequentialWrite_recordSize64KB_fileSize4MB");
            writeFileRandomAccesswithRecordSizes(recordSizearray[1], fileSizearray[0]/concurencyCount, (char *) filename);
            exit(0);
        }


    }

    // Wait for all child processes to finish
    for (int j = 0; j < concurencyCount; j++)
    {
        wait(NULL);
    }


    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    //elapsed_time = ((double)(end_time - start_time));

    gettimeofday(&end, NULL);
    exec_time = (double) (end.tv_sec - start.tv_sec) + (double) (end.tv_usec - start.tv_usec) / 1000000;
    printf("\nExecution time: %lf seconds\n", exec_time);


}

//@@@@@=======================

































void randomWrite_recordSize16MB_fileSize4MB(int concurencyCount)
{
    printf("\n=========================================================================");
    printf("\nlog entry:randomWrite_recordSize16MB_fileSize4MB, concurrency count=%d",concurencyCount);

    // Perform  benchmark
    clock_t start_time, end_time;
    double elapsed_time;
    start_time = clock();


    struct timeval start, end;
    double exec_time;
    gettimeofday(&start, NULL);

    int recordSize64KB =  64 * 1024;
    int recordSize1MB =  1024 * 1024;
    int recordSize16MB =  16 * 1024 * 1024;

    int fileSize4MB = 4 * 1024 * 1024;
    int fileSize1GB =  1024 * 1024 * 1024 ;

    int recordSizearray[] = { recordSize64KB, recordSize1MB, recordSize16MB};
    int fileSizearray[] = { fileSize4MB, fileSize1GB};


    pid_t pids[concurencyCount];


    // Create the specified number of processes
    for (int j = 0; j < concurencyCount; j++)
    {
        pids[j] = fork();
        if (pids[j] == -1)
        {
            perror("fork() error");
            exit(EXIT_FAILURE);
        }

        else if (pids[j] == 0)
        {
            // Child process
            printf("\nchild pid=%d",getpid());
            pid_t pid = getpid();
            int pid_as_int = (int)pid;
            char* pid_as_String = intToString(pid_as_int);
            char* filename = concatenateStrings("1_RandomWrite_recordSize16MB_fileSize4MB",pid_as_String );

            //writeFileRandomAccesswithRecordSizes(recordSizearray[0]/concurencyCount, fileSizearray[0], (char *) "1_SequentialWrite_recordSize64KB_fileSize4MB");
            writeFileRandomAccesswithRecordSizes(recordSizearray[2], fileSizearray[0]/concurencyCount, (char *) filename);
            exit(0);
        }


    }

    // Wait for all child processes to finish
    for (int j = 0; j < concurencyCount; j++)
    {
        wait(NULL);
    }


    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    //elapsed_time = ((double)(end_time - start_time));

    gettimeofday(&end, NULL);
    exec_time = (double) (end.tv_sec - start.tv_sec) + (double) (end.tv_usec - start.tv_usec) / 1000000;
    printf("\nExecution time: %lf seconds\n", exec_time);


}

//@@@@@=======================

































void randomWrite_recordSize64KB_fileSize1GB(int concurencyCount)
{
    printf("\n=========================================================================");
    printf("\nlog entry:randomWrite_recordSize64KB_fileSize1GB, concurrency count=%d",concurencyCount);

    // Perform  benchmark
    clock_t start_time, end_time;
    double elapsed_time;
    start_time = clock();


    struct timeval start, end;
    double exec_time;
    gettimeofday(&start, NULL);

    int recordSize64KB =  64 * 1024;
    int recordSize1MB =  1024 * 1024;
    int recordSize16MB =  16 * 1024 * 1024;

    int fileSize4MB = 4 * 1024 * 1024;
    int fileSize1GB =  1024 * 1024 * 1024 ;

    int recordSizearray[] = { recordSize64KB, recordSize1MB, recordSize16MB};
    int fileSizearray[] = { fileSize4MB, fileSize1GB};


    pid_t pids[concurencyCount];


    // Create the specified number of processes
    for (int j = 0; j < concurencyCount; j++)
    {
        pids[j] = fork();
        if (pids[j] == -1)
        {
            perror("fork() error");
            exit(EXIT_FAILURE);
        }

        else if (pids[j] == 0)
        {
            // Child process
            printf("\nchild pid=%d",getpid());
            pid_t pid = getpid();
            int pid_as_int = (int)pid;
            char* pid_as_String = intToString(pid_as_int);
            char* filename = concatenateStrings("1_randomWrite_recordSize64KB_fileSize1GB",pid_as_String );

            //writeFileRandomAccesswithRecordSizes(recordSizearray[0]/concurencyCount, fileSizearray[0], (char *) "1_SequentialWrite_recordSize64KB_fileSize4MB");
            writeFileRandomAccesswithRecordSizes(recordSizearray[0], fileSizearray[1]/concurencyCount, (char *) filename);
            exit(0);
        }


    }

    // Wait for all child processes to finish
    for (int j = 0; j < concurencyCount; j++)
    {
        wait(NULL);
    }


    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    //elapsed_time = ((double)(end_time - start_time));

    gettimeofday(&end, NULL);
    exec_time = (double) (end.tv_sec - start.tv_sec) + (double) (end.tv_usec - start.tv_usec) / 1000000;
    printf("\nExecution time: %lf seconds\n", exec_time);


}

//@@@@@=======================

































void randomWrite_recordSize1MB_fileSize1GB(int concurencyCount)
{
    printf("\n=========================================================================");
    printf("\nlog entry:randomWrite_recordSize1MB_fileSize1GB, concurrency count=%d",concurencyCount);

    // Perform  benchmark
    clock_t start_time, end_time;
    double elapsed_time;
    start_time = clock();


    struct timeval start, end;
    double exec_time;
    gettimeofday(&start, NULL);

    int recordSize64KB =  64 * 1024;
    int recordSize1MB =  1024 * 1024;
    int recordSize16MB =  16 * 1024 * 1024;

    int fileSize4MB = 4 * 1024 * 1024;
    int fileSize1GB =  1024 * 1024 * 1024 ;

    int recordSizearray[] = { recordSize64KB, recordSize1MB, recordSize16MB};
    int fileSizearray[] = { fileSize4MB, fileSize1GB};


    pid_t pids[concurencyCount];


    // Create the specified number of processes
    for (int j = 0; j < concurencyCount; j++)
    {
        pids[j] = fork();
        if (pids[j] == -1)
        {
            perror("fork() error");
            exit(EXIT_FAILURE);
        }

        else if (pids[j] == 0)
        {
            // Child process
            printf("\nchild pid=%d",getpid());
            pid_t pid = getpid();
            int pid_as_int = (int)pid;
            char* pid_as_String = intToString(pid_as_int);
            char* filename = concatenateStrings("1_RandomWrite_recordSize1MB_fileSize1GB",pid_as_String );

            //writeFileRandomAccesswithRecordSizes(recordSizearray[0]/concurencyCount, fileSizearray[0], (char *) "1_SequentialWrite_recordSize64KB_fileSize4MB");
            writeFileRandomAccesswithRecordSizes(recordSizearray[1], fileSizearray[1]/concurencyCount, (char *) filename);
            exit(0);
        }


    }

    // Wait for all child processes to finish
    for (int j = 0; j < concurencyCount; j++)
    {
        wait(NULL);
    }


    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    //elapsed_time = ((double)(end_time - start_time));

    gettimeofday(&end, NULL);
    exec_time = (double) (end.tv_sec - start.tv_sec) + (double) (end.tv_usec - start.tv_usec) / 1000000;
    printf("\nExecution time: %lf seconds\n", exec_time);



}

//@@@@@=======================

































void randomWrite_recordSize16MB_fileSize1GB(int concurencyCount)
{
    printf("\n=========================================================================");
    printf("\nlog entry:randomWrite_recordSize16MB_fileSize1GB, concurrency count=%d",concurencyCount);

    // Perform  benchmark
    clock_t start_time, end_time;
    double elapsed_time;
    start_time = clock();


    struct timeval start, end;
    double exec_time;
    gettimeofday(&start, NULL);

    int recordSize64KB =  64 * 1024;
    int recordSize1MB =  1024 * 1024;
    int recordSize16MB =  16 * 1024 * 1024;

    int fileSize4MB = 4 * 1024 * 1024;
    int fileSize1GB =  1024 * 1024 * 1024 ;

    int recordSizearray[] = { recordSize64KB, recordSize1MB, recordSize16MB};
    int fileSizearray[] = { fileSize4MB, fileSize1GB};


    pid_t pids[concurencyCount];


    // Create the specified number of processes
    for (int j = 0; j < concurencyCount; j++)
    {
        pids[j] = fork();
        if (pids[j] == -1)
        {
            perror("fork() error");
            exit(EXIT_FAILURE);
        }

        else if (pids[j] == 0)
        {
            // Child process
            printf("\nchild pid=%d",getpid());
            pid_t pid = getpid();
            int pid_as_int = (int)pid;
            char* pid_as_String = intToString(pid_as_int);
            char* filename = concatenateStrings("1_RandomWrite_recordSize16MB_fileSize1GB",pid_as_String );

            //writeFileRandomAccesswithRecordSizes(recordSizearray[0]/concurencyCount, fileSizearray[0], (char *) "1_SequentialWrite_recordSize64KB_fileSize4MB");
            writeFileRandomAccesswithRecordSizes(recordSizearray[2], fileSizearray[1]/concurencyCount, (char *) filename);
            exit(0);
        }


    }

    // Wait for all child processes to finish
    for (int j = 0; j < concurencyCount; j++)
    {
        wait(NULL);
    }


    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    //elapsed_time = ((double)(end_time - start_time));

    gettimeofday(&end, NULL);
    exec_time = (double) (end.tv_sec - start.tv_sec) + (double) (end.tv_usec - start.tv_usec) / 1000000;
    printf("\nExecution time: %lf seconds\n", exec_time);


}

//@@@@@=======================

































void sequentialRead_recordSize64KB_fileSize4MB(int concurencyCount)
{
    printf("\n=========================================================================");
    printf("\nlog entry:sequentialRead_recordSize64KB_fileSize4MB, concurrency count=%d",concurencyCount);

    // Perform  benchmark
    clock_t start_time, end_time;
    double elapsed_time;
    start_time = clock();


    struct timeval start, end;
    double exec_time;
    gettimeofday(&start, NULL);

    int recordSize64KB =  64 * 1024;
    int recordSize1MB =  1024 * 1024;
    int recordSize16MB =  16 * 1024 * 1024;

    int fileSize4MB = 4 * 1024 * 1024;
    int fileSize1GB =  1024 * 1024 * 1024 ;

    int recordSizearray[] = { recordSize64KB, recordSize1MB, recordSize16MB};
    int fileSizearray[] = { fileSize4MB, fileSize1GB};


    pid_t pids[concurencyCount];


    // Create the specified number of processes
    for (int j = 0; j < concurencyCount; j++)
    {
        pids[j] = fork();
        if (pids[j] == -1)
        {
            perror("fork() error");
            exit(EXIT_FAILURE);
        }

        else if (pids[j] == 0)
        {
            // Child process
            printf("\nchild pid=%d",getpid());
            pid_t pid = getpid();
            int pid_as_int = (int)pid;
            char* pid_as_String = intToString(pid_as_int);
            char* filename = "file2";

            //writeFileSequentialAccessWithRecordSizes(recordSizearray[0]/concurencyCount, fileSizearray[0], (char *) "1_SequentialWrite_recordSize64KB_fileSize4MB");
            readFileSequentialAccessWithRecordSizee(recordSizearray[0], fileSizearray[0]/concurencyCount, (char *) filename);
            exit(0);
        }


    }

    // Wait for all child processes to finish
    for (int j = 0; j < concurencyCount; j++)
    {
        wait(NULL);
    }


    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    //elapsed_time = ((double)(end_time - start_time));

    gettimeofday(&end, NULL);
    exec_time = (double) (end.tv_sec - start.tv_sec) + (double) (end.tv_usec - start.tv_usec) / 1000000;
    printf("\nExecution time: %lf seconds\n", exec_time);


}

//@@@@@=======================

































void sequentialRead_recordSize1MB_fileSize4MB(int concurencyCount)
{
    printf("\n=========================================================================");
    printf("\nlog entry:sequentialRead_recordSize1MB_fileSize4MB, concurrency count=%d",concurencyCount);

    // Perform  benchmark
    clock_t start_time, end_time;
    double elapsed_time;
    start_time = clock();


    struct timeval start, end;
    double exec_time;
    gettimeofday(&start, NULL);

    int recordSize64KB =  64 * 1024;
    int recordSize1MB =  1024 * 1024;
    int recordSize16MB =  16 * 1024 * 1024;

    int fileSize4MB = 4 * 1024 * 1024;
    int fileSize1GB =  1024 * 1024 * 1024 ;

    int recordSizearray[] = { recordSize64KB, recordSize1MB, recordSize16MB};
    int fileSizearray[] = { fileSize4MB, fileSize1GB};


    pid_t pids[concurencyCount];


    // Create the specified number of processes
    for (int j = 0; j < concurencyCount; j++)
    {
        pids[j] = fork();
        if (pids[j] == -1)
        {
            perror("fork() error");
            exit(EXIT_FAILURE);
        }

        else if (pids[j] == 0)
        {
            // Child process
            printf("\nchild pid=%d",getpid());
            pid_t pid = getpid();
            int pid_as_int = (int)pid;
            char* pid_as_String = intToString(pid_as_int);
            char* filename = "file2";

            //writeFileSequentialAccessWithRecordSizes(recordSizearray[0]/concurencyCount, fileSizearray[0], (char *) "1_SequentialWrite_recordSize64KB_fileSize4MB");
            readFileSequentialAccessWithRecordSizee(recordSizearray[1], fileSizearray[0]/concurencyCount, (char *) filename);
            exit(0);
        }


    }

    // Wait for all child processes to finish
    for (int j = 0; j < concurencyCount; j++)
    {
        wait(NULL);
    }


    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    //elapsed_time = ((double)(end_time - start_time));

    gettimeofday(&end, NULL);
    exec_time = (double) (end.tv_sec - start.tv_sec) + (double) (end.tv_usec - start.tv_usec) / 1000000;
    printf("\nExecution time: %lf seconds\n", exec_time);


}

//@@@@@=======================

































void sequentialRead_recordSize16MB_fileSize4MB(int concurencyCount)
{
    printf("\n=========================================================================");
    printf("\nlog entry:sequentialRead_recordSize16MB_fileSize4MB, concurrency count=%d",concurencyCount);

    // Perform  benchmark
    clock_t start_time, end_time;
    double elapsed_time;
    start_time = clock();


    struct timeval start, end;
    double exec_time;
    gettimeofday(&start, NULL);

    int recordSize64KB =  64 * 1024;
    int recordSize1MB =  1024 * 1024;
    int recordSize16MB =  16 * 1024 * 1024;

    int fileSize4MB = 4 * 1024 * 1024;
    int fileSize1GB =  1024 * 1024 * 1024 ;

    int recordSizearray[] = { recordSize64KB, recordSize1MB, recordSize16MB};
    int fileSizearray[] = { fileSize4MB, fileSize1GB};


    pid_t pids[concurencyCount];


    // Create the specified number of processes
    for (int j = 0; j < concurencyCount; j++)
    {
        pids[j] = fork();
        if (pids[j] == -1)
        {
            perror("fork() error");
            exit(EXIT_FAILURE);
        }

        else if (pids[j] == 0)
        {
            // Child process
            printf("\nchild pid=%d",getpid());
            pid_t pid = getpid();
            int pid_as_int = (int)pid;
            char* pid_as_String = intToString(pid_as_int);
            char* filename = "file2";

            //writeFileSequentialAccessWithRecordSizes(recordSizearray[0]/concurencyCount, fileSizearray[0], (char *) "1_SequentialWrite_recordSize64KB_fileSize4MB");
            readFileSequentialAccessWithRecordSizee(recordSizearray[2], fileSizearray[0]/concurencyCount, (char *) filename);
            exit(0);
        }


    }

    // Wait for all child processes to finish
    for (int j = 0; j < concurencyCount; j++)
    {
        wait(NULL);
    }


    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    //elapsed_time = ((double)(end_time - start_time));

    gettimeofday(&end, NULL);
    exec_time = (double) (end.tv_sec - start.tv_sec) + (double) (end.tv_usec - start.tv_usec) / 1000000;
    printf("\nExecution time: %lf seconds\n", exec_time);


}

//@@@@@=======================

































void sequentialRead_recordSize64KB_fileSize1GB(int concurencyCount)
{
    printf("\n=========================================================================");
    printf("\nlog entry:sequentialRead_recordSize64KB_fileSize1GB, concurrency count=%d",concurencyCount);

    // Perform  benchmark
    clock_t start_time, end_time;
    double elapsed_time;
    start_time = clock();


    struct timeval start, end;
    double exec_time;
    gettimeofday(&start, NULL);

    int recordSize64KB =  64 * 1024;
    int recordSize1MB =  1024 * 1024;
    int recordSize16MB =  16 * 1024 * 1024;

    int fileSize4MB = 4 * 1024 * 1024;
    int fileSize1GB =  1024 * 1024 * 1024 ;

    int recordSizearray[] = { recordSize64KB, recordSize1MB, recordSize16MB};
    int fileSizearray[] = { fileSize4MB, fileSize1GB};


    pid_t pids[concurencyCount];


    // Create the specified number of processes
    for (int j = 0; j < concurencyCount; j++)
    {
        pids[j] = fork();
        if (pids[j] == -1)
        {
            perror("fork() error");
            exit(EXIT_FAILURE);
        }

        else if (pids[j] == 0)
        {
            // Child process
            printf("\nchild pid=%d",getpid());
            pid_t pid = getpid();
            int pid_as_int = (int)pid;
            char* pid_as_String = intToString(pid_as_int);
            char* filename = "file1";

            //writeFileSequentialAccessWithRecordSizes(recordSizearray[0]/concurencyCount, fileSizearray[0], (char *) "1_SequentialWrite_recordSize64KB_fileSize4MB");
            readFileSequentialAccessWithRecordSizee(recordSizearray[0], fileSizearray[1]/concurencyCount, (char *) filename);
            exit(0);
        }


    }

    // Wait for all child processes to finish
    for (int j = 0; j < concurencyCount; j++)
    {
        wait(NULL);
    }


    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    //elapsed_time = ((double)(end_time - start_time));

    gettimeofday(&end, NULL);
    exec_time = (double) (end.tv_sec - start.tv_sec) + (double) (end.tv_usec - start.tv_usec) / 1000000;
    printf("\nExecution time: %lf seconds\n", exec_time);


}

//@@@@@=======================

































void sequentialRead_recordSize1MB_fileSize1GB(int concurencyCount)
{
    printf("\n=========================================================================");
    printf("\nlog entry:sequentialRead_recordSize1MB_fileSize1GB, concurrency count=%d",concurencyCount);

    // Perform  benchmark
    clock_t start_time, end_time;
    double elapsed_time;
    start_time = clock();


    struct timeval start, end;
    double exec_time;
    gettimeofday(&start, NULL);

    int recordSize64KB =  64 * 1024;
    int recordSize1MB =  1024 * 1024;
    int recordSize16MB =  16 * 1024 * 1024;

    int fileSize4MB = 4 * 1024 * 1024;
    int fileSize1GB =  1024 * 1024 * 1024 ;

    int recordSizearray[] = { recordSize64KB, recordSize1MB, recordSize16MB};
    int fileSizearray[] = { fileSize4MB, fileSize1GB};


    pid_t pids[concurencyCount];


    // Create the specified number of processes
    for (int j = 0; j < concurencyCount; j++)
    {
        pids[j] = fork();
        if (pids[j] == -1)
        {
            perror("fork() error");
            exit(EXIT_FAILURE);
        }

        else if (pids[j] == 0)
        {
            // Child process
            printf("\nchild pid=%d",getpid());
            pid_t pid = getpid();
            int pid_as_int = (int)pid;
            char* pid_as_String = intToString(pid_as_int);
            char* filename = "file1";

            //writeFileSequentialAccessWithRecordSizes(recordSizearray[0]/concurencyCount, fileSizearray[0], (char *) "1_SequentialWrite_recordSize64KB_fileSize4MB");
            readFileSequentialAccessWithRecordSizee(recordSizearray[1], fileSizearray[1]/concurencyCount, (char *) filename);
            exit(0);
        }


    }

    // Wait for all child processes to finish
    for (int j = 0; j < concurencyCount; j++)
    {
        wait(NULL);
    }


    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    //elapsed_time = ((double)(end_time - start_time));

    gettimeofday(&end, NULL);
    exec_time = (double) (end.tv_sec - start.tv_sec) + (double) (end.tv_usec - start.tv_usec) / 1000000;
    printf("\nExecution time: %lf seconds\n", exec_time);


}

//@@@@@=======================

































void sequentialRead_recordSize16MB_fileSize1GB(int concurencyCount)
{
    printf("\n=========================================================================");
    printf("\nlog entry:sequentialRead_recordSize16MB_fileSize1GB, concurrency count=%d",concurencyCount);

    // Perform  benchmark
    clock_t start_time, end_time;
    double elapsed_time;
    start_time = clock();


    struct timeval start, end;
    double exec_time;
    gettimeofday(&start, NULL);

    int recordSize64KB =  64 * 1024;
    int recordSize1MB =  1024 * 1024;
    int recordSize16MB =  16 * 1024 * 1024;

    int fileSize4MB = 4 * 1024 * 1024;
    int fileSize1GB =  1024 * 1024 * 1024 ;

    int recordSizearray[] = { recordSize64KB, recordSize1MB, recordSize16MB};
    int fileSizearray[] = { fileSize4MB, fileSize1GB};


    pid_t pids[concurencyCount];


    // Create the specified number of processes
    for (int j = 0; j < concurencyCount; j++)
    {
        pids[j] = fork();
        if (pids[j] == -1)
        {
            perror("fork() error");
            exit(EXIT_FAILURE);
        }

        else if (pids[j] == 0)
        {
            // Child process
            printf("\nchild pid=%d",getpid());
            pid_t pid = getpid();
            int pid_as_int = (int)pid;
            char* pid_as_String = intToString(pid_as_int);
            char* filename = "file1";

            //writeFileSequentialAccessWithRecordSizes(recordSizearray[0]/concurencyCount, fileSizearray[0], (char *) "1_SequentialWrite_recordSize64KB_fileSize4MB");
            readFileSequentialAccessWithRecordSizee(recordSizearray[2], fileSizearray[1]/concurencyCount, (char *) filename);
            exit(0);
        }


    }

    // Wait for all child processes to finish
    for (int j = 0; j < concurencyCount; j++)
    {
        wait(NULL);
    }


    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    //elapsed_time = ((double)(end_time - start_time));

    gettimeofday(&end, NULL);
    exec_time = (double) (end.tv_sec - start.tv_sec) + (double) (end.tv_usec - start.tv_usec) / 1000000;
    printf("\nExecution time: %lf seconds\n", exec_time);


}

//@@@@@=======================

































void randomRead_recordSize64KB_fileSize4MB(int concurencyCount)
{
    printf("\n=========================================================================");
    printf("\nlog entry:randomRead_recordSize64KB_fileSize4MB, concurrency count=%d",concurencyCount);

    // Perform  benchmark
    clock_t start_time, end_time;
    double elapsed_time;
    start_time = clock();


    struct timeval start, end;
    double exec_time;
    gettimeofday(&start, NULL);

    int recordSize64KB =  64 * 1024;
    int recordSize1MB =  1024 * 1024;
    int recordSize16MB =  16 * 1024 * 1024;

    int fileSize4MB = 4 * 1024 * 1024;
    int fileSize1GB =  1024 * 1024 * 1024 ;

    int recordSizearray[] = { recordSize64KB, recordSize1MB, recordSize16MB};
    int fileSizearray[] = { fileSize4MB, fileSize1GB};


    pid_t pids[concurencyCount];


    // Create the specified number of processes
    for (int j = 0; j < concurencyCount; j++)
    {
        pids[j] = fork();
        if (pids[j] == -1)
        {
            perror("fork() error");
            exit(EXIT_FAILURE);
        }

        else if (pids[j] == 0)
        {
            // Child process
            printf("\nchild pid=%d",getpid());
            pid_t pid = getpid();
            int pid_as_int = (int)pid;
            char* pid_as_String = intToString(pid_as_int);
            char* filename = "file2";

            //writeFileSequentialAccessWithRecordSizes(recordSizearray[0]/concurencyCount, fileSizearray[0], (char *) "1_SequentialWrite_recordSize64KB_fileSize4MB");
            readFileRandomAccesswithRecordSizee(recordSizearray[0], fileSizearray[0]/concurencyCount, (char *) filename);
            exit(0);
        }


    }

    // Wait for all child processes to finish
    for (int j = 0; j < concurencyCount; j++)
    {
        wait(NULL);
    }


    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    //elapsed_time = ((double)(end_time - start_time));

    gettimeofday(&end, NULL);
    exec_time = (double) (end.tv_sec - start.tv_sec) + (double) (end.tv_usec - start.tv_usec) / 1000000;
    printf("\nExecution time: %lf seconds\n", exec_time);


}

//@@@@@=======================

































void randomRead_recordSize1MB_fileSize4MB(int concurencyCount)
{
    printf("\n=========================================================================");
    printf("\nlog entry:randomRead_recordSize1MB_fileSize4MB, concurrency count=%d",concurencyCount);

    // Perform  benchmark
    clock_t start_time, end_time;
    double elapsed_time;
    start_time = clock();


    struct timeval start, end;
    double exec_time;
    gettimeofday(&start, NULL);

    int recordSize64KB =  64 * 1024;
    int recordSize1MB =  1024 * 1024;
    int recordSize16MB =  16 * 1024 * 1024;

    int fileSize4MB = 4 * 1024 * 1024;
    int fileSize1GB =  1024 * 1024 * 1024 ;

    int recordSizearray[] = { recordSize64KB, recordSize1MB, recordSize16MB};
    int fileSizearray[] = { fileSize4MB, fileSize1GB};


    pid_t pids[concurencyCount];


    // Create the specified number of processes
    for (int j = 0; j < concurencyCount; j++)
    {
        pids[j] = fork();
        if (pids[j] == -1)
        {
            perror("fork() error");
            exit(EXIT_FAILURE);
        }

        else if (pids[j] == 0)
        {
            // Child process
            printf("\nchild pid=%d",getpid());
            pid_t pid = getpid();
            int pid_as_int = (int)pid;
            char* pid_as_String = intToString(pid_as_int);
            char* filename = "file2";

            //writeFileSequentialAccessWithRecordSizes(recordSizearray[0]/concurencyCount, fileSizearray[0], (char *) "1_SequentialWrite_recordSize64KB_fileSize4MB");
            readFileRandomAccesswithRecordSizee(recordSizearray[1], fileSizearray[0]/concurencyCount, (char *) filename);
            exit(0);
        }


    }

    // Wait for all child processes to finish
    for (int j = 0; j < concurencyCount; j++)
    {
        wait(NULL);
    }


    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    //elapsed_time = ((double)(end_time - start_time));

    gettimeofday(&end, NULL);
    exec_time = (double) (end.tv_sec - start.tv_sec) + (double) (end.tv_usec - start.tv_usec) / 1000000;
    printf("\nExecution time: %lf seconds\n", exec_time);


}

//@@@@@=======================

































void randomRead_recordSize16MB_fileSize4MB(int concurencyCount)
{
    printf("\n=========================================================================");
    printf("\nlog entry:randomRead_recordSize16MB_fileSize4MB, concurrency count=%d",concurencyCount);

    // Perform  benchmark
    clock_t start_time, end_time;
    double elapsed_time;
    start_time = clock();


    struct timeval start, end;
    double exec_time;
    gettimeofday(&start, NULL);

    int recordSize64KB =  64 * 1024;
    int recordSize1MB =  1024 * 1024;
    int recordSize16MB =  16 * 1024 * 1024;

    int fileSize4MB = 4 * 1024 * 1024;
    int fileSize1GB =  1024 * 1024 * 1024 ;

    int recordSizearray[] = { recordSize64KB, recordSize1MB, recordSize16MB};
    int fileSizearray[] = { fileSize4MB, fileSize1GB};


    pid_t pids[concurencyCount];


    // Create the specified number of processes
    for (int j = 0; j < concurencyCount; j++)
    {
        pids[j] = fork();
        if (pids[j] == -1)
        {
            perror("fork() error");
            exit(EXIT_FAILURE);
        }

        else if (pids[j] == 0)
        {
            // Child process
            printf("\nchild pid=%d",getpid());
            pid_t pid = getpid();
            int pid_as_int = (int)pid;
            char* pid_as_String = intToString(pid_as_int);
            char* filename = "file2";

            //writeFileSequentialAccessWithRecordSizes(recordSizearray[0]/concurencyCount, fileSizearray[0], (char *) "1_SequentialWrite_recordSize64KB_fileSize4MB");
            readFileRandomAccesswithRecordSizee(recordSizearray[2], fileSizearray[0]/concurencyCount, (char *) filename);
            exit(0);
        }


    }

    // Wait for all child processes to finish
    for (int j = 0; j < concurencyCount; j++)
    {
        wait(NULL);
    }


    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    //elapsed_time = ((double)(end_time - start_time));

    gettimeofday(&end, NULL);
    exec_time = (double) (end.tv_sec - start.tv_sec) + (double) (end.tv_usec - start.tv_usec) / 1000000;
    printf("\nExecution time: %lf seconds\n", exec_time);


}

//@@@@@=======================

































void randomRead_recordSize64KB_fileSize1GB(int concurencyCount)
{
    printf("\n=========================================================================");
    printf("\nlog entry:randomRead_recordSize64KB_fileSize1GB, concurrency count=%d",concurencyCount);

    // Perform  benchmark
    clock_t start_time, end_time;
    double elapsed_time;
    start_time = clock();


    struct timeval start, end;
    double exec_time;
    gettimeofday(&start, NULL);

    int recordSize64KB =  64 * 1024;
    int recordSize1MB =  1024 * 1024;
    int recordSize16MB =  16 * 1024 * 1024;

    int fileSize4MB = 4 * 1024 * 1024;
    int fileSize1GB =  1024 * 1024 * 1024 ;

    int recordSizearray[] = { recordSize64KB, recordSize1MB, recordSize16MB};
    int fileSizearray[] = { fileSize4MB, fileSize1GB};


    pid_t pids[concurencyCount];


    // Create the specified number of processes
    for (int j = 0; j < concurencyCount; j++)
    {
        pids[j] = fork();
        if (pids[j] == -1)
        {
            perror("fork() error");
            exit(EXIT_FAILURE);
        }

        else if (pids[j] == 0)
        {
            // Child process
            printf("\nchild pid=%d",getpid());
            pid_t pid = getpid();
            int pid_as_int = (int)pid;
            char* pid_as_String = intToString(pid_as_int);
            char* filename = "file1";

            //writeFileSequentialAccessWithRecordSizes(recordSizearray[0]/concurencyCount, fileSizearray[0], (char *) "1_SequentialWrite_recordSize64KB_fileSize4MB");
            readFileRandomAccesswithRecordSizee(recordSizearray[0], fileSizearray[1]/concurencyCount, (char *) filename);
            exit(0);
        }


    }

    // Wait for all child processes to finish
    for (int j = 0; j < concurencyCount; j++)
    {
        wait(NULL);
    }


    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    //elapsed_time = ((double)(end_time - start_time));

    gettimeofday(&end, NULL);
    exec_time = (double) (end.tv_sec - start.tv_sec) + (double) (end.tv_usec - start.tv_usec) / 1000000;
    printf("\nExecution time: %lf seconds\n", exec_time);


}

//@@@@@=======================

































void randomRead_recordSize1MB_fileSize1GB(int concurencyCount)
{
    printf("\n=========================================================================");
    printf("\nlog entry:randomRead_recordSize1MB_fileSize1GB, concurrency count=%d",concurencyCount);

    // Perform  benchmark
    clock_t start_time, end_time;
    double elapsed_time;
    start_time = clock();


    struct timeval start, end;
    double exec_time;
    gettimeofday(&start, NULL);

    int recordSize64KB =  64 * 1024;
    int recordSize1MB =  1024 * 1024;
    int recordSize16MB =  16 * 1024 * 1024;

    int fileSize4MB = 4 * 1024 * 1024;
    int fileSize1GB =  1024 * 1024 * 1024 ;

    int recordSizearray[] = { recordSize64KB, recordSize1MB, recordSize16MB};
    int fileSizearray[] = { fileSize4MB, fileSize1GB};


    pid_t pids[concurencyCount];


    // Create the specified number of processes
    for (int j = 0; j < concurencyCount; j++)
    {
        pids[j] = fork();
        if (pids[j] == -1)
        {
            perror("fork() error");
            exit(EXIT_FAILURE);
        }

        else if (pids[j] == 0)
        {
            // Child process
            printf("\nchild pid=%d",getpid());
            pid_t pid = getpid();
            int pid_as_int = (int)pid;
            char* pid_as_String = intToString(pid_as_int);
            char* filename = "file1";

            //writeFileSequentialAccessWithRecordSizes(recordSizearray[0]/concurencyCount, fileSizearray[0], (char *) "1_SequentialWrite_recordSize64KB_fileSize4MB");
            readFileRandomAccesswithRecordSizee(recordSizearray[1], fileSizearray[1]/concurencyCount, (char *) filename);
            exit(0);
        }


    }

    // Wait for all child processes to finish
    for (int j = 0; j < concurencyCount; j++)
    {
        wait(NULL);
    }


    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    //elapsed_time = ((double)(end_time - start_time));

    gettimeofday(&end, NULL);
    exec_time = (double) (end.tv_sec - start.tv_sec) + (double) (end.tv_usec - start.tv_usec) / 1000000;
    printf("\nExecution time: %lf seconds\n", exec_time);


}

//@@@@@=======================

































void randomRead_recordSize16MB_fileSize1GB(int concurencyCount)
{
    printf("\n=========================================================================");
    printf("\nlog entry:randomRead_recordSize16MB_fileSize1GB, concurrency count=%d",concurencyCount);

    // Perform  benchmark
    clock_t start_time, end_time;
    double elapsed_time;
    start_time = clock();


    struct timeval start, end;
    double exec_time;
    gettimeofday(&start, NULL);

    int recordSize64KB =  64 * 1024;
    int recordSize1MB =  1024 * 1024;
    int recordSize16MB =  16 * 1024 * 1024;

    int fileSize4MB = 4 * 1024 * 1024;
    int fileSize1GB =  1024 * 1024 * 1024 ;

    int recordSizearray[] = { recordSize64KB, recordSize1MB, recordSize16MB};
    int fileSizearray[] = { fileSize4MB, fileSize1GB};


    pid_t pids[concurencyCount];


    // Create the specified number of processes
    for (int j = 0; j < concurencyCount; j++)
    {
        pids[j] = fork();
        if (pids[j] == -1)
        {
            perror("fork() error");
            exit(EXIT_FAILURE);
        }

        else if (pids[j] == 0)
        {
            // Child process
            printf("\nchild pid=%d",getpid());
            pid_t pid = getpid();
            int pid_as_int = (int)pid;
            char* pid_as_String = intToString(pid_as_int);
            char* filename = "file1";

            //writeFileSequentialAccessWithRecordSizes(recordSizearray[0]/concurencyCount, fileSizearray[0], (char *) "1_SequentialWrite_recordSize64KB_fileSize4MB");
            readFileRandomAccesswithRecordSizee(recordSizearray[2], fileSizearray[1]/concurencyCount, (char *) filename);
            exit(0);
        }


    }

    // Wait for all child processes to finish
    for (int j = 0; j < concurencyCount; j++)
    {
        wait(NULL);
    }


    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    //elapsed_time = ((double)(end_time - start_time));

    gettimeofday(&end, NULL);
    exec_time = (double) (end.tv_sec - start.tv_sec) + (double) (end.tv_usec - start.tv_usec) / 1000000;
    printf("\nExecution time: %lf seconds\n", exec_time);


}

//@@@@@=======================
































void workWithConcurrency11(int concurencyCount)
{


    randomRead_recordSize64KB_fileSize4MB(concurencyCount);


}





void workWithConcurrency(int concurencyCount)
{
    sequentialWrite_recordSize64KB_fileSize4MB(concurencyCount);
    sequentialWrite_recordSize1MB_fileSize4MB(concurencyCount);
    sequentialWrite_recordSize16MB_fileSize4MB(concurencyCount);
    sequentialWrite_recordSize64KB_fileSize1GB(concurencyCount);
    sequentialWrite_recordSize1MB_fileSize1GB(concurencyCount);
    sequentialWrite_recordSize16MB_fileSize1GB(concurencyCount);


    randomWrite_recordSize64KB_fileSize4MB(concurencyCount);
    randomWrite_recordSize1MB_fileSize4MB(concurencyCount);
    randomWrite_recordSize16MB_fileSize4MB(concurencyCount);
    randomWrite_recordSize64KB_fileSize1GB(concurencyCount);
    randomWrite_recordSize1MB_fileSize1GB(concurencyCount);
    randomWrite_recordSize16MB_fileSize1GB(concurencyCount);


    sequentialRead_recordSize64KB_fileSize4MB(concurencyCount);
    sequentialRead_recordSize1MB_fileSize4MB(concurencyCount);
    sequentialRead_recordSize16MB_fileSize4MB(concurencyCount);
    sequentialRead_recordSize64KB_fileSize1GB(concurencyCount);
    sequentialRead_recordSize1MB_fileSize1GB(concurencyCount);
    sequentialRead_recordSize16MB_fileSize1GB(concurencyCount);



    randomRead_recordSize64KB_fileSize4MB(concurencyCount);
    randomRead_recordSize1MB_fileSize4MB(concurencyCount);
    randomRead_recordSize16MB_fileSize4MB(concurencyCount);
    randomRead_recordSize64KB_fileSize1GB(concurencyCount);
    randomRead_recordSize1MB_fileSize1GB(concurencyCount);
    randomRead_recordSize16MB_fileSize1GB(concurencyCount);

}




int main(int argc, char **argv)
{
    int processCount;
    if(argc !=2){
        printf("argument count is not equal to 2");
        return -1;
    }
    processCount = atoi(argv[1]);

    printf("\nrunning file benchmark");
    printf("\nprocessCount=%d",processCount);

    workWithConcurrency(processCount);


    //workWithConcurrency11(processCount);


    //int numProcesses[] = {1,2, 4, 8};
//    int numProcesses[] = {8};
//    int numOfProcessArraySize=sizeof(numProcesses) / sizeof(numProcesses[0]);

    //for (int i = 0; i < numOfProcessArraySize; i++)
//    {
//        int processCount = numProcesses[i];
//        workWithConcurrency(processCount);
//    }

    return 0;
}
