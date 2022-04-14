/**
 * @file main.c
 * @author Arnauld BIGANZOLI <biganzoli@laplace.univ-tlse.fr>
 * @brief Serial Port Programming using Win32 API
 * @version 0.1
 * @date 2022-04-14
 *
 * @copyright Copyright (c) 2022
 * @src https://www.xanthium.in/Serial-Port-Programming-using-Win32-API
 */

#include <windows.h>
#include <stdio.h>
//#include <stdlib.h>

char buffer[256] = {0};

int main()
{
    HANDLE hComm;

    hComm = CreateFile("\\\\.\\COM10",               // port name (com0com: COM10 <=> COM11)
                       GENERIC_READ | GENERIC_WRITE, // Read/Write
                       0,                            // No Sharing
                       NULL,                         // No Security
                       OPEN_EXISTING,                // Open existing port only
                       0,                            // Non Overlapped I/O
                       NULL);                        // Null for Comm Devices

    if (hComm == INVALID_HANDLE_VALUE)
        printf("Error in opening serial port\r\n");
    else
        printf("Opening serial port successful\r\n");

    while (1)
    {
        DWORD number_bytes_read;

        if (ReadFile(hComm, buffer, 256, &number_bytes_read, NULL))
        {
            if (number_bytes_read > 0)
            {
                printf("Nombre de caractere dans le buffer : %ld\r\n", number_bytes_read);
                printf("Lecture du buffer : %s\r\n", buffer);

                // Si le buffer contient le message "hello", alors on retourne le message "world"
                if (strstr(buffer, "hello"))
                    WriteFile(hComm, " world!\r\n", 9, &number_bytes_read, NULL);

                // Si le buffer contient le message "exit", alors on termine le programme
                if (strstr(buffer, "exit"))
                    break;
                memset(buffer, 0, 256);
            }
        }
        else
        {
            printf("Error in reading serial port\r\n");
        }
    }

    printf("Serial port closed\r\n");
    CloseHandle(hComm); // Closing the Serial Port

    return 0;
}
